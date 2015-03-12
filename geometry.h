#include <vector>
#include <cassert>
#include <iostream>

template <typename T> struct vec3 {
    vec3() { x = T(); y = T(); z = T(); }
    vec3(T t1, T t2, T t3) : x(t1), y(t2), z(t3) {};
    T x, y, z;
};

typedef vec3<float> Vec3f;
typedef vec3<int>   Vec3i;

