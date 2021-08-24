#pragma once




template <typename T>
class IAddingStrategy
{
public:
	virtual void add(INode<T>* root, INode<T>* to_add) = 0;
};

template <typename T>
class RandomAddingStrategy : public IAddingStrategy<T>
{
private:

	float m_chance_of_adding_to_current_node;

public:
	RandomAddingStrategy(float chance_of_adding_to_current_node)
		:	m_chance_of_adding_to_current_node(chance_of_adding_to_current_node)
	{}

	bool shouldAddInCurrentNode(INode<T>* node);
};


