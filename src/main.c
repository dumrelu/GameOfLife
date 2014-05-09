#include <stdio.h>
#include "engine.h"
#include <unistd.h>

int main(int argc, char *argv[])
{	
	//Prepare engine
	Engine *engine = engine_create(15, 16, 30);
	
	engine_add_entity(engine, entity_create(5, 3));
	engine_add_entity(engine, entity_create(4, 4));
	engine_add_entity(engine, entity_create(5, 4));
	engine_add_entity(engine, entity_create(6, 4));
	engine_add_entity(engine, entity_create(4, 5));
	engine_add_entity(engine, entity_create(6, 5));
	engine_add_entity(engine, entity_create(5, 6));

	//Print entities
	int i, j, g;
	for(g = 0; g < 10; g++)
	{
		for(i = 0; i < engine->height; i++)
		{
			for(j = 0; j < engine->width; j++)
				if(!engine_is_free(engine, j, i))
					printf("1");
				else 
					printf(" ");
			printf("\n");
		}
		engine_update(engine);
		printf("Saving: ");
		engine_print_state(engine);
		engine_save(engine, "testfile.sav");
		for(i = 0; i < engine->n_queue; i++)
			entity_printf(engine->e_queue[i]);
		engine_free(engine);
		printf("Loading: ");
		engine = engine_load("testfile.sav");
		engine_print_state(engine);
		for(i = 0; i < engine->n_queue; i++)
			entity_printf(engine->e_queue[i]);
		sleep(1);
	}

	//Free mem
	engine_free(engine);

	return 0;
}
