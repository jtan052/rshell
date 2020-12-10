#ifndef EXEC_CPP
#define EXEC_CPP


#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <cstdlib>
#include <string>
#include <string.h>
#include <vector>

#include "../header/Exec.h"
#include "../header/Base.h"

using namespace std;

Exec::Exec(){}

Exec::Exec(string exe)
{
    this->executable = exe;
}

string Exec::getData()
{
    return this->executable;
}

bool Exec::test_execute()
{
    //cout << "helper function is now called" << endl;   
    
    //cout << "first test: " << this->executable << endl;
    //cout << "got here" << endl;
    struct stat testStruct;
    
    if (executable.size() > 4 && executable.at(4) == ' '){
        unsigned i = 4;
        while (i < executable.size() && executable.at(i) == ' ') {
            i++;
        }
        if (i < executable.size()) {
            executable = executable.substr(i);   
        }
        else {
            cout << "(False)" << endl;
            return 0;
        }
    }

    if (executable.at(executable.size() - 1) == ' ') {
        unsigned i = executable.size() - 1;    
        while (executable.at(i) == ' ') {
            i--;
        }
        executable = executable.substr(0, i + 1);
    }

    string flag = executable.substr(0, 2);
    
    if (flag.at(0) == '-') {
        // removes the space for flag
        if (executable.size() > 2 && executable.at(2) == ' ') {
            unsigned i = 2;
            while (i < executable.size() && executable.at(i) == ' ') {
                i++;
            }
            executable = executable.substr(i);
        }
        if (flag != "-f" && flag != "-d" && flag != "-e") {
            cout << "INVALID FLAG! -> (False)" << endl;
            return 0;
        }  
        if (stat(executable.c_str(), &testStruct) == -1) {
            cout << "(False)" << endl;
            return 0;
        }
        if (flag == "-f") {
            if (S_ISREG(testStruct.st_mode)) {
                cout << "(True)" << endl;
                return 1;
            }
            cout << "(False)" << endl;
            return 0;
        }
        else if (flag == "-d") {
            if (S_ISDIR(testStruct.st_mode)) {
                cout << "(True)" << endl;
                return 1;
            }
            cout << "(False)" << endl;
            return 0;
        }
        else if (flag == "-e") {
            cout << "(True)" << endl;
            return 1; 
        }
    }
    // case for no flag!
    if (stat(executable.c_str(), &testStruct) == -1) {
        cout << "(False)" << endl;
        return 0;
    }
    
    cout << "(True)" << endl;
    return 1;
}

bool Exec::execute()
{
    if (executable == " exit" || executable == " exit " || executable == " exit "){
        exit(0);
    }
    
    //cout << "checking for test" << endl;
    //cout << "third if preflow: " << this->executable << endl;
    
   if (executable.at(1) == '[' && executable.at(executable.size() - 1) == ']') {
       //cout << "first if checked: " << this->executable << endl;
       executable.replace(0, 2, "test ");
       executable.erase(executable.size() - 1); 
       //cout << "end of if: " << this->executable << endl;
       return test_execute();
    }
    if (executable == "test " || executable == "test" || executable == " test") {
        //cout << "second if checked" << endl;
        cout << "User input is only test, no parameters" << endl;
        return 0;
    }
    else if (executable.substr(0, 6) == " test ") {
        //cout << "third if checked, calling helper function" << endl;
        executable.erase(0,1);
        //call the helper function
        return test_execute(); 
    }
    
    int status;
    
    char* command = (char*)this->executable.c_str();
    vector<char*> commandArgs;
    char* letter;
    letter = strtok(command, " ");
    while (letter != NULL) {
        if (letter != '\0')
            commandArgs.push_back(letter);
        
        letter = strtok(NULL, " ");
    }

    char** args = new char*[commandArgs.size()+1];

    for (unsigned i = 0; i < commandArgs.size(); i++) {
        args[i] = commandArgs.at(i);
    }
    
    args[commandArgs.size()] = NULL;
    
    pid_t pid = fork();
    
    if(pid == -1){
        perror("pid fail");
        return false;
    }
    
    if (pid == 0){  //child process
        if(execvp(args[0], args) == -1){
            executable.erase(0,1);
            cout << this->executable << " is an invalid command!" << endl;
            //perror("exec");
            exit(1);
        }
    }
    
    if (pid > 0){   //parent process
        waitpid(-1, &status, 0);
        if(status > 0){
            return 0;
        }
        if(WEXITSTATUS(status) == 0){
            return 1;
        }
        if(WEXITSTATUS(status) == 1){
            return 0;
        }
    }
    return 0;
}



#endif 
