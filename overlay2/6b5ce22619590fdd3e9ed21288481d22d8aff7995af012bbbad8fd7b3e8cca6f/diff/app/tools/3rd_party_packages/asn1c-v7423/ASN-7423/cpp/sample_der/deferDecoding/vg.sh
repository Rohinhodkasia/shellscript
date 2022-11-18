valgrind --leak-check=full ../../../bin/asn1c Test.asn -c++ -der -trace -print TestPrint.cpp -config Test.cfg -noencode -cfile Test.cpp
