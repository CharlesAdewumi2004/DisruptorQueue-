#pragma once
#include <atomic>
#include <array>
#include <cstddef>
#include <optional>
#include "Slot.hpp"

template <typename objType, size_t sizeOfBuffer>
class DisruptorQueue {
  	private:
		static constexpr size_t BUFFER_SIZE = sizeOfBuffer;
		static constexpr size_t INDEX_MASK = sizeOfBuffer - 1;

		std::array<Slot<objType>, BUFFER_SIZE> buffer;
		std::atomic<size_t> tail; // write position (producer index)
		std::atomic<size_t> head; // read position (consumer index)

    public:
      	DisruptorQueue(): head(0), tail(0), buffer() {}
        bool push(const objType &object) {
      		size_t seqNum = tail.fetch_add(1, std::memory_order_acq_rel);
      		size_t index = seqNum & INDEX_MASK;
      		Slot<objType>& slot = buffer[index];

      		while (slot.sequence.load(std::memory_order_acquire) != seqNum) {}
      		slot.value = object;
      		slot.sequence.store(seqNum + 1, std::memory_order_release);
      		return true;
        }
		objType pop() {
      			size_t seqNum = head.load(std::memory_order_relaxed);
      			size_t index = seqNum & INDEX_MASK;
      			Slot<objType>& slot = buffer[index];

      			// Spin until the producer writes this slot
      			while (slot.sequence.load(std::memory_order_acquire) != seqNum + 1) {
      				// Optionally pause or yield here
      			}

      			objType value = slot.value;  // Copy or move out
      			slot.sequence.store(seqNum + sizeOfBuffer, std::memory_order_release);  // Mark slot empty
      			head.store(seqNum + 1, std::memory_order_relaxed);  // Advance head

      			return value;
      		}



};