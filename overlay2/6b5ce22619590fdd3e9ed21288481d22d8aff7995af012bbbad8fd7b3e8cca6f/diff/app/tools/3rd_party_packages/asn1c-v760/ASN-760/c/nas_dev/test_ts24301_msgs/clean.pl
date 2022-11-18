#!/usr/local/bin/perl
# Clean all sample directories

if (defined ($ENV{'VCINSTALLDIR'})) {
    $makecmd = 'nmake -nologo clean';
}
else { $makecmd = 'make clean RM="rm -f"'; }

foreach $filename (`ls`) {
    $filename =~ s/\n$//;
    if (-d $filename) {
        chdir ($filename);
        if (-e "makefile") {
            print "cleaning $filename ..\n";
            `$makecmd`;
        }
        chdir ("..");
    }
}

