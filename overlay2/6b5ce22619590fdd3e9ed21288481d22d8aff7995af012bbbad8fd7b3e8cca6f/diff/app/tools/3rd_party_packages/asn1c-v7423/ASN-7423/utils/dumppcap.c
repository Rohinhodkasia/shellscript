/* Dump the contents of a libpcap file as documented at:
   http://wiki.wireshark.org/Development/LibpcapFileFormat */

#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

typedef struct pcap_hdr_s {
   OSUINT32 magic_number;   /* magic number */
   OSUINT16 version_major;  /* major version number */
   OSUINT16 version_minor;  /* minor version number */
   OSINT32  thiszone;       /* GMT to local correction */
   OSUINT32 sigfigs;        /* accuracy of timestamps */
   OSUINT32 snaplen;        /* max length of captured packets, in octets */
   OSUINT32 network;        /* data link type */
} pcap_hdr_t;

typedef struct pcaprec_hdr_s {
   OSUINT32 ts_sec;         /* timestamp seconds */
   OSUINT32 ts_usec;        /* timestamp microseconds */
   OSUINT32 incl_len;       /* number of octets of packet saved in file */
   OSUINT32 orig_len;       /* actual length of packet */
} pcaprec_hdr_t;

#define DECODEINT(numbuf, nbytes, pvalue, swapped) \
{ int i; *pvalue = 0; \
if (swapped) { \
   for (i = nbytes-1; i >= 0; i--) { *pvalue = *pvalue * 256 + numbuf[i]; } \
} \
else { \
   for (i = 0; i < nbytes; i++) { *pvalue = *pvalue * 256 + numbuf[i]; } \
}}

static int writePacketFile (int pktno, const OSOCTET* pktbuf, size_t pktlen)
{
   char filename[32];
   sprintf (filename, "packet%d.bin", pktno);
   return rtxFileWriteBinary (filename, pktbuf, pktlen);
}

int main (int argc, char** argv)
{
   FILE* fp;
   long len;
   int  i, pktno = 1, stat;
   OSINT32 int32;
   OSUINT32 uint32, pktlen;
   OSUINT16 uint16;
   OSOCTET numbuf[8];
   OSOCTET* packetbuf;
   OSBOOL swapped;

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

   len = fread (numbuf, 1, 4, fp);
   if (len == 4) {
      /* Check magic number */
      swapped = (numbuf[0] == 0xd4);
      printf ("Magic number: ");
      for (i = 0; i < 4; i++) {
         printf ("0x%02x ", numbuf[i]);
      }
      if (swapped) printf ("  (swapped)");
      printf ("\n");
   }

   printf ("*** SECTION HEADER ***\n");
   len = fread (numbuf, 1, 2, fp);
   if (len == 2) {
      DECODEINT (numbuf, 2, &uint16, swapped);
      printf ("Major version: %hd\n", uint16);
   }

   len = fread (numbuf, 1, 2, fp);
   if (len == 2) {
      DECODEINT (numbuf, 2, &uint16, swapped);
      printf ("Minor version: %hd\n", uint16);
   }

   len = fread (numbuf, 1, 4, fp);
   if (len == 4) {
      DECODEINT (numbuf, 4, &int32, swapped);
      printf ("GMT time offset: %d\n", int32);
   }

   len = fread (numbuf, 1, 4, fp);
   if (len == 4) {
      DECODEINT (numbuf, 4, &uint32, swapped);
      printf ("Accuracy of timestamps: %u\n", uint32);
   }

   len = fread (numbuf, 1, 4, fp);
   if (len == 4) {
      DECODEINT (numbuf, 4, &uint32, swapped);
      printf ("Max length of captured packets: %u\n", uint32);
   }

   len = fread (numbuf, 1, 4, fp);
   if (len == 4) {
      DECODEINT (numbuf, 4, &uint32, swapped);
      printf ("Data link type: %u\n", uint32);
   }

   while ((len = fread (numbuf, 1, 4, fp)) == 4) {
      printf ("\n");
      printf ("*** PACKET HEADER ***\n");

      DECODEINT (numbuf, 4, &uint32, swapped);
      printf ("Timestamp seconds: %u\n", uint32);

      len = fread (numbuf, 1, 4, fp);
      if (len == 4) {
         DECODEINT (numbuf, 4, &uint32, swapped);
         printf ("Timestamp microseconds: %u\n", uint32);
      }
      else break;

      len = fread (numbuf, 1, 4, fp);
      if (len == 4) {
         DECODEINT (numbuf, 4, &pktlen, swapped);
         printf ("Packet length (in file): %u\n", pktlen);
      }
      else break;

      len = fread (numbuf, 1, 4, fp);
      if (len == 4) {
         DECODEINT (numbuf, 4, &uint32, swapped);
         printf ("Packet length (actual): %u\n", uint32);
      }
      else break;

      /* Read and dump packet */

      packetbuf = (OSOCTET*) malloc (pktlen);
      if (0 == packetbuf) {
         printf ("ERROR: could not allocate packet buffer.\n");
         return -1;
      }
      len = fread (packetbuf, 1, pktlen, fp);
      if (len == (long)pktlen) {
         rtxHexDump (packetbuf, pktlen);
         writePacketFile (pktno++, packetbuf, pktlen);
      }
      free (packetbuf);
   }

   fclose (fp);

   return 0;
}
