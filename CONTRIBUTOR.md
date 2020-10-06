# lu_brain dev guide

## Modules and folder structures

TBD

## Prefixes

- All public or potentially public identifiers should start with prefixes `lu_` (methods, globals, structs), 
`LU_` (constants) or `Lu_` (pointers to public structs).

- All public files should start with prefix `lu_`.

- All NON public files should not have prefix `lu_`.

- There are special files: `__readme.md`, `_module.h`, `_module.lu` (or `_module.c`), and `_typedefs.h`

- `I_`, `Lu_I`, `i_`, `lu_i` prefixes are used for identifiers related to interface structures.

For data received from or passed to methods that are from outside libraries use types appropriate for 
these libraries. Don't assume lu_size is uint. "Wrap" these methods with our own methods when possible:

	#define lu_value_round round 
	#define lu_value_abs fabs


## NAMING 
---

Structs are named always lower case:

	struct lu_brain {

	};

	sizeof(struct lu_brain)

Pointers to struct always have first letter of every word capitalized and have underscore between words:
	
	Lu_Brain

We always know that Lu_Brain is actualy struct lu_brain* (pointer to struct lu_brain).

When method allocates memory and return lu_p_byte or lu_p_void pointer its name should end with "alloc". Opposite
to "alloc" is "free". 

	mem_instance_alloc()
	mem_instance_free()

When method allocates memory, potentially initiaze it and returns pointer to a struct its name should end with "create". 
Opposite to "create" is "destroy".

	mem_table_create()
	mem_table_destroy()

Initialiazators (initialize data structure but not allocate) look like this:

	mem_table_init()
	mem_table_deinit()

## Assertions

- Use `lu_user_assert(expression, message)` and `lu_user_assert_void(expression, message)` to validate/assert in bublic API methods.

- Use `lu_assert(expression)` to validate/assert in internal methods.






