all : outdirs
	cd src; $(MAKE)
	cd src2; perl mkdepend.pl
	cd ./debug/build; $(MAKE)
	cd ./release/build; $(MAKE)

outdirs :
	perl -e "mkdir ('./debug/lib', 0777) if (! -e './debug/lib')"
	perl -e "mkdir ('./release/lib', 0777) if (! -e './release/lib')"

clean:
	cd src; $(MAKE) clean
	cd ./debug/build; $(MAKE) clean
	cd ./release/build; $(MAKE) clean
