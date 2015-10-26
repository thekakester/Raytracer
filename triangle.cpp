#ifndef TRIANGLE_CPP
#define TRIANGLE_CPP

#include "triangle.h"

Triangle::Triangle(Vec3 p1, Vec3 p2, Vec3 p3) : v1(p1), v2(p2), v3(p3) {
}

float Triangle::intersectsRay(Ray ray) {
	
	return 0;
}

Vec3 Triangle::getNormal(Vec3 intersect){
    //TODO use the intersect vector some how
    Vec3 edgeA = v1.subtract(v2);
    Vec3 edgeB = v3.subtract(v2);
    return edgeA.cross(edgeB).normalize();
}
#endif
