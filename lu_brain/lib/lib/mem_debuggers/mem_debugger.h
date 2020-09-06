/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Mem_Debugger 

	struct mem_debugger {
		struct mem_debugger_interface 	super;

		
	};

	// Mem_Debugger doesn't use Mem for it's own allocations, using standard library instead
	Mem_Debugger mem_debugger_create(Mem mem_to_observe);
	void mem_debugger_destroy(Mem_Debugger self);

	void mem_debugger_print(Mem_Debugger self);
	void mem_debugger_print_and_destroy(Mem_Debugger self);