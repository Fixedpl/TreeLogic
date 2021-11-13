#include "Node.h"





namespace tl
{
	Node::Node()
	{
	}

	bool Node::addSonPtr(INode* node)
	{
		node->setFather(this);
		m_sons.push_back(node);
		return true;
	}

	void Node::addSonPtrRandomly(INode* node)
	{
		std::uniform_int_distribution<std::mt19937::result_type> random_int(0, m_sons.size());
		auto iterator = m_sons.begin();
		for (int i = 0; i < random_int(this->m_rng); ++i) {
			++iterator;
		}
		m_sons.insert(iterator, node);
	}

	void Node::removeSonPtr(INode* node)
	{
		m_sons.erase(std::find(m_sons.begin(), m_sons.end(), node));
	}

	void Node::swapSonPtrs(INode* son, INode* replacement)
	{
		for (int i = 0; i < m_sons.size(); ++i) {
			if (son == m_sons[i]) {
				m_sons[i] = replacement;
				break;
			}
		}
	}

	uint32_t Node::sonsCount()
	{
		return m_sons.size();
	}

	uint32_t Node::subtreeNodeCount()
	{
		uint32_t count = 0;
		for (auto& node : m_sons) {
			count += node->subtreeNodeCount() + 1;
		}
		return count;
	}

	std::vector<INode*> Node::getSonsAbstract()
	{
		return m_sons;
	}
}

