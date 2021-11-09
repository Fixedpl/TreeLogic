#pragma once
#include <iostream>
#include <vector>

class INode;

enum class FatherDirection {
	NONE, LEFT, RIGHT
};

class PrettyPrintTree
{
private:

	void addSpaces(std::string& line, const uint32_t& spaces_amount);

	void buildTreeSkeleton(INode* root_node,
						   std::string* tree_view,
						   const uint32_t& size,
						   const uint32_t& level = 0, 
						   const FatherDirection& father_direction = FatherDirection::NONE);

	void fillMissingLines(std::string* tree_view, const uint32_t& size);

	uint32_t findDiameter(INode* root_node, const uint32_t& level = 1);

public:

	void print(INode* root_node);

};


