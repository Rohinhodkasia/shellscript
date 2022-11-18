# create new test case
#
# usage: perl newTest.pl <type>
# <type> is generated 3GPP type name

$type = shift;
die ("type argument not provided") if (!defined ($type));
$type2 = $type . "Rand";

mkdir ($type, 0777);
mkdir ($type2, 0777);

sub copyFile {
    local $srcdir = shift;
    local $destdir = shift;
    local $type = shift;
    local $filename = shift;
    local $srcfilepath = $srcdir . '/' . $filename;

    open (INFILE, $srcfilepath) || die ("could not open $srcfilepath");
    open (OUTFILE, ">$destdir/$filename")|| 
        die ("could not open $destdir/$filename for output");

    while (<INFILE>) {
        s/\s+$//;
        s/BA_List_Pref/$type/g;
        print OUTFILE "$_\n";
    }

    close (INFILE);
    close (OUTFILE);
}


&copyFile ('./BA_List_Pref', "./$type", $type, 'writer.c');
&copyFile ('./BA_List_Pref', "./$type", $type, 'reader.c');
&copyFile ('./BA_List_PrefRand', "./$type2", $type, 'writer.c');
&copyFile ('./BA_List_PrefRand', "./$type2", $type, 'reader.c');

`cp ./BA_List_Pref/makefile ./$type`;
`cp ./BA_List_Pref/makefile ./$type2`;

