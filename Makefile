CC = g++ -Wall -lm
OBJS = main.o vec3.o ray.o material.o sphere.o triangle.o stb_image_write.o
.SUFFIXES: .c .o .h   # Define our suffix list

%.o: %.cpp
	$(CC) -c -o $@ $<

build: $(OBJS)
	$(CC) -o raytracer $(OBJS)

run: raytracer
	./raytracer

clean:
	rm *.o -f -v
	rm raytracer -v -f
