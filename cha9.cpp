#include<iostream>
#include<fstream>
#include<fstream>
#include<limits>
#include"hitableList.h"
#include"sphere.h"
#include"float.h"
#include"camera.h"
#include"material.h"
#include"lambertian.h"
#include"metal.h"
#include"dielectric.h"

using namespace std;

vec3 color(const ray &r, hitable *world, int depth = 0)
{
	hitRecord rec;
	if (world->hit(r, 0.0001, (numeric_limits<float>::max)(), rec))
	{
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.matPtr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation*color(scattered, world, depth + 1);
			//vec3 target = rec.p + rec.normal + random_in_unit_sphere();
			//scattered = ray(rec.p, target - rec.p);
			//return 0.5*color(scattered, world, depth + 1);
		}
		else
		{
			return vec3(0, 0, 0);
		}
	}
	else
	{
		vec3 unitDirection = unitVector(r.direction());
		float t = 0.5*(unitDirection.y() + 1.0);
		return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);//white,light blue
	}
}

int main()
{
	int nx = 400;
	int ny = 200;
	int ns = 300;
	ofstream img;
	//img.open("C:\\ray tracing image\\diffuse-material2.ppm");
	//return 0.9*color(ray(rec.p, target - rec.p), world);

	//
	img.open("C:\\ray tracing image\\9-4.ppm");
	//return 0.5*color(ray(rec.p, target - rec.p), world);



	img << "P3" << endl << nx << " " << ny << endl << "255" << endl;

	/*vec3 leftLow(-3.0, 1.0, -1.5);
	vec3 hori(6.0, 0.0, 0.0);
	vec3 vert(0.0, 0.0, 3.0);
	vec3 origin(0.0, 0.0, 0.0);
	*/
	hitable *list[5];
	/*list[0] = new sphere(vec3(0, 1, 0), 0.5,new lambertian(vec3(0.8,0.3,0.3)));

	list[1] = new sphere(vec3(0, 0, -100.5), 100,new metal(vec3(0.8,0.6,0.2)));
	list[2] = new sphere(vec3(1, 1, 0), 0.5, new lambertian(vec3(0.8, 0.8, 0.0)));
	list[3] = new sphere(vec3(-1, 1, 0), 0.5, new metal(vec3(0.8, 0.8, 0.8)));*/



	list[0] = new sphere(vec3(0, 1, 0), 0.5, new lambertian(vec3(0.8, 0.8, 0.5)));

	list[1] = new sphere(vec3(0, 1, -100.5), 100, new lambertian(vec3(0.2, 0.1, 0.5)));
	//	list[2] = new sphere(vec3(1, 1, 0), 0.5, new metal(vec3(0.8, 0.6, 0.2)));
	list[2] = new sphere(vec3(1, 1, 0), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.5));

	//list[3] = new sphere(vec3(-1, 1, 0), 0.5, new metal(vec3(0.8, 0.8, 0.8)));
	list[3] = new sphere(vec3(-1, 1, 0), 0.5, new dielectric(1.5));
	list[4] = new sphere(vec3(-1, 1, 1), 0.2, new dielectric(1.5));


	hitable *world = new hitableList(list, 5);

	camera cam;

	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			/*float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			ray r(origin, leftLow + u*hori + v*vert);*/

			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++)
			{
				//	float random = rand() % (100) / float(100);
				float random = rand() / (float)RAND_MAX;
				float u = float(i + random) / float(nx);
				float v = float(j + random) / float(ny);
				ray r = cam.getRay(u, v);
				vec3 p = r.point_at_parameter(2.0);
				col += color(r, world);
			}
			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);

			img << ir << " " << ig << " " << ib << endl;
		}
	}

	img.close();
	return 0;

}