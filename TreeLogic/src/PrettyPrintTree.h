#pragma once
#include <iostream>
#include <vector>

class BINode;

enum class FatherDirection {
	NONE, LEFT, RIGHT
};

class PrettyPrintTree
{
private:

	void addSpaces(std::string& line, const uint32_t& spaces_amount);

	void buildTreeSkeleton(BINode* root_node,
						   std::string* tree_view,
						   const uint32_t& size,
						   const uint32_t& level = 0, 
						   const FatherDirection& father_direction = FatherDirection::NONE);

	void fillMissingLines(std::string* tree_view, const uint32_t& size);

	uint32_t findDiameter(BINode* root_node, const uint32_t& level = 1);

public:

	void print(BINode* root_node);

};


