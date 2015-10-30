#ifndef TRIANGLE_CPP
#define TRIANGLE_CPP

#include <cmath>
#include "triangle.h"

#define EPSILON 0.0000001

Triangle::Triangle(Vec3 p1, Vec3 p2, Vec3 p3) : v1(p1), v2(p2), v3(p3){}

float Triangle::intersectsRay(Ray ray) {
	//We used:
	//http://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
	//and
	//http://geomalgorithms.com/a06-_intersect-2.html
	//as a reference for this function

	//calculate the normal
	Vec3 normal = v2.minus(v1).cross(v3.minus(v1)).normalize();

	//Get the direction of the ray
	//Vec3 direction = ray.direction.minus(ray.origin);

	//Check for the parallel case by checking if the angle
	//between the the normal and direction is 0
	//Note that we use < EPSILON instead of == 0
	//since we have may not have a perfectly parallel
	//vector, and we need some cut off point
	if(fabs(normal.dot(ray.direction)) < EPSILON){
		return -1;
	}

	//calculate the depth on the ray that the intersection occurs
	Vec3 w = ray.origin.minus(v1);
	float nDw = -normal.dot(w);
	float nDd = normal.dot(ray.direction);
	float depth = nDw / nDd;

	//if the depth is negative, then the point is behind the camera
	//We don't want to draw it, so return -1
	if(depth < 0) return -1;

	//Compute the intersection point
	Vec3 projPt = ray.direction.multiplyByScalar(depth);
	Vec3 p(projPt.x + ray.origin.x, projPt.y + ray.origin.y, projPt.z + ray.origin.z);

	//Make sure that p is in the triangle, not just the plane of the triangle
	Vec3 a = v2.minus(v1);
	Vec3 b = p.minus(v1);
	Vec3 c = a.cross(b).normalize();
	if(normal.dot(c) < 0) return -1;

	a = v3.minus(v2);
	b = p.minus(v2);
	c = a.cross(b).normalize();
	if(normal.dot(c) < 0) return -1;

	a = v1.minus(v3);
	b = p.minus(v3);
	c = a.cross(b).normalize();
	if(normal.dot(c) < 0) return -1;

	return depth;
}

Vec3 Triangle::getNormal(Vec3 intersect){
    return v2.minus(v1).cross(v3.minus(v1)).normalize();
}

int Triangle::ignoreNegativeDiffuse() {
	return 1;
}
#endif
