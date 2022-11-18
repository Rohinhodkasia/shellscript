/* This test driver program encodes a data record and writes the        */
/* encoded result to an output file..                                   */

#include <stdio.h>
#include <stdlib.h>
#include "Test.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxReal.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 40960

static void fill_Name (ASN1T_Name* pName, 
                       const char* fn, const char* mi, const char* ln);


DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   OSOCTET      msgbuf[MAXMSGLEN];
   int          i, j, stat;
   const char*  filename = "message.xml";
   OSBOOL       verbose = FALSE, trace = TRUE, cxer = FALSE;
   OSUINT32     melem[] = { 0, 1, 100, 1000};
   ASN1T_TestType_iseqof_element ielem[] = { 0,1,2,3,4 };
   OSREAL       relem[] = { 1.0, 3.14159, 2e-2, 3, 4, 5, 6, 0};
   OSBOOL       belem[] = { 0,1,1,0,1};
   int lseq[1024];
   OSOCTET bs[10];
   ASN1T_ChoiceType choices[3];
   ASN1T_Name name;

   // Process command line arguments 

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else if (!strcmp (argv[i], "-cxer")) cxer = TRUE;
         else {
            printf ("usage: writer [ -v ] [ -o <filename>] [ -cxer ]\n");
            printf ("   -cxer          use canonical XER rules (CXER)\n");
            printf ("   -v             verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace       do not display trace info\n");
            return 0;
         }
      }
   }

   // Create an instance of the compiler generated class.  This
   // example uses a static message buffer..

   OSXMLEncodeBuffer encodeBuffer (msgbuf, sizeof(msgbuf));
   if (cxer) rtxCtxtSetFlag (encodeBuffer.getCtxtPtr(), OSXMLC14N);

   ASN1T_TestType testData;
   ASN1C_TestType testC (encodeBuffer, testData);
   OSCTXT& ctxt = *encodeBuffer.getCtxtPtr ();

   /* Populate structure of generated type */

   testData.utc = "030922190538-0400";
   testData.utc1 = "040229190538Z";
   testData.gtc = "20030922190538.3141+0430";
   testData.gtc1 = "20040229190538.3141Z";

   testData.real = 3.14159;
   testData.m.boolean_Present = 1;
   testData.boolean_ = 1;
   testData.nan = rtxGetNaN();
   testData.enum_ = TestType_enum_::yes;
   testData.iseqof2.n = 5;
   testData.iseqof2.elem[0] = 1;
   testData.iseqof2.elem[1] = 2;
   testData.iseqof2.elem[2] = 3;
   testData.iseqof2.elem[3] = 4;
   testData.iseqof2.elem[4] = 5;

   testData.seqofEnum.n = 4;
   testData.seqofEnum.elem = melem;

   testData.iseqof.n = 5;
   testData.iseqof.elem = ielem;

   relem[3] = rtxGetMinusZero();
   relem[4] = rtxGetMinusInfinity();
   relem[5] = rtxGetNaN();
   relem[6] = rtxGetPlusInfinity();
   testData.rseqof.n = 8;
   testData.rseqof.elem = relem;

   testData.bseqof.n = 5;
   testData.bseqof.elem = belem;

   testData.m.bs3Present = 1;
   testData.bs3.numbits = 7;
   testData.bs3.data[0] = 0;
   rtxSetBit (testData.bs3.data, testData.bs3.numbits, ASN1C_BS3::zero);
   rtxSetBit (testData.bs3.data, testData.bs3.numbits, ASN1C_BS3::a);
   rtxSetBit (testData.bs3.data, testData.bs3.numbits, ASN1C_BS3::b);
   rtxSetBit (testData.bs3.data, testData.bs3.numbits, ASN1C_BS3::c);

   testData.bs1.numbits = 8;
   testData.bs1.data[0] = 0;
   rtxSetBit (testData.bs1.data, testData.bs1.numbits, 
             ASN1C_TestType_bs1::zero);
   rtxSetBit (testData.bs1.data, testData.bs1.numbits, ASN1C_TestType_bs1::a);
   rtxSetBit (testData.bs1.data, testData.bs1.numbits, ASN1C_TestType_bs1::b);
   rtxSetBit (testData.bs1.data, testData.bs1.numbits, ASN1C_TestType_bs1::c);

   testData.bs0.numbits = 10*8 - 2;
   testData.bs0.data = bs;
   for (i = 0; i < sizeof (bs); i++)
      bs[i] = (OSOCTET) (0xAA* (i + 1));

   testData.bs2.numbits = 0;
   testData.bs2.data = 0;

   ASN1C_TestType_bsseqof1 bsseqof1_ListHelper (testC, testData.bsseqof1);
   for (i = 0; i < 4; i++) {
      OSOCTET* data;
      ASN1TDynBitStr* pbitstr = bsseqof1_ListHelper.NewElement();
      
      pbitstr->numbits = 5*8 - 1;
      data = (OSOCTET*) testC.memAlloc (5);
      pbitstr->data = data;
      for (j = 0; j < 5; j++) {
         data[j] = (OSOCTET) ((i + 1)* (j + 1) * 0xCC);
      }

      bsseqof1_ListHelper.Append (pbitstr);
   }

   testData.m.bsseqof2Present = 1;
   ASN1C__SeqOfTestType_bsseqof2_element 
      bsseqof2_ListHelper (testC, testData.bsseqof2);

   for (i = 0; i < 4; i++) {
      ASN1T_TestType_bsseqof2_element* 
         pElem = bsseqof2_ListHelper.NewElement();

      pElem->numbits = 7;
      for (j = 0; j < 1; j++) {
         pElem->data[j] = (OSOCTET) ((i + 1)* (j + 1) * 0xCC);
      }

      bsseqof2_ListHelper.Append (pElem);
   }

   ASN1C_TestType_osseqof1 osseqof1_ListHelper (testC, testData.osseqof1);
   ASN1TDynOctStr* poctstr;

   for (i = 0; i < 4; i++) {
      OSOCTET* data;

      poctstr = osseqof1_ListHelper.NewElement();
      poctstr->numocts = 5;
      data = (OSOCTET*) testC.memAlloc (5);
      poctstr->data = data;
      for (j = 0; j < 5; j++) {
         data[j] = (OSOCTET) ((i + 1)* (j + 1) * 0xCC);
      }
      osseqof1_ListHelper.Append (poctstr);
   }
   testData.m.osseqof1Present = 1;

   ASN1C_TestType_csseqof1 csseqof1_ListHelper (testC, testData.csseqof1);
   for (i = 0; i < 3; i++) {
      static const char* str[] = { "Objective", "Systems", "Inc." };

      csseqof1_ListHelper.Append (str[i]);
   }

   testData.val1 = 21;
   testData.val2 = TestType_val2::value2;

   testData.m.nullvalPresent = 1;

   for (i = 0; i < 20; i++)
      lseq[i] = i;
   testData.iseqof1.n = 20;
   testData.iseqof1.elem = lseq;

   ASN1C__SeqOfChoiceType seqofChoiceC (encodeBuffer, testData.seqofChoice);

   choices[0].t = T_ChoiceType_e1;
   choices[0].u.e1 = 1;
   seqofChoiceC.append (&choices[0]);

   choices[1].t = T_ChoiceType_e2;
   choices[1].u.e2 = "String data";
   seqofChoiceC.append (&choices[1]);

   choices[2].t = T_ChoiceType_e3;
   fill_Name (&name, "Art", "S", "Bolgar");
   choices[2].u.e3 = &name;
   seqofChoiceC.append (&choices[2]);

   ASN1T_ChildInformation* pChildInfo;
   ASN1C__SeqOfChildInformation 
      children_ListHelper (testC, testData.children);

   fill_Name (&testData.name, "John", "P", "Smith");

   // fill first child record

   pChildInfo = children_ListHelper.NewElement();
   fill_Name (&pChildInfo->name, "Ralph", "T", "Smith");
   pChildInfo->dateOfBirth = "19571111";
   children_ListHelper.Append (pChildInfo);

   // fill second child record

   pChildInfo = children_ListHelper.NewElement();
   fill_Name (&pChildInfo->name, "Susan", "B", "Jones");
   pChildInfo->dateOfBirth = "19590717";
   children_ListHelper.Append (pChildInfo);

   /* Encode */

   if ((stat = testC.Encode()) == 0) {
      if (trace) {
         printf ("encoded XML message:\n");
         printf ((const char*)msgbuf);
         printf ("\n");
      }
   }
   else {
      printf ("Encoding failed\n");
      encodeBuffer.printErrorInfo ();
      exit (-1);
   }
  
   /* Write the encoded message out to the output file */

   if (encodeBuffer.write (filename) < 0) {
      printf ("Error writing XML document to file '%s'\n", filename);
      return -1;
   }

   return 0;
}

// Routine to fill the test record with test data 

// Routine to fill a name structure

static void fill_Name (ASN1T_Name* pName, 
                       const char* fn, const char* mi, const char* ln)
{
   pName->givenName = fn;
   pName->initial = mi;
   pName->familyName = ln;
}

