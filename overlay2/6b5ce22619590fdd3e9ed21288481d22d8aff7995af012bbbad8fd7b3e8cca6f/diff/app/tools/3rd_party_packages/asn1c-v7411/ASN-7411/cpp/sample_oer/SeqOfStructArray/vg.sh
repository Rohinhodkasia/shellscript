valgrind --leak-check=full ../../../bin/asn1c test.asn -cpp -oer -print -array -arraySize 10 -test -trace -fqtvalue
