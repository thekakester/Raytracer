CC = g++ -c -Wall
OBJS = main.o vec3.o

build: $(OBJS)
	g++ -o raytracer $(OBJS)

run: raytracer
	./raytracer

.c.o: vec3.cpp
	$(CC) -c vec3.cpp
clean:
	rm *.o -f
	rm raytracer
