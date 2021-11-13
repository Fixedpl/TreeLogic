#include "INode.h"

namespace tl
{
	INode::INode()
		:
		m_id(0),
		m_father(nullptr)
	{
	}

	INode::~INode()
	{
	}


	uint32_t INode::getId()
	{
		return m_id;
	}


	void INode::setId(const uint32_t& id)
	{
		m_id = id;
	}


	bool INode::hasFather() const
	{
		return m_father != nullptr;
	}

	INode* INode::getFatherAbstract()
	{
		return m_father;
	}

	void INode::setFather(INode* node)
	{
		if (m_father) {
			std::cout << "[WARNING] Father already exists. TNode was overwritten\n";
		}
		m_father = node;
	}
}
