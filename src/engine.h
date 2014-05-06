#ifndef ENGINE_H
#define ENGINE_H

#include <stdio.h>
#include <stdlib.h>
#include "entity.h"

#define MAX_HEIGHT 100
#define MAX_WIDTH 100
#define MAX_ENTITIES 50

typedef struct {
	//Dimensions
	int height;
	int width;

	//Matrix of entities
	Entity *entities[MAX_HEIGHT][MAX_WIDTH];

	//List of entities
	Entity *e_list[MAX_ENTITIES];

	//Game info
	int ups;	//Updates/sec
	int n_entities;	//Current number of entities in the game
	int n_updates;	//Number of updates
} Engine;


//Initialize the engine with the given parameters
void engine_init(
	Engine *engine, 
	int height, 
	int width, 
	int ups
);

//Prints the current state of the engine
void engine_print_state(
	Engine *engine
);

//Checks if the given coordinates are valid
bool engine_is_correct(
	Engine *engine, 
	int x, 
	int y
);

//Checks if the given position is free(no other entity is on there)
bool engine_is_free(
	Engine *engine,
	int x, 
	int y
);

//Add an entity in the engine
bool engine_add_entity(
	Engine *engine, 
	Entity *entity
);

//Removes an entity from the engine + frees entity memory TODO: more tests
bool engine_remove_entity(
	Engine *engine, 
	int x,
	int y
);

//TODO: engine_get_entity

//Free all the memory used	TODO:
void engine_free(
	Engine *engine
);

#endif /*ENGINE_H*/
