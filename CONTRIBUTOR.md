FOR CONTRIBUTORS
===

TYPES
---

Any type or method that is visible to END users should start with "lu_" prefix. 
Typedefs of pointers for END users should be prefixed with "Lu_" (Lu_Brain, Lu_Neuron).

Prefixes "lu_", "Lu_" should be avoided in internal code. 
Exception are shared types defined in basic/lu_types.h). 
"LU_" is used in internal code as prefix to macroses (LU_NEU_H, LU_MEM_ALLOC_H).

For data received from or passed to methods that are from outside libraries use types appropriate for 
these libraries. Don't assume lu_size is uint. "Wrap" these methods with our own methods when possible:

	#define lu_value_round round 
	#define lu_value_abs fabs

NAMING 
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



FOLDER STRUCTURE
---





