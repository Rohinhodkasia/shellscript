#include "TS24301Msgs.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"
#include "rt3gppsrc/rt3gppNasSec.h"

#define MAXMSGLEN 300

int main (int argc, char** argv)
{
   TS24301Msg_PDU pdu;
   TS24301Msg_GUTIReallocCmd data;
   TS24301Msg_GUTIReallocCmd* pvalue = &data;
   OSCTXT	ctxt;
   OSOCTET	msgbuf[MAXMSGLEN], *msgptr;
   const char*  filename = "message.dat";
   OSSIZE       len;
   int		i, ret;
   OSBOOL verbose = FALSE;
   OSCrypt128Key integKey = {
      0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
      0x98, 0x76, 0x54, 0x32, 0x10, 0xfe, 0xdc, 0xba
   };
   OSCrypt128Key encryptKey = {
      0x98, 0x76, 0x54, 0x32, 0x10, 0xfe, 0xdc, 0xba,
      0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef
   };

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else {
            printf ("usage: writer [-v]\n");
            printf ("   -v  verbose mode: print trace info\n");
            return 0;
         }
      }
   }

   /* Initialize context structure */

   ret = rtInitContext (&ctxt);
   if (0 != ret) {
      printf ("rtInitContext failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
      return ret;
   }

   ret = rtx3gppSecInitialize(&ctxt);
   if (0 != ret) {
      rtxErrPrint (&ctxt);
   }

   ret = rtx3gppAssignAlgorithmKeys (&ctxt, &integKey, &encryptKey,
      OS3GPPSecAlgorithm_AES, OS3GPPSecAlgorithm_AES);
   if ( ret == RTERR_NOTSUPP ) {
      printf ("Warning: unable to set AES algorithm; falling back to "
              "NULL algorithm.\n");
      rtxErrReset (&ctxt);
      ret = rtx3gppAssignAlgorithmKeys (&ctxt, NULL, NULL, 
         OS3GPPSecAlgorithm_NULL_ALG, OS3GPPSecAlgorithm_NULL_ALG);
   }
   if (0 != ret) {
      rtxErrPrint (&ctxt);
   }

   ctxt.p3gppSec->count = 15;
   ctxt.p3gppSec->bearerId = 0;
   ctxt.p3gppSec->direction = 0; /*uplink*/

   /* Populate data structure */

   asn1Init_TS24301Msg_PDU (&pdu);
   pdu.m.secHdrPresent = 1;
   pdu.secHdr.secHdrType = TS24007L3_SecHdrType_integProt;
   pdu.secHdr.protoDiscr = TS24007L3_ProtoDiscr_epsMobMgmt;
   pdu.secHdr.msgAuthCode = 12345678;
   pdu.secHdr.seqNumber  = 1;
   pdu.l3HdrOpts.t = T_TS24007L3_L3HdrOptions_secHdr;
   pdu.l3HdrOpts.u.secHdr = 0;
   pdu.protoDiscr = TS24007L3_ProtoDiscr_epsMobMgmt;
   asn1SetTC_TS24301Msg_PDU_obj_GUTIReallocCmd (&ctxt, &pdu, pvalue);

   asn1Init_TS24301Msg_GUTIReallocCmd (pvalue);

   pvalue->guti.length = 0; /* will be calculated */
   pvalue->guti.filler = 7;
   pvalue->guti.oddEvenInd = FALSE;
   pvalue->guti.typeOfIdent = TS24301IE_EPSMobileIdentity_typeOfIdent_imsi;

   switch (pvalue->guti.typeOfIdent) {
      /* guti */
      case 6:
         rtxStrncpy(pvalue->guti.content.u.guti.mcc_mnc.mcc,
                    sizeof(pvalue->guti.content.u.guti.mcc_mnc.mcc), "648", 4);
         rtxStrncpy(pvalue->guti.content.u.guti.mcc_mnc.mnc,
                    sizeof(pvalue->guti.content.u.guti.mcc_mnc.mnc), "03", 4);
         {
            static const OSOCTET testdata[] = {
            0x70, 0xc1 };
            OSCRTLMEMCPY ((void*)pvalue->guti.content.u.guti.mmeGroupID, testdata, 2);
         }
         pvalue->guti.content.u.guti.mmeCode = 216;
         {
            static const OSOCTET testdata[] = {
            0x59, 0x86, 0x36, 0x2 };
            OSCRTLMEMCPY ((void*)pvalue->guti.content.u.guti.tmsi, testdata, 4);
         }
         break;

      /* imsi */
      case 1:
         /* Populate the Character String */
         rtxStrncpy(pvalue->guti.content.u.imsi,
                    sizeof(pvalue->guti.content.u.imsi), "##b*0b60744447", 15);
         break;

      /* imei */
      case 3:
         /* Populate the Character String */
         rtxStrncpy(pvalue->guti.content.u.imei,
                    sizeof(pvalue->guti.content.u.imei), "##b*0b60744447", 15);
         break;
   }

   pvalue->m.taiListPresent = 1;
   pvalue->taiList.length = 0;

   pvalue->taiList.idents.n = 1;
   pvalue->taiList.idents.elem[0].spare = 0;
   pvalue->taiList.idents.elem[0].typeOfList = 1;
   pvalue->taiList.idents.elem[0].numElements = 9;

   switch (pvalue->taiList.idents.elem[0].typeOfList) {
      /* partTrkIdentList0 */
      case 0:
         rtxStrncpy(pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList0.mcc_mnc.mcc,
                    sizeof(pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList0.mcc_mnc.mcc),
                    "646", 4);

         rtxStrncpy(pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList0.mcc_mnc.mnc,
                    sizeof(pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList0.mcc_mnc.mnc),
                    "01", 4);

         pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList0.tacs.n = 5;
         {
            static const OSOCTET testdata[] = {
            0x11, 0x79 };
            OSCRTLMEMCPY ((void*)pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList0.tacs.elem[0].data, testdata, 2);
         }
         {
            static const OSOCTET testdata[] = {
            0x65, 0x93 };
            OSCRTLMEMCPY ((void*)pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList0.tacs.elem[1].data, testdata, 2);
         }
         {
            static const OSOCTET testdata[] = {
            0xc4, 0xf6 };
            OSCRTLMEMCPY ((void*)pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList0.tacs.elem[2].data, testdata, 2);
         }
         {
            static const OSOCTET testdata[] = {
            0xe5, 0x41 };
            OSCRTLMEMCPY ((void*)pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList0.tacs.elem[3].data, testdata, 2);
         }
         {
            static const OSOCTET testdata[] = {
            0x51, 0x4a };
            OSCRTLMEMCPY ((void*)pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList0.tacs.elem[4].data, testdata, 2);
         }
         break;

      /* partTrkIdentList1 */
      case 1:
         rtxStrncpy(pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList1.mcc_mnc.mcc,
                    sizeof(pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList1.mcc_mnc.mcc),
                    "622", 4);
         rtxStrncpy(pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList1.mcc_mnc.mnc,
                    sizeof(pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList1.mcc_mnc.mnc),
                    "01", 4);

         {
            static const OSOCTET testdata[] = {
            0x76, 0xe5 };
            OSCRTLMEMCPY ((void*)pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList1.tac.data, testdata, 2);
         }
         break;

      /* partTrkIdentList2 */
      case 2:
         pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList2.n = 1;
         rtxStrncpy(pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList2.elem[0].mcc_mnc.mcc,
                    sizeof(pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList2.elem[0].mcc_mnc.mcc),
                    "520", 4);
         rtxStrncpy(pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList2.elem[0].mcc_mnc.mnc,
                    sizeof(pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList2.elem[0].mcc_mnc.mnc),
                    "99", 4);
         {
            static const OSOCTET testdata[] = {
            0x1c, 0xc4 };
            OSCRTLMEMCPY ((void*)pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList2.elem[0].tac.data, testdata, 2);
         }
         break;

   }

   pvalue->m._v16ExtPresent = 1;
   pvalue->m.ueRadioCapIdPresent = 1;
   pvalue->ueRadioCapId.capId.numocts = 2;
   pvalue->ueRadioCapId.capId.data = (OSOCTET *)rtxMemAlloc(&ctxt, 2);
   {
      static const OSOCTET testdata[] = { 0xab, 0xcd };
      OSCRTLMEMCPY((void *)pvalue->ueRadioCapId.capId.data, testdata, 2);
   }

   pvalue->m.ueRadioCapIdDelIndPresent = 1;
   pvalue->ueRadioCapIdDelInd.deletionReq = 5;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Encode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS24301Msg_PDU (&ctxt, &pdu);
   if (0 != ret) {
      printf ("encode PDU failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
      printf ("Bit fields:\n");
      rtxDiagBitTracePrint (ctxt.pBitFldList, "");
      printf ("\n");
      return ret;
   }
   msgptr = rtxCtxtGetMsgPtr (&ctxt);
   len = rtxCtxtGetMsgLen (&ctxt);

   if (verbose) {
      printf ("Encoding was successful\n");
      printf ("Hex dump of encoded record:\n");
      rtxHexDump (msgptr, len);
      printf ("\n");
      printf ("Bit fields:\n");
      rtxDiagBitTracePrint (ctxt.pBitFldList, "");
      printf ("\n");
   }

   /* Verify buffer is byte-aligned */
   OSRTASSERT (ctxt.buffer.bitOffset == 8 || ctxt.buffer.bitOffset == 0);

   /* Write encoded message to output file */

   ret = rtxFileWriteBinary (filename, msgptr, len);
   if (0 != ret) {
      printf ("rtxFileWriteBinary failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
      return ret;
   }

   rtxFreeContext (&ctxt);

   return 0;
}
