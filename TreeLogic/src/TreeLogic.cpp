#include <iostream>

#include "Tree.h"

int main()
{
    ITree<std::string>* regularTree = new Tree<std::string>();
    INode<std::string>* root = regularTree->add("Pierwszy node");
    for (int i = 0; i < 20; i++) {
        regularTree->add("");
    }
    regularTree->add("Drugi node");
    regularTree->printToConsole();
    std::cin;
}


