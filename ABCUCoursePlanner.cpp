//============================================================================
// Name        : ABCUCoursePlanner.cpp
// Author      : Nicholas Ciesla
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Course {
	string courseNumber; // unique identifier
	string courseName;
	vector<string> prerequisites; //vector for pre reqs

};

// Internal structure for tree node
/***********************************************************************READ THIS PROF!
 * Just a note here, When I loaded this file into eclipse. I noticed it had a bucnh of random Hasbatble code in the Node Struct
 * Not even code for a node, fairly certain it was an insert function. May want to check that out.
 * *********************************************************************
 */
struct Node {
	Course course;
	Node* left;
	Node* right;

	// default constructor
	Node() {
		left = nullptr;
		right = nullptr;
	}

	// initialize with a bid
	Node(Course aCourse) {
		course = aCourse;
		left = nullptr;
		right = nullptr;
	}

};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
	Node* root;

	void inOrder(Node* node);
	Node* removeNode(Node* node, string bidId);
	void DestroyTree(Node* node);


public:
	BinarySearchTree();
	virtual ~BinarySearchTree();
	void InOrder();
	void Insert(Course course);
	void Remove(string courseNumber);
	Course Search(string courseNumber);
	int coursesLoaded;
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
	//root is equal to nullptr
	this->root = nullptr;
	this->coursesLoaded = 0;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {

	DestroyTree(this->root);

}

void BinarySearchTree::DestroyTree(Node* node) {
	// RECURSIVE DESTRUCTOR UTILITY
	//Postorder traversal
	if (node != nullptr) {
		DestroyTree(node->left);
		DestroyTree(node->right);
		delete node;
	}
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
	if (this->root == nullptr) {
		cout << "Tree empty" << endl;
	}
	else {
		// call inOrder fuction and pass root
		inOrder(this->root);
	}

}


/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Course course) {
	// FIXME (5) Implement inserting a bid into the tree
	// create a new node with given course
	Node* node = new Node(course);
	// create a node for traversal and an int for node placement
	Node* curr;
	string key;
	// if root equal to null ptr (tree empty)
	if (this->root == nullptr) {
		this->root = node;
		this->coursesLoaded++;
	}
	else {
		// assign curr to the root
		curr = this->root;
		// set ID of bid to key.
		key = course.courseNumber;
		// search for node placement position
		while (curr != nullptr) {
			// if key is less than curr's key
			if (key < curr->course.courseNumber) {
				// if curr's left branch is open
				if (curr->left == nullptr) {
					// set curr's left branch to node
					curr->left = node;
					// set curr to null to break loop
					curr = nullptr;
					// increment bids loaded
					this->coursesLoaded++;
				}
				else {
					// advance curr node left
					curr = curr->left;
				}
			}
			else {
				if (curr->right == nullptr) {
					// set curr's right branch to node
					curr->right = node;
					// set curr to null to break loop
					curr = nullptr;
					// increment bids loaded
					this->coursesLoaded++;
				}
				else {
					// advance curr node right
					curr = curr->right;
				}
			}
		}
	}
}


//* Remove a bid (keeping in for future reference

void BinarySearchTree::Remove(string courseNumber) {
	// Pointers for traversal and operations
	Node* par = nullptr;
	Node* curr = this->root;
	Node* suc = nullptr;
	Course course;
	string key = courseNumber;


	while (curr != nullptr) { //search for bid with loop
		// if bid is found
		if (key == curr->course.courseNumber) {
			if (curr->left == nullptr && curr->right == nullptr) { // remove leaf
				if (par == nullptr) { //Node is root
					this->root = nullptr;
				}
				else if (par->left == curr) { //Node is left of prev
					par->left = nullptr;
				}
				else { //Node is right of prev
					par->right = nullptr;
				}
			}
			else if (curr->right == nullptr) { // remove node with only left child
				if (par == nullptr) { //Node is root
					this->root = curr->left;
				}
				if (par->left == curr) { //Node is left of prev
					par->left = curr->left;
				}
				else { //Node is right of prev
					par->right = curr->left;
				}
			}
			else if (curr->left == nullptr) { // remove node with only right child
				if (par == nullptr) { //Node is root
					this->root = curr->right;
				}
				if (par->left == curr) { //Node is left of prev
					par->left = curr->right;
				}
				else { //Node is right of prev
					par->right = curr->right;
				}
			}
			else { // remove node with two children

				suc = curr->right;
				//loop to find successor
				while (suc->left != nullptr) {
					suc = suc->left;
				}
				course = suc->course; //save value, remove suc, swap value
				Remove(course.courseNumber);
				curr->course = course;

			}
			this->coursesLoaded--;
			return;
		}
		else if (key < curr->course.courseNumber) {
			// advance curr left
			par = curr;
			curr = curr->left;
		}
		else {
			// advance curr right (key is larger than curr's bid)
			par = curr;
			curr = curr->right;
		}
	}
	// if this point is reached, the bid was not found.
	cout << courseNumber << " not found" << endl;
}

/**
 * Search for a bid
 */
Course BinarySearchTree::Search(string courseNumber) {
	// set current node equal to root and create bid
	Node* curr = this->root;
	Course course;
	unsigned int i;
	// set key to bidId converted to int
	string key = courseNumber;

	for (i = 0; i < key.size(); i++) { // make alpha charecters uppercase
		if (isalpha(key.at(i))) {
			key.at(i) = toupper(key.at(i));
		}
	}

	while (curr != nullptr) {
		// if current node is a match
		if (key == curr->course.courseNumber) {
			// set bid to curr's bid
			course = curr->course;
			// set curr to null to break loop
			curr = nullptr;
		}        // if curr's bid is less than key
		else if (key < curr->course.courseNumber) {
			// advance curr left
			curr = curr->left;
		}
		else {
			// advance curr right (key is larger than curr's bid)
			curr = curr->right;
		}
	}
	// return bid, even if empty.
	return course;
}


void BinarySearchTree::inOrder(Node* node) {
	//if node is equal to null ptr
	if (node == nullptr) {
		return;
	}

	//InOrder left
	inOrder(node->left);
	//output course number and course name
	cout << node->course.courseNumber << ": " << node->course.courseName << endl;
	//InOder right
	inOrder(node->right);
}


//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayCourse(Course course) {
	unsigned int i;

	cout << course.courseNumber << ": " << course.courseName << endl;
	for (i = 0; i < course.prerequisites.size(); i++) {

		cout << "    " << course.prerequisites.at(i) << endl;
	}
	return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
int loadCourses(string filePath, BinarySearchTree* bst) {
	cout << "Loading course file " << filePath << endl;

	// Create file reader
	ifstream inFS;
	string line;
	unsigned int i;


	inFS.open(filePath);

	if (!inFS.is_open()) {
		cout << "Could not open " << filePath << endl;
		return -1;
	}
	// loop to read lines from text file
	while (!inFS.eof()) {

		Course course;
		vector<string> pieces;
		//get line from file
		getline(inFS, line);

		// var for finding index of commas
		size_t pos = 0;
		while ((pos = line.find(',')) != string::npos) {
			pieces.push_back(line.substr(0, pos)); // add peice to peices
			line.erase(0, pos + 1); // trim peice off of line
		}

		pieces.push_back(line); // add last peice

		line.erase(); // clear line

		if (pieces.size() < 2) {
			// if not enough info
			cout << "Data Format error, please try again" << endl;
			return -1;
		}

		// assign number and name
		course.courseNumber = pieces.at(0);
		course.courseName = pieces.at(1);

		// if course has pre reqs, add them to prerequisites
		if (pieces.size() > 2) {
			for (i = 2; i < pieces.size(); i++) {
				course.prerequisites.push_back(pieces.at(i));
			}
		}

		// push this Course
		bst->Insert(course);
	}

	return 1;

}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
	str.erase(remove(str.begin(), str.end(), ch), str.end());
	return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

	// process command line arguments
	string filePath, courseNumber;
	switch (argc) {
	case 2:
		filePath = argv[1];
		courseNumber = "CSCI400";
		break;
	case 3:
		filePath = argv[1];
		courseNumber = argv[2];
		break;
	default:
		filePath = "ABCU_Advising_Program_Input.txt";
		courseNumber = "CSCI400";
	}

	// Define a timer variable
	clock_t ticks;

	// Define a binary search tree to hold all bids
	BinarySearchTree* bst;
	bst = new BinarySearchTree;

	Course course;

	int choice = 0;
	while (choice != 9) {
		cout << "Menu:" << endl;
		cout << "  1. Load Courses" << endl;
		cout << "  2. Print Course List" << endl;
		cout << "  3. Print Course" << endl;
		cout << "  9. Exit" << endl;
		cout << "Enter choice: ";
		cin >> choice;

		switch (choice) {

		case 1:
			
			bst = new BinarySearchTree;

			// Initialize a timer variable before loading bids
			ticks = clock();

			// Complete the method call to load the bids
			if (loadCourses(filePath, bst) == -1) {
				// if fails, reassign bst to blank tree.
				bst = new BinarySearchTree;
			}
			else {
				// Calculate elapsed time and display result
				ticks = clock() - ticks; // current clock ticks minus starting clock ticks
				cout << "time: " << ticks << " clock ticks" << endl;
				cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
				// print number of bids loaded
				cout << bst->coursesLoaded << " Courses loaded." << endl;
			}

			break;

		case 2:
			bst->InOrder();
			break;

		case 3:
			cout << "Please enter Course Number:";
			cin >> courseNumber;

			ticks = clock();
			course = bst->Search(courseNumber);

			ticks = clock() - ticks;



			//print course info
			if (!course.courseNumber.empty()) {
				displayCourse(course);
			}
			else {
				cout << "Course " << courseNumber << " not found!" << endl;
			}

			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

			break;

		case 9:

			cout << "Good bye." << endl;

			return 0;

			break;

		}

	}

}
