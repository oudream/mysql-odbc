// Copyright (c) 2000, 2015, Oracle and/or its affiliates. All rights reserved. 
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
// which is part of <MySQL Product>, is also subject to the 
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

#include "mysys_priv.h"
#include "my_sys.h"
#include "my_static.h"
#include "mysys_err.h"
#include "m_string.h"
#include "mysql/psi/mysql_stage.h"
#include "mysql/psi/mysql_file.h"

#ifdef HAVE_SYS_RESOURCE_H
#include <sys/resource.h>
#endif

#ifdef _WIN32
#include <locale.h>
#include <crtdbg.h>
/* WSAStartup needs winsock library*/
#pragma comment(lib, "ws2_32")
my_bool sys_have_tcpip=0;
#endif

#define SCALE_SEC       100
#define SCALE_USEC      10000

my_bool mysys_init_done= FALSE;
ulong  mysys_thread_stack_size= 65536;
MYSQL_FILE *mysys_stdin= NULL;
static MYSQL_FILE instrumented_stdin;


static ulong atoi_octal(const char *str)
{
  long int tmp;
  while (*str && my_isspace(&my_charset_latin1, *str))
    str++;
  str2int(str,
	  (*str == '0' ? 8 : 10),       /* Octalt or decimalt */
	  0, INT_MAX, &tmp);
  return (ulong) tmp;
}


#if defined(MY_MSCRT_DEBUG)
int set_crt_report_leaks()
{
  HANDLE hLogFile;

  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF        // debug allocation on
                 | _CRTDBG_LEAK_CHECK_DF     // leak checks on exit
                 | _CRTDBG_CHECK_ALWAYS_DF   // memory check (slow)
                 );

  return ((
    NULL == (hLogFile= GetStdHandle(STD_ERROR_HANDLE)) ||
    -1 == _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE) ||
    _CRTDBG_HFILE_ERROR == _CrtSetReportFile(_CRT_WARN, hLogFile) ||
    -1 == _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE) ||
    _CRTDBG_HFILE_ERROR == _CrtSetReportFile(_CRT_ERROR, hLogFile) ||
    -1 == _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE) ||
    _CRTDBG_HFILE_ERROR == _CrtSetReportFile(_CRT_ASSERT, hLogFile)) ? 1 : 0);
}
#endif


/**
  Initialize my_sys functions, resources and variables

  @return Initialization result
    @retval FALSE Success
    @retval TRUE  Error. Couldn't initialize environment
*/
my_bool my_sys_init()
{
  if (mysys_init_done)
    return FALSE;

  mysys_init_done= TRUE;

#if defined(MY_MSCRT_DEBUG)
  set_crt_report_leaks();
#endif

  mysys_umask= 0640;                       /* Default umask for new files */
  mysys_umask_dir= 0750;                   /* Default umask for new directories */

  instrumented_stdin.m_file= stdin;
  instrumented_stdin.m_psi= NULL;       /* not yet instrumented */
  mysys_stdin= & instrumented_stdin;

  if (my_thread_global_init())
    return TRUE;

  if (mysys_thread_init())
    return TRUE;

  return FALSE;
} /* my_init */


	/* End my_sys */

void mysys_end(int infoflag)
{
  /*
    We do not use DBUG_ENTER here, as after cleanup DBUG is no longer
    operational, so we cannot use DBUG_RETURN.
  */

  FILE *info_file= (DBUG_FILE ? DBUG_FILE : stderr);

  if (!mysys_init_done)
    return;

  if ((infoflag & MY_CHECK_ERROR) || (info_file != stderr))

  {					/* Test if some file is left open */
    if (mysys_file_opened | mysys_stream_opened)
    {
      char ebuff[512];
      my_snprintf(ebuff, sizeof(ebuff), EE(EE_OPEN_WARNING),
                  mysys_file_opened, mysys_stream_opened);
      mysys_message_stderr(EE_OPEN_WARNING, ebuff, MYF(0));
      DBUG_PRINT("error", ("%s", ebuff));
      my_print_open_files();
    }
  }
  free_charsets();
  my_error_unregister_all();
  my_once_free();

  if ((infoflag & MY_GIVE_INFO) || (info_file != stderr))
  {
#ifdef HAVE_GETRUSAGE
    struct rusage rus;
    if (!getrusage(RUSAGE_SELF, &rus))
      fprintf(info_file,"\n\
User time %.2f, System time %.2f\n                              \
Maximum resident set size %ld, Integral resident set size %ld\n\
Non-physical pagefaults %ld, Physical pagefaults %ld, Swaps %ld\n\
Blocks in %ld out %ld, Messages in %ld out %ld, Signals %ld\n\
Voluntary context switches %ld, Involuntary context switches %ld\n",
	      (rus.ru_utime.tv_sec * SCALE_SEC +
	       rus.ru_utime.tv_usec / SCALE_USEC) / 100.0,
	      (rus.ru_stime.tv_sec * SCALE_SEC +
	       rus.ru_stime.tv_usec / SCALE_USEC) / 100.0,
	      rus.ru_maxrss, rus.ru_idrss,
	      rus.ru_minflt, rus.ru_majflt,
	      rus.ru_nswap, rus.ru_inblock, rus.ru_oublock,
	      rus.ru_msgsnd, rus.ru_msgrcv, rus.ru_nsignals,
	      rus.ru_nvcsw, rus.ru_nivcsw);
#endif
#if defined(_WIN32)
   _CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE );
   _CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDERR );
   _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE );
   _CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDERR );
   _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE );
   _CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDERR );
   _CrtCheckMemory();
   _CrtDumpMemoryLeaks();
#endif
  }

  if (!(infoflag & MY_DONT_FREE_DBUG))
  {
    DBUG_END();                /* Must be done before my_thread_end */
  }

  my_thread_end();
  my_thread_global_end();

#ifdef _WIN32
  if (sys_have_tcpip)
    WSACleanup();
#endif /* _WIN32 */

  mysys_init_done= FALSE;
} /* my_end */


#ifdef _WIN32
/*
  my_parameter_handler

  Invalid parameter handler we will use instead of the one "baked"
  into the CRT for MSC v8.  This one just prints out what invalid
  parameter was encountered.  By providing this routine, routines like
  lseek will return -1 when we expect them to instead of crash.
*/

void my_parameter_handler(const wchar_t * expression, const wchar_t * function,
                          const wchar_t * file, unsigned int line,
                          uintptr_t pReserved)
{
  DBUG_PRINT("my",("Expression: %s  function: %s  file: %s, line: %d",
		   expression, function, file, line));
}

#define OFFSET_TO_EPOC ((__int64) 134774 * 24 * 60 * 60 * 1000 * 1000 * 10)
#define MS 10000000

static void win_init_time()
{
  /* The following is used by time functions */
  FILETIME ft;
  LARGE_INTEGER li, t_cnt;

  DBUG_ASSERT(sizeof(LARGE_INTEGER) == sizeof(query_performance_frequency));

  if (QueryPerformanceFrequency((LARGE_INTEGER *)&query_performance_frequency) == 0)
    query_performance_frequency= 0;
  else
  {
    GetSystemTimeAsFileTime(&ft);
    li.LowPart=  ft.dwLowDateTime;
    li.HighPart= ft.dwHighDateTime;
    query_performance_offset= li.QuadPart-OFFSET_TO_EPOC;
    QueryPerformanceCounter(&t_cnt);
    query_performance_offset-= (t_cnt.QuadPart /
                                query_performance_frequency * MS +
                                t_cnt.QuadPart %
                                query_performance_frequency * MS /
                                query_performance_frequency);
  }
}


/*------------------------------------------------------------------
  Name: CheckForTcpip| Desc: checks if tcpip has been installed on system
  According to Microsoft Developers documentation the first registry
  entry should be enough to check if TCP/IP is installed, but as expected
  this doesn't work on all Win32 machines :(
------------------------------------------------------------------*/

#define TCPIPKEY  "SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters"
#define WINSOCK2KEY "SYSTEM\\CurrentControlSet\\Services\\Winsock2\\Parameters"
#define WINSOCKKEY  "SYSTEM\\CurrentControlSet\\Services\\Winsock\\Parameters"


#endif /* _WIN32 */

PSI_stage_info sys_stage_waiting_for_table_level_lock=
{0, "Waiting for table level lock", 0};

#ifdef HAVE_PSI_INTERFACE

PSI_mutex_key key_BITMAP_mutex, key_IO_CACHE_append_buffer_lock,
  key_IO_CACHE_SHARE_mutex, key_KEY_CACHE_cache_lock,
  key_THR_LOCK_charset, key_THR_LOCK_heap,
  key_THR_LOCK_lock, key_THR_LOCK_malloc,
  key_THR_LOCK_mutex, key_THR_LOCK_myisam, key_THR_LOCK_net,
  key_THR_LOCK_open, key_THR_LOCK_threads,
  key_TMPDIR_mutex, key_THR_LOCK_myisam_mmap;

static PSI_mutex_info all_mysys_mutexes[]=
{
  { &key_BITMAP_mutex, "BITMAP::mutex", 0},
  { &key_IO_CACHE_append_buffer_lock, "IO_CACHE::append_buffer_lock", 0},
  { &key_IO_CACHE_SHARE_mutex, "IO_CACHE::SHARE_mutex", 0},
  { &key_KEY_CACHE_cache_lock, "KEY_CACHE::cache_lock", 0},
  { &key_THR_LOCK_charset, "THR_LOCK_charset", PSI_FLAG_GLOBAL},
  { &key_THR_LOCK_heap, "THR_LOCK_heap", PSI_FLAG_GLOBAL},
  { &key_THR_LOCK_lock, "THR_LOCK_lock", PSI_FLAG_GLOBAL},
  { &key_THR_LOCK_malloc, "THR_LOCK_malloc", PSI_FLAG_GLOBAL},
  { &key_THR_LOCK_mutex, "THR_LOCK::mutex", 0},
  { &key_THR_LOCK_myisam, "THR_LOCK_myisam", PSI_FLAG_GLOBAL},
  { &key_THR_LOCK_net, "THR_LOCK_net", PSI_FLAG_GLOBAL},
  { &key_THR_LOCK_open, "THR_LOCK_open", PSI_FLAG_GLOBAL},
  { &key_THR_LOCK_threads, "THR_LOCK_threads", PSI_FLAG_GLOBAL},
  { &key_TMPDIR_mutex, "TMPDIR_mutex", PSI_FLAG_GLOBAL},
  { &key_THR_LOCK_myisam_mmap, "THR_LOCK_myisam_mmap", PSI_FLAG_GLOBAL}
};

PSI_rwlock_key key_SAFE_HASH_lock;

static PSI_rwlock_info all_mysys_rwlocks[]=
{
  { &key_SAFE_HASH_lock, "SAFE_HASH::lock", 0}
};

PSI_cond_key key_IO_CACHE_SHARE_cond,
  key_IO_CACHE_SHARE_cond_writer,
  key_THR_COND_threads;

static PSI_cond_info all_mysys_conds[]=
{
  { &key_IO_CACHE_SHARE_cond, "IO_CACHE_SHARE::cond", 0},
  { &key_IO_CACHE_SHARE_cond_writer, "IO_CACHE_SHARE::cond_writer", 0},
  { &key_THR_COND_threads, "THR_COND_threads", 0}
};

#ifdef HAVE_LINUX_LARGE_PAGES
PSI_file_key key_file_proc_meminfo;
#endif /* HAVE_LINUX_LARGE_PAGES */
PSI_file_key key_file_charset, key_file_cnf;

static PSI_file_info all_mysys_files[]=
{
#ifdef HAVE_LINUX_LARGE_PAGES
  { &key_file_proc_meminfo, "proc_meminfo", 0},
#endif /* HAVE_LINUX_LARGE_PAGES */
  { &key_file_charset, "charset", 0},
  { &key_file_cnf, "cnf", 0}
};

PSI_stage_info *all_mysys_stages[]=
{
  &sys_stage_waiting_for_table_level_lock
};

static PSI_memory_info all_mysys_memory[]=
{
#ifdef _WIN32
  { &key_memory_win_SECURITY_ATTRIBUTES, "win_SECURITY_ATTRIBUTES", 0},
  { &key_memory_win_PACL, "win_PACL", 0},
  { &key_memory_win_IP_ADAPTER_ADDRESSES, "win_IP_ADAPTER_ADDRESSES", 0},
#endif

  { &key_memory_max_alloca, "max_alloca", 0},
  { &key_memory_charset_file, "charset_file", 0},
  { &key_memory_charset_loader, "charset_loader", 0},
  { &key_memory_lf_node, "lf_node", 0},
  { &key_memory_lf_dynarray, "lf_dynarray", 0},
  { &key_memory_lf_slist, "lf_slist", 0},
  { &key_memory_LIST, "LIST", 0},
  { &key_memory_IO_CACHE, "IO_CACHE", 0},
  { &key_memory_KEY_CACHE, "KEY_CACHE", 0},
  { &key_memory_SAFE_HASH_ENTRY, "SAFE_HASH_ENTRY", 0},
  { &key_memory_MY_TMPDIR_full_list, "MY_TMPDIR::full_list", 0},
  { &key_memory_MY_BITMAP_bitmap, "MY_BITMAP::bitmap", 0},
  { &key_memory_my_compress_alloc, "my_compress_alloc", 0},
  { &key_memory_pack_frm, "pack_frm", 0},
  { &key_memory_my_err_head, "my_err_head", 0},
  { &key_memory_my_file_info, "mysys_file_info", 0},
  { &key_memory_MY_DIR, "MY_DIR", 0},
  { &key_memory_MY_STAT, "MY_STAT", 0},
  { &key_memory_QUEUE, "QUEUE", 0},
  { &key_memory_DYNAMIC_STRING, "DYNAMIC_STRING", 0},
  { &key_memory_TREE, "TREE", 0}
};

void mysys_init_mysys_psi_keys()
{
  const char* category= "mysys";
  int count;

  count= sizeof(all_mysys_mutexes)/sizeof(all_mysys_mutexes[0]);
  mysql_mutex_register(category, all_mysys_mutexes, count);

  count= sizeof(all_mysys_rwlocks)/sizeof(all_mysys_rwlocks[0]);
  mysql_rwlock_register(category, all_mysys_rwlocks, count);

  count= sizeof(all_mysys_conds)/sizeof(all_mysys_conds[0]);
  mysql_cond_register(category, all_mysys_conds, count);

  count= sizeof(all_mysys_files)/sizeof(all_mysys_files[0]);
  mysql_file_register(category, all_mysys_files, count);

  count= array_elements(all_mysys_stages);
  mysql_stage_register(category, all_mysys_stages, count);

  count= array_elements(all_mysys_memory);
  mysql_memory_register(category, all_mysys_memory, count);
}
#endif /* HAVE_PSI_INTERFACE */

