/**
	Copyright © 2020 Oleh Ihorovych Novosad 

	test_brain tests internal stuff related to brain top layer code.
	Dont use Lu_ for nouns (pointers to structs) or lu_ for methods here.
*/

#include "unity.h"
#include "brain/brain.h"



void setUp(void)
{ 

}

void tearDown(void)
{	

}

void sleep(lu_size t)
{

}

void test_brain_create_destroy(void) 
{
	Brain_Opts 	brain_opts = brain_opts_create(1, 512);
	Brain brain = brain_create(brain_opts);

	brain_destroy(brain);
	brain_opts_destroy(brain_opts);
}