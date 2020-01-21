/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/
#ifndef _LU_ECS_H
#define _LU_ECS_H

///////////////////////////////////////////////////////////////////////////////
// Nouns

	typedef struct ecs* 		Ecs; 
	typedef struct entity* 		Entity;
	typedef struct component* 	Component;

///////////////////////////////////////////////////////////////////////////////
// Component

	struct component {
		Entity 			entity;
	};

///////////////////////////////////////////////////////////////////////////////
// Entity

	enum entity_flags {
		ENTITY_ACTIVE = 1,
	};

	struct entity {	
		Ecs 			ecs;
		Arr 			components;
		lu_flags		flags; 
	};

	Entity entity_create(Ecs);
	void entity_destroy(Entity*);

	//entity_append(

	static inline lu_p_void entity_get(Entity self, lu_size index)
	{
		return arr_get(self->components, index);
	}

///////////////////////////////////////////////////////////////////////////////
// ECS

	struct ecs {
		//Sis_Alloc 		entities; 
		Arr 			systems; // SOA
	};

	//
	// systems_size potentially could be greater than components_size but usually (not required) not
	// less than components_size
	//
	Ecs ecs_create(lu_size components_size, lu_size systems_size);
	void ecs_destroy(Ecs*);

	void ecs_component_type_append(Ecs self, lu_size soa_index, lu_size component_size, lu_size components_size);

	void ecs_components_each(Ecs self, lu_size components_index, void (*block)(lu_p_void));
	void ecs_components_each_1p(
		Ecs self, lu_size components_index, 
		void (*block)(lu_p_void, lu_p_void p1), 
		lu_p_void p1
	);
	void ecs_components_each_2p(
		Ecs self, 
		lu_size components_index, 
		void (*block)(lu_p_void, lu_p_void p2), 
		lu_p_void p1, 
		lu_p_void p2
	);


#endif // _LU_ECS_H