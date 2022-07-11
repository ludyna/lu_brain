/**
	Copyright © 2022 Oleh Ihorovych Novosad
*/

///////////////////////////////////////////////////////////////////////////////
// 

#define lu_macro__xy_to_ix(x, y, w) y * w + x
#define lu_macro__xyz_to_ix(x, y, z, w, h) z * w * h + y * w + x
#define lu_macro__value_in_2d_array(values, x, y, w) values[lu_macro__xy_to_ix(x, y, w)]
#define lu_macro__value_in_3d_array(values, x, y, z, w, h) values[lu_macro__xyz_to_ix(x, y, z, w, h)]