/* Program to read a binary file and dump in hex format to stdout */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char** argv)
{
   FILE*    fp;
   char     hexstr[49], ascstr[17];
   size_t   ai = 0, i = 0;
   int      ch;
   unsigned int  ui;
   unsigned char b, ascii = 1, string = 0;
   const char* filename = 0;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < (size_t)argc; i++) {
         if (*argv[i] == '-') {
            if (!strcmp (argv[i], "-noascii")) {
               ascii = 0;  /* do not dump ASCII characters */
            }
            else if (!strcmp (argv[i], "-string")) {
               string = 1; /* dump as contiguous string of hex chars */
            }
         }
         else {
            filename = argv[i];
         }
      }
   }

   if (0 == filename) {
      printf ("usage: hexdump <filename> [-noascii]\n");
      return -1;
   }

   fp = fopen (filename, "rb");
   if (0 == fp) {
      printf ("file '%s' could not be opened for read access\n", filename);
      return -2;
   }

   if (!string) {
      memset (hexstr, ' ', 48); hexstr[48] = '\0';
      memset (ascstr, ' ', 16); ascstr[16] = '\0';
   }

   for (i = 0;;)
   {
      ch = fgetc (fp);
      if (ch == EOF) break;

      if (string) {
         printf ("%02x", ch);
         continue;
      }
      b = (unsigned char) ch;
      ui = b >> 4;
      hexstr[i] = (char)((ui <= 9) ? ui + '0' : ui - 10 + 'a');
      ui = b & 0x0F;  /* shave off MS nibble */
      hexstr[i+1] = (char)((ui <= 9) ? ui + '0' : ui - 10 + 'a');
      hexstr[i+2] = (i < sizeof(hexstr) - 2) ? ' ' : '\0';
      if (ascii) {
         ascstr[ai++] = (char) (isprint(b) ? b : '.');
      }
      i += 3;

      if (i >= sizeof(hexstr)-1)
      {
         printf ("%s %s\n", hexstr, ascstr);

         memset (hexstr, ' ', 48);
         memset (ascstr, ' ', 16);
         ai = 0; i = 0;
      }
   }

   if (i > 0 && !string) printf ("%48s %s\n", hexstr, ascstr);

   return 0;
}
