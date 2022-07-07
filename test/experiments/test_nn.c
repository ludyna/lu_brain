/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

#include "unity.h"
#include "lib/_module.h"

///////////////////////////////////////////////////////////////////////////////
// Typedefs

	#define LINKS__SIZE 64
	#define T_LAYER__D_SIZE 10
	#define LAYERS__SIZE 4
	#define LAYERS__LABELS_SIZE 512

	typedef struct t_cell* T_Cell;
	typedef struct t_link* T_Link;
	typedef struct t_layer* T_Layer;

///////////////////////////////////////////////////////////////////////////////
// T_Link

	struct t_link {
		T_Cell links[LINKS__SIZE];
		lu_size links_count;

		// debug
		char name[25];
	};

	static inline T_Link t_link__init(T_Link self, const char* str)
	{
		lu__assert(self);

		self->links_count = 0;
		strcpy(self->name, str);

		return self;
	}

	static inline void t_link__add(T_Link self, T_Cell cell)
	{
		lu__assert(self->links_count + 1 < LINKS__SIZE);

		self->links[self->links_count] = cell;
		++self->links_count;
	}

	static inline void t_link__fire(T_Link self, lu_value sig, lu_size wave_id, T_Cell source);

///////////////////////////////////////////////////////////////////////////////
// T_Cell

	struct t_cell {

		struct t_link labels;

		struct t_link tl;
		struct t_link tr;
		struct t_link bl;
		struct t_link br;

		struct t_link children;

		lu_value sig;
		lu_size wave_id;
		lu_value mult;

		// debug info
		lu_size layer_ix;
		lu_size x;
		lu_size y;
		lu_size z;
	};

	static inline void t_cell__reset_sig(T_Cell self)
	{
		lu__assert(self);

		self->sig = 0;
		self->wave_id = LU__SIZE_MAX; 
		self->mult = 1;
	}

	static inline T_Cell t_cell__init(
		T_Cell self,
		lu_size layer_ix,
		lu_size x,
		lu_size y,
		lu_size z
	)
	{
		lu__assert(self);

		t_link__init(&self->labels, "labels");

		t_link__init(&self->tl, "tl");
		t_link__init(&self->tr, "tr");
		t_link__init(&self->bl, "bl");
		t_link__init(&self->br, "br");

		t_link__init(&self->children, "children");

		t_cell__reset_sig(self);

		self->layer_ix = layer_ix;
		self->x = x;
		self->y = y;
		self->z = z;

		return self;
	}

	static inline void t_cell__add_sig(T_Cell self, lu_value sig, lu_size wave_id)
	{
		lu__assert(self);

		if (self->wave_id != wave_id)
		{
			self->sig = 0;
		}
		
		if (self->children.links_count > 0)
		{
			sig /= self->children.links_count; //1/4 always
		}

		self->wave_id = wave_id;

		//lu__debug("\nadd sig = %.2f", sig);
		self->sig += sig; 
	}

	static inline void t_cell__fire(T_Cell self, lu_size wave_id)
	{
		lu__assert(self);

		if (self->wave_id != wave_id) return;

		t_link__fire(&self->labels, self->sig, self->wave_id, self);
		t_link__fire(&self->tl, self->sig, self->wave_id, self);
		t_link__fire(&self->tr, self->sig, self->wave_id, self);
		t_link__fire(&self->bl, self->sig, self->wave_id, self);
		t_link__fire(&self->br, self->sig, self->wave_id, self);
	}

	static inline void t_cell__connect_4_to_1(T_Cell c1, T_Cell c2, T_Cell c3, T_Cell c4, T_Cell p)
	{
		lu__assert(c1);
		lu__assert(c2);
		lu__assert(c3);
		lu__assert(c4);
		lu__assert(p);

		t_link__add(&p->children, c1);
		t_link__add(&p->children, c2);
		t_link__add(&p->children, c3);
		t_link__add(&p->children, c4);

		t_link__add(&c1->tl, p);
		t_link__add(&c2->tr, p);
		t_link__add(&c3->bl, p);
		t_link__add(&c4->br, p);
	} 

	static inline void t_cell__connect_1_to_1(T_Cell c1, T_Cell p)
	{
		lu__assert(c1);
		lu__assert(p);

		t_link__add(&p->children, c1);
		t_link__add(&c1->tl, p);
	} 

	static inline void t_cell__connect_label(T_Cell self, T_Cell label)
	{
		lu__assert(self);
		lu__assert(label);

		t_link__add(&self->labels, label);
	}

	static inline void t_cell__print(T_Cell self)
	{
		lu__debug(
			"\nCELL LAYER_ID: %ld, xyz=(%ld, %ld, %ld), sig=%.2f, wave_id=%ld, children_count=%ld", 
			self->layer_ix,
			self->x,
			self->y,
			self->z,
			self->sig,
			self->wave_id,
			self->children.links_count
		);
	}

///////////////////////////////////////////////////////////////////////////////
// T_Link Methods


	static inline void t_link__fire(T_Link self, lu_value sig, lu_size wave_id, T_Cell source)
	{
		lu__assert(self);

		T_Cell cell;
		for (lu_size i = 0; i < self->links_count; i++)
		{
			cell = self->links[i];
			lu__assert(cell);

			lu__debug(
				"\nFIRING %s [%ld](%ld,%d,%d, links=%ld, s=%.2f, w=%ld) =>[%ld](%ld,%d,%d, s=%.2f, w=%ld)", 
				self->name,
				source->layer_ix,
				source->x,
				source->y,
				source->z,
				source->children.links_count,
				sig,
				wave_id,
				cell->layer_ix,
				cell->x,
				cell->y,
				cell->z,
				cell->sig,
				cell->wave_id

			);

			t_cell__add_sig(cell, sig, wave_id);

			lu__debug(
				" RES =>[%ld](%ld,%d,%d, links=%ld, s=%.2f, w=%ld)", 
				cell->layer_ix,
				cell->x,
				cell->y,
				cell->z,
				cell->children.links_count,
				cell->sig,
				cell->wave_id
			);
		}

	}

///////////////////////////////////////////////////////////////////////////////
// T_Layer

	struct t_layer {
		struct t_cell* cells;

		lu_size w;
		lu_size h;
		lu_size d;

		lu_size layer_ix;
	};

	static inline T_Layer t_layer__init(T_Layer self, lu_size w, lu_size h, lu_size d, lu_size layer_ix)
	{
		lu__assert(self);
		lu__assert(w > 0);
		lu__assert(h > 0);
		lu__assert(d > 0);

		self->w = w;
		self->h = h;
		self->d = d;
		self->layer_ix = layer_ix;

		lu_size whd = self->w * self->h * self->d;

		self->cells = (struct t_cell*) lu_mem__alloc(lu_g_mem, sizeof(struct t_cell) * whd);
		lu__assert(self->cells);

		T_Cell cell;
		lu_size x;
		lu_size y;
		lu_size z;

		for (z = 0; z < self->d; z++)
		{
			for (y = 0; y < self->h; y++)
			{
				for (x = 0; x < self->w; x++)
				{
					cell = &self->cells[z * self->w * self->h + y * self->w + x];

					t_cell__init(cell, self->layer_ix, x, y, z);
				}
			}
		}

		return self;
	}

	static inline void t_layer__deinit(T_Layer self)
	{
		lu__assert(self);
		lu__assert(self->cells);

		lu_mem__free(lu_g_mem, (lu_p_byte) self->cells);
		self->cells = NULL;
	}

	static inline T_Cell t_layer__get_cell(T_Layer self, lu_size x, lu_size y, lu_size z)
	{
		lu__assert(self);
		lu__assert(x < self->w);
		lu__assert(y < self->h);
		lu__assert(z < self->d);

		return &self->cells[z * self->h * self->w + y * self->w + x];
	}

	static inline void t_layer__connect_4_1(
		T_Layer self, 
		T_Layer p_layer, 
		lu_size x_1, lu_size y_1, lu_size z_1,
		lu_size x_2, lu_size y_2, lu_size z_2,
		lu_size x_3, lu_size y_3, lu_size z_3,
		lu_size x_4, lu_size y_4, lu_size z_4,
		lu_size x_p, lu_size y_p, lu_size z_p
	)
	{
		T_Cell c_1 = t_layer__get_cell(self, x_1, y_1, z_1);
		T_Cell c_2 = t_layer__get_cell(self, x_2, y_2, z_2);
		T_Cell c_3 = t_layer__get_cell(self, x_3, y_3, z_3);
		T_Cell c_4 = t_layer__get_cell(self, x_4, y_4, z_4);

		T_Cell p = t_layer__get_cell(p_layer, x_p, y_p, z_p);

		t_cell__connect_4_to_1(c_1, c_2, c_3, c_4, p);
	}

	static inline void t_layer__connect_1_1(
		T_Layer self, 
		T_Layer p_layer, 
		lu_size x_1, lu_size y_1, lu_size z_1,
		lu_size x_p, lu_size y_p, lu_size z_p
	)
	{
		T_Cell c_1 = t_layer__get_cell(self, x_1, y_1, z_1);

		T_Cell p = t_layer__get_cell(p_layer, x_p, y_p, z_p);

		t_cell__connect_1_to_1(c_1, p);
	}

	static inline void t_layer__reset_sig(T_Layer self)
	{
		lu__assert(self);

		lu_size size = self->w * self->h * self->d;

		T_Cell cell;
		for (lu_size i = 0; i < size; i++)
		{
			cell = &self->cells[i];

			t_cell__reset_sig(cell);
		}
	}

	////
	// Important
	static inline void t_layer__set_sig(
		T_Layer self, 
		lu_value sig, 
		lu_size wave_id,
		lu_size x_1, lu_size y_1, lu_size z_1
	)
	{
		T_Cell c_1 = t_layer__get_cell(self, x_1, y_1, z_1);
		t_cell__add_sig(c_1, sig, wave_id);
	}

	static inline void t_layer__fire(T_Layer self, lu_size wave_id)
	{
		lu__assert(self);

		lu_size size = self->w * self->h * self->d;

		T_Cell cell;
		for (lu_size i = 0; i < size; i++)
		{
			cell = &self->cells[i];

			t_cell__fire(cell, wave_id);
		}
	}

	static inline void t_layer__print(T_Layer self, lu_size x_1, lu_size y_1, lu_size z_1)
	{  
		lu__assert(self);

		T_Cell c_1 = t_layer__get_cell(self, x_1, y_1, z_1);
		lu__assert(c_1);

		t_cell__print(c_1);
	}


///////////////////////////////////////////////////////////////////////////////
// Data

	Lu_Mem_Debugger md;

	struct t_layer layers[LAYERS__SIZE];
	struct t_layer labels;

///////////////////////////////////////////////////////////////////////////////
// Layers 

	static inline void layers__init()
	{
		T_Layer layer;

		lu_size w = 4;
		lu_size h = 4; 
		for (lu_size i = 0; i < LAYERS__SIZE; i++)
		{
			layer = &layers[i];
			t_layer__init(layer, w, h, T_LAYER__D_SIZE, i);
			--w;
			--h;
		}

		lu__assert(w == 0);
		lu__assert(h == 0);

		t_layer__init(&labels, LAYERS__LABELS_SIZE, 1, 1, 69);
	}

	static inline void layers__deinit()
	{
		t_layer__deinit(&labels);

		T_Layer layer;
		for (lu_size i = 0; i < LAYERS__SIZE; i++)
		{
			layer = &layers[i];
			t_layer__deinit(layer);
		}
	}

	static inline void layers__reset_sig()
	{
		T_Layer layer;
		for (lu_size i = 0; i < LAYERS__SIZE; i++)
		{
			layer = &layers[i];
			t_layer__reset_sig(layer);
		}
	}

	////
	// Very nonoptimal fire
	static inline void layers__fire(lu_size wave_id)
	{
		T_Layer layer;
		for (lu_size i = 0; i < LAYERS__SIZE; i++)
		{
			layer = &layers[i];
			t_layer__fire(layer, wave_id);
		}
	}

///////////////////////////////////////////////////////////////////////////////
// Labels

	static inline void labels__connect(lu_size label_ix, T_Layer layer, lu_size x_1, lu_size y_1, lu_size z_1)
	{
		lu__assert(layer);

		T_Cell c_1 = t_layer__get_cell(layer, x_1, y_1, z_1);
		T_Cell label_cell = t_layer__get_cell(&labels, label_ix, 0, 0);

		t_cell__connect_label(c_1, label_cell);
	}

	static inline void labels__print(lu_size wave_id)
	{
		lu__debug("\n\nLABELS for wave_id = %ld: ", wave_id);

		lu_size size = labels.w * labels.h * labels.d;

		T_Cell cell;
		for (lu_size i = 0; i < size; i++)
		{
			cell = &labels.cells[i];

			if (cell->wave_id == wave_id)
			{
				lu__debug("\n	LABEL %ld SIG: %.2f", i, cell->sig);
			}
		}
	}
	
///////////////////////////////////////////////////////////////////////////////
// Setup

	// setUp is executed for each test, even if test does nothing
	void setUp(void)
	{ 
		md = lu_mem_debugger__create(lu_g_mem);
		TEST_ASSERT(md);

		layers__init();
	}

	void tearDown(void)
	{	
		layers__deinit();

		lu_mem_debugger__print(md);

		TEST_ASSERT(lu_mem_debugger__is_all_freed(md));
	    lu_mem_debugger__destroy(md, true);
	}

///////////////////////////////////////////////////////////////////////////////
// Tests

	void test_nn_simple(void)
	{
		t_layer__connect_4_1(
			&layers[0],
			&layers[1],

			1, 1, 0,
			2, 1, 0,
			1, 2, 0,
			2, 2, 0,

			1, 1, 0
		);

		labels__connect(0, &layers[1], 1, 1, 0);

		t_layer__connect_4_1(
			&layers[0],
			&layers[1],
			
			1, 1, 0,
			2, 1, 1,
			1, 2, 0,
			2, 2, 0,

			1, 1, 1
		);

		labels__connect(1, &layers[1], 1, 1, 1);

		t_layer__connect_1_1(
			&layers[0],
			&layers[1],
			
			1, 1, 0,

			1, 1, 2
		);

		labels__connect(2, &layers[1], 1, 1, 2);

		//
		// 33 
		//

		t_layer__set_sig(&layers[0], 1.0, 33, 1, 1, 0);
		t_layer__set_sig(&layers[0], 1.0, 33, 2, 1, 0);
		t_layer__set_sig(&layers[0], 1.0, 33, 1, 2, 0);
		t_layer__set_sig(&layers[0], 1.0, 33, 2, 2, 0);

		layers__fire(33);

		labels__print(33);

		//
		// 34
		//

		t_layer__set_sig(&layers[0], 1.0, 34, 1, 1, 0);

		layers__fire(34);

		labels__print(34);

		t_layer__print(&layers[1], 1, 1, 0);
		t_layer__print(&layers[1], 1, 1, 1);
		t_layer__print(&layers[1], 1, 1, 2);

	}