#include "gof_screen.h"

GoF_Screen *screen_create(int x, int y,int height, int width,int entity_length)
{
	//Allocate memory
	GoF_Screen *screen = (GoF_Screen*) malloc(sizeof(GoF_Screen));

	//Set info
	screen->x = x;
	screen->y = y;
	screen->height = height;
	screen->width = width;
	screen->entity_length = entity_length;
}

void screen_draw(GoF_Screen *screen, Graphics *g, Engine *engine)
{	//TODO: refactor
	int a_l = screen->entity_length - 2, i, j;

	//Set background color
	graphics_background(g, 41, 64, 60);

	//Set grid color
	graphics_color(g, 255, 0, 0);

	//Clear screen
	graphics_clear_screen(g);
	
	//Draw vertical lines
	int start_x, end_x;
	for(i = 0; i <= screen->width; i++)
	{
		end_x = start_x = i * screen->entity_length;
		graphics_draw_line(g, start_x, 0, end_x, screen->height * screen->entity_length);
	}

	//Draw horizontal lines
	int start_y, end_y;
	for(i = 0; i <= screen->height; i++)
	{
		start_y = end_y = i * screen->entity_length;
		graphics_draw_line(g, 0, start_y, screen->width * screen->entity_length, end_y);
	}

	//Draw entities
	int x, y;
	int last_type = -1;
	for(i = 0; i < screen->height; i++)
		for(j = 0; j < screen->width; j++)
		{
			x = j+screen->x;
			y = i+screen->y;

			if(engine_is_correct(engine, x, y))
			{
				if(!engine_is_free(engine, x, y))
				{
					if(last_type != 1) {
						graphics_color(g, 0, 255, 0);
						last_type = 1;
					}
					graphics_draw_fill_rect(g, j*screen->entity_length+1, i*screen->entity_length+1, a_l, a_l);
				}
			}
			else
			{
				if(last_type != 2) {
					graphics_color(g, 255, 0, 0);
					last_type = 2;
				}
				graphics_draw_fill_rect(g, j*screen->entity_length+1, i*screen->entity_length+1, a_l, a_l);
			}
		}
			

	//Text color
	graphics_color(g, 0, 0, 255);

	//Write info
	char info[50];
	sprintf(info, "Number of entities: %d / %d", engine->n_entities, MAX_ENTITIES);
	graphics_draw_string(g, screen->width * screen->entity_length + 10, 10, info);

	sprintf(info, "Number of entities in queue: %d / %d", engine->n_queue, MAX_ENTITIES);
	graphics_draw_string(g, screen->width * screen->entity_length + 10, 30, info);

	sprintf(info, "Current FPS: %d", engine->ups);
	graphics_color(g, 255, 236, 139);
	graphics_draw_string(g, screen->width * screen->entity_length + 10, 50, info);
}

void screen_free(GoF_Screen *screen)
{
	free(screen);
}
