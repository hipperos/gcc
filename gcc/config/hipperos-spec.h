/* Base configuration file for all Maestro targets.
   Copyright (C) 2018 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.

You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */

/*
 * Common Maestro configuration.
 * All Maestro architectures should include this file, which will specify
 * their commonalities.
 * Adapted from gcc/freebsd-spec.h
 */

#define HIPPEROS_TARGET_OS_CPP_BUILTINS() \
  do \
    { \
    builtin_define ("__hipperos__"); \
    builtin_define ("__maestro__"); \
  } \
  while (0)

/*
 * Note first that the start/end files are only included if neither
 * -nostdlib or -nostartfiles are provided.
 * Then in our case, crt0 is only provided if -maestro is not defined.
 * This is used to make compiler checks pass (in particular, the one executed
 * for the compilation of libstdc++).
 * Indeed, in crt0 (from Newlib) we have defined empty implementations of every
 * standard call supported by Maestro.
 * This is required as long as our libc depends on libapi.
 *
 * - crti.o: Defines the function prolog; _init in the .init section and _fini
 *      in the .fini section. glibc calls this 'initfini.c'.
 * - crtbegin.o (generated from crtstuff.c): support for getting C++ file-scope
 *      static object constructed before entering 'main'.
 * - crtend.o (generated from crtstuff.c): support for getting C++ file-scope
 *      static object constructed before entering 'main'.
 * - crtn.o: "Finalizer" file
 *
 * NOTE This is duplicated in the rs6000 port as ecrti.o (resp. ecrtn.o)
 *      replaces the usual crti.o (resp. crtn.o).
 *      See gcc/config/rs6000/sysv4.h
 */
#define HIPPEROS_STARTFILE_SPEC "%{!maestro: crt0%O%s} crti%O%s crtbegin%O%s"

#define HIPPEROS_ENDFILE_SPEC "crtend%O%s crtn%O%s"

/*
 * Some targets do not set up LIB_SPECS, override it, here.
 */
#define HIPPEROS_STD_LIB_SPEC ""

/*
 * Use with the libc only if -maestro has been provided.
 * This is required due to the dummy crt0 used to passe compiler checks.
 * Note that there is a cross-dependency between the libc depends and the libapi
 * that is not solved here.
 *
 * If -maestro-sl has been given, link with the kernel-specific build of
 * compiler-rt.
 */
#define HIPPEROS_LIB_SPEC \
    "%{!maestro: " HIPPEROS_STD_LIB_SPEC "} " \
    "%{!nostdlib: %{maestro: -lc %{maestro-sl: -lcompiler_rt_kernel}}}"

/*
 * -z max-page-size
 *   Defines the maximum page size to 4KB.
 * -z separate-code
 *   Put data and text in separate segments by default.
 * --gc-sections
 *   In combination with the compiler options "-ffunction-sections" and
 *   "-fdata-sections", this removes unused code/data.
 */
#define HIPPEROS_LINK_SPEC \
    "-z max-page-size=0x1000" \
    " -z separate-code" \
    " -static" \
    " --gc-sections" \
    " --no-dynamic-linker"
