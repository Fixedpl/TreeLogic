#pragma once
#include <iostream>
#include <vector>

template <typename T>
class INode;

enum class FatherDirection {
	NONE, LEFT, RIGHT
};

template <typename T>
class PrettyPrintTree
{
private:

	void addSpaces(std::string& line, const uint32_t& spaces_amount);

	void buildTreeSkeleton(INode<T>* root_node,
						   std::string* tree_view,
						   const uint32_t& size,
						   const uint32_t& level = 0, 
						   const FatherDirection& father_direction = FatherDirection::NONE);

	void fillMissingLines(std::string* tree_view, const uint32_t& size);

	uint32_t findDiameter(INode<T>* root_node, const uint32_t& level = 1);

public:

	void print(INode<T>* root_node);

};

#include "INode.h"

template <typename T>
void PrettyPrintTree<T>::addSpaces(std::string& line, const uint32_t& spaces_amount)
{
	for (int i = 0; i < spaces_amount; i++)
		line += " ";
}

template <typename T>
void PrettyPrintTree<T>::buildTreeSkeleton(INode<T>* root_node, 
										   std::string* tree_view, 
										   const uint32_t& size, 
										   const uint32_t& level,
										   const FatherDirection& father_direction)
{
	std::vector<INode<T>*> sons = root_node->getSons();
	uint32_t sons_count = root_node->sonsCount();
	uint32_t left_sons  = (sons_count + 1) / 2;

	for (int i = 0; i < left_sons; ++i) {
		buildTreeSkeleton(sons[i], tree_view, size, level + 2, FatherDirection::LEFT);
	}

	uint32_t root_node_id_length = std::to_string(root_node->getId()).size();
	for (int i = 0; i < size; ++i) {
		if (i == level) {
			tree_view[i] += " " + std::to_string(root_node->getId()) + " ";
		}
		else {
			addSpaces(tree_view[i], root_node_id_length + 2);
		}
	}

	if (level != 0) {
		tree_view[level - 1][tree_view[level - 1].size() - 2] = '+';
		if (father_direction == FatherDirection::LEFT) {
			tree_view[level - 1][tree_view[level - 1].size() - 1] = '-';
		}
		else if (father_direction == FatherDirection::RIGHT) {
			tree_view[level - 1][tree_view[level - 1].size() - 3] = '-';
		}
	}
	if (level + 1 < size && sons_count > 0) {
		tree_view[level + 1][tree_view[level + 1].size() - 2] = '+';
	}

	for (int i = left_sons; i < sons_count; ++i) {
		buildTreeSkeleton(sons[i], tree_view, size, level + 2, FatherDirection::RIGHT);
	}
}

template <typename T>
void PrettyPrintTree<T>::fillMissingLines(std::string* tree_view, const uint32_t& size)
{
	for (int i = 1; i < size; i += 2) {
		bool lock = false;
		for (int j = 0; j < tree_view[i].size() - 1; ++j) {
			if (tree_view[i][j] == '+' && tree_view[i][j + 1] == '-') {
				lock = true;
				++j;
			}
			else if (lock && tree_view[i][j] != '+') {
				tree_view[i][j] = '-';
			}
			else {
				lock = false;
			}
		}

		for (int j = tree_view[i].size() - 1; j > 0; --j) {
			if (tree_view[i][j] == '+' && tree_view[i][j - 1] == '-') {
				lock = true;
				--j;
			}
			else if (lock && tree_view[i][j] != '+') {
				tree_view[i][j] = '-';
			}
			else {
				lock = false;
			}
		}
	}
}

template <typename T>
uint32_t PrettyPrintTree<T>::findDiameter(INode<T>* root_node, const uint32_t& level /* = 1 */)
{
	uint32_t highest = level;
	for (auto& son : root_node->getSons()) {
		uint32_t son_diameter = findDiameter(son, level + 1);
		highest = std::max(son_diameter, highest);
	}
	return highest;
}

template <typename T>
void PrettyPrintTree<T>::print(INode<T>* root_node)
{
	uint32_t tree_diameter = 2 * findDiameter(root_node) - 1;
	std::string* tree_view_to_fill = new std::string[tree_diameter];

	buildTreeSkeleton(root_node, tree_view_to_fill, tree_diameter);
	fillMissingLines(tree_view_to_fill, tree_diameter);

	for (int i = 0; i < tree_diameter; ++i) {
		std::cout << tree_view_to_fill[i] << std::endl;
	}

	delete[] tree_view_to_fill;
}
