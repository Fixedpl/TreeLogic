#pragma once
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <ctime>

#include "Node.h"


class BNode : virtual public INode
{
public:

	BNode();

	bool addSonPtr(INode* node);

	void addSonPtrRandomly(INode* node);

	void removeSonPtr(INode* node);

	void swapSonPtrs(INode* son, INode* replacement);

	uint32_t sonsCount();

	uint32_t subtreeNodeCount();

	void setLeftSon(INode* node);
	void setRightSon(INode* node);

	std::vector<INode*> getSonsAbstract();

protected:

	INode* m_left_son = nullptr;
	INode* m_right_son = nullptr;

};



template <typename T>
class TBNode : public TINode<T>, public BNode
{
public:

	TBNode(const uint32_t& id, const T& data);
	TBNode(const T& data);

	std::vector<TINode<T>*> getSons();

	TINode<T>* getLeftSon();
	TINode<T>* getRightSon();

};

template <typename T>
TBNode<T>::TBNode(const uint32_t& id, const T& data)
:
TINode<T>(id, data)
{
}

template<typename T>
TBNode<T>::TBNode(const T& data)
:
TINode<T>(0, data)
{
}

template <typename T>
std::vector<TINode<T>*> TBNode<T>::getSons()
{
	std::vector<TINode<T>*> sons;
	if (this->m_left_son != nullptr)
		sons.push_back(dynamic_cast<TINode<T>*>(this->m_left_son));
	if (m_right_son != nullptr)
		sons.push_back(dynamic_cast<TINode<T>*>(this->m_right_son));

	return sons;
}

template<typename T>
TINode<T>* TBNode<T>::getLeftSon()
{
	return this->m_left_son;
}

template<typename T>
inline TINode<T>* TBNode<T>::getRightSon()
{
	return this->m_right_son;
}


