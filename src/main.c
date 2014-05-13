#include <stdio.h>
#include "engine.h"
#include "gof_screen.h"
#include <unistd.h>

int main(int argc, char *argv[])
{	
	//Prepare engine
	//engine_save(engine, "glider.sav");
	Engine *engine = engine_load("glider.sav");

	GoF_Screen *screen = screen_create(0, 0, 30, 30, 20);
	Graphics g;
	graphics_init(&g, 800, 800, "The Game of Life!");

	screen_draw(screen, &g, engine);	

	//Print entities
	/*int i, j, g;
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
		sleep(1);
	}*/

	char input = 0;
	while(input != 'q')
	{
		screen_draw(screen, &g, engine);

		sleep(1);

		engine_update(engine);
		
		if(graphics_check_event(&g))
			input = graphics_event(&g);
	}

	//Free mem
	engine_free(engine);
	screen_free(screen);
	graphics_close(&g);

	return 0;
}

//Engine *engine = engine_create(30, 30, 30);
	
	/*
	engine_add_entity(engine, entity_create(5+10, 3+10));
	engine_add_entity(engine, entity_create(4+10, 4+10));
	engine_add_entity(engine, entity_create(5+10, 4+10));
	engine_add_entity(engine, entity_create(6+10, 4+10));
	engine_add_entity(engine, entity_create(4+10, 5+10));
	engine_add_entity(engine, entity_create(6+10, 5+10));
	engine_add_entity(engine, entity_create(5+10, 6+10));
	

	engine_add_entity(engine, entity_create(15, 15));
	engine_add_entity(engine, entity_create(16, 16));
	engine_add_entity(engine, entity_create(16, 17));
	engine_add_entity(engine, entity_create(15, 17));
	engine_add_entity(engine, entity_create(14, 17));*/
