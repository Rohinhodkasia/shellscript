/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 6.4.B, Date: 10-Feb-2011.
 */
#include "IEEE-11073-20601-ASN1.h"
#include "rtxsrc/rtxCommon.h"

#include "rtxsrc/rtxPrint.h"
#include "rtxsrc/rtxStreamMemory.h"

int main (int argc, char** argv)
{
   ApduType   apdu;
   AarqApdu   aarq;
   DataProto* pDataProto;
   PhdAssociationInformation phdAssocInfo;

   OSCTXT     ctxt, ctxt2;
   OSOCTET*   msgptr;
   int        i, len, stat;
   OSBOOL     trace = TRUE;
   OSBOOL     verbose = FALSE;
   const char* filename = "message.dat";

   /* Process command line arguments */
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [-v] [-o <filename>]  [-notrace]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 1;
         }
      }
   }

   /* Initialize context structure */
   stat = rtInitContext (&ctxt);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }
   rtxSetDiag (&ctxt, verbose);

   /* Populate and encode PhdAssociationInformation */
   /* Note: it works better to memset this record to zero rather than 
      calling the init function due to the static bit array fields */
   OSCRTLMEMSET (&phdAssocInfo, 0, sizeof(phdAssocInfo));

   phdAssocInfo.protocol_version.numbits = 32;
   phdAssocInfo.protocol_version.data[0] = 0x40;

   phdAssocInfo.encoding_rules.numbits = 16;
   rtxSetBit (phdAssocInfo.encoding_rules.data, 16, EncodingRules_mder);

   phdAssocInfo.nomenclature_version.numbits = 32;
   rtxSetBit (phdAssocInfo.nomenclature_version.data, 32, 
              NomenclatureVersion_nom_version1);

   phdAssocInfo.functional_units.numbits = 32;

   phdAssocInfo.system_type.numbits = 32;
   rtxSetBit (phdAssocInfo.system_type.data, 32, SystemType_sys_type_agent);
   {
   static const OSOCTET sysId[] = {
      0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38
   } ;
   phdAssocInfo.system_id.numocts = (OSUINT32) sizeof(sysId);
   phdAssocInfo.system_id.data = (OSOCTET*) sysId;
   }
   phdAssocInfo.dev_config_id = extended_config_start;

   phdAssocInfo.data_req_mode_capab.data_req_mode_flags.numbits = 16;
   phdAssocInfo.data_req_mode_capab.data_req_init_agent_count = 1;
   phdAssocInfo.data_req_mode_capab.data_req_init_manager_count = 0;

   /* Create memory output stream */
   stat = rtxStreamMemoryCreateWriter (&ctxt, 0, 0);
   if (stat < 0) {
      printf ("Create memory output stream failed\n");
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return stat;
   }

   /* Encode */
   stat = MDEREnc_PhdAssociationInformation (&ctxt, &phdAssocInfo);

   msgptr = rtxStreamMemoryGetBuffer (&ctxt, &len);

   if (trace) {
      printf ("Hex dump of encoded record:\n");
      rtxHexDump (msgptr, len);
   }
   if (stat < 0) {
      printf ("Encoding failed\n");
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return stat;
   }

   /* Initialize 2nd context structure */
   stat = rtInitContext (&ctxt2);
   if (stat != 0) {
      rtxErrPrint (&ctxt2);
      return stat;
   }
   rtxSetDiag (&ctxt2, verbose);

   /* Populate apdu with test data */
   OSCRTLMEMSET (&aarq, 0, sizeof(AarqApdu));
   aarq.assoc_version.numbits = 32;
   rtxSetBit (aarq.assoc_version.data, 32, AssociationVersion_assoc_version1);

   pDataProto = rtxMemAllocType (&ctxt2, DataProto);
   pDataProto->data_proto_id = data_proto_id_20601;
   pDataProto->data_proto_info.numocts = len;
   pDataProto->data_proto_info.data = msgptr;

   rtxDListAppend (&ctxt2, &aarq.data_proto_list, pDataProto);

   apdu.t = T_ApduType_aarq;
   apdu.u.aarq = &aarq;

   if (trace) {
      printf ("The following record will be encoded:\n");
      asn1Print_ApduType ("apdu", &apdu);
      printf ("\n");
   }

   /* Create memory output stream */
   stat = rtxStreamMemoryCreateWriter (&ctxt2, 0, 0);
   if (stat < 0) {
      printf ("Create memory output stream failed\n");
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return stat;
   }

   /* Encode */
   stat = MDEREnc_ApduType (&ctxt2, &apdu);

   msgptr = rtxStreamMemoryGetBuffer (&ctxt2, &len);

   if (trace) {
      printf ("Hex dump of encoded record:\n");
      rtxHexDump (msgptr, len);
   }
   if (stat < 0) {
      printf ("Encoding failed\n");
      rtxErrPrint (&ctxt2);
   }
   else {
      /* Write the encoded message out to the output file */
      stat = rtxFileWriteBinary (filename, msgptr, len);
      if (stat < 0) {
         printf ("Write to file failed\n");
         rtxErrPrint (&ctxt);
      }
   }

   rtFreeContext (&ctxt);
   rtFreeContext (&ctxt2);

   return 0;
}
