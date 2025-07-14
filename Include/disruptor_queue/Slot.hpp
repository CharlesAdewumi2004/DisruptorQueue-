
#include <cstddef>
#include <atomic>

template <typename objType>
struct Slot {
	std::atomic<size_t> sequence;
	objType value;
};