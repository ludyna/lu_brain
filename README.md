# lu_brain dev guide

## Prefixes

- All public or potentially public identifiers should start with prefixes `lu_` (methods, globals, structs), 
`LU_` (constants) or `Lu_` (pointers to public structs).

- All public files should start with prefix `lu_`.

- All NON public files should not have prefix `lu_`.

- There are special files: `__readme.md`, `_module.h`, `_module.lu` (or `_module.c`), and `_typedefs.h`

- `I_`, `Lu_I`, `i_`, `lu_i` prefixes are used for identifiers related to interface structures.

## Assertions

- Use `lu_user_assert(expression, message)` and `lu_user_assert_void(expression, message)` to validate/assert in bublic API methods.

- Use `lu_assert(expression)` to validate/assert in internal methods.