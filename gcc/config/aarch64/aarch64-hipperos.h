/* Definitions for AArch64 running HIPPEROS
   Copyright (C) 2018 Free Software Foundation, Inc.

   This file is part of GCC.

   GCC is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   GCC is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GCC; see the file COPYING3.  If not see
   <http://www.gnu.org/licenses/>.  */

#ifndef GCC_AARCH64_HIPPEROS_H
#define GCC_AARCH64_HIPPEROS_H

#if TARGET_FIX_ERR_A53_835769_DEFAULT
#define CA53_ERR_835769_SPEC \
  " %{!mno-fix-cortex-a53-835769:--fix-cortex-a53-835769}"
#else
#define CA53_ERR_835769_SPEC \
  " %{mfix-cortex-a53-835769:--fix-cortex-a53-835769}"
#endif

#if TARGET_FIX_ERR_A53_843419_DEFAULT
#define CA53_ERR_843419_SPEC \
  " %{!mno-fix-cortex-a53-843419:--fix-cortex-a53-843419}"
#else
#define CA53_ERR_843419_SPEC \
  " %{mfix-cortex-a53-843419:--fix-cortex-a53-843419}"
#endif

/*
 * Most of these translations are copied from the standard aarch64 file.
 */
#define HIPPEROS_TARGET_LINK_SPEC "%{h*}			\
   %{static:-Bstatic}				\
   %{shared:-shared}				\
   %{symbolic:-Bsymbolic}			\
   %{!static:%{rdynamic:-export-dynamic}}	\
   %{mbig-endian:-EB} %{mlittle-endian:-EL}"	\
  CA53_ERR_835769_SPEC \
  CA53_ERR_843419_SPEC

#undef  LINK_SPEC
#define LINK_SPEC HIPPEROS_TARGET_LINK_SPEC	\
                  HIPPEROS_LINK_SPEC	\
                  CA53_ERR_835769_SPEC	\
                  CA53_ERR_843419_SPEC

#define GNU_USER_TARGET_MATHFILE_SPEC \
  "%{Ofast|ffast-math|funsafe-math-optimizations:crtfastmath%O%s}"

#undef ENDFILE_SPEC
#define ENDFILE_SPEC \
    GNU_USER_TARGET_MATHFILE_SPEC " " \
    HIPPEROS_ENDFILE_SPEC

#endif /* GCC_AARCH64_HIPPEROS_H */
