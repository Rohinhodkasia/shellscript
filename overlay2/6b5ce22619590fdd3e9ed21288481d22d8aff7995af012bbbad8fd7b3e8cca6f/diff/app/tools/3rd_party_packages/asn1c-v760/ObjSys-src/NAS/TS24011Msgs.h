/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 7.6.0, Date: 15-Feb-2022.
 */
#ifndef TS24011MSGS_H
#define TS24011MSGS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include "rtkey.h"
#include "rtxsrc/rtxCommon.h"
#include "rtsrc/asn1type.h"

#include "TS24007L3.h"
#include "TS24011IES.h"

/**
 * Header file for ASN.1 module TS24011Msgs
 */
typedef enum {
   T_TS24011Msgs_TS24011_OBJECTSET_UNDEF_,
   T_TS24011Msgs_TS24011_OBJECTSET_obj_CP_DATA,
   T_TS24011Msgs_TS24011_OBJECTSET_obj_CP_ACK,
   T_TS24011Msgs_TS24011_OBJECTSET_obj_CP_ERROR
} TS24011_OBJECTSET_TVALUE;

/**************************************************************/
/*                                                            */
/*  CPDATA                                                    */
/*                                                            */
/**************************************************************/
/*
CPDATA ::= SEQUENCE {
   cpUserData [0] CPUserData
}
*/
typedef struct EXTERN TS24011Msg_CPDATA {
   TS24011IE_CPUserData cpUserData;
} TS24011Msg_CPDATA;

EXTERN int NASEnc_TS24011Msg_CPDATA (OSCTXT* pctxt, TS24011Msg_CPDATA* pvalue);

EXTERN int NASDec_TS24011Msg_CPDATA (OSCTXT* pctxt, TS24011Msg_CPDATA* pvalue);

EXTERN int asn1PrtToStrm_TS24011Msg_CPDATA (OSCTXT *pctxt, 
   const char* name, const TS24011Msg_CPDATA* pvalue);

EXTERN TS24011Msg_CPDATA* asn1Test_TS24011Msg_CPDATA (OSCTXT* pctxt);

EXTERN int asn1Init_TS24011Msg_CPDATA (TS24011Msg_CPDATA* pvalue);

/**************************************************************/
/*                                                            */
/*  CPERROR                                                   */
/*                                                            */
/**************************************************************/
/*
CPERROR ::= SEQUENCE {
   cpCause [0] CPCauseValue
}
*/
typedef struct EXTERN TS24011Msg_CPERROR {
   TS24011IE_CPCauseValue cpCause;
} TS24011Msg_CPERROR;

EXTERN int NASEnc_TS24011Msg_CPERROR (OSCTXT* pctxt, TS24011Msg_CPERROR* pvalue
   );

EXTERN int NASDec_TS24011Msg_CPERROR (OSCTXT* pctxt, TS24011Msg_CPERROR* pvalue
   );

EXTERN int asn1PrtToStrm_TS24011Msg_CPERROR (OSCTXT *pctxt, 
   const char* name, const TS24011Msg_CPERROR* pvalue);

EXTERN TS24011Msg_CPERROR* asn1Test_TS24011Msg_CPERROR (OSCTXT* pctxt);

EXTERN int asn1Init_TS24011Msg_CPERROR (TS24011Msg_CPERROR* pvalue);

/**************************************************************/
/*                                                            */
/*  CP_PDU                                                    */
/*                                                            */
/**************************************************************/
/*
CP-PDU ::= SEQUENCE {
   l3HdrOpts [0] EXPLICIT L3HdrOptions, -- L3 header, octet 1, bits 5 thru 8
   protoDiscr [1] NAS-PROTOCOL-CLASS.&protoDiscr ({TS24011-OBJECTSET}),
   msgType [2] NAS-PROTOCOL-CLASS.&msgType ({TS24011-OBJECTSET}) (0..255),
   data [3] EXPLICIT NAS-PROTOCOL-CLASS.&Value ({TS24011-OBJECTSET}{@protoDiscr,@msgType})
}
*/
typedef struct EXTERN TS24011Msg_CP_PDU {
   TS24007L3_L3HdrOptions l3HdrOpts;
   TS24007L3_ProtoDiscr protoDiscr;
   OSUINT8 msgType;
   struct  {
      /**
       * information object selector
       */
      TS24011_OBJECTSET_TVALUE t;

      /**
       * TS24011-OBJECTSET information objects
       */
      union {
         /**
          * protoDiscr: sms
          * msgType: mt-CP-DATA
          */
         TS24011Msg_CPDATA *obj_CP_DATA;
         /**
          * protoDiscr: sms
          * msgType: mt-CP-ACK
          */
         /**
          * protoDiscr: sms
          * msgType: mt-CP-ERROR
          */
         TS24011Msg_CPERROR *obj_CP_ERROR;
      } u;
   } data;
} TS24011Msg_CP_PDU;

EXTERN int NASEnc_TS24011Msg_CP_PDU (OSCTXT* pctxt, TS24011Msg_CP_PDU* pvalue);

EXTERN int NASDec_TS24011Msg_CP_PDU (OSCTXT* pctxt, TS24011Msg_CP_PDU* pvalue);

EXTERN int asn1PrtToStrm_TS24011Msg_CP_PDU (OSCTXT *pctxt, 
   const char* name, const TS24011Msg_CP_PDU* pvalue);

EXTERN void asn1SetTC_TS24011Msg_CP_PDU_obj_CP_DATA
   (OSCTXT* pctxt, TS24011Msg_CP_PDU* pElem, TS24011Msg_CPDATA *pvalue);

EXTERN void asn1SetTC_TS24011Msg_CP_PDU_obj_CP_ACK
   (OSCTXT* pctxt, TS24011Msg_CP_PDU* pElem);

EXTERN void asn1SetTC_TS24011Msg_CP_PDU_obj_CP_ERROR
   (OSCTXT* pctxt, TS24011Msg_CP_PDU* pElem, TS24011Msg_CPERROR *pvalue);

EXTERN TS24011Msg_CP_PDU* asn1Test_TS24011Msg_CP_PDU (OSCTXT* pctxt);

EXTERN int asn1Init_TS24011Msg_CP_PDU (TS24011Msg_CP_PDU* pvalue);

/**************************************************************/
/*                                                            */
/*  RPHeader                                                  */
/*                                                            */
/**************************************************************/
/*
 RP Message header 
RPHeader ::= SEQUENCE {
   spare [0] INTEGER (0..31) DEFAULT 0, -- should be set to 0
   rpMsgType [1] INTEGER (0..7),
   rpMsgRef [2] INTEGER (0..255)
}
*/
typedef struct EXTERN TS24011Msg_RPHeader {
   OSUINT8 spare;
   OSUINT8 rpMsgType;
   OSUINT8 rpMsgRef;
} TS24011Msg_RPHeader;

EXTERN int NASEnc_TS24011Msg_RPHeader (OSCTXT* pctxt
   , TS24011Msg_RPHeader* pvalue);

EXTERN int NASDec_TS24011Msg_RPHeader (OSCTXT* pctxt
   , TS24011Msg_RPHeader* pvalue);

EXTERN int asn1PrtToStrm_TS24011Msg_RPHeader (OSCTXT *pctxt, 
   const char* name, const TS24011Msg_RPHeader* pvalue);

EXTERN TS24011Msg_RPHeader* asn1Test_TS24011Msg_RPHeader (OSCTXT* pctxt);

EXTERN int asn1Init_TS24011Msg_RPHeader (TS24011Msg_RPHeader* pvalue);

/**************************************************************/
/*                                                            */
/*  RPDataMSOriginating                                       */
/*                                                            */
/**************************************************************/
/*
 7.3.1.2 RP-DATA (MS To Network) 
<is3GMessage/>
RPDataMSOriginating ::= SEQUENCE {
   origAddrLen [0] INTEGER (0..255) DEFAULT 0,
   destAddress [1] RPDestinationAddress,
   userData [2] RPUserData
}
*/
typedef struct EXTERN TS24011Msg_RPDataMSOriginating {
   OSUINT8 origAddrLen;
   TS24011IE_RPDestinationAddress destAddress;
   TS24011IE_RPUserData userData;
} TS24011Msg_RPDataMSOriginating;

EXTERN int NASEnc_TS24011Msg_RPDataMSOriginating (OSCTXT* pctxt
   , TS24011Msg_RPDataMSOriginating* pvalue);

EXTERN int NASDec_TS24011Msg_RPDataMSOriginating (OSCTXT* pctxt
   , TS24011Msg_RPDataMSOriginating* pvalue);

EXTERN int asn1PrtToStrm_TS24011Msg_RPDataMSOriginating (OSCTXT *pctxt, 
   const char* name, const TS24011Msg_RPDataMSOriginating* pvalue);

EXTERN TS24011Msg_RPDataMSOriginating*
    asn1Test_TS24011Msg_RPDataMSOriginating (OSCTXT* pctxt);

EXTERN int asn1Init_TS24011Msg_RPDataMSOriginating (
   TS24011Msg_RPDataMSOriginating* pvalue);

/**************************************************************/
/*                                                            */
/*  RPDataMSTerminated                                        */
/*                                                            */
/**************************************************************/
/*
 7.3.1.1 RP-DATA (Network to MS) 
<is3GMessage/>
RPDataMSTerminated ::= SEQUENCE {
   origAddress [0] RPOriginatorAddress,
   destAddrLen [1] INTEGER (0..255) DEFAULT 0,
   userData [2] RPUserData
}
*/
typedef struct EXTERN TS24011Msg_RPDataMSTerminated {
   TS24011IE_RPOriginatorAddress origAddress;
   OSUINT8 destAddrLen;
   TS24011IE_RPUserData userData;
} TS24011Msg_RPDataMSTerminated;

EXTERN int NASEnc_TS24011Msg_RPDataMSTerminated (OSCTXT* pctxt
   , TS24011Msg_RPDataMSTerminated* pvalue);

EXTERN int NASDec_TS24011Msg_RPDataMSTerminated (OSCTXT* pctxt
   , TS24011Msg_RPDataMSTerminated* pvalue);

EXTERN int asn1PrtToStrm_TS24011Msg_RPDataMSTerminated (OSCTXT *pctxt, 
   const char* name, const TS24011Msg_RPDataMSTerminated* pvalue);

EXTERN TS24011Msg_RPDataMSTerminated*
    asn1Test_TS24011Msg_RPDataMSTerminated (OSCTXT* pctxt);

EXTERN int asn1Init_TS24011Msg_RPDataMSTerminated (
   TS24011Msg_RPDataMSTerminated* pvalue);

/**************************************************************/
/*                                                            */
/*  RP_ACK                                                    */
/*                                                            */
/**************************************************************/
/*
 7.3.2 RP-SMMA 
 7.3.3 RP-ACK 
<is3GMessage/>
RP-ACK ::= SEQUENCE {
   --<iei format="tlv">41</iei>
   userData [0] RPUserData OPTIONAL
}
*/
typedef struct EXTERN TS24011Msg_RP_ACK {
   struct {
      unsigned userDataPresent : 1;
   } m;
   TS24011IE_RPUserData userData;
} TS24011Msg_RP_ACK;

EXTERN int NASEnc_TS24011Msg_RP_ACK (OSCTXT* pctxt, TS24011Msg_RP_ACK* pvalue);

EXTERN int NASDec_TS24011Msg_RP_ACK (OSCTXT* pctxt, TS24011Msg_RP_ACK* pvalue);

EXTERN int asn1PrtToStrm_TS24011Msg_RP_ACK (OSCTXT *pctxt, 
   const char* name, const TS24011Msg_RP_ACK* pvalue);

EXTERN TS24011Msg_RP_ACK* asn1Test_TS24011Msg_RP_ACK (OSCTXT* pctxt);

EXTERN int asn1Init_TS24011Msg_RP_ACK (TS24011Msg_RP_ACK* pvalue);

/**************************************************************/
/*                                                            */
/*  RP_ERROR                                                  */
/*                                                            */
/**************************************************************/
/*
 7.3.4 RP-ERROR 
<is3GMessage/>
RP-ERROR ::= SEQUENCE {
   rpCause [0] RPCauseElem,
   --<iei format="tlv">41</iei>
   userData [1] RPUserData OPTIONAL
}
*/
typedef struct EXTERN TS24011Msg_RP_ERROR {
   struct {
      unsigned userDataPresent : 1;
   } m;
   TS24011IE_RPCauseElem rpCause;
   TS24011IE_RPUserData userData;
} TS24011Msg_RP_ERROR;

EXTERN int NASEnc_TS24011Msg_RP_ERROR (OSCTXT* pctxt
   , TS24011Msg_RP_ERROR* pvalue);

EXTERN int NASDec_TS24011Msg_RP_ERROR (OSCTXT* pctxt
   , TS24011Msg_RP_ERROR* pvalue);

EXTERN int asn1PrtToStrm_TS24011Msg_RP_ERROR (OSCTXT *pctxt, 
   const char* name, const TS24011Msg_RP_ERROR* pvalue);

EXTERN TS24011Msg_RP_ERROR* asn1Test_TS24011Msg_RP_ERROR (OSCTXT* pctxt);

EXTERN int asn1Init_TS24011Msg_RP_ERROR (TS24011Msg_RP_ERROR* pvalue);

/**************************************************************/
/*                                                            */
/*  RP_PDU                                                    */
/*                                                            */
/**************************************************************/
/*
RP-PDU ::= SEQUENCE {
   header [0] RPHeader,
   --<inline/>
   infoElem [1] EXPLICIT CHOICE {
      --<selector element="header.rpMsgType" value="0"/>
      dataToNet [0] RPDataMSOriginating,
      --<selector element="header.rpMsgType" value="1"/>
      dataToMS [1] RPDataMSTerminated,
      --<selector element="header.rpMsgType" value="2"/>
      ackToNet [2] RP-ACK,
      --<selector element="header.rpMsgType" value="3"/>
      ackToMS [3] RP-ACK,
      --<selector element="header.rpMsgType" value="4"/>
      errorToNet [4] RP-ERROR,
      --<selector element="header.rpMsgType" value="5"/>
      errorToMS [5] RP-ERROR,
      --<selector element="header.rpMsgType" value="6"/>
      smma [6] NULL
   }
}
*/
typedef struct EXTERN TS24011Msg_RP_PDU {
   TS24011Msg_RPHeader header;
   struct  {
      union {
         /* selector element = header.rpMsgType, value = 0 */
         TS24011Msg_RPDataMSOriginating dataToNet;
         /* selector element = header.rpMsgType, value = 1 */
         TS24011Msg_RPDataMSTerminated dataToMS;
         /* selector element = header.rpMsgType, value = 2 */
         TS24011Msg_RP_ACK ackToNet;
         /* selector element = header.rpMsgType, value = 3 */
         TS24011Msg_RP_ACK ackToMS;
         /* selector element = header.rpMsgType, value = 4 */
         TS24011Msg_RP_ERROR errorToNet;
         /* selector element = header.rpMsgType, value = 5 */
         TS24011Msg_RP_ERROR errorToMS;
         /* selector element = header.rpMsgType, value = 6 */
      } u;
   } infoElem;
} TS24011Msg_RP_PDU;

EXTERN int NASEnc_TS24011Msg_RP_PDU (OSCTXT* pctxt, TS24011Msg_RP_PDU* pvalue);

EXTERN int NASDec_TS24011Msg_RP_PDU (OSCTXT* pctxt, TS24011Msg_RP_PDU* pvalue);

EXTERN int asn1PrtToStrm_TS24011Msg_RP_PDU (OSCTXT *pctxt, 
   const char* name, const TS24011Msg_RP_PDU* pvalue);

EXTERN TS24011Msg_RP_PDU* asn1Test_TS24011Msg_RP_PDU (OSCTXT* pctxt);

EXTERN int asn1Init_TS24011Msg_RP_PDU (TS24011Msg_RP_PDU* pvalue);

/* Value definitions */

#define ASN1V_mt_CP_DATA 1
#define ASN1V_mt_CP_ACK 4
#define ASN1V_mt_CP_ERROR 16

#ifdef __cplusplus
}
#endif

#endif