#undef NO_IMPLICIT_EXTERN_C
#define NO_IMPLICIT_EXTERN_C

#undef TARGET_HIPPEROS
#define TARGET_HIPPEROS 1

// #undef STARTFILE_SPEC
// #define STARTFILE_SPEC ""
//
// #undef ENDFILE_SPEC
// #define ENDFILE_SPEC   ""

#define STD_LIB_SPEC ""

// #undef LIBGCC_SPEC
// #define LIBGCC_SPEC ""

#undef LIB_SPEC
#define LIB_SPEC "%{!huser: " STD_LIB_SPEC "} " \
"%{!nostdlib: %{huser: --start-group -lapi -lcompiler_rt -lc --end-group}}"

#undef TARGET_OS_CPP_BUILTINS
#define TARGET_OS_CPP_BUILTINS() \
  do { \
    builtin_define ("__hipperos__"); \
  } while(0);
