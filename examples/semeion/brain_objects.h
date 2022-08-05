
#include "semeion.h"
#include "semeion.c"


struct brain_objects {
	Lu_Brain brain;
	Lu_Rec rec;
	Lu_Wave save_wave;
	Lu_Wave match_wave;
}; 

typedef struct brain_objects* Brain_Objects;

static inline void brain_objects__init( 
	Brain_Objects self,
	struct lu_config config
)
{

	self->brain = lu_brain__create(config);
	lu__assert(self->brain);
	
	self->rec = lu_brain__rec_add(
		/*belongs to*/			self->brain, 
		/*width*/				8, 
		/*height*/				8, 
		/*depth*/				1,
		/*predefined config */ 	lu_rec_config__get_by_id(LU_REC__MONO1_IMAGE)
	);	
	lu__assert(self->rec);

	// After we added all recs we need to build/rebuild brain
	lu_brain__build(self->brain);

	// Create save_wave
	
	self->save_wave = lu_wave__create_save_wave(self->brain);
	lu__assert(self->save_wave);  

	self->match_wave = lu_wave__create_match_wave(self->brain);
	lu__assert(self->match_wave);
}

static inline void brain_objects__deinit(
	Brain_Objects self
)	
{
	lu__assert(self->brain);
	lu__assert(self->save_wave);
	lu__assert(self->match_wave);
	
	lu_wave__destroy(self->match_wave);
	lu_wave__destroy(self->save_wave);
	lu_brain__destroy(self->brain);
}
