#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <random>

template <typename T>
class IAddingStrategy;



template <typename T>
class INode
{
protected:

	uint32_t m_id;

	T m_data;

	std::random_device m_random_device;
	std::mt19937 m_rng;

public:

	INode<T>* m_father = nullptr;

public:

	INode(const uint32_t& id, const T& data);

	virtual ~INode() {}

	virtual void addSonPtr(INode<T>* node) = 0;

	virtual void addSonPtrRandomly(INode<T>* node) = 0;

	virtual void removeSonPtr(INode<T>* node) = 0;

	virtual void swapSonPtrs(INode<T>* son, INode<T>* replacement) = 0;

	virtual std::vector<INode<T>*> getSons() = 0;

	virtual uint32_t sonsCount() = 0;

	virtual uint32_t subtreeNodeCount() = 0;

	inline uint32_t getId() { return m_id; }

	inline T getData() { return m_data; }

	void setData(const T& data) { m_data = data; }

};

template <typename T>
INode<T>::INode(const uint32_t& id, const T& data)
{
	m_id = id;
	m_data = data;
}
