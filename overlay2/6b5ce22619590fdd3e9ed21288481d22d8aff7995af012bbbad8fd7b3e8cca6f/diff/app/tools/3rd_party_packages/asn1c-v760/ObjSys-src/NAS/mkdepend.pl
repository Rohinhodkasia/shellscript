# generate dependency rules file (rules.mk) 
# usage: mkdepend [-v]

$g_debug = 0;

$numargs = @ARGV;

if ($numargs >= 1 && $ARGV[$numargs - 1] eq "-v") {
    $g_debug = 1;
}

if (-e "rules.mk") {
    `rm -f rules.mk~`;
    `mv rules.mk rules.mk~`;
}

open (OUTFILE, ">rules.mk") || 
    die ("could not open rules.mk for output");

print OUTFILE "# C to object file compilation rules\n";

# open objects2.mk file and use to get list of target objects

open (INFILE, "objects.mk") || die ("could not open objects.mk: $!");

while (<INFILE>) {
    if (/(\w+)\$\(OBJ\)/) {
        $filebase = $1;
        # print "$filebase\n";

        # determine source file
        if ( -e "$filebase.c" ) {
            &addRules ("$filebase.c");
        }
        else {
            print "source file for $filebase not found\n";
        }
    }
}

close (INFILE);
close (OUTFILE);

sub addRules {
    local $sourcefile = shift;
    local $cfile = 0;
    local @rules = (`gcc $sourcefile -E -MM -I. -I../../..`);

    foreach $line (@rules) {
        # if line starts with a non-whitespace character, it is the 
        # start of a new rule ..
        if ($line =~ /^\w/) {
            # change .o to $(OBJ)
            $line =~ s/\.o/\$(OBJ)/;

            # add a newline 
            print OUTFILE "\n";

            # get C source file from rule
            $cfile = '$(SRCDIR)$(PS)' . $sourcefile;
        }

        # change source file paths to use macro names
        $line =~ s/\.\.\/\.\.\/\.\.\/rtsrc\//\$\(RTSRCDIR\)\$\(PS\)/g;
        $line =~ s/\.\.\/\.\.\/\.\.\/rtxsrc\//\$\(RTXSRCDIR\)\$\(PS\)/g;
        $line =~ s/\.\.\/\.\.\/\.\.\/rt3gppsrc\//\$\(RT3GPPSRCDIR\)\$\(PS\)/g;
        $line =~ s/rtkey.h//;
        $line =~ s/\s(TS\w+\.[ch])/ \$\(SRCDIR\)\$\(PS\)$1/g;
        $line =~ s/\s(nas\w+\.[ch])/ \$\(SRCDIR\)\$\(PS\)$1/g;

        print OUTFILE $line;
    }

    # add compile command
    if ($cfile) {
        print OUTFILE 
            "\t\$(CC) \$(CFLAGS) -c \$(IPATHS) $cfile\n";
    }
}
