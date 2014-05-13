compile: bin bin/main.o bin/entity.o bin/engine.o bin/gof_screen.o bin/graphics.o
	gcc  bin/entity.o bin/main.o bin/engine.o bin/gof_screen.o bin/graphics.o -ogof -lm -lX11

bin: 
	mkdir bin/

bin/main.o: src/main.c
	gcc -o bin/main.o -c src/main.c

bin/entity.o: src/entity.c
	gcc -o bin/entity.o -c src/entity.c

bin/engine.o: src/engine.c
	gcc -o bin/engine.o -c src/engine.c

bin/gof_screen.o: src/gof_screen.c
	gcc -o bin/gof_screen.o -c src/gof_screen.c

bin/graphics.o: src/graphics.c
	gcc -o bin/graphics.o -c src/graphics.c

exec: compile
	./gof
