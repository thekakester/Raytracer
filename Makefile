CC = g++ -Wall
OBJS = main.o vec3.o material.o sphere.o triangle.o

build: $(OBJS)
	$(CC) -o raytracer $(OBJS)

run: raytracer
	./raytracer

.c.o: vec3.cpp
	$(CC) -c vec3.cpp
clean:
	rm *.o -f
	rm raytracer
