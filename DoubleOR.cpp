#ifndef DOUBLE_OR
#define DOUBLE_OR
#include "../header/DoubleOR.h"
#include "../header/Connector.h"

// Constructors
DoubleOR::DoubleOR() : Connector() {this->id = 2;}

DoubleOR::DoubleOR(Base* left, Base* right) : Connector(left, right) {
    this->id = 2;
    this->left = left;
    this->right = right;
}

// // set left
// void DoubleOR::setLeft(Base* left) {
//     this->left = left;
// }

// // set right
// void DoubleOR::setRight(Base* right) {
//     this->right = right;
// }

// checks if the left side fails then the right side will execute
// if left side works then return false
// if left side fails then return true
// left must fail to execute right
bool DoubleOR::execute() {
    // if (!(left->execute())) 
    // {
    //     if (right->execute()) 
    //     {
    //         return true;
    //     }
    //     else 
    //     {
    //         return false;
    //     }
    // }
    // return true;
    
    //cout << "DoubleOR.cpp line 42" << endl;
    if (left->execute() == false )
    {
        //cout << "DoubleOR.cpp line 45" << endl;
        return right->execute();
    }
    
    //cout << "left->execute() returned true" << endl;
    
    return true;
}
#endif
