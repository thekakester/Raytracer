#ifndef TRIANGLE_CPP
#define TRIANGLE_CPP

#include <cmath>
#include "triangle.h"

#define EPSILON 0.000001

Triangle::Triangle(Vec3 p1, Vec3 p2, Vec3 p3) : v1(p1), v2(p2), v3(p3) {
}

float Triangle::intersectsRay(Ray ray) {
	//We used:
	//http://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
	//as a reference for this function

	//Calculate the normal
	Vec3 edgeA = v2.subtract(v1);
	Vec3 edgeB = v3.subtract(v1);
	Vec3 normal = edgeA.cross(edgeB).normalize();

	/*printf("v1 x: %.2f y: %.2f z: %.2f\n", v1.x, v1.y, v1.z);
	printf("v2 x: %.2f y: %.2f z: %.2f\n", v2.x, v2.y, v2.z);
	printf("v3 x: %.2f y: %.2f z: %.2f\n", v3.x, v3.y, v3.z);
	printf("eA x: %.2f y: %.2f z: %.2f\n", edgeA.x, edgeA.y, edgeA.z);
	printf("eB x: %.2f y: %.2f z: %.2f\n", edgeB.x, edgeB.y, edgeB.z);
	printf("No x: %.2f y: %.2f z: %.2f\n", normal.x, normal.y, normal.z);*/

	//Check for the parallel case
	//Note that we use < EPSILON instead of == 0
	//since we have may not have a perfectly parallel
	//vector, but we need some cut off point
	if(fabs(normal.dot(ray.direction)) < EPSILON){
		return -1;
	}

	//calculate the depth on the ray that the intersection occurs
	float depth = (normal.dot(ray.origin) + normal.dot(v1)) / normal.dot(ray.direction);

	//if the depth is negative, then the point is behind the camera
	//We don't want to draw it, so return -1
	if(depth < 0) return -1;

	//Compute the intersection point
	Vec3 projPt = ray.direction.multiplyByScalar(depth);
	Vec3 p(projPt.x + ray.origin.x, projPt.y + ray.origin.y, projPt.z + ray.origin.z);

	//Make sure that p is in the triangle, not just the plane of the triangle
	Vec3 a = v2.subtract(v1);
	Vec3 b = p.subtract(v1);
	Vec3 c = a.cross(b).normalize();
	if(normal.dot(c) < 0) return -1;

	a = v3.subtract(v2);
	b = p.subtract(v2);
	c = a.cross(b).normalize();
	if(normal.dot(c) < 0) return -1;

	a = v1.subtract(v3);
	b = p.subtract(v3);
	c = a.cross(b).normalize();
	if(normal.dot(c) < 0) return -1;

	return depth;
}

Vec3 Triangle::getNormal(Vec3 intersect){
	//Calculate the normal
	Vec3 edgeA = v2.subtract(v1);
	Vec3 edgeB = v3.subtract(v1);
	return edgeA.cross(edgeB);
}
#endif
