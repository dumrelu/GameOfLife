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

void graphics_background(Graphics *graphics, unsigned char red, unsigned char green, unsigned char blue)
{
	XColor color;
	color.pixel = 0;
	color.red = red<<8;
	color.green = green<<8;
	color.blue = blue<<8;
	XAllocColor(graphics->display, graphics->colormap, &color);

	XSetWindowAttributes attr;
	attr.background_pixel = color.pixel;
	XChangeWindowAttributes(graphics->display, graphics->window, CWBackPixel,&attr);
}

void graphics_clear_screen(Graphics *graphics)
{
	XClearWindow(graphics->display,graphics->window);
}

void graphics_flush(Graphics *graphics)
{
	XFlush(graphics->display);
}

int graphics_check_event(Graphics *graphics)
{
	XEvent e;

	if(XCheckMaskEvent(graphics->display,-1,&e)) {
		if(e.type==KeyPress) {
			XPutBackEvent(graphics->display,&e);
				return 1;
		} else if (e.type==ButtonPress) {
			XPutBackEvent(graphics->display,&e);
   				return 1;
		} else
			return 0;
       }
}

char graphics_event(Graphics *graphics)
{
	XEvent e;

	XNextEvent(graphics->display,&e);

	if(e.type==KeyPress) {
		graphics->last_x = e.xkey.x;
		graphics->last_y = e.xkey.y;
		return XLookupKeysym(&e.xkey,0);
	} else if(e.type==ButtonPress) {
		graphics->last_x = e.xkey.x;
		graphics->last_y = e.xkey.y;
		return e.xbutton.button;
	}

	return -1;
}
