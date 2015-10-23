#include <iostream>
#include "triangle.h"
#include "sphere.h"
#include "vec3.h"


using namespace std;

void setupWorld();

int main() {
	cout << "Raytracer started!\n";
	
	setupWorld();	//Execute Dr. Kuhl's code from the assignment

}

/*********************************************
The code posted on canvas.
This will setup the world for the assignment
Only minor adjustments were made in this code
to make it compatable with our classes
**********************************************/
void setupWorld() {

	// make a Material which is reflective
	Material refl;
	refl.reflective = 1;
	refl.color = Vec3(0,0,0); // color is not used when Material is reflective!

	// make several diffuse Materials to choose from
	Material red;
	red.reflective = 0;
	red.color = Vec3(1,0,0);
	Material blue;
	blue.reflective = 0;
	blue.color = Vec3(0,0,1);
	Material white;
	white.reflective = 0;
	white.color = Vec3(1,1,1);

	// create three Spheres
	Sphere sph1;
	sph1.pos = Vec3(0,0,-16);
	sph1.radius = 2;
	sph1.mat = refl;
	Sphere sph2;
	sph2.pos = Vec3(3,-1,-14);
	sph2.radius = 1;
	sph2.mat = refl;
	Sphere sph3;
	sph3.pos = Vec3(-3,-1,-14);
	sph3.radius = 1;
	sph3.mat = red;

	// back wall
	Triangle back1 = Triangle(Vec3(-8,-2,-20), Vec3(8,-2,-20), Vec3(8,10,-20));
	back1.mat = blue;
	Triangle back2 = Triangle(Vec3(-8,-2,-20), Vec3(8,10,-20), Vec3(-8,10,-20));
	back2.mat = blue;

	// floor
	Triangle bot1 = Triangle(Vec3(-8,-2,-20), Vec3(8,-2,-10), Vec3(8,-2,-20));
	bot1.mat = white;
	Triangle bot2 = Triangle(Vec3(-8,-2,-20), Vec3(-8,-2,-10), Vec3(8,-2,-10));
	bot2.mat = white;

	// right red Triangle
	Triangle right = Triangle(Vec3(8,-2,-20), Vec3(8,-2,-10), Vec3(8,10,-20));
	right.mat = red;
}
