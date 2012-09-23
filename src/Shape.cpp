#include "Shape.h"

Shape::Shape(Vec2f center, float radius){
	start_center_ = center;
	center_ = center;
	radius_ = radius;
}

void Shape::draw(){
	gl::color(Color8u(0,0,0));
	gl::drawSolidCircle(center_, radius_);
	gl::color(Color8u(255,255,255));
	gl::drawSolidCircle(center_, radius_-3);
}

bool Shape::containsPoint(Vec2i point){
	return (sqrt(pow((point.x-center_.x),2)+pow((point.y-center_.y),2))<=radius_);
}

void Shape::moveShape(double frame_number){
	center_.x = 300 - (300-start_center_.x)*cos(frame_number) + start_center_.x;
	center_.y = abs(start_center_.y*sin(frame_number))+ start_center_.y;
}