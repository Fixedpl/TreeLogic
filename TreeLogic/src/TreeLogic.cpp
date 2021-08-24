#include <iostream>

#include "Tree.h"
#include "IAddingStrategy.h"

int main()
{
    ITree<std::string>* regularTree = new Tree<std::string>();

    IAddingStrategy<std::string>* adding_strat = new BalancedAddingStrategyRegularTree<std::string>(2);
    IAddingStrategy<std::string>* adding_strat2 = new RandomAddingStrategyRegularTree<std::string>(0.05f);

    regularTree->setAddingStrategy(adding_strat);

    for (int i = 0; i < 10; i++) {
        regularTree->add("");
    }

    regularTree->setAddingStrategy(adding_strat2);

    for (int i = 0; i < 10; i++) {
        regularTree->add("");
    }

    regularTree->printToConsole();
    
    delete regularTree;
    delete adding_strat;
    delete adding_strat2;


    return 0;
}


