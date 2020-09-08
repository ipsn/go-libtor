#if defined(ARCH_LINUX64) || defined(ARCH_ANDROID64) || defined(ARCH_DARWIN64)
  #include "crypto/bn_conf.x64.h"
#endif

#if defined(ARCH_LINUX32) || defined(ARCH_ANDROID32) || defined(ARCH_DARWIN32)
  #include "crypto/bn_conf.x86.h"
#endif
