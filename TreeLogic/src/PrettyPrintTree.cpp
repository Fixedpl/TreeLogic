#include "PrettyPrintTree.h"

#include "INode.h"

namespace tl
{
	void PrettyPrintTree::addSpaces(std::string& line, const uint32_t& spaces_amount)
	{
		for (int i = 0; i < spaces_amount; i++)
			line += " ";
	}

	void PrettyPrintTree::buildTreeSkeleton(INode* root_node,
		std::string* tree_view,
		const uint32_t& size,
		const uint32_t& level,
		const FatherDirection& father_direction)
	{
		/****************************************************************
		*	buildTreeSkeleton function builds this:
		*
		*			  0
		*		   +- + -+
		*		   1	 3
		*		+- +
		*		2
		*
		*	There are lines missing which are filled with fillMissingLines
		*
		*	Divides possibly many sons into left sons and right sons
		*	and then traverse the tree with In Order performing
		*	actions on each node. Basically rendering tree from left to right
		* ***************************************************************/
		std::vector<INode*> sons = root_node->getSonsAbstract();
		uint32_t sons_count = root_node->sonsCount();
		uint32_t left_sons = (sons_count + 1) / 2;

		for (int i = 0; i < left_sons; ++i) {
			buildTreeSkeleton(sons[i], tree_view, size, level + 2, FatherDirection::LEFT);
		}

		/****************************************************************
		*	It renders leftmost node and adds spacing on every other node
		*	Each node has 1 spacing on each side
		*
		*	root_node_id_length is needed to know how many lines
		*	to render relating to id length e.g. left needs more spacing:
		*
		*	+-----+					+--+
		*	1000  1					2  1
		*
		* ***************************************************************/
		uint32_t root_node_id_length = std::to_string(root_node->getId()).size();
		for (int i = 0; i < size; ++i) {
			if (i == level) {
				tree_view[i] += " " + std::to_string(root_node->getId()) + " ";
			}
			else {
				addSpaces(tree_view[i], root_node_id_length + 2);
			}
		}


		// If its not topmost most node adds + above and - on appropriate side
		// - here is needed for filling lines later
		if (level != 0) {
			tree_view[level - 1][tree_view[level - 1].size() - 2] = '+';
			if (father_direction == FatherDirection::LEFT) {
				tree_view[level - 1][tree_view[level - 1].size() - 1] = '-';
			}
			else if (father_direction == FatherDirection::RIGHT) {
				tree_view[level - 1][tree_view[level - 1].size() - 3] = '-';
			}
		}
		// If its not botmost node adds + below it
		if (level + 1 < size && sons_count > 0) {
			tree_view[level + 1][tree_view[level + 1].size() - 2] = '+';
		}


		for (int i = left_sons; i < sons_count; ++i) {
			buildTreeSkeleton(sons[i], tree_view, size, level + 2, FatherDirection::RIGHT);
		}
	}

	void PrettyPrintTree::fillMissingLines(std::string* tree_view, const uint32_t& size)
	{
		/*****************************************
		*	It turns patterns like this:
		*
		*	+-		+		+		-+
		*
		*	into this:
		*
		*	+-------+		+--------+
		*
		****************************************/
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

	uint32_t PrettyPrintTree::findDiameter(INode* root_node, const uint32_t& level /* = 1 */)
	{
		uint32_t highest = level;
		for (auto& son : root_node->getSonsAbstract()) {
			uint32_t son_diameter = findDiameter(son, level + 1);
			highest = std::max(son_diameter, highest);
		}
		return highest;
	}

	void PrettyPrintTree::print(INode* root_node)
	{
		/********************************************************************
		*   First it finds tree diameter to know how many levels
		*   of string to create. Since tree looks like this in console:
		*
		*		  0
		*	   +--+--+
		*      1	 3
		*   +--+
		*   2
		*
		*	it needs to reserve 2 * tree_diameter - 1 strings to be filled.
		********************************************************************/

		uint32_t tree_diameter_tests = 2 * findDiameter(root_node) - 1;
		std::string* tree_view_to_fill = new std::string[tree_diameter_tests];

		buildTreeSkeleton(root_node, tree_view_to_fill, tree_diameter_tests);
		fillMissingLines(tree_view_to_fill, tree_diameter_tests);

		for (int i = 0; i < tree_diameter_tests; ++i) {
			std::cout << tree_view_to_fill[i] << std::endl;
		}

		delete[] tree_view_to_fill;
	}
}

