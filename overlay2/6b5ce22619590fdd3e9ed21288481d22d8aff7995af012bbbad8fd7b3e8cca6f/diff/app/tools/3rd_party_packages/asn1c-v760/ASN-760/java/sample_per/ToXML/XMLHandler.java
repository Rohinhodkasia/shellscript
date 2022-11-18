// This is an implementation of a simple print handler class.  It outputs 
// the fields of an encoded BER message to stdout in a structured output 
// format..

package sample_per.ToXML;

import com.objsys.asn1j.runtime.*;
import java.io.*;

class XMLHandler implements Asn1NamedEventHandler {
   private static final int START = 1;
   private static final int CHARS = 2;
   private static final int END = 3;

   protected String mVarName;
   protected int mIndentSpaces = 0;
   protected int mLastItem;

   public XMLHandler (String varName) {
      mVarName = varName;
      System.out.print ("<" + mVarName + ">");
      mLastItem = START;
   }

   public void startElement (String name, int index) {
      if (mLastItem == START) {
         System.out.println ("");
         mIndentSpaces += 3;
      }
      indent();
      System.out.print ("<" + name + ">");
      mLastItem = START;
   }

   public void endElement (String name, int index) {
      if (mLastItem == END) {
         mIndentSpaces -= 3;
         indent ();
      }
      System.out.println ("</" + name + ">");
      mLastItem = END;
   }

   public void characters (String svalue, short typeCode) {
      System.out.print (svalue);
      mLastItem = CHARS;
   }

   public void finished () {
      System.out.println ("</" + mVarName + ">");
   }

   private void indent () {
      for (int i = 0; i < mIndentSpaces; i++) 
         System.out.print (" ");
   }

}
