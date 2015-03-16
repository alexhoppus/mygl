#include "obj_file.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <stdlib.h>     /* srand, rand */

using namespace std;

int Obj_file::read_file()
{
	FILE *file;
	char str[100];
	char id[10], val1[10], val2[10], val3[10];
	int n_v = 0, n_f = 0;
	file = fopen (file_name.c_str(),"r");
	if (!file) {
		cout << "Can't open file " << file_name << endl;
		return -1;
	}

	while (fgets(str, 100, file) != NULL) {
		sscanf(str, "%s %*s", id);
		if (!strcmp(id, "v")) {
			float v1, v2, v3;
			sscanf(str, "%*s %f %f %f", &v1, &v2, &v3);
			vertices.push_back(Vec3f(v1, v2, v3)); n_v++;
		} else if (!strcmp(id, "f")) {
			int f1, f2, f3;
			sscanf(str, "%*s %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d",
				&f1, &f2, &f3);
			faces.push_back(Vec3i(f1, f2, f3)); n_f++;
		} else {
			/*Skip*/
		}
	};
	cout << "Number of vertices " << n_v << endl;
	cout << "Number of faces " << n_f << endl;
	return 0;
}

void Model::line(int x0, int y0, int x1, int y1, TGAColor color)
{
	bool steep = false;
	if (std::abs(x0-x1)<std::abs(y0-y1)) {
        	std::swap(x0, y0);
        	std::swap(x1, y1);
        	steep = true;
    	}
    	if (x0>x1) {
        	std::swap(x0, x1);
        	std::swap(y0, y1);
    	}
    	int dx = x1-x0;
    	int dy = y1-y0;
    	int derror2 = std::abs(dy)*2;
    	int error2 = 0;
    	int y = y0;
    	for (int x=x0; x<=x1; x++) {
        	if (steep) {
            		image.set(y, x, color);
        	} else {
            		image.set(x, y, color);
        	}
        	error2 += derror2;

        	if (error2 > dx) {
            		y += (y1>y0?1:-1);
            		error2 -= dx*2;
        	}
    	}
}
int Model::point_in_triangle(Vec2i p, Vec2i p0, Vec2i p1, Vec2i p2)
{
	int s = p0.y * p2.x - p0.x * p2.y + (p2.y - p0.y) * p.x + (p0.x - p2.x) * p.y;
    	int t = p0.x * p1.y - p0.y * p1.x + (p0.y - p1.y) * p.x + (p1.x - p0.x) * p.y;

	if ((s < 0) != (t < 0))
        	return 0;

    	int A = -p1.y * p2.x + p0.y * (p2.x - p1.x) + p0.x * (p1.y - p2.y) + p1.x * p2.y;
	if (A < 0.0) {
        	s = -s;
        	t = -t;
        	A = -A;
    	}
	return s >= 0 && t >= 0 && (s + t) <= A;
}

void Model::triangle(Vec2i p1, Vec2i p2, Vec2i p3, TGAColor color) {
	int max_x, max_y, min_x, min_y;
	max_x = std::max(p3.x, std::max(p1.x, p2.x));
	max_y = std::max(p3.y, std::max(p1.y, p2.y));
        min_x = std::min(p3.x, std::min(p1.x, p2.x));
        min_y = std::min(p3.y, std::min(p1.y, p2.y));
	for (int x = min_x; x <= max_x; x++) {
		for (int y = min_y; y <= max_y; y++) {
			if (point_in_triangle(Vec2i(x, y), p1, p2, p3)) {
				image.set(x, y, color);
			}
		}
	}
}

void Model::render(std::string out_file_name, TGAColor color)
{
	int width = image.get_width();
	int height = image.get_height();
	std::vector<Vec3i>::iterator it = datafile.faces.begin();
	Vec3f light_dir(0, 0, 1);
	for (; it != datafile.faces.end(); it++) {
		Vec3f vp;
		Vec3i vertices = *it;
		Vec3f v1 = datafile.vertices[vertices.x - 1];
		Vec3f v2 = datafile.vertices[vertices.y - 1];
		Vec3f v3 = datafile.vertices[vertices.z - 1];
	        Vec2i p1(((v1.x + 1.) * width / 2.), ((v1.y + 1.) * height / 2.));
		Vec2i p2(((v2.x + 1.) * width / 2.), ((v2.y + 1.) * height / 2.));
		Vec2i p3(((v3.x + 1.) * width / 2.), ((v3.y + 1.) * height / 2.));
		Vec3f vector1 = v2 - v1;
		Vec3f vector2 = v3 - v1;
		vp = vector1.vector_product(vector2);
		vp.normalize();
		float intensity = vp.dot_product(light_dir);

		if (intensity >= 0) {
			triangle(p1, p2, p3, TGAColor(intensity * 255,
				intensity * 255, intensity * 255));
		}	
	}
	image.write_tga_file(out_file_name.c_str());
	return;
}
