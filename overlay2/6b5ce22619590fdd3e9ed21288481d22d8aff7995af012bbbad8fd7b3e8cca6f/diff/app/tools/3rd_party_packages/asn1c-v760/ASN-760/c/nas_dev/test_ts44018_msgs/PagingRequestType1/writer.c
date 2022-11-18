#include "TS44018Msgs.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300

TS44018Msg_PagingRequestType1*
    asn1Test_TS44018Msg_PagingRequestType1 (OSCTXT* pctxt)
{
   TS44018Msg_PagingRequestType1* pvalue = rtxMemAllocType (pctxt, TS44018Msg_PagingRequestType1);
   asn1Init_TS44018Msg_PagingRequestType1 (pvalue);

   pvalue->channelsNeededForMobiles1And2.channel_second = 2;

   pvalue->channelsNeededForMobiles1And2.channel_first = 2;

   pvalue->pageMode.spare_bit = 0;

   pvalue->pageMode.pm = 1;

   pvalue->mobileIdentity1.t =  1;
   rtxStrncpy (pvalue->mobileIdentity1.u.imsi, sizeof(pvalue->mobileIdentity1.u.imsi), "46688123456789", 15);

   pvalue->m.mobileIdentity2Present = 1;
   pvalue->mobileIdentity2.t =  1;
   rtxStrncpy (pvalue->mobileIdentity2.u.imsi, sizeof(pvalue->mobileIdentity2.u.imsi), "28401123456789", 15);
   return (pvalue);
}


TS44018IE_P1_Rest_Octets* asn1Test_TS44018IE_P1_Rest_Octets (OSCTXT* pctxt)
{
   TS44018IE_P1_Rest_Octets* pvalue = rtxMemAllocType (pctxt, TS44018IE_P1_Rest_Octets);
   asn1Init_TS44018IE_P1_Rest_Octets (pvalue);

   pvalue->m.component_1Present = 1;

   pvalue->component_1.nln_pch = 1;

   pvalue->component_1.nln_status_PCH = 0;

   pvalue->m.priority1Present = 1;
   pvalue->priority1 = 5;

   pvalue->m.priority2Present = 1;
   pvalue->priority2 = 5;

   pvalue->m.group_Call_informationPresent = 1;

   pvalue->group_Call_information.group_Call_Reference[0] = 0xf1;
   pvalue->group_Call_information.group_Call_Reference[1] = 0x5d;
   pvalue->group_Call_information.group_Call_Reference[2] = 0xcc;
   pvalue->group_Call_information.group_Call_Reference[3] = 0x5d;
   pvalue->group_Call_information.group_Call_Reference[4] = 0xdc;

   pvalue->group_Call_information.m.group_Channel_DescriptionPresent = 1;

   pvalue->group_Call_information.group_Channel_Description.channel_Description = 729644;

   pvalue->group_Call_information.group_Channel_Description.m.component_2Present = 1;
   pvalue->group_Call_information.group_Channel_Description.component_2.t =  1;

   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.length = 180;

   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.numbits = 1440;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[0] = 0x34;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[1] = 0x59;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[2] = 0x3b;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[3] = 0x4c;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[4] = 0x3f;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[5] = 0x72;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[6] = 0x6c;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[7] = 0x52;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[8] = 0x5c;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[9] = 0x5e;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[10] = 0x47;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[11] = 0x4e;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[12] = 0x51;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[13] = 0x31;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[14] = 0x41;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[15] = 0x71;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[16] = 0x73;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[17] = 0x75;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[18] = 0x60;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[19] = 0x3c;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[20] = 0x58;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[21] = 0x74;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[22] = 0x38;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[23] = 0x6a;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[24] = 0x41;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[25] = 0x40;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[26] = 0x3a;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[27] = 0x6f;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[28] = 0x51;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[29] = 0x45;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[30] = 0x45;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[31] = 0x61;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[32] = 0x6e;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[33] = 0x5c;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[34] = 0x43;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[35] = 0x37;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[36] = 0x58;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[37] = 0x3a;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[38] = 0x65;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[39] = 0x4a;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[40] = 0x74;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[41] = 0x42;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[42] = 0x74;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[43] = 0x5b;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[44] = 0x44;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[45] = 0x3f;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[46] = 0x56;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[47] = 0x41;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[48] = 0x3f;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[49] = 0x41;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[50] = 0x4d;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[51] = 0x73;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[52] = 0x3f;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[53] = 0x61;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[54] = 0x73;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[55] = 0x5c;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[56] = 0x38;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[57] = 0x38;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[58] = 0x55;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[59] = 0x59;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[60] = 0x59;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[61] = 0x30;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[62] = 0x50;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[63] = 0x51;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[64] = 0x5c;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[65] = 0x70;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[66] = 0x64;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[67] = 0x4a;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[68] = 0x34;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[69] = 0x5f;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[70] = 0x65;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[71] = 0x3e;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[72] = 0x72;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[73] = 0x63;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[74] = 0x69;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[75] = 0x4c;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[76] = 0x73;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[77] = 0x4a;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[78] = 0x69;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[79] = 0x48;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[80] = 0x67;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[81] = 0x4d;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[82] = 0x51;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[83] = 0x30;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[84] = 0x38;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[85] = 0x5a;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[86] = 0x68;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[87] = 0x40;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[88] = 0x62;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[89] = 0x53;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[90] = 0x75;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[91] = 0x51;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[92] = 0x5f;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[93] = 0x50;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[94] = 0x38;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[95] = 0x45;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[96] = 0x4a;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[97] = 0x6c;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[98] = 0x6b;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[99] = 0x5a;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[100] = 0x62;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[101] = 0x5a;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[102] = 0x68;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[103] = 0x6a;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[104] = 0x54;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[105] = 0x5b;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[106] = 0x40;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[107] = 0x5d;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[108] = 0x3b;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[109] = 0x33;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[110] = 0x3b;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[111] = 0x72;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[112] = 0x50;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[113] = 0x5c;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[114] = 0x38;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[115] = 0x65;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[116] = 0x4c;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[117] = 0x36;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[118] = 0x75;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[119] = 0x45;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[120] = 0x59;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[121] = 0x75;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[122] = 0x66;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[123] = 0x42;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[124] = 0x4f;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[125] = 0x6f;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[126] = 0x63;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[127] = 0x75;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[128] = 0x71;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[129] = 0x59;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[130] = 0x59;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[131] = 0x5d;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[132] = 0x49;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[133] = 0x57;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[134] = 0x51;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[135] = 0x6d;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[136] = 0x3c;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[137] = 0x6d;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[138] = 0x60;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[139] = 0x54;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[140] = 0x71;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[141] = 0x6b;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[142] = 0x50;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[143] = 0x57;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[144] = 0x5d;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[145] = 0x65;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[146] = 0x52;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[147] = 0x34;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[148] = 0x6b;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[149] = 0x52;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[150] = 0x49;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[151] = 0x4f;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[152] = 0x5d;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[153] = 0x45;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[154] = 0x6d;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[155] = 0x42;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[156] = 0x3e;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[157] = 0x5b;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[158] = 0x41;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[159] = 0x3a;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[160] = 0x4a;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[161] = 0x30;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[162] = 0x73;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[163] = 0x63;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[164] = 0x57;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[165] = 0x4f;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[166] = 0x67;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[167] = 0x6f;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[168] = 0x52;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[169] = 0x5d;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[170] = 0x4d;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[171] = 0x59;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[172] = 0x53;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[173] = 0x34;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[174] = 0x3b;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[175] = 0x46;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[176] = 0x69;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[177] = 0x69;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[178] = 0x56;
   pvalue->group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[179] = 0x5e;

   pvalue->m.packet_Page_Indication_1Present = 1;
   pvalue->packet_Page_Indication_1 = TS44018IE_LHType_lbit;

   pvalue->m.packet_Page_Indication_2Present = 1;
   pvalue->packet_Page_Indication_2 = TS44018IE_LHType_lbit;

   pvalue->m.component_7Present = 1;

   pvalue->component_7.m.component_1Present = 1;
   pvalue->component_7.component_1.t =  3;

   pvalue->component_7.component_1.u.choice_3.reduced_GCR = 33952516;

   pvalue->component_7.component_1.u.choice_3.vstk_rand[0] = 0x6d;
   pvalue->component_7.component_1.u.choice_3.vstk_rand[1] = 0xa1;
   pvalue->component_7.component_1.u.choice_3.vstk_rand[2] = 0x2e;
   pvalue->component_7.component_1.u.choice_3.vstk_rand[3] = 0x17;
   pvalue->component_7.component_1.u.choice_3.vstk_rand[4] = 0x63;

   pvalue->component_7.m.component_2Present = 1;

   pvalue->component_7.component_2.m.mbms_Notification_1Present = 1;
   pvalue->component_7.component_2.mbms_Notification_1.t =  1;

   pvalue->component_7.component_2.mbms_Notification_1.u.choice_1.m.component_1Present = 1;

   pvalue->component_7.component_2.mbms_Notification_1.u.choice_1.component_1.mbms_p_t_m_channel_description.m.frequency_ParametersPresent = 1;

   pvalue->component_7.component_2.mbms_Notification_1.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.tsc = 6;

   pvalue->component_7.component_2.mbms_Notification_1.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.t =  2;

   pvalue->component_7.component_2.mbms_Notification_1.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.indirect_encoding.maio = 19;

   pvalue->component_7.component_2.mbms_Notification_1.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.indirect_encoding.ma_number = 10;

   pvalue->component_7.component_2.mbms_Notification_1.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.indirect_encoding.m.component_3Present = 1;

   pvalue->component_7.component_2.mbms_Notification_1.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.indirect_encoding.component_3.change_mark_1 = 0;

   pvalue->component_7.component_2.mbms_Notification_1.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.indirect_encoding.component_3.m.change_mark_2Present = 1;
   pvalue->component_7.component_2.mbms_Notification_1.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.indirect_encoding.component_3.change_mark_2 = 2;

   pvalue->component_7.component_2.mbms_Notification_1.u.choice_1.component_1.mbms_p_t_m_channel_description.dl_timeslot_allocation = 97;

   /* zero elements */

   pvalue->component_7.component_2.m.mbms_Notification_2Present = 1;

   pvalue->component_7.component_2.mbms_Notification_2.m.mbms_Channel_Parameters_IEPresent = 1;
   pvalue->component_7.component_2.mbms_Notification_2.mbms_Channel_Parameters_IE.t =  1;

   pvalue->component_7.component_2.mbms_Notification_2.mbms_Channel_Parameters_IE.u.choice_1.m.component_1Present = 1;

   pvalue->component_7.component_2.mbms_Notification_2.mbms_Channel_Parameters_IE.u.choice_1.component_1.mbms_p_t_m_channel_description.m.frequency_ParametersPresent = 1;

   pvalue->component_7.component_2.mbms_Notification_2.mbms_Channel_Parameters_IE.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.tsc = 4;

   pvalue->component_7.component_2.mbms_Notification_2.mbms_Channel_Parameters_IE.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.t =  2;

   pvalue->component_7.component_2.mbms_Notification_2.mbms_Channel_Parameters_IE.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.indirect_encoding.maio = 50;

   pvalue->component_7.component_2.mbms_Notification_2.mbms_Channel_Parameters_IE.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.indirect_encoding.ma_number = 7;

   pvalue->component_7.component_2.mbms_Notification_2.mbms_Channel_Parameters_IE.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.indirect_encoding.m.component_3Present = 1;

   pvalue->component_7.component_2.mbms_Notification_2.mbms_Channel_Parameters_IE.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.indirect_encoding.component_3.change_mark_1 = 2;

   pvalue->component_7.component_2.mbms_Notification_2.mbms_Channel_Parameters_IE.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.indirect_encoding.component_3.m.change_mark_2Present = 1;
   pvalue->component_7.component_2.mbms_Notification_2.mbms_Channel_Parameters_IE.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.indirect_encoding.component_3.change_mark_2 = 0;

   pvalue->component_7.component_2.mbms_Notification_2.mbms_Channel_Parameters_IE.u.choice_1.component_1.mbms_p_t_m_channel_description.dl_timeslot_allocation = 223;

   /* zero elements */

   pvalue->component_7.component_2.m.mbms_InformationPresent = 1;

   /* zero elements */

   pvalue->component_7.component_2.mbms_Information.m.component_2Present = 1;

   pvalue->component_7.component_2.mbms_Information.component_2.same_as_notification_flag = 0;

   /* zero elements */

   /* zero elements */

   pvalue->m.component_8Present = 1;

   pvalue->component_8.m.amr_ConfigPresent = 1;
   pvalue->component_8.amr_Config = 4;

   pvalue->m.component_9Present = 1;

   pvalue->component_9.priority_Uplink_Access = 0;

   pvalue->component_9.m.etws_Primary_NotificationPresent = 1;

   pvalue->component_9.etws_Primary_Notification.component_1.t =  1;
   pvalue->component_9.etws_Primary_Notification.component_1.u.total_No_Of_Segments_For_ETWS_Primary_Notification = 4;

   pvalue->component_9.etws_Primary_Notification.pni = 0;

   pvalue->component_9.etws_Primary_Notification.length_Of_Segment = 5;

   pvalue->component_9.etws_Primary_Notification.etws_Primary_Notification_Data.numbits = 5;
   pvalue->component_9.etws_Primary_Notification.etws_Primary_Notification_Data.data[0] = 0x42;

   pvalue->m.component_10Present = 1;

   pvalue->component_10.implicit_Reject_CS = 0;

   pvalue->component_10.implicit_Reject_PS = 0;

   pvalue->m.ipa_SupportPresent = 1;
   pvalue->ipa_Support = 0;
   return (pvalue);
}


int main (int argc, char** argv)
{
   TS44018Msg_L2_PSEUDO_LEN_PDU pdu;

   OSCTXT	ctxt;
   OSCTXT*  pctxt = &ctxt;
   OSOCTET	msgbuf[MAXMSGLEN], *msgptr;
   const char*  filename = "message.dat";
   OSSIZE       len;
   int		i, ret;
   OSBOOL       verbose = FALSE;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else {
            printf ("usage: writer [-v]\n");
            printf ("   -v  verbose mode: print trace info\n");
            return 0;
         }
      }
   }

   /* Initialize context structure */

   ret = rtInitContext (&ctxt);
   if (0 != ret) {
      printf ("rtInitContext failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
      return ret;
   }
   rtxSetDiag (&ctxt, verbose);

   /* Populate data structure */

   asn1Init_TS44018Msg_L2_PSEUDO_LEN_PDU (&pdu);
   pdu.l3HdrOpts.t = 1;
   pdu.l3HdrOpts.u.skipInd = 0;
   pdu.protoDiscr = TS24007L3_ProtoDiscr_rrMgmt;
   pdu.msgType = ASN1V_ts44018Msg_mt_PagingRequestType1;
   pdu.data.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_PagingRequestType1;
   pdu.data.u.obj_PagingRequestType1 =
      asn1Test_TS44018Msg_PagingRequestType1(pctxt);

   pdu.restOctets.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_PagingRequestType1;
   pdu.restOctets.u.obj_PagingRequestType1 =
      asn1Test_TS44018IE_P1_Rest_Octets(pctxt);


   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018Msg_L2_PSEUDO_LEN_PDU (&ctxt, &pdu);
   if (0 != ret) {
      printf ("encode PDU failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
      return ret;
   }
   /* Verify buffer is byte-aligned */
   OSRTASSERT (ctxt.buffer.bitOffset == 8 || ctxt.buffer.bitOffset == 0);

   msgptr = rtxCtxtGetMsgPtr (&ctxt);
   len = rtxCtxtGetMsgLen (&ctxt);


   if (verbose) {
      printf ("Encoding was successful\n");
      printf ("Hex dump of encoded record:\n");
      rtxHexDump (msgptr, len);
      printf ("\n");
      printf ("Bit fields:\n");
      rtxDiagBitTracePrint (ctxt.pBitFldList, "");
      printf ("\n");
   }

   /* Write encoded message to output file */

   ret = rtxFileWriteBinary (filename, msgptr, len);
   if (0 != ret) {
      printf ("rtxFileWriteBinary failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
      return ret;
   }

   rtxFreeContext (&ctxt);

   return 0;
}
