# create new test case
#
# usage: perl newTest.pl <type>
# <type> is generated 3GPP type name

$type = shift;
die ("type argument not provided") if (!defined ($type));
$type2 = $type . "Rand";

mkdir ($type, 0777);

sub copyFile {
    local $type = shift;
    local $filename = shift;
    local $srcfilepath = './MobileStationClassmark2/' . $filename;
    local $destdir = "./$type";

    open (INFILE, $srcfilepath) || die ("could not open $srcfilepath");
    open (OUTFILE, ">$destdir/$filename")|| 
        die ("could not open $destdir/$filename for output");

    while (<INFILE>) {
        s/\s+$//;
        s/MobileStationClassmark2/$type/g;
        print OUTFILE "$_\n";
    }

    close (INFILE);
    close (OUTFILE);
}

&copyFile ($type, 'writer.c');
&copyFile ($type, 'reader.c');
`cp ./MobileStationClassmark2/makefile ./$type`;
`cp -r ./$type ./$type2`;
