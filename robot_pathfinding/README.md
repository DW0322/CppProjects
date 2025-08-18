# Robot Path Simulator

This project is a completed simulation of a path-finding robot, developed in C++. The robot navigates through a grid-based environment, internally represented as a graph. The grid layout makes directional movement (up, down, left, right) intuitive and easy to visualize.

## Features

- Breadth-First Search (BFS) Algorithm:
The robot uses the BFS algorithm to find the shortest path from a starting node to a target node. Each node maintains a reference to its parent, allowing for accurate reconstruction of the shortest path once the goal is reached.

- Random Obstacle Generation:
Some cells in the grid are randomly blocked using the C++ Standard Library's random number generator (<random>). This simulates obstacles in the robot’s environment, adding variability and complexity to the pathfinding challenge.

## Summary

The simulation successfully demonstrates efficient and reliable pathfinding, even in the presence of random obstacles. It provides a clear visualization of both the robot’s movements and the resulting path.
