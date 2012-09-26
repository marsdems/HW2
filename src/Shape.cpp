#include "Shape.h"

// Added ColorA as a parameter to allow for different colors
Shape::Shape(Vec2f center, float radius, ColorA color){
	start_center_ = center;
	center_ = center;
	radius_ = radius;
	color_ = color;
}

void Shape::draw(){
	//Enabled alpha blending and changed Color to ColorA
	gl::enableAlphaBlending();
	gl::color(ColorA(0,0,0, .5f));
	gl::drawSolidCircle(center_, radius_);
	gl::color(ColorA(color_));
	gl::drawSolidCircle(center_, radius_-3);
}

bool Shape::containsPoint(Vec2i point){
	return (sqrt(pow((point.x-center_.x),2)+pow((point.y-center_.y),2))<=radius_);
}

void Shape::moveShape(double frame_number){
	center_.x = 300 - (300-start_center_.x)*cos(frame_number) + start_center_.x;
	center_.y = abs(start_center_.y*sin(frame_number))+ start_center_.y;
}