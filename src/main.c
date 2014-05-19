#include <stdio.h>
#include "engine.h"
#include "gof_screen.h"
#include <unistd.h>
#include <time.h>
#include <ctype.h>

#define LEFT_ARROW 81
#define UP_ARROW 82
#define RIGHT_ARROW 83
#define DOWN_ARROW 84

Engine *prepare_game(char *save_name);

int main(int argc, char *argv[])
{	
	char input = 0;
	char save_name[50];


	//Prepare engine
	Engine *engine = prepare_game(save_name);

	GoF_Screen *screen = screen_create(0, 0, 30, 30, 20);
	Graphics g;
	graphics_init(&g, 800, 900, "The Game of Life!");

	input = 0;
	while(input != 'k')
	{
		screen_draw(screen, &g, engine);
		input = graphics_event(&g);

		if(input == 1)
			engine_add_entity(engine, entity_create(g.last_x/screen->entity_length, g.last_y/screen->entity_length));
		else if(input == 3)
			engine_remove_entity(engine, g.last_x/screen->entity_length, g.last_y/screen->entity_length);
	}

	//Input
	input = 0;
	int sens = 5;

	//Main game loop
	while(input != 'q')
	{	
		//Draw on screen
		screen_draw(screen, &g, engine);

		//Update Engine
		engine_update(engine);
		
		//Process input
		while(graphics_check_event(&g))
		{
			input = graphics_event(&g);
			switch(input)
			{
				case 'p':
					engine->ups++;
					break;
				case 'm':
					if(engine->ups > 1)
						engine->ups--;
					break;
				case '.':
					sens++;
					break;
				case ',':
					if(sens > 1)
						sens--;
					break;
				case UP_ARROW:
					screen->y -= sens;
					break;
				case DOWN_ARROW:
					screen->y += sens;
					break;
				case LEFT_ARROW:
					screen->x -= sens;
					break;
				case RIGHT_ARROW:
					screen->x += sens;
					break;
			}
		}

		//Sleep
		usleep((1000/engine->ups) * 1000);
	}

	//Close graphics
	graphics_close(&g);

	//Save game
	printf("Saving game...\n");
	engine_save(engine, save_name);

	//Free mem
	engine_free(engine);
	screen_free(screen);

	return 0;
}

Engine *prepare_game(char *save_name)
{
	char input;
	
	//Read option
	printf("Load save? [Y/n]: ");
	scanf("%c", &input);

	//Process
	if(toupper(input) == 'Y')
	{
		printf("Name of the save file to be loaded: ");
		scanf("%s", save_name);
		return engine_load(save_name);
	} else
	{
		printf("Name of the new save file: ");
		scanf("%s", save_name);
		
		int height, width, ups;
		
		printf("New engine:\n\t->height: ");
		scanf("%d", &height);

		printf("\t->width: ");
		scanf("%d", &width);

		printf("\t->ups: ");
		scanf("%d", &ups);

		return engine_create(height, width, ups);
	}
}
