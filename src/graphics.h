#ifndef GOF_GRAPHICS_H
#define GOF_GRAPHICS_H

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	Display *display;
	Window window;
	GC gc;
	Colormap colormap;
	Visual *visual;
	int last_x;
	int last_y;
	int wheight;
	int wwidth;
} Graphics;

//Init xlib
int graphics_init(Graphics *graphics, int height, int width, const char *window_name);

//Clean up
void graphics_close(Graphics *graphics);

//Set drawing color
void graphics_color(Graphics *graphics, unsigned char red, unsigned char green, unsigned char blue);

//Set background color
void graphics_background(Graphics *graphics, unsigned char red, unsigned char green, unsigned char blue);

//Clear screen
void graphics_clear_screen(Graphics *graphics);

//Flush output to screen
void graphics_flush(Graphics *graphics);

//Had an event occured? TODO
int graphics_check_event(Graphics *graphics);

//Get the event TODO
char graphics_event(Graphics *graphics);

//Draw point TODO
void graphics_draw_point(Graphics *graphics, int x, int y);

//Draw line TODO
void graphics_draw_line(Graphics *graphics, int x1, int y1, int x2, int y2);

//Draw rect TODO
void graphics_draw_rect(Graphics *graphics, int x, int y, int height, int width);

//Draw fill rect TODO
void graphics_draw_fill_rect(Graphics *graphics, int x, int y, int height, int width);

//TODO: images

#endif /*GOF_GRAPHICS_H*/
