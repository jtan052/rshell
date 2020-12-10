#ifndef CONNECTOR_CPP
#define CONNECTOR_CPP
#include <iostream>
#include "../header/Connector.h"
#include "../header/Base.h"

using namespace std;

// Constructors
Connector::Connector() { }

Connector::Connector(Base* left, Base* right) 
{
    this->left = left;
    this->right = right;
}

void Connector::setLeft(Base* left) {
    //cout << "left fail" << endl;
    this->left = left;
}

// set right
void Connector::setRight(Base* right) {
    //cout << "Right fail " << endl;
    this->right = right;
}

int Connector::getid() {
    return id;
}
#endif
