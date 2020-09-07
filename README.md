# lu_brain dev guide

- All public or potentially public identifiers should start with prefixes `lu_` (methods, globals, structs), 
`LU_` (constants) or `Lu_` (pointers to public structs).

- All public files should start with prefix `lu_`.

- All NON pulblic files should not have prefix `lu_`.

- There are special files: `__readme.md`, `_module.h`, `_module.lu` (or `_module.c`), and `_typedefs.h`