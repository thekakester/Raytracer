#ifndef VEC3_H
#define VEC3_H

class Vec3 {
public:
	Vec3(float x,float y, float z);
	float x,y,z;
	Vec3 subtract(Vec3);
	float magnitude();
	Vec3 multiplyByScalar(float);
	Vec3 normalize();
	float dot(Vec3);
};

#endif
