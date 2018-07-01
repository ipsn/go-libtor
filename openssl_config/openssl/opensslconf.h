#if defined(ARCH_LINUX64) || defined(ARCH_ANDROID64)
  #include "openssl/opensslconf.x64.h"
#endif

#if defined(ARCH_LINUX32) || defined(ARCH_ANDROID32)
  #include "openssl/opensslconf.x86.h"
#endif
