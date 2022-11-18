package com.objsys.sample.android;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;

/**
 * This class provides an base class for encode-decode tests.
 * 
 * Special notes for implementors of subclasses:
 *    The populate method for EncodeDecodeTest should be implemented to populate
 *    an internal PDU object.
 *    
 *    The encode method should be implemented to encode the internal PDU object.
 *    
 *    The decode method should be implemented to decode to a temporary PDU
 *    object, which it should print to the stream returned by getPduPrintStream.
 *    {@link #getPrintedDecodedPdu()} is implemented to return whatever was
 *    written to this stream.
 *    
 *    The free method should be implemented to reset the internal PDU to null,
 *    and should invoke this class's free method.
 *
 */
public abstract class AbstractEncodeDecodeTest implements EncodeDecodeTest {
 
   
   /**
    * The stream to which the pdu is printed.
    * This is returned by getPduPrintStream
    */
   private ByteArrayOutputStream printPduStream = null;


   @Override
   public String getPrintedDecodedPdu() {
      if ( printPduStream == null )
         throw new IllegalStateException("nothing printed yet");
      
      return printPduStream.toString();
   }

   /**
    * Overrides of this method should invoke this method also so that
    * resources owned by this base class can be freed.
    * 
    * This version of the method assigns all object references to null.
    */
   @Override
   public void free() {
      printPduStream = null;
   }

   
   /**
    * Return the stream to which decoded pdu's should be printed.
    * @return
    */
   protected PrintStream getPduPrintStream() {
      
      this.printPduStream = new ByteArrayOutputStream();
      return new PrintStream(this.printPduStream);
   }
}
