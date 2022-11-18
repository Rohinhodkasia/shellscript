// This is an implementation of a simple print handler class.  It outputs 
// the fields of an encoded BER message to stdout in a structured output 
// format..

package sample_ber.EventHandler;

import com.objsys.asn1j.runtime.*;
import java.io.*;

class PrintHandler implements Asn1NamedEventHandler {
   protected String mVarName;
   protected int mIndentSpaces = 0;

   public PrintHandler (String varName) {
      mVarName = varName;
      System.out.println (mVarName + " = {");
      mIndentSpaces += 3;
   }

   public void startElement (String name, int index) {
      indent();
      System.out.print (name);
      if (index >= 0) 
          System.out.print ("[" + index + "]");
      System.out.println (" = {");
      mIndentSpaces += 3;
   }

   public void endElement (String name, int index) {
      mIndentSpaces -= 3;
      indent ();
      System.out.println ("}");
   }

   public void characters (String svalue, short typeCode) {
      indent ();
      System.out.println (svalue);
   }

   private void indent () {
      for (int i = 0; i < mIndentSpaces; i++) 
         System.out.print (" ");
   }

}
