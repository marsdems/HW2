#include "Node.h"

Node::Node(Shape *nodeData, Node *next, Node *prev){
	nodeData_ = nodeData;
	next_ = next;
	prev_ = prev;
}

Node::Node(Shape *nodeData){
	nodeData_ = nodeData;
}

Node::Node(Node *next, Node *prev){
	next_ = next;
	prev_ = prev;
}

void Node::add_pointers(Node *next_node, Node *prev_node){
	next_ = next_node;
	prev_ = prev_node;
}

void Node::draw(){
	nodeData_ -> draw();
}

bool Node::containsPoint(Vec2i point){
	return nodeData_ -> containsPoint(point);
}

void Node::moveShape(double frame_number){
	return nodeData_ -> moveShape(frame_number);
}
