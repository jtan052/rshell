#ifndef RIGHT_CPP
#define RIGHT_CPP
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../header/Right.h"

Right::Right() : left(0), right("") {this->id = 5;}

void Right::setLeft(Base* leftExec) 
{ 
    this->left = leftExec;
}

void Right::setRight(string rightexecname) 
{ 
    this->right = rightexecname; 
    
}

bool Right::execute() {
    
	// Removing leading whitespace
	    int i = 0;
	    while (right.at(i) == ' ') {
	        i++;
	    }
	    right = right.substr(i);
	    
    // Removing trailing whitespace
    int end = right.size() - 1;
    while (right.at(end) == ' ') {
        end--;
    }
    right = right.substr(0, end + 1);
    
	// saves stdinput buffer
	int intsave = dup(1);
	
	// Opens file for input
	int filecheck = open(right.c_str(),O_WRONLY| O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	
	// return error if file does not open
	if (filecheck == -1) 
	{
		perror("Error opening file");
		return false;
	}
    
	// closes input previous
	close(1);
	dup2(filecheck, 1);
	
	//cout << "testing" << endl;
	
	// execute command on the left
	bool work = left->execute();
	// Restore std output conditions
	
	close(1);
	dup2(intsave, 1);

	return work;
}
#endif