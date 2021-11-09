#pragma once
#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <random>



class BINode
{
public:

	BINode();

	virtual ~BINode();

	virtual bool addSonPtr(BINode* node) = 0;

	virtual void addSonPtrRandomly(BINode* node) = 0;

	virtual void removeSonPtr(BINode* node) = 0;

	virtual void swapSonPtrs(BINode* son, BINode* replacement) = 0;

	virtual uint32_t sonsCount() = 0;

	virtual uint32_t subtreeNodeCount() = 0;

	virtual std::vector<BINode*> getSonsAbstract() = 0;

	uint32_t getId();
	void setId(const uint32_t& id);

	BINode* getFatherAbstract();
	void setFather(BINode* node);

protected:

	uint32_t m_id;

	BINode* m_father;

	std::random_device m_random_device;
	std::mt19937 m_rng;

};


template <typename T>
class INode : virtual public BINode
{
public:

	INode(const uint32_t& id, const T& data);

	virtual ~INode();

	virtual std::vector<INode<T>*> getSons() = 0;

	INode<T>* getFather();

	inline T getData();

	void setData(const T& data);


protected:

	T m_data;

};

template <typename T>
INode<T>::INode(const uint32_t& id, const T& data)
:
m_data(data)
{
	m_id = id;
}

template<typename T>
INode<T>::~INode()
{
}


template<typename T>
INode<T>* INode<T>::getFather()
{
	return dynamic_cast<INode<T>*>(this->m_father);
}

template<typename T>
T INode<T>::getData()
{
	return m_data;
}

template<typename T>
void INode<T>::setData(const T& data)
{
	m_data = data;
}

