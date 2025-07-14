Overview
This document outlines the design of `DisruptorQueue<T>`, a concurrent, generic, high-performance message queue based on the Disruptor Pattern. It is implemented in modern C++ and supports multiple producers and multiple consumers (MPMC), making it suitable for low-latency, high-throughput systems. While the design supports multiple consumers, it can be safely used with just one consumer in applications like order book engines.

## Motivation
Traditional concurrent queues often rely on locks or dynamic memory allocation, which can introduce latency spikes and reduce throughput under high contention. `DisruptorQueue<T>` mitigates these issues by using a lock-free, fixed-size ring buffer and atomic operations, ensuring efficient communication across threads.

## Goals
- MPMC (Multiple Producer, Multiple Consumer) support
- Lock-free, non-blocking operations
- Fixed-size, cache-aligned ring buffer
- Generic templated type support
- Predictable, low-latency behavior
- Scalable and reusable across systems

## Design

### Ring Buffer
The queue uses a preallocated, circular buffer of type `T` with a size that must be a power of two. This allows fast wrapping of indices using bitwise operations, which improves performance and cache efficiency.

### Slot Metadata
Each slot in the buffer includes:
- A data field of type `T`
- A sequence number (or tag) to track slot status

This enables correct coordination between producers and consumers in a lock-free manner.

### Memory Model
The queue leverages memory ordering (`std::memory_order_acquire`/`release`) to guarantee visibility and correctness without locks. CAS operations and atomic fetches ensure safe concurrent access.

### Operation Semantics
- **Producers** claim a slot via atomic index increments, write their data, and publish the slot as available.
- **Consumers** read data if the slot’s sequence confirms it's ready and advance their read index.
- Proper wraparound and cache padding are used to avoid false sharing and contention.

## Use in Order Book Engine
Even though the design supports multiple consumers, the queue can be instantiated with a **single consumer** in the order book system. This preserves the determinism and simplicity required for sequential order matching, while keeping the queue reusable in other contexts with parallel consumers.

## Use Cases
- Real-time order matching systems
- Event streaming and logging
- Distributed or multi-threaded actor systems
- High-frequency trading engines
- Simulation frameworks

## References
- LMAX Disruptor Whitepaper
- Modern C++ Concurrency in Action by Anthony Williams
- Concurrency Kit, Facebook folly, and moodycamel concurrentqueue