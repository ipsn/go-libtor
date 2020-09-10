#if defined(ARCH_LINUX64) || defined(ARCH_ANDROID64) || defined(ARCH_LINUX32) || defined(ARCH_ANDROID32)
  #include "dso_conf.linux.h"
#endif

#ifdef ARCH_DARWIN64
  #include "dso_conf.darwin.h"
#endif
