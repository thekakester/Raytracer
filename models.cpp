#include "models.h"
#include <fstream>
#include "triangle.h"
#include <math.h>

using namespace std;

void loadModel(string model, vector<Intersectable*>* objects, Vec3 scale, Vec3 rotation, Vec3 translation, Material material) {
	ifstream myfile;
	myfile.open (model);
	
	string buffer;
	myfile >> buffer;
	
	int vertexCount = stoi(buffer);
	cout << model << " has " << vertexCount << " vertices\n";
	
	//Bounding rectangle
	Vec3 min = Vec3(0,0,0);
	Vec3 max = Vec3(0,0,0);
	
	//Load up each vertex!
	Vec3* vertices[vertexCount];
	for (int i = 0; i < vertexCount; i++) {
		//Read each 3 points
		myfile >> buffer;
		float x = (stof(buffer) * scale.x);
		myfile >> buffer;
		float y = (stof(buffer) * scale.y);
		myfile >> buffer;
		float z = (stof(buffer) * scale.z);
		
		//Rotate around y axis
		float newX = (x*cos(rotation.y)) + (z*sin(rotation.y));
		float newZ = (z*cos(rotation.y)) - (x*sin(rotation.y));
		
		x = newX;
		z = newZ;
		
		x += translation.x;
		y += translation.y;
		z += translation.z;
		
		min.x = (x < min.x) ? x : min.x;
		min.y = (y < min.y) ? y : min.y;
		min.z = (z < min.z) ? z : min.z;
		
		max.x = (x > max.x) ? x : max.x;
		max.y = (y > max.y) ? y : max.y;
		max.z = (z > max.z) ? z : max.z;
		
		vertices[i] = new Vec3(x,y,z);
	}
	
	printf("Bounding: <%.2f,%.2f,%.2f> <%.2f,%.2f,%.2f>\n",
			min.x,min.y,min.z,max.x, max.y, max.z);

	
	//Read triangles until we hit EOF
	while (!myfile.eof()) {
		myfile >> buffer;		
		int index1 = stoi(buffer)-1;	//obj is 1 indexed.
		
		myfile >> buffer;
		int index2 = stoi(buffer)-1;
		
		myfile >> buffer;
		int index3 = stoi(buffer)-1;

		
		//Create a triangle with these indices!
		Triangle* triangle = new Triangle(*vertices[index1],*vertices[index2],*vertices[index3]);
		triangle->mat = material;
		objects->push_back(triangle);
		
		//printf("<%.2f,%.2f,%.2f>\t<%.2f,%.2f,%.2f>\t<%.2f,%.2f,%.2f>\n",
		//	triangle->v1.x,triangle->v1.y,triangle->v1.z,
		//	triangle->v2.x,triangle->v2.y,triangle->v2.z,
		//	triangle->v3.x,triangle->v3.y,triangle->v3.z);
	}
}
