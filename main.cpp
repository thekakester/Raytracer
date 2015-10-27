#include <iostream>
#include <vector>
#include <math.h>
#include "triangle.h"
#include "intersectable.h"
#include "sphere.h"
#include "vec3.h"
#include "ray.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define WIDTH 600
#define HEIGHT 600
#define FILENAME "output.png"

using namespace std;

//PROTOTYPES START
void traceRays();
void setupWorld();
Vec3 shootRay(Ray, int);
//PROTOTYPES END!

Vec3 cameraPosition = Vec3(0,0,0);
Vec3 light = Vec3(3,5,-15);
char image[WIDTH*HEIGHT*3];

vector<Intersectable*> objects;

int main() {
	cout << "Raytracer starting!\n";
	
	setupWorld();	//Execute Dr. Kuhl's code from the assignment
	cout << "World created!\n";
	cout << "Tracing rays...\n";

	traceRays();

    printf("\e[1ATracing rays... %d%%\n", 100);
    
	cout << "Done!\n";
	cout << "Saving image... ";
	stbi_write_png(FILENAME, WIDTH, HEIGHT, 3, image, WIDTH*3);
	cout << "Done!\nRaytracing complete!\n";
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
	refl.reflective = 0.5f;
	refl.color = Vec3(0,0,1); // color is not used when Material is reflective!

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
	
	//Light yellow!
	Material yellow;
	yellow.reflective = 0;
	yellow.color = Vec3(1,1,0);

	// create three Spheres
	Sphere* sph1 = new Sphere();
	sph1->pos = Vec3(0,0,-16);
	sph1->radius = 2;
	sph1->mat = refl;
	Sphere* sph2 = new Sphere();
	sph2->pos = Vec3(3,-1,-14);
	sph2->radius = 1;
	sph2->mat = refl;
	Sphere* sph3 = new Sphere();
	sph3->pos = Vec3(-3,-1,-14);
	sph3->radius = 1;
	sph3->mat = red;


	//Add a sphere at the light
	Sphere* lightSphere = new Sphere();
	lightSphere->pos = light;
	lightSphere->mat = yellow;
	lightSphere->radius = 0.05f;

	//Add the spheres to our vector
	//NOTE!  (Sphere at position 0 in vector does not have light act on it!)
	objects.push_back(lightSphere);
	objects.push_back(sph1);
	objects.push_back(sph2);
	objects.push_back(sph3);
	
	// back wall
	Triangle* back1 = new Triangle(Vec3(-8,-2,-20), Vec3(8,-2,-20), Vec3(8,10,-20));
	back1->mat = blue;
	Triangle* back2 = new Triangle(Vec3(-8,-2,-20), Vec3(8,10,-20), Vec3(-8,10,-20));
	back2->mat = blue;

	// floor
	Triangle* bot1 = new Triangle(Vec3(-8,-2,-20), Vec3(8,-2,-10), Vec3(8,-2,-20));
	bot1->mat = white;
	Triangle* bot2 = new Triangle(Vec3(-8,-2,-20), Vec3(-8,-2,-10), Vec3(8,-2,-10));
	bot2->mat = white;

	// right red Triangle
	Triangle* right = new Triangle(Vec3(8,-2,-20), Vec3(8,-2,-10), Vec3(8,10,-20));
	right->mat = red;

	//Add the triangles to our vector
	objects.push_back(back1);
	objects.push_back(back2);
	objects.push_back(bot1);
	objects.push_back(bot2);
	objects.push_back(right);
}

/****************************************************************
This actually runs the ray-tracing and saves the data to image[]
****************************************************************/
void traceRays() {
	for (int row = 0; row < HEIGHT; row++) {
		//For progress, print off percentage every few rows
		if (row % 20 == 0) {
		    printf("\e[1ATracing rays... %d%%\n", (int)((row*100.0f)/HEIGHT));
		}

		for (int col = 0; col < WIDTH; col++) {
			//Decides where in image[] to set data!
			int baseIndex = (row * WIDTH + col) * 3;
			
			//Image plane is at Z = -2, and has a width/height of 2/2
			//This means x and y coordinates range from -1 to 1
			//This means that we shoot a ray from camera position to the plane
			float xCoord = (((float)col / WIDTH ) * 2) - 1;	//Between -1 and 1
			float yCoord = (((float)row / HEIGHT) * 2) - 1;	//Between -1 and 1
			yCoord *= -1;	//Make sure to flip to handle rows
			float zCoord = -2.0f;
			
			//Create a point out of this data
			Vec3 imagePixel = Vec3(xCoord,yCoord,zCoord);
			
			//Create a ray from the camera to the imagePixel
			Ray ray = Ray(cameraPosition,imagePixel);

			//Recursively shoot ray and get back a color!
			//Pass in 0 to represent that we have performed 0 iterations so far
			Vec3 color = shootRay(ray,0);

			//Convert values of 0.0 to 1.0 to 0-255
			color.x *= 255;
			color.y *= 255;
			color.z *= 255;

			//Set the color for this pixel!
			image[baseIndex+0] = color.x;
			image[baseIndex+1] = color.y;
			image[baseIndex+2] = color.z;
			
		}
	}
}

/**Shoot a given ray at the scene and return
a color.  This is recursive, so it could potentially go deeper!
Only do up to 1000 recurses before deciding to return black!
**/
Vec3 shootRay(Ray ray, int iteration) {

	//If we recursed too many times
	if (iteration > 10) {
		return Vec3(0,0,0);		//Return black!
	}

	//Loop over every object and check for collision!
	for (unsigned int i = 0; i < objects.size(); i++) {
		Intersectable* object = objects.at(i);
		
		//printf("Ray/Sphere collision: Ray <%.2f,%.2f,%.2f><%.2f,%.2f,%.2f> Sphere[<%.2f,%.2f,%.2f> r:%.2f]\n",ray.origin.x, ray.origin.y, ray.origin.z, ray.direction.x, ray.direction.y, ray.direction.z, sphere.pos.x, sphere.pos.y, sphere.pos.z, sphere.radius);

		float d = object->intersectsRay(ray);
		if (d >= 0) {
			//Return the color of the sphere dotted with the normal
			Vec3 intersectionPoint = ray.pointAtDistance(d);

			//Calculate the normal of the sphere
			Vec3 normal = object->getNormal(intersectionPoint);

			//If we intersected with a reflective surface, bounce it!
			//TODO: Go above and beyond!  Let reflective be a percentage!
			Vec3 reflectiveColor = Vec3(0,0,0);
			
			//Only calculate if we are somewhat reflective
			if (object->mat.reflective > 0) {
				reflectiveColor = shootRay(ray.reflect(intersectionPoint,normal),iteration+1);
			}
			
			//Let "p" be the percentage of this reflection
			//Let "q" be 1-p
			//This will be "p" % whatever this color is
			//and q % regular diffuse!
			reflectiveColor.multiplyByScalar(object->mat.reflective);

			//printf("Intersect at point <%.2f,%.2f,%.2f>\n",intersectionPoint.x, intersectionPoint.y, intersectionPoint.z);
		
			//Check if we can see the light
			//Create a ray from the point to the light
			Ray rayToLight = Ray(intersectionPoint,light);

			bool seesLight = true;	//Set to false if intersects

			//Check if we hit anything
			for (unsigned int j = 1; j < objects.size(); j++) {
				if (i==j) { continue; }
				
				//If we intersect
				float dist = objects.at(j)->intersectsRay(rayToLight);
				if (dist >= 0) {
					seesLight = false; //We failed!
					break;
				}
			}

			//Its time to calculate the color to return

			//Ambient light!
			Vec3 ambience = object->mat.color.multiplyByScalar(0.2f);
			Vec3 diffuse = Vec3(0,0,0);

			if (seesLight) {
				//Dot the lightray with normal
				float correlation = normal.dot(rayToLight.direction);
				if (correlation < 0) { correlation = 0; }

				//Special case for calculating light
				//Ignire diffuse for the light in our scene
				if (i == 0) { correlation = 1; }				
	
				//Diffuse is 80%!
				diffuse = object->mat.color.multiplyByScalar(correlation * 0.8);
			}
			
			//The return color is:
			// Reflection + (diffuse + ambient)
			Vec3 returnColor = diffuse.add(ambience);
			
			//How much of an impact does reflection have on this?
			//(note, this does nothing if object is not reflective)
			returnColor = returnColor.multiplyByScalar(1 - object->mat.reflective);
			returnColor = returnColor.add(reflectiveColor);
			return returnColor;
		}
	}
	//Recurse!
	return shootRay(ray, iteration+1);
}
