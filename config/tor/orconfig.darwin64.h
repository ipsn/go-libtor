/* orconfig.h.  Generated from orconfig.h.in by configure.  */
/* orconfig.h.in.  Generated from configure.ac by autoheader.  */

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* tor's build directory */
#define BUILDDIR ""

/* tor's configuration directory */
#define CONFDIR ""

#define SHARE_DATADIR ""

#define LOCALSTATEDIR ""

/* Enable smartlist debugging */
/* #undef DEBUG_SMARTLIST */

/* Defined if we're turning off memory safety code to look for bugs */
/* #undef DISABLE_MEMORY_SENTINELS */

/* Defined if we're not going to look for a torrc in SYSCONF */
/* #undef DISABLE_SYSTEM_TORRC */

/* Define to 1 iff memset(0) sets doubles to 0.0 */
#define DOUBLE_0_REP_IS_ZERO_BYTES 1

/* Defined if we default to host local appdata paths on Windows */
/* #undef ENABLE_LOCAL_APPDATA */

/* Defined if we're building with NSS. */
/* #undef ENABLE_NSS */

/* Defined if we're building with OpenSSL or LibreSSL */
#define ENABLE_OPENSSL 1

/* Defined if we're building with support for in-process restart debugging. */
/* #undef ENABLE_RESTART_DEBUGGING */

/* Defined if we're going to try to use zstd's "static-only" APIs. */
#define ENABLE_ZSTD_ADVANCED_APIS 1

/* Define if enum is always signed */
/* #undef ENUM_VALS_ARE_SIGNED */

/* Define to nothing if C supports flexible array members, and to 1 if it does
   not. That way, with a declaration like `struct s { int n; double
   d[FLEXIBLE_ARRAY_MEMBER]; };', the struct hack can be used with pre-C99
   compilers. When computing the size of such an object, don't use 'sizeof
   (struct s)' as it overestimates the size. Use 'offsetof (struct s, d)'
   instead. Don't use 'offsetof (struct s, d[0])', as this doesn't work with
   MSVC and with C++ compilers. */
#define FLEXIBLE_ARRAY_MEMBER /**/

/* Define to 1 if you have the `accept4' function. */
/* #undef HAVE_ACCEPT4 */

/* Define to 1 if you have the <android/log.h> header file. */
/* #undef HAVE_ANDROID_LOG_H */

/* Define to 1 if you have the <arpa/inet.h> header file. */
#define HAVE_ARPA_INET_H 1

/* defined if we have the fallthrough attribute. */
/* #undef HAVE_ATTR_FALLTHROUGH */

/* Define to 1 if you have the `backtrace' function. */
#define HAVE_BACKTRACE 1

/* Define to 1 if you have the `backtrace_symbols_fd' function. */
#define HAVE_BACKTRACE_SYMBOLS_FD 1

/* Define to 1 if you have the `cap_set_proc' function. */
/* #undef HAVE_CAP_SET_PROC */

/* True if we have -Wnull-dereference */
#define HAVE_CFLAG_WNULL_DEREFERENCE 1

/* True if we have -Woverlength-strings */
#define HAVE_CFLAG_WOVERLENGTH_STRINGS 1

/* True if we have -Wunused-const-variable */
/* #undef HAVE_CFLAG_WUNUSED_CONST_VARIABLE */

/* Define to 1 if you have the `clock_gettime' function. */
#define HAVE_CLOCK_GETTIME 1

/* Define to 1 if you have the <crt_externs.h> header file. */
#define HAVE_CRT_EXTERNS_H 1

/* Define to 1 if you have the <crypto_scalarmult_curve25519.h> header file.
   */
/* #undef HAVE_CRYPTO_SCALARMULT_CURVE25519_H */

/* Define to 1 if you have the <cygwin/signal.h> header file. */
/* #undef HAVE_CYGWIN_SIGNAL_H */

/* Define to 1 if you have the declaration of `mlockall', and to 0 if you
   don't. */
#define HAVE_DECL_MLOCKALL 1

/* Define to 1 if you have the declaration of `SecureZeroMemory', and to 0 if
   you don't. */
/* #undef HAVE_DECL_SECUREZEROMEMORY */

/* Define to 1 if you have the declaration of `_getwch', and to 0 if you
   don't. */
/* #undef HAVE_DECL__GETWCH */

/* Define to 1 if you have the <errno.h> header file. */
#define HAVE_ERRNO_H 1

/* Define to 1 if you have the `ERR_load_KDF_strings' function. */
#define HAVE_ERR_LOAD_KDF_STRINGS 1

/* Define to 1 if you have the <event2/bufferevent_ssl.h> header file. */
#define HAVE_EVENT2_BUFFEREVENT_SSL_H 1

/* Define to 1 if you have the <event2/dns.h> header file. */
#define HAVE_EVENT2_DNS_H 1

/* Define to 1 if you have the <event2/event.h> header file. */
#define HAVE_EVENT2_EVENT_H 1

/* Define to 1 if you have the `eventfd' function. */
/* #undef HAVE_EVENTFD */

/* Define to 1 if you have the `EVP_PBE_scrypt' function. */
#define HAVE_EVP_PBE_SCRYPT 1

/* Define to 1 if you have the `evutil_secure_rng_add_bytes' function. */
#define HAVE_EVUTIL_SECURE_RNG_ADD_BYTES 1

/* Define to 1 if you have the `evutil_secure_rng_set_urandom_device_file'
   function. */
#define HAVE_EVUTIL_SECURE_RNG_SET_URANDOM_DEVICE_FILE 1

/* Define to 1 if you have the <execinfo.h> header file. */
#define HAVE_EXECINFO_H 1

/* Define to 1 if you have the `explicit_bzero' function. */
/* #undef HAVE_EXPLICIT_BZERO */

/* Defined if we have extern char **environ already declared */
/* #undef HAVE_EXTERN_ENVIRON_DECLARED */

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define to 1 if you have the `flock' function. */
#define HAVE_FLOCK 1

/* Define to 1 if you have the `ftime' function. */
#define HAVE_FTIME 1

/* Define to 1 if you have the `getaddrinfo' function. */
#define HAVE_GETADDRINFO 1

/* Define to 1 if you have the `getdelim' function. */
#define HAVE_GETDELIM 1

/* Define to 1 if you have the `getentropy' function. */
#define HAVE_GETENTROPY 1

/* Define this if you have any gethostbyname_r() */
/* #undef HAVE_GETHOSTBYNAME_R */

/* Define this if gethostbyname_r takes 3 arguments */
/* #undef HAVE_GETHOSTBYNAME_R_3_ARG */

/* Define this if gethostbyname_r takes 5 arguments */
/* #undef HAVE_GETHOSTBYNAME_R_5_ARG */

/* Define this if gethostbyname_r takes 6 arguments */
/* #undef HAVE_GETHOSTBYNAME_R_6_ARG */

/* Define to 1 if you have the `getifaddrs' function. */
#define HAVE_GETIFADDRS 1

/* Define to 1 if you have the `getline' function. */
#define HAVE_GETLINE 1

/* Define to 1 if you have the `getpass' function. */
#define HAVE_GETPASS 1

/* Define to 1 if you have the `getresgid' function. */
/* #undef HAVE_GETRESGID */

/* Define to 1 if you have the `getresuid' function. */
/* #undef HAVE_GETRESUID */

/* Define to 1 if you have the `getrlimit' function. */
#define HAVE_GETRLIMIT 1

/* Define to 1 if you have the `gettimeofday' function. */
#define HAVE_GETTIMEOFDAY 1

/* Define to 1 if you have the `get_current_dir_name' function. */
/* #undef HAVE_GET_CURRENT_DIR_NAME */

/* Define to 1 if you have the `gmtime_r' function. */
#define HAVE_GMTIME_R 1

/* Define to 1 if you have the `gnu_get_libc_version' function. */
/* #undef HAVE_GNU_GET_LIBC_VERSION */

/* Define to 1 if you have the <gnu/libc-version.h> header file. */
/* #undef HAVE_GNU_LIBC_VERSION_H */

/* Define to 1 if you have the <grp.h> header file. */
#define HAVE_GRP_H 1

/* Define to 1 if you have the `htonll' function. */
/* #undef HAVE_HTONLL */

/* Define to 1 if you have the <ifaddrs.h> header file. */
#define HAVE_IFADDRS_H 1

/* Define to 1 if you have the `inet_aton' function. */
#define HAVE_INET_ATON 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the `ioctl' function. */
#define HAVE_IOCTL 1

/* Define to 1 if you have the `issetugid' function. */
#define HAVE_ISSETUGID 1

/* Defined if KIST scheduler is supported on this system */
/* #undef HAVE_KIST_SUPPORT */

/* Define to 1 if you have the `cap' library (-lcap). */
/* #undef HAVE_LIBCAP */

/* Define to 1 if you have the <libscrypt.h> header file. */
/* #undef HAVE_LIBSCRYPT_H */

/* Define to 1 if you have the `libscrypt_scrypt' function. */
/* #undef HAVE_LIBSCRYPT_SCRYPT */

/* Define to 1 if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define to 1 if you have the <linux/if.h> header file. */
/* #undef HAVE_LINUX_IF_H */

/* Define to 1 if you have the <linux/netfilter_ipv4.h> header file. */
/* #undef HAVE_LINUX_NETFILTER_IPV4_H */

/* Define to 1 if you have the <linux/netfilter_ipv6/ip6_tables.h> header
   file. */
/* #undef HAVE_LINUX_NETFILTER_IPV6_IP6_TABLES_H */

/* Define to 1 if you have the <linux/types.h> header file. */
/* #undef HAVE_LINUX_TYPES_H */

/* Define to 1 if you have the `llround' function. */
#define HAVE_LLROUND 1

/* Define to 1 if you have the `localtime_r' function. */
#define HAVE_LOCALTIME_R 1

/* Define to 1 if you have the `lround' function. */
#define HAVE_LROUND 1

/* Have LZMA */
/* #undef HAVE_LZMA */

/* Define to 1 if you have the <machine/limits.h> header file. */
#define HAVE_MACHINE_LIMITS_H 1

/* Define to 1 if you have the `mach_approximate_time' function. */
#define HAVE_MACH_APPROXIMATE_TIME 1

/* Defined if the compiler supports __FUNCTION__ */
#define HAVE_MACRO__FUNCTION__ 1

/* Defined if the compiler supports __FUNC__ */
/* #undef HAVE_MACRO__FUNC__ */

/* Defined if the compiler supports __func__ */
#define HAVE_MACRO__func__ 1

/* Define to 1 if you have the `mallinfo' function. */
/* #undef HAVE_MALLINFO */

/* Define to 1 if you have the <malloc.h> header file. */
/* #undef HAVE_MALLOC_H */

/* Define to 1 if you have the <malloc/malloc.h> header file. */
#define HAVE_MALLOC_MALLOC_H 1

/* Define to 1 if you have the <malloc_np.h> header file. */
/* #undef HAVE_MALLOC_NP_H */

/* Define to 1 if you have the `memmem' function. */
#define HAVE_MEMMEM 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `memset_s' function. */
#define HAVE_MEMSET_S 1

/* Define to 1 if you have the `mlockall' function. */
#define HAVE_MLOCKALL 1

/* Define to 1 if you have the `mmap' function. */
#define HAVE_MMAP 1

/* Compile with Directory Authority feature support */
#define HAVE_MODULE_DIRAUTH 1

/* Define to 1 if you have the <nacl/crypto_scalarmult_curve25519.h> header
   file. */
/* #undef HAVE_NACL_CRYPTO_SCALARMULT_CURVE25519_H */

/* Define to 1 if you have the <netdb.h> header file. */
#define HAVE_NETDB_H 1

/* Define to 1 if you have the <netinet/in6.h> header file. */
/* #undef HAVE_NETINET_IN6_H */

/* Define to 1 if you have the <netinet/in.h> header file. */
#define HAVE_NETINET_IN_H 1

/* Define to 1 if you have the <net/if.h> header file. */
#define HAVE_NET_IF_H 1

/* Define to 1 if you have the <net/pfvar.h> header file. */
/* #undef HAVE_NET_PFVAR_H */

/* Define to 1 if you have the `pipe' function. */
#define HAVE_PIPE 1

/* Define to 1 if you have the `pipe2' function. */
/* #undef HAVE_PIPE2 */

/* Define to 1 if you have the `prctl' function. */
/* #undef HAVE_PRCTL */

/* Define to 1 if you have the `pthread_condattr_setclock' function. */
/* #undef HAVE_PTHREAD_CONDATTR_SETCLOCK */

/* Define to 1 if you have the `pthread_create' function. */
#define HAVE_PTHREAD_CREATE 1

/* Define to 1 if you have the <pthread.h> header file. */
#define HAVE_PTHREAD_H 1

/* Define to 1 if you have the <pwd.h> header file. */
#define HAVE_PWD_H 1

/* Define to 1 if you have the `readpassphrase' function. */
#define HAVE_READPASSPHRASE 1

/* Define to 1 if you have the <readpassphrase.h> header file. */
#define HAVE_READPASSPHRASE_H 1

/* Define to 1 if you have the `rint' function. */
#define HAVE_RINT 1

/* Define to 1 if the system has the type `rlim_t'. */
#define HAVE_RLIM_T 1

/* Define to 1 if you have the `RtlSecureZeroMemory' function. */
/* #undef HAVE_RTLSECUREZEROMEMORY */

/* have Rust */
/* #undef HAVE_RUST */

/* Define to 1 if the system has the type `sa_family_t'. */
#define HAVE_SA_FAMILY_T 1

/* Define to 1 if you have the <seccomp.h> header file. */
/* #undef HAVE_SECCOMP_H */

/* Define to 1 if you have the `SecureZeroMemory' function. */
/* #undef HAVE_SECUREZEROMEMORY */

/* Define to 1 if you have the `sigaction' function. */
#define HAVE_SIGACTION 1

/* Define to 1 if you have the <signal.h> header file. */
#define HAVE_SIGNAL_H 1

/* Define to 1 if you have the `socketpair' function. */
#define HAVE_SOCKETPAIR 1

/* Define to 1 if the system has the type `ssize_t'. */
#define HAVE_SSIZE_T 1

/* Define to 1 if you have the `SSL_CIPHER_find' function. */
#define HAVE_SSL_CIPHER_FIND 1

/* Define to 1 if you have the `SSL_CTX_set1_groups_list' function. */
/* #undef HAVE_SSL_CTX_SET1_GROUPS_LIST */

/* Define to 1 if you have the `SSL_CTX_set_security_level' function. */
#define HAVE_SSL_CTX_SET_SECURITY_LEVEL 1

/* Define to 1 if you have the `SSL_get_client_ciphers' function. */
#define HAVE_SSL_GET_CLIENT_CIPHERS 1

/* Define to 1 if you have the `SSL_get_client_random' function. */
#define HAVE_SSL_GET_CLIENT_RANDOM 1

/* Define to 1 if you have the `SSL_get_server_random' function. */
#define HAVE_SSL_GET_SERVER_RANDOM 1

/* Define to 1 if you have the `SSL_SESSION_get_master_key' function. */
#define HAVE_SSL_SESSION_GET_MASTER_KEY 1

/* Define to 1 if `state' is a member of `SSL'. */
/* #undef HAVE_SSL_STATE */

/* Define to 1 if you have the `statvfs' function. */
#define HAVE_STATVFS 1

/* Define to 1 if you have the <stdatomic.h> header file. */
#define HAVE_STDATOMIC_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strcasecmp' function. */
#define HAVE_STRCASECMP 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strlcat' function. */
#define HAVE_STRLCAT 1

/* Define to 1 if you have the `strlcpy' function. */
#define HAVE_STRLCPY 1

/* Define to 1 if you have the `strncasecmp' function. */
#define HAVE_STRNCASECMP 1

/* Define to 1 if you have the `strnlen' function. */
#define HAVE_STRNLEN 1

/* Define to 1 if you have the `strptime' function. */
#define HAVE_STRPTIME 1

/* Define to 1 if you have the `strtok_r' function. */
#define HAVE_STRTOK_R 1

/* Define to 1 if you have the `strtoull' function. */
#define HAVE_STRTOULL 1

/* Define to 1 if the system has the type `struct in6_addr'. */
#define HAVE_STRUCT_IN6_ADDR 1

/* Define to 1 if `s6_addr16' is a member of `struct in6_addr'. */
/* #undef HAVE_STRUCT_IN6_ADDR_S6_ADDR16 */

/* Define to 1 if `s6_addr32' is a member of `struct in6_addr'. */
/* #undef HAVE_STRUCT_IN6_ADDR_S6_ADDR32 */

/* Define to 1 if the system has the type `struct sockaddr_in6'. */
#define HAVE_STRUCT_SOCKADDR_IN6 1

/* Define to 1 if `sin6_len' is a member of `struct sockaddr_in6'. */
#define HAVE_STRUCT_SOCKADDR_IN6_SIN6_LEN 1

/* Define to 1 if `sin_len' is a member of `struct sockaddr_in'. */
#define HAVE_STRUCT_SOCKADDR_IN_SIN_LEN 1

/* Define to 1 if `get_cipher_by_char' is a member of `struct ssl_method_st'.
   */
/* #undef HAVE_STRUCT_SSL_METHOD_ST_GET_CIPHER_BY_CHAR */

/* Define to 1 if `tcpi_snd_mss' is a member of `struct tcp_info'. */
/* #undef HAVE_STRUCT_TCP_INFO_TCPI_SND_MSS */

/* Define to 1 if `tcpi_unacked' is a member of `struct tcp_info'. */
/* #undef HAVE_STRUCT_TCP_INFO_TCPI_UNACKED */

/* Define to 1 if `tv_sec' is a member of `struct timeval'. */
#define HAVE_STRUCT_TIMEVAL_TV_SEC 1

/* Define to 1 if you have the `sysconf' function. */
#define HAVE_SYSCONF 1

/* Define to 1 if you have the `sysctl' function. */
#define HAVE_SYSCTL 1

/* Define to 1 if you have the <syslog.h> header file. */
#define HAVE_SYSLOG_H 1

/* Have systemd */
/* #undef HAVE_SYSTEMD */

/* Have systemd v209 or more */
/* #undef HAVE_SYSTEMD_209 */

/* Define to 1 if you have the <sys/capability.h> header file. */
/* #undef HAVE_SYS_CAPABILITY_H */

/* Define to 1 if you have the <sys/eventfd.h> header file. */
/* #undef HAVE_SYS_EVENTFD_H */

/* Define to 1 if you have the <sys/fcntl.h> header file. */
#define HAVE_SYS_FCNTL_H 1

/* Define to 1 if you have the <sys/file.h> header file. */
#define HAVE_SYS_FILE_H 1

/* Define to 1 if you have the <sys/ioctl.h> header file. */
#define HAVE_SYS_IOCTL_H 1

/* Define to 1 if you have the <sys/limits.h> header file. */
/* #undef HAVE_SYS_LIMITS_H */

/* Define to 1 if you have the <sys/mman.h> header file. */
#define HAVE_SYS_MMAN_H 1

/* Define to 1 if you have the <sys/param.h> header file. */
#define HAVE_SYS_PARAM_H 1

/* Define to 1 if you have the <sys/prctl.h> header file. */
/* #undef HAVE_SYS_PRCTL_H */

/* Define to 1 if you have the <sys/random.h> header file. */
#define HAVE_SYS_RANDOM_H 1

/* Define to 1 if you have the <sys/resource.h> header file. */
#define HAVE_SYS_RESOURCE_H 1

/* Define to 1 if you have the <sys/select.h> header file. */
#define HAVE_SYS_SELECT_H 1

/* Define to 1 if you have the <sys/socket.h> header file. */
#define HAVE_SYS_SOCKET_H 1

/* Define to 1 if you have the <sys/statvfs.h> header file. */
#define HAVE_SYS_STATVFS_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/syscall.h> header file. */
#define HAVE_SYS_SYSCALL_H 1

/* Define to 1 if you have the <sys/sysctl.h> header file. */
#define HAVE_SYS_SYSCTL_H 1

/* Define to 1 if you have the <sys/syslimits.h> header file. */
#define HAVE_SYS_SYSLIMITS_H 1

/* Define to 1 if you have the <sys/time.h> header file. */
#define HAVE_SYS_TIME_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/ucontext.h> header file. */
#define HAVE_SYS_UCONTEXT_H 1

/* Define to 1 if you have the <sys/un.h> header file. */
#define HAVE_SYS_UN_H 1

/* Define to 1 if you have the <sys/utime.h> header file. */
/* #undef HAVE_SYS_UTIME_H */

/* Define to 1 if you have the <sys/wait.h> header file. */
#define HAVE_SYS_WAIT_H 1

/* Define to 1 if you have the <time.h> header file. */
#define HAVE_TIME_H 1

/* Define to 1 if you have the `timingsafe_memcmp' function. */
/* #undef HAVE_TIMINGSAFE_MEMCMP */

/* Define to 1 if you have the `TLS_method' function. */
#define HAVE_TLS_METHOD 1

/* Define to 1 if you have the `truncate' function. */
#define HAVE_TRUNCATE 1

/* Define to 1 if you have the <ucontext.h> header file. */
/* #undef HAVE_UCONTEXT_H */

/* Define to 1 if the system has the type `uint'. */
#define HAVE_UINT 1

/* Define to 1 if you have the `uname' function. */
#define HAVE_UNAME 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the `usleep' function. */
#define HAVE_USLEEP 1

/* Define to 1 if you have the <utime.h> header file. */
#define HAVE_UTIME_H 1

/* Define to 1 if the system has the type `u_char'. */
#define HAVE_U_CHAR 1

/* Define to 1 if you have the `vasprintf' function. */
#define HAVE_VASPRINTF 1

/* Have Zstd */
/* #undef HAVE_ZSTD */

/* Define to 1 if you have the `ZSTD_estimateCStreamSize' function. */
/* #undef HAVE_ZSTD_ESTIMATECSTREAMSIZE */

/* Define to 1 if you have the `ZSTD_estimateDCtxSize' function. */
/* #undef HAVE_ZSTD_ESTIMATEDCTXSIZE */

/* Define to 1 if you have the `_NSGetEnviron' function. */
#define HAVE__NSGETENVIRON 1

/* Define to 1 if you have the `_vscprintf' function. */
/* #undef HAVE__VSCPRINTF */

/* name of the syslog facility */
#define LOGFACILITY LOG_DAEMON

/* Define to 1 iff malloc(0) returns a pointer */
#define MALLOC_ZERO_WORKS 1

/* Define to 1 iff memset(0) sets pointers to NULL */
#define NULL_REP_IS_ZERO_BYTES 1

/* Name of package */
#define PACKAGE "tor"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME "tor"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "tor {{.StrVer}}"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "tor"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "{{.StrVer}}"

/* How to access the PC from a struct ucontext */
#define PC_FROM_UCONTEXT uc_mcontext->__ss.__rip

/* Define to 1 iff right-shifting a negative value performs sign-extension */
#define RSHIFT_DOES_SIGN_EXTEND 1

/* The size of `cell_t', as computed by sizeof. */
#define SIZEOF_CELL_T 0

/* The size of `char', as computed by sizeof. */
#define SIZEOF_CHAR 1

/* The size of `int', as computed by sizeof. */
#define SIZEOF_INT 4

/* The size of `long', as computed by sizeof. */
#define SIZEOF_LONG 8

/* The size of `long long', as computed by sizeof. */
#define SIZEOF_LONG_LONG 8

/* The size of `pid_t', as computed by sizeof. */
#define SIZEOF_PID_T 4

/* The size of `SHA_CTX', as computed by sizeof. */
#define SIZEOF_SHA_CTX 96

/* The size of `short', as computed by sizeof. */
#define SIZEOF_SHORT 2

/* The size of `size_t', as computed by sizeof. */
#define SIZEOF_SIZE_T 8

/* The size of `socklen_t', as computed by sizeof. */
#define SIZEOF_SOCKLEN_T 4

/* The size of `time_t', as computed by sizeof. */
#define SIZEOF_TIME_T 8

/* The size of `void *', as computed by sizeof. */
#define SIZEOF_VOID_P 8

/* The size of `__int64', as computed by sizeof. */
#define SIZEOF___INT64 0

/* tor's sourcedir directory */
#define SRCDIR ""

/* Set to 1 if we can compile a simple stdatomic example. */
#define STDATOMIC_WORKS 1

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Compile the event tracing instrumentation */
/* #undef TOR_EVENT_TRACING_ENABLED */

/* Compile with Android specific features enabled */
/* #undef USE_ANDROID */

/* Defined if we should use an internal curve25519_donna{,_c64} implementation
   */
#define USE_CURVE25519_DONNA 1

/* Defined if we should use a curve25519 from nacl */
/* #undef USE_CURVE25519_NACL */

/* Tracing framework to log debug */
/* #undef USE_EVENT_TRACING_DEBUG */

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif


/* "Define to enable transparent proxy support" */
/* #undef USE_TRANSPARENT */

/* Define to 1 iff we represent negative integers with two's complement */
#define USING_TWOS_COMPLEMENT 1

/* Version number of package */
#define VERSION "{{.StrVer}}"

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
/* #  undef WORDS_BIGENDIAN */
# endif
#endif

/* Enable large inode numbers on Mac OS X 10.5.  */
#ifndef _DARWIN_USE_64_BIT_INODE
# define _DARWIN_USE_64_BIT_INODE 1
#endif

/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _FILE_OFFSET_BITS */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

/* Define to 1 if on MINIX. */
/* #undef _MINIX */

/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
/* #undef _POSIX_1_SOURCE */

/* Define to 1 if you need to in order for `stat' and other things to work. */
/* #undef _POSIX_SOURCE */

/* Define on some platforms to activate x_r() functions in time.h */
/* #undef _REENTRANT */
