/* \author Aaron Brown */
// Quiz on implementing kd tree

#include "../../render/render.h"
#include <math.h>

const unsigned int SPACE_DIMENTION = 2;
// Structure to represent node of kd tree
struct Node
{
	std::vector<float> point;
	int id;
	Node* left;
	Node* right;

	Node(std::vector<float> arr, int setId)
	:	point(arr), id(setId), left(NULL), right(NULL)
	{}

	~Node()
	{
		delete left;
		delete right;
	}
};

struct KdTree
{
	Node* root;

	KdTree()
	: root(NULL)
	{}

	~KdTree()
	{
		delete root;
	}

	//My question is: Why we do all this in header file instead of kdtree.cpp ??
	//May I make normal kdtree.cpp file with calculation and transform this .h file to real .h file?
	//I left all this like "it is" for pass porpouse

	void insertHelper(Node** node, unsigned int depth, std::vector<float> point, int id) {
		
		if (*node = NULL) {
			*node = new Node(point, id);
		}
		else {
			
			unsigned int current_dim = depth % SPACE_DIMENTION;	///we will look for x or y for 2D

			Node* next_node = nullptr;

			if (point[current_dim] < ((*node)->point[current_dim])) {
			
				next_node = (*node)->left;
			
			}
			else {
			
				next_node = (*node)->right;
				
			}

			insertHelper(&next_node, depth+1, point, id);
		}

	}


	void insert(std::vector<float> point, int id)
	{
		// TODO: Fill in this function to insert a new point into the tree
		// the function should create a new node and place correctly with in the root 
		insertHelper(&root, 0, point, id);

	}

	bool withinDistanceTolerance(float pointCoordinate, float targetCoordinate, float distanceTolerance) {
	
		return ((pointCoordinate>=(targetCoordinate - distanceTolerance)) && (pointCoordinate <= (targetCoordinate + distanceTolerance)));
	
	}

	void searchHelper(std::vector<float> target, Node* node, int depth, float distanceTolerance, std::vector<int>& ids) {
	
		if (node != NULL) {
		
			if (withinDistanceTolerance(node->point[0], target[0], distanceTolerance) && withinDistanceTolerance(node->point[1], target[1], distanceTolerance)) {
			
				float distance = sqrt(pow((nodepoint[0]-target[0]), 2) + pow((nodepoint[1] - target[1]), 2));

				if (distance <= distanceTolerance)
				{
					ids.emplace_back(distance);
				}
			
			}

			unsigned int d = depth % SPACE_DIMENTION;
			if ((target[d]-distanceTolerance)<node->point[d]) {
				searchHelper(target, node->left, depth+1, distanceTolerance, ids);
			}
			if ((target[d] + distanceTolerance) > node->point[d])
			{
				searchHelper(target, node->right, depth + 1, distanceTolerance, ids);
			}
		
		}
	
	}

	// return a list of point ids in the tree that are within distance of target
	std::vector<int> search(std::vector<float> target, float distanceTolerance)
	{
		std::vector<int> ids;
		// I reserved fix size to avoid unnececary dealocation, espetially for first some add
		// I choose size/2 for have only one dealocation in case we will have more than half of points within distance tolerance
		ids.reserve(target.size()/2);

		searchHelper(target, root, 0, distanceTolerance, ids);

		return ids;
	}
	

};




