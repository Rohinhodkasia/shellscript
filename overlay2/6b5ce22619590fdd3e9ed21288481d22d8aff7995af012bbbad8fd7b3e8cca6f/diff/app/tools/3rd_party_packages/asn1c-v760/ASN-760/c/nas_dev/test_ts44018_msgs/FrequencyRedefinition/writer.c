#include "TS44018Msgs.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300

int main (int argc, char** argv)
{
   TS44018Msg_DL_DCCH_PDU pdu;
   TS44018Msg_FrequencyRedefinition data;
   TS44018Msg_FrequencyRedefinition* pvalue = &data;

   OSCTXT	ctxt;
   OSOCTET	msgbuf[MAXMSGLEN], *msgptr;
   const char*  filename = "message.dat";
   OSSIZE       len;
   int		i, ret;
   OSBOOL       verbose = FALSE;

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
   rtxSetDiag (&ctxt, verbose);

   /* Populate data structure */

   asn1Init_TS44018Msg_DL_DCCH_PDU (&pdu);
   pdu.l3HdrOpts.t = 1;
   pdu.l3HdrOpts.u.skipInd = 0;
   pdu.protoDiscr = TS24007L3_ProtoDiscr_rrMgmt;
   pdu.msgType = ASN1V_ts44018Msg_mt_FrequencyRedefinition;
   pdu.data.t = T_TS44018Msgs_DL_DCCH_Messages_obj_FrequencyRedefinition;
   pdu.data.u.obj_FrequencyRedefinition = pvalue;


   asn1Init_TS44018Msg_FrequencyRedefinition (pvalue);

   pvalue->channelDescr.channel_type_and_TDMA_offset = 24;

   pvalue->channelDescr.tn = 5;

   pvalue->channelDescr.tsc = 3;

   pvalue->channelDescr.component_4.t =  2;

   pvalue->channelDescr.component_4.u.choice_2.spare_bit = 0;

   pvalue->channelDescr.component_4.u.choice_2.arfcn = 307;

   pvalue->mobileAllocation.length = 17;

   pvalue->mobileAllocation.mac.numbits = 136;
   pvalue->mobileAllocation.mac.data[0] = 0x6f;
   pvalue->mobileAllocation.mac.data[1] = 0x6d;
   pvalue->mobileAllocation.mac.data[2] = 0x55;
   pvalue->mobileAllocation.mac.data[3] = 0x64;
   pvalue->mobileAllocation.mac.data[4] = 0x39;
   pvalue->mobileAllocation.mac.data[5] = 0x74;
   pvalue->mobileAllocation.mac.data[6] = 0x55;
   pvalue->mobileAllocation.mac.data[7] = 0x63;
   pvalue->mobileAllocation.mac.data[8] = 0x3f;
   pvalue->mobileAllocation.mac.data[9] = 0x66;
   pvalue->mobileAllocation.mac.data[10] = 0x66;
   pvalue->mobileAllocation.mac.data[11] = 0x4a;
   pvalue->mobileAllocation.mac.data[12] = 0x75;
   pvalue->mobileAllocation.mac.data[13] = 0x3f;
   pvalue->mobileAllocation.mac.data[14] = 0x56;
   pvalue->mobileAllocation.mac.data[15] = 0x4c;
   pvalue->mobileAllocation.mac.data[16] = 0x3f;

   pvalue->startingTime.t1prime = 3;

   pvalue->startingTime.t3 = 34;

   pvalue->startingTime.spare_bit = 30;

   pvalue->m.cellChannelDescrPresent = 1;
   pvalue->cellChannelDescr.t =  2;

   pvalue->cellChannelDescr.u.choice_2.spare_bit = 1;

   pvalue->cellChannelDescr.u.choice_2.component_2.t =  2;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_512[0] = 0xdb;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_512[1] = 0xfe;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_512[2] = 0xc4;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_512[3] = 0x56;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_512[4] = 0x58;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_512[5] = 0xcd;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_512[6] = 0xea;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_512[7] = 0x9;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_512[8] = 0x48;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_512[9] = 0x83;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_512[10] = 0x49;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_512[11] = 0xa2;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_512[12] = 0xa3;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_512[13] = 0x22;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_512[14] = 0xe6;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_512[15] = 0xc3;

   pvalue->m.carrierIndicationPresent = 1;

   pvalue->carrierIndication.spare_bit = 0;

   pvalue->carrierIndication.ci = 0;

   pvalue->m.mobileAllocationC2Present = 1;

   pvalue->mobileAllocationC2.length = 44;

   pvalue->mobileAllocationC2.mac.numbits = 352;
   pvalue->mobileAllocationC2.mac.data[0] = 0x63;
   pvalue->mobileAllocationC2.mac.data[1] = 0x3f;
   pvalue->mobileAllocationC2.mac.data[2] = 0x35;
   pvalue->mobileAllocationC2.mac.data[3] = 0x70;
   pvalue->mobileAllocationC2.mac.data[4] = 0x72;
   pvalue->mobileAllocationC2.mac.data[5] = 0x55;
   pvalue->mobileAllocationC2.mac.data[6] = 0x59;
   pvalue->mobileAllocationC2.mac.data[7] = 0x38;
   pvalue->mobileAllocationC2.mac.data[8] = 0x6e;
   pvalue->mobileAllocationC2.mac.data[9] = 0x4a;
   pvalue->mobileAllocationC2.mac.data[10] = 0x5e;
   pvalue->mobileAllocationC2.mac.data[11] = 0x32;
   pvalue->mobileAllocationC2.mac.data[12] = 0x31;
   pvalue->mobileAllocationC2.mac.data[13] = 0x4f;
   pvalue->mobileAllocationC2.mac.data[14] = 0x48;
   pvalue->mobileAllocationC2.mac.data[15] = 0x56;
   pvalue->mobileAllocationC2.mac.data[16] = 0x68;
   pvalue->mobileAllocationC2.mac.data[17] = 0x5d;
   pvalue->mobileAllocationC2.mac.data[18] = 0x5c;
   pvalue->mobileAllocationC2.mac.data[19] = 0x30;
   pvalue->mobileAllocationC2.mac.data[20] = 0x4b;
   pvalue->mobileAllocationC2.mac.data[21] = 0x64;
   pvalue->mobileAllocationC2.mac.data[22] = 0x5c;
   pvalue->mobileAllocationC2.mac.data[23] = 0x50;
   pvalue->mobileAllocationC2.mac.data[24] = 0x66;
   pvalue->mobileAllocationC2.mac.data[25] = 0x35;
   pvalue->mobileAllocationC2.mac.data[26] = 0x41;
   pvalue->mobileAllocationC2.mac.data[27] = 0x40;
   pvalue->mobileAllocationC2.mac.data[28] = 0x64;
   pvalue->mobileAllocationC2.mac.data[29] = 0x5d;
   pvalue->mobileAllocationC2.mac.data[30] = 0x6e;
   pvalue->mobileAllocationC2.mac.data[31] = 0x46;
   pvalue->mobileAllocationC2.mac.data[32] = 0x58;
   pvalue->mobileAllocationC2.mac.data[33] = 0x60;
   pvalue->mobileAllocationC2.mac.data[34] = 0x57;
   pvalue->mobileAllocationC2.mac.data[35] = 0x6b;
   pvalue->mobileAllocationC2.mac.data[36] = 0x39;
   pvalue->mobileAllocationC2.mac.data[37] = 0x6d;
   pvalue->mobileAllocationC2.mac.data[38] = 0x75;
   pvalue->mobileAllocationC2.mac.data[39] = 0x3e;
   pvalue->mobileAllocationC2.mac.data[40] = 0x5f;
   pvalue->mobileAllocationC2.mac.data[41] = 0x36;
   pvalue->mobileAllocationC2.mac.data[42] = 0x33;
   pvalue->mobileAllocationC2.mac.data[43] = 0x70;

   pvalue->m.channelDescriptionC2Present = 1;

   pvalue->channelDescriptionC2.tsc = 0;

   pvalue->channelDescriptionC2.component_2.t =  1;

   pvalue->channelDescriptionC2.component_2.u.choice_1.maio = 53;

   pvalue->channelDescriptionC2.component_2.u.choice_1.hsn = 21;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018Msg_DL_DCCH_PDU (&ctxt, &pdu);
   if (0 != ret) {
      printf ("encode PDU failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);

      printf ("Bit fields:\n");
      rtxDiagBitTracePrint (ctxt.pBitFldList, "");
      printf ("\n");

      return ret;
   }
   /* Verify buffer is byte-aligned */
   OSRTASSERT (ctxt.buffer.bitOffset == 8 || ctxt.buffer.bitOffset == 0);

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
