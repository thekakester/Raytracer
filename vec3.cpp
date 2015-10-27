#ifndef VEC3_CPP
#define VEC3_CPP

#include "vec3.h"
#include <math.h>

Vec3::Vec3(float x, float y, float z){
	Vec3::x = x;
	Vec3::y = y;
	Vec3::z = z;
}

/**Create and return a normalized vector!**/
Vec3 Vec3::normalize() {
	float magnitude = Vec3::magnitude();
	return Vec3(Vec3::x/magnitude, Vec3::y/magnitude, Vec3::z/magnitude);
}

/**Add "other" with this
*/
Vec3 Vec3::add(Vec3 other) {
	return Vec3(Vec3::x+other.x, Vec3::y+other.y, Vec3::z+other.z);
}

/**Subtract "other" from this
aka "return this-other"
NOTE: THIS IS OPPOSITE OF RAYTO()**/
Vec3 Vec3::minus(Vec3 other) {
	return Vec3(Vec3::x-other.x, Vec3::y-other.y, Vec3::z-other.z);
}

/**Get the magnitude of this vector
**/
float Vec3::magnitude() {
	return sqrt((Vec3::x*Vec3::x)+(Vec3::y*Vec3::y)+(Vec3::z*Vec3::z));
}

/**Dot two vec3s together
**/
float Vec3::dot(Vec3 other) {
	return (Vec3::x*other.x) + (Vec3::y*other.y) + (Vec3::z*other.z);
}

/**Cross two vec3s together
**/
Vec3 Vec3::cross(Vec3 other) {
	return Vec3(Vec3::y * other.z - Vec3::z * other.y, 
	            Vec3::z * other.x - Vec3::x * other.z,
	            Vec3::x * other.y - Vec3::y * other.x);
}

/**Multiply this vec3 by a scalar and RETURN A NEW VEC3
**/
Vec3 Vec3::multiplyByScalar(float scalar) {
	return Vec3(Vec3::x*scalar,Vec3::y*scalar,Vec3::z*scalar);
}

#endif
