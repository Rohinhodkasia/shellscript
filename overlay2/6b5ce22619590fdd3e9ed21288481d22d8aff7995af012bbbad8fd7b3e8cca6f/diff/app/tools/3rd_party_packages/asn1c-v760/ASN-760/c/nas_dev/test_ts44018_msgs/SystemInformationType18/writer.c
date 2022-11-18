#include "TS44018Msgs.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300


TS44018IE_SI18_Rest_Octets* asn1Test_TS44018IE_SI18_Rest_Octets (OSCTXT* pctxt)
{
   TS44018IE_SI18_Rest_Octets* pvalue = rtxMemAllocType (pctxt, TS44018IE_SI18_Rest_Octets);
   asn1Init_TS44018IE_SI18_Rest_Octets (pvalue);

   pvalue->si18_change_mark = 2;

   pvalue->si18_index = 4;

   pvalue->si18_last = 0;

   pvalue->spare_bit = 2;

   pvalue->non_GSM_Message.non_GSM_Protocol_Discriminator = 2;

   pvalue->non_GSM_Message.nr_of_container_octets = 6;

   switch (pvalue->non_GSM_Message.nr_of_container_octets) {
      /* choice-1 */
      case 0:
         break;

      /* choice-2 */
      default:

         pvalue->non_GSM_Message.component_3.u.choice_2.container.n = 6;
         pvalue->non_GSM_Message.component_3.u.choice_2.container.elem[0] = 121;

         pvalue->non_GSM_Message.component_3.u.choice_2.container.elem[1] = 6;

         pvalue->non_GSM_Message.component_3.u.choice_2.container.elem[2] = 18;

         pvalue->non_GSM_Message.component_3.u.choice_2.container.elem[3] = 70;

         pvalue->non_GSM_Message.component_3.u.choice_2.container.elem[4] = 199;

         pvalue->non_GSM_Message.component_3.u.choice_2.container.elem[5] = 25;

         pvalue->non_GSM_Message.component_3.u.choice_2.m.non_GSM_Message_structPresent = 1;
         pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct = rtxMemAllocTypeZ (pctxt, TS44018IE_Non_GSM_Message_struct);

         pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->non_GSM_Protocol_Discriminator = 3;

         pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->nr_of_container_octets = 5;

         switch (pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->nr_of_container_octets) {
            /* choice-1 */
            case 0:
               break;

            /* choice-2 */
            default:

               pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.container.n = 5;
               pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.container.elem[0] = 163;

               pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.container.elem[1] = 244;

               pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.container.elem[2] = 85;

               pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.container.elem[3] = 34;

               pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.container.elem[4] = 226;

               pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.m.non_GSM_Message_structPresent = 1;
               pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct = rtxMemAllocTypeZ (pctxt, TS44018IE_Non_GSM_Message_struct);

               pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->non_GSM_Protocol_Discriminator = 3;

               pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->nr_of_container_octets = 1;

               switch (pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->nr_of_container_octets) {
                  /* choice-1 */
                  case 0:
                     break;

                  /* choice-2 */
                  default:

                     pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.container.n = 1;
                     pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.container.elem[0] = 189;

                     pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.m.non_GSM_Message_structPresent = 1;
                     pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct = rtxMemAllocTypeZ (pctxt, TS44018IE_Non_GSM_Message_struct);

                     pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->non_GSM_Protocol_Discriminator = 3;

                     pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->nr_of_container_octets = 7;

                     switch (pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->nr_of_container_octets) {
                        /* choice-1 */
                        case 0:
                           break;

                        /* choice-2 */
                        default:

                           pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.container.n = 7;
                           pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.container.elem[0] = 25;

                           pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.container.elem[1] = 90;

                           pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.container.elem[2] = 188;

                           pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.container.elem[3] = 13;

                           pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.container.elem[4] = 107;

                           pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.container.elem[5] = 219;

                           pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.container.elem[6] = 250;

                           pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.m.non_GSM_Message_structPresent = 1;
                           pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct = rtxMemAllocTypeZ (pctxt, TS44018IE_Non_GSM_Message_struct);

                           pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->non_GSM_Protocol_Discriminator = 6;

                           pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->nr_of_container_octets = 7;

                           switch (pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->nr_of_container_octets) {
                              /* choice-1 */
                              case 0:
                                 break;

                              /* choice-2 */
                              default:

                                 pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.container.n = 7;
                                 pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.container.elem[0] = 108;

                                 pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.container.elem[1] = 218;

                                 pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.container.elem[2] = 87;

                                 pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.container.elem[3] = 178;

                                 pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.container.elem[4] = 162;

                                 pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.container.elem[5] = 112;

                                 pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.container.elem[6] = 252;

                                 pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.m.non_GSM_Message_structPresent = 1;
                                 pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct = rtxMemAllocTypeZ (pctxt, TS44018IE_Non_GSM_Message_struct);

                                 pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->non_GSM_Protocol_Discriminator = 1;

                                 pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->nr_of_container_octets = 0;

                           }
                           break;

                     }
                     break;

               }
               break;

         }
         break;

   }
   return (pvalue);
}


int main (int argc, char** argv)
{
   TS44018Msg_L2_PSEUDO_LEN_PDU pdu;

   OSCTXT	ctxt;
   OSCTXT*  pctxt = &ctxt;
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

   asn1Init_TS44018Msg_L2_PSEUDO_LEN_PDU (&pdu);
   pdu.l3HdrOpts.t = 1;
   pdu.l3HdrOpts.u.skipInd = 0;
   pdu.protoDiscr = TS24007L3_ProtoDiscr_rrMgmt;
   pdu.msgType = ASN1V_ts44018Msg_mt_SystemInformationType18;
   pdu.data.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType18;

   pdu.restOctets.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType18;
   pdu.restOctets.u.obj_SystemInformationType18 =
      asn1Test_TS44018IE_SI18_Rest_Octets(pctxt);


   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018Msg_L2_PSEUDO_LEN_PDU (&ctxt, &pdu);
   if (0 != ret) {
      printf ("encode PDU failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
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
