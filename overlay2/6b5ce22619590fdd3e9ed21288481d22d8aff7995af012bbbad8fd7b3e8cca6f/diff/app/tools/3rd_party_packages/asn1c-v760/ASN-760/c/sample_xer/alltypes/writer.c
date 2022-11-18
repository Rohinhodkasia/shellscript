/* This test driver program encodes a data record and writes the        */
/* encoded result to an output file..                                   */

#include <stdio.h>
#include <stdlib.h>
#include "Test.h"

#define MAXMSGLEN 40960

static void fill_Name (Name* pName, char* fn, char* mi, char* ln);
static void fill_jSmith (OSCTXT* pctxt, TestType* pPR);

int main (int argc, char** argv)
{
   TestType     testData;
   OSCTXT       ctxt;
   OSOCTET      msgbuf[MAXMSGLEN];
   int          i, j, lseq[1024], stat;
   size_t       s;
   const char*  filename = "message.xml";
   OSBOOL       verbose = FALSE, trace = TRUE, cxer = FALSE;
   FILE*        fp;
   OSUINT32     melem[] = { married, single, divorced, children };
   OSREAL       relem[] = { 1.0, 3.14159, 2e-2, 3, 4, 5, 6, 0};
   OSBOOL       belem[] = { 0,1,1,0,1};
   OSOCTET      bs[10], *pdata;
   ChoiceType   choices[3];
   Name         name;
   TestType_iseqof_element ielem[] = { 0,1,2,3,4 };
   char         chs[2049];
   OSOCTET      ocs[2048];
   ASN1OpenType ot;
   static OSOCTET otdata[] = { 0x9F, 0x32, 0x04, 0x06, 0x54, 0x32, 0x10 };
   ASN1DynBitStr* pbitstr;
   TestType_bsseqof2_element* pseqofbitstr;
   ASN1DynOctStr* poctstr;
   static const char* seqofstr[] = { "Objective", "Systems", "Inc." };
   static const OSUTF8CHAR* seqoidstr[] = { 
         (const unsigned char *)"/ISO/Test-IRI",
         (const unsigned char *)"/ISO/Test-Systems" };

   /* Process command line arguments */

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

   /* Init */

   if (rtXmlInitContext (&ctxt) != 0) {
      rtxErrPrint (&ctxt);
      return -1;
   }
   rtxSetDiag (&ctxt, verbose);

   rtXmlSetEncBufPtr(&ctxt, msgbuf, sizeof(msgbuf));
   if (cxer) rtxCtxtSetFlag(&ctxt, OSXMLC14N);

   /* Populate structure of generated type */
   memset (&testData, 0, sizeof (testData));

   testData.utc = "031231235538-0406";
   testData.utc1 = "040229190538Z";
   testData.gtc = "20030101020538.00+0430";
   testData.gtc1 = "20040229190538.3141Z";

   testData.bs0.numbits = 10*8 - 2;
   testData.bs0.data = bs;
   for (s = 0; s < sizeof (bs); s++)
      bs[s] = (OSOCTET) (0xAA* (s + 1));

   testData.bs1.numbits = 8;
   testData.bs1.data[0] = 0;
   rtxSetBit (testData.bs1.data, testData.bs1.numbits, TestType_bs1_zero_1);
   rtxSetBit (testData.bs1.data, testData.bs1.numbits, TestType_bs1_a_1);
   rtxSetBit (testData.bs1.data, testData.bs1.numbits, TestType_bs1_b_1);
   rtxSetBit (testData.bs1.data, testData.bs1.numbits, TestType_bs1_c_1);

   testData.bs2.numbits = 0;
   testData.bs2.data = 0;

   testData.bs3.numbits = 7;
   testData.bs3.data[0] = 0;
   rtxSetBit (testData.bs3.data, testData.bs3.numbits, BS3_zero);
   rtxSetBit (testData.bs3.data, testData.bs3.numbits, BS3_a);
   rtxSetBit (testData.bs3.data, testData.bs3.numbits, BS3_b);
   rtxSetBit (testData.bs3.data, testData.bs3.numbits, BS3_c);

   for (s = 0; s < sizeof (chs);s++) {
      chs [s] = (char)(s%62 + 'A');
   }
   chs[sizeof(chs)-1] = '\0';
   testData.cs = chs;
   
   {
      OSUINT32 nchars;
      rtxUTF8ToDynUniStr32(&ctxt, "Àðòåì", 
            &testData.unis.data, &nchars);
      testData.unis.nchars = nchars;
   }

   {
      OSUINT32 nchars;
      rtxUTF8ToDynUniStr(&ctxt, "Àðòåì Áîëãàð", 
            &testData.bmps.data, &nchars);
      testData.bmps.nchars = nchars;
   }

   for (s = 0; s < sizeof (ocs);s++) {
      ocs [s] = (OSOCTET)s;
   }
   testData.os.numocts = sizeof (ocs);
   testData.os.data = ocs;

   testData.val1 = 21;
   testData.val2 = value2;
   testData.bi = "-658728037322887475642149743974551809";
   testData.enum_ = yes;
   
   testData.real = 3.14159;
   testData.nan = rtxGetNaN();
   
   testData.boolean_ = 1;
   
   testData.oid = oid;
   testData.roid = roid;
   testData.oid_iri = OSUTF8("/ISO/Test-IRI");
   testData.rel_oid_iri = OSUTF8("Test-IRI");
   
   fill_jSmith (&ctxt, &testData);
   fill_Name (&testData.child.name, "AAA", "SSS", "BBB");
   testData.child.dateOfBirth = "aaaaaaaaa";

   testData.seqofEnum.n = 4;
   testData.seqofEnum.elem = melem;

   rtxDListInit (&testData.bsseqof1);
   for (i = 0; i < 4; i++) {
      pbitstr = rtxMemAllocType (&ctxt, ASN1DynBitStr);
      pbitstr->numbits = 5*8 - 1;
      pdata = (OSOCTET*) rtxMemAlloc (&ctxt, 5);
      for (j = 0; j < 5; j++) {
         pdata[j] = (OSOCTET) ((i + 1)* (j + 1) * 0xCC);
      }
      pbitstr->data = pdata;
      rtxDListAppend (&ctxt, &testData.bsseqof1, (void*)pbitstr);
   }

   rtxDListInit (&testData.bsseqof2);
   for (i = 0; i < 4; i++) {
      pseqofbitstr = rtxMemAllocType (&ctxt, TestType_bsseqof2_element);
      pseqofbitstr->numbits = 7;
      for (j = 0; j < 1; j++) {
         pseqofbitstr->data[j] = (OSOCTET) ((i + 1)* (j + 1) * 0xCC);
      }
      rtxDListAppend (&ctxt, &testData.bsseqof2, (void*)pseqofbitstr);
   }

   rtxDListInit (&testData.osseqof1);
   for (i = 0; i < 4; i++) {
      poctstr = rtxMemAllocType (&ctxt, ASN1DynOctStr);
      poctstr->numocts = 5;
      pdata = (OSOCTET*) rtxMemAlloc (&ctxt, 5);
      for (j = 0; j < 5; j++) {
         pdata[j] = (OSOCTET) ((i + 1)* (j + 1) * 0xCC);
      }
      poctstr->data = pdata;
      rtxDListAppend (&ctxt, &testData.osseqof1, (void*)poctstr);
   }

   rtxDListInit (&testData.csseqof1);
   for (i = 0; i < 3; i++) {
      rtxDListAppend (&ctxt, &testData.csseqof1, (void*)seqofstr[i]);
   }

   testData.rseqof.n = 8;
   testData.rseqof.elem = relem;
   relem[3] = rtxGetMinusZero();
   relem[4] = rtxGetMinusInfinity();
   relem[5] = rtxGetNaN();
   relem[6] = rtxGetPlusInfinity();

   testData.bseqof.n = 5;
   testData.bseqof.elem = belem;

   testData.iseqof.n = 5;
   testData.iseqof.elem = ielem;

   for (i = 0; i < 20; i++)
      lseq[i] = i;
   testData.iseqof1.n = 20;
   testData.iseqof1.elem = lseq;

   testData.iseqof2.n = 5;
   testData.iseqof2.elem[0] = 1;
   testData.iseqof2.elem[1] = 2;
   testData.iseqof2.elem[2] = 3;
   testData.iseqof2.elem[3] = 4;
   testData.iseqof2.elem[4] = 5;

   rtxDListInit (&testData.seqofChoice);
   choices[0].t = T_ChoiceType_e1;
   choices[0].u.e1 = 1;
   rtxDListAppend (&ctxt, &testData.seqofChoice, &choices[0]);
   choices[1].t = T_ChoiceType_e2;
   choices[1].u.e2 = "String data";
   rtxDListAppend (&ctxt, &testData.seqofChoice, &choices[1]);
   choices[2].t = T_ChoiceType_e3;
   fill_Name (&name, "Art", "S", "Bolgar");
   choices[2].u.e3 = &name;
   rtxDListAppend (&ctxt, &testData.seqofChoice, &choices[2]);

   rtxDListInit (&testData.seqofOidIri);
   for (i = 0; i < 2; i++) {
      rtxDListAppend (&ctxt, &testData.seqofOidIri, (void*)seqoidstr[i]);
   }

   ot.data = otdata;
   ot.numocts = sizeof (otdata);
   rtxDListAppend (&ctxt, &testData.extElem1, &ot);

   /* Encode */

   stat = XmlEnc_TestType_PDU (&ctxt, &testData);

   if (stat == 0) {
      if (trace) {
         printf ("encoded XML message:\n");
         printf ("%s\n", (char*)msgbuf);
      }
   }
   else {
      printf ("Encoding failed\n");
      rtxErrPrint (&ctxt);
      exit (-1);
   }
  
   /* Write the encoded message out to the output file */

   if ((fp = fopen (filename, "wb")) != NULL) {
      fputs ((char*)msgbuf, fp);
      fclose (fp);
   }
   else {
      printf ("Error opening %s for write access\n", filename);
      return -1;
   }
   rtFreeContext (&ctxt);
   return 0;

}

/* Routine to fill the testData record with test data */

static void fill_jSmith (OSCTXT* pctxt, TestType* pPR)
{
   ChildInformation* pChildInfo;

   fill_Name (&pPR->name, "John", "P", "Smith");

   rtxDListInit (&pPR->children);

   /* fill first child record */

   pChildInfo = rtxMemAllocType (pctxt, ChildInformation);
   fill_Name (&pChildInfo->name, "Ralph", "T", "Smith");
   pChildInfo->dateOfBirth = "19571111";
   rtxDListAppend (pctxt, &pPR->children, pChildInfo);

   /* fill second child record */

   pChildInfo = rtxMemAllocType (pctxt, ChildInformation);
   fill_Name (&pChildInfo->name, "Susan", "B", "Jones");
   pChildInfo->dateOfBirth = "19590717";
   rtxDListAppend (pctxt, &pPR->children, pChildInfo);
}

/* Routine to fill a name structure */

static void fill_Name (Name* pName, char* fn, char* mi, char* ln)
{
   pName->givenName = fn;
   pName->initial = mi;
   pName->familyName = ln;
}

