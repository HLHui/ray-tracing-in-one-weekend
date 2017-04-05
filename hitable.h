#pragma once
#include "ray.h"

class material;

struct hitRecord
{
public:
	float t;
	vec3 p;
	vec3 normal;
	material *matPtr;
	//vec3 c; 
	//float r;
	
};
class hitable
{
public:
	virtual bool hit(const ray &r, float tMin, float tmax, hitRecord &rec) const = 0;
};


