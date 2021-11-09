#include "BNode.h"



BBBNode::BBBNode()
{
}


bool BBBNode::addSonPtr(BINode* node)
{
	if (m_left_son && m_right_son) {
		std::cout << "[ERROR] BBNode.h: Couldn't add son because BBNode already has 2 sons\n";
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

void BBBNode::addSonPtrRandomly(BINode* node)
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

void BBBNode::removeSonPtr(BINode* node)
{
	if (m_left_son == node)
		m_left_son = nullptr;
	else
		m_right_son = nullptr;
}


void BBBNode::swapSonPtrs(BINode* son, BINode* replacement)
{
	if (m_left_son == son)
		m_left_son = replacement;
	else
		m_right_son = replacement;
}

uint32_t BBBNode::sonsCount()
{
	if (m_left_son && m_right_son)
		return 2;
	else if (!m_left_son && !m_right_son)
		return 0;
	return 1;
}

uint32_t BBBNode::subtreeNodeCount()
{
	uint32_t count = 1;
	if (m_left_son)
		count += m_left_son->subtreeNodeCount();
	if (m_right_son)
		count += m_right_son->subtreeNodeCount();
	return count;
}


void BBBNode::setLeftSon(BINode* node)
{
	if (m_left_son) {
		std::cout << "[WARNING] BBNode.h: Binary node already has left. Node was overwritten\n";
	}
	m_left_son = node;
}

void BBBNode::setRightSon(BINode* node)
{
	if (m_left_son) {
		std::cout << "[WARNING] BBNode.h: Binary node already has right son. Node was overwritten\n";
	}
	m_right_son = node;
}

std::vector<BINode*> BBBNode::getSonsAbstract()
{
	std::vector<BINode*> sons;
	if (m_left_son) {
		sons.push_back(m_left_son);
	}
	if (m_right_son) {
		sons.push_back(m_right_son);
	}
	return sons;
}


