#ifndef SEMICOLON_CPP
#define SEMICOLON_CPP
#include "../header/Semicolon.h"
#include "../header/Connector.h"
#include "../header/Base.h"

// Constructors
Semicolon::Semicolon() : Connector() {
    this->id = 3;
    left = 0;
    right = 0;
}

Semicolon::Semicolon(Base* left, Base* right) : Connector(left,right) {
    this->id = 3;
    this->left = left;
    this->right = right;
}

// // set left
// void Semicolon::setLeft(Base* left) {
//     this->left = left;
// }

// // set right
// void Semicolon::setRight(Base* right) {
//     this->right = right;
// }

//always execute regardless of previous pass or fail.
bool Semicolon::execute() {
        left->execute();
        right->execute();
    return true;
}
#endif
