/**
	Copyright © 2020 Oleh Ihorovych Novosad 

	ECS is Entity Component System which is optimized for speed 
	(not normalized) database in memory similar to relational databases.

	Ideally component dont need to have reference to entity. Component should 
	have everything system needs even if it means data is repeated.

	Ideally entity should not have list of components. All work should be done 
	at system levels. Ideally components should just have entity_id.
*/
#ifndef _LU_ECS_DB_H
#define _LU_ECS_DB_H

// ///////////////////////////////////////////////////////////////////////////////
// // Nouns

// 	typedef struct ecs* 		Ecs; 
// 	typedef struct entity* 		Entity;
// 	typedef struct component* 	Component;

// ///////////////////////////////////////////////////////////////////////////////
// // Component

// 	struct record {
		
// 	};

// ///////////////////////////////////////////////////////////////////////////////
// // Entity_+

// 	struct table {	

// 	};

// 	Entity entity_create(Ecs);
// 	void entity_destroy(Entity*);

// 	//entity_append(

// 	static inline lu_p_void entity_get(Entity self, lu_size index)
// 	{
// 		return arr_get(self->components, index); 
// 	}

// ///////////////////////////////////////////////////////////////////////////////
// // ECS

// 	struct ecs_db {
// 		//Sis_Alloc 		entities; 
// 		Arr 			tables; // SOA, Ideally we should be able to get components by entity ID?
// 	};

// 	//
// 	// systems_size potentially could be greater than components_size but usually (not required) not
// 	// less than components_size
// 	//
// 	Ecs ecs_create(lu_size components_size, lu_size systems_size);
// 	void ecs_destroy(Ecs*);

// 	void ecs_component_type_append(
// 		Ecs self, 
// 		lu_size soa_index, 
// 		lu_size component_size, 
// 		lu_size components_size
// 	);

// 	void ecs_components_each(Ecs self, lu_size components_index, void (*block)(lu_p_void));
// 	void ecs_components_each_1p(
// 		Ecs self, lu_size components_index, 
// 		void (*block)(lu_p_void, lu_p_void p1), 
// 		lu_p_void p1
// 	);
// 	void ecs_components_each_2p(
// 		Ecs self, 
// 		lu_size components_index, 
// 		void (*block)(lu_p_void, lu_p_void p2), 
// 		lu_p_void p1, 
// 		lu_p_void p2
// 	);


#endif // _LU_ECS_H