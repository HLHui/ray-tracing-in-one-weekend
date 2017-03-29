#pragma once

#include"material.h"

class lambertian :public material
{
public:
	lambertian(const vec3 &a) : albedo(a) {}
	virtual bool scatter(const ray &rIn, const hitRecord &rec, vec3 &attenuation, ray &scattered) const;
private:
	vec3 albedo;//attenuation
};

vec3 random_in_unit_sphere()
{
	vec3 p(1, 1, 1);
	while (p.squaredLength() >= 1.0)
	{
		// Generate 3 random values between 0 and 1 (floating point)
		float ux = (rand() / (float)RAND_MAX);
		float uy = (rand() / (float)RAND_MAX);
		float uz = (rand() / (float)RAND_MAX);

		p = 2.0*vec3(ux, uy, uz) - vec3(1, 1, 1);
	}
	return p;

}

bool lambertian::scatter(const ray &rIn, const hitRecord &rec, vec3 &attenuation, ray &scattered) const
{
	vec3 target = rec.p + rec.normal + random_in_unit_sphere();
	scattered = ray(rec.p, target - rec.p);
	attenuation = albedo;
	return true;
}