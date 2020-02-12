
Any type or method that is visible to END users should start with "lu_" prefix. 
Typedefs of pointers for END users should be prefixed with "Lu_" (Lu_Brain, Lu_Neuron).

Prefixes "lu_", "Lu_" should be avoided in internal code. 
Exception are shared types defined in basic/lu_types.h). 
"LU_" is used in internal code as prefix to macroses (LU_NEU_H, LU_MEM_ALLOC_H).

I use "modular" folder structure:

	my_module
		src 
			my_something_1.lu
			my_something_2.lu
			my_module.lu

		my_module.h

Header file (always have main header file for module which has the same name as module folder) is included like this:
	
	#include "my_module/my_module.h"

Module source code is included down in source code hierarchy like this:

	#include "my_module/src/my_module.lu"

lu_brain is module itself which uses submodule brain.


