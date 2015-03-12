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
	void triangle(int x0, int y0, int x1, int y1, int x2, int y2, TGAColor color);
public:
	Model() : image(1024, 768, TGAImage::RGB) {};
	Obj_file datafile;
	void render(std::string out_file_name, TGAColor color);
};

