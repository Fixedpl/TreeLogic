#include <iostream>

#include "Tree.h"

int main()
{
    ITree<std::string>* regularTree = new Tree<std::string>();
    regularTree->add("Pierwszy node");
    std::cin;
}


