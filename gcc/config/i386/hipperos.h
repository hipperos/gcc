/* Definitions for Intel 386 running HIPPEROS with ELF format.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

/* The ELF ABI for the i386 says that records and unions are returned
   in memory.  */

#define SUBTARGET_RETURN_IN_MEMORY(TYPE, FNTYPE) \
	(TYPE_MODE (TYPE) == BLKmode \
	 || (VECTOR_MODE_P (TYPE_MODE (TYPE)) && int_size_in_bytes (TYPE) == 8))

/* Override the default comment-starter of "/".  */
#undef  ASM_COMMENT_START
#define ASM_COMMENT_START "#"

#undef  ASM_APP_ON
#define ASM_APP_ON "#APP\n"

#undef  ASM_APP_OFF
#define ASM_APP_OFF "#NO_APP\n"

#undef DBX_REGISTER_NUMBER
#define DBX_REGISTER_NUMBER(n) \
  (TARGET_64BIT ? dbx64_register_map[n] : svr4_dbx_register_map[n])

#undef  NO_PROFILE_COUNTERS
#define NO_PROFILE_COUNTERS	1

/* Tell final.c that we don't need a label passed to mcount.  */

#undef  MCOUNT_NAME
#define MCOUNT_NAME ".mcount"

/* Make gcc agree with <machine/ansi.h>.  */

#undef  SIZE_TYPE
#define SIZE_TYPE	(TARGET_64BIT ? "long unsigned int" : "unsigned int")

#undef  PTRDIFF_TYPE
#define PTRDIFF_TYPE	(TARGET_64BIT ? "long int" : "int")

#undef  WCHAR_TYPE_SIZE
#define WCHAR_TYPE_SIZE	(TARGET_64BIT ? 32 : BITS_PER_WORD)

/* Use the STARTFILE_SPEC from config/hipperos-spec.h.  */
#undef  STARTFILE_SPEC
#define STARTFILE_SPEC HIPPEROS_STARTFILE_SPEC

/* Use the ENDFILE_SPEC from config/hipperos-spec.h.  */
#undef  ENDFILE_SPEC
#define ENDFILE_SPEC HIPPEROS_ENDFILE_SPEC

/* Use the ENDFILE_SPEC from config/hipperos-spec.h.  */
#undef LINK_SPEC
#define LINK_SPEC HIPPEROS_LINK_SPEC

/*
 * Everything from here has been copied from i386elf.h
 *
 * This is required as we want to avoid compiler warnings dues to the
 * redefinition of the *_SPEC macros.
 */

/* The routine used to output sequences of byte values.  We use a special
   version of this for most svr4 targets because doing so makes the
   generated assembly code more compact (and thus faster to assemble)
   as well as more readable.  Note that if we find subparts of the
   character sequence which end with NUL (and which are shorter than
   ELF_STRING_LIMIT) we output those using ASM_OUTPUT_LIMITED_STRING.  */

#undef ASM_OUTPUT_ASCII
#define ASM_OUTPUT_ASCII(FILE, STR, LENGTH)				\
  do									\
    {									\
      const unsigned char *_ascii_bytes =				\
        (const unsigned char *) (STR);					\
      const unsigned char *limit = _ascii_bytes + (LENGTH);		\
      unsigned bytes_in_chunk = 0;					\
      for (; _ascii_bytes < limit; _ascii_bytes++)			\
	{								\
	  const unsigned char *p;					\
	  if (bytes_in_chunk >= 64)					\
	    {								\
	      fputc ('\n', (FILE));					\
	      bytes_in_chunk = 0;					\
	    }								\
	  for (p = _ascii_bytes; p < limit && *p != '\0'; p++)		\
	    continue;							\
	  if (p < limit && (p - _ascii_bytes) <= (long) ELF_STRING_LIMIT) \
	    {								\
	      if (bytes_in_chunk > 0)					\
		{							\
		  fputc ('\n', (FILE));					\
		  bytes_in_chunk = 0;					\
		}							\
	      ASM_OUTPUT_LIMITED_STRING ((FILE), (const char *) _ascii_bytes); \
	      _ascii_bytes = p;						\
	    }								\
	  else								\
	    {								\
	      if (bytes_in_chunk == 0)					\
		fputs (ASM_BYTE, (FILE));				\
	      else							\
		fputc (',', (FILE));					\
	      fprintf ((FILE), "0x%02x", *_ascii_bytes);			\
	      bytes_in_chunk += 5;					\
	    }								\
	}								\
      if (bytes_in_chunk > 0)						\
	fputc ('\n', (FILE));						\
    }									\
  while (0)

#define LOCAL_LABEL_PREFIX	"."

/* Switch into a generic section.  */
#define TARGET_ASM_NAMED_SECTION  default_elf_asm_named_section

#undef BSS_SECTION_ASM_OP
#define BSS_SECTION_ASM_OP "\t.section\t.bss"

#undef ASM_OUTPUT_ALIGNED_BSS
#define ASM_OUTPUT_ALIGNED_BSS(FILE, DECL, NAME, SIZE, ALIGN) \
  asm_output_aligned_bss (FILE, DECL, NAME, SIZE, ALIGN)
