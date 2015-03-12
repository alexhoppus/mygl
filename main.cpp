#include "tgaimage.h"
#include "obj_file.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

int main(int argc, char** argv) {
        //TGAImage image(100, 100, TGAImage::RGB);
        //image.set(52, 41, red);
        //image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	//line(0, 0, 50, 50, image, white);
        //image.write_tga_file("output.tga");
	Model m;
	std::string s("/home/alexhoppus/Desktop/mygl/african_head.obj");
	std::string out_file("render.tga");

	m.datafile.set_file_name(s);
	m.datafile.read_file();
	m.render(out_file, white);
        return 0;
}
