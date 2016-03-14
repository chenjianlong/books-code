
// -*- C++ -*-
// $Id$
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl CLD
// ------------------------------
#ifndef CLD_EXPORT_H
#define CLD_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (CLD_HAS_DLL)
#  define CLD_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && CLD_HAS_DLL */

#if !defined (CLD_HAS_DLL)
#  define CLD_HAS_DLL 1
#endif /* ! CLD_HAS_DLL */

#if defined (CLD_HAS_DLL) && (CLD_HAS_DLL == 1)
#  if defined (CLD_BUILD_DLL)
#    define CLD_Export ACE_Proper_Export_Flag
#    define CLD_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define CLD_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* CLD_BUILD_DLL */
#    define CLD_Export ACE_Proper_Import_Flag
#    define CLD_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define CLD_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* CLD_BUILD_DLL */
#else /* CLD_HAS_DLL == 1 */
#  define CLD_Export
#  define CLD_SINGLETON_DECLARATION(T)
#  define CLD_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* CLD_HAS_DLL == 1 */

// Set CLD_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (CLD_NTRACE)
#  if (ACE_NTRACE == 1)
#    define CLD_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define CLD_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !CLD_NTRACE */

#if (CLD_NTRACE == 1)
#  define CLD_TRACE(X)
#else /* (CLD_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define CLD_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (CLD_NTRACE == 1) */

#endif /* CLD_EXPORT_H */

// End of auto generated file.
