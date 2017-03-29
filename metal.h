#pragma once
#include"material.h"

//class metal :public material
//{
//public:
//	metal(const vec3 &a) : albedo(a) {}
//	virtual bool scatter(const ray &rIn, const hitRecord &rec, vec3 &attenuation, ray &scattered) const;
//	vec3 albedo;
//};
//bool metal::scatter(const ray &rIn, const hitRecord &rec, vec3 &attenuation, ray &scattered) const
//{
//	vec3 reflected = reflect(unitVector(rIn.direction()), rec.normal);
//	scattered = ray(rec.p, reflected);
//	attenuation = albedo;
//	return (reflected, dot(scattered.direction(), rec.normal) > 0);
//}cha8

class metal :public material
{
public:
	float fuzz;
	vec3 albedo;
	metal(const vec3 &a, float f=0.3) :albedo(a)
	{
		if (f < 1)
		{
			fuzz = f;
		}
		else
		{
			fuzz = 1;
		}
	}
	virtual bool scatter(const ray &rIn, const hitRecord &rec, vec3 &attenuation, ray &scattered) const;
	
};

vec3 reflect(const vec3 &v, const vec3 &n)
{
	vec3 vp;
	return v - 2 * dot(v, n)*n;
}



bool metal::scatter(const ray &rIn, const hitRecord &rec, vec3 &attenuation, ray &scattered) const
{
	vec3 reflected = reflect(unitVector(rIn.direction()), rec.normal);
	scattered = ray(rec.p, reflected + fuzz*random_in_unit_sphere());
	attenuation = albedo;
	return (dot(scattered.direction(), rec.normal) > 0);
}