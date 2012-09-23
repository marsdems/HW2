#include "cinder\gl\gl.h"
#include "Shape.h"

using namespace ci;

class Node {
public:
	Node(Shape *nodeData, Node *next, Node *prev);
	Node(Shape *nodeData);
	Node(Node *next, Node *prev);
	void add_pointers(Node *next_node, Node *prev_node);
	void draw();
	bool containsPoint(Vec2i point);
	void moveShape(double frame_number);

	Shape *nodeData_;
	Node *next_;
	Node *prev_;
};