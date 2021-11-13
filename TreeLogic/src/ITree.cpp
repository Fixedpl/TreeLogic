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

ITree::ITree()
:
m_tree_diameter(0)
{
}

void ITree::remove(INode* node)
{
	_remove(node);
	m_tree_diameter = recalculateTreeDiameter(m_root_node, 0);
}


void ITree::swapNodes(INode* first_node, INode* second_node)
{
	if (first_node == m_root_node || second_node == m_root_node) {
		std::cout << "[ERROR]Tree.h: Can't swap root node";
		return;
	}

	first_node->getFatherAbstract()->swapSonPtrs(first_node, second_node);
	second_node->getFatherAbstract()->swapSonPtrs(second_node, first_node);

	INode* buffor = first_node->getFatherAbstract();
	first_node->setFather(second_node->getFatherAbstract());
	second_node->setFather(buffor);
}

void ITree::printToConsole()
{
	if (m_root_node != nullptr) {
		m_tree_printer.print(m_root_node);
	}
	else {
		std::cout << "[WARNING]TITree.h: Trying to print empty tree\n";
	}
}

void ITree::setAddingStrategy(IAddingStrategy* adding_strategy)
{
	m_current_adding_strategy = adding_strategy;
}


INode* ITree::findNodeWithIDAbstract(const uint32_t& id, INode* starting_node, const int32_t& depth_limit)
{
	if (!starting_node) {
		return nullptr;
	}
	if (starting_node->getId() == id) {
		return starting_node;
	}
	if (depth_limit) {
		for (auto& son : starting_node->getSonsAbstract()) {
			INode* return_value = findNodeWithIDAbstract(id, son, depth_limit - 1);
			if (return_value) {
				return return_value;
			}
		}
	}
	return nullptr;
}

uint32_t ITree::getDiameter() const
{
	return m_tree_diameter;;
}

bool ITree::isEmpty() const
{
	return m_root_node == nullptr;
}


INode* ITree::_add(INode* to_add)
{
	if (m_root_node == nullptr) {
		m_root_node = to_add;
		m_tree_diameter = 1;
	}
	else {
		uint32_t path_diameter = m_current_adding_strategy->add(m_root_node, to_add);
		potentialDiameter(path_diameter);
	}
	return to_add;
}


INode* ITree::_add(INode* to_add, const std::string& path)
{
	if (!path.size()) {
		std::cout << "[ERROR] TITree.h: Empty path passed when adding node. Abandoning insertion\n";
		return nullptr;
	}

	int32_t number_from_string = 0;
	uint32_t current_index = 0;
	current_index = first_number_to_int(path, current_index, number_from_string);
	to_add->setId(number_from_string);
	if (!m_root_node) {
		if (current_index < path.size()) {
			std::cout << "[ERROR] TITree.h: Tree has no root but more than 1 nodes included in path. Abandoning insertion\n";
			return nullptr;
		}
		m_tree_diameter = 1;
		m_root_node = to_add;
		return to_add;
	}
	// Overwrite root node
	if (current_index == path.size()) {
		std::cout << "[WARNING] TITree.h: TNode with this id already exists. TNode was overwritten\n";
		delete m_root_node;
		m_root_node = to_add;
		return to_add;
	}
	if (m_root_node->getId() != number_from_string) {
		std::cout << "[ERROR] TITree.h: Couldn't find node with id " << number_from_string << ". Abandoning insertion\n";
		return nullptr;
	}

	uint32_t path_diameter = 0;
	current_index++;
	INode* current_node = m_root_node;
	INode* previous_node = current_node;
	while (current_index < path.size()) {
		number_from_string = 0;

		current_index = first_number_to_int(path, current_index, number_from_string);

		previous_node = current_node;
		if ((current_node = findNodeWithIDAbstract(number_from_string, current_node, 1)) == nullptr && current_index != path.size()) {
			std::cout << "[ERROR] TITree.h: Couldn't find node with id " << number_from_string << ". Abandoning insertion\n";
			return nullptr;
		}
		path_diameter++;
		current_index++;
	}
	to_add->setId(number_from_string);
	if (current_node) {
		std::cout << "[WARNING] TITree.h: TNode with this id already exists. TNode was overwritten\n";
		previous_node->swapSonPtrs(current_node, to_add);
		potentialDiameter(path_diameter);
		delete current_node;
	}
	else {
		if (!previous_node->addSonPtr(to_add)) {
			return nullptr;
		}
		potentialDiameter(path_diameter + 1);
	}
	return to_add;
}

void ITree::_remove(INode* node)
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

uint32_t ITree::recalculateTreeDiameter(INode* starting_node, const uint32_t& current_diameter)
{
	if (!starting_node) {
		return current_diameter;
	}
	uint32_t highest_diameter = current_diameter + 1;
	for (const auto& son : starting_node->getSonsAbstract()) {
		uint32_t diameter = recalculateTreeDiameter(son, current_diameter + 1);
		if (diameter > highest_diameter) {
			highest_diameter = diameter;
		}
	}
	return highest_diameter;
}

void ITree::potentialDiameter(const uint32_t& path_diameter)
{
	if (path_diameter > m_tree_diameter) {
		m_tree_diameter = path_diameter;
	}
}
