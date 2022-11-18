my $makeprog = getMakeProg();

print `$makeprog`;

if (-e "writer.exe" || -e "writer") {
    `writer > writer.log 2>&1`;

    if (-e 'writer.log' && -e './good/writer.log') {
        print `diff writer.log ./good/writer.log`;
    }
}

sub getMakeProg {
    my $makeprog = "make";
    if (defined ($ENV{'MAKEPROG'})) {
        $makeprog = $ENV{'MAKEPROG'};
    }
    elsif (defined ($ENV{'MSVCDIR'}) || 
           defined ($ENV{'MSDEVDIR'}) ||
           defined ($ENV{'MSDevDir'})) {
        $makeprog = "nmake -nologo";
    }
    else {
        $makeprog = "make";
    }
    return $makeprog;
}
