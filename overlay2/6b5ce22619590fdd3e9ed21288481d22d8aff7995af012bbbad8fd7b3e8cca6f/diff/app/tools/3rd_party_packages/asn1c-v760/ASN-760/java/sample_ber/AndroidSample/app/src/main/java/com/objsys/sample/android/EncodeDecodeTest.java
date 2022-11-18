package com.objsys.sample.android;

import java.io.InputStream;
import java.io.OutputStream;

/**
 * An interface for encode/decode tests.  
 * To encode a message, you may use:
 *    test.populate();
 *    test.encode(rules, outputStream);
 *
 * To decode a message, you may use:
 *    test.decode(rules, inputStream);
 *    test.getPrintedDecodedPdu();
 */
public interface EncodeDecodeTest {
	
	/**
	 * Create an populate a PDU for encoding.
	 */
	void populate();

	/**
	 * Encode PDU using given coding rules.
	 * @param rule The encoding rules to encode with
	 * @param out The OutputStream to encode to
	 * @throws UnsupportedOperationException if not implemented
	 */
	void encode(EncodingRules rule, OutputStream out);
	
	/**
	 * Decode previously encoded message to new PDU using given coding rules.
	 * @param in The input stream. 
	 */
	void decode(EncodingRules rule, InputStream in);
	
	/**
	 * @return The printed version of previously decoded PDU
	 */
	String getPrintedDecodedPdu();

	/**
	 * Return list of the supported encoding rules.
	 * @return
	 */
	EncodingRules[] getSupportedEncodingRules();
	
	/**
	 * Discard references to all previously generated objects so that they
	 * can be garbage collected.
	 */
	void free();
}
