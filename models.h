#ifndef MODELS_H
#define MODELS_H

#include <vector>
#include <string>
#include "intersectable.h"

using namespace std;

void loadModel(string model, vector<Intersectable*>* objects, Vec3 scale, Vec3 rotation, Vec3 translation, Material material);

#endif
