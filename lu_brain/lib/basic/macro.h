/**
	Copyright © 2022 Oleh Ihorovych Novosad
*/

///////////////////////////////////////////////////////////////////////////////
// 

#define lu_macro__values_2d(values, x, y, w, h) values[y * w + x]
#define lu_macro__values_3d(values, x, y, z, w, h, d) values[z * w * h + y * w + x]