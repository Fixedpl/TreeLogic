#include <iostream>

#include "Tree.h"
#include "IAddingStrategy.h"

int main()
{
    ITree<std::string>* regularTree = new Tree<std::string>();

    IAddingStrategy<std::string>* adding_strat = new BalancedAddingStrategyRegularTree<std::string>(2);
    IAddingStrategy<std::string>* adding_strat2 = new RandomAddingStrategyRegularTree<std::string>(0.3f);
    
    ITraversalStrategy<std::string>* traversing_strat = new BFSTraversal<std::string>();

    regularTree->setAddingStrategy(adding_strat2);
    regularTree->setTraversingStrategy(traversing_strat);



    for (int i = 0; i < 10; i++) {
        regularTree->add("");
    }

    regularTree->setAddingStrategy(adding_strat);

    regularTree->add("test 1");
    regularTree->add("test 1");
    regularTree->add("test 2");

    regularTree->printToConsole();

    Iterator<INode<std::string>*>* it = regularTree->traverse();

    while (it->hasNext()) {
        std::cout << it->next()->getId() << ", ";
    }

    std::cout << std::endl;

    regularTree->printToConsole();

    delete regularTree;
    delete adding_strat;
    delete adding_strat2;
    delete traversing_strat;

    return 0;
}


