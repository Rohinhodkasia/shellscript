valgrind --leak-check=full ../../../bin/asn1c test.asn -c++ -ber -print print.cpp -cfile TimeString.cpp -pdu "*"
