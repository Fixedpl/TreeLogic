#pragma once
#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <random>


namespace tl
{
	class INode
	{
	public:

		INode();

		virtual ~INode();

		virtual bool addSonPtr(INode* node) = 0;

		virtual void addSonPtrRandomly(INode* node) = 0;

		virtual void removeSonPtr(INode* node) = 0;

		virtual void swapSonPtrs(INode* son, INode* replacement) = 0;

		virtual uint32_t sonsCount() = 0;

		virtual uint32_t subtreeNodeCount() = 0;

		virtual std::vector<INode*> getSonsAbstract() = 0;

		uint32_t getId();
		void setId(const uint32_t& id);

		bool hasFather() const;
		INode* getFatherAbstract();
		void setFather(INode* node);

	protected:

		uint32_t m_id;

		INode* m_father;

		std::random_device m_random_device;
		std::mt19937 m_rng;

	};


	template <typename T>
	class TINode : virtual public INode
	{
	public:

		TINode(const uint32_t& id, const T& data);

		virtual ~TINode();

		virtual std::vector<TINode<T>*> getSons() = 0;

		TINode<T>* getFather();

		inline T getData();

		void setData(const T& data);


	protected:

		T m_data;

	};

	template <typename T>
	TINode<T>::TINode(const uint32_t& id, const T& data)
		:
		m_data(data)
	{
		m_id = id;
	}

	template<typename T>
	TINode<T>::~TINode()
	{
	}


	template<typename T>
	TINode<T>* TINode<T>::getFather()
	{
		return dynamic_cast<TINode<T>*>(this->m_father);
	}

	template<typename T>
	T TINode<T>::getData()
	{
		return m_data;
	}

	template<typename T>
	void TINode<T>::setData(const T& data)
	{
		m_data = data;
	}
}


