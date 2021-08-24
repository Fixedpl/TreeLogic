#include <iostream>

#include "Tree.h"

int main()
{
    ITree<std::string>* regularTree = new Tree<std::string>();
    INode<std::string>* root = regularTree->add("Pierwszy node");
    regularTree->add("Drugi node");
    std::cin;
}


