#include <iostream>
#include <algorithm>
#include <cmath>

class Point {
public:
	int x;
	int y;

	Point() : x(0), y(0) {
		printCreate();
	}
	Point(const int x, const int   y) : x(x), y(y) {
		printCreate();
	}
	Point(const Point& a) : x(a.x), y(a.y) {
		printCreate();
	}
	Point(const Point* a) : x(a->x), y(a->y) {
		printCreate();
	}

	~Point() {
		//std::cout << "Delite Point:" << (int)this % 1000 << std::endl;
	}
	double distTo(const Point& a);
	double distTo(const Point* a);
private:
	void printCreate() {
		//std::cout << "Point: " << x << '\t' << y << '\t' << "id " << (int)this % 1000 << std::endl;
	}

};

double Point::distTo(const Point& a) {
	return sqrt(pow(a.x - x, 2) + pow(a.y - y, 2));
}
double Point::distTo(const Point* a) {
	return sqrt(pow(a->x - x, 2) + pow(a->y - y, 2));
}




class Circle : public Point {
public:
	int r;

	Circle() : Point(0, 0), r(1) {
		printCreate();
	}
	Circle(const int x, const int y, const int r) :Point(x, y), r(r) {
		printCreate();
	}
	Circle(const Circle& a) :Point(a.x, a.y), r(a.r) {
		printCreate();
	}
	Circle(const Circle* a) :Point(a->x, a->y), r(a->r) {
		printCreate();
	}
	double distTo(const Circle& a);
	double distTo(const Circle* a);

	double square();
	~Circle() {
		//std::cout << "Delite Circle:" << (int)this % 1000 << std::endl;
	}

private:
	void printCreate() {
		//std::cout << "Circle: " << x << '\t' << y << '\t' << r << '\t' << "id " << (int)this % 1000 << std::endl;
	}
};

double Circle::distTo(const Circle& a) {
	double dist = sqrt(pow(a.x - x, 2) + pow(a.y - y, 2));
	return dist;
}

double Circle::distTo(const Circle* a) {
	double dist = sqrt(pow(a->x - x, 2) + pow(a->y - y, 2));
	return dist;
}
double Circle::square() {
	return  3.14 * pow(r, 2);
}



class PairOfCircles {
protected:
	Circle* circle1;
	Circle* circle2;
public:
	PairOfCircles() {
		circle1 = new Circle(1, 1, 1);
		circle2 = new Circle(2, 2, 1);
		printCreate();
	}
	PairOfCircles(int x1, int y1, int r1, int x2, int y2, int r2) {
		circle1 = new Circle(x1, y1, r1);
		circle2 = new Circle(x2, y2, r2);
		printCreate();
	}
	PairOfCircles(const Circle& a, const Circle& b) {
		circle1 = new Circle(a);
		circle2 = new Circle(b);
		printCreate();
	}
	PairOfCircles(const Circle* a, const Circle* b) {
		circle1 = new Circle(a);
		circle2 = new Circle(b);
		printCreate();
	}
	PairOfCircles(const PairOfCircles* a) {
		circle1 = new Circle(a->circle1);
		circle2 = new Circle(a->circle2);
		printCreate();
	}
	PairOfCircles(const PairOfCircles& a) {
		circle1 = new Circle(a.circle1);
		circle2 = new Circle(a.circle2);
		printCreate();
	}
	~PairOfCircles() {
		//std::cout << "Delite PairOfCircles:" << (int)this % 1000 << std::endl;
		delete circle1;
		delete circle2;
	}

	double square();


private:
	void printCreate() {
		//std::cout << "PairOfCircles: " << circle1 << '\t' << circle2 << '\t' << "id" << (int)this % 1000 << std::endl;
	}
};


double  PairOfCircles::square() {

	float distance = circle1->distTo(circle2);

	if (distance >= circle1->r + circle2->r) {
		// Нет пересечений

		return circle1->square() + circle2->square();
	}
	else if (distance <= fabs(circle1->r - circle2->r)) {
		// Если окружность внутри другой
		return std::max(circle1->square(), circle2->square());
	}
	else {
		// Если пересекаются
		float f1, f2;
		float s1, s2;
		f1 = 2 * acos((pow(circle1->r, 2) - pow(circle2->r, 2) + pow(distance, 2)) / (2 * circle1->r * distance));
		f2 = 2 * acos((pow(circle2->r, 2) - pow(circle1->r, 2) + pow(distance, 2)) / (2 * circle2->r * distance));
		s1 = (pow(circle1->r, 2) * (f1 - sin(f1))) / 2;
		s2 = (pow(circle2->r, 2) * (f2 - sin(f2))) / 2;
		return circle1->square() + circle2->square() - (s1 + s2);
	}
	return 1;
}




