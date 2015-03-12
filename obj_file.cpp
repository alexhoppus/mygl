#include "obj_file.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cmath>

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

void Model::triangle(int x0, int y0, int x1, int y1, int x2, int y2, TGAColor color)
{
	line(x0, y0, x1, y1, color);
	line(x1, y1, x2, y2, color);
	line(x2, y2, x0, y0, color);
}

void Model::render(std::string out_file_name, TGAColor color)
{
	int width = image.get_width();
	int height = image.get_height();
	std::vector<Vec3i>::iterator it = datafile.faces.begin();
	for (; it != datafile.faces.end(); it++) {
		Vec3i vertices = *it;
		Vec3f v1 = datafile.vertices[vertices.x];
		Vec3f v2 = datafile.vertices[vertices.y];
		Vec3f v3 = datafile.vertices[vertices.z];
	        int x0 = (v1.x + 1.) * width / 2.;
	        int y0 = (v1.y + 1.) * height / 2.;
	        int x1 = (v2.x + 1.) * width / 2.;
	        int y1 = (v2.y + 1.) * height / 2.;
	        int x2 = (v3.x + 1.) * width / 2.;
	        int y2 = (v3.y + 1.) * height / 2.;
		triangle(x0, y0, x1, y1, x2, y2, color);
	}
	image.write_tga_file(out_file_name.c_str());
	return;
}
