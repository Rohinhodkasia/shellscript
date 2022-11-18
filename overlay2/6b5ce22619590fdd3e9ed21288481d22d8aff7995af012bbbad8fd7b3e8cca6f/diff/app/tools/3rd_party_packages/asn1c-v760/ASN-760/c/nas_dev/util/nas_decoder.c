/* NAS decoder program.  This program accepts as input an L3 message    */
/* from a hex string and then decodes it and outputs a bit trace and    */
/* decoded results in brace text form.                                  */

#include <stdio.h>
#include "TS24008Msgs.h"
#include "TS24011Msgs.h"
#include "TS24301Msgs.h"
#include "TS24501Msgs.h"
#include "TS44018Msgs.h"
#include "TS44018Misc.h"
#include "rtxsrc/rtxBitDecode.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxPrint.h"
#include "rtxsrc/rtxPrintStream.h"
#include "rt3gppsrc/rt3gppNasSec.h"

static int usage() {
   static const char* usageText = 
   "usage: nas_decoder -hex <string> [-msgtype <type>] [-bittrace] ...\n"
   "   -hex      Hexadecimal string containing encoded message.\n"
   "   -msgtype  Type of message to be decoded. Valid values are \n"
   "             nas3g, naslte, nas5g, rrc, rrc_L2_pseudo, rrc_short_pd, \n"
   "             rrc_synch_chan, rrc_compact_synch_chan. \n"
   "             Default is nas3g.\n"
   "   -bittrace Print bit trace of decoded bit patterns.\n"
   "   -encode   Re-encode message after decode and check if match.\n"
   "   -count    Security uplink or downlink count.\n"
   "   -dir 0|1  Direction: 0 = uplink, 1 = downlink.\n"
   "   -ekey <string>  Encryption key hex string.\n"
   "   -ikey <string>  Integrity key hex string.\n"
   "   -dcch     Message is from DCCH channel.  Applies to RR Mgmt.\n"
   "   -sacch    Message is from SACCH channel.  Applies to RR Mgmt.\n"
   "   -acs      When decoding 44.018 SI Type 7 or 8 messages, this flag\n"
   "             indicates that ACS was set in SI Type 4 message.\n"
   "             By default, we assume ACS was not set.\n"
   "   -version  Version of the specification desired \n"
   "             Default is the latest version when decoder was built.\n";

   printf ("%s\n", usageText);

   return 0;
}


/*
Methods for printing ARFCN lists in various messages.
*/
static int printAssignmentCommandArfcn(OSCTXT* pctxt, 
   TS44018Msg_AssignmentCommand* pvalue);

static int printDtmAssignmentCommandArfcn(OSCTXT* pctxt, 
   TS44018Msg_DtmAssignmentCommand* pvalue);

static int printExtendedMeasurementOrderArfcn(OSCTXT* pctxt, 
   TS44018Msg_ExtendedMeasurementOrder* pvalue);

static int printHandoverCommandArfcn(OSCTXT* pctxt, 
   TS44018Msg_HandoverCommand* pvalue);

static int printPacketAssignmentArfcn(OSCTXT* pctxt, 
   TS44018Msg_PacketAssignment* pvalue);

static int printSIType2Arfcn(OSCTXT* pctxt, 
   TS44018Msg_SystemInformationType2* pvalue);

static int printSIType2bisArfcn(OSCTXT* pctxt, 
   TS44018Msg_SystemInformationType2bis* pvalue);

static int printSIType2terArfcn(OSCTXT* pctxt, 
   TS44018Msg_SystemInformationType2ter* pvalue);

static int printSIType5Arfcn(OSCTXT* pctxt, 
   TS44018Msg_SystemInformationType5* pvalue);

static int printSIType5bisArfcn(OSCTXT* pctxt, 
   TS44018Msg_SystemInformationType5bis* pvalue);

static int printSIType5terArfcn(OSCTXT* pctxt, 
   TS44018Msg_SystemInformationType5ter* pvalue);

static int printSI10bisArfcn(OSCTXT* pctxt,
   TS44018Msg_SYSTEM_INFORMATION_TYPE_10bis* pvalue);

static int printVGCS_Neighbour_Cell_InformationArfcn(OSCTXT* pctxt,
   TS44018Msg_VGCS_Neighbour_Cell_Information* pvalue);


/* Helper for SI 3, 7, 8 */
static int printSIType3Detail(OSCTXT* pctxt, 
   TS44018Msg_L2_PSEUDO_LEN_PDU* pvalue);

static int printSIType7Detail(OSCTXT* pctxt, 
   TS44018Msg_L2_PSEUDO_LEN_PDU* pvalue, OSBOOL acs);

static int printSIType8Detail(OSCTXT* pctxt, 
   TS44018Msg_L2_PSEUDO_LEN_PDU* pvalue, OSBOOL acs);

static int setEncBufPtr (OSCTXT* pctxt, OSOCTET* msgbuf, size_t bufsize)
{
   int ret = rtxCtxtSetBufPtr (pctxt, msgbuf, bufsize);
   if (0 != ret) {
      printf ("rtxCtxtSetBufPtr for encode failed; status = %d\n", ret);
      rtxErrPrint (pctxt);
      printf ("\n\n");
   }
   return ret;
}

int main (int argc, char** argv)
{
   TS24008Msg_PDU ts24008PDU;
   TS24301Msg_PDU ts24301PDU;
   TS24501Msg_PDU ts24501PDU;
   TS24011Msg_CP_PDU ts24011PDU;
   TS24011Msg_RP_PDU ts24011RPDU;
   TS44018Msg_DL_DCCH_PDU ts44018DlDcch;
   TS44018Msg_UL_DCCH_PDU ts44018UlDcch;
   TS44018Msg_UL_SACCH_PDU ts44018UlSacch;
   TS44018Msg_L2_PSEUDO_LEN_PDU ts44018L2Plen;
   TS44018Msg_RR_Short_PD_PDU ts44018ShortPd;
   TS44018Msg_SynchChannelInfo ts44018SynchChannelInfo;
   TS44018Msg_CompactSynchChannelInfo ts44018CompactSynchChannelInfo;

   OSCTXT	ctxt;
   OSOCTET*     msgbuf;
   OSOCTET*     tmpbuf;
   const char*  hexmsg = 0;
   const char*  ekey = 0;
   const char*  ikey = 0;
   OSUINT32     count, ver = 0;
   int          i, ret;
   OSSIZE       len;
   OSBOOL       bitTrace = FALSE;
   OSBOOL       rpduDecoded = FALSE;
   OSBOOL       encode = FALSE;
   OSUINT8      dir = 0; /* 0 = uplink, 1 = downlink */
   static const OSUINT8 UPLINK = 0;
   static const OSUINT8 DOWNLINK = 1;

   /* ACS is set from the command line.  It applies when decoding 44.018
      System Information Type 7 or 8 messages.  It is based on a flag
      that is sent in the System Information Type 4 message.
   */
   OSBOOL       acs = FALSE;
   
   enum { SACCH, DCCH } channel = DCCH;

   enum { notSet, nas3G, nasLTE, nas5G, sms, rrc, rrc_l2_pseudo, rrc_short_pd,
         rrc_synch_chan, rrc_compact_synch_chan } msgType = notSet;

   DECLARE_MEMLEAK_DETECTOR;

   printf ("\n");
   printf ("NAS Decoder Utility\n");
   printf ("Built with code generated using ASN1C v%s\n", ASN1C_VERSION);
   printf ("\n");

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-bittrace") ||
             !strcmp (argv[i], "-v")) {
            bitTrace = TRUE;
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
               else if (0 == rtxStricmp (msgTypeText, "nas5g")) {
                  msgType = nas5G;
               }
               else if (0 == rtxStricmp (msgTypeText, "sms")) {
                  msgType = sms;
               }
               else if (0 == rtxStricmp (msgTypeText, "rrc")) {
                  msgType = rrc;
               }
               else if (0 == rtxStricmp (msgTypeText, "rrc_l2_pseudo")) {
                  msgType = rrc_l2_pseudo;
               }
               else if (0 == rtxStricmp (msgTypeText, "rrc_short_pd")) {
                  msgType = rrc_short_pd;
               }
               else if (0 == rtxStricmp (msgTypeText, "rrc_synch_chan")) {
                  msgType = rrc_synch_chan;
               }
               else if (0 == rtxStricmp (msgTypeText, "rrc_compact_synch_chan"))
               {
                  msgType = rrc_compact_synch_chan;
               }
               else {
                  printf ("invalid message type argument - "
                          "must be nas3G, nas5G, nasLTE, or RRC\n");
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
         else if (!strcmp (argv[i], "-ekey")) {
            if (i < argc) {
               ekey = argv[++i];
            }
            else {
               printf ("encrypt key hex text argument missing\n");
               return -1;
            }
         }
         else if (!strcmp (argv[i], "-ikey")) {
            if (i < argc) {
               ikey = argv[++i];
            }
            else {
               printf ("integrity key hex text argument missing\n");
               return -1;
            }
         }
         else if (!strcmp (argv[i], "-dir")) {
            if (i < argc) {
               const char* dirstr = argv[++i];
               if (*dirstr == '0' || *dirstr == 'u') { dir = 0; }
               else if (*dirstr == '1' || *dirstr == 'd') { dir = 1; }
               else {
                  printf ("invalid direction, must be 0 or 1\n");
                  return -1;
               }
            }
            else {
               printf ("direction argument missing\n");
               return -1;
            }
         }
         else if (!strcmp (argv[i], "-count")) {
            if (i < argc) {
               if (0 != rtxCharStrToUInt (argv[++i], &count)) {
                  printf ("invalid count, must be a valid number\n");
                  return -1;
               }
            }
            else {
               printf ("count argument missing\n");
               return -1;
            }
         }
         else if (!strcmp (argv[i], "-encode")) {
            encode = TRUE;
         }
         else if (!strcmp (argv[i], "-dcch")) { channel = DCCH; }
         else if (!strcmp (argv[i], "-sacch")) { channel = SACCH; }
         else if (!strcmp (argv[i], "-acs")) { acs = TRUE; }
         else if (!strcmp (argv[i], "-version"))
         {
            if (i < argc)
            {
               if (0 != rtxCharStrToUInt(argv[++i], &ver))
               {
                  printf("invalid version, must be a valid number\n");
                  return -1;
               }
            }
         }
         else {
            return usage();
         }
      }
   }

   if (0 == hexmsg) {
      printf ("ERROR: -hex <string> is a required argument\n\n");
      return usage();
   }

   /* Initialize context structure */

   ret = rtInitContext (&ctxt);
   if (0 != ret) {
      printf ("rtInitContext failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
      return ret;
   }
   ctxt.version = ver;

   if (dir == DOWNLINK)
   {
      // Network originated...
      rtxCtxtClearFlag(&ctxt, OS3GMOBORIG);
   }
   else
   {
      // Mobile originated...
      rtxCtxtSetFlag(&ctxt, OS3GMOBORIG);
   }

   /* If security arguments are present, initialize security context */

   if (0 != ekey || 0 != ikey) {
      OSCrypt128Key integKey, encryptKey;
      if (0 != ekey) {
         ret = rtxHexCharsToBin 
            (ekey, strlen(ekey), encryptKey, sizeof(encryptKey));

         if (ret < 0) {
            printf ("converion of ekey to binary failed, status = %d\n", ret);
            return ret;
         }
      }

      if (0 != ikey) {
         ret = rtxHexCharsToBin 
            (ikey, strlen(ikey), integKey, sizeof(integKey));

         if (ret < 0) {
            printf ("converion of ikey to binary failed, status = %d\n", ret);
            return ret;
         }
      }

      ret = rtx3gppSecInitialize (&ctxt);
      if (0 != ret) {
         rtxErrPrint (&ctxt);
         return ret;
      }
 
      ret = rtx3gppAssignAlgorithmKeys (&ctxt, &integKey, 
         &encryptKey, OS3GPPSecAlgorithm_AES, OS3GPPSecAlgorithm_AES);

      if (ret == RTERR_NOTSUPP) {
         printf ("Warning: unable to set AES algorithm; "
                 "falling back to NULL algorithm.\n");
         rtxErrReset (&ctxt);
         ret = rtx3gppAssignAlgorithmKeys (&ctxt, NULL, NULL, 
            OS3GPPSecAlgorithm_NULL_ALG, OS3GPPSecAlgorithm_NULL_ALG);
      }

      if (0 != ret) {
         rtxErrPrint (&ctxt);
         return ret;
      }

      ctxt.p3gppSec->count = count;
      ctxt.p3gppSec->bearerId = 0;
      ctxt.p3gppSec->direction = dir;
   }

   ret = rtxHexCharsToBinCount (hexmsg, 0);
   if (ret >= 0) {
      msgbuf = (OSOCTET*) rtxMemAlloc (&ctxt, ret);
      if (0 == msgbuf) {
         printf ("ERROR: No memory available for message buffer "
                 "(%d bytes)\n", ret);
         return RTERR_NOMEM;
      }
      ret = rtxHexCharsToBin (hexmsg, 0, msgbuf, ret);
      if (ret < 0) {
         printf ("ERROR: Conversion of hex chars to binary failed, "
                 "status = %d\n", ret);
         return ret;
      }
      else len = (OSSIZE) ret;
   }
   else {
      printf ("ERROR: rtxHexCharsToBinCount failed, status = %d\n", ret);
      return ret;
   }

   /* Make a copy of the message buffer for later comparisons in case
      original message was encrypted */

   tmpbuf = (OSOCTET*) rtxMemAlloc (&ctxt, len);
   if (0 == tmpbuf) {
      printf ("ERROR: No memory available for temp work buffer "
              "(" OSSIZEFMT " bytes)\n", len);
      return RTERR_NOMEM;
   }
   OSCRTLMEMCPY (tmpbuf, msgbuf, len);

   /* Set message buffer pointer */

   ret = rtxCtxtSetBufPtr (&ctxt, tmpbuf, len);
   if (0 != ret) {
      printf ("rtxCtxtSetBufPtr failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
      return ret;
   }

   /* If message type not set, attempt to determine by decoding L3 header */

   if (msgType == notSet) {
      OSRTBufSave savedBuf;
      OSOCTET ub, pd;
   
      OSRTBUFSAVE2 (&ctxt, &savedBuf);
   
      /* decode security header type */
      ret = rtxDecBitsToByte (&ctxt, &ub, 4);
      if (ret < 0) {
         rtxErrPrint (&ctxt);
         return ret;
      }
  
      /* decode protocol discriminator */
      ret = rtxDecBitsToByte (&ctxt, &pd, 4);
      if (ret < 0) {
         rtxErrPrint (&ctxt);
         return ret;
      }
   
      OSRTBUFRESTORE2 (&ctxt, &savedBuf);

      switch (pd) {
      case TS24007L3_ProtoDiscr_epsMobMgmt:
      case TS24007L3_ProtoDiscr_epsSessMgmt:
         /* if message is ciphered, make sure security context initialized */
         if ((ub == TS24007L3_SecHdrType_integProtAndCipher ||
              ub == TS24007L3_SecHdrType_integProtAndCipherAndSecCtxt) &&
             0 == ctxt.p3gppSec) {
            printf ("ERROR: security parameters must be set to decode "
                    "ciphered message\n");
            rtxFreeContext (&ctxt);
            return RTERR_FAILED;
         }

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
   
      case TS24007L3_ProtoDiscr_rrMgmt:
         msgType = rrc;
         break;

      default:
         printf ("ERROR: protocol discriminator %s not supported\n", 
                 TS24007L3_ProtoDiscr_ToString (pd));
         rtxFreeContext (&ctxt);
         return RTERR_NOTSUPP;
      }
   }

   /* Enable bit tracing */
   if (bitTrace) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Call decode function */
   switch (msgType) {
      case nas3G:
         ret = NASDec_TS24008Msg_PDU (&ctxt, &ts24008PDU);
         break;

      case nasLTE:
         ret = NASDec_TS24301Msg_PDU (&ctxt, &ts24301PDU);
         break;

      case nas5G:
         ret = NASDec_TS24501Msg_PDU (&ctxt, &ts24501PDU);
         break;

      case sms:
         /* Decode CP message */
         ret = NASDec_TS24011Msg_CP_PDU (&ctxt, &ts24011PDU);
         if (0 == ret) {
            if (ts24011PDU.data.t == 
                T_TS24011Msgs_TS24011_OBJECTSET_obj_CP_DATA) {

               if (bitTrace) {
                  printf ("***\n");
                  printf ("CPDATA bit fields:\n");
                  rtxDiagBitTracePrint (ctxt.pBitFldList, "");
                  printf ("***\n");
                  printf ("\n");

                  rtxDiagCtxtBitFieldListInit (&ctxt);
               }

               /* Set message buffer pointer to point at CP-DATA contents */
               ret = rtxCtxtSetBufPtr 
                  (&ctxt, ts24011PDU.data.u.obj_CP_DATA->cpUserData.data,
                   ts24011PDU.data.u.obj_CP_DATA->cpUserData.numocts);

               if (0 != ret) {
                  printf ("rtxCtxtSetBufPtr failed; status = %d\n", ret);
                  rtxErrPrint (&ctxt);
                  return ret;
               }

               /* Decode RP-PDU */
               ret = NASDec_TS24011Msg_RP_PDU (&ctxt, &ts24011RPDU);

               rpduDecoded = TRUE;
            }
         }
         break;

      case rrc:
         /* Decode RR message (standard L3 format) */
         if ( dir == DOWNLINK && channel == DCCH )
            ret = NASDec_TS44018Msg_DL_DCCH_PDU( &ctxt, &ts44018DlDcch);
         else if ( dir == UPLINK && channel == DCCH )
            ret = NASDec_TS44018Msg_UL_DCCH_PDU( &ctxt, &ts44018UlDcch);
         else if ( dir == UPLINK && channel == SACCH )
            ret = NASDec_TS44018Msg_UL_SACCH_PDU( &ctxt, &ts44018UlSacch);
         else {
            printf("ERROR: no messages known for channel %s on %s\n", 
               channel == DCCH ? "DCCH" : "SACCH",
               dir == DOWNLINK ? "DL" : "UL" );
            return RTERR_NOTSUPP;
         }
         break;

      case rrc_l2_pseudo:
         ret = NASDec_TS44018Msg_L2_PSEUDO_LEN_PDU(&ctxt, &ts44018L2Plen);
         break;

      case rrc_short_pd:
         ret = NASDec_TS44018Msg_RR_Short_PD_PDU(&ctxt, &ts44018ShortPd);
         break;

      case rrc_synch_chan:
         ret = NASDec_TS44018Msg_SynchChannelInfo(&ctxt, 
                                                   &ts44018SynchChannelInfo);
         /* msg is 25 bits, skip 7 bits */
         rtxSkipBits(&ctxt, 7);
         break;

      case rrc_compact_synch_chan:
         ret = NASDec_TS44018Msg_CompactSynchChannelInfo(&ctxt, 
                                              &ts44018CompactSynchChannelInfo);
         /* msg is 25 bits, skip 7 bits */
         rtxSkipBits(&ctxt, 7);
         break;


      default:
         /* not yet supported */
         printf ("ERROR: message type %d not supported\n", msgType);
         return RTERR_NOTSUPP;
   }

   /* Check for extraneous data */
   if (0 == ret && ctxt.buffer.byteIndex < ctxt.buffer.size) {
      ret = LOG_RTERR (&ctxt, RTERR_EXTRDATA);
   }

   if (bitTrace) {
      printf ("***\n");
      printf ("Bit fields:\n");
      rtxDiagBitTracePrint (ctxt.pBitFldList, "");
      printf ("***\n");
      printf ("\n");
   }

   if (0 != ret) {
      if (ret == RTERR_NOSECPARAMS) {
         printf ("No security parameters provided.\n");
         printf ("Message integrity could not be verified.\n");
         printf ("\n");
         rtxErrReset (&ctxt);
         ret = 0;
      }
      else {
         printf ("decode PDU failed; status = %d\n", ret);
         rtxErrPrint (&ctxt);
         rtxFreeContext (&ctxt);
         return ret;
      }
   }

   /* Print fields */

   /* Register print-to-stream callback function */
   rtxSetPrintStream (&ctxt, &rtxPrintStreamToStdoutCB, 0);

   /* Invoke generated print-to-stream function */
   switch (msgType) {
   case nas3G:
      asn1PrtToStrm_TS24008Msg_PDU (&ctxt, "PDU", &ts24008PDU);
      break;

   case nasLTE:
      asn1PrtToStrm_TS24301Msg_PDU (&ctxt, "PDU", &ts24301PDU);
      break;

   case nas5G:
      asn1PrtToStrm_TS24501Msg_PDU (&ctxt, "PDU", &ts24501PDU);
      break;

   case sms:
      asn1PrtToStrm_TS24011Msg_CP_PDU (&ctxt, "CPDU", &ts24011PDU);
      if (rpduDecoded) {
         asn1PrtToStrm_TS24011Msg_RP_PDU (&ctxt, "RPDU", &ts24011RPDU);
      }
      break;

   case rrc:
      ret = 0;
      if ( dir == DOWNLINK && channel == DCCH ) {
         asn1PrtToStrm_TS44018Msg_DL_DCCH_PDU(&ctxt, "PDU", &ts44018DlDcch);

         if ( ts44018DlDcch.data.t == 
                  T_TS44018Msgs_DL_DCCH_Messages_obj_AssignmentCommand ) 
         {
            ret = printAssignmentCommandArfcn(&ctxt, 
                     ts44018DlDcch.data.u.obj_AssignmentCommand);
         }
         else if ( ts44018DlDcch.data.t ==
                     T_TS44018Msgs_DL_DCCH_Messages_obj_DtmAssignmentCommand )
         {
            ret = printDtmAssignmentCommandArfcn(&ctxt,
                     ts44018DlDcch.data.u.obj_DtmAssignmentCommand);
         }
         else if ( ts44018DlDcch.data.t ==
                     T_TS44018Msgs_DL_DCCH_Messages_obj_HandoverCommand )
         {
            ret = printHandoverCommandArfcn(&ctxt,
                     ts44018DlDcch.data.u.obj_HandoverCommand);
         }         
         else if ( ts44018DlDcch.data.t ==
                     T_TS44018Msgs_DL_DCCH_Messages_obj_PacketAssignment )
         {
            ret = printPacketAssignmentArfcn(&ctxt,
                     ts44018DlDcch.data.u.obj_PacketAssignment);
         }         
      }
      else if ( dir == UPLINK && channel == DCCH )
         asn1PrtToStrm_TS44018Msg_UL_DCCH_PDU(&ctxt, "PDU", &ts44018UlDcch);
      else if ( dir == UPLINK && channel == SACCH )
         asn1PrtToStrm_TS44018Msg_UL_SACCH_PDU(&ctxt, "PDU", &ts44018UlSacch);

      if ( ret < 0 ) {
         /* ret < 0 will only occur if printing extra info failed */
         rtxErrPrint(&ctxt);
         rtxErrReset(&ctxt);
      }

      
      break;

   case rrc_l2_pseudo:
      ret = 0;
      asn1PrtToStrm_TS44018Msg_L2_PSEUDO_LEN_PDU(&ctxt, "PDU", &ts44018L2Plen);

      if ( ts44018L2Plen.data.t ==
               T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_ExtendedMeasurementOrder )
      {
         ret = printExtendedMeasurementOrderArfcn(&ctxt,
                  ts44018L2Plen.data.u.obj_ExtendedMeasurementOrder );
      }
      else if ( ts44018L2Plen.data.t ==
               T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType2 )
      {
         ret = printSIType2Arfcn(&ctxt,
                  ts44018L2Plen.data.u.obj_SystemInformationType2 );
      }
      else if ( ts44018L2Plen.data.t ==
               T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType2bis )
      {
         ret = printSIType2bisArfcn(&ctxt,
                  ts44018L2Plen.data.u.obj_SystemInformationType2bis );
      }
      else if ( ts44018L2Plen.data.t ==
               T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType2ter )
      {
         ret = printSIType2terArfcn(&ctxt,
                  ts44018L2Plen.data.u.obj_SystemInformationType2ter );
      }
      else if ( ts44018L2Plen.data.t ==
               T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType3 )
      {
         ret = printSIType3Detail(&ctxt, &ts44018L2Plen);
      }
      else if ( ts44018L2Plen.data.t ==
               T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType5 )
      {
         ret = printSIType5Arfcn(&ctxt,
                  ts44018L2Plen.data.u.obj_SystemInformationType5 );
      }
      else if ( ts44018L2Plen.data.t ==
               T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType5bis )
      {
         ret = printSIType5bisArfcn(&ctxt,
                  ts44018L2Plen.data.u.obj_SystemInformationType5bis );
      }
      else if ( ts44018L2Plen.data.t ==
               T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType5ter )
      {
         ret = printSIType5terArfcn(&ctxt,
                  ts44018L2Plen.data.u.obj_SystemInformationType5ter );
      }
      else if ( ts44018L2Plen.data.t ==
               T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType7 )
      {
         ret = printSIType7Detail(&ctxt, &ts44018L2Plen, acs);
      }
      else if ( ts44018L2Plen.data.t ==
               T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType8 )
      {
         ret = printSIType8Detail(&ctxt, &ts44018L2Plen, acs);
      }


      if ( ret < 0 ) {
         /* ret < 0 will only occur if printing extra info failed */
         rtxErrPrint(&ctxt);
         rtxErrReset(&ctxt);
      }

      break;

   case rrc_short_pd:
      ret = 0;
      asn1PrtToStrm_TS44018Msg_RR_Short_PD_PDU(&ctxt, "PDU", &ts44018ShortPd);

      if ( ts44018ShortPd.data.t ==
               T_TS44018Msgs_RR_Short_PD_Messages_obj_system_information_type_10bis )
      {
         ret = printSI10bisArfcn(&ctxt,
                  ts44018ShortPd.data.u.obj_system_information_type_10bis );
      }
      else if ( ts44018ShortPd.data.t ==
               T_TS44018Msgs_RR_Short_PD_Messages_obj_vgcs_neighbour_cell_information )
      {
         ret = printVGCS_Neighbour_Cell_InformationArfcn(&ctxt,
                  ts44018ShortPd.data.u.obj_vgcs_neighbour_cell_information );
      }

      if ( ret < 0 ) {
         /* ret < 0 will only occur if printing extra info failed */
         rtxErrPrint(&ctxt);
         rtxErrReset(&ctxt);
      }

      break;

   case rrc_synch_chan:
      asn1PrtToStrm_TS44018Msg_SynchChannelInfo(&ctxt, "SynchChannelInfo",
                                                &ts44018SynchChannelInfo);
      break;

   case rrc_compact_synch_chan:
      asn1PrtToStrm_TS44018Msg_CompactSynchChannelInfo(&ctxt, 
                   "CompactSynchChannelInfo", &ts44018CompactSynchChannelInfo);
      break;

   default:;
   }

   if (encode) {
      OSOCTET msgbuf2[256];
      OSSIZE  msglen1 = len, msglen2;

      printf ("\n");
      printf ("***\n");

      /* Encode message */

      ret = setEncBufPtr (&ctxt, msgbuf2, sizeof(msgbuf2));
      if (0 != ret) return ret;

      /* Enable bit tracing */

      if (bitTrace) {
         rtxDiagCtxtBitFieldListInit (&ctxt);
      }

      /* Call encode function */

      switch (msgType) {
      case nas3G:
         ret = NASEnc_TS24008Msg_PDU (&ctxt, &ts24008PDU);
         break;

      case nasLTE:
         ret = NASEnc_TS24301Msg_PDU (&ctxt, &ts24301PDU);
         break;

      case nas5G:
         ret = NASEnc_TS24501Msg_PDU (&ctxt, &ts24501PDU);
         break;

      case sms:
         if (rpduDecoded) {
            memset (ts24011PDU.data.u.obj_CP_DATA->cpUserData.data, 0, 
                    sizeof(ts24011PDU.data.u.obj_CP_DATA->cpUserData.data));
            
            ret = setEncBufPtr 
               (&ctxt, ts24011PDU.data.u.obj_CP_DATA->cpUserData.data, 
                sizeof(ts24011PDU.data.u.obj_CP_DATA->cpUserData.data));
            if (0 != ret) return ret;

            ret = NASEnc_TS24011Msg_RP_PDU (&ctxt, &ts24011RPDU);
            if (0 == ret) {
               ts24011PDU.data.u.obj_CP_DATA->cpUserData.numocts =
                  rtxCtxtGetMsgLen (&ctxt);
               ret = setEncBufPtr (&ctxt, msgbuf2, sizeof(msgbuf2));
               if (0 != ret) return ret;
            }
         }
         ret = NASEnc_TS24011Msg_CP_PDU (&ctxt, &ts24011PDU);
         break;

      case rrc:
         if ( dir == DOWNLINK && channel == DCCH )
            ret = NASEnc_TS44018Msg_DL_DCCH_PDU( &ctxt, &ts44018DlDcch);
         else if ( dir == UPLINK && channel == DCCH )
            ret = NASEnc_TS44018Msg_UL_DCCH_PDU( &ctxt, &ts44018UlDcch);
         else if ( dir == UPLINK && channel == SACCH )
            ret = NASEnc_TS44018Msg_UL_SACCH_PDU( &ctxt, &ts44018UlSacch);

         break;

      case rrc_l2_pseudo:
         ret = NASEnc_TS44018Msg_L2_PSEUDO_LEN_PDU(&ctxt, &ts44018L2Plen);
         break;

      case rrc_short_pd:
         ret = NASEnc_TS44018Msg_RR_Short_PD_PDU(&ctxt, &ts44018ShortPd);
         break;

      case rrc_synch_chan:
         ret = NASEnc_TS44018Msg_SynchChannelInfo(&ctxt, 
                                                   &ts44018SynchChannelInfo);
         break;

      case rrc_compact_synch_chan:
         ret = NASEnc_TS44018Msg_CompactSynchChannelInfo(&ctxt, 
                                              &ts44018CompactSynchChannelInfo);
         break;


      default:
         /* Other messages types (SMS, RRC) are not yet supported */
         printf ("ERROR: message type %d not supported\n", msgType);
         return RTERR_NOTSUPP;
      }

      if (bitTrace) {
         printf ("Encoded bit fields:\n");
         rtxDiagBitTracePrint (ctxt.pBitFldList, "");
         printf ("\n");
      }

      if (0 != ret && ret != RTERR_NOSECPARAMS) {
         printf ("Encode NAS message failed\n");
         rtxErrPrint (&ctxt);
         return ret;
      }

      /* Compare encoded with original.  If not equal, output info and 
         output hex dump of messages. */

      msglen2 = rtxCtxtGetMsgLen (&ctxt);

      ret = (msglen1 == msglen2) ?
         memcmp (msgbuf, msgbuf2, msglen1) : -1;

      if (0 != ret) {
         printf ("Encoded message does not match original\n");
         printf ("Original:\n");
         rtxHexDump (msgbuf, msglen1);
         printf ("Encoded:\n");
         rtxHexDump (msgbuf2, msglen2);

         if (msglen1 != msglen2) {
            printf ("message lengths are not equal\n");
         }
         else {
            size_t j = 0;
            for ( ; j < msglen1; j++) {
               if (msgbuf[j] != msgbuf2[j]) {
                  printf ("byte at index %lu mismatch: %x != %x\n", 
                          (unsigned long)j, msgbuf[j], msgbuf2[j]);
               }
            }
         }
      }

      printf ("***\n");
   }

   rtxFreeContext (&ctxt);

   return ret;
}



static int printAssignmentCommandArfcn(OSCTXT* pctxt, 
   TS44018Msg_AssignmentCommand* pvalue)
{
   int ret = 0;
   OSUINT16* arfcns;
   OSUINT16 arfcnCount;
   
   
   printf("\nAdditional details:\n");
   ret = TS44018IE_Frequency_List_decodeARFCN( 
            pctxt, &pvalue->freqListAfterTime,
            &arfcns, &arfcnCount);

   if ( ret < 0 ) return LOG_RTERR(pctxt, ret);
   printf("\tfreqListAfterTime ARFCN list = ");
   TS44018IE_printArfcns(arfcns, arfcnCount);
   printf("\n");

      
   ret = TS44018IE_Cell_Channel_Description_decodeARFCN( 
            pctxt, &pvalue->cellChannelDesc, &arfcns, &arfcnCount);

   if ( ret < 0 ) return LOG_RTERR(pctxt, ret);
   printf("\tcellChannelDesc ARFCN list = ");
   TS44018IE_printArfcns(arfcns, arfcnCount);
   printf("\n");
      
   ret = TS44018IE_Frequency_List_decodeARFCN( 
            pctxt, &pvalue->frequencyListBeforeTime,
            &arfcns, &arfcnCount);

   if ( ret < 0 ) return LOG_RTERR(pctxt, ret);

   printf("\tfrequencyListBeforeTime ARFCN list = ");
   TS44018IE_printArfcns(arfcns, arfcnCount);
   printf("\n");
   
   return ret;
}


static int printDtmAssignmentCommandArfcn(OSCTXT* pctxt, 
   TS44018Msg_DtmAssignmentCommand* pvalue)
{
   int ret = 0;
   OSUINT16* arfcns;
   OSUINT16 arfcnCount;
   
   
   printf("\nAdditional details:\n");
   ret = TS44018IE_Cell_Channel_Description_decodeARFCN( 
            pctxt, &pvalue->cellChannelDescription,
            &arfcns, &arfcnCount);

   if ( ret < 0 ) return LOG_RTERR(pctxt, ret);
   printf("\tcellChannelDescription ARFCN list = ");
   TS44018IE_printArfcns(arfcns, arfcnCount);
   printf("\n");

   ret = TS44018IE_Frequency_List_decodeARFCN( 
            pctxt, &pvalue->frequencyList,
            &arfcns, &arfcnCount);

   if ( ret < 0 ) return LOG_RTERR(pctxt, ret);

   printf("\tfrequencyList ARFCN list = ");
   TS44018IE_printArfcns(arfcns, arfcnCount);
   printf("\n");      

   ret = TS44018IE_Frequency_List_decodeARFCN( 
            pctxt, &pvalue->frequencyListC2,
            &arfcns, &arfcnCount);

   if ( ret < 0 ) return LOG_RTERR(pctxt, ret);

   printf("\tfrequencyListC2 ARFCN list = ");
   TS44018IE_printArfcns(arfcns, arfcnCount);
   printf("\n");      
   
   return ret;
}

static int printExtendedMeasurementOrderArfcn(OSCTXT* pctxt, 
   TS44018Msg_ExtendedMeasurementOrder* pvalue)
{
   int ret = 0;
   OSUINT16* arfcns;
   OSUINT16 arfcnCount;
   
   
   printf("\nAdditional details:\n");
   ret = TS44018IE_Extended_Measurement_Frequency_List_decodeARFCN( 
            pctxt, &pvalue->extendedMeasurementFrequencyList,
            &arfcns, &arfcnCount);

   if ( ret < 0 ) return LOG_RTERR(pctxt, ret);
   printf("\textendedMeasurementFrequencyList ARFCN list = ");
   TS44018IE_printArfcns(arfcns, arfcnCount);
   printf("\n");
   
   return ret;
}


static int printHandoverCommandArfcn(OSCTXT* pctxt, 
   TS44018Msg_HandoverCommand* pvalue)
{
   int ret = 0;
   OSUINT16* arfcns;
   OSUINT16 arfcnCount;
   
   
   printf("\nAdditional details:\n");

   ret = TS44018IE_Frequency_Short_List_decodeARFCN( 
            pctxt, &pvalue->freqShortListAfterTime,
            &arfcns, &arfcnCount);

   if ( ret < 0 ) return LOG_RTERR(pctxt, ret);
   printf("\tfreqShortListAfterTime ARFCN list = ");
   TS44018IE_printArfcns(arfcns, arfcnCount);
   printf("\n");

   ret = TS44018IE_Frequency_List_decodeARFCN( 
            pctxt, &pvalue->freqListAfterTime,
            &arfcns, &arfcnCount);

   if ( ret < 0 ) return LOG_RTERR(pctxt, ret);
   printf("\tfreqListAfterTime ARFCN list = ");
   TS44018IE_printArfcns(arfcns, arfcnCount);
   printf("\n");

      
   ret = TS44018IE_Cell_Channel_Description_decodeARFCN( 
            pctxt, &pvalue->cellChannelDescr, &arfcns, &arfcnCount);

   if ( ret < 0 ) return LOG_RTERR(pctxt, ret);
   printf("\tcellChannelDescr ARFCN list = ");
   TS44018IE_printArfcns(arfcns, arfcnCount);
   printf("\n");
      
   ret = TS44018IE_Frequency_Short_List_decodeARFCN( 
            pctxt, &pvalue->freqShortListBeforeTime,
            &arfcns, &arfcnCount);

   if ( ret < 0 ) return LOG_RTERR(pctxt, ret);
   printf("\tfreqShortListBeforeTime ARFCN list = ");
   TS44018IE_printArfcns(arfcns, arfcnCount);
   printf("\n");

   ret = TS44018IE_Frequency_List_decodeARFCN( 
            pctxt, &pvalue->freqListBeforeTime,
            &arfcns, &arfcnCount);

   if ( ret < 0 ) return LOG_RTERR(pctxt, ret);

   printf("\tfreqListBeforeTime ARFCN list = ");
   TS44018IE_printArfcns(arfcns, arfcnCount);
   printf("\n");
   
   return ret;
}


static int printPacketAssignmentArfcn(OSCTXT* pctxt, 
   TS44018Msg_PacketAssignment* pvalue)
{
   int ret = 0;
   OSUINT16* arfcns;
   OSUINT16 arfcnCount;
   
   
   printf("\nAdditional details:\n");
   ret = TS44018IE_Frequency_List_decodeARFCN( 
            pctxt, &pvalue->freqListC2,
            &arfcns, &arfcnCount);

   if ( ret < 0 ) return LOG_RTERR(pctxt, ret);
   printf("\tfreqListC2 ARFCN list = ");
   TS44018IE_printArfcns(arfcns, arfcnCount);
   printf("\n");
   
   return ret;
}

static int printSIType2Arfcn(OSCTXT* pctxt, 
   TS44018Msg_SystemInformationType2* pvalue)
{
   int ret = 0;
   OSUINT16* arfcns;
   OSUINT16 arfcnCount;
   
   
   printf("\nAdditional details:\n");
   ret = TS44018IE_Neighbour_Cell_Description_decodeARFCN( 
            pctxt, &pvalue->bcchFrequencyList,
            &arfcns, &arfcnCount);

   if ( ret < 0 ) return LOG_RTERR(pctxt, ret);
   printf("\tbcchFrequencyList ARFCN list = ");
   TS44018IE_printArfcns(arfcns, arfcnCount);
   printf("\n");
   
   return ret;
}

static int printSIType2bisArfcn(OSCTXT* pctxt, 
   TS44018Msg_SystemInformationType2bis* pvalue)
{
   int ret = 0;
   OSUINT16* arfcns;
   OSUINT16 arfcnCount;
   
   
   printf("\nAdditional details:\n");
   ret = TS44018IE_Neighbour_Cell_Description_decodeARFCN( 
            pctxt, &pvalue->extendedBCCHFrequencyList,
            &arfcns, &arfcnCount);

   if ( ret < 0 ) return LOG_RTERR(pctxt, ret);
   printf("\textendedBCCHFrequencyList ARFCN list = ");
   TS44018IE_printArfcns(arfcns, arfcnCount);
   printf("\n");
   
   return ret;
}

static int printSIType2terArfcn(OSCTXT* pctxt, 
   TS44018Msg_SystemInformationType2ter* pvalue)
{
   int ret = 0;
   OSUINT16* arfcns;
   OSUINT16 arfcnCount;
   
   
   printf("\nAdditional details:\n");
   ret = TS44018IE_Neighbour_Cell_Description_2_decodeARFCN( 
            pctxt, &pvalue->extendedBCCHFrequencyList,
            &arfcns, &arfcnCount);

   if ( ret < 0 ) return LOG_RTERR(pctxt, ret);
   printf("\textendedBCCHFrequencyList ARFCN list = ");
   TS44018IE_printArfcns(arfcns, arfcnCount);
   printf("\n");
   
   return ret;
}

static int printSIType5Arfcn(OSCTXT* pctxt, 
   TS44018Msg_SystemInformationType5* pvalue)
{
   int ret = 0;
   OSUINT16* arfcns;
   OSUINT16 arfcnCount;
   
   
   printf("\nAdditional details:\n");
   ret = TS44018IE_Neighbour_Cell_Description_decodeARFCN( 
            pctxt, &pvalue->bcchFrequencyList,
            &arfcns, &arfcnCount);

   if ( ret < 0 ) return LOG_RTERR(pctxt, ret);
   printf("\tbcchFrequencyList ARFCN list = ");
   TS44018IE_printArfcns(arfcns, arfcnCount);
   printf("\n");
   
   return ret;
}


static int printSIType5bisArfcn(OSCTXT* pctxt, 
   TS44018Msg_SystemInformationType5bis* pvalue)
{
   int ret = 0;
   OSUINT16* arfcns;
   OSUINT16 arfcnCount;
   
   
   printf("\nAdditional details:\n");
   ret = TS44018IE_Neighbour_Cell_Description_decodeARFCN( 
            pctxt, &pvalue->extensionBCCHFrequencyListDescription,
            &arfcns, &arfcnCount);

   if ( ret < 0 ) return LOG_RTERR(pctxt, ret);
   printf("\textensionBCCHFrequencyListDescription ARFCN list = ");
   TS44018IE_printArfcns(arfcns, arfcnCount);
   printf("\n");
   
   return ret;
}

static int printSIType5terArfcn(OSCTXT* pctxt, 
   TS44018Msg_SystemInformationType5ter* pvalue)
{
   int ret = 0;
   OSUINT16* arfcns;
   OSUINT16 arfcnCount;
   
   
   printf("\nAdditional details:\n");
   ret = TS44018IE_Neighbour_Cell_Description_2_decodeARFCN( 
            pctxt, &pvalue->extendedBCCHFrequencyList,
            &arfcns, &arfcnCount);

   if ( ret < 0 ) return LOG_RTERR(pctxt, ret);
   printf("\textendedBCCHFrequencyList ARFCN list = ");
   TS44018IE_printArfcns(arfcns, arfcnCount);
   printf("\n");
   
   return ret;
}

static int printSI10bisNeighbourCellInfoArfcn(OSCTXT* pctxt, 
   TS44018IE_SI10bis_Neighbour_Cell_Info* pvalue,
   const char* prefixName)
{
   int ret = 0;
   OSUINT16* arfcns;
   OSUINT16 arfcnCount;
   
   if ( pvalue->m.component_2Present ) {
      if ( pvalue->component_2.t == T_SI10bis_Neighbour_Cell_Info_component_2_frequency_Short_List)
      {
         ret = TS44018IE_Frequency_Short_List_2_decodeARFCN( 
            pctxt, &pvalue->component_2.u.frequency_Short_List,
            &arfcns, &arfcnCount);

         if ( ret < 0 ) return LOG_RTERR(pctxt, ret);

         printf("\t%s.component_2.frequency_Short_List ARFCN list = ",
            prefixName);
         TS44018IE_printArfcns(arfcns, arfcnCount);
         printf("\n");         
      }
      else {
         ret = TS44018IE_Frequency_List_decodeARFCN( 
            pctxt, &pvalue->component_2.u.frequency_List,
            &arfcns, &arfcnCount);

         if ( ret < 0 ) return LOG_RTERR(pctxt, ret);

         printf("\t%s.component_2.frequency_List ARFCN list = ",
            prefixName);
         TS44018IE_printArfcns(arfcns, arfcnCount);
         printf("\n");         
      }
   }
   
   return ret;
}


static int printSI10bisRestOctetsArfcn(OSCTXT* pctxt, 
   TS44018IE_SI10bis_Rest_Octets* pvalue,
   const char* prefixName)
{
   char buffer[1024];

   OSUINT32 i = 0;
   for(i = 0; i < pvalue->component_2.n; i++) {
      int ret;

      os_snprintf(buffer, 1024, "%s.component_2[%u].si10bis_Neighbor_Cell_Info",
                  prefixName, i);
      ret = printSI10bisNeighbourCellInfoArfcn(pctxt, 
         &pvalue->component_2.elem[i].si10bis_Neighbour_Cell_Info,
         buffer );
      if ( ret < 0 ) return LOG_RTERR(pctxt, ret);
   }

   return 0;
}


static int printVGCS_Neighbour_Cell_InformationArfcn(OSCTXT* pctxt,
   TS44018Msg_VGCS_Neighbour_Cell_Information* pvalue)
{
   char buffer[1024];
   OSUINT32 i = 0;

   printf("\nAdditional details:\n");   

   for(i = 0; i < pvalue->si10bis_Neighbour_Cell_Info_list.n; i++) {
      int ret;

      os_snprintf(buffer, 1024, "si10bis_Neighbour_Cell_Info_list[%u]",
                  i);
      ret = printSI10bisNeighbourCellInfoArfcn(pctxt, 
         &pvalue->si10bis_Neighbour_Cell_Info_list.elem[i],
         buffer );
      if ( ret < 0 ) return LOG_RTERR(pctxt, ret);
   }  

   return 0;
}


static int printSI10bisArfcn(OSCTXT* pctxt,
   TS44018Msg_SYSTEM_INFORMATION_TYPE_10bis* pvalue)
{
   printf("\nAdditional details:\n");   

   return printSI10bisRestOctetsArfcn(pctxt, 
      pvalue, "rest_octets");
}


static int printSIType3Detail(OSCTXT* pctxt, 
   TS44018Msg_L2_PSEUDO_LEN_PDU* pvalue)
{
   int ret = 0;
   OSBOOL iuModeSupported;
   TS44018Msg_SystemInformationType3* pmsg = 
               pvalue->data.u.obj_SystemInformationType3;
   TS44018IE_SI3_Rest_Octets_Data* pdata = 
               pvalue->restOctets.u.obj_SystemInformationType3;
   TS44018IE_SI3_Rest_Octets restOctets;
   
   /* 
   Set the decode buffer to point to the raw rest octets data.
   Cast away the const-ness of data; decoding from it won't modify it anyway.
   */
   ret = rtxCtxtSetBufPtr(pctxt, (OSOCTET*)pdata->data.data, 
                           pdata->data.numocts);
   if ( ret < 0 ) return LOG_RTERR(pctxt, ret);

   /* set iuModeSupported.  I am not sure whether cbq3 == 1 
      ("Iu mode capable MSs barred") counts as Iu mode supported or not.
      We're just assuming here that it does.
   */
   iuModeSupported = pmsg->controlChannelDescription.cbq3 != 0;

   /* Decode and then print the rest octets. */

   ret = NASDec_TS44018IE_SI3_Rest_Octets(pctxt, &restOctets, iuModeSupported);

   if ( ret < 0 ) return LOG_RTERR(pctxt, ret);

   asn1PrtToStrm_TS44018IE_SI3_Rest_Octets(pctxt, "SI 3 Rest Octets", 
                                             &restOctets);
   
   return ret;
}


static int printSIType7Detail(OSCTXT* pctxt, 
   TS44018Msg_L2_PSEUDO_LEN_PDU* pvalue, OSBOOL acs)
{
   int ret = 0;
   TS44018IE_SI7_Rest_Octets restOctets;

   /* Set message buffer pointer to raw rest octets data.
      Cast away const-ness to avoid warning. */

   ret = rtxCtxtSetBufPtr (pctxt, 
         (OSOCTET*) pvalue->restOctets.u.obj_SystemInformationType7->data,
         pvalue->restOctets.u.obj_SystemInformationType7->numocts);

   if ( 0 < ret ) return LOG_RTERR(pctxt, ret);
 
   /* Decode rest octets and then print them. */

   ret = NASDec_TS44018IE_SI7_Rest_Octets (pctxt, &restOctets, acs );
   if ( 0 < ret ) return LOG_RTERR(pctxt, ret);

   asn1PrtToStrm_TS44018IE_SI7_Rest_Octets(pctxt, "SI7 Rest Octets", 
                                             &restOctets);

   return ret;
}


static int printSIType8Detail(OSCTXT* pctxt, 
   TS44018Msg_L2_PSEUDO_LEN_PDU* pvalue, OSBOOL acs)
{
   int ret = 0;
   TS44018IE_SI8_Rest_Octets restOctets;

   /* Set message buffer pointer to raw rest octets data.
      Cast away const-ness to avoid warning. */

   ret = rtxCtxtSetBufPtr (pctxt, 
         (OSOCTET*) pvalue->restOctets.u.obj_SystemInformationType8->data,
         pvalue->restOctets.u.obj_SystemInformationType8->numocts);

   if ( 0 < ret ) return LOG_RTERR(pctxt, ret);
 
   /* Decode rest octets and then print them. */

   ret = NASDec_TS44018IE_SI8_Rest_Octets (pctxt, &restOctets, acs );
   if ( 0 < ret ) return LOG_RTERR(pctxt, ret);

   asn1PrtToStrm_TS44018IE_SI8_Rest_Octets(pctxt, "SI8 Rest Octets", 
                                             &restOctets);

   return ret;
}
