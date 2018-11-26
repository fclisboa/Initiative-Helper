all: p1 p2 p6 p4 p5 p7 p8 p9 p3

p1: src/mainwindow.cc src/mainwindow.h src/playerframe.h src/monsterframe.h src/lineentry.h
	g++ -c src/mainwindow.cc `pkg-config gtkmm-3.0 --cflags --libs`

p2: src/initiative.cc src/mainwindow.h
	g++ -c src/initiative.cc `pkg-config gtkmm-3.0 --cflags --libs`

p3: mainwindow.o initiative.o
	g++ mainwindow.o initiative.o playerframe.o monsterframe.o lineentry.o monsterentry.o monsterlist.o newmonstertemplate.o -o initiative_helper `pkg-config gtkmm-3.0 --cflags --libs`

p4: src/playerframe.cc src/playerframe.h
	g++ -c src/playerframe.cc `pkg-config gtkmm-3.0 --cflags --libs`

p5: src/monsterframe.cc src/monsterframe.h
	g++ -c src/monsterframe.cc `pkg-config gtkmm-3.0 --cflags --libs`

p6: src/lineentry.cc src/lineentry.h
	g++ -c src/lineentry.cc `pkg-config gtkmm-3.0 --cflags --libs`

p7: src/monsterlist.cc src/monsterlist.h
	g++ -c src/monsterlist.cc `pkg-config gtkmm-3.0 --cflags --libs`

p8: src/monsterentry.cc src/monsterentry.h
	g++ -c src/monsterentry.cc `pkg-config gtkmm-3.0 --cflags --libs`

p9: src/newmonstertemplate.cc src/newmonstertemplate.h
	g++ -c src/newmonstertemplate.cc `pkg-config gtkmm-3.0 --cflags --libs`

install: initiative_helper
	mkdir -p $(DESTDIR)
	cp $(SRCDIR)/initiative_helper $(DESTDIR)