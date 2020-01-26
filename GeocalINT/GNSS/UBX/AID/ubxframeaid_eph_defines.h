#ifndef UBXFRAMEAID_EPH_DEFINES_H
#define UBXFRAMEAID_EPH_DEFINES_H

#include <cstdint>
#include <cmath>
#include <Utils/mathphy.h>

namespace GNSS
{
constexpr   int POS_SVID = 0;
constexpr   int POS_HOW = 4;

constexpr   int WEEKTIME_BIT_SIZE = 10;
constexpr   int WEEKTIME_BIT_OFFSET = 14;

constexpr   int L2CODE_BIT_SIZE = 2;
constexpr   int L2CODE_BIT_OFFSET = 12;

constexpr   int URA_BIT_SIZE = 4;
constexpr   int URA_BIT_OFFSET = 8;

constexpr   int SVH_BIT_SIZE = 6;
constexpr   int SVH_BIT_OFFSET = 2;

constexpr   int IOCDMSB_BIT_SIZE = 2;
constexpr   int IODCMSB_BIT_OFFSET = 0;

constexpr   int IOCDLSB_BIT_SIZE = 8;
constexpr   int IOCDLSB_BIT_OFFSET = 16;

constexpr   int TGD_BIT_SIZE = 8;
constexpr   int TGD_BIT_OFFSET = 0;

constexpr   int TOC_BIT_SIZE = 16;
constexpr   int TOC_BIT_OFFSET = 0;

constexpr   int F0_BIT_SIZE = 22;
constexpr   int F0_BIT_OFFSET = 2;
constexpr  int32_t F0_32SIGNED_MASK = (int32_t)0xFFC00000;

constexpr   int F1_BIT_SIZE = 16;
constexpr   int F1_BIT_OFFSET = 0;

constexpr   int F2_BIT_SIZE = 8;
constexpr   int F2_BIT_OFFSET = 16;

constexpr   int IODE_BIT_SIZE = 8;
constexpr   int IODE_BIT_OFFSET = 16;

constexpr   int CRS_BIT_SIZE = 16;
constexpr   int CRS_BIT_OFFSET = 0;
constexpr   double CRS_SCALE_FACTOR = cpow(2,-5);   //meters

constexpr   int DN_BIT_SIZE = 16;
constexpr   int DN_BIT_OFFSET = 8;
constexpr   double DN_SCALE_FACTOR = cpow(2,-43);   //semi-circles/sec

constexpr   int M0MSB_BIT_SIZE = 8;
constexpr   int M0MSB_BIT_OFFSET = 0;

constexpr   int M0LSB_BIT_SIZE = 24;
constexpr   int M0LSB_BIT_OFFSET = 0;
constexpr   double M0_SCALE_FACTOR = cpow(2,-31);   //semi-circles

constexpr   int CUC_BIT_SIZE = 16;
constexpr   int CUC_BIT_OFFSET = 8;
constexpr   double CUC_SCALE_FACTOR = cpow(2,29);   //radians

constexpr   int EMSB_BIT_SIZE = 8;
constexpr   int EMSB_BIT_OFFSET = 0;

constexpr   int ELSB_BIT_SIZE  =24;
constexpr   int ELSB_BIT_OFFSET = 0;
constexpr   double E_SCALE_FACTOR = cpow(2,-33);    //none

constexpr   int CUS_BIT_SIZE = 16;
constexpr   int CUS_BIT_OFFSET = 8;
constexpr   double CUS_SCALE_FACTOR = cpow(2,-29);  //radians

constexpr   int SQRTAMSB_BIT_SIZE = 8;
constexpr   int SQRTAMSB_BIT_OFFSET = 0;
constexpr   double SQRTA_SCALE_FACTOR = cpow(2,-19);    //sqrt meters

constexpr   int SQRTALSB_BIT_SIZE = 24;
constexpr   int SQRTALSB_BIT_OFFSET = 0;

constexpr   int TOE_BIT_SIZE = 16;
constexpr   int TOE_BIT_OFFSET = 8;
constexpr   double TOE_SCALE_FACTOR = cpow(2,4);    //seconds

constexpr   int FIT_BIT_SIZE = 1;
constexpr   int FIT_BIT_OFFSET = 7;

constexpr   int AODO_BIT_SIZE = 5;
constexpr   int AODO_BIT_OFFSET = 2;

constexpr   int CIC_BIT_SIZE = 16;
constexpr   int CIC_BIT_OFFSET = 8;
constexpr   double CIC_SCALE_FACTOR = cpow(2,-39);  //radians

constexpr   int OMEGA0MSB_BIT_SIZE = 8;
constexpr   int OMEGA0MSB_BIT_OFFSET = 0;

constexpr   int OMEGA0LSB_BIT_SIZE = 24;
constexpr   int OMEGA0LSB_BIT_OFFSET = 0;
constexpr   double OMEGA0_SCALE_FACTOR = cpow(2,-31);   //semi-circles

constexpr   int CIS_BIT_SIZE = 16;
constexpr   int CIS_BIT_OFFSET = 8;
constexpr   double CIS_SCALE_FACTOR = cpow(2,-29);  //radians

constexpr   int I0MSB_BIT_SIZE = 8;
constexpr   int I0MSB_BIT_OFFSET = 0;

constexpr   int I0LSB_BIT_SIZE = 24;
constexpr   int I0LSB_BIT_OFFSET = 0;
constexpr   double I0_SCALE_FACTOR = cpow(2,-31);   //semi-circles

constexpr   int CRC_BIT_SIZE = 16;
constexpr   int CRC_BIT_OFFSET = 8;
constexpr   double CRC_SCALE_FACTOR = cpow(2,-5);   //meters

constexpr   int OMEGAMSB_BIT_SIZE = 8;
constexpr   int OMEGAMSB_BIT_OFFSET = 0;

constexpr   int OMEGALSB_BIT_SIZE = 24;
constexpr   int OMEGALSB_BIT_OFFSET = 0;
constexpr   double OMEGA_SCALE_FACTOR = cpow(2,-31);    // semi-circles

constexpr   int OMEGAP_BIT_SIZE = 24;
constexpr   int OMEGAP_BIT_OFFSET = 0;
constexpr   int32_t  OMEGAP_32SIGNED_MASK = (int32_t)0xFF000000;
constexpr   double OMEGAP_SCALE_FACTOR = cpow(2,-43);   //semi-circles/sec

constexpr   int IDOT_BIT_SIZE = 14;
constexpr   int IDOT_BIT_OFFSET = 2;
constexpr   double IDOT_SCALE_FACTOR = cpow(2,-43);
constexpr   int16_t IDOT_16SIGNED_MASK = (int16_t)0xC000;

}

#endif // UBXFRAMEAID_EPH_DEFINES_H
