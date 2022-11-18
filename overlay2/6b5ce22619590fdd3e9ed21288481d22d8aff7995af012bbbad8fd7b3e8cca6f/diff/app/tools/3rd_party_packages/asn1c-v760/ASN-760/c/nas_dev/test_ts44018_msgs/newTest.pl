# create new test case
#
# usage: perl newTest.pl <type> <pdu>
# <type> is generated 3GPP type name
# <pdu> is what takes place of * in TS44018Msg_*_PDU, eg. DL_DCCH

$type = shift;
$pdu = shift;

die ("type argument not provided") if (!defined ($type));
die ("PDU prefix argument not provided") if (!defined ($pdu));

mkdir ($type, 0777);

sub copyFile {
   local $type = shift;
   local $filename = shift;
   local $srcfilepath = './NOTIFICATION_FACCH/' . $filename;
   local $destdir = "./$type";

   open (INFILE, $srcfilepath) || die ("could not open $srcfilepath");
   open (OUTFILE, ">$destdir/$filename")|| 
      die ("could not open $destdir/$filename for output");

   while (<INFILE>) {
      $lctype = lc($type);
      s/\s+$//;
      s/NOTIFICATION_FACCH/$type/g;
      
      s/RR_Short_PD/${pdu}/g;
      if ($pdu eq "RR_Short_PD") {
         # For RR_Short_PDU, I used lowercase names
         s/notification_facch/$lctype/g;
      }
      else {
         s/notification_facch/$type/g;
         # Replace header stuff
         s/pdu\.rr_short_PD = 0;/pdu.l3HdrOpts.t = 1;\n   pdu.l3HdrOpts.u.skipInd = 0;\n   pdu.protoDiscr = TS24007L3_ProtoDiscr_rrMgmt;/;
         
         next if /pdu\.short_layer_2_header = 0;/
      }
      print OUTFILE "$_\n";
   }

   close (INFILE);
   close (OUTFILE);
}

&copyFile ($type, 'writer.c');
&copyFile ($type, 'reader.c');
`cp ./NOTIFICATION_FACCH/makefile ./$type`;
