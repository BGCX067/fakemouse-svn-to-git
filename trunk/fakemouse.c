#include <ncurses.h>
#include <X11/Xlib.h>
#include "fakemouse.h"

static WINDOW *mainwnd;
static WINDOW *screen;

void screen_init(void) {
	mainwnd = initscr();
	noecho();
	cbreak();
	keypad(screen, TRUE);	// FIXME
}

void screen_end(void) {
	endwin();
}

int main() {
	screen_init();
   	Display *display = XOpenDisplay(0);
	
	int delta_x, delta_y, delta = 16, x, do_exit = 0;

	while(1){
		delta_x = 0;
		delta_y = 0;

		x = getch();
		
//		printf("%i\n\r", x);
//

		switch(x){
			case ERR :
				do_exit = 1;
				break;
			case KEY_LEFT : case 'a':
				delta_x = -delta;
				break;
			case KEY_UP : case 'w':
				delta_y = -delta;
				break;
			case KEY_RIGHT : case 'd':
				delta_x = delta;
				break;
			case KEY_DOWN : case 's':
				delta_y = delta;
				break;
			case 'q':
				do_exit = 1;
				break;
			case ' ': case 'c':
				mouseClick(1);
				break;
			case '\\':
				mouseClick(3);
				break;
			case '-':
				delta /= 2;
				if(delta == 0) delta = 1;
				break;

			case '+': case '=':
				delta *= 2;
				break;
		}

		if(do_exit == 1) break;

		XWarpPointer(display, None, None, 0, 0, 0, 0, delta_x, delta_y);
    		
		XFlush(display);	
	}

	XCloseDisplay(display);
	screen_end();
    	return 0;
}
