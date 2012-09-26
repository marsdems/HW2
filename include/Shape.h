#ifndef SHAPE_H
#define SHAPE_H

#include "cinder\gl\gl.h"

using namespace ci;

class Shape {
public:
	Shape(Vec2f center, float radius, ColorA color_);
	void draw();
	bool containsPoint(Vec2i point);
	void moveShape(double frame_number);
private:
	Vec2f center_;
	Vec2f start_center_;
	float radius_;
	ColorA color_;
};

#endif