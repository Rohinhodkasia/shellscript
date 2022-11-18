package com.objsys.sample.android;

/**
 * Represents a description of a PDU encode/decode test.
 */
public class PduTestDescription {

	private String description;
	private EncodeDecodeTest test;
	
	/**
	 * Create a PduDescription.
	 * @param description The description for this PDU, as shown to the user.
	 * @param test The populator for this instance of the PDU.
	 */
	public PduTestDescription(String description, EncodeDecodeTest test)
	{
		this.description = description;
		this.test = test;
	}
	
	public String toString() { return description; }
	
	public EncodeDecodeTest getTest() { return test; }
}
