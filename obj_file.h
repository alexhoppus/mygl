#include "geometry.h"
class Obj_file {
private:
        std::string file_name;
        std::vector<Vec3f> vertices;
        std::vector<Vec3i> faces;
public:
        Obj_file(std::string input_file) : file_name(input_file) {};
                
        void read_file();
};

