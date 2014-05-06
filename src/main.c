#include <stdio.h>
#include "engine.h"

int main(int argc, char *argv[])
{
	Entity *entity = entity_create(1, 1);
	entity_printf(entity);
	
	Engine engine;
	engine_init(&engine, 10, 10, 30);

	engine_add_entity(&engine, entity);

	engine_print_state(&engine);

	entity_printf(entity);
	entity_printf(engine_get_entity(&engine, 1, 1));
	entity_printf(engine_get_entity(&engine, 2, 1));

	engine_remove_entity(&engine, 1, 1);

	engine_print_state(&engine);

	return 0;
}
