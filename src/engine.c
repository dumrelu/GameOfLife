#include "engine.h"

void engine_init(Engine *engine, int height, int width, int ups)
{
	//Set matrix size
	engine->height = height;
	engine->width = width;

	//Init matrix to NULL
	int i, j;
	for(i = 0; i < height; i++)
		for(j = 0; j < width; j++)
			engine->entities[i][j] = NULL;

	//Init list to NULL
	for(i = 0; i < MAX_ENTITIES; i++)
		engine->e_list[i] = NULL;

	//Set game info
	engine->ups = ups;
	engine->n_entities = 0;
	engine->n_updates = 0;
}

void engine_print_state(Engine *engine)
{
	printf("Engine info: \n");
	printf("\t->matrix size = %dx%d [hxw].\n",  engine->height, engine->width);
	printf("\t->Number of entities currently in the engine: %d.\n", engine->n_entities);
	printf("\t->Current ups: %d. Total updates: %d.\n", engine->ups, engine->n_updates);
}

bool engine_is_correct(Engine *engine, int x, int y)
{
	if( x >= 0 && x < engine->width && y >= 0 && y < engine->height)
		return true;
	return false;
}

bool engine_is_free(Engine *engine, int x, int y)
{
	if(!engine_is_correct(engine, x, y))
		return false;
	return (engine->entities[y][x] == NULL);
}

bool engine_add_entity(Engine *engine, Entity *entity)
{
	//If no more free space left, don't add
	if(engine->n_entities+1 >= MAX_ENTITIES)
		return false;

	//If pos if not free, don't add
	if(!engine_is_free(engine, entity->x, entity->y))
		return false;

	//Add to the engine
	engine->entities[entity->y][entity->x] = entity;
	entity->e_id = engine->n_entities;
	engine->e_list[engine->n_entities++] = entity;

	//Entity added to the engine
	return true;
}
