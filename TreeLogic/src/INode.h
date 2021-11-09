#pragma once
#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <random>



template <typename T>
class INode
{
public:

	INode(const uint32_t& id, const T& data);

	virtual ~INode();

	virtual bool addSonPtr(INode<T>* node) = 0;

	virtual void addSonPtrRandomly(INode<T>* node) = 0;

	virtual void removeSonPtr(INode<T>* node) = 0;

	virtual void swapSonPtrs(INode<T>* son, INode<T>* replacement) = 0;

	virtual std::vector<INode<T>*> getSons() = 0;

	virtual uint32_t sonsCount() = 0;

	virtual uint32_t subtreeNodeCount() = 0;

	inline uint32_t getId();
	void setId(const uint32_t& id);

	inline T getData();

	void setData(const T& data);

	INode<T>* getFather();
	void setFather(INode<T>* node);

protected:

	uint32_t m_id;

	T m_data;

	std::random_device m_random_device;
	std::mt19937 m_rng;

	INode<T>* m_father = nullptr;

};

template <typename T>
INode<T>::INode(const uint32_t& id, const T& data)
{
	m_id = id;
	m_data = data;
}

template<typename T>
INode<T>::~INode()
{
}

template<typename T>
uint32_t INode<T>::getId()
{
	return m_id;
}

template<typename T>
void INode<T>::setId(const uint32_t& id)
{
	m_id = id;
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

template<typename T>
INode<T>* INode<T>::getFather()
{
	return m_father;;
}

template<typename T>
void INode<T>::setFather(INode<T>* node)
{
	if (m_father) {
		std::cout << "[WARNING] Father already exists. Node was overwritten\n";
	}
	m_father = node;
}
