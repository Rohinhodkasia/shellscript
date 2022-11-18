valgrind --leak-check=full ../../../bin/asn1c TAP-0311.asn -c++ -ber -stream -print print.cpp -config tap3.cfg -geninit -pdu "*" -noopenext
