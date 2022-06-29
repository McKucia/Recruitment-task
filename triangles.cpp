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

// bool inTriangle(const triangle& triangle, const vec2& point) {

// 	auto p1 = triangle.points[0], p2 = triangle.points[1], p3 = triangle.points[2];

//     float AB = (point.y - p1.y)*(p2.x - p1.x)  -  (point.x - p1.x)*(p2.y - p1.y);
//     float CA = (point.y - p3.y)*(p1.x - p3.x)  -  (point.x - p3.x)*(p1.y - p3.y);
//     float BC = (point.y - p2.y)*(p3.x - p2.x)  -  (point.x - p2.x)*(p3.y - p2.y);

//     if (AB * BC > 0.f && BC * CA > 0.f)
//         return true;
//     return false;    
// }

bool isColliding(triangle& triangle1, triangle& triangle2 ) {
	triangle *t1 = &triangle1;
	triangle *t2 = &triangle2;

	for(int shape = 0; shape < 2; shape++) {
		if(shape == 1) {
			t1 = &triangle2;
			t2 = &triangle1;
		}

		for(int a = 0; a < t1->points.size(); a++) {
			int b = (a + 1) % t1->points.size(); // zapobieganie przed wyjsciem poza tablice
			vec2 axisProjection( -(t1->points[b].y - t1->points[a].y), t1->points[b].x - t1->points[a].x );

			float minT1 = INT_MAX, maxT1 = INT_MIN;
			for(int p = 0; p < t1->points.size(); p++) {
				float q = (t1->points[p].x * axisProjection.x + t1->points[p].y * axisProjection.y);
				minT1 = std::min(minT1, q);
				maxT1 = std::max(maxT1, q);
			}

			float minT2 = INT_MAX, maxT2 = INT_MIN;
			for(int p = 0; p < t2->points.size(); p++) {
				float q = (t2->points[p].x * axisProjection.x + t2->points[p].y * axisProjection.y);
				minT2 = std::min(minT2, q);
				maxT2 = std::max(maxT2, q);
			}

			if(!(maxT2 >= minT1 && maxT1 >= minT2)) 
				return false; 
		}
	}

	return true;
}

int main() {
	vec2 p1(0, 0), 		// a
		p2(2, 0), 		// b
		p3(1, 1.5), 	// c
		p4(1.5, 1.5), 	// d
		p5(3.5, 1.5), 	// e
		p6(3.5, 3), 	// f
		p7(3, 2.5), 	// h
		p8(5.5, 4), 	// i
		p9(3.5, 3.5),	// g
		p10(3.5, 2.5), 	// j
		p11(5, 2), 		// k
		p12(3.5, 1.5), 	// e
		p13(1, 1), 		// m
		p14(1, 0.5), 	// n
		p15(4, 2), 		// l
		p16(0.5, 3.5), 	// o
		p17(2, 4),		// p
		p18(4.5, 2.5), 	// q
		p19(4.5, 1.5), 	// r
		p20(5.5, 2); 	// s

	triangle t1(p1, p2, p3), // ABC
		t2(p4, p5, p6),		 // DEF
		t3(p7, p8, p9),		 // GHI
		t4(p10, p11, p12),	 // JKE
		t5(p13, p14, p15), 	 // MNL
		t6(p16, p17, p3),	 // OPC
		t7(p18, p19, p20);	 // QSR

	std::cout << isColliding(t1, t2) << std::endl; // false
	std::cout << isColliding(t2, t3) << std::endl; // true
	std::cout << isColliding(t1, t3) << std::endl; // false
	std::cout << isColliding(t5, t1) << std::endl; // true
	std::cout << isColliding(t5, t4) << std::endl << std::endl ; // true

	std::cout << isColliding(t4, t2) << std::endl; // true
	std::cout << isColliding(t7, t5) << std::endl; // false
	std::cout << isColliding(t6, t1) << std::endl; // true
	std::cout << isColliding(t5, t2) << std::endl; // true


	return 0;
}