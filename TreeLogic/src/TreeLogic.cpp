#include <iostream>

#include "Tree.h"
#include "BinaryTree.h"
#include "IAddingStrategy.h"

int main()
{
    ITree<std::string>* binary_tree = new BinaryTree<std::string>();

    IAddingStrategy<std::string>* balanced_strat_btree = new BalancedAddingStrategyBinaryTree<std::string>();

    binary_tree->setAddingStrategy(balanced_strat_btree);

    binary_tree->add("root node");
    binary_tree->add("child node");
    binary_tree->add("child node");
    binary_tree->add("child node");

    while (true) {
        std::vector<INode<std::string>*> vec;

        binary_tree->search("root node", vec);

        binary_tree->printToConsole();

        binary_tree->remove(vec[0]);

        binary_tree->add("root node");
        binary_tree->add("child node");
        binary_tree->add("child node");
        binary_tree->add("child node");
        binary_tree->add("child node");
        binary_tree->add("child node");
        binary_tree->add("child node");
        binary_tree->add("child node");
        binary_tree->add("child node");

        std::string empty;
        std::cin >> empty;
    }
    

    return 0;
}