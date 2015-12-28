all: fakemouse

fakemouse: mouseclick.o fakemouse.o
	gcc -lX11 -lncurses -L/usr/X11R6/lib/ -o $@ $?

fakemouse.o: fakemouse.c
	gcc -c -L/usr/X11R6/lib/ -o $@ $?

mouseclick.o: mouseclick.c
	gcc -c -L/usr/X11R6/lib -o $@ $?

clean:
	rm -f fakemouse mouseclick.o fakemouse.o

install: fakemouse
	cp fakemouse /usr/local/bin
