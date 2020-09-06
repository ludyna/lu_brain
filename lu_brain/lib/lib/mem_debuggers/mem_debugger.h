/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Mem_Debugger 

	struct md_item {
		lu_p_byte 	address;
		
	};

	struct mem_debugger {
		struct i_mem_debugger 	super;

		
	};

	Mem_Debugger mem_debugger_create();
	void mem_debugger_destroy(Mem_Debugger self);

	void mem_debugger_print(Mem_Debugger self);
	void mem_debugger_print_and_destroy(Mem_Debugger self);