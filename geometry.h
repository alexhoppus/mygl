#include <vector>
#include <cassert>
#include <iostream>
#include <math.h>
#include <iostream>
using namespace std;
template <typename T> struct vec3 {
	vec3() { x = T(); y = T(); z = T(); }
	vec3(T t1, T t2, T t3) : x(t1), y(t2), z(t3) {};
	T x, y, z;
	vec3 operator+(const vec3 &val) {
		return vec3<T>(x + val.x, y + val.y,
				z + val.z);
	};
        vec3 operator-(const vec3 &val) {
                return vec3<T>(x - val.x, y - val.y,
                                z - val.z);
        };
	vec3 operator*(const float &val) {
                return vec3<T>(x * val, y * val, z * val);
        };
	void print() {	
		cout << "[" << x << ", " << y << ", " << z << "]" << endl;
	}
	vec3<T> vector_product(vec3<T> val) {
		/*A^B = (AyBz-AzBy, AzBx-AxBz,AxBy-AyBx)*/
		return vec3<T>(y*val.z - z*val.y, z*val.x - x*val.z,
			x * val.y - y * val.x);
	}

        float dot_product(vec3<T> val) {
                /*A^B = (AyBz-AzBy, AzBx-AxBz,AxBy-AyBx)*/
                return (float)(x*val.x + y*val.y + z*val.z);
        }


	float dist() {
		return sqrt(x*x+y*y+z*z);
	}
	vec3<float> normalize() {
		float d_inv = 1.0 / dist();
		x = x * (float) d_inv;
		y = y * (float) d_inv;
		z = z * (float) d_inv;
	}
	
};

template <typename T> struct vec2 {
	vec2() { x = T(); y = T();}
	vec2(T t1, T t2) : x(t1), y(t2) {};
	T x, y;
	vec2 operator+(const vec2 &val) {
                return vec2<T>(x + val.x, y + val.y);
        };
        vec2 operator-(const vec2 &val) {
                return vec2<T>(x - val.x, y - val.y);
        };
        vec2 operator*(const float &val) {
                return vec2<T>(x * val, y * val);
        };

};

typedef vec3<float> Vec3f;
typedef vec3<int>   Vec3i;
typedef vec2<float> Vec2f;
typedef vec2<int>   Vec2i;

