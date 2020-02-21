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


I use "modular" folder structure:

	my_module
		src 
			my_module.lu
			my_something_1.lu
			my_something_2.lu


		my_module.h

Header file (always have main header file for module which has the same name as module folder) is included like this:
	
	#include "my_module/my_module.h"

Module source code is included down in source code hierarchy like this:

	#include "my_module/src/my_module.lu"

lu_brain is module itself which uses submodule brain.

src folders should not have subdirectory with src name directly. 

	src
		src

	Above is wrong and should not exist.

But you can have something like this

	my_module
		src 
			my_module_2
				src
					my_module_2.lu
				my_module_2.h
				my_something_2.h
			my_src_subfolder
				my_src_1.lu
				my_src_2.lu
				my_src_subfolder.lu

			my_module.lu

		my_module.h
		my_something.h
		my_something_3.h

As a result we have module my_module that uses one sub-module my_module_2 and source sublfolder my_src_subfolder.
What is difference between my_module_2 and my_src_subfolder? The last one doesn't have header files and therefore is 
directly included in my_module.lu.

Files my_something.h and my_something_3.h should be included in my_module.h, otherwise why are they there?

File my_something_2.h should be included in my_module_2.h

File my_module_2.h should be inclueded in my_module.h

Files my_src_1.lu and my_src_2.lu should be included in my_src_subfolder.lu.

Files my_module_2.lu and my_src_subfolder.lu should be included in my_module.lu.

Source sub-folders like my_src_subfolder should not have src folder. src folder should be in modules only.

In short, modules have top-level header files and top-level src folder, source sub-folders don't have top-level header files and top-level src folders.



