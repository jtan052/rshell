#ifndef DOUBLE_AND
#define DOUBLE_AND
#include "../header/DoubleAND.h"
#include "../header/Connector.h"
#include "../header/Base.h"

// Constructors
DoubleAND::DoubleAND() : Connector() {this->id = 1;}

DoubleAND::DoubleAND(Base* left, Base* right) : Connector(left, right) {
    this->id = 1;
    this->left = left;
    this->right = right;
}

// set left
// void DoubleAND::setLeft(Base* left) {
//     this->left = left;
// }

// // set right
// void DoubleAND::setRight(Base* right) {
//     this->right = right;
// }

// checks if the left and right side worked
// if worked then return true
// if didn't work then return false
// left must pass for right to execute
bool DoubleAND::execute() {
    // if (left->execute()) {
    //     if (right->execute()) {
    //         return true;
    //     }
    //     else {
    //         return false;
    //     }
    // }
    // return false;
    //cout << "DoubleAND.cpp line 39" << endl;
    if (left->execute() == true )
    {
        //cout << "DoubleAND.cpp line 42" << endl;
        return right->execute();
    }
    
    return true;
 
}
#endif
