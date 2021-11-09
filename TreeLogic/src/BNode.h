#pragma once
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <ctime>

#include "Node.h"


class BBBNode : virtual public BINode
{
public:

	BBBNode();

	bool addSonPtr(BINode* node);

	void addSonPtrRandomly(BINode* node);

	void removeSonPtr(BINode* node);

	void swapSonPtrs(BINode* son, BINode* replacement);

	uint32_t sonsCount();

	uint32_t subtreeNodeCount();

	void setLeftSon(BINode* node);
	void setRightSon(BINode* node);

	std::vector<BINode*> getSonsAbstract();

protected:

	BINode* m_left_son = nullptr;
	BINode* m_right_son = nullptr;

};



template <typename T>
class BBNode : public INode<T>, public BBBNode
{
public:

	BBNode(const uint32_t& id, const T& data);
	BBNode(const T& data);

	std::vector<INode<T>*> getSons();

	INode<T>* getLeftSon();
	INode<T>* getRightSon();

};

template <typename T>
BBNode<T>::BBNode(const uint32_t& id, const T& data)
:
INode<T>(id, data)
{
}

template<typename T>
BBNode<T>::BBNode(const T& data)
:
INode<T>(0, data)
{
}

template <typename T>
std::vector<INode<T>*> BBNode<T>::getSons()
{
	std::vector<INode<T>*> sons;
	if (this->m_left_son != nullptr)
		sons.push_back(dynamic_cast<INode<T>*>(this->m_left_son));
	if (m_right_son != nullptr)
		sons.push_back(dynamic_cast<INode<T>*>(this->m_right_son));

	return sons;
}

template<typename T>
INode<T>* BBNode<T>::getLeftSon()
{
	return this->m_left_son;
}

template<typename T>
inline INode<T>* BBNode<T>::getRightSon()
{
	return this->m_right_son;
}


