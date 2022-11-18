   /* There is no presence bit for SI 4 Rest Octets_O.
      It is up to the user to populate it when appropriate.
      According to the specification, "SI4 Rest Octets_O" will be present
      if and only if ACS from System Information Type 4 is 1.
   */
   RTXCTXTPUSHELEMNAME (pctxt, "si4-Rest-Octets-O");

   if (pvalue->m.si4_Rest_Octets_OPresent) {

      ret = NASEnc_TS44018IE_SI4_Rest_Octets_O (pctxt, &pvalue->
         si4_Rest_Octets_O);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

   }
   RTXCTXTPOPELEMNAME (pctxt);
