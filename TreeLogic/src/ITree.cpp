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
