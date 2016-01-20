#ifndef POINT_HPP
#define POINT_HPP
#include <cmath>
class Point {
public:
	double x, y;
	Point(double x = 0, double y = 0) {	
		this->x = x;
		this->y = y;
	}
	double operator * (Point b) {
		return this->x*b.y - this->y*b.x;
	}
	Point operator - (Point b) {
		return Point(this->x-b.x, this->y-b.y);
	}
	double operator / (Point a) { // dot product
		return this->x*a.x + this->y*a.y;
	}
	double dis(Point a) {
		return sqrt((this->x-a.x)*(this->x-a.x) + (this->y-a.y)*(this->y-a.y));
	}
	double val() {
		return sqrt(this->x*this->x + this->y*this->y);
	}
};
bool operator < (Point a, Point b) {
	return (a.y > b.y) || (a.y == b.y && a.x < b.x);
}
#endif
