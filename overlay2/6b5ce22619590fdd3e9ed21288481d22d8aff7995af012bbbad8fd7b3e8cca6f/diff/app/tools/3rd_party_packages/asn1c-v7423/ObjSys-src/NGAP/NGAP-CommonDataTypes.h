/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 7.4.2.3, Date: 10-Sep-2020.
 */
#ifndef NGAP_COMMONDATATYPES_H
#define NGAP_COMMONDATATYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include "rtkey.h"
#include "rtxsrc/rtxCommon.h"
#include "rtpersrc/asn1per.h"

/**
 * Header file for ASN.1 module NGAP-CommonDataTypes
 */
/**************************************************************/
/*                                                            */
/*  Criticality                                               */
/*                                                            */
/**************************************************************/
/*
Criticality ::= ENUMERATED { reject(0), ignore(1), notify(2) }
*/
typedef enum {
   reject = 0,
   ignore = 1,
   notify = 2
} Criticality_Root;

typedef OSUINT32 Criticality;

EXTERN int asn1PE_Criticality (OSCTXT* pctxt, Criticality value);

EXTERN int asn1PD_Criticality (OSCTXT* pctxt, Criticality* pvalue);

EXTERN void asn1Print_Criticality (const char* name, const Criticality* pvalue);

EXTERN int asn1PrtToStr_Criticality (const char* name, Criticality* pvalue, 
   char* buffer, OSSIZE bufSize);

EXTERN int asn1PrtToStrm_Criticality (OSCTXT *pctxt, 
   const char* name, const Criticality* pvalue);

EXTERN extern const OSEnumItem Criticality_ENUMTAB[];
#define Criticality_ENUMTABSIZE 3

EXTERN const OSUTF8CHAR* Criticality_ToString (OSINT32 value);

EXTERN int Criticality_ToEnum (OSCTXT* pctxt,
   const OSUTF8CHAR* value, Criticality* pvalue);

EXTERN int Criticality_ToEnum2 (OSCTXT* pctxt,
   const OSUTF8CHAR* value, OSSIZE valueLen, Criticality* pvalue);

/**************************************************************/
/*                                                            */
/*  Presence                                                  */
/*                                                            */
/**************************************************************/
/*
Presence ::= ENUMERATED { optional(0), conditional(1), mandatory(2) }
*/
typedef enum {
   optional = 0,
   conditional = 1,
   mandatory = 2
} Presence_Root;

typedef OSUINT32 Presence;

EXTERN int asn1PE_Presence (OSCTXT* pctxt, Presence value);

EXTERN int asn1PD_Presence (OSCTXT* pctxt, Presence* pvalue);

EXTERN void asn1Print_Presence (const char* name, const Presence* pvalue);

EXTERN int asn1PrtToStr_Presence (const char* name, Presence* pvalue, char* buffer, 
   OSSIZE bufSize);

EXTERN int asn1PrtToStrm_Presence (OSCTXT *pctxt, 
   const char* name, const Presence* pvalue);

EXTERN extern const OSEnumItem Presence_ENUMTAB[];
#define Presence_ENUMTABSIZE 3

EXTERN const OSUTF8CHAR* Presence_ToString (OSINT32 value);

EXTERN int Presence_ToEnum (OSCTXT* pctxt,
   const OSUTF8CHAR* value, Presence* pvalue);

EXTERN int Presence_ToEnum2 (OSCTXT* pctxt,
   const OSUTF8CHAR* value, OSSIZE valueLen, Presence* pvalue);

/**************************************************************/
/*                                                            */
/*  ProcedureCode                                             */
/*                                                            */
/**************************************************************/
/*
ProcedureCode ::= INTEGER (0..255)
*/
typedef OSUINT8 ProcedureCode;

EXTERN int asn1PE_ProcedureCode (OSCTXT* pctxt, ProcedureCode value);

EXTERN int asn1PD_ProcedureCode (OSCTXT* pctxt, ProcedureCode* pvalue);

EXTERN void asn1Print_ProcedureCode (const char* name, const ProcedureCode* pvalue);

EXTERN int asn1PrtToStr_ProcedureCode (const char* name, ProcedureCode* pvalue, 
   char* buffer, OSSIZE bufSize);

EXTERN int asn1PrtToStrm_ProcedureCode (OSCTXT *pctxt, 
   const char* name, const ProcedureCode* pvalue);

/**************************************************************/
/*                                                            */
/*  ProtocolExtensionID                                       */
/*                                                            */
/**************************************************************/
/*
ProtocolExtensionID ::= INTEGER (0..65535)
*/
typedef OSUINT16 ProtocolExtensionID;

EXTERN int asn1PE_ProtocolExtensionID (OSCTXT* pctxt, ProtocolExtensionID value);

EXTERN int asn1PD_ProtocolExtensionID (OSCTXT* pctxt, ProtocolExtensionID* pvalue);

EXTERN void asn1Print_ProtocolExtensionID 
   (const char* name, const ProtocolExtensionID* pvalue);

EXTERN int asn1PrtToStr_ProtocolExtensionID (const char* name, 
   ProtocolExtensionID* pvalue, char* buffer, OSSIZE bufSize);

EXTERN int asn1PrtToStrm_ProtocolExtensionID (OSCTXT *pctxt, 
   const char* name, const ProtocolExtensionID* pvalue);

/**************************************************************/
/*                                                            */
/*  ProtocolIE_ID                                             */
/*                                                            */
/**************************************************************/
/*
ProtocolIE-ID ::= INTEGER (0..65535)
*/
typedef OSUINT16 ProtocolIE_ID;

EXTERN int asn1PE_ProtocolIE_ID (OSCTXT* pctxt, ProtocolIE_ID value);

EXTERN int asn1PD_ProtocolIE_ID (OSCTXT* pctxt, ProtocolIE_ID* pvalue);

EXTERN void asn1Print_ProtocolIE_ID (const char* name, const ProtocolIE_ID* pvalue);

EXTERN int asn1PrtToStr_ProtocolIE_ID (const char* name, ProtocolIE_ID* pvalue, 
   char* buffer, OSSIZE bufSize);

EXTERN int asn1PrtToStrm_ProtocolIE_ID (OSCTXT *pctxt, 
   const char* name, const ProtocolIE_ID* pvalue);

/**************************************************************/
/*                                                            */
/*  TriggeringMessage                                         */
/*                                                            */
/**************************************************************/
/*
TriggeringMessage ::= ENUMERATED { initiating-message(0), successful-outcome(1), unsuccessfull-outcome(2) }
*/
typedef enum {
   initiating_message = 0,
   successful_outcome = 1,
   unsuccessfull_outcome = 2
} TriggeringMessage_Root;

typedef OSUINT32 TriggeringMessage;

EXTERN int asn1PE_TriggeringMessage (OSCTXT* pctxt, TriggeringMessage value);

EXTERN int asn1PD_TriggeringMessage (OSCTXT* pctxt, TriggeringMessage* pvalue);

EXTERN void asn1Print_TriggeringMessage 
   (const char* name, const TriggeringMessage* pvalue);

EXTERN int asn1PrtToStr_TriggeringMessage (const char* name, 
   TriggeringMessage* pvalue, char* buffer, OSSIZE bufSize);

EXTERN int asn1PrtToStrm_TriggeringMessage (OSCTXT *pctxt, 
   const char* name, const TriggeringMessage* pvalue);

EXTERN extern const OSEnumItem TriggeringMessage_ENUMTAB[];
#define TriggeringMessage_ENUMTABSIZE 3

EXTERN const OSUTF8CHAR* TriggeringMessage_ToString (OSINT32 value);

EXTERN int TriggeringMessage_ToEnum (OSCTXT* pctxt,
   const OSUTF8CHAR* value, TriggeringMessage* pvalue);

EXTERN int TriggeringMessage_ToEnum2 (OSCTXT* pctxt,
   const OSUTF8CHAR* value, OSSIZE valueLen, TriggeringMessage* pvalue);

/**************************************************************/
/*                                                            */
/*  PrivateIE_ID                                              */
/*                                                            */
/**************************************************************/
/*
PrivateIE-ID ::= CHOICE {
   local [0] INTEGER (0..65535),
   global [1] OBJECT IDENTIFIER
}
*/
/* Choice tag constants */

#define T_PrivateIE_ID_local            1
#define T_PrivateIE_ID_global           2

typedef struct EXTERN PrivateIE_ID {
   OSINT32 t;
   union {
      /* t = 1 */
      OSUINT16 local;
      /* t = 2 */
      ASN1OBJID *global;
   } u;
} PrivateIE_ID;

EXTERN int asn1PE_PrivateIE_ID (OSCTXT* pctxt, PrivateIE_ID* pvalue);

EXTERN int asn1PD_PrivateIE_ID (OSCTXT* pctxt, PrivateIE_ID* pvalue);

EXTERN void asn1Print_PrivateIE_ID (const char* name, const PrivateIE_ID* pvalue);

EXTERN int asn1PrtToStr_PrivateIE_ID (const char* name, PrivateIE_ID* pvalue, 
   char* buffer, OSSIZE bufSize);

EXTERN int asn1PrtToStrm_PrivateIE_ID (OSCTXT *pctxt, 
   const char* name, const PrivateIE_ID* pvalue);

EXTERN int asn1Init_PrivateIE_ID (PrivateIE_ID* pvalue);

EXTERN OSBOOL asn1Equals_PrivateIE_ID (const PrivateIE_ID* pvalue1, const PrivateIE_ID* pvalue2);

#ifdef __cplusplus
}
#endif

#endif
