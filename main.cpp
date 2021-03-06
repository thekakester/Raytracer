#include <iostream>
#include <vector>
#include <math.h>
#include <pthread.h>
#include <random>
#include "triangle.h"
#include "intersectable.h"
#include "sphere.h"
#include "vec3.h"
#include "ray.h"
#include "models.h"
#include <cfloat>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define WIDTH 512
#define HEIGHT 512

//Set SINGLEX and SINGLEY to a (x,y) coordinate to only run the
//ray tracer for a specific pixel of the output image.  This is good
//For tracking where a ray bounces!
//Set to -1 to ignore!
//NOTE: This creates no output image!
#define SINGLEX = -1
#define SINGLEY = -1;

using namespace std;

//PROTOTYPES START
void traceRays();
Vec3 shootRay(Ray, int, Intersectable*);
void setupReferenceWorld();
void setupCustomWorld();
void setupFancyWorld();
float randFloat(float low, float high);
void *shoot_thread(void *data);
//PROTOTYPES END!

Vec3 cameraPosition = Vec3(0,0,0);
Vec3 light = Vec3(3,5,-15);

char image[WIDTH*HEIGHT*3];

vector<Intersectable*> objects;

int main(int argc, char** argv) {
	cout << "Raytracer starting!\n";

	cout << "Building scene...\n";
	string filename;
	if(argc > 1 && strcmp(argv[1], "custom") == 0){
		setupCustomWorld();	//Execute our cutom world
		filename = "custom.png";
	}else if (argc > 1 && strcmp(argv[1],"fancy") == 0){
		setupFancyWorld();
		filename = "fancy.png";
	} else {
		setupReferenceWorld();	//Execute Dr. Kuhl's code from the assignment
		filename = "reference.png";
	}

	cout << "Tracing rays...\n";

	traceRays();

	printf("\e[1ATracing rays... Done!\n");

	cout << "Saving image to " << filename << "... ";
	stbi_write_png(filename.c_str(), WIDTH, HEIGHT, 3, image, WIDTH*3);
	cout << "Done!\nRaytracing complete!\n";
	pthread_exit(NULL);
}

/*********************************************
The code posted on canvas.
This will setup the world for the assignment
Only minor adjustments were made in this code
to make it compatable with our classes
 **********************************************/
void setupReferenceWorld() {

	// make a Material which is reflective
	Material refl;
	refl.reflective = 1.0f;
	refl.color = Vec3(0,0,1); // color is not used when Material is reflective!

	// make several diffuse Materials to choose from
	Material red;
	red.reflective = 0.0f;
	red.color = Vec3(1,0,0);
	Material blue;
	blue.reflective = 0.0f;
	blue.color = Vec3(0,0,1);
	Material white;
	white.reflective = 0.0f;
	white.color = Vec3(1,1,1);

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

	// back wall
	Triangle* back1 = new Triangle(Vec3(-8,-2,-20), Vec3(8,-2,-20), Vec3(8,10,-20));
	back1->mat = blue;
	Triangle* back2 = new Triangle(Vec3(-8,-2,-20), Vec3(8,10,-20), Vec3(-8,10,-20));
	back2->mat = blue;
	
	// Wall behind camera (easter egg if transparency is on
	Triangle* camback1 = new Triangle(Vec3(-8,-2,1), Vec3(8,-2,1), Vec3(8,10,1));
	camback1->mat = blue;
	Triangle* camback2 = new Triangle(Vec3(-8,-2,1), Vec3(8,10,1), Vec3(-8,10,1));
	camback2->mat = blue;

	// floor
	Triangle* bot1 = new Triangle(Vec3(-8,-2,-20), Vec3(8,-2,-10), Vec3(8,-2,-20));
	bot1->mat = white;
	Triangle* bot2 = new Triangle(Vec3(-8,-2,-20), Vec3(-8,-2,-10), Vec3(8,-2,-10));
	bot2->mat = white;

	// right red Triangle
	Triangle* right = new Triangle(Vec3(8,-2,-20), Vec3(8,-2,-10), Vec3(8,10,-20));
	right->mat = red;

	//Add the triangles to our vector
	objects.push_back(right);
	objects.push_back(back1);
	objects.push_back(back2);
	//objects.push_back(camback1);
	//objects.push_back(camback2);
	objects.push_back(bot1);
	objects.push_back(bot2);
	objects.push_back(sph3);
	objects.push_back(sph1);
	objects.push_back(sph2);
}

void setupFancyWorld() {
	Material mat = Material();
	mat.color = Vec3(1.0f,1.0f,1.0f);
	mat.reflective = 0.2f;
	mat.transparent = 0;
	loadModel("bs.model",&objects, Vec3(1/20.0f,1/20.0f,1/20.0f), Vec3(0,0,0), Vec3(0,-1,-15),mat);

	Material mat2 = Material();
	mat2.color = Vec3(0.5f,0.5f,0.0f);
	mat2.reflective = 0.2f;
	mat2.transparent = 0;
	loadModel("alley.model",&objects, Vec3(0.5f,0.5f,0.5f), Vec3(0,0,0), Vec3(0,-1,0),mat2);
}

void setupCustomWorld() {
	// water
	Triangle* waterTri[14];
	Vec3 verts[16]{
		Vec3(0.0f,-2.1f,-2.0f),
		Vec3(1.0f,-2.1f,-2.5f),
		Vec3(2.2f,-2.1f,-4.5f),
		Vec3(2.4f,-2.1f,-6.5f),
		Vec3(1.7f,-2.1f,-8.8f),
		Vec3(2.4f,-2.1f,-10.6f),
		Vec3(2.6f,-2.1f,-12.0f),//
		Vec3(2.0f,-2.1f,-14.1f),
		Vec3(0.0f,-2.1f,-14.5f),
		Vec3(-2.0f,-2.1f,-14.0f),
		Vec3(-3.4f,-2.1f,-12.8f),//
		Vec3(-3.4f,-2.1f,-11.4f),//
		Vec3(-3.0f,-2.1f,-9.0f),
		Vec3(-2.8f,-2.1f,-7.5f),
		Vec3(-2.5f,-2.1f,-6.5f),
		Vec3(-1.0f,-2.1f,-2.5f)
	};

	Material water_mat;
	water_mat.reflective = 0.8f;
	water_mat.transparent = 0.7f;
	water_mat.color = Vec3(0.4,0.4f,1.0f);

	int j = 15;
	for(int i = 1; i <= 7; i++){
		waterTri[i] = new Triangle(verts[i], verts[i+1], verts[j--]);
		waterTri[i]->mat = water_mat;
		objects.push_back(waterTri[i]);
	}

	j = 7;
	for(int i = 9; i <= 15; i++){
		waterTri[i-1] = new Triangle(verts[i], verts[(i+1) % 16], verts[j--]);
		waterTri[i-1]->mat = water_mat;
		objects.push_back(waterTri[i-1]);
	}

	Vec3 a(-10, -2.0f, -1);
	Vec3 b(10, -2.0f, -1);
	Vec3 c(10, -2.0f, -20);
	Vec3 d(-10, -2.0f, -20);

	Triangle* grass[20];

	grass[0] = new Triangle(a, verts[0], b);
	for(int i = 0; i <= 5; i++){
		grass[i+1] = new Triangle(verts[i], verts[i+1], b);
	}

	grass[7] = new Triangle(b, verts[6], c);
	for(int i = 6; i <= 8; i++){
		grass[i+2] = new Triangle(verts[i], verts[i+1], c);
	}

	grass[11] = new Triangle(c, verts[9], d);
	for(int i = 9; i <= 11; i++){
		grass[i+3] = new Triangle(verts[i], verts[i+1], d);
	}

	grass[15] = new Triangle(d, verts[12], a);
	for(int i = 12; i <= 15; i++){
		grass[i+4] = new Triangle(verts[i], verts[(i+1) % 16], a);
	}

	Material grass_mat;
	grass_mat.color = Vec3(0.1f,0.3f,0.1f);

	for(int i = 0; i < 20; i++){
		grass[i]->mat = grass_mat;
		objects.push_back(grass[i]);
	}

	Material sky_mat;
	sky_mat.color = Vec3(.001,.001,.1);
	sky_mat.transparent = 0.0f;

	Triangle* sky1 = new Triangle(Vec3(-10,-2,-20), Vec3(10,-2,-20), Vec3(10,10,-20));
	sky1->mat = sky_mat;
	Triangle* sky2 = new Triangle(Vec3(-10,-2,-20), Vec3(10,10,-20), Vec3(-10,10,-20));
	sky2->mat = sky_mat;
	objects.push_back(sky1);
	objects.push_back(sky2);


	Material dirt_mat;
	dirt_mat.color = Vec3(0.2f,0.2f,0.0f);

	// floor
	Triangle* dirt1 = new Triangle(Vec3(-10,-2.4,-20), Vec3(10,-2.4,-1), Vec3(10,-2.4,-20));
	dirt1->mat = dirt_mat;
	objects.push_back(dirt1);

	Triangle* dirt2 = new Triangle(Vec3(-10,-2.4,-20), Vec3(-10,-2.4,-1), Vec3(10,-2.4,-1));
	dirt2->mat = dirt_mat;
	objects.push_back(dirt2);


	Material moon_mat;
	moon_mat.color = Vec3(1.0,1.0f,0.81f);

	Sphere* moon = new Sphere();
	moon->pos = Vec3(3,5,-21);
	moon->radius = 2;
	moon->mat = moon_mat;
	objects.push_back(moon);

	srand(300);
	for(int i = 0; i < 100; i++){
		Sphere* star = new Sphere();
		star->pos = Vec3(randFloat(-10.0f,10.0f), randFloat(-1.8f, 10.0f),randFloat(-20.4999f,-20.496f));
		star->radius = .5;
		star->mat = moon_mat;
		objects.push_back(star);
	}

}

float randFloat(float low, float high){
	return low + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(high-low)));
}

/****************************************************************
This actually runs the ray-tracing and saves the data to image[]
 ****************************************************************/
void traceRays() {
	int threadCount = 8;
	printf("%d Objects in scene\n",(int)objects.size());

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for (int row = 0; row < HEIGHT; row++) {
		//For progress, print off percentage every few rows
		if (row % 20 == 0) {
			printf("\e[1ATracing rays... %d%%\n", (int)((row*100.0f)/HEIGHT));
		}
		int increment = 0;
		for (int col = 0; col < WIDTH; col+=increment) {

			pthread_t threads[threadCount];

			//We are going to draw as many pixels as possible, but if we are
			//at the end of the row, then we can't draw the full amount
			//se we need to make sure that we do not try to draw too many
			increment = 0;
			while(increment < threadCount && col + increment < WIDTH){
				Vec3* data = new Vec3(row, col+increment, 0);
				pthread_create(&threads[increment], NULL,shoot_thread, (void *)data);
				increment++;
			}

			for(int i = 0; i < increment; i++){
				pthread_join(threads[i], NULL);
			}
		}
	}
	pthread_attr_destroy(&attr);
}

void *shoot_thread(void *data){
	Vec3* vData = (Vec3*)data;
	int row = vData->x;
	int col = vData->y;

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
	//Pass in -1, meaning that this ray isn't bouncing off of any object.
	Vec3 color = shootRay(ray,0,NULL);

	//Convert values of 0.0 to 1.0 to 0-255
	color.x *= 255;
	color.y *= 255;
	color.z *= 255;

	//Set the color for this pixel!
	image[baseIndex+0] = color.x;
	image[baseIndex+1] = color.y;
	image[baseIndex+2] = color.z;
	pthread_exit(NULL);
	return 0;
}

/**Shoot a given ray at the scene and return
a color.  This is recursive, so it could potentially go deeper!
Only do up to 1000 recurses before deciding to return black!
 *
 * fromObject is the index of the object that the ray is coming from
 * This makes sure we don't accidentally collide with ourself
 **/
Vec3 shootRay(Ray ray, int iteration, Intersectable* fromObject) {
	//If we recursed too many times
	if (iteration > 100) {
		return Vec3(0,0,0);		//Return black!
	}

	//Loop over every object and check for collision!
	Intersectable* closest = NULL;
	float closeDist = FLT_MAX;
	for (unsigned int i = 0; i < objects.size(); i++) {
		Intersectable* object = objects.at(i);
		
		if (object == fromObject) { continue; }	//Don't check collision with ourself

		//printf("Ray/Sphere collision: Ray <%.2f,%.2f,%.2f><%.2f,%.2f,%.2f> Sphere[<%.2f,%.2f,%.2f> r:%.2f]\n",ray.origin.x, ray.origin.y, ray.origin.z, ray.direction.x, ray.direction.y, ray.direction.z, sphere.pos.x, sphere.pos.y, sphere.pos.z, sphere.radius);

		float d = object->intersectsRay(ray);
		if (d >= 0 && d < closeDist) {
			closeDist = d;
			closest = object;
		}
	}
	
	//If we intersected something...
	if (closest != NULL) {
		//Return the color of the sphere dotted with the normal
		Vec3 intersectionPoint = ray.pointAtDistance(closeDist);

		//Calculate the normal of the sphere
		Vec3 normal = closest->getNormal(intersectionPoint);

		//Return the normal for color
		//return Vec3((normal.x + 1) / 2,(normal.y + 1) / 2,(normal.z + 1) / 2);

		//If we intersected with a reflective surface, bounce it!
		Vec3 reflectiveColor = Vec3(0,0,0);

		//Only calculate if we are somewhat reflective
		if (closest->mat.reflective > 0) {
			reflectiveColor = shootRay(ray.reflect(intersectionPoint,normal),iteration+1, closest);
		}

		//Let "p" be the percentage of this reflection
		//Let "q" be 1-p
		//This will be "p" % whatever this color is
		//and q % regular diffuse!
		reflectiveColor = reflectiveColor.multiplyByScalar(closest->mat.reflective);

		Vec3 transparentColor = Vec3(0,0,0);

		//Only calculate if we are somewhat reflective
		if (closest->mat.transparent > 0) {
			transparentColor = shootRay(ray,iteration+1,closest);
		}

		//Let "p" be the percentage of this reflection
		//Let "q" be 1-p
		//This will be "p" % whatever this color is
		//and q % regular diffuse!
		transparentColor = transparentColor.multiplyByScalar(closest->mat.transparent);

		//Check if we can see the light
		//Create a ray from the point to the light
		Ray rayToLight = Ray(intersectionPoint,light);

		float distToLight = rayToLight.origin.minus(light).magnitude();

		bool seesLight = true;	//Set to false if intersects

		//Check if we hit anything
		for (unsigned int j = 0; j < objects.size(); j++) {
			//Don't check collision with ourself
			Intersectable* other = objects.at(j);
			if (other == closest) { continue; }

			//If we intersect
			float dist = other->intersectsRay(rayToLight);

			if (dist > 0.0 && dist < distToLight) {
				seesLight = false; //We failed!
				break;
			}
		}

		//Its time to calculate the color to return

		//Ambient light!
		Vec3 ambience = closest->mat.color.multiplyByScalar(0.2f);
		Vec3 diffuse = Vec3(0,0,0);

		if (seesLight) {
			//Dot the lightray with normal
			float correlation = normal.dot(rayToLight.direction);
			
			//Triangles can be the absolute value of this
			if (closest->ignoreNegativeDiffuse() == 1) {
				correlation = fabs(correlation);
			}
			
			if (correlation < 0) { correlation = 0; }

			//Diffuse is 80%!
			diffuse = closest->mat.color.multiplyByScalar(correlation * 0.8);
		}

		//The return color is:
		// Reflection + (diffuse + ambient)
		Vec3 returnColor = diffuse.add(ambience);

		//How much of an impact does reflection have on this?
		//(note, this does nothing if object is not reflective)
		returnColor = returnColor.multiplyByScalar(1 - closest->mat.reflective);
		returnColor = returnColor.add(reflectiveColor);
		returnColor = returnColor.multiplyByScalar(1 - closest->mat.transparent);
		returnColor = returnColor.add(transparentColor);
		return returnColor;
	}
	//If we're not hitting something, return black!
	return Vec3(0,0,0);	
}
