# DisruptorQueue

**DisruptorQueue** is a high-performance, concurrent queue library designed for modern C++ systems that require low-latency, high-throughput messaging between threads. Inspired by the Disruptor Pattern, this library provides a general-purpose, reusable, and scalable infrastructure component suitable for use in demanding environments such as financial trading systems, real-time analytics pipelines, and simulation engines.

The library is implemented as a header-only C++ template that supports multiple producers and multiple consumers (MPMC), although it can be safely used with only one consumer or one producer depending on the application's requirements.

---

## Key Features

- **Concurrent and Lock-Free:** Designed for thread-safe communication without the use of traditional locks, ensuring minimal context switching and synchronization overhead.
- **MPMC Support:** Allows multiple threads to concurrently push to and pop from the queue, with internal mechanisms for safe coordination and memory consistency.
- **Fixed-Size Ring Buffer:** Utilizes a preallocated, circular buffer to avoid heap allocations and reduce memory fragmentation.
- **Generic Templating:** Can be instantiated with any fixed-size structure, such as order messages, event records, or log entries.
- **Cache-Friendly:** Engineered to reduce cache misses and avoid false sharing through padding and memory alignment.
- **Production Ready:** Suitable for integration into systems where performance, predictability, and reliability are critical.

---

## Intended Use Cases

- Order ingestion for financial trading systems
- Real-time event dispatching in simulation frameworks
- Multi-threaded logging and telemetry processing
- Message buffering in actor-based or distributed systems
- High-frequency or parallel analytics pipelines

---

## Status

This library is in active development. While the queue supports MPMC semantics by design, it is currently being used in projects with a single consumer thread for deterministic processing (e.g., order book engines). The implementation is structured to allow seamless extension to more advanced coordination patterns in the future.

---

## Philosophy

DisruptorQueue is designed to be as close to the hardware as reasonable for application-level code. It prioritizes performance, simplicity, and correctness, and is modeled after well-known patterns used in low-latency systems. Developers can use it directly or adapt its structure to build more complex pipelines.

---

## License

MIT License
