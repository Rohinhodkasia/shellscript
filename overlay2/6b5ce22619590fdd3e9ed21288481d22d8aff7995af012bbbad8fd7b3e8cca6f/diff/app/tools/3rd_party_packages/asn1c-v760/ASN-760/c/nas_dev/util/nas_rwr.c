/* NAS read-write-read program.  This program accepts as input an L3    */
/* message from a hex string and then decodes it, re-encodes it, and    */
/* then decodes it again.  It then compares the re-encoded bit pattern  */
/* with the original to look for differences and compares the 2nd       */
/* decoded structure with the first to see if there are differences     */
/* there..                                                              */

#include <stdio.h>
#include "TS24008Msgs.h"
#include "TS24011Msgs.h"
#include "TS24301Msgs.h"
#include "rtxsrc/rtxBitDecode.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxPrint.h"
#include "rtxsrc/rtxPrintStream.h"

static int usage() {
   static const char* usageText = 
   "usage: reader -hex <string> [-msgtype <type>] [-bittrace]\n"
   "   -hex      Hexadecimal string containing encoded message.\n"
   "   -msgfile  File containing hex strings to be decoded, one per line\n"
   "   -msgtype  Type of message to be decoded. Valid values are \n"
   "             nas3g, naslte, and rrc. Default is nas3g.\n"
   "   -bittrace Print bit trace of decoded bit patterns.\n";

   printf ("%s\n", usageText);

   return 0;
}

typedef enum { notSet, nas3G, nasLTE, sms, rrc } MsgType;

static int rwrMessage 
(OSCTXT* pctxt, const char* hexmsg, int idx, MsgType msgType, OSBOOL bitTrace);

int main (int argc, char** argv)
{
   OSCTXT	ctxt;
   const char*  hexmsg = 0;
   const char*  msgfile = 0;
   int          i, ret;
   OSBOOL       bitTrace = FALSE;
   OSBOOL       verbose = FALSE;
   MsgType      msgType = notSet;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-bittrace")) {
            bitTrace = TRUE;
         }
         else if (!strcmp (argv[i], "-v")) {
            bitTrace = TRUE;
            verbose = TRUE;
         }
         else if (!strcmp (argv[i], "-msgtype")) {
            if (i < argc) {
               const char* msgTypeText = argv[++i];
               if (0 == rtxStricmp (msgTypeText, "nas3g")) {
                  msgType = nas3G;
               }
               else if (0 == rtxStricmp (msgTypeText, "naslte")) {
                  msgType = nasLTE;
               }
               else if (0 == rtxStricmp (msgTypeText, "sms")) {
                  msgType = sms;
               }
               else if (0 == rtxStricmp (msgTypeText, "rrc")) {
                  msgType = rrc;
               }
               else {
                  printf ("invalid message type argument - "
                          "must be nas3G, nasLTE, or RRC\n");
                  return -1;
               }
            }
            else {
               printf ("message type argument missing\n");
               return -1;
            }
         }
         else if (!strcmp (argv[i], "-hex")) {
            if (i < argc) {
               hexmsg = argv[++i];
            }
            else {
               printf ("hex message text argument missing\n");
               return -1;
            }
         }
         else if (!strcmp (argv[i], "-msgfile")) {
            if (i < argc) {
               msgfile = argv[++i];
            }
            else {
               printf ("message file argument missing\n");
               return -1;
            }
         }
         else {
            return usage();
         }
      }
   }

   if (0 == hexmsg && 0 == msgfile) {
      printf ("ERROR: -hex <string> or -msgfile <file> is required\n\n");
      return usage();
   }

   /* Initialize context structure */

   ret = rtInitContext (&ctxt);
   if (0 != ret) {
      printf ("rtInitContext failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
      return ret;
   }
   rtxSetDiag (&ctxt, verbose);

   if (0 != hexmsg) {
      ret = rwrMessage (&ctxt, hexmsg, 0, msgType, bitTrace);
   }
   else { /* message file */
      char lbuf[1024];
      FILE* fp;
      int ret2 = 0;

      ret = rtxFileOpen (&fp, msgfile, "r");
      if (0 != ret) {
         printf ("Open message file '%s' failed.\n");
         return ret;
      }

      i = 0;
      while (0 != fgets (lbuf, sizeof(lbuf), fp)) {
         ret = rwrMessage (&ctxt, lbuf, i++, msgType, bitTrace);
         if (0 != ret && 0 == ret2) ret2 = ret;
      }

      fclose (fp);
      ret = ret2;
   }

   rtxFreeContext (&ctxt);

   return ret;
}

static int rwrMessage 
(OSCTXT* pctxt, const char* hexmsg, int idx, MsgType msgType, OSBOOL bitTrace)
{
   TS24008Msg_PDU ts24008PDU;
   TS24301Msg_PDU ts24301PDU;
   TS24011Msg_CP_PDU ts24011PDU;
   TS24011Msg_RP_PDU ts24011RPDU;
   OSOCTET*     msgbuf1;
   OSOCTET      msgbuf2[256];
   OSSIZE       msglen1, msglen2;
   OSBOOL       rpduDecoded = FALSE;
   int          i, ret;

   RTDIAG2 (pctxt, "Processing message %s\n", hexmsg);

   ret = rtxHexCharsToBinCount (hexmsg, 0);
   if (ret >= 0) {
      msgbuf1 = (OSOCTET*) rtxMemAlloc (pctxt, ret);
      if (0 == msgbuf1) {
         printf ("ERROR: No memory available for message buffer "
                 "(%d bytes)\n", ret);
         return RTERR_NOMEM;
      }
      ret = rtxHexCharsToBin (hexmsg, 0, msgbuf1, ret);
      if (ret < 0) {
         printf ("ERROR: Conversion of hex chars to binary failed, "
                 "status = %d\n", ret);
         return ret;
      }
      else msglen1 = (OSSIZE) ret;
   }
   else {
      printf ("ERROR: rtxHexCharsToBinCount failed, status = %d\n", ret);
      return ret;
   }

   /* Set message buffer pointer */

   ret = rtxCtxtSetBufPtr (pctxt, msgbuf1, msglen1);
   if (0 != ret) {
      printf ("rtxCtxtSetBufPtr failed; status = %d\n", ret);
      rtxErrPrint (pctxt);
      return ret;
   }

   /* If message type not set, attempt to determine by decoding L3 header */

   if (msgType == notSet) {
      OSRTBufSave savedBuf;
      OSOCTET ub, pd;
   
      OSRTBUFSAVE2 (pctxt, &savedBuf);
   
      /* decode security header type */
      ret = rtxDecBitsToByte (pctxt, &ub, 4);
      if (0 != ret) return LOG_RTERR (pctxt, ret);
   
      /* decode protocol discriminator */
      ret = rtxDecBitsToByte (pctxt, &pd, 4);
      if (ret < 0) return LOG_RTERR (pctxt, ret);
   
      OSRTBUFRESTORE2 (pctxt, &savedBuf);

      switch (pd) {
      case TS24007L3_ProtoDiscr_epsMobMgmt:
      case TS24007L3_ProtoDiscr_epsSessMgmt:
         msgType = nasLTE;
         break;

      case TS24007L3_ProtoDiscr_mobMgmt:
      case TS24007L3_ProtoDiscr_callCtrl:
      case TS24007L3_ProtoDiscr_gprsMobMgmt:
      case TS24007L3_ProtoDiscr_sessMgmt:
         msgType = nas3G;
         break;

      case TS24007L3_ProtoDiscr_sms:
         msgType = sms;
         break;

      default:
         printf ("ERROR: protocol discriminator %s not supported\n", 
                 TS24007L3_ProtoDiscr_ToString (pd));
         rtxFreeContext (pctxt);
         return 0;
      }
   }

   for (i = 0; i < 2; i++) {
      /* Enable bit tracing */

      if (bitTrace) {
         rtxDiagCtxtBitFieldListInit (pctxt);
      }

      /* Call decode function */

      switch (msgType) {
      case nas3G:
         ret = NASDec_TS24008Msg_PDU (pctxt, &ts24008PDU);
         break;

      case nasLTE:
         ret = NASDec_TS24301Msg_PDU (pctxt, &ts24301PDU);
         break;

      case sms:
         /* Decode CP message */
         ret = NASDec_TS24011Msg_CP_PDU (pctxt, &ts24011PDU);
         if (0 == ret) {
            if (ts24011PDU.data.t == 
                T_TS24011Msgs_TS24011_OBJECTSET_obj_CP_DATA) {

               if (bitTrace) {
                  printf ("CPDATA bit fields:\n");
                  rtxDiagBitTracePrint (pctxt->pBitFldList, "");
                  printf ("\n");

                  rtxDiagCtxtBitFieldListInit (pctxt);
               }

               /* Set message buffer pointer to point at CP-DATA contents */
               ret = rtxCtxtSetBufPtr 
                  (pctxt, ts24011PDU.data.u.obj_CP_DATA->cpUserData.data, 
                   ts24011PDU.data.u.obj_CP_DATA->cpUserData.numocts);

               if (0 != ret) {
                  printf ("rtxCtxtSetBufPtr failed; status = %d\n", ret);
                  rtxErrPrint (pctxt);
                  return ret;
               }

               /* Decode RP-PDU */
               ret = NASDec_TS24011Msg_RP_PDU (pctxt, &ts24011RPDU);

               rpduDecoded = TRUE;
            }
         }
         break;

      default:
         /* RRC is not yet supported */
         printf ("ERROR: message type %d not supported\n", msgType);
         return RTERR_NOTSUPP;
      }

      /* Check for extraneous data */
      if (0 == ret && pctxt->buffer.byteIndex < pctxt->buffer.size) {
         ret = RTERR_EXTRDATA;
      }

      if (0 != ret) {
         OSBOOL retry = FALSE;
         if (msgType == nasLTE) {
            if (ts24301PDU.msgType == ASN1V_ts24301Msg_mt_DetachRequest) {
               retry = TRUE;
            }
         }
         if (retry) {
            /* Switch directions and try decode again */
            if (rtxCtxtTestFlag (pctxt, OS3GMOBORIG)) {
               rtxCtxtClearFlag (pctxt, OS3GMOBORIG);
            }
            else {
               rtxCtxtSetFlag (pctxt, OS3GMOBORIG);
            }
            /* Reset byte index */
            pctxt->buffer.byteIndex = 0;
         }
         else break;
      }
      else break;
   }

   if (bitTrace) {
      printf ("Decoded bit fields:\n");
      rtxDiagBitTracePrint (pctxt->pBitFldList, "");
      printf ("\n");
   }

   if (0 != ret) {
      printf ("decode PDU failed; status = %d\n", ret);
      rtxErrPrint (pctxt);
      return ret;
   }

   /* Encode message */

   ret = rtxCtxtSetBufPtr (pctxt, msgbuf2, sizeof(msgbuf2));
   if (0 != ret) {
      printf ("rtxCtxtSetBufPtr for encode failed; status = %d\n", ret);
      rtxErrPrint (pctxt);
      printf ("\n\n");
      return ret;
   }

   /* Enable bit tracing */

   if (bitTrace) {
      rtxDiagCtxtBitFieldListInit (pctxt);
   }

   /* Call encode function */

   switch (msgType) {
   case nas3G:
      ret = NASEnc_TS24008Msg_PDU (pctxt, &ts24008PDU);
      break;

   case nasLTE:
      ret = NASEnc_TS24301Msg_PDU (pctxt, &ts24301PDU);
      break;

   default:
      /* Other messages types (SMS, RRC) are not yet supported */
      printf ("ERROR: message type %d not supported\n", msgType);
      return RTERR_NOTSUPP;
   }

   if (bitTrace) {
      printf ("Encoded bit fields:\n");
      rtxDiagBitTracePrint (pctxt->pBitFldList, "");
      printf ("\n");
   }

   if (0 != ret) {
      printf ("Encode NAS message failed\n");
      rtxErrPrint (pctxt);
      return ret;
   }

   /* Compare encoded with original.  If not equal, output info and 
      output hex dump of messages. */

   msglen2 = rtxCtxtGetMsgLen (pctxt);

   ret = (msglen1 == msglen2) ?
      memcmp (msgbuf1, msgbuf2, msglen1) : -1;

   if (0 != ret) {
      printf ("Encoded message at index %d does not match original\n", idx);
      printf ("Original:\n");
      rtxHexDump (msgbuf1, msglen1);
      printf ("Encoded:\n");
      rtxHexDump (msgbuf2, msglen2);

      if (msglen1 != msglen2) {
         printf ("message lengths are not equal\n");
      }
      else {
         size_t j = 0;
         for ( ; j < msglen1; j++) {
            if (msgbuf1[j] != msgbuf2[j]) {
               printf ("byte at index %lu mismatch: %x != %x\n", 
                       (unsigned long)j, msgbuf1[j], msgbuf2[j]);
            }
         }
      }
   }

   return ret;
}
