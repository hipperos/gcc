/*
 * Common Maestro configuration.
 * All Maestro architectures should include this file, which will specify
 * their commonalities.
 * Adapted from gcc/freebsd.h
 */

/* In case we need to know.  */
#undef TARGET_HIPPEROS
#define TARGET_HIPPEROS 1

#undef  TARGET_OS_CPP_BUILTINS
#define TARGET_OS_CPP_BUILTINS() HIPPEROS_TARGET_OS_CPP_BUILTINS()

#undef  STARTFILE_SPEC
#define STARTFILE_SPEC HIPPEROS_STARTFILE_SPEC

#undef  ENDFILE_SPEC
#define ENDFILE_SPEC HIPPEROS_ENDFILE_SPEC

#undef  LIB_SPEC
#define LIB_SPEC HIPPEROS_LIB_SPEC

/************************[  Target stuff  ]***********************************/

/* All Maestro Architectures support the ELF object file format.  */
#undef  OBJECT_FORMAT_ELF
#define OBJECT_FORMAT_ELF

/* Don't assume anything about the header files.  */
#undef  NO_IMPLICIT_EXTERN_C
#define NO_IMPLICIT_EXTERN_C	1

/* Prefer int for int32_t (see stdint-newlib.h).  */
#undef STDINT_LONG32
#define STDINT_LONG32 (INT_TYPE_SIZE != 32 && LONG_TYPE_SIZE == 32)
