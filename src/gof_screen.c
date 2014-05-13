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
	int actual_en_length = screen->entity_length - 2, i, j;

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

	//Set entity draw color
	graphics_color(g, 0, 255, 0);

	//Draw entities
	for(i = screen->y; i < screen->height; i++)
		for(j = screen->x; j < screen->width; j++)
			if(!engine_is_free(engine, j, i))
				graphics_draw_fill_rect(g, j*screen->entity_length+1, i*screen->entity_length+1, actual_en_length, actual_en_length);

	//Flush graphics
	graphics_flush(g);
}

void screen_free(GoF_Screen *screen)
{
	free(screen);
}
