#ifndef GOF_SCREEN_H
#define GOF_SCREEN_h

#include "engine.h"
#include "graphics.h"
#include <stdlib.h>

typedef struct 
{
	//Screen starting coordinates
	int x;
	int y;

	//Screen dimensions
	int height;
	int width;
	
	//Entity dimension
	int entity_length;
} GoF_Screen;

//Allocate memory and create screen
GoF_Screen *screen_create(
	int x, int y,
	int height, int width,
	int entity_length
);

void screen_draw(
	GoF_Screen *screen, 
	Graphics *g, 
	Engine *engine
);

//Free memory
void screen_free(
	GoF_Screen *screen
);


#endif /*GOF_SCREEN_H*/
