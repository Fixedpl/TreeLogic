#pragma once
#include <cstdint>
#include <queue>

class IDHandler
{
private:

	std::priority_queue<uint32_t, std::vector<uint32_t>, std::greater<uint32_t>> m_free_ids;

	uint32_t m_max_id_count;

private:

	// [begId, endId)
	void addRange(const uint32_t& begId, const uint32_t& endId) {
		for (uint32_t i = begId; i < endId; i++) {
			m_free_ids.push(i);
		}
	}

public:

	IDHandler()
		: m_max_id_count(16)
	{
		addRange(0, 16);
	}

	void pushId(const uint32_t& id) {
		m_free_ids.push(id);
	}

	uint32_t pullId() {
		if (m_free_ids.empty()) {
			addRange(m_max_id_count, m_max_id_count * 2);
			m_max_id_count *= 2;
		}
		uint32_t id = m_free_ids.top();
		m_free_ids.pop();
		return id;
	}

};

