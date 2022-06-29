#include <iostream>
#include <array>

struct vec2
{
    vec2() {};
	vec2(float _x, float _y) : x(_x), y(_y) {};

	float x, y; 
};

struct triangle {
	triangle(vec2 _point1, vec2 _point2, vec2 _point3) {
		points[0] = _point1;
		points[1] = _point2;
		points[2] = _point3;
	};

	std::array<vec2, 3> points;
};

bool isColliding(const triangle& triangle1, const triangle& triangle2 ) {
	std::cout << triangle1.points.at(0).x << std::endl;
}

int main() {
	vec2 p1(0, 0), p2(2, 0), p3(1, 1.5);
	vec2 p4(1.5, 1.5), p5(3.5, 1.5), p6(3.5, 3);
	vec2 p7(3, 2.5), p8(4, 2.5), p9(3, 3.5);
	triangle t1(p1, p2, p3);
	triangle t2(p4, p5, p6);
	triangle t3(p7, p8, p9);

 	isColliding(t3, t2);

	return 0;
}