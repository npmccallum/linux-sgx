#include "ippcp.h"

#define IPPFUN(type,name,arg) extern type IPP_STDCALL name arg

#ifndef NULL
#ifdef  __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#if defined (_M_AMD64) || defined (__x86_64__)

#define AVX3X_FEATURES ( ippCPUID_AVX512F|ippCPUID_AVX512CD|ippCPUID_AVX512VL|ippCPUID_AVX512BW|ippCPUID_AVX512DQ )
#define AVX3M_FEATURES ( ippCPUID_AVX512F|ippCPUID_AVX512CD|ippCPUID_AVX512PF|ippCPUID_AVX512ER )


IPPAPI(IppStatus, y8_ippsECCPSetPointAtInfinity,(IppsECCPPointState* pPoint, IppsECCPState* pECC))
IPPAPI(IppStatus, l9_ippsECCPSetPointAtInfinity,(IppsECCPPointState* pPoint, IppsECCPState* pECC))

IPPFUN(IppStatus,sgx_disp_ippsECCPSetPointAtInfinity,(IppsECCPPointState* pPoint, IppsECCPState* pECC))
{
  Ipp64u features;
  ippcpGetCpuFeatures( &features );

      if( ippCPUID_AVX2  == ( features & ippCPUID_AVX2  )) { /* HasweLl ia32=H9, x64=L9 */
        return l9_ippsECCPSetPointAtInfinity( pPoint, pECC );
      } else 
      if( ippCPUID_SSE42 == ( features & ippCPUID_SSE42 )) { /* Nehalem or Westmer = PenrYn + SSE42 + ?CLMUL + ?AES + ?SHA */
        return y8_ippsECCPSetPointAtInfinity( pPoint, pECC );
      } else 
        return ippStsCpuNotSupportedErr;
}
#else


IPPAPI(IppStatus, p8_ippsECCPSetPointAtInfinity,(IppsECCPPointState* pPoint, IppsECCPState* pECC))
IPPAPI(IppStatus, h9_ippsECCPSetPointAtInfinity,(IppsECCPPointState* pPoint, IppsECCPState* pECC))

IPPFUN(IppStatus,sgx_disp_ippsECCPSetPointAtInfinity,(IppsECCPPointState* pPoint, IppsECCPState* pECC))
{
  Ipp64u features;
  ippcpGetCpuFeatures( &features );

      if( ippCPUID_AVX2  == ( features & ippCPUID_AVX2  )) { /* HasweLl ia32=H9, x64=L9 */
        return h9_ippsECCPSetPointAtInfinity( pPoint, pECC );
      } else 
      if( ippCPUID_SSE42 == ( features & ippCPUID_SSE42 )) { /* Nehalem or Westmer = PenrYn + SSE42 + ?CLMUL + ?AES + ?SHA */
        return p8_ippsECCPSetPointAtInfinity( pPoint, pECC );
      } else 
        return ippStsCpuNotSupportedErr;
}
#endif
