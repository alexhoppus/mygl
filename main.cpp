#include "tgaimage.h"
#include "obj_file.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

int main(int argc, char** argv) {
	Model m;
	std::string s("/home/alexhoppus/Desktop/OpenGL/mygl/african_head.obj");
	std::string out_file("render.tga");

	m.datafile.set_file_name(s);
	m.datafile.read_file();
	m.render(out_file, white);

        return 0;
}
