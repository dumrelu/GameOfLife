#include <stdio.h>
#include "engine.h"
#include <unistd.h>

int main(int argc, char *argv[])
{	
	//Prepare engine
	Engine engine;
	engine_init(&engine, 15, 15, 30);
	
	engine_add_entity(&engine, entity_create(5, 3));
	engine_add_entity(&engine, entity_create(4, 4));
	engine_add_entity(&engine, entity_create(5, 4));
	engine_add_entity(&engine, entity_create(6, 4));
	engine_add_entity(&engine, entity_create(4, 5));
	engine_add_entity(&engine, entity_create(6, 5));
	engine_add_entity(&engine, entity_create(5, 6));

	//Print entities
	int i, j, g;
	for(g = 0; g < 30; g++)
	{
		engine_update(&engine);
		for(i = 0; i < engine.height; i++)
		{
			for(j = 0; j < engine.width; j++)
				if(!engine_is_free(&engine, j, i))
					printf("1");
				else 
					printf(" ");
			printf("\n");
		}
		sleep(1);
	}

	//entity_printf(entity2);

	//Free mem
	engine_free(&engine);

	return 0;
}
