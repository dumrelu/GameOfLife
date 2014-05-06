#include <stdio.h>
#include "engine.h"

int main(int argc, char *argv[])
{	
	//Prepare engine
	Engine engine;
	engine_init(&engine, 10, 10, 30);
	
	//Prepare some entities
	Entity *entity1 = entity_create(0, 0);
	Entity *entity2 = entity_create(1, 0);
	Entity *entity3 = entity_create(0, 4);

	//Add them to the engine
	engine_add_entity(&engine, entity1);
	engine_add_entity(&engine, entity2);
	engine_add_entity(&engine, entity3);

	//Testing game logic
	engine_update_entity(&engine, 1, 0);

	//Print entities
	int i, j;
	for(i = 0; i < engine.height; i++)
	{
		for(j = 0; j < engine.width; j++)
			if(!engine_is_free(&engine, j, i))
				printf("1");
			else 
				printf(" ");
		printf("\n");
	}

	entity_printf(entity2);

	//Free mem
	engine_free(&engine);

	return 0;
}
