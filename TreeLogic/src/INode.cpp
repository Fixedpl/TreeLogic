#include "INode.h"


BINode::BINode()
	:
	m_id(0),
	m_father(nullptr)
{
}

BINode::~BINode()
{
}


uint32_t BINode::getId()
{
	return m_id;
}


void BINode::setId(const uint32_t& id)
{
	m_id = id;
}


BINode* BINode::getFatherAbstract()
{
	return m_father;;
}

void BINode::setFather(BINode* node)
{
	if (m_father) {
		std::cout << "[WARNING] Father already exists. Node was overwritten\n";
	}
	m_father = node;
}