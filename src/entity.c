#include "entity.h"

Entity *entity_create(int x, int y)
{
	//Alloc mem
	Entity *entity = (Entity*) malloc( sizeof(Entity) );

	//Set data
	entity->x = x;
	entity->y = y;
	entity->e_id = -1;
	entity->alive = true;
	entity->generation = 1;
}

void entity_printf(Entity *entity)
{
	if(entity == NULL)
		printf("Entity(NULL)\n");
	else
		printf("Entity(x=%d, y=%d, state=%s, e_id=%d, gen=%d)\n", entity->x, entity->y, (entity->alive) ? "alive" : "dead", entity->e_id, entity->generation);
}
