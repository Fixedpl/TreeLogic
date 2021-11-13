#include "BNode.h"


namespace tl
{
	BNode::BNode()
	{
	}


	bool BNode::addSonPtr(INode* node)
	{
		if (m_left_son && m_right_son) {
			std::cout << "[ERROR] TBNode.h: Couldn't add son because TBNode already has 2 sons\n";
			return false;
		}
		if (!m_left_son) {
			m_left_son = node;
		}
		else {
			m_right_son = node;
		}
		return true;
	}

	void BNode::addSonPtrRandomly(INode* node)
	{
		std::uniform_real_distribution<float> random_float(0.0f, 1.0f);
		if (!m_left_son && !m_right_son) {
			if (random_float(this->m_rng) <= 0.5f)
				m_left_son = node;
			else
				m_right_son = node;
		}
		else {
			addSonPtr(node);
		}
	}

	void BNode::removeSonPtr(INode* node)
	{
		if (m_left_son == node)
			m_left_son = nullptr;
		else
			m_right_son = nullptr;
	}


	void BNode::swapSonPtrs(INode* son, INode* replacement)
	{
		if (m_left_son == son)
			m_left_son = replacement;
		else
			m_right_son = replacement;
	}

	uint32_t BNode::sonsCount()
	{
		if (m_left_son && m_right_son)
			return 2;
		else if (!m_left_son && !m_right_son)
			return 0;
		return 1;
	}

	uint32_t BNode::subtreeNodeCount()
	{
		uint32_t count = 1;
		if (m_left_son)
			count += m_left_son->subtreeNodeCount();
		if (m_right_son)
			count += m_right_son->subtreeNodeCount();
		return count;
	}


	void BNode::setLeftSon(INode* node)
	{
		if (m_left_son) {
			std::cout << "[WARNING] TBNode.h: Binary node already has left. TNode was overwritten\n";
		}
		m_left_son = node;
	}

	void BNode::setRightSon(INode* node)
	{
		if (m_left_son) {
			std::cout << "[WARNING] TBNode.h: Binary node already has right son. TNode was overwritten\n";
		}
		m_right_son = node;
	}

	std::vector<INode*> BNode::getSonsAbstract()
	{
		std::vector<INode*> sons;
		if (m_left_son) {
			sons.push_back(m_left_son);
		}
		if (m_right_son) {
			sons.push_back(m_right_son);
		}
		return sons;
	}
}



