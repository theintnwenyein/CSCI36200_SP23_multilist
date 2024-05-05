#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


struct Node{
	int studentID;
	int classID;
	int grade;
	Node* next_student;
	Node* next_class;
}; // end Node

// Dummy nodes
// If Node has a constructor like Node(student,class,grade) then the dummy nodes will be Node* studentIndex = new Node(0,0,0)
Node* studentIndex = nullptr;
Node* classIndex = nullptr;

// function to insert a new node to the list
void createNode(int student, int course, int grade){
	Node* newNode = new Node();
	newNode->studentID = student;
	newNode->classID = course;
	newNode->grade = grade;
	newNode->next_student = nullptr;
	newNode->next_class = nullptr;
	
	// Need to search for the wanted student and course first before creating a new node
	
	// if there is no student yet, make the new node a header
	if(studentIndex == nullptr){
		studentIndex = newNode;
	}// end if

	// If there is at least one student in the student list
	else{
		Node* currentNode = studentIndex;
		Node* previousNode = nullptr;

		// Keep searching the wanted student node if the list is not empty and the current node's student ID is less than the wanted student ID
		while(currentNode != nullptr && currentNode->studentID < student){
			previousNode = currentNode;
			currentNode = currentNode->next_student;
		}// end while

		// If there is only one student in the list and it is the wanted student, make the newNode the header
		if(previousNode == nullptr){
			newNode->next_student = studentIndex;
			studentIndex = newNode;
		}// end if

		// if the list is not empty and there is more than one student(and found the wanted student), put the newNode in the list between the previousNode and currentNode
		else{
			previousNode->next_student = newNode;
			newNode->next_student = currentNode;
		}// end else
	}// end else



	// If there is no classes yet in the list, make the newNode the class header
	if(classIndex == nullptr){
		classIndex = newNode;
	}// end if

	// If there is at least one class in the list
	else{
		Node* currentNode = classIndex;
		Node* previousNode = nullptr;

		// Keep searching for the wanted class as long as the currentNode is not empty and its classID is smaller than the watned classID
		while(currentNode != nullptr && currentNode->classID < course){
			previousNode = currentNode;
			currentNode = currentNode->next_class;
		}// end while

		// If there is only one class in the list and it is the wanted class, make the newNode the class header
		if(previousNode == nullptr){
			newNode->next_class = classIndex;
			classIndex = newNode;
		}// end if

		// If there is more than one class (and found the wanted class), put the newNode in the list between the previousNode and the currentNode
		else{
			previousNode->next_class = newNode;
			newNode->next_class = currentNode;
		}// end else
	}// end else
}// end createNode


// Function to print the list of active students in each nonempty class 
void printClasses(){
	Node* currentNode = classIndex;

	// While the class list is not empty, print out the class number and the student lists of those classes
	while(currentNode != nullptr){
		int classID = currentNode->classID;
		std::cout<<"Class "<< classID << ": Students ";
		while(currentNode != nullptr && currentNode->classID == classID){ // make sure to print only the students with the same classID
			// we don't want to print all the students' IDs after the currentNode since those studentNodes may have different classIDs
			std::cout<<currentNode->studentID<<", ";
			currentNode = currentNode->next_student;
		}// end while
		std::cout<<" "<<std::endl;
	}// end while
}// end printClasses


// Function to print the list of classes each active student takes
void printStudents(){
	Node* currentNode = studentIndex;

	// If the student list is not empty, print out the studentID and the list of classes associated with each studentID
	while(currentNode != nullptr){
		int studentID = currentNode->studentID;
		std::cout<<"Students "<<studentID<<": Classes ";
		while(currentNode != nullptr && currentNode->studentID == studentID){ // Make sure to only print the classes associate with the same studentID
			// If the next node's studentID is different, we don't want to print its class but keep searching until the end of the list
			std::cout<<currentNode->classID<<", ";
			currentNode = currentNode->next_class;
		}// end while
		std::cout<<" "<<std::endl;
	}// end while
}// end printStudents
int main(){
	std::ifstream inputFile; // file to read
	std::string line;
	std::stringstream ss;
	std::string studentID,courseID,grade;

	inputFile.open("multilist_input.txt"); // open the file, get each line, and break down each line into three pieces of data
	while(getline(inputFile,line)){
		ss.clear();
		ss.str(line);

		// Set comma as the delimiter
		getline(ss, studentID, ',');
		getline(ss, courseID, ',');
		getline(ss, grade, ',');

		// change from string to int
		int student = stoi(studentID);
		int course = stoi(courseID);
		int grades = stoi(grade);

		createNode(student,course,grades);

	}// end while
	
	inputFile.close(); // Close the file

	printStudents();
	std::cout<<" "<<std::endl;
	printClasses();
	return 0;
}// end main
