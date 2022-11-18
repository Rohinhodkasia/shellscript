#!/usr/local/bin/perl
# Execute all test programs

if ($^O !~ /Windows/) {
   $ENV{"PATH"} = $ENV{"PATH"} . ":.";
}

if (defined ($ENV{'VCINSTALLDIR'})) {
    $makeprog = "nmake -nologo";
}
else { $makeprog = "make"; }

@dirlist = (`ls .`);
my $rc;

foreach $filename (@dirlist) {
    $filename =~ s/\n$//;

    if (-d $filename) {
        chdir ($filename);

        if (-e "makefile") {
            print ("\n$filename\n");

            `$makeprog`;

            if (-e "writer.exe" || -e "writer") {
                print ("executing writer ..\n");
                `writer -v > writer.log`;
                $rc = $?;
                if ($rc != 0) {
                    print "WRITER FAILURE\n";
                    print `writer`;
                }
                elsif (-e "./good/writer.log") {
                    # uncomment to update good writer.log file
                    # `cp -pf writer.log ./good/writer.log`;
                    print "diff writer.log ./good/writer.log\n";
                    print `diff writer.log ./good/writer.log`;
                }
                print ("writer complete\n");
            }

            if (-e "reader.exe" || -e "reader") {
                print ("executing reader ..\n");
                `reader -v > reader.log`;
                $rc = $?;
                if ($rc != 0) {
                    print "READER FAILURE\n";
                    print `reader`;
                }
                elsif (-e "./good/reader.log") {
                    # uncomment to update good reader.log file
                    # `cp -pf reader.log ./good/reader.log`;
                    print "diff reader.log ./good/reader.log\n";
                    print `diff reader.log ./good/reader.log`;
                }
                print ("reader complete\n");
            }
        }

        chdir ('..');
    }
}
