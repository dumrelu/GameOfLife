compile: bin bin/main.o bin/entity.o bin/engine.o
	gcc  bin/entity.o bin/main.o bin/engine.o -ogof -lm

bin: 
	mkdir bin/

bin/main.o: src/main.c
	gcc -o bin/main.o -c src/main.c

bin/entity.o: src/entity.c
	gcc -o bin/entity.o -c src/entity.c

bin/engine.o: src/engine.c
	gcc -o bin/engine.o -c src/engine.c

exec: compile
	./gof
