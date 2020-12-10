#ifndef PIPE_CPP
#define PIPE_CPP
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdlib>
#include <string.h>
#include <vector>
#include "../header/Pipe.h"

Pipe::Pipe() : left(0), right("") 
{
    this->id = 8;
}

void Pipe::setLeft(Base* leftExec) 
{ 
    //cout << "Pipe.cpp: setLeft(Base*)" << endl;
    left = leftExec; 
    //cout << "Pipe.cpp: setLeft(Base*) END" << endl;
}

void Pipe::setRight(string rightexecname) 
{ 
    //cout << "Pipe.cpp: setRight(string)" << endl;
    right = rightexecname; 
    //cout << "Pipe.cpp: setRight(string)" << endl;
    
}
    

bool Pipe::execute()
{
    //cout << "Pipe.cpp: execute()" << endl;
    int piper1[2];
    pipe(piper1);
    
    // Removing leading whitespace same thing
    if (right.at(0) == ' ') 
    {
        unsigned i = 0;
        while (right.at(i) == ' ') 
        {
            i++;
        }
        right = right.substr(i);
    }

    // Removing trailing whitespace same thing
    
    if (right.at(right.size()-1) == ' ') 
    {
        unsigned i = right.size() - 1;
        while (right.at(i) == ' ') 
        {
            i--;
        }
        right = right.substr(0, i + 1);
    }

 
    //Convert to a cstring and create char* vector
    char* strrer = (char*)right.c_str();
    vector<char*> fights;
    char* strrer2;
    strrer2 = strtok(strrer, " ");
    while (strrer2 != NULL) {
        if (strrer2 != '\0')
            fights.push_back(strrer2);
        
        strrer2 = strtok(NULL, " ");
    }

    // 
    // Make char* array to pass into execvp()
    
    char** starstar = new char*[fights.size()+1];

    for (unsigned i = 0; i < fights.size(); i++) 
    {
        starstar[i] = fights.at(i);
    }
    
    starstar[fights.size()] = NULL;

    int status;

    int saveOut = dup(1);
    if (saveOut == -1) 
    {
        perror("dup out");
        return false;
    }

    int saveIn = dup(0);
    if (saveIn == -1) 
    {
        perror("dup in");
        return false;
    }

    //overwrite stdout save output
    if (dup2(piper1[1], 1) == -1) 
    {
        perror("dup2 out");
        return false;
    }

    //overwrite stdin -- saveinput
    if (dup2(piper1[0], 0) == -1) 
    {
        perror("dup2 in");
        return false;
    }

    //execute lefthand side
    bool leftside = left->execute();

    //restore stdout
    if (dup2(saveOut, 1) == -1) 
    {
        perror("fix left");
        return false;
    }

    if (close(piper1[1]) == -1) 
    {
        perror("close 1");
        return false;
    }

    if (!leftside) 
    {
        return false;
    }

    
    pid_t pid = fork();

    // If error with fork
    if (pid == -1) {
        perror("fork failure");
        exit(1);
    }

    // Child
    if (pid == 0) 
    {
        // Execute righthand side
        if (execvp(starstar[0], starstar) == -1) 
        {
            perror("rightside exec");
            exit(1);
        }
        exit(1);
    }

    delete[] starstar;

    // Parent
    if (pid > 0) 
    {
        if (close(piper1[0]) == -1) 
        {
            perror("close input");
            return false;
        }

        //restore standard input
        waitpid(pid, &status, 0);
      
        if (dup2(saveIn, 0) == -1) 
        {
            perror("fix right");
            return false;
        }  
        if (status > 0) // sstatus shouldn't be returned
            return false;
        else if (WEXITSTATUS(status) == 0)
        {
            return true;
        }
        else if (WEXITSTATUS(status) == 1) 
        {    
            return false;
        }

    }
    // Shouldn't be hit
    
    return false;
}
#endif