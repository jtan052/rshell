#ifndef APPEND_CPP
#define APPEND_CPP
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../header/Append.h"

Append::Append() : left(0), right("") 
{
    this->id = 6;
}

void Append::setLeft(Base* leftExec) 
{ 
    left = leftExec;
    
}

void Append::setRight(string rightexecname) 
{ 
    right = rightexecname; 
    
}


bool Append::execute() {
    //cout << "entered the execute for apppend" << endl;
    // Removing leading whitespace
    if (right.at(0) == ' ') {
        unsigned i = 0;
        while (right.at(i) == ' ') {
            i++;
        }
        right = right.substr(i);
    }

    // Removing trailing whitespace
    if (right.at(right.size() - 1) == ' ') { 
        unsigned i = right.size() - 1;
        while (right.at(i) == ' ') {
            i--;
        }
        right = right.substr(0, i+1);
    }
    
    //cout << "got here" << endl;
    //cout << "APPEND.cpp: 42" << endl;
	// saves stdinput buffer
	int intsave = dup(1);
	
	// Opens filecheck for input
	int filecheck = open(right.c_str(), O_CREAT|O_APPEND|O_RDWR);
	
	// return error if filecheck does not open
	if (filecheck == -1) 
	{
		perror("Could not open filecheck");
		return false;
	}
    //cout << "APPEND.cpp: 55" << endl;
	// closes previous input
	close(1);
	dup2(filecheck, 1);

	// execute left command
	
	bool ifexec = left->execute();

	// Restore std output conditions
	close(1);
	dup2(intsave, 1);
	
	return ifexec;
}
#endif