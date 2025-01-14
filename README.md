# 42-Philosophers

This project explores the basics of multithreading by simulating the classic dining philosophers problem. It teaches essential concepts like creating threads and using mutexes to manage shared resources.

Features:
- Simulates philosophers alternating between eating, thinking, and sleeping at a shared table.
- Each philosopher has one fork, but they need two forks to eat. Philosophers must coordinate with their neighbors to pick up their left and right forks.
- Implements thread management and mutexes to prevent resource conflicts
- Avoids data races and ensures proper memory management.
- Stops the simulation when a philosopher dies of starvation.
