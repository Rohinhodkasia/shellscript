import sys
sys.path.append('../../..')

from osyspyrt.asn1ber import Asn1BerDecodeContext
from osyspyrt.asn1error import Asn1MissingRequiredError
from osyspyrt.asn1univtype import Asn1Type
from osyspyrt.strutil import openBrace


class Dss_Parms(Asn1Type):
    """Populate the following member variables for this class
    p = int
    q = int
    g = int
    """

    def ber_encode(self, encbuf, explicit=True):
        aal = 0

        # encode g
        if not hasattr(self, "g"):
            raise Asn1MissingRequiredError("g")

        aal += encbuf.encode_integer(self.g)

        # encode q
        if not hasattr(self, "q"):
            raise Asn1MissingRequiredError("q")

        aal += encbuf.encode_integer(self.q)

        # encode p
        if not hasattr(self, "p"):
            raise Asn1MissingRequiredError("p")

        aal += encbuf.encode_integer(self.p)

        # encode tag and length
        if explicit:
            llen = encbuf.encode_def_len(aal)
            encbuf.buffer = bytes([0x30]) + encbuf.buffer
            aal += llen + 1

        return aal

    def ber_decode(self, decbuf, explicit=True, impllen=None):
        if explicit:
            assert(decbuf.match_tag_byte(0x30)), "SEQUENCE tag match failed"
            llen = decbuf.decode_length()
        else:
            llen = impllen

        # decode SEQUENCE

        decctxt = Asn1BerDecodeContext(decbuf, llen)

        # decode p

        elemlen = decctxt.match_elem_tag(b'\x02')
        if elemlen is not None:
            self.p = decbuf.decode_integer(False, elemlen)
        else:
            raise Asn1MissingRequiredError("p")

        # decode q

        elemlen = decctxt.match_elem_tag(b'\x02')
        if elemlen is not None:
            self.q = decbuf.decode_integer(False, elemlen)
        else:
            raise Asn1MissingRequiredError("q")

        # decode g

        elemlen = decctxt.match_elem_tag(b'\x02')
        if elemlen is not None:
            self.g = decbuf.decode_integer(False, elemlen)
        else:
            raise Asn1MissingRequiredError("g")

        return self

    def to_string(self, elemName, indent):
        s, indstr = openBrace(elemName, indent)
        s += "%s  p = %d\n" % (indstr, self.p)
        s += "%s  q = %d\n" % (indstr, self.q)
        s += "%s  g = %d\n" % (indstr, self.g)
        s += "%s}\n" % indstr
        return s

    def print_value(self, elemName="Dss_Parms", indent=0):
        print(self.to_string(elemName, indent))
