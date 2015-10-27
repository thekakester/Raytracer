#ifndef TRIANGLE_CPP
#define TRIANGLE_CPP

#include <cmath>
#include "triangle.h"

#define EPSILON 0.000001

Triangle::Triangle(Vec3 p1, Vec3 p2, Vec3 p3) : v1(p1), v2(p2), v3(p3){}

float Triangle::intersectsRay(Ray ray) {
	//We used:
	//http://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
	//as a reference for this function

	//calculate the normal
	Vec3 normal = v2.minus(v1).cross(v3.minus(v1)).normalize();

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
	Vec3 c = v2.minus(v1).cross(p.minus(v1)).normalize();
	if(normal.dot(c) < 0) return -1;

	c = v3.minus(v2).cross(p.minus(v2)).normalize();
	if(normal.dot(c) < 0) return -1;

	c = v1.minus(v3).cross(p.minus(v3)).normalize();
	if(normal.dot(c) < 0) return -1;

	return depth;
}

Vec3 Triangle::getNormal(Vec3 intersect){
    //TODO use the intersect vector some how
    return v2.minus(v1).cross(v3.minus(v1)).normalize();
}
#endif
