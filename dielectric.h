#pragma once

#include "material.h"
#include "metal.h"
//#include "log.h"

class dielectric :public material
{
public:
	dielectric(float ri):refIdx(ri){}
	virtual bool scatter(const ray &rIn, const hitRecord &rec, vec3 &attenuation, ray &scattered) const;
	float refIdx;
};

bool refract(const vec3 &v, const vec3 &n, float ni_over_nt, vec3 &refracted)
{
	vec3 uv = unitVector(v);
	float dt = dot(uv, n);
	float discriminat = 1.0 - ni_over_nt*ni_over_nt*(1 - dt*dt);
	if (discriminat > 0)
	{
		refracted = ni_over_nt*(uv - n*dt) - n*sqrt(discriminat);
		return true;
	}
	else
	{
		return false;
	}
}

bool dielectric::scatter(const ray &rIn, const hitRecord &rec, vec3 &attenuation, ray &scattered) const
{
	vec3 outwardNormal;
	vec3 reflected = reflect(rIn.direction(), rec.normal);
	float ni_over_nt;
	attenuation = vec3(1.0, 1.0, 1.0);
	vec3 refracted;
	if (dot(rIn.direction(), rec.normal) > 0)
	{
		outwardNormal = -rec.normal;
		ni_over_nt = refIdx;
	}
	else
	{
		outwardNormal = rec.normal;
		ni_over_nt = 1.0 / refIdx;
	}
	if (refract(rIn.direction(), outwardNormal, ni_over_nt, refracted))
	{
		scattered = ray(rec.p, refracted);
	}
	else {
		scattered = ray(rec.p, refracted);
		return false;
	}
	return true;
}
