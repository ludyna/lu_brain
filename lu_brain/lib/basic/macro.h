/**
	Copyright © 2022 Oleh Ihorovych Novosad
*/

///////////////////////////////////////////////////////////////////////////////
// 

#define lu_macro__value_in_2d_array(values, x, y, w) values[y * w + x]
#define lu_macro__value_in_3d_array(values, x, y, z, w, h) values[z * w * h + y * w + x]