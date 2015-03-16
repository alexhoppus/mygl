#include "geometry.h"
#include "tgaimage.h"

class Obj_file {
private:
        std::string file_name;
public:
        std::vector<Vec3f> vertices;
        std::vector<Vec3i> faces;
	Obj_file() {};
        Obj_file(std::string input_file) : file_name(input_file) {};
        int read_file();
	void set_file_name(std::string s) {file_name = s;};
};

class Model {
private:
	TGAImage image;
	void line(int x0, int y0, int x1, int y1, TGAColor color);
	int point_in_triangle(Vec2i p, Vec2i p0, Vec2i p1, Vec2i p2);
public:
	Model() : image(1024, 768, TGAImage::RGB) {};
	void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAColor color);
	Obj_file datafile;
	void render(std::string out_file_name, TGAColor color);
};

