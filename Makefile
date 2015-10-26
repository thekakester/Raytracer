CC = g++
FLAGS = -Wall -std=c++11 -lm
OBJS = vec3.o ray.o material.o sphere.o triangle.o stb_image_write.o main.o
.SUFFIXES: .c .o .h   # Define our suffix list

%.o: %.cpp %.h intersectable.h
	$(CC) $(FLAGS) -c -o $@ $<

build: $(OBJS)
	$(CC) $(FLAGS) -o raytracer $(OBJS)

main.o: main.cpp
	g++ -Wall -std=c++11 -lm -c -o main.o main.cpp

run: raytracer
	./raytracer

clean:
	rm *.o -f -v
	rm raytracer -v -f
	rm output.png -v -f
