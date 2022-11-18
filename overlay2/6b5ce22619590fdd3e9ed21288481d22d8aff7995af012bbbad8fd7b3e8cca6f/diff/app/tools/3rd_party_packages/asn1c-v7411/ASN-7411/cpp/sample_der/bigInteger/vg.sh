valgrind --leak-check=full ../../../bin/asn1c bigInt.asn -c++ -der -print print.cpp -config bigInt.cfg -cfile BigInt.cpp
