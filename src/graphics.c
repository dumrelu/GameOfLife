#include "graphics.h"

int graphics_init(Graphics *graphics, int height, int width, const char *window_name)
{
	//Save screen width and height
	graphics->wheight = height;
	graphics->wwidth = width;

	graphics->display = XOpenDisplay(0);
	if(!graphics->display)
		return 0;
	
	graphics->visual = DefaultVisual(graphics->display,0);
	if(!graphics->visual)
		return 0;

	int black = BlackPixel(graphics->display, DefaultScreen(graphics->display));
	graphics->window = XCreateSimpleWindow(graphics->display, DefaultRootWindow(graphics->display), 0, 0, width, height, 0, black, black);

	XSetWindowAttributes attr;
	attr.backing_store = Always;

	XChangeWindowAttributes(graphics->display,graphics->window,CWBackingStore,&attr);

	XStoreName(graphics->display,graphics->window,window_name);

	XSelectInput(graphics->display, graphics->window, StructureNotifyMask|KeyPressMask|ButtonPressMask);

	XMapWindow(graphics->display,graphics->window);

	graphics->gc = XCreateGC(graphics->display, graphics->window, 0, 0);

	graphics->colormap = DefaultColormap(graphics->display,0);

	int white = WhitePixel(graphics->display, DefaultScreen(graphics->display));
	XSetForeground(graphics->display, graphics->gc, white);

	for(;;) {
		XEvent e;
		XNextEvent(graphics->display, &e);
		if (e.type == MapNotify)
			break;
	}

	return 1;
}

void graphics_close(Graphics *graphics)
{
	XFreeGC(graphics->display, graphics->gc);
	XCloseDisplay(graphics->display);
}

void graphics_color(Graphics *graphics, unsigned char red, unsigned char green, unsigned char blue)
{
	XColor color;
	color.pixel = ((blue&0xff) | ((green&0xff)<<8) | ((red&0xff)<<16));
	XSetForeground(graphics->display, graphics->gc, color.pixel);
}


