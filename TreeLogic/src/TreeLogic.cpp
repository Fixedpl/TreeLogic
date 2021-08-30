#include <iostream>

#include "Tree.h"
#include "IAddingStrategy.h"

int main()
{
    ITree<std::string>* regularTree = new Tree<std::string>();

    regularTree->add("root node");
    regularTree->add("child node");
    regularTree->add("child node");
    regularTree->add("child node");

    while (true) {
        std::vector<INode<std::string>*> vec;

        regularTree->search("root node", vec);

        regularTree->printToConsole();

        regularTree->remove(vec[0]);

        regularTree->printToConsole();

        regularTree->add("root node");
        regularTree->add("child node");
        regularTree->add("child node");
        regularTree->add("child node");

        regularTree->printToConsole();
        std::string empty;
        std::cin >> empty;
    }
    

    return 0;
}