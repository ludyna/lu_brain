# lu_brain dev guide


## PREFIXES

- All public or potentially public identifiers should start with prefixes `lu_` (methods, globals, structs), 
`LU_` (constants) or `Lu_` (pointers to public structs).

- All public files should start with prefix `lu_`.

- All NON public files should not have prefix `lu_`.

- There are special files: `__readme.md`, `_module.h`, `_module.lu` (or `_module.c`), and `_typedefs.h`

- `I_`, `Lu_I`, `i_`, `lu_i` prefixes are used for identifiers related to interface structures.

For data received from or passed to methods that are from outside libraries use types appropriate for 
these libraries. Don't assume lu_size is uint. "Wrap" these methods with our own methods when possible:

	#define lu_round round 
	#define lu_value_abs fabs

## NAMING 
---

We use most readable and the best naming convention I know which is "snake". 

Structs are named always lower case:

	struct lu_brain {

	};

	sizeof(struct lu_brain)

Pointers to struct always have first letter of every word capitalized and have underscore between words:
	
	Lu_Brain

We always know that Lu_Brain is actualy "struct lu_brain* " (pointer to struct lu_brain).

We always typedef pointers to structs to avoid using * (star) :

typedef struct lu_brain* Lu_Brain;

This makes code much more readable.

When method allocates memory and return lu_p_byte or lu_p_void pointer its name should end with "alloc". Opposite
to "alloc" is "free". 

	mem_instance_alloc()
	mem_instance_free()

When method allocates memory, potentially initiaze it and returns pointer to a struct its name should end with "create". 
Opposite to "create" is "destroy".

	Mem_Table mem_table_create(...);
	void mem_table_destroy(Mem_Table self);

When creation of object(struct) is "controlled" by other object (other than Mem) you can also use spawn() and die():

	N_Cell n_cell_spawn(Hnn self, lu_size type); // here N_Cell creation is controlled by Hnn object
	void n_cell_die(N_self, N_Cell cell);

Initialiazators (initialize data structure but not allocate) look like this:

	mem_table_init()
	mem_table_deinit()

## OBJECTS



## Assertions

- Use `lu_user_assert(expression, message)` and `lu_user_assert_void(expression, message)` to validate/assert in bublic API methods.

- Use `lu_assert(expression)` to validate/assert in internal methods.


## COMMENTS



## MODULES

TBD