package com.objsys.sample.android;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.net.Socket;
import java.util.ArrayList;

import com.objsys.R;
import com.objsys.asn1j.runtime.Asn1MessageBuffer;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.app.ProgressDialog;
import android.content.DialogInterface;
import android.content.DialogInterface.OnCancelListener;
import android.os.Bundle;
import android.text.method.ScrollingMovementMethod;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RadioGroup;
import android.widget.RadioGroup.OnCheckedChangeListener;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

public class AndroidSampleActivity extends Activity implements OnClickListener {
	
   private static final int DIALOG_METHOD = 1;
   
   /* GUI objects */
   private Spinner spinner_pdu;
	private Spinner spinner_rules;
	private View runButton;
	private View methodButton;
	private TextView encodedMessage;
	private TextView decodedMessage;	
	private Dialog methodDialog;
	
	private ArrayAdapter<EncodingRules> encRuleAdapter;
	
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        spinner_pdu = (Spinner)findViewById(R.id.spinner_pdu);
        spinner_pdu.setOnItemSelectedListener(new PduSelectionListener() );
        
        encodedMessage = (TextView)findViewById(R.id.tv_encodedMessage);
        encodedMessage.setMovementMethod(
              ScrollingMovementMethod.getInstance() );
        decodedMessage = (TextView)findViewById(R.id.tv_decodedMessage);
        decodedMessage.setMovementMethod( 
              ScrollingMovementMethod.getInstance() );
        
        runButton = findViewById(R.id.button_run);
        runButton.setOnClickListener(this);
        
        methodButton = findViewById(R.id.button_method);
        methodButton.setOnClickListener(this);

        //Add any other tests to this array
        PduTestDescription[] descriptions = new PduTestDescription[] {
           new PduTestDescription("Employee PersonnelRecord", 
                 new com.objsys.sample.Employee.EncodeDecodeTest() ),
           new PduTestDescription("NBAP", 
                       new com.objsys.sample.NBAP.EncodeDecodeTest() )                 
        };
        
        
        ArrayAdapter<PduTestDescription> pduDescriptionsAdapter = 
        		new ArrayAdapter<PduTestDescription>(this, 
        		   android.R.layout.simple_spinner_item, 
        		   descriptions);

        pduDescriptionsAdapter.setDropDownViewResource(
              android.R.layout.simple_spinner_dropdown_item);
        spinner_pdu.setAdapter(pduDescriptionsAdapter);
        
        //Create and set adapter for encoding rules list
        //The list is populated when a PDU test is selected        
        encRuleAdapter = 
              new ArrayAdapter<EncodingRules>(this, android.R.layout.simple_spinner_item,   
                    new ArrayList<EncodingRules>() );
        spinner_rules = (Spinner) findViewById(R.id.spinner_rules);
        spinner_rules.setAdapter(encRuleAdapter);
    }

	@Override
	public void onClick(View v) {
		if ( v == runButton ) {
		   //clear any earlier output
		   encodedMessage.setText("");
		   decodedMessage.setText("");
		   
			PduTestDescription pduDesc = (PduTestDescription) 
			      spinner_pdu.getSelectedItem();
			
			EncodingRules rules = (EncodingRules)
			      spinner_rules.getSelectedItem();
						
			EncodeDecodeTest test = pduDesc.getTest();
			test.populate();
						
			//figure what method of testing to use
			//If the methodDialog is not created, then we use local encode/decode.
			RadioGroup rg = methodDialog == null ? null :
			     (RadioGroup) methodDialog.findViewById(R.id.radioGroup1);

			int method = rg == null ? R.id.rb_decode_local :
			   rg.getCheckedRadioButtonId();

			if ( method == R.id.rb_decode_local )
			   runLocalEncodeDecodeTest(test, rules);
			else
			   runSocketEncodeTest(test, rules);

			test.free();
		}	
		else if ( v == methodButton ) {
		   showDialog(DIALOG_METHOD);		   
		}
	}
	
	@Override
	protected Dialog onCreateDialog(int dialog)
	{
	   switch(dialog) {
	   case DIALOG_METHOD:
	      
	      methodDialog = new Dialog(this);

	      methodDialog.setContentView(R.layout.select_test_method);
	      methodDialog.setTitle("Specify Test Method");
	      
	      final View socketLayout = 
	            methodDialog.findViewById(R.id.socket_layout);
	      
	      //socketLayout contains controls applicable only when the user picks
	      //encode to socket option.  Hide the layout. 
	      socketLayout.setVisibility(View.GONE);
	      
	      //setup a listener to hide/show the socketLayout according to
	      //user selection
	      ((RadioGroup)methodDialog.findViewById(R.id.radioGroup1))
	         .setOnCheckedChangeListener( new OnCheckedChangeListener() {
               
               @Override
               public void onCheckedChanged(RadioGroup group, int checkedId) {
                  int desiredVisibility = 
                        checkedId == R.id.rb_encode_to_socket ? 
                              View.VISIBLE : View.GONE;
                  
                  if ( desiredVisibility != socketLayout.getVisibility())
                     socketLayout.setVisibility(desiredVisibility);
               }
            } );
	      
	      //setup listener for info button
	      ((Button)methodDialog.findViewById(R.id.btnInfo))
	            .setOnClickListener(new OnClickListener() {
                  @Override
                  public void onClick(View v) {
                     //Give an informational dialog
                     AlertDialog.Builder builder = 
                           new AlertDialog.Builder(methodDialog.getContext());
                     builder.setMessage(R.string.server_info);
                     builder.setNeutralButton("Ok", null);
                     builder.show();
                  }
               });
	      
	      //setup listener for ok button
	      ((Button)methodDialog.findViewById(R.id.btnOk))
	         .setOnClickListener(new OnClickListener() {               
               @Override
               public void onClick(View v) {  
                  methodDialog.dismiss();
               }
            });
	      
	      //Supply defaults for server address and port
	      ((EditText)methodDialog.findViewById(R.id.et_server_address))
	         .setText("10.0.2.2");  //default IP address for host machine

	      ((EditText)methodDialog.findViewById(R.id.et_server_port))
         .setText("9000");  //default IP address for host machine
	      
	      return methodDialog;
	      
	   default:
	      return null;
	   }
	}
	
	private void runLocalEncodeDecodeTest(EncodeDecodeTest test, 
	      EncodingRules rules)
	{
      //Create output stream to receive output
      ByteArrayOutputStream out = new ByteArrayOutputStream();

      test.encode(rules, out);
      
      //dump the encoded data to hex.  Create an input stream on the
      //encoded data; reuse "out" to receive hex representation
      ByteArrayInputStream encodedData = 
            new ByteArrayInputStream(out.toByteArray());
      
      out.reset();
      Asn1MessageBuffer.hexDump(encodedData, new PrintStream(out));
      
      encodedMessage.setText( out.toString() );
      
      encodedData.reset();
      test.decode(rules, encodedData);
      decodedMessage.setText( test.getPrintedDecodedPdu() );	   
	}
	
	/**
	 * Using the given test and rules, encode to a socket.
	 * @param test  The populate method should already have been invoked.
	 * @param rules
	 */
	private void runSocketEncodeTest(EncodeDecodeTest test, 
         EncodingRules rules)
   {
      try {        
         //Create output stream to receive output
         ByteArrayOutputStream out = new ByteArrayOutputStream();

         test.encode(rules, out);
         
         //dump the encoded data to hex.  Create an input stream on the
         //encoded data; reuse "out" to receive hex representation
         byte[] encodedData = out.toByteArray();
         ByteArrayInputStream encodedDataStream = 
               new ByteArrayInputStream(encodedData);
         
         out.reset();
         Asn1MessageBuffer.hexDump(encodedDataStream, new PrintStream(out));
         
         encodedMessage.setText("Encoded message to transmit is:\n");
         encodedMessage.append( out.toString() );

         //create dialog as cancelable.  If user cancels, we can't really
         //cancel the transmission, but we won't wait for it anymore.
         ProgressDialog dialog = ProgressDialog.show(this, "", 
               "Transmitting data to server. Please wait...", true, true);
         
         new Thread ( new TransmitServerWorker(dialog, encodedData)).start();
      }
      finally {}
   }

	class TransmitServerWorker implements Runnable {
	   private Dialog dialog;
	   private byte[] data;
	   
      //If the dialog is cancelled, the UI thread will fire the on cancel
      //listener which will set canceled true.  It should suffice to make
      //this field volatile, as we only want to ensure seeing the latest
      //setting.
	   private volatile boolean canceled = false;

	   /**
	    * Create worker to transmit data to server
	    * @param dialog The dialog to dismiss when done.
	    * @param data  The data to transmit.
	    */
	   public TransmitServerWorker(Dialog dialog, byte[] data) {
	      this.dialog = dialog;
	      this.data = data;
	   }

      @Override
      public void run() {
         EditText etServerAddress = (EditText) 
               methodDialog.findViewById(R.id.et_server_address);
         EditText etServerPort = (EditText)
               methodDialog.findViewById(R.id.et_server_port);
         
         String IPADDRESS = etServerAddress.getText().toString();         
         int port = Integer.parseInt(etServerPort.getText().toString());
         
         try {
            //register a listener for dialog being cancelled
            dialog.setOnCancelListener( new OnCancelListener() {              
               @Override
               public void onCancel(DialogInterface dialog) {
                  canceled = true;                 
               }
            });
            
            Socket socket = new Socket (IPADDRESS, port, null, 0);
            socket.getOutputStream().write(data);
            
            if (!canceled) {
               //notify user data transmitted
               AndroidSampleActivity.this.runOnUiThread(
                     new Runnable() {
                        public void run() {
                           Toast.makeText(AndroidSampleActivity.this, 
                                 "Data transmitted", Toast.LENGTH_SHORT).show();
                  }
              });
            }            
         }
         catch (final Exception e) {
            if ( !canceled ) {
               //notify user of error
               encodedMessage.post( new Runnable() {
                  @Override
                  public void run() {
                     encodedMessage.setText( e.toString() );
                  }            
                 });
            }
         }
         dialog.dismiss();
      }
	}
	
	
	/**
	 * Event handler for selection of a PDU test.  This adjusts the list
	 * of encoding rules based on the supported encoding rules for the test.
	 */
	class PduSelectionListener implements OnItemSelectedListener
	{

      @Override
      public void onItemSelected(AdapterView<?> parent, View view, int pos,
            long id) 
      {
         PduTestDescription testDesc = (PduTestDescription) parent.getItemAtPosition(pos); 
         
         encRuleAdapter.clear();
         for (EncodingRules rule : testDesc.getTest().getSupportedEncodingRules()) {
            encRuleAdapter.add(rule);
         }
      }

      @Override
      public void onNothingSelected(AdapterView<?> arg0) {
         encRuleAdapter.clear();
      }
	}
}