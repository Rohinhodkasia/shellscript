EXTERN int NASDec_TS44018IE_VGCS_Ciphering_Parameters (OSCTXT* pctxt
   , TS44018IE_VGCS_Ciphering_Parameters* pvalue)
{
   OSBOOL rand_ind, lac_ind, cell_ind;

   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "VGCS_Ciphering_Parameters");

   OSCRTLMEMSET (&pvalue->m, 0, sizeof(pvalue->m));

   /* decode spare */

   RTXCTXTPUSHELEMNAME (pctxt, "spare");

   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxSkipBits (pctxt, 2);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);

   /* decode rand-ind */

   RTXCTXTPUSHELEMNAME (pctxt, "rand-ind");

   RTDIAG_NEWBITFIELD (pctxt, "BOOLEAN");

   ret = rtxDecBit (pctxt, &rand_ind);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);

   /* decode lac-ind */

   RTXCTXTPUSHELEMNAME (pctxt, "lac-ind");

   RTDIAG_NEWBITFIELD (pctxt, "BOOLEAN");

   ret = rtxDecBit (pctxt, &lac_ind);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);

   /* decode cell-ind */

   RTXCTXTPUSHELEMNAME (pctxt, "cell-ind");

   RTDIAG_NEWBITFIELD (pctxt, "BOOLEAN");

   ret = rtxDecBit (pctxt, &cell_ind);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);

   /* decode b22-count */

   RTXCTXTPUSHELEMNAME (pctxt, "b22-count");

   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxDecBitsToByte (pctxt, &pvalue->b22_count, 1);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);

   /* decode cell-global-count */

   RTXCTXTPUSHELEMNAME (pctxt, "cell-global-count");

   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxDecBitsToByte (pctxt, &pvalue->cell_global_count, 2);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);

   /* decode cell-identity */

   RTXCTXTPUSHELEMNAME (pctxt, "cell-identity");
   {
      OSBOOL cell_identity_present = cell_ind;

      if (cell_identity_present) {
         RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

         ret = rtxDecBitsToByte (pctxt, &pvalue->cell_identity, 8);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTDIAG_SETBITFLDCOUNT (pctxt);
         pvalue->m.cell_identityPresent = 1;
      }
   }
   RTXCTXTPOPELEMNAME (pctxt);

   /* decode location-area-identification */

   RTXCTXTPUSHELEMNAME (pctxt, "location-area-identification");
   {
      OSBOOL location_area_identification_present = lac_ind;

      if (location_area_identification_present) {
         RTDIAG_NEWBITFIELD (pctxt, "OCTET STRING");

         ret = rtxDecBitsToByteArray (pctxt, pvalue->location_area_identification, 5, 40);

         RTDIAG_SETBITFLDCOUNT (pctxt);
         pvalue->m.location_area_identificationPresent = 1;
      }
   }
   RTXCTXTPOPELEMNAME (pctxt);

   /* decode vstk_rand */

   {
      OSBOOL vstk_rand_present = rand_ind;

      if (vstk_rand_present) {
         RTXCTXTPUSHELEMNAME (pctxt, "vstk_rand");

         {
            OSSIZE bufsize = sizeof(pvalue->vstk_rand);
            RTDIAG_NEWBITFIELD (pctxt, "BIT STRING");

            ret = rtxDecBitsToByteArray (pctxt, pvalue->vstk_rand, bufsize, 36);

            RTDIAG_SETBITFLDCOUNT (pctxt);
         }
         pvalue->m.vstk_randPresent = 1;

         RTXCTXTPOPELEMNAME (pctxt);

         /* decode spare2 */

         RTXCTXTPUSHELEMNAME (pctxt, "spare2");

         RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

         ret = rtxSkipBits (pctxt, 4);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTDIAG_SETBITFLDCOUNT (pctxt);

         RTXCTXTPOPELEMNAME (pctxt);
      }
   }
   


   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}