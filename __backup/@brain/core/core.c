/**
	Copyright © 2019 Oleh Ihorovych Novosad
*/

#include <stdio.h>
#include <stdlib.h>
#include "@brain/core/core.h"

Core core_create(lu_size synapse_buff_size, lu_size neuron_buff_size, lu_size wave_buff_size, lu_size processor_buff_size)
{
	Core self = (Core) malloc(sizeof(struct core));
	lu_assert(self != NULL);

	self->neus 		= sis_alloc_create(neuron_buff_size, sizeof(struct neu));
	self->lins 		= sis_alloc_create(synapse_buff_size, sizeof(struct lin));
	self->waves		= sis_alloc_create(wave_buff_size, sizeof(struct wave));
	self->proc	  	= processor_create(processor_buff_size);

	neu_time_init(&self->t);

	return self;
}

void core_destroy(Core* self)
{
	sis_alloc_destroy(&(*self)->lins);
	sis_alloc_destroy(&(*self)->neus);
	sis_alloc_destroy(&(*self)->waves);
	processor_destroy(&(*self)->proc);

	lu_free((void **) self);
	lu_assert(*self == NULL);
}

Neu core_neu_alloc(Core self)
{
	Neu neu = (Neu) sis_alloc_item_alloc(self->neus);
	//neu_init_default(neu);
	return neu;
}

Lin core_lin_alloc(Core self)
{ 
	Lin lin = (Lin) sis_alloc_item_alloc(self->lins);
	lin_init_default(lin);
	return lin;
}
