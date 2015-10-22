#include <iostream>

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
setupWorld() {

	// make a material which is reflective
	material refl;
	refl.reflective = 1;
	refl.color = vec3(0,0,0); // color is not used when material is reflective!
	// make several diffuse materials to choose from
	material red;
	red.reflective = 0;
	red.color = vec3(1,0,0);
	material blue;
	blue.reflective = 0;
	blue.color = vec3(0,0,1);
	material white;
	white.reflective = 0;
	white.color = vec3(1,1,1);
	// create three spheres
	sphere sph1;
	sph1.pos = vec3(0,0,-16);
	sph1.radius = 2;
	sph1.mat = refl;
	sphere sph2;
	sph2.pos = vec3(3,-1,-14);
	sph2.radius = 1;
	sph2.mat = refl;
	sphere sph3;
	sph3.pos = vec3(-3,-1,-14);
	sph3.radius = 1;
	sph3.mat = red;
	// back wall
	triangle back1;
	triangle_new(vec3(-8,-2,-20),
	vec3(8,-2,-20),
	vec3(8,10,-20), &back1);
	back1.mat = blue;
	triangle back2;
	triangle_new(vec3(-8,-2,-20),
	vec3(8,10,-20),
	vec3(-8,10,-20), &back2);
	back2.mat = blue;
	// floor
	triangle bot1;
	triangle_new(vec3(-8,-2,-20),
	vec3(8,-2,-10),vec3(8,-2,-20), &bot1);
	bot1.mat = white;
	triangle bot2;
	triangle_new(vec3(-8,-2,-20),
	vec3(-8,-2,-10),
	vec3(8,-2,-10), &bot2);
	bot2.mat = white;
	// right red triangle
	triangle right;
	triangle_new(vec3(8,-2,-20),
	vec3(8,-2,-10),
	vec3(8,10,-20), &right);
	right.mat = red;

}
