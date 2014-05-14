#include "engine.h"
#include <math.h>

Engine *engine_create(int height,int width,int ups)
{
	//Allocate memory
	Engine *engine = (Engine*) malloc(sizeof(Engine));

	//Check if allocated
	if(engine == NULL)
		return NULL;

	//Init
	if(engine_init(engine, height, width, ups))
		return engine;
	else //If initialization failed
	{
		free(engine);
		return NULL;
	}
}

bool engine_init(Engine *engine, int height, int width, int ups)
{
	//If given dimensions greater the max dimensions, fail
	if(height > MAX_HEIGHT || width > MAX_WIDTH)
		return false;

	//Set matrix size
	engine->height = height;
	engine->width = width;

	//Init matrix to NULL
	int i, j;
	for(i = 0; i < height; i++)
		for(j = 0; j < width; j++)
			engine->entities[i][j] = NULL;

	//Init list and queue to NULL
	for(i = 0; i < MAX_ENTITIES; i++)
	{
		engine->e_list[i] = NULL;
		engine->e_queue[i] = NULL;
	}
	//Set game info
	engine->ups = ups;
	engine->n_entities = 0;
	engine->n_queue = 0;

	return true;
}

void engine_print_state(Engine *engine)
{
	printf("Engine info: \n");
	printf("\t->matrix size = %dx%d [hxw].\n",  engine->height, engine->width);
	printf("\t->Number of entities currently in the engine: %d.\n", engine->n_entities);
	printf("\t->Number of entities currently in the queue: %d.\n", engine->n_queue);
	printf("\t->Current ups: %d.\n", engine->ups);
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

void engine_update(Engine *engine)
{
	//Iterators
	int i, j;

	//Remove all the dead units
	for(i = 0; i < engine->n_entities; i++)
	{
		if(engine->e_list[i]->alive == false)	//If the entity is dead, remove it from the engine
		{
			engine_remove_entity(engine, engine->e_list[i]->x, engine->e_list[i]->y);
			i--;
		}
	}

	//Process queue
	engine_process_queue(engine);


	//Update all the coordinates
	for(i = 0; i < engine->height; i++)
		for(j = 0; j < engine->width; j++)
			engine_update_entity(engine, j, i);
}

void engine_update_entity(Engine *engine, int x, int y)
{
	//Iterators
	int i, j;

	//Holds the number of neighbours
	int n_neighbours = 0;

	//Count the neighbours
	for(i = -1; i <= 1; i++)
		for(j = -1; j <= 1; j++)
		{
			if(i == 0 && j == 0)
				continue;
			if(engine_is_correct(engine, x+j, y+i) && !engine_is_free(engine, x+j, y+i))
				n_neighbours++;

		}

	//Fetch the entity at the given coordinates
	Entity *entity = engine_get_entity(engine, x, y);

	//The logic
	if(entity == NULL)	//For a space that is 'empty' or 'unpopulated'
	{
		if(n_neighbours == 3) //Each cell with three neighbors becomes populated.
			engine_add_queue(engine, entity_create(x, y));	//Add a new entity to the queue at the current position
	} else //For a space that is 'populated':
	{
		if(n_neighbours < 2) //Each cell with one or no neighbors dies, as if by loneliness.
			entity->alive = false;	//signal the engine that the entity should be removed
		else if(n_neighbours >= 4) //Each cell with four or more neighbors dies, as if by overpopulation.
			entity->alive = false;	//signal the engine that the entity should be removed
		else	//Each cell with two or three neighbors survives. 
			entity->generation++;
	}
}

bool engine_add_queue(Engine *engine, Entity *entity)
{
	if(engine->n_queue+1 >= MAX_ENTITIES)
		return false;

	engine->e_queue[engine->n_queue++] = entity;

	return true;
}

void engine_process_queue(Engine *engine)
{
	//Add the entities in the queue to the engine
	int i;
	for(i = 0; i < engine->n_queue; i++)
	{
		engine_add_entity(engine, engine->e_queue[i]);
		engine->e_queue[i] = NULL;
	}

	engine->n_queue = 0;
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

bool engine_remove_entity(Engine *engine, int x, int y)
{
	//Check if there is an entity to remve
	if(engine_is_free(engine, x, y))
	{
		return false;
	}
	//Fetch the entity
	Entity *entity = engine->entities[y][x];

	//Remove from matrix
	engine->entities[y][x] = NULL;

	//Remove from list
	//Set the last element of the list in the soon to be removed entity pos
	engine->e_list[entity->e_id] = engine->e_list[engine->n_entities-1];
	engine->e_list[entity->e_id]->e_id = entity->e_id;
	engine->e_list[engine->n_entities-1] = NULL;
	engine->n_entities--;	//Update number of entities

	//Free entity memory
	free(entity);

	return true;
}

Entity *engine_get_entity(Engine *engine, int x, int y)
{
	if(!engine_is_correct(engine, x, y))
		return NULL;
	return engine->entities[y][x];
}

void engine_free(Engine *engine)
{
	engine_end(engine);
	free(engine);
}

void engine_end(Engine *engine)
{
	int i, j;
	
	//Free memory
	for(i = 0; i < engine->n_entities; i++)
		free(engine->e_list[i]);
	for(i = 0; i < engine->n_queue; i++)
		free(engine->e_queue[i]);

	//No dangling pointers pls
	for(i = 0; i < engine->n_entities; i++)
		engine->e_list[i] = NULL;
	for(i = 0; i < engine->n_queue; i++)
		engine->e_queue[i] = NULL;
	for(i = 0; i < engine->height; i++)
		for(j = 0; j < engine->width; j++)
			engine->entities[i][j] = NULL;
}

bool engine_save(Engine *engine, const char *savefile_name)
{	//TODO: refactor
	//Iterators
	int i, j;

	//Open file
	FILE *savefile = fopen(savefile_name, "wb");
	if(!savefile)
		return false;

	//Write dimentions
	fwrite(&engine->height, sizeof(int), 1, savefile);
	fwrite(&engine->width, sizeof(int), 1, savefile);	

	//Write game info
	fwrite(&engine->ups, sizeof(int), 1, savefile);
	fwrite(&engine->n_queue, sizeof(int), 1, savefile);

	//Write the queue(just the coordinates)
	for(i = 0; i < engine->n_queue; i++)
	{
		fwrite(&engine->e_queue[i]->x, sizeof(int), 1, savefile);
		fwrite(&engine->e_queue[i]->y, sizeof(int), 1, savefile);
	}

	//Write the current entities
	int exists = 1, nexists = 0;
	Entity *entity;
	for(i = 0; i < engine->height; i++)
		for(j = 0; j < engine->width; j++)
		{
			entity = engine_get_entity(engine, j, i);
			if(entity)
			{
				fwrite(&exists, 1, 1, savefile);
				if(entity->alive)
					fwrite(&exists, 1, 1, savefile);
				else
					fwrite(&nexists, 1, 1, savefile);
			}
			else
			{
				fwrite(&nexists, 1, 1, savefile);
				fwrite(&nexists, 1, 1, savefile);
			}
		}
	

	//Done
	fclose(savefile);
	return true;
}

Engine *engine_load(const char *savefile_name)
{	//TODO: refactor
	//Iterators
	int i, j;

	//Open file
	FILE *savefile = fopen(savefile_name, "rb");
	if(!savefile)
		return NULL;

	//Variables engine info will be temporarely stored
	int height, width;
	int ups, n_queue;

	//Read dimentions
	fread(&height, sizeof(int), 1, savefile);
	fread(&width, sizeof(int), 1, savefile);

	//Read game info
	fread(&ups, sizeof(int), 1, savefile);
	fread(&n_queue, sizeof(int), 1, savefile);

	//Create engine
	Engine *engine = engine_create(height, width, ups);
	if(!engine)
		return NULL;

	//Create the queue
	int x, y;
	for(i = 0; i < n_queue; i++)
	{	
		//Read coordinates from file
		fread(&x, sizeof(int), 1, savefile);
		fread(&y, sizeof(int), 1, savefile);

		//Add to queue
		engine_add_queue(engine, entity_create(x, y));
	}

	//Load entities
	int exists = 0;
	Entity *entity;
	for(i = 0; i < height; i++)
	{
		for(j = 0; j < width; j++)
		{
			fread(&exists, 1, 1, savefile);
			if(!exists)
			{
				fread(&exists, 1, 1, savefile);
				continue;
			}

			entity = entity_create(j, i);
			engine_add_entity(engine, entity);
			
			fread(&exists, 1, 1, savefile);
			
			entity->alive = exists;
		}
	}

	//Done
	fclose(savefile);	
	return engine;
}
