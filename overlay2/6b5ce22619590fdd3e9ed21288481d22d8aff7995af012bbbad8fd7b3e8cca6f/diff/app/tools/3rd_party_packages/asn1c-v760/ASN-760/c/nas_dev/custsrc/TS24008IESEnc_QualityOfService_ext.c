if (pvalue->m.extPresent) {
   ret = NASEnc_TS24008IE_QosExt (pctxt, &pvalue->ext);
   if (ret < 0) return LOG_RTERR (pctxt, ret);
}
