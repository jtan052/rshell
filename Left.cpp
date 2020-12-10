#ifndef LEFT_CPP
#define LEFT_CPP
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../header/Left.h"

Left::Left() : left(0), right("") 
{
    this->id = 7;
}

void Left::setLeft(Base* leftExec) 
{ 
    //cout << "Success1" << endl;
    left = leftExec;
    
}

void Left::setRight(string rightexecname) 
{ 
    //cout << "Success2" << endl;
    right = rightexecname; 
    
}

bool Left::execute() 
{
    // Removing leading whitespace
        int i = 0;
        while (right.at(i) == ' ') {
            i++;
        }
        right = right.substr(i);

    // Removing trailing whitespace
        int a = right.size() - 1;
        while (right.at(a) == ' ') {
            a--;
        }
        right = right.substr(0, a + 1);

	// saves stdinput buffer
	int save = dup(0);
	
	// Opens file for input
	int file = open(right.c_str(),O_RDWR);
	
	// return error if file does not open
	if (file == -1) 
	{
		perror("Could not open file");
		return false;
	}

	// closes previous input
	close(0);
	dup2(file, 0);
    
	// execute left command
	//cout << "Left.cpp: execute()" << endl;
	
	bool wow = left->execute();

	// Restore std output conditions
	close(0);
	dup2(save, 0);
	
	return wow;
}
#endif