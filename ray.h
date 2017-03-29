#pragma once
#include "vec.h"

class ray
{
public:
	// Constructors
	ray() {}
	ray( const vec3& _ori, const vec3& _dir ) 
	{
		ori = _ori;
		dir = _dir;
		dir /= dir.length();
	}

	// Methods
	const vec3& origin() const { return ori; };
	const vec3& direction() const { return dir; }
	
	//return intersection
	vec3 point_at_parameter(float t) const { return ori + t*dir; }

private:
	vec3 ori;
	vec3 dir;
};
