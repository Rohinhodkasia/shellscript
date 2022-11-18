EXTERN int NASEnc_TS24008IE_AccessPointName (OSCTXT* pctxt
   , TS24008IE_AccessPointName value)
{
   int ret = 0;
   OSUINT8 i, j, len = (OSUINT8) OSCRTLSTRLEN(value) + 1;
   const char* sp;

   if (len > 100) {
      rtxErrAddStrParm (pctxt, "AccessPointName.length");
      rtxErrAddIntParm (pctxt, len);
      return LOG_RTERR (pctxt, RTERR_CONSVIO);
   }
   RTXCTXTPUSHTYPENAME (pctxt, "AccessPointName");

   /* Encode length */
   RTDIAG_NEWBITFIELD (pctxt, "length");

   ret = rtxWriteBytes (pctxt, &len, 1);
   if (0 != ret) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   /* Encode segments */
   for (i = 0; value[i] != '\0';) {
      /* scan for . or end of string */
      sp = &value[i];
      for (j = 0; value[i] != '.' && value[i] != '\0'; j++) i++;
      if (value[i] == '.') i++;

      /* encode segment length */
      RTDIAG_NEWBITFIELD (pctxt, "segment length");

      ret = rtxWriteBytes (pctxt, &j, 1);
      if (0 != ret) return LOG_RTERR (pctxt, ret);

      RTDIAG_SETBITFLDCOUNT (pctxt);
      RTDIAG_NEWBITFIELD (pctxt, "IA5String");

      ret = rtxWriteBytes (pctxt, (OSOCTET*)sp, j);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTDIAG_SETBITFLDCOUNT (pctxt);
   }

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}
