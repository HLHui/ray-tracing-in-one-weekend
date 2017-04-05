#pragma once
#include"ray.h"
#define M_PI 3.1415926

//vec3 random_in_unit_disk()
//{
//	vec3 p;
//	do 
//{
//		float ux = rand() / (float)RAND_MAX;
//		float uy = rand() / (float)RAND_MAX;
//		p = 2.0*vec3(ux,uy,0) - vec3(1, 1, 0);
//	} while (dot(p, p) >= 1.0);
//	return p;
//}

vec3 random_in_unit_disk()
{
	vec3 p;
	do
	{
		float ux = rand() / (float)RAND_MAX;
		float uz = rand() / (float)RAND_MAX;
		p = 2.0*vec3(ux, 0, uz) - vec3(1, 0, 1);
	} while (dot(p, p) >= 1.0);
	return p;
}

class camera
{
public:
//#if 0
//	camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect/*,float aperture,float focusDist*/)
//	{
//
//		//		lensRadius = aperture / 2;
//		float theta = vfov*M_PI / 180;
//		float halfHeight = tan(theta / 2);
//		float halfWidth = aspect*halfHeight;
//		origin = lookfrom;
//		w = unitVector(lookfrom - lookat);
//		u = unitVector(cross(vup, w));
//		v = cross(w, u);
//		leftLow = origin - halfWidth*u - halfHeight*v - w;
//		hori = 2 * halfWidth*u;
//		vert = 2 * halfHeight*v;
//		//		leftLow = origin - halfWidth*focusDist*u - halfHeight*focusDist*v - focusDist*w;
//		//hori = 2 * halfHeight*focusDist*u;
//		//vert = 2 * halfHeight*focusDist*v;
//	}
//	float lensRadius;
//	vec3 u, v, w;
//	vec3 leftLow;
//	vec3 origin;
//	vec3 hori;
//	vec3 vert;
//	ray getRay(float s, float t)
//	{
//		//	vec3 rd = lensRadius*random_in_unit_sphere();
//		return ray(origin, leftLow + s*hori + t*vert - origin);
//	}
//#else
	camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focusDisk)
	{
		lensRadius = aperture / 2;
		float theta = vfov*M_PI / 180;
		float halfHeight = tan(theta / 2);
		float halfWidth = aspect*halfHeight;
		origin = lookfrom;
		w = unitVector(lookfrom - lookat);
		u = unitVector(cross(vup, w));
		v = cross(w, u);
		leftLow = origin - halfWidth*focusDisk*u - halfHeight*focusDisk*v - focusDisk*w;

		hori = 2 * halfWidth*focusDisk* u;
		vert = 2 * halfHeight* focusDisk*v;
	}

	/*ray getRay(float s, float t)
	{
		vec3 rd = lensRadius * random_in_unit_disk();
		vec3 offset = (u * rd.x()) + (v * rd.y());
		return ray(origin + offset, leftLow + s * hori + t * vert - origin - offset);
	}*/

	ray getRay(float s, float t)
	{
		vec3 rd = lensRadius * random_in_unit_disk();
		vec3 offset = (u * rd.x()) + (v * rd.z());
		return ray(origin + offset, leftLow + s * hori + t * vert - origin - offset);
	}

	vec3 leftLow;
	vec3 hori;
	vec3 vert;
	vec3 origin;
	vec3 u, v, w;
	float lensRadius;
//#endif
};