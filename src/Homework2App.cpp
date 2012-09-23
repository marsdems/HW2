#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Resources.h"
#include "cinder/text.h"
#include "cinder/gl/Texture.h"
#include "Node.h"
#include "Shape.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Homework2App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void keyDown( KeyEvent event);
	void update();
	void draw();
	void prepareSettings(Settings *settings);
private:
	Node* getSelectedNode(Vec2i mouse_click);
	void bringToFront(Node *selected_node);
	void sendToBack();
	void makeTextBox();
	void reverseOrder();

	Node *sentinel_node;
	Node *node_one;
	Node *node_two;
	Node *node_three;
	Node *node_four;

	Shape *shape_one;
	Shape *shape_two;
	Shape *shape_three;
	Shape *shape_four;

	double frame_number;
	gl::Texture *text_texture;
	bool display_text;
	TextBox *text_box;
};

void Homework2App::setup(){
	frame_number = 0;
	display_text = true;
	makeTextBox();

	shape_one = new Shape(Vec2f(200, 100), 100);
	shape_two = new Shape(Vec2f(150, 150), 100);
	shape_three = new Shape(Vec2f(100, 200), 100);
	shape_four = new Shape(Vec2f(50, 250), 100);
	
	node_one = new Node(shape_one);
	node_two = new Node(shape_two);
	node_three = new Node(shape_three);
	node_four = new Node(shape_four);
	sentinel_node = new Node(node_one, node_four);

	node_one -> add_pointers(node_two, sentinel_node);
	node_two -> add_pointers(node_three, node_one);
	node_three -> add_pointers(node_four, node_two);
	node_four -> add_pointers(sentinel_node, node_three);
}

void Homework2App::makeTextBox(){
	text_box = new TextBox();
	text_box -> setText("Hello!\nPress backspace to move \n   the top shape to the bottom, or\nClick a shape to bring it to the front.\nPress / to reverse the order\nPress ? to dismiss");
	text_box -> setFont(Font("Tahoma", 40));
	text_box->setBackgroundColor(ColorA(0,0,0,0.5));
	text_texture = new gl::Texture(text_box -> render());
}

void Homework2App::reverseOrder(){

	Node* current_ = sentinel_node;
	Node* temp;
	do{
		temp = current_ -> next_;
		current_ -> next_ = current_ -> prev_;
		current_ -> prev_ = temp;
		current_  = temp;
	} while(current_ != sentinel_node);
}

void Homework2App::mouseDown( MouseEvent event ){
	Vec2i mouse_location = event.getPos();

	Node *selected_node = getSelectedNode(mouse_location);

	if(selected_node != NULL)
		bringToFront(selected_node);

}

void Homework2App::keyDown( KeyEvent event){
	if(event.getCode() == 0x0008)
		sendToBack();
	if(event.getChar() == '?')
		display_text = !display_text;
	if(event.getChar() == '/')
		reverseOrder();

}

void Homework2App::sendToBack(){
	Node* first_node = sentinel_node -> prev_;
	sentinel_node -> prev_ = sentinel_node -> prev_ -> prev_;
	sentinel_node -> prev_ -> next_ = sentinel_node;

	first_node -> next_ = sentinel_node -> next_;
	first_node -> prev_ = sentinel_node;

	sentinel_node -> next_ -> prev_ = first_node;
	sentinel_node -> next_ = first_node;
	

}

void Homework2App::bringToFront(Node* clicked_node){
	clicked_node -> prev_ -> next_ = clicked_node -> next_;
	clicked_node -> next_ -> prev_ = clicked_node -> prev_;

	clicked_node -> next_ = sentinel_node;
	clicked_node -> prev_ = sentinel_node -> prev_;

	sentinel_node -> prev_ -> next_ = clicked_node;
	sentinel_node -> prev_ = clicked_node;

}

Node* Homework2App::getSelectedNode(Vec2i mouse_click_location){
	Node* selected_node = sentinel_node -> prev_;
	Node* current_ = sentinel_node -> next_;
	while(current_ != sentinel_node){
		if(current_ -> containsPoint(mouse_click_location))
			selected_node = current_;
		current_ = current_ -> next_;
	}

	return selected_node;

}

void Homework2App::update(){
	frame_number += 0.01;

	Node* current_ = sentinel_node -> next_;
	do{
		current_ -> moveShape(frame_number);
		current_  = current_ -> next_;
	} while(current_ != sentinel_node);
	
}

void Homework2App::draw(){
	//Color background gray
	gl::clear( Color8u(200,200,200));

	Node* current_ = sentinel_node -> next_;
	do{
		current_ -> draw();
		current_  = current_ -> next_;
	} while(current_ != sentinel_node);

	if(display_text)
		gl::draw(*text_texture);
}

void Homework2App::prepareSettings(Settings *settings){
    settings->setWindowSize( 800, 600 );
    settings->setFrameRate( 60.0f );
}

CINDER_APP_BASIC( Homework2App, RendererGl )
