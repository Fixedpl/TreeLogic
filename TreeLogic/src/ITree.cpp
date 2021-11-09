#include "ITree.h"

uint32_t first_number_to_int(const std::string& string, const uint32_t& starting_index, int32_t& output_value)
{
	int32_t next_space_index = starting_index;
	while (next_space_index < string.size() && string[next_space_index] != ' ') {
		next_space_index++;
	}
	int32_t iterate_number = next_space_index - 1;
	uint32_t power = 0;
	while (iterate_number >= 0 && string[iterate_number] >= '0' && string[iterate_number] <= '9') {
		output_value += static_cast<int32_t>((string[iterate_number--] - '0') * std::pow(10, power++));
	}
	if (iterate_number >= 0 && string[iterate_number] == '-') {
		output_value *= -1;
	}
	return next_space_index;
}

BITree::BITree(IAddingStrategy* default_adding_strategy)
:
m_current_adding_strategy(default_adding_strategy)
{
}

void BITree::remove(BINode* node)
{
	m_id_handler.pushId(node->getId());

	for (auto& son : node->getSonsAbstract()) {
		remove(son);
	}

	if (node->getFatherAbstract() != nullptr) {
		node->getFatherAbstract()->removeSonPtr(node);
	}
	else {
		m_root_node = nullptr;
	}

	delete node;
}


void BITree::swapNodes(BINode* first_node, BINode* second_node)
{
	if (first_node == m_root_node || second_node == m_root_node) {
		std::cout << "[ERROR]Tree.h: Can't swap root node";
		return;
	}

	first_node->getFatherAbstract()->swapSonPtrs(first_node, second_node);
	second_node->getFatherAbstract()->swapSonPtrs(second_node, first_node);

	BINode* buffor = first_node->getFatherAbstract();
	first_node->setFather(second_node->getFatherAbstract());
	second_node->setFather(buffor);
}

void BITree::printToConsole()
{
	if (m_root_node != nullptr) {
		m_tree_printer.print(m_root_node);
	}
	else {
		std::cout << "[WARNING]ITree.h: Trying to print empty tree\n";
	}
}

void BITree::setAddingStrategy(IAddingStrategy* adding_strategy)
{
	m_current_adding_strategy = adding_strategy;
}


BINode* BITree::findNodeWithIDAbstract(const uint32_t& id, BINode* starting_node, const int32_t& depth_limit)
{
	if (!starting_node) {
		return nullptr;
	}
	if (starting_node->getId() == id) {
		return starting_node;
	}
	if (depth_limit) {
		for (auto& son : starting_node->getSonsAbstract()) {
			BINode* return_value = findNodeWithIDAbstract(id, son, depth_limit - 1);
			if (return_value) {
				return return_value;
			}
		}
	}
	return nullptr;
}


BINode* BITree::_add(BINode* to_add)
{
	if (m_root_node == nullptr) {
		m_root_node = to_add;
	}
	else {
		m_current_adding_strategy->add(m_root_node, to_add);
	}
	return to_add;
}


BINode* BITree::_add(BINode* to_add, const std::string& path)
{
	if (!path.size()) {
		std::cout << "[ERROR] ITree.h: Empty path passed when adding node. Abandoning insertion\n";
		return nullptr;
	}

	int32_t number_from_string = 0;
	uint32_t current_index = 0;
	current_index = first_number_to_int(path, current_index, number_from_string);
	to_add->setId(number_from_string);
	if (!m_root_node) {
		if (current_index < path.size()) {
			std::cout << "[ERROR] ITree.h: Tree has no root but more than 1 nodes included in path. Abandoning insertion\n";
			return nullptr;
		}
		m_root_node = to_add;
		return to_add;
	}
	// Overwrite root node
	if (current_index == path.size()) {
		std::cout << "[WARNING] ITree.h: Node with this id already exists. Node was overwritten\n";
		delete m_root_node;
		m_root_node = to_add;
		return to_add;
	}
	if (m_root_node->getId() != number_from_string) {
		std::cout << "[ERROR] ITree.h: Couldn't find node with id " << number_from_string << ". Abandoning insertion\n";
		return nullptr;
	}

	current_index++;
	BINode* current_node = m_root_node;
	BINode* previous_node = current_node;
	while (current_index < path.size()) {
		number_from_string = 0;

		current_index = first_number_to_int(path, current_index, number_from_string);

		previous_node = current_node;
		if ((current_node = findNodeWithIDAbstract(number_from_string, current_node, 1)) == nullptr && current_index != path.size()) {
			std::cout << "[ERROR] ITree.h: Couldn't find node with id " << number_from_string << ". Abandoning insertion\n";
			return nullptr;
		}
		current_index++;
	}
	to_add->setId(number_from_string);
	if (current_node) {
		std::cout << "[WARNING] ITree.h: Node with this id already exists. Node was overwritten\n";
		previous_node->swapSonPtrs(current_node, to_add);
		delete current_node;
	}
	else {
		if (!previous_node->addSonPtr(to_add)) {
			return nullptr;
		}
	}
	return to_add;
}
