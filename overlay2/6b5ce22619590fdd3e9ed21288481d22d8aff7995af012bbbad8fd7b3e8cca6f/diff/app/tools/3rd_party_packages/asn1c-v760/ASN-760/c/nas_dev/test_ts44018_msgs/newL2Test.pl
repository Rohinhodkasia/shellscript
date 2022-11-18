# create new test case for L2 Pseudo Length message
#
# usage: perl newL2Test.pl <type> <restOctetType>
# <type> is generated 3GPP type name
# <restOctetType> is name of rest octets type

$type = shift;
$restOctetType = shift;

die ("type argument not provided") if (!defined ($type));
die ("restOctetType argument not provided") if (!defined ($restOctetType));

mkdir ($type, 0777);

sub copyFile {
   local $type = shift;
   local $filename = shift;
   local $srcfilepath = './ImmediateAssignment/' . $filename;
   local $destdir = "./$type";

   open (INFILE, $srcfilepath) || die ("could not open $srcfilepath");
   open (OUTFILE, ">$destdir/$filename")|| 
      die ("could not open $destdir/$filename for output");

   while (<INFILE>) {
      $lctype = lc($type);
      s/\s+$//;
      s/ImmediateAssignment/$type/g;
      
      s/IA_Rest_Octets/${restOctetType}/g;

      print OUTFILE "$_\n";
   }

   close (INFILE);
   close (OUTFILE);
}

&copyFile ($type, 'writer.c');
&copyFile ($type, 'reader.c');
`cp ./ImmediateAssignment/makefile ./$type`;
