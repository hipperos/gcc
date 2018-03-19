#undef NO_IMPLICIT_EXTERN_C
#define NO_IMPLICIT_EXTERN_C

#undef TARGET_HIPPEROS
#define TARGET_HIPPEROS 1

#undef TARGET_OS_CPP_BUILTINS
#define TARGET_OS_CPP_BUILTINS() \
  do { \
    builtin_define ("__hipperos__"); \
  } while(0);
