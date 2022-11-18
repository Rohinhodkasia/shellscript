package com.objsys.sample.NBAP;


import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import com.objsys.asn1j.runtime.*;
import gen.nbap.NBAP_CommonDataTypes.Criticality;
import gen.nbap.NBAP_CommonDataTypes.MessageDiscriminator;
import gen.nbap.NBAP_CommonDataTypes.ProcedureCode;
import gen.nbap.NBAP_CommonDataTypes.ProcedureID;
import gen.nbap.NBAP_CommonDataTypes.ProcedureID_ddMode;
import gen.nbap.NBAP_CommonDataTypes.TransactionID;
import gen.nbap.NBAP_Constants._NBAP_ConstantsValues;
import gen.nbap.NBAP_PDU_Contents.RadioLinkSetupResponseFDD;
import gen.nbap.NBAP_PDU_Contents.RadioLinkSetupResponseFDD_protocolIEs;
import gen.nbap.NBAP_PDU_Descriptions.NBAP_PDU;
import gen.nbap.NBAP_PDU_Descriptions.SuccessfulOutcome;
import com.objsys.sample.android.AbstractEncodeDecodeTest;
import com.objsys.sample.android.EncodingRules;

public class EncodeDecodeTest extends AbstractEncodeDecodeTest
{
   private static final EncodingRules suppRules[] = 
      { EncodingRules.ALIGNED_PER,
        EncodingRules.UNALIGNED_PER };
   
   private NBAP_PDU pdu;
   
	@Override
	public void populate() {

      pdu = new NBAP_PDU();

      SuccessfulOutcome obj1;
      obj1 = new SuccessfulOutcome();
      obj1.procedureID = new ProcedureID( new ProcedureCode(_NBAP_ConstantsValues.id_radioLinkSetup), ProcedureID_ddMode.fdd() );
      obj1.criticality = Criticality.reject();
      obj1.messageDiscriminator = MessageDiscriminator.common();
      obj1.transactionID = new TransactionID();
      obj1.transactionID.set_shortTransActionId( new Asn1Integer(81) );

      RadioLinkSetupResponseFDD data;
      obj1.value = data = new RadioLinkSetupResponseFDD();
      
      data.protocolIEs = new RadioLinkSetupResponseFDD_protocolIEs(0);

      pdu.set_succesfulOutcome(obj1);	   
	}

   @Override
   public void encode(EncodingRules rule, OutputStream out) {

      if ( pdu == null )
         throw new IllegalStateException("populate not invoked");
                  
      boolean aligned = false;
      try {
         switch( rule ) {
         case ALIGNED_PER:
            aligned = true;
            //fall through
         case UNALIGNED_PER:
            Asn1PerEncodeBuffer buffer = new Asn1PerEncodeBuffer(aligned);
            pdu.encode(buffer);
            buffer.write(out);
            break;

         default:
            throw new UnsupportedOperationException("Encoding rule " +
                  rule.toString() + " not supported for this test.");
         }
      }
      catch (IOException e) { throw new RuntimeException(e); }
      catch (Asn1Exception e) { throw new RuntimeException(e); }      
   }

   @Override
   public void decode(EncodingRules rule, InputStream in) {
      
      boolean aligned = false;
      
      try {
         NBAP_PDU localPdu = new NBAP_PDU();

         switch( rule) {
         case ALIGNED_PER:
            aligned = true;
            //fall through
         case UNALIGNED_PER: {         
            Asn1PerDecodeBuffer buffer = 
               new Asn1PerDecodeBuffer(in, aligned);
            localPdu.decode(buffer);
            break;
         }
         default:
            throw new UnsupportedOperationException("Encoding rule " +
                  rule.toString() + " not supported for this test.");
         }         
         
         localPdu.print(getPduPrintStream(), "NBAP_PDU", 0);
      }
      catch (IOException e) { throw new RuntimeException(e); }
      catch (Asn1Exception e) { throw new RuntimeException(e); }      
   }
   
   public void free() {
      this.pdu = null;
      super.free();
   }
   
   @Override
   public EncodingRules[] getSupportedEncodingRules() { return suppRules; }
}
