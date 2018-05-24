// Copyright (c) 2007, 2018, Oracle and/or its affiliates. All rights reserved. 
// 
// This program is free software; you can redistribute it and/or modify 
// it under the terms of the GNU General Public License, version 2.0, as 
// published by the Free Software Foundation. 
// 
// This program is also distributed with certain software (including 
// but not limited to OpenSSL) that is licensed under separate terms, 
// as designated in a particular file or component or in included license 
// documentation. The authors of MySQL hereby grant you an 
// additional permission to link the program and your derivative works 
// with the separately licensed software that they have included with 
// MySQL. 
// 
// Without limiting anything contained in the foregoing, this file, 
// which is part of MySQL Connector/ODBC, is also subject to the 
// Universal FOSS Exception, version 1.0, a copy of which can be found at 
// http://oss.oracle.com/licenses/universal-foss-exception. 
// 
// This program is distributed in the hope that it will be useful, but 
// WITHOUT ANY WARRANTY; without even the implied warranty of 
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
// See the GNU General Public License, version 2.0, for more details. 
// 
// You should have received a copy of the GNU General Public License 
// along with this program; if not, write to the Free Software Foundation, Inc., 
// 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA 

#ifndef MY_CONFIG_H
#define MY_CONFIG_H

/*
 * From configure.cmake, in order of appearance 
 */
#define HAVE_LLVM_LIBCPP 1
/* #undef _LARGEFILE_SOURCE */

/* Libraries */
/* #undef HAVE_LIBM */
/* #undef HAVE_LIBNSL */
/* #undef HAVE_LIBCRYPT */
/* #undef HAVE_LIBSOCKET */
/* #undef HAVE_LIBDL */
/* #undef HAVE_LIBRT */
/* #undef HAVE_LIBWRAP */

/* Header files */
#define HAVE_ALLOCA_H 1
#define HAVE_ARPA_INET_H 1
#define HAVE_DLFCN_H 1
#define HAVE_EXECINFO_H 1
/* #undef HAVE_FPU_CONTROL_H */
#define HAVE_GRP_H 1
/* #undef HAVE_IEEEFP_H */
#define HAVE_LANGINFO_H 1
/* #undef HAVE_MALLOC_H */
#define HAVE_NETINET_IN_H 1
#define HAVE_POLL_H 1
#define HAVE_PWD_H 1
#define HAVE_STRINGS_H 1
#define HAVE_SYS_CDEFS_H 1
#define HAVE_SYS_IOCTL_H 1
#define HAVE_SYS_MMAN_H 1
#define HAVE_SYS_RESOURCE_H 1
#define HAVE_SYS_SELECT_H 1
#define HAVE_SYS_SOCKET_H 1
#define HAVE_TERM_H 1
#define HAVE_TERMIOS_H 1
/* #undef HAVE_TERMIO_H */
#define HAVE_UNISTD_H 1
#define HAVE_SYS_WAIT_H 1
#define HAVE_SYS_PARAM_H 1
#define HAVE_FNMATCH_H 1
#define HAVE_SYS_UN_H 1
#define HAVE_VIS_H 1
#define HAVE_SASL_SASL_H 1

/* Libevent */
/* #undef HAVE_DEVPOLL */
/* #undef HAVE_SYS_DEVPOLL_H */
/* #undef HAVE_SYS_EPOLL_H */
#define HAVE_TAILQFOREACH 1

/* Functions */
/* #undef HAVE_ALIGNED_MALLOC */
#define HAVE_BACKTRACE 1
/* #undef HAVE_PRINTSTACK */
#define HAVE_INDEX 1
#define HAVE_CLOCK_GETTIME 1
/* #undef HAVE_CUSERID */
/* #undef HAVE_DIRECTIO */
#define HAVE_FTRUNCATE 1
/* #undef HAVE_COMPRESS */
/* #undef HAVE_CRYPT */
/* #undef HAVE_DLOPEN */
#define HAVE_FCHMOD 1
#define HAVE_FCNTL 1
#define HAVE_FDATASYNC 1
/* #undef HAVE_DECL_FDATASYNC */
/* #undef HAVE_FEDISABLEEXCEPT */
#define HAVE_FSEEKO 1
#define HAVE_FSYNC 1
/* #undef HAVE_GETHOSTBYADDR_R */
/* #undef HAVE_GETHRTIME */
#define HAVE_GETNAMEINFO 1
#define HAVE_GETPASS 1
/* #undef HAVE_GETPASSPHRASE */
#define HAVE_GETPWNAM 1
#define HAVE_GETPWUID 1
#define HAVE_GETRLIMIT 1
#define HAVE_GETRUSAGE 1
#define HAVE_INITGROUPS 1
#define HAVE_ISSETUGID 1
#define HAVE_GETUID 1
#define HAVE_GETEUID 1
#define HAVE_GETGID 1
#define HAVE_GETEGID 1
/* #undef HAVE_LSTAT */
#define HAVE_MADVISE 1
/* #undef HAVE_MALLOC_INFO */
/* #undef HAVE_MEMRCHR */
#define HAVE_MLOCK 1
#define HAVE_MLOCKALL 1
/* #undef HAVE_MMAP64 */
#define HAVE_POLL 1
/* #undef HAVE_POSIX_FALLOCATE */
#define HAVE_POSIX_MEMALIGN 1
#define HAVE_PREAD 1
/* #undef HAVE_PTHREAD_CONDATTR_SETCLOCK */
#define HAVE_PTHREAD_SIGMASK 1
/* #undef HAVE_READLINK */
/* #undef HAVE_REALPATH */
/* #undef HAVE_SETFD */
#define HAVE_SIGACTION 1
#define HAVE_SLEEP 1
#define HAVE_STPCPY 1
#define HAVE_STPNCPY 1
#define HAVE_STRLCPY 1
/* #undef HAVE_STRNLEN */
#define HAVE_STRLCAT 1
#define HAVE_STRSIGNAL 1
#define HAVE_FGETLN 1
#define HAVE_STRSEP 1
/* #undef HAVE_TELL */
#define HAVE_VASPRINTF 1
/* #undef HAVE_MEMALIGN */
#define HAVE_NL_LANGINFO 1
/* #undef HAVE_HTONLL */
#define DNS_USE_CPU_CLOCK_FOR_ID 1
/* #undef HAVE_EPOLL */
/* #undef HAVE_EVENT_PORTS */
#define HAVE_INET_NTOP 1
#define HAVE_WORKING_KQUEUE 1
#define HAVE_TIMERADD 1
#define HAVE_TIMERCLEAR 1
#define HAVE_TIMERCMP 1
#define HAVE_TIMERISSET 1

/* WL2373 */
#define HAVE_SYS_TIME_H 1
#define HAVE_SYS_TIMES_H 1
#define HAVE_TIMES 1
#define HAVE_GETTIMEOFDAY 1

/* Symbols */
#define HAVE_LRAND48 1
#define GWINSZ_IN_SYS_IOCTL 1
#define FIONREAD_IN_SYS_IOCTL 1
#define FIONREAD_IN_SYS_FILIO 1
/* #undef HAVE_SIGEV_THREAD_ID */
/* #undef HAVE_SIGEV_PORT */
/* #undef HAVE_LOG2 */

#define HAVE_ISINF 1

#define HAVE_KQUEUE_TIMERS 1
/* #undef HAVE_POSIX_TIMERS */

/* Endianess */
/* #undef WORDS_BIGENDIAN */

/* Type sizes */
#define SIZEOF_VOIDP     8
#define SIZEOF_CHARP     8
#define SIZEOF_LONG      8
#define SIZEOF_SHORT     2
#define SIZEOF_INT       4
#define SIZEOF_LONG_LONG 8
#define SIZEOF_OFF_T     8
#define SIZEOF_TIME_T    8
/* #undef HAVE_UINT */
/* #undef HAVE_ULONG */
#define HAVE_U_INT32_T 1
#define HAVE_STRUCT_TIMESPEC 1

/* Support for tagging symbols with __attribute__((visibility("hidden"))) */
#define HAVE_VISIBILITY_HIDDEN 1

/* Code tests*/
#define STACK_DIRECTION -1
#define TIME_WITH_SYS_TIME 1
/* #undef NO_FCNTL_NONBLOCK */
#define HAVE_PAUSE_INSTRUCTION 1
/* #undef HAVE_FAKE_PAUSE_INSTRUCTION */
/* #undef HAVE_HMT_PRIORITY_INSTRUCTION */
#define HAVE_ABI_CXA_DEMANGLE 1
#define HAVE_BUILTIN_UNREACHABLE 1
#define HAVE_BUILTIN_EXPECT 1
#define HAVE_BUILTIN_STPCPY 1
#define HAVE_GCC_ATOMIC_BUILTINS 1
#define HAVE_GCC_SYNC_BUILTINS 1
/* #undef HAVE_VALGRIND */

/* IPV6 */
/* #undef HAVE_NETINET_IN6_H */
/* #undef HAVE_STRUCT_SOCKADDR_IN6 */
/* #undef HAVE_STRUCT_IN6_ADDR */
/* #undef HAVE_IPV6 */

/* #undef ss_family */
#define HAVE_SOCKADDR_IN_SIN_LEN 1
#define HAVE_SOCKADDR_IN6_SIN6_LEN 1

/*
 * Platform specific CMake files
 */
#define MACHINE_TYPE ""
/* #undef HAVE_LINUX_LARGE_PAGES */
/* #undef HAVE_SOLARIS_LARGE_PAGES */
/* #undef HAVE_SOLARIS_ATOMIC */
/* #undef HAVE_SOLARIS_STYLE_GETHOST */
#define SYSTEM_TYPE "Darwin"
/* Windows stuff, mostly functions, that have Posix analogs but named differently */
/* #undef IPPROTO_IPV6 */
/* #undef IPV6_V6ONLY */
/* This should mean case insensitive file system */
/* #undef FN_NO_CASE_SENSE */

/*
 * From main CMakeLists.txt
 */
/* #undef MAX_INDEXES */
/* #undef WITH_INNODB_MEMCACHED */
/* #undef ENABLE_MEMCACHED_SASL */
/* #undef ENABLE_MEMCACHED_SASL_PWDB */
/* #undef ENABLED_PROFILING */
/* #undef HAVE_ASAN */
/* #undef ENABLED_LOCAL_INFILE */
/* #undef OPTIMIZER_TRACE */
#define DEFAULT_MYSQL_HOME "/usr/local"
#define SHAREDIR "/usr/local/"
#define DEFAULT_BASEDIR "/usr/local"
#define MYSQL_DATADIR "/usr/local"
#define MYSQL_KEYRINGDIR "/usr/local"
#define DEFAULT_CHARSET_HOME "/usr/local"
#define PLUGINDIR "/usr/local/"
/* #undef DEFAULT_SYSCONFDIR */
/* #undef DEFAULT_TMPDIR */
/* #undef INSTALL_SBINDIR */
/* #undef INSTALL_BINDIR */
/* #undef INSTALL_MYSQLSHAREDIR */
/* #undef INSTALL_SHAREDIR */
/* #undef INSTALL_PLUGINDIR */
/* #undef INSTALL_INCLUDEDIR */
/* #undef INSTALL_SCRIPTDIR */
/* #undef INSTALL_MYSQLDATADIR */
/* #undef INSTALL_MYSQLKEYRINGDIR */
/* #undef INSTALL_PLUGINTESTDIR */
/* #undef INSTALL_INFODIR */
/* #undef INSTALL_MYSQLTESTDIR */
/* #undef INSTALL_DOCREADMEDIR */
/* #undef INSTALL_DOCDIR */
/* #undef INSTALL_MANDIR */
/* #undef INSTALL_SUPPORTFILESDIR */
/* #undef INSTALL_LIBDIR */

/*
 * Readline
 */
/* #undef HAVE_MBSTATE_T */
/* #undef HAVE_LANGINFO_CODESET */
/* #undef HAVE_WCSDUP */
/* #undef HAVE_WCHAR_T */
/* #undef HAVE_WINT_T */
/* #undef HAVE_CURSES_H */
/* #undef HAVE_NCURSES_H */
/* #undef USE_LIBEDIT_INTERFACE */
/* #undef HAVE_HIST_ENTRY */
/* #undef USE_NEW_EDITLINE_INTERFACE */

/*
 * Libedit
 */
/* #undef HAVE_DECL_TGOTO */

/*
 * DTrace
 */
/* #undef HAVE_DTRACE */

/*
 * Character sets
 */
#define MYSQL_DEFAULT_CHARSET_NAME "latin1"
#define MYSQL_DEFAULT_COLLATION_NAME "latin1_swedish_ci"
#define HAVE_CHARSET_armscii8 1
#define HAVE_CHARSET_ascii 1
#define HAVE_CHARSET_big5 1
#define HAVE_CHARSET_cp1250 1
#define HAVE_CHARSET_cp1251 1
#define HAVE_CHARSET_cp1256 1
#define HAVE_CHARSET_cp1257 1
#define HAVE_CHARSET_cp850 1
#define HAVE_CHARSET_cp852 1 
#define HAVE_CHARSET_cp866 1
#define HAVE_CHARSET_cp932 1
#define HAVE_CHARSET_dec8 1
#define HAVE_CHARSET_eucjpms 1
#define HAVE_CHARSET_euckr 1
#define HAVE_CHARSET_gb2312 1
#define HAVE_CHARSET_gbk 1
#define HAVE_CHARSET_gb18030 1
#define HAVE_CHARSET_geostd8 1
#define HAVE_CHARSET_greek 1
#define HAVE_CHARSET_hebrew 1
#define HAVE_CHARSET_hp8 1
#define HAVE_CHARSET_keybcs2 1
#define HAVE_CHARSET_koi8r 1
#define HAVE_CHARSET_koi8u 1
#define HAVE_CHARSET_latin1 1
#define HAVE_CHARSET_latin2 1
#define HAVE_CHARSET_latin5 1
#define HAVE_CHARSET_latin7 1
#define HAVE_CHARSET_macce 1
#define HAVE_CHARSET_macroman 1
#define HAVE_CHARSET_sjis 1
#define HAVE_CHARSET_swe7 1
#define HAVE_CHARSET_tis620 1
#define HAVE_CHARSET_ucs2 1
#define HAVE_CHARSET_ujis 1
#define HAVE_CHARSET_utf8mb4 1
/* #undef HAVE_CHARSET_utf8mb3 */
#define HAVE_CHARSET_utf8 1
#define HAVE_CHARSET_utf16 1
#define HAVE_CHARSET_utf32 1
#define HAVE_UCA_COLLATIONS 1

/*
 * Feature set
 */
/* #undef WITH_PARTITION_STORAGE_ENGINE */

/*
 * Performance schema
 */
#define WITH_PERFSCHEMA_STORAGE_ENGINE 1
/* #undef DISABLE_PSI_THREAD */
/* #undef DISABLE_PSI_MUTEX */
/* #undef DISABLE_PSI_RWLOCK */
/* #undef DISABLE_PSI_COND */
/* #undef DISABLE_PSI_FILE */
/* #undef DISABLE_PSI_TABLE */
/* #undef DISABLE_PSI_SOCKET */
/* #undef DISABLE_PSI_STAGE */
/* #undef DISABLE_PSI_STATEMENT */
/* #undef DISABLE_PSI_SP */
/* #undef DISABLE_PSI_PS */
/* #undef DISABLE_PSI_IDLE */
/* #undef DISABLE_PSI_STATEMENT_DIGEST */
/* #undef DISABLE_PSI_METADATA */
/* #undef DISABLE_PSI_MEMORY */
/* #undef DISABLE_PSI_TRANSACTION */

/*
 * syscall
*/
/* #undef HAVE_SYS_THREAD_SELFID */
#define HAVE_SYS_GETTID 1
/* #undef HAVE_PTHREAD_GETTHREADID_NP */
/* #undef HAVE_PTHREAD_SETNAME_NP */
/* #undef HAVE_INTEGER_PTHREAD_SELF */

/* Platform-specific C++ compiler behaviors we rely upon */

/*
  This macro defines whether the compiler in use needs a 'typename' keyword
  to access the types defined inside a class template, such types are called
  dependent types. Some compilers require it, some others forbid it, and some
  others may work with or without it. For example, GCC requires the 'typename'
  keyword whenever needing to access a type inside a template, but msvc
  forbids it.
 */
/* #undef HAVE_IMPLICIT_DEPENDENT_NAME_TYPING */


/*
 * MySQL version
 */
/* #undef DOT_FRM_VERSION */
#define MYSQL_VERSION_MAJOR 
#define MYSQL_VERSION_MINOR 
#define MYSQL_VERSION_PATCH 
#define MYSQL_VERSION_EXTRA ""
#define PACKAGE "mysql"
#define PACKAGE_BUGREPORT ""
#define PACKAGE_NAME "MySQL Server"
#define PACKAGE_STRING "MySQL Server "
#define PACKAGE_TARNAME "mysql"
#define PACKAGE_VERSION ""
#define VERSION ""
#define PROTOCOL_VERSION 10

/*
 * CPU info
 */
/* #undef CPU_LEVEL1_DCACHE_LINESIZE */

/*
 * NDB
 */
/* #undef WITH_NDBCLUSTER_STORAGE_ENGINE */
/* #undef HAVE_PTHREAD_SETSCHEDPARAM */

/*
 * Other
 */
/* #undef EXTRA_DEBUG */
#define HAVE_CHOWN 1

/*
 * Hardcoded values needed by libevent/NDB/memcached
 */
#define HAVE_FCNTL_H 1
#define HAVE_GETADDRINFO 1
#define HAVE_INTTYPES_H 1
/* libevent's select.c is not Windows compatible */
#ifndef _WIN32
#define HAVE_SELECT 1
#endif
#define HAVE_SIGNAL_H 1
#define HAVE_STDARG_H 1
#define HAVE_STDINT_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STRDUP 1
#define HAVE_STRTOK_R 1
#define HAVE_STRTOLL 1
#define HAVE_SYS_STAT_H 1
#define HAVE_SYS_TYPES_H 1
#define SIZEOF_CHAR 1

/*
 * Needed by libevent
 */
#define HAVE_SOCKLEN_T 1

/* For --secure-file-priv */
/* #undef DEFAULT_SECURE_FILE_PRIV_DIR */
/* #undef DEFAULT_SECURE_FILE_PRIV_EMBEDDED_DIR */
/* #undef HAVE_LIBNUMA */

/* For default value of --early_plugin_load */
/* #undef DEFAULT_EARLY_PLUGIN_LOAD */

#endif
