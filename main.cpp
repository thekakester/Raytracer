#include <iostream>
#include <vector>
#include "triangle.h"
#include "sphere.h"
#include "vec3.h"
#include "ray.h"
#include "math.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define WIDTH 1400
#define HEIGHT 900
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

vector<Sphere> spheres;
vector<Triangle> triangles;

int main() {
	cout << "Raytracer starting!\n";
	
	setupWorld();	//Execute Dr. Kuhl's code from the assignment
	cout << "World created!\n";
	cout << "Tracing rays... ";

	traceRays();

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
	refl.reflective = 1;
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


	//Add a sphere at the light
	Sphere lightSphere;
	lightSphere.pos = light;
	lightSphere.mat = yellow;
	lightSphere.radius = 0.05f;

	//Add the spheres to our vector
	//NOTE!  (Sphere at position 0 in vector does not have light act on it!)
	spheres.push_back(lightSphere);
	spheres.push_back(sph1);
	spheres.push_back(sph2);
	spheres.push_back(sph3);
	
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

	//Add the triangles to our vector
	triangles.push_back(back1);
	triangles.push_back(back2);
	triangles.push_back(bot1);
	triangles.push_back(bot2);
	triangles.push_back(right);
}

/****************************************************************
This actually runs the ray-tracing and saves the data to image[]
****************************************************************/
void traceRays() {
	for (int row = 0; row < HEIGHT; row++) {
		//For progress, print off percentage every few rows
		if (row % 20 == 0) {
			cout << (row*100.0f)/HEIGHT << "%\n";
		}

		for (int col = 0; col < WIDTH; col++) {
			//Decides where in image[] to set data!
			int baseIndex = (row * WIDTH + col) * 3;
			
			//Image plane is at Z = -2, and has a width/height of 2/2
			//This means x and y coordinates range from -1 to 1
			//This means that we shoot a ray from camera position to the plane
			float xCoord = (((float)col / WIDTH ) * 2) - 1;	//Between -1 and 1
			float yCoord = (((float)row / HEIGHT) * 2) - 1;	//Between -1 and 1
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
	if (iteration > 0) {
		return Vec3(0,0,0);		//Return black!
	}

	//Loop over every sphere and check for collision!
	for (unsigned int i = 0; i < spheres.size(); i++) {
		Sphere sphere = spheres.at(i);
		//printf("Ray/Sphere collision: Ray <%.2f,%.2f,%.2f><%.2f,%.2f,%.2f> Sphere[<%.2f,%.2f,%.2f> r:%.2f]\n",ray.origin.x, ray.origin.y, ray.origin.z, ray.direction.x, ray.direction.y, ray.direction.z, sphere.pos.x, sphere.pos.y, sphere.pos.z, sphere.radius);

		float d = sphere.intersectsRay(ray);
		if (d >= 0) {
			//Return the color of the sphere dotted with the normal
			Vec3 intersectionPoint = ray.pointAtDistance(d);

			//printf("Intersect at point <%.2f,%.2f,%.2f>\n",intersectionPoint.x, intersectionPoint.y, intersectionPoint.z);
		
			//Check if we can see the light
			//Create a ray from the point to the light
			Ray rayToLight = Ray(intersectionPoint,light);

			bool seesLight = true;	//Set to false if intersects

			//Check if we hit anything
			for (unsigned int j = 1; j < spheres.size(); j++) {
				if (i==j) { continue; }
				
				//If we intersect
				float dist = spheres.at(j).intersectsRay(rayToLight);
				if (dist >= 0) {
					seesLight = false; //We failed!
					break;
				}
			}

			if (seesLight) {
				//Calculate the normal of the sphere
				Vec3 normal = intersectionPoint.subtract(sphere.pos).normalize();
	
				//Dot the lightray with normal
				float correlation = normal.dot(rayToLight.direction);
				if (correlation < 0) { correlation = 0; }

				//Special case for calculating light
				if (i == 0) { correlation = 1; }				

				return sphere.mat.color.multiplyByScalar(correlation);
			} else {
				return sphere.mat.color.multiplyByScalar(0.0f);
			}
		}
	}
	
	//Recurse!
	return shootRay(ray, iteration+1);
}
