package sample_ber.EmployeeSocketStream;

import com.objsys.asn1j.runtime.*;
import java.io.*;
import java.net.*;

public class Reader {
   public static void main (String args[]) {
       String ipAddress = null;
       int port = 9000;
       boolean trace = true;

      // Process command line arguments

      if (args.length > 0) {
         for (int i = 0; i < args.length; i++) {
            if (args[i].equals ("-v")) 
                Diag.instance().setEnabled (true);
            else if (args[i].equals ("-l")) {
               String param = new String (args[++i]);
               ipAddress = new String (param);
               int pi = ipAddress.indexOf (':');
               if (pi != -1)
                  ipAddress = ipAddress.substring (0, pi);
               String portStr = param.substring (pi + 1);
               try {
                  port = Integer.parseInt (portStr);
               }
               catch (Exception x) {
                  System.out.println ("Invalid port value");
                  return;
               }
            }
            else if (args[i].equals ("-notrace")) trace = false;
            else {
                System.out.println ("usage: Reader [ -v ] [ -l <ip-address:port>]");
                System.out.println ("   -v  verbose mode: print trace info");
                System.out.println ("   -l <ip-address:port>  bind local " +
                                          "<ip-address:port>.");
                System.out.println ("   -notrace  do not display trace info");
                return;
            }
         }
      }

      ServerSocket serverSocket = null;
      Socket socket = null;
      try {
          // Create sockets

          serverSocket = new ServerSocket (port, 1, 
             (ipAddress != null) ? InetAddress.getByName (ipAddress) : null);

          if (trace) System.out.println ("Wait for connection...\n");
          socket = serverSocket.accept ();

          if (trace) {
             System.out.println ("Connection established with " + 
                socket.getInetAddress() + ":" + socket.getPort());
          }

          // Create a decode buffer object

          Asn1BerDecodeBuffer decodeBuffer = 
             new Asn1BerDecodeBuffer (socket.getInputStream ());

          // Read and decode the message

          PersonnelRecord personnelRecord = new PersonnelRecord ();
          personnelRecord.decode (decodeBuffer);
          if (trace) {
              System.out.println ("Decode was successful");
              personnelRecord.print (System.out, "personnelRecord", 0);
          }
      }
      catch (Exception e) {
          System.out.println (e.getMessage());
          e.printStackTrace();           
          System.exit(-1);
      }
      finally {
         try {
            if (serverSocket != null)
               serverSocket.close ();
            if (socket != null)
               socket.close ();
         }
         catch (Exception ex) {System.exit(-1);}
      }
   }
}
