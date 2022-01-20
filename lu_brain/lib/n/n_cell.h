/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// N_Cell_0

	enum n_cell_type {
		N_CT__0,
		N_CT__VALUE,
		N_CT__1,
		N_CT__2,
		N_CT__3,
		N_CT__4
	};

	struct lu_n_cell_0 {
		lu_byte type;
	};
	
	static inline N_Cell_0 n_cell_0__init(N_Cell_0 self, lu_byte type)
	{
		lu__assert(self);
		self->type = type;

		return self;
	}

///////////////////////////////////////////////////////////////////////////////
// N_Cell_Value

	struct n_cell_value {
		struct lu_n_cell_0 super;

		lu_value value;
	};

///////////////////////////////////////////////////////////////////////////////
// N_Cell_1

	struct lu_n_cell_1 {
		struct lu_n_cell_0 super;

		N_Cell_0 top_left;
	};

	static inline N_Cell_1 n_cell_1__init(N_Cell_1 self, lu_byte type)
	{
		n_cell_0__init((N_Cell_0) self, type);

		self->top_left = NULL;

		return self;
	}

///////////////////////////////////////////////////////////////////////////////
// N_Cell_2

	struct lu_n_cell_2 {
		struct lu_n_cell_1 super;

		N_Cell_0 top_right;
	};

	static inline N_Cell_2 n_cell_2__init(N_Cell_2 self, lu_byte type)
	{
		n_cell_1__init((N_Cell_1) self, type);

		self->top_right = NULL;

		return self;
	}

///////////////////////////////////////////////////////////////////////////////
// N_Cell_3

	struct lu_n_cell_3 {
		struct lu_n_cell_2 super;

		N_Cell_0 bottom_left;
	};

	static inline N_Cell_3 n_cell_3__init(N_Cell_3 self, lu_byte type)
	{
		n_cell_2__init((N_Cell_2) self, type);

		self->bottom_left = NULL;

		return self;
	}

///////////////////////////////////////////////////////////////////////////////
// N_Cell_4

	struct lu_n_cell_4 {
		struct lu_n_cell_3 super;

		N_Cell_0 bottom_right;
	}; 

	static inline N_Cell_4 n_cell_4__init(N_Cell_4 self, lu_byte type)
	{
		n_cell_3__init((N_Cell_3) self, type);

		self->bottom_right = NULL;

		return self;
	}

///////////////////////////////////////////////////////////////////////////////
// Macro

	#define n_cell__type_get(c) (((N_Cell_0)c)->type)
	#define n_cell__top_left_get(c) (((N_Cell_0)c)->top_left)
	#define n_cell__top_right_get(c) (((N_Cell_2)c)->top_right)
	#define n_cell__bottom_left_get(c) (((N_Cell_3)c)->bottom_left)
	#define n_cell__bottom_right_get(c) (((N_Cell_4)c)->bottom_right)

///////////////////////////////////////////////////////////////////////////////
// Parent Equality

	static inline lu_bool n_cell__parent_eq_1(N_Cell_1 self, N_Cell_0 top_left)
	{
		return self->top_left == top_left;
	}

	static inline lu_bool n_cell__parent_eq_2(N_Cell_2 self, N_Cell_0 top_left, N_Cell_0 top_right)
	{
		return self->top_right == top_right && n_cell__parent_eq_1((N_Cell_1) self, top_left);
	}

	static inline lu_bool n_cell__parent_eq_3(N_Cell_3 self, N_Cell_0 top_left, N_Cell_0 top_right, N_Cell_0 bottom_left)
	{
		return self->bottom_left == bottom_left && n_cell__parent_eq_2((N_Cell_2) self, top_left, top_right);
	}

	static inline lu_bool n_cell__parent_eq_4(N_Cell_4 self, N_Cell_0 top_left, N_Cell_0 top_right, N_Cell_0 bottom_left, N_Cell_0 bottom_right)
	{
		self->bottom_right == bottom_right && n_cell__parent_eq_3((N_Cell_3) self, top_left, top_right, bottom_left);
	}