/* Dump the contents of a pcapng file as documented at:
   https://github.com/pcapng/pcapng */

#include "rtxsrc/rtxErrCodes.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

typedef struct {
   OSOCTET block_type[4];   /* Block Type = 0x0A0D0D0A */
   OSUINT32 block_len;      /* Block total length */
   OSUINT32 magic_number;   /* magic number */
   OSUINT16 version_major;  /* major version number */
   OSUINT16 version_minor;  /* minor version number */

} pcapng_secthdr;

#define DECODEINT(numbuf, nbytes, pvalue, swapped) \
{ int i; *pvalue = 0; \
if (swapped) { \
   for (i = nbytes-1; i >= 0; i--) { *pvalue = *pvalue * 256 + numbuf[i]; } \
} \
else { \
   for (i = 0; i < nbytes; i++) { *pvalue = *pvalue * 256 + numbuf[i]; } \
}}

static int decodeLen (FILE* fp, OSSIZE* plen, OSBOOL swapped)
{
   OSOCTET lenbuf[4];
   if (fread (lenbuf, 1, 4, fp) != 4) {
      printf ("invalid length, unexpected EOF\n");
      return RTERR_ENDOFBUF;
   }
   DECODEINT (lenbuf, 4, plen, swapped);
   return 0;
}

static int hexdump (FILE* fp, OSSIZE nbytes)
{
   OSOCTET ub;
   OSSIZE  i;
   for (i = 0; i < nbytes; i++) {
      if (fread (&ub, 1, 1, fp) != 1) {
         printf ("ERROR: unexpected EOF\n");
         return RTERR_ENDOFBUF;
      }
      printf ("%02x ", ub);
      if ((i + 1) % 16 == 0)
         printf ("\n");
   }
   printf ("\n");
   return 0;
}

int main (int argc, char** argv)
{
   FILE* fp;
   OSSIZE len = 0;
   OSOCTET lenbuf[4];
   OSOCTET numbuf[8];
   OSBOOL swapped;
   int blockType, stat;

   if (argc != 2) {
      printf ("usage: dumppcap <filename>\n");
      printf ("  <filename>  Name of file in libpcap format\n");
      return 0;
   }

   stat = rtxFileOpen (&fp, argv[1], "rb");
   if (0 != stat) {
      perror ("fopen");
      printf ("filename: '%s'\n", argv[1]);
      return stat;
   }

   /* Block type */
   len = fread (numbuf, 1, 4, fp);
   if (len == 4) {
      if (numbuf[0] == 0x0a && numbuf[1] == 0x0d &&
          numbuf[2] == 0x0d && numbuf[3] == 0x0a) {
         printf ("section header..\n");

         /* length */
         if (fread (lenbuf, 1, 4, fp) != 4) {
            printf ("invalid length, unexpected EOF\n");
            return RTERR_ENDOFBUF;
         }

         /* magic number */
         if (fread (numbuf, 1, 4, fp) == 4) {
            /* Check magic number */
            int i;
            swapped = (numbuf[0] == 0x4d);
            printf ("Magic number: ");
            for (i = 0; i < 4; i++) {
               printf ("0x%02x ", numbuf[i]);
            }
            if (swapped) printf ("  (swapped)");
            printf ("\n");
         }
         else {
            printf ("Unexpected EOF, not enough bytes for magic number\n");
            return RTERR_ENDOFBUF;
         }

         /* Decode length */
         DECODEINT (lenbuf, 4, &len, swapped);
         printf ("block length = " OSSIZEFMT "\n", len);

         /* Skip to end of block */
         if (len >= 12) {
            if (fseek (fp, len - 12, SEEK_CUR) != 0) {
               printf ("error skipping header block\n");
               return RTERR_READERR;
            }

            for (;;) {
               /* read next block type */
               len = fread (numbuf, 1, 4, fp);
               if (0 == len) break;
               else if (len != 4) {
                  printf ("invalid length, unexpected EOF\n");
                  return RTERR_ENDOFBUF;
               }

               DECODEINT (numbuf, 4, &blockType, swapped);
               printf ("next block type = %d\n", blockType);

               /* length */
               len = fread (lenbuf, 1, 4, fp);
               if (len != 4) {
                  printf ("invalid length, unexpected EOF\n");
                  return RTERR_ENDOFBUF;
               }
               DECODEINT (lenbuf, 4, &len, swapped);
               printf ("block length = " OSSIZEFMT "\n", len);

               if (6 == blockType) {
                  /* enhanced packet block */
                  /* skip to captured packet length */
                  if (0 == fseek (fp, 12, SEEK_CUR)) {
                     OSSIZE cplen, oplen;

                     stat = decodeLen (fp, &cplen, swapped);
                     if (0 != stat) return stat;
                     printf ("captured packet length = " OSSIZEFMT "\n", cplen);

                     stat = decodeLen (fp, &oplen, swapped);
                     if (0 != stat) return stat;
                     printf ("original packet length = " OSSIZEFMT "\n", oplen);

                     long fpos = ftell (fp);
                     printf ("current file position is %ld\n", fpos);

                     /* dump packet data */
                     stat = hexdump (fp, cplen);
                     if (0 != stat) return stat;

                     /* skip to end of block */
                     if (len >= 28) {
                        if (0 != fseek (fp, len - (cplen + 28), SEEK_CUR)) {
                           printf ("error skipping to end of EPB\n");
                           return RTERR_READERR;
                        }
                     }
                     else {
                        printf ("ERROR: invalid EPB length, "
                                "must be at least 28\n");
                        break;
                     }
                  }
                  else {
                     printf ("Error skipping to packet length field\n");
                  }
               }
               else {
                  /* skip block */
                  if (len >= 8) {
                     if (0 != fseek (fp, len - 8, SEEK_CUR)) {
                        printf ("error skipping header block\n");
                        return RTERR_READERR;
                     }
                  }
                  else {
                     printf ("ERROR: invalid length, must be at least 8\n");
                     break;
                  }
               }
            }
         }
         else {
            printf ("ERROR: invalid length, must be at least 12\n");
         }
      }
   }
   else {
      printf ("Unexpected EOF, not enough bytes for block type\n");
      return RTERR_ENDOFBUF;
   }

   return 0;
}




