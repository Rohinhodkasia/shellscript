#!/usr/local/bin/perl
# Execute all sample programs in given subdirectory.  Note that this script 
# can also be used to execute scripts in a test directory be using the 
# test subdir name in place of encoding rules (for example, test_xml)..

use File::Spec;
use Cwd;

# Make some adjustments to the PATH.  For Windows we want the local directory,
# the dev directory, the bin directory, and the language's lib directory
# included in the PATH.
# For non-Windows we want the local directory and the bin directory included.
$windows = 0;
my $ps; # For Java ME XER and XML tests...
if ($^O =~ /Win/) {
    $windows = 1;
    $devDir = `cd`;
    chomp($devDir);
    $newpath = $ENV{"PATH"};
    $newpath .= ';.;' . $devDir . ';..\..\..\bin' . ';..\..\lib';
    $ENV{"PATH"} = $newpath;
    $ps = ";";
}
else { 
    $ENV{"PATH"} = $ENV{"PATH"} . ':.:../../../bin';
    if (defined($ENV{"LD_LIBRARY_PATH"})) {
        $ENV{"LD_LIBRARY_PATH"} = $ENV{"LD_LIBRARY_PATH"} . ':.:../../lib';
    }
    else {
        $ENV{"LD_LIBRARY_PATH"} = '.:../../lib';
    }
    # print "LD_LIBRARY_PATH = $ENV{\"LD_LIBRARY_PATH\"}\n";
    $ps = ":";
}

select STDERR; $| = 1;
select STDOUT; $| = 1;

sub usage {
    local $arch = shift;
    print "usage: sample.pl <subdir> <rules> <function>\n";
    print "  <subdir>       language subdirectory\n";
    if ($arch eq "w32") {
        print "                 (c, cpp, ";
    }
    else { # assume x64
        print "                 (c_64, cpp_64, ";
    }
    print "java, csharp, python, go, xsd)\n";
    print "  <rules>        encoding rules or test subdirectory\n";
    print "                 (ber, der, per, xer, xml, test_*, unit_*, all)\n";
    print "  <function>     function (test, clean, or valgrind)\n";
    print "  [-nodir]       execute <function> in subdir (nodir)\n";
    print "  [-make <make>] name of make utility to invoke (ex. nmake)\n";
    print "  [-genlic <type>] generate a license for testing. <type> can be\n";
    print "                 eval, ifloat, hostid, float, or custom XML\n";
    print "                 filename\n";
    print "  [-dirpat <pattern>] only execute tests in directories that\n";
    print "                 match given pattern\n";
    print "  [-stop]        quit on error\n";
    exit(1);
}

my $architecture = (!-e "c") ? "x64" : "w32";
usage($architecture) if ($#ARGV < 2);
    
$subdir = shift @ARGV;
$rules  = shift @ARGV;
my $function = shift @ARGV;
my $nostop = 1;
my $nerror = 0;
my $verbose = 0;
my $makeprog;
my $genlic;
my $dirpattern;
our $timings = 0;

while ($_ = shift @ARGV) {
    if ($_ eq '-make') {
        usage($architecture) unless $makeprog = shift @ARGV;
        next;
    } elsif ($_ eq '-stop') {
        $nostop = 0;
    } elsif ($_ eq '-nodir') {
        $nodir = 1;
    } elsif ($_ eq '-hread' || $_ eq '-v') {
        $verbose = 1;
    } elsif ($_ eq '-showtiming') {
        $timings = 1;
    } elsif ($_ eq '-genlic') {
        usage($architecture) unless $genlic = shift @ARGV;
    } elsif ($_ eq '-dirpat') {
        usage($architecture) unless $dirpattern = shift @ARGV;
    } else {
        print STDERR "Unknown option '$_'\n";
        usage($architecture);
    }
}

my $known_subdir = 0;
if ($subdir eq "java" || $subdir eq "csharp" || $subdir eq "go" ||
    $subdir eq "xsd") {
    $known_subdir = 1;
}
elsif ($subdir eq "python") {
    $ENV{"PYTHONPATH"} = "../..";
    $known_subdir = 1;
}
elsif ($architecture eq "w32") {
    $known_subdir = ($subdir eq "c" || $subdir =~ /^c_(\w+)/ ||
                     $subdir eq "cpp" || $subdir =~ /^cpp_(\w+)/);
}
else {
    $known_subdir = ($subdir eq "c_64" || $subdir =~ /^c_(vs|VS)\d{4}_64/ ||
                     $subdir eq "cpp_64" || $subdir =~ /^cpp_(vs|VS)\d{4}_64/);
}
die ("$subdir is not a known subdirectory " .
     '(must be c|c_64, cpp|cpp_64, csharp, java, python, go, or xsd)')
    unless ($known_subdir);

die ("$rules are not valid encoding rules\n" . 
     "(must be ber, cer, der, json, mder, oer, per, xer, xml, avn,\n" .
     " test_*, unit_*, or all)") 
    unless ($rules eq "ber" || $rules eq "cer" || $rules eq "der" || 
            $rules eq "per" || $rules eq "uper" || $rules eq "xer" || 
            $rules eq "xml" || $rules eq "all" || $rules =~ /test_/ ||
            $rules eq "json" || $rules =~ /unit_/ || $rules eq "mder" ||
            $rules eq "oer" || $rules eq "avn" || $nodir);

die ("$function is not a known function (must be test or clean)") 
    unless ($function eq "test" || $function eq "clean" || 
            $function eq "valgrind");

die ("valgrind cannot be run on Windows") 
    if ($function eq "valgrind" && $windows);

# if $genlic is set, generate a license file
if (defined($genlic)) {
    # deactivate existing license
    my $licres = `./bin/asn1c -licdeact`;
    die ($licres) if ($licres =~ /^ERROR/);

    if ($genlic eq "float") {
        # RLM floating license
        $licres = `./bin/asn1c -licinstall ./testlic/float.webserver.lic`;
        die ($licres) if ($licres =~ /^ERROR/);
    }
    else {
        # generate license key and activate
        # create new key
        my $licwriter = './licmgr/bin/licwriter ';
        if ($genlic eq "eval") {
            $licwriter .= '-product ASN1C -minVersion 7.4 -maxVersion 7.5 -d 30 -all -pro';
        }
        elsif ($genlic eq "ifloat") {
            $licwriter .= '-xml ./testlic/asn1c_ifloat_test.xml';
        }
        elsif ($genlic eq "hostid") {
            $licwriter .= '-xml ./testlic/asn1c_hostid_local.xml';
        }
        elsif ($genlic =~ /\.xml$/) {
            # custom license file
            $licwriter .= '-xml ' . $genlic;
        }
        else {
            die ("unsupported license type '" . $genlic . "'");
        }

        print ("$licwriter\n") if ($verbose);
        
        my $lickey = `$licwriter -base64str`;
        die ($lickey) if ($lickey =~ /^ERROR/);
        print ("lickey = $lickey\n") if ($verbose);

        # activate new license
        $licres = `./bin/asn1c -lickey $lickey`;
        die ($licres) if ($licres =~ /^ERROR/);
    }
}

$makeprog = getMakeProg() unless $makeprog;
@skipList = loadSkipList();

# set XSD and XERCES variables
$XSDLIBDIR = "../../../xsd/lib";
$XERCESDIR = "../../../xsd/xmlParsers/xerces-2_2_0";
$XERCESCLASSPATH = "\".;$XERCESDIR/xercesImpl.jar;$XERCESDIR/xmlParserAPIs.jar;$XERCESDIR/xercesSamples.jar\"";

$subdir = 'golang' if $subdir eq 'go';
chdir ("./$subdir") || die("could not chdir to $subdir");

# handle dynamic link libraries on mac os X
$bmac = 0;
$bredirectok = 1;
if ($^O =~ /darwin/) {
   $bmac = 1;
   # macOS 11 (Big Sur) seems to have a lot of problems with redirection.
   $pv = `sw_vers -productVersion`;
   chomp($pv);
   @pieces = split(/\./, $pv);
   $major = $pieces[0];
   $bredirectok = 0 if ($major >= 11);
   $tmpdir = `pwd`;
   chomp($tmpdir);
   $ENV{'DYLD_FALLBACK_LIBRARY_PATH'} = "$tmpdir/lib"; 
}

if ($subdir eq "xsd") {
    print "--- Executing XSD sample programs ---\n";
    &execSamples ("sample", $function, $dirpattern);
}
elsif ($rules eq "all") {
    print "--- Executing $function on $subdir ber samples ---\n";
    &execSamples ("sample_ber", $function, $dirpattern);
    print "--- Executing $function on $subdir der samples ---\n";
    &execSamples ("sample_der", $function, $dirpattern);
    print "--- Executing $function on $subdir per samples ---\n";
    &execSamples ("sample_per", $function, $dirpattern);
    print "--- Executing $function on $subdir uper samples ---\n";
    &execSamples ("sample_uper", $function, $dirpattern);
    print "--- Executing $function on $subdir oer samples ---\n";
    &execSamples ("sample_oer", $function, $dirpattern);
    print "--- Executing $function on $subdir xer samples ---\n";
    &execSamples ("sample_xer", $function, $dirpattern);
    print "--- Executing $function on $subdir xml samples ---\n";
    &execSamples ("sample_xml", $function, $dirpattern);
    print "--- Executing $function on $subdir json samples ---\n";
    &execSamples ("sample_json", $function, $dirpattern);
    print "--- Executing $function on $subdir avn samples ---\n";
    &execSamples ("sample_avn", $function, $dirpattern);
}
elsif ($nodir) {
    chdir($rules) or die "Unable to change directory: $!";
    execSampleInCwd($subdir, ".", $rules, $function);
    chdir("..");
}
elsif ($rules =~ /test_/) {
    &execSamples ($rules, $function, $dirpattern);
}
elsif ($rules =~ /unit_/) {
    if ($function eq "test") {
        # generate an rtkey.dat file and define ACLICFILE to point to it.
        `../bin/asn1c -genlic`;
        $ENV{"ACLICFILE"} = "../../rtkey.dat";
    }

    &execSamples ($rules, $function, $dirpattern);

    if ($function eq "test") {
        # delete the ACLICFILE environment variable definition and remove the
        # rtkey.dat file that we created.
        delete $ENV{"ACLICFILE"};
        `rm rtkey.dat`;
    }
}
else {
    print "--- Executing $function on $subdir $rules samples ---\n";
    &execSamples ("sample_${rules}", $function, $dirpattern);
}
exit $nerror; 

sub execSampleInCwd {
    my $subdir = shift @_;
    my $dirName = shift @_;
    my $filename = shift @_;
    my $function = shift @_;

    my $ranBuild = 0;

    if ( ! -d "../$filename" ) {
        die "Invalid filename '$filename'";
    }

    # Is this directory in the skip list?
    if (checkSkipList()) {
        printTestName($filename);
        print "SKIPPED\n";
        return;
    }

    my $tms = time();

    # if special test script exists, execute it
    if (-e "test.pl" && $function eq "test") {
        printTestName($filename);
        execCmd("perl test.pl") or return;
        print "\n";
    }
    elsif (-e "clean.pl" && $function eq "clean") {
        printTestName($filename) if ($verbose);
        execCmd("perl clean.pl") or return;
    }
    elsif ($function eq "valgrind") {
        if (-e 'vg.sh') {
            if (-x 'vg.sh') {
                printTestName($filename);
                $verbose = 1;
                $noleak = 0;

                execCmd("./vg.sh > vg.log 2>&1") or return;
                # check log for leaks
                open (my $vg_log, "vg.log") || die ("open vg.log: $!");
                my $displayLines = 0;
                while (<$vg_log>) {
                    if (/definitely lost: 0 bytes/) {
                        print "No leaks found\n";
                        $noleak = 1;
                        last;
                    }
                }
                close (LOGFILE);
                if ($noleak == 0) {
                    seek ($vg_log, 0, 0);             
                    open (LOGFILE, "vg.log") || die ("open vg.log: $!");
                    while (<$vg_log>) {
                        if (/HEAP\sSUMMARY/) {
                            $displayLines = 1;
                        }
                        if ($displayLines) { print $_; }
                    }
                }
                close ($vg_log);
            }
            else {
                print ("ERROR: vg.sh exists but is not executable\n");
            }
        }
        else { print '!'; }

        print "\n";
    }

    # else execute standard test procedure

    elsif (-e "build.xml") {
        if ($function eq "test") {
            printTestName($filename);
            execCmd("ant build");
            #Searches for build.xml files. Executes ant build to test them.	
            if (-e "Writer.class") {
                execCmd("ant writer");
            }		
            if (-e "Reader.class") {
                execCmd("ant reader");
            }
            $ranBuild = 1;
        }
        elsif ($function eq "clean") {
            execCmd("ant clean") or return;
        }
    }
    #Runs reader and writer
    elsif (-e "makefile") {
        if ($function eq "test") {
            # major kludge: if java and jsources.mk does not 
            # exist, create a dummy file
            if ($subdir eq "java" && ! -e "jsources.mk") {
                &genJsources ();
                #open (MKFILE, ">jsources.mk");
                #print MKFILE "JSOURCES = \n";
                #close (MKFILE);
            }
            if ($subdir eq "csharp") {
                if ( -e '../../asn1rtcs.dll') {
                    `cp ../../asn1rtcs.dll .`;
                }
                elsif ( -e '../../lic_asn1rtcs.dll') {
                    `cp ../../lic_asn1rtcs.dll ./asn1rtcs.dll`;
                }
                else {
                    die ('C# run-time DLL file asn1rtcs.dll not found');
                }
            }

            printTestName($filename);
            execCmd($makeprog) or return;

            if ($dirName =~ /_xer_javame/) {
               &doXerJavaMeTest($filename);
            }
            elsif ($dirName =~ /_xml_javame/) {
               &doXmlJavaMeTest($filename);
            }

            $ranBuild = 1;
        }
        elsif ($function eq "clean") {
            printTestName($filename) if ($verbose);
            execCmd("$makeprog clean") or return;
        }
    }

    if ($ranBuild) {
      if ($dirName =~ /_xer_javame/ || $dirName =~ /_xml_javame/) 
      {
         # do nothing.  These are handled above and only makefiles are
         # supported.
      }
      elsif ($dirName =~ /unit_/) { # Unit testing
         &doUnitTest ($subdir, $dirName);
      }
      elsif ($dirName =~/_javame/) {   #either BER or PER
         &doJavaMeTest($subdir);
      }
      elsif ($dirName =~ /_[bcdo]er/ || $dirName =~ /_mder/ || 
             $dirName =~ /_cdr/ || $dirName =~ /_depends/) {
          &doBERTest ($subdir, $dirName);
      }
      elsif ($dirName =~ /_per/) {
          &doPERTest ($subdir);
      }      
      elsif ($dirName =~ /_aper/) {
          &doAPERTest ($subdir);
      }      
      elsif ($dirName =~ /_uper/) {
          &doUPERTest ($subdir);
      }
      elsif ($dirName =~ /^(nas_dev|nasapi)/) {
          # (nasapi is the folder name for an installed Java NAS kit)
          &do3GPPTest ($subdir);
      }
      elsif ($dirName =~ /_xer/) {
          &doXERTest ($subdir);
      }
      elsif ($dirName =~ /_xml/) {
          &doXMLTest ($subdir);
      }
      elsif ($dirName =~ /_json/) {
          &doJSONTest ($subdir);
      }
      elsif ($dirName =~ /_avn/) {
          &doAVNTest ($subdir);
      }
      elsif ($subdir ne "xsd") {
          die ("unknown subdirectory.");
      }

      my $tme = time();
      my $dur = $tme - $tms;

      if ($main::timings) {
         print "\t[ " . int($dur/60) . "m " . $dur % 60 . "s ]" 
            if ($function ne "clean");
      }
      print "\n";
    }
}

sub execSamples {
    local $dirName = shift;
    local $func = shift;
    local $dirpat = shift;
    if (!(-e $dirName)) {
        print "ERROR: subdir $dirName does not exist, test skipped\n";
        return;
    }
    # print "executing sample programs in directory $dirName\n";
    chdir ($dirName);
    @dirlist = (`ls .`);

    foreach $filename (@dirlist) {
        $filename =~ s/\n$//;

        if (-d $filename) {
            next if ($filename eq "EmployeeSocketStream");

            if (defined($dirpat)) {
                next if (!($filename =~ m/$dirpat/));
            }

            chdir ($filename);

            execSampleInCwd($subdir, $dirName, $filename, $func);

            chdir ('..');
        }
    }

    chdir ('..');
    if (index ($dirName, '/') >= 0) {
        chdir ('..');
    }
    print "\n" if $func eq "clean";
}

sub execRWProg {
    local ($rwcmd) = @_;
    if (-e 'runexe.bat' && $windows) {
        return execCmd ("runexe.bat $rwcmd");
    }
    else {
        return execCmdToLog ("$rwcmd");
    }
}

sub doJavaMeTest {
    local ($subdir) = @_;
    my $ntest = 0;

   if (-e "message.dat" && -e "message.out.dat") {
      execDiff("diff -w message.dat message.out.dat"); # or return;
      $ntest++;
   }
   if (-e "message.a.dat" && -e "message.a.out.dat") {
      execDiff("diff -w message.a.dat message.a.out.dat"); # or return;
      $ntest++;
   }
   if (-e "message.u.dat" && -e "message.u.out.dat") {
      execDiff("diff -w message.u.dat message.u.out.dat"); # or return;
      $ntest++;
   }
}

sub doXerJavaMeTest {
   local ($filename) = @_;
   if (-e "EncDec.class") {
      $classpath = "../..";
      $classpath .= "${ps}../../../javame_px/asn1rt.jar";
      $classpath .= "${ps}../../xerces/xercesImpl.jar";
      $classpath .= "${ps}../../xerces/xml-apis.jar";
      execCmd("java -classpath $classpath test_xer_javame.$filename.EncDec");
   }
}

sub doXmlJavaMeTest {
   local ($filename) = @_;
   if (-e "EncDec.class") {
      $classpath = "../..";
      $classpath .= "${ps}../../../javame_px/asn1rt.jar";
      $classpath .= "${ps}../../xerces/xercesImpl.jar";
      $classpath .= "${ps}../../xerces/xml-apis.jar";
      execCmd("java -classpath $classpath test_xml_javame.$filename.EncDec");
   }
}


sub doAVNTest {
   local ($subdir, $rulesdir) = @_;
   my $ntest = 0;

   if ($subdir eq "c" || $subdir eq "cpp" ) {
      if (-e "writer.exe" || -e "writer") {
         print (".");
         if ($bredirectok) {
            `writer -v > writer.log`;
         }
         else {
            `writer -v`;
         }
         $rc = $?;
         if ($rc != 0) {
            error("writer.exe -v");
         } 

         $ntest++;
      }

      if (-e "reader.exe" || -e "reader") {
         print (".");
         if ($bredirectok) {
            `reader -v > reader.log`;
         }
         else {
            `reader -v`;
         }
         $rc = $?;
         if ($rc != 0) {
            error("reader.exe -v");
         } 
         
         $ntest++;
      }
   }
    
   my @goodfiles = opendir(GOODDIR, './good');
   while ($goodfile = readdir(GOODDIR)) {
      if (-e $goodfile && ! -d $goodfile) {
          execDiff("diff -b $goodfile ./good/$goodfile");
          $ntest++;
      }
   }
   closedir(GOODDIR);
    
   print "!" unless $ntest;
}


sub doBERTest {
    local ($subdir, $rulesdir) = @_;
    my $ntest = 0;

    if ($subdir eq "java" || $subdir eq "csharp" ) {
        if (-e "writer.log" && -e "writer.glg") {
            execDiff("diff -w writer.log writer.glg"); # or return;
            $ntest++;
        }
        if (-e "reader.log" && -e "reader.glg") {
            execDiff("diff -w reader.log reader.glg"); # or return;
            $ntest++;
        }
        if (-e "readeri.log") {
            if (-e "readeri.glg") {
                execDiff("diff -w readeri.log readeri.glg"); # or return;
                $ntest++;
            }
            elsif (-e "reader.glg") {
                execDiff("diff -w readeri.log reader.glg"); # or return;
                $ntest++;
            }
        }
        if (-e "./good/message.dat") {
            execDiff("diff -b message.dat ./good") ; # or return;
            $ntest++;
        }
    }
    elsif ($subdir eq "python") {
        my @goodfiles = opendir(GOODDIR, './good');
        while ($goodfile = readdir(GOODDIR)) {
            if (-e $goodfile && ! -d $goodfile) {
                execDiff("diff -w $goodfile ./good/$goodfile");
                $ntest++;
            }
        }
        closedir(GOODDIR);
    }
    else {
        if ((-e "server.exe" || -e "server") && 
            (-e "client.exe" || -e "client")) {
            execClientServer();# or return;
            $ntest++;
        }
        if (-e "writer.exe" || -e "writer") {
            execRWProg ("writer -notrace");# or return;
            $ntest++;
        }

        if (-e "reader.exe" || -e "reader") {
            execRWProg ("reader -notrace"); # or return;
            $ntest++;
        }

        if (-e "message_ber.dat") {
            execDiff("diff message.dat message_ber.dat"); # or return;
            $ntest++;
        }
        if (-e "./good/message.dat") {
            execDiff("diff -b message.dat ./good") ; # or return;
            $ntest++;
        }

        # convert BER data file to indef length and verify we 
        # can read and decode it

        if ((-e "reader.exe" || -e "reader") 
            && -e "message.dat" 
            && $rulesdir =~ /_[bc]er/
            && !-e "nomessagei.dat")
        {
            execCmd ("ber2indef message.dat messagei.dat"); # or return;
            execRWProg ("reader -i messagei.dat -notrace"); # or return;
            $ntest++;
        }

    }
    print "!" unless $ntest;
}

sub do3GPPTest {
    local ($subdir) = @_;
    my $ntest = 0;

    if ($subdir eq "c") {
        if (-e "writer.exe" || -e "writer") {
            # execRWProg ("writer -notrace") ;
            print (".");
            `writer -v > writer.log`;
            $rc = $?;
            if ($rc != 0) {
               error("writer.exe -v");
            } 

            $ntest++;
        }
        if (-e "reader.exe" || -e "reader") {
            # execRWProg ("reader -notrace") ;
            print (".");
            `reader -v > reader.log`;
            $rc = $?;
            if ($rc != 0) {
               error("reader.exe -v");
            } 
            $ntest++;
        }
        # diff output file with known good output
        if (-e "writer.log" && -e "./good/writer.log") {
            execDiff ("diff -w writer.log ./good/writer.log") ; # or return;
            $ntest++;
        }
        if (-e "reader.log" && -e "./good/reader.log") {
            execDiff ("diff -w reader.log ./good/reader.log") ; # or return;
            $ntest++;
        }
    }
    elsif ($subdir eq "java" ) {
        if (-e "writer.log" && -e "./good/writer.log") {
            execDiff("diff -w writer.log ./good/writer.log") ; # or return;
            $ntest++;
        }
        if (-e "reader.log" && -e "./good/reader.log") {
            execDiff("diff -w reader.log ./good/reader.log") ; # or return;
            $ntest++;
        }
    }

    print "!" unless $ntest;
}

sub doPERTest {
    local ($subdir) = @_;
    my $ntest = 0;

    if ($subdir eq "java" || $subdir eq "csharp" ) {
        if (-e "writer_a.log" && -e "writer_a.glg") {
            execDiff("diff -w writer_a.log writer_a.glg") ; # or return;
            $ntest++;
        }
        if (-e "reader_a.log" && -e "reader_a.glg") {
            execDiff("diff -w reader_a.log reader_a.glg") ; # or return;
            $ntest++;
        }
        if (-e "writer_u.log" && -e "writer_u.glg") {
            execDiff("diff -w writer_u.log writer_u.glg") ; # or return;
            $ntest++;
        }
        if (-e "reader_u.log" && -e "reader_u.glg") {
            execDiff("diff -w reader_u.log reader_u.glg") ; # or return;
            $ntest++;
        }
    }
    elsif ($subdir eq "golang") {
        if (-e "writer.log" && -e "good/writer.log") {
            execDiff("diff -w writer.log good/writer.log") ; # or return;
            $ntest++;
        }
        if (-e "reader.log" && -e "good/reader.log") {
            execDiff("diff -w reader.log good/reader.log") ; # or return;
            $ntest++;
        }
    }
    else {
        if ((-e "server.exe" || -e "server") && 
            (-e "client.exe" || -e "client")) {
            execClientServer() ; # or return;
            $ntest++;
        }

        if (-e "writer.exe" || -e "writer") {
            execRWProg ("writer -a -notrace") ; # or return;
            $ntest++;
        }

        if (-e "reader.cmd") {
            open (CMDFILE, "reader.cmd") || die ("open reader.cmd: $!");
            while (<CMDFILE>) {
                chomp;
                execRWProg ($_) ; # or return;
                $ntest++;
            }
            close (CMDFILE);
        }
        elsif (-e "reader.exe" || -e "reader") {
            execRWProg ("reader -a -notrace") ; # or return;
            $ntest++;
        }

        if (-e "message_a.dat") {
            execDiff("diff message.dat message_a.dat");
            $ntest++;
        }
        elsif (-e "good/message_a.dat") {
            execDiff("diff message.dat good/message_a.dat");
            $ntest++;
        }

        if (-e "writer.exe" || -e "writer") {
            execRWProg ("writer -u -notrace") ; # or return;
            $ntest++;

            # only do unaligned reader test if writer exists (this is 
            # because megaco only contains an aligned data file)..

            if (-e "reader.exe" || -e "reader") {
                execRWProg ("reader -u -notrace") ; # or return;
            }

            if (-e "message_u.dat") {
                execDiff("diff message.dat message_u.dat") ; # or return;
            }
            elsif (-e "good/message_u.dat") {
                execDiff("diff message.dat good/message_u.dat");
                $ntest++;
            }
        }
    }
    print "!" unless $ntest;
}

# Similar to doPERTest except defaults to aligned PER only, so does not run
#  any unaligned PER tests...
sub doAPERTest {
    local ($subdir) = @_;
    my $ntest = 0;

    if ((-e "server.exe" || -e "server") && 
        (-e "client.exe" || -e "client")) {
        execClientServer(); # or return;
        $ntest++;
    }

    if (-e "writer.exe" || -e "writer") {
        execRWProg ("writer -notrace"); # or return;
        $ntest++;
    }

    if (-e "reader.exe" || -e "reader") {
        execRWProg ("reader -notrace"); # or return;
        $ntest++;
    }

    print "!" unless $ntest;
}

sub doUPERTest {
    local ($subdir) = @_;
    my $ntest = 0;

    if ($subdir eq "java" || $subdir eq "csharp" ) {
        if (-e "writer_u.log" && -e "writer_u.glg") {
            execDiff("diff -w writer_u.log writer_u.glg") ; # or return;
            $ntest++;
        }
        if (-e "reader_u.log" && -e "reader_u.glg") {
            execDiff("diff -w reader_u.log reader_u.glg") ; # or return;
            $ntest++;
        }
    }
    elsif ($subdir eq "golang") {
        if (-e "writer.log" && -e "good/writer.log") {
            execDiff("diff -w writer.log good/writer.log") ; # or return;
            $ntest++;
        }
        if (-e "reader.log" && -e "good/reader.log") {
            execDiff("diff -w reader.log good/reader.log") ; # or return;
            $ntest++;
        }
    }
    else {
        if ((-e "server.exe" || -e "server") && 
            (-e "client.exe" || -e "client")) {
            execClientServer() ; # or return;
            $ntest++;
        }

        if (-e "writer.exe" || -e "writer") {
            execRWProg ("writer -notrace") ; # or return;
            $ntest++;
        }

        if (-e "reader.exe" || -e "reader") {
            execRWProg ("reader -notrace") ; # or return;
            $ntest++;
        }

        if (-e "message_u.dat") {
            execDiff("diff message.dat message_u.dat") ; # or return;
        }
    }

    print "!" unless $ntest;
}

sub doXERTest {
    local ($subdir) = @_;
    my $ntest = 0;

    if ($subdir eq "java" || $subdir eq "csharp" ) {
        if (-e "writer.log" && -e "writer.glg") {
            execDiff("diff -w writer.log writer.glg") ; # or return;
            $ntest++;
        }
        if (-e "reader.log" && -e "reader.glg") {
            execDiff("diff -w reader.log reader.glg") ; # or return;
            $ntest++;
        }
        if (-e "./good/message.xml") {
            execDiff("diff -w message.xml ./good") ; # or return;
            $ntest++;
        }
        if (-e "message.xml" && -e "message.glg") {
            execDiff("diff -w message.xml message.glg") ; # or return;
            $ntest++;
        }
    }
    else {
        if ((-e "server.exe" || -e "server") && 
            (-e "client.exe" || -e "client")) {
            execClientServer() ; # or return;
            $ntest++;
        }

        if (-e "writer.exe" || -e "writer") {
            execRWProg ("writer -notrace") ; # or return;
            $ntest++;
        }

        if (-e "reader.exe" || -e "reader") {
            execRWProg ("reader -notrace") ; # or return;
            $ntest++;
        }

        if (-e "./good/message.xml") {
            execDiff("diff -w message.xml ./good/message.xml") ; # or return;
            $ntest++;
        }
        if (-e "message.xml" && -e "message.glg") {
            execDiff("diff -w message.xml message.glg") ; # or return;
            $ntest++;
        }
    }
    print "!" unless $ntest;
}


sub doXMLTest {
    local ($subdir) = @_;
    local $filename;
    my $ntest = 0;

    if ($subdir eq "java" || $subdir eq "csharp" ) {
        if (-e "writer.log" && -e "writer.glg") {
            execDiff("diff -w writer.log writer.glg");
            $ntest++;
        }
        if (-e "reader.log" && -e "reader.glg") {
            execDiff("diff -w reader.log reader.glg");
            $ntest++;
        }
        if (-e "message.xml" && -e "message.glg") {
            execDiff("diff -w message.xml message.glg");
            $ntest++;
        }
    }
    else {
        
        if ((-e "server.exe" || -e "server") && 
            (-e "client.exe" || -e "client")) {
            execClientServer();
            $ntest++;
        }

        if (-e "writer.exe" || -e "writer") {
            execRWProg ("writer -notrace");
            $ntest++;
        }

        if (-e "reader.exe" || -e "reader") {
            execRWProg ("reader -notrace");
            $ntest++;
        }
    }

    if (-e "message.glg") {
        execDiff("diff -w message.xml message.glg");
        $ntest++;
    }

    if (-e "message.xml") {
        # check if XSD file(s) exist
        $hasXSDs = 0;
        foreach $filename (`ls .`) {
            $filename =~ s/\n$//;
            $hasXSDs = ($filename =~ /\.xsd$/);
            last if $hasXSDs;
        }

        # if XSD files exist, valiidate instance
        if ($hasXSDs && -e '../../../java/util/Val.class') {
            $res = `java -cp ../../../java/util/Val Val message.xml *.xsd`;
            chomp $res;
            if ($res eq "Instance is valid.") {
                print ".";
            }
            else {
                print "$res\n";
            }
        }
    }

    print "!" unless $ntest;
}

sub doJSONTest {
    local ($subdir, $rulesdir) = @_;
    my $ntest = 0;

    if ($subdir eq "java" || $subdir eq "csharp" ) {
        if (-e "writer.log" && -e "writer.glg") {
            execDiff("diff -w writer.log writer.glg"); # or return;
            $ntest++;
        }
        if (-e "reader.log" && -e "reader.glg") {
            execDiff("diff -w reader.log reader.glg"); # or return;
            $ntest++;
        }
        if (-e "./good/message.json") {
            execDiff("diff -b message.json ./good") ; # or return;
            $ntest++;
        }
    }
    elsif ($subdir eq "python") {
        my @goodfiles = opendir(GOODDIR, './good');
        while ($goodfile = readdir(GOODDIR)) {
            if (-e $goodfile && ! -d $goodfile) {
                execDiff("diff -b $goodfile ./good/$goodfile");
                $ntest++;
            }
        }
        closedir(GOODDIR);
    }    
    else {

        if ((-e "server.exe" || -e "server") && 
            (-e "client.exe" || -e "client")) {
            execClientServer();# or return;
            $ntest++;
        }
        if (-e "writer.exe" || -e "writer") {
            execRWProg ("writer -notrace");# or return;
            $ntest++;
        }

        if (-e "reader.exe" || -e "reader") {
            execRWProg ("reader -notrace"); # or return;
            $ntest++;
        }

        if (-e "./good/message.json") {
            execDiff("diff -b message.json ./good") ; # or return;
            $ntest++;
        }
    }
    print "!" unless $ntest;
}

sub doUnitTest {
   # basics here are that we'll run all of the programs that are associated
   # with the given testing directory, et c.
   my $lang = shift @_; # language is the subdir; test is the dirName
   my $test = shift @_;
   my    $ntest = 0;

   # if we're doing C/C++, we need to collect all of the files and execute their
   # equivalent tests; we assume the test names are the same as the sources
   # less the .c/.cpp extension
   @filelist = `ls *.$lang`;

   for $file(@filelist) {
      chomp($file);
      $file =~ s/\.$lang//;
      $file = "./${file}";

      # found an executable
      if (-e $file || -e "$file.exe") {
         execUnit ($file);
         $ntest ++;
      }
   }
}

sub genJsources {
    $cmdLine = "";
    $asn1c = "";
    $tempDir = "__!!!__";
    open (INMAKE, "makefile");
    while (<INMAKE>) {
        if (/^\s*(\$\(ASN1C\))/ || /^\s*(\$\(ASN1C90\))/) {
            $asn1c = $1;
            s/^\s*//;
            $cmdLine = $_;
            last;
        }
    }
    close (INMAKE);
    return if ($asn1c eq "" || $cmdLine eq "");

    #print "Cmdline from MAKEFILE: $cmdLine";
    #print "\$ASN1C macro: $asn1c\n";
    $pwd = `pwd`;
    
    $pwd =~ /java/;
    if ($asn1c eq "\$\(ASN1C\)") {
        $asn1cPath = $`."bin/asn1c";
        $cmdLine =~ s/\$\(ASN1C\)/$asn1cPath/;
    }
    else {
        $asn1cPath = $`."bin/asn1c90";
        $cmdLine =~ s/\$\(ASN1C90\)/$asn1cPath/;
    }

    $cmdLine =~ s/\n$//;
    $cmdLine .= " -genjsources -o $tempDir";

    `mkdir $tempDir`;

    $cmdLine =~ s/^\/cygdrive\/(\w)/$1:/;
    #print "$cmdLine\n";

    #`/asn1c/dev/bin/asn1c simple-ROSE.asn -ber -java -print -pkgpfx sample_ber -genjsources -o __\$\$\$\$___`;
    `$cmdLine 2>&1`;

    @files = `ls $tempDir`;
    foreach $file (@files) {
        #print $file;
        $file =~ s/\n$//;
        if ($file =~ /.mk$/) {
            # copy $file to ./jsources.mk and replace $tempDir by .

            open (INSRCMK, "$tempDir/$file");
            open (OUTSRCMK, ">jsources.mk");

            #`cp -f $tempDir/$file ./jsources.mk`;
            while (<INSRCMK>) {
                #print $_;
                s/$tempDir/\./;
                print OUTSRCMK $_;
            }

            close (OUTSRCMK);
            close (INSRCMK);
            last;                    
        }
    }
    `rm -rf $tempDir/*`;
    `rmdir $tempDir`;
}

sub loadSkipList {
    my $skipfile = "skiplist.inc";
    my @list;
    if (-e $skipfile) {
        open SKIP, $skipfile or die "Unable to open '$skipfile': $!";
        foreach (<SKIP>) {
            chomp;
            next if /^\s*$/;
            next if /^#/;
                @list[++$#list] = $_;
        }
        close SKIP;
    }
    return @list;
}

sub checkSkipList {
    # Is this directory in the skip list?
    $currDir = getcwd();
    $currDir = "\L$currDir" if ($windows);
    foreach $dir (@skipList) {
        $dir = "\L$dir" if ($windows);
        my $dirLen = length($dir);
        next if $dirLen == 0;
        my $currDirLen = length($currDir);
        if ($currDirLen >= $dirLen) {
            if (substr($currDir, -$dirLen, $dirLen) eq $dir) {
                return 1;
            }
        }
    }
    return 0;
}

sub getMakeProg {

    my $makeprog = "make";
    if (defined ($ENV{'MAKEPROG'})) {
        $makeprog = $ENV{'MAKEPROG'};
    }
    elsif (defined ($ENV{'MSVCDIR'}) || 
           defined ($ENV{'MSDEVDIR'}) ||
           defined ($ENV{'MSDevDir'}) ||
	   defined ($ENV{'VCINSTALLDIR'})) {
        $makeprog = "nmake -nologo";
    }
    else {
        $makeprog = "make";
    }
    return $makeprog;
}

sub printTestName {
    if ($verbose) { 
        print "*********************************************************\n";
    }
    local ($name) = shift @_;
    printf("$name%" . (30 - length($name)) . "s", '');
}

sub error {
    my $cmd = shift @_;
    my $sig = shift @_;
    my $cwd;
    chomp($cwd = `pwd`);
    
    $nerror++;

    if ($sig == 2) {
        print "\n\nReceived SIGINT, stopping there.\n\n";
        exit 1;
    } elsif ($nostop) {
        if ($function eq "clean") {
            print "\nDirectory: $cwd\n";
        }
        print " ERROR cmd=$cmd\n";
    } else {
        print "\n\n### TEST FAILURE ###\n";
        print "Command: $cmd\n";
        print "Directory: $cwd\n\n";
        exit 1;
    }
}

sub execCmd {
    local ($cmd) = @_;
    my $devnull = File::Spec->devnull();

    $cmd =~ tr|/|\\| if ($ENV{'OS'} =~ /Windows/i && 
                         !$ENV{'TERM'} =~ /cygwin/);

    if ($verbose) {
        print "\n$cmd \n";
        print `$cmd`;
    }
    else {
        print (".");
        my $_cmd = "$cmd > $devnull";
        $_cmd .= " 2> $devnull" if  $nostop;
        system($_cmd);
    }

    $rc = $?;
    if ($rc != 0) {
        if($verbose) { printf "FAIL\n"; }
        error($cmd);
        return 0;
    }
    if($verbose) { printf "OK\n"; }
    return 1;
}

sub execUnit {
   local ($cmd) = @_;
   my $devnull = File::Spec->devnull();

   if ($ENV{'OS'} =~ /Windows/i) {
      $cmd =~ s/\//\\/g unless ($ENV{'TERM'} =~ /cygwin/i);
   }

   #$cmd =~ tr|/|\\| if ($ENV{'OS'} =~ /Windows/i && !$ENV{'TERM'} =~ /cygwin/);

   my $_cmd = "$cmd > $devnull";
   $_cmd .= " 2> $devnull" if $nostop;

   system ($_cmd);
   $rc = $?;

   if ($rc != 0) {
      print ("F (${_cmd}) ");
      $nerror++;

      # run command again and print output to stdout
      print "$cmd\n";
      print `$cmd`;

      return 0;
   }
   else {
      print ("P");
   }

   return 1;
}

sub execCmdToLog {
    local ($cmd) = @_;

    print (".");

    $cmd =~ tr|/|\\| if ($ENV{'OS'} =~ /Windows/i && 
                         !$ENV{'TERM'} =~ /cygwin/);
    my $_cmd = "$cmd > temp.log 2>&1";
    if ($bredirectok) {
       system($_cmd);
       $rc = $?;
       if ($rc != 0) {
           #print("return code = $rc\n");
           error($cmd);
           return 0;
       }
       # check log file for memory leaks
       open (LOGFILE, "temp.log") || die ("could not open temp.log");
       my $printLines = 0;
       while (<LOGFILE>) {
           if (/Detected\smemory\sleaks/) {
               $printLines = 1;
           }
           if ($printLines) {
               print $_;
           }
       }
       close LOGFILE;
       unlink ('temp.log');
    }
    else {
       `$cmd`;
    }
    return 1;
}

sub execDiff {
    local ($cmd) = @_;
    my $out;
    
    if ($verbose) {
        print "\n$cmd ";
    } else {
        print (".");
    }
    $out = `$cmd`;
    if (length($out) > 0) {
        if($verbose) { printf "FAIL\n"; }
        error($cmd);
        return 0;
    }
    if($verbose) { printf "OK\n"; }
}

sub execClientServer {
    
    my $child_pid;
    my $server_rc;
    my $client_rc;
    my $server_cmd = "server";
    my $client_cmd = "client";
    if ($ENV{'OS'} =~ /Windows/i && !$ENV{'TERM'} =~ /cygwin/) {
        $client_cmd =~ tr|/|\\|; 
        $server_cmd =~ tr|/|\\|;
    }
    my $cmd = "server & client";
    if ($verbose) {
        print "\nCommand: $cmd\n";
    } else {
        print (".");
    }
    
    if (!defined($child_pid = fork())) {
        die "cannot fork: $!";
        
    } elsif ($child_pid) {
        
        # start server
        `$server_cmd`;
        $server_rc = $?;
        # wait for child to return
        waitpid($child_pid, 0);
        $client_rc = $?;
        
    } else {
        
        sleep 1; # give some time to the server
        # start the client
        `$client_cmd`;
        # exit with appropriate return code
        exit ($? != 0);
    } 
    
    if (($server_rc != 0) || ($client_rc != 0)) {
        error($cmd);
        return 0;
    }
    return 1;

}

# Same as the system command but the outputs of the command are suppressed
sub silent_system {
    
    my $cmd = shift;
    my $child_pid;
    
    # Work-around older File::Spec modules without devnull method.
    my $devnull = "";
    eval "use File::Spec;";
    eval { $devnull = File::Spec->devnull(); } unless $@;
    $devnull = "/dev/null" if $@;

    if ($ENV{'OS'} =~ /Windows/i) {
        # Fallback to shell redirection for windows
        my $_cmd = "$cmd > $devnull";
        $_cmd .= " 2> $devnull" if  $nostop;
        system($_cmd);
        return;
    }
    
    if (!defined($child_pid = fork()))
    {
        die "cannot fork: $!";
    }
    elsif ($child_pid)
    {
        # wait for child to return
        waitpid($child_pid, 0);
    }
    else
    {
        # silence command output 
        open STDOUT, ">$devnull" or die "Unable to open $devnull: $!";
        open STDERR, ">$devnull" or die "Unable to open $devnull: $!";
        # execute command
        exec($cmd) or die "Cannot execute command."
    } 
    
}
