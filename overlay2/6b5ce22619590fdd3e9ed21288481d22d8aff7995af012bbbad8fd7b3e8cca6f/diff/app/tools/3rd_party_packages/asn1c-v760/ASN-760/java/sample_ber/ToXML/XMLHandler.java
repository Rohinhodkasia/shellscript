// This is an implementation of a simple print handler class.  It outputs 
// the fields of an encoded BER message to stdout in a structured output 
// format..

package sample_ber.ToXML;

import com.objsys.asn1j.runtime.*;
import java.io.*;

class XMLHandler implements Asn1NamedEventHandler {
   protected String mVarName;
   protected int mIndentSpaces = 0;

   public XMLHandler (String varName) {
      mVarName = varName;
      System.out.println ("<" + mVarName + ">");
      mIndentSpaces += 3;
   }

   public void startElement (String name, int index) {
      indent();
      System.out.println ("<" + name + ">");
      mIndentSpaces += 3;
   }

   public void endElement (String name, int index) {
      mIndentSpaces -= 3;
      indent ();
      System.out.println ("</" + name + ">");
   }

   public void characters (String svalue, short typeCode) {
      indent ();
      String typeName = new String (Asn1Type.getTypeName(typeCode));
      typeName.replace (' ', '_');
      System.out.print ("<" + typeName + ">");
      System.out.print (svalue);
      System.out.println ("</" + typeName + ">");
   }

   public void finished () {
      System.out.println ("</" + mVarName + ">");
   }

   private void indent () {
      for (int i = 0; i < mIndentSpaces; i++) 
         System.out.print (" ");
   }

}
