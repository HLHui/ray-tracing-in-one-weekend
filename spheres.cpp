#include<iostream>
#include<conio.h>
#include<fstream>
#include<limits>
#include<sstream>
#include"ray.h"
#include"camera.h"
#include"hitable.h"
#include"sphere.h"
#include"hitableList.h"
#include"float.h"

using namespace std;


vec3 color(const ray &r, hitable *world, int depth)
{
	hitRecord rec;
	if (world->hit(r, 0.001, (numeric_limits<float>::max)(), rec))
	{
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.matPtr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation *color(scattered, world, depth + 1);
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
		return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
	}
}

hitable *randomScene()
{
	int n = 500;
	hitable **list = new hitable *[n + 1];
	list[0] = new sphere(vec3(0, -1000.5, 0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
	int i = 1;
	float randomNum = rand() / float(RAND_MAX);
	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			float chooseMat = randomNum;
			vec3 center(a + 0.9*randomNum, 0.2, b + 0.9*randomNum);
			if ((center - vec3(4, 0.2, 0)).length() > 0.9)
			{
				if (chooseMat < 0.8)
				{
					list[i++] = new sphere(center, 0.2, new lambertian(vec3(randomNum*randomNum, randomNum*randomNum, randomNum*randomNum)));
				}
				else if (chooseMat < 0.95)
				{
					list[i++] = new sphere(center, 0.2, new metal(vec3(0.5*(1 + randomNum), 0.5*(1 + randomNum), 0.5*(1 + randomNum)), 0.5*(1 + randomNum)));
				}
				else
				{
					list[i++] = new sphere(center, 0.2, new dielectric(1.5));
				}
			}
		}
	}
	list[i++] = new sphere(vec3(0, 0, -1), 1.0, new dielectric(1.5));
	list[i++] = new sphere(vec3(-4, 0, -1), 1.0, new lambertian(vec3(0.4, 0.2, 0.1)));
	list[i++] = new sphere(vec3(4, 0, -1), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));
	return new hitableList(list, i);
}



int main()
{
	int nx = 1200;
	int ny = 600;
	int ns = 20;
	hitable *list[5];

	list[0] = new sphere(vec3(0, 1, 0), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));
	list[1] = new sphere(vec3(0, 1, -100.5), 100, new lambertian(vec3(0.8, 0.6, 0.2)));
	list[2] = new sphere(vec3(1, 1, 0), 0.5, new metal(vec3(0.8, 0.8, 0.0),0.0));
	list[3] = new sphere(vec3(-1, 1, 0), 0.5, new dielectric(1.5));
	list[4] = new sphere(vec3(-1, 1, 0), -0.45, new dielectric(1.5));

	hitable *world = new hitableList(list, 5);
	world = randomScene();

	//vec3 p2(-2, 2, 1), p1(-1, 2, 1);
	//float time = 0.f;
	//const float timeStep = 0.1;
	//int iteration = 1;
	
	//while(time < 1.f) {
		// File output
		//std::stringstream ssFileOut;
		//ssFileOut << "C:\\ray tracing image\\anim_" << iteration << ".ppm";
		ofstream img;
		img.open("C:\\ray tracing image\\11-9.ppm");
		//img.open(ssFileOut.str());
		img << "P3" << endl << nx << " " << ny << endl << "255" << endl;

//		vec3 cameraPos = time*p1 + (1 - time)*p2;
//		camera cam(cameraPos, vec3(0, 1, 0), vec3(0, 0, 1), 90, float(nx) / float(ny));
		vec3 lookfrom(13, 5, 3);
		vec3 lookat(0, 1, 0);
		float diskToFocus = (lookfrom - lookat).length();
		float aperture = 2.0;
		//camera cam(lookfrom, lookat, vec3(0, 0, 1), 20, float(nx) / float(ny));
		camera cam(lookfrom, lookat, vec3(0, 0, 1), 20, float(nx) / float(ny), 0.1, 10.0);

		for (int j = ny - 1; j >= 0; j--)
		{
			for (int i = 0; i < nx; i++)
			{
				vec3 col(0, 0, 0);
				for (int s = 0; s < ns; s++)
				{
					float random = rand() % (100) / float(100);  
					float u = float(i + random) / float(nx);
					float v = float(j + random) / float(ny);
					//col = vec3(u, v, 0) * ns;break;
					ray r = cam.getRay(u, v);
					vec3 p = r.point_at_parameter(2.0);
					col += color(r, world, 0);
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

		//iteration += 1;
		//time += timeStep;
	//}
	return 0;

}