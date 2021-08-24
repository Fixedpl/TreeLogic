#pragma once
#include <list>

#include "Iterator.h"



template <typename T>
class TreeIterator : public Iterator<T>
{
private:

	std::list<T> m_list;

public:

	void add(T node);

	bool hasNext();

	T next();
};

template<typename T>
void TreeIterator<T>::add(T node)
{
	m_list.push_back(node);
}

template<typename T>
bool TreeIterator<T>::hasNext()
{
	return !m_list.empty();
}

template<typename T>
T TreeIterator<T>::next()
{
	T nextNode = nullptr;
	if (hasNext()) {
		nextNode = m_list.front();
		m_list.pop_front();
	}
	return nextNode;
}