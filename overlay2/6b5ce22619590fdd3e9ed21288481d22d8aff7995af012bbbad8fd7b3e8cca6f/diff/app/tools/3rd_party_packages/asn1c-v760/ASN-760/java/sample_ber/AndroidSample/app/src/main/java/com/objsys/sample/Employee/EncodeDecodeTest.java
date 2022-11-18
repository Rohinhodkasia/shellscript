package com.objsys.sample.Employee;


import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import com.objsys.asn1j.runtime.*;
import com.objsys.sample.android.AbstractEncodeDecodeTest;
import com.objsys.sample.android.EncodingRules;
import gen.Employee.*;

public class EncodeDecodeTest extends AbstractEncodeDecodeTest
{
   private static final EncodingRules suppRules[] = { EncodingRules.BER };
   
   private PersonnelRecord personnelRecord;
   
	@Override
	public void populate() {
	    personnelRecord = new PersonnelRecord();
	    
	    personnelRecord.name = new Name ("John", "P", "Smith");
	    personnelRecord.title = new Asn1IA5String ("Director");
	    personnelRecord.number = new EmployeeNumber (51);
	    personnelRecord.dateOfHire = new Date ("19710917");
	    personnelRecord.nameOfSpouse = new Name ("Mary", "T", "Smith");
	    personnelRecord.children = new _SeqOfChildInformation (2);
	    personnelRecord.children.elements[0] =
	        new ChildInformation (new Name ("Ralph", "T", "Smith"), "19571111");
	    personnelRecord.children.elements[1] =
	        new ChildInformation (new Name ("Susan", "B", "Jones"), "19590717");
	}

   @Override
   public void encode(EncodingRules rule, OutputStream out) {

      if ( personnelRecord == null )
         throw new IllegalStateException("populate not invoked");
                  
      try {
         switch( rule ) {
         case BER: {            
            Asn1BerOutputStream berOut = new Asn1BerOutputStream(out);
            personnelRecord.encode(berOut, true);
            berOut.close();
            break;
         }
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
      
      try {
         PersonnelRecord pdu = new PersonnelRecord();

         switch( rule) {
         case BER: {         
            Asn1BerDecodeBuffer buffer = 
               new Asn1BerDecodeBuffer(in);
            pdu.decode(buffer);
            break;
         }
         default:
            throw new UnsupportedOperationException("Encoding rule " +
                  rule.toString() + " not supported for this test.");
         }         
         
         pdu.print(getPduPrintStream(), "personnelRecord", 0);
      }
      catch (IOException e) { throw new RuntimeException(e); }
      catch (Asn1Exception e) { throw new RuntimeException(e); }      
   }
   
   public void free() {
      this.personnelRecord = null;
      super.free();
   }
   
   @Override
   public EncodingRules[] getSupportedEncodingRules() { return suppRules; }

}
