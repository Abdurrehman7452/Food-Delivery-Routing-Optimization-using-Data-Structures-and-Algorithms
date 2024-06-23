# Food Delivery Routing Optimization using Data Structures and Algorithms

Food Polar Bear is a Food Delivery Routing Optimization in operating in Grid City wants to optimize its route planning for delivering orders to customers efficiently. 
The task is done in C++ in Data Structures and Algotihms project.

# Dependencies 
 Miscrosoft Visual Studio, C++ VScode extension or Dev C++ can be used to run this script.

# Introduction
This project involves developing a delivery route optimization system for a food delivery service. The goal is to manage multiple riders and restaurants, ensuring that orders are delivered in the shortest possible time. The system uses a grid-based representation of a city, where each node corresponds to a location. We utilize Breadth-First Search (BFS) to find the shortest paths within the grid.

# Program Structure
The program is written in C++ and consists of several key components:

# Struct Definitions:

Order: Represents a customer's order with attributes for name, location, and delivery time.
Restaurant: Represents a restaurant with attributes for name, location, number of orders, and an array of Order objects.
Rider: Represents a delivery rider with attributes for ID and location.
Graph: Represents the city grid as a graph using an adjacency matrix to store the weights of the edges between nodes.
# Graph Construction and Initialization:

The Graph constructor initializes the adjacency matrix to zero.
addEdge method adds bidirectional edges between nodes with specified weights.
# BFS for Shortest Path Calculation:

The calculateShortestTime function performs BFS to find the shortest path between two nodes. It updates the total delivery time and prints the traversal path.
# Grid Printing:

printGrid and printLocation functions visualize the grid, marking restaurant and order locations.
# Order Sorting and Rider Assignment:

The sortOrders function sorts orders based on their distances.
The shouldChangeRider function decides if a rider should be switched based on a distance threshold.
# Main Function:

Reads input from a file and initializes restaurants, riders, and the graph.
Manages the delivery process, assigning orders to riders and calculating the total delivery time for each test case.

# Implementation Details

# Input Handling
The program begins by reading input from a file. The input includes the number of test cases, grid size (N), number of riders (I), and number of restaurants (R). For each restaurant, it reads the location and details of each order.

# Graph Construction
The city grid is represented as a graph with nodes corresponding to grid positions. Edges are added between adjacent nodes (right and bottom neighbors) to create a grid-like structure.

# Order Assignment and Delivery
Orders are assigned to riders in a way that minimizes the total delivery time. The process involves:

- Calculating the shortest distance from the restaurant to each order location using BFS.
- Sorting orders based on these distances.
- Assigning the nearest order to the rider and updating the current location of the rider.
- Repeating the process until all orders are delivered, potentially switching riders if necessary.

# Visualization
The grid and locations of restaurants and orders are printed to the console for visualization purposes. This helps in understanding the distribution of orders and the movement of riders.

# Example Execution
An example execution involves initializing the grid, adding edges, and assigning orders to riders. The program prints the grid, restaurants, and orders, then calculates the delivery routes, printing each step of the rider's journey and the total delivery time for each test case.

# Conclusion
This program effectively models a delivery optimization problem using graph theory and BFS for shortest path calculation. The implementation ensures that orders are delivered efficiently, taking into consideration the distances and the need for potential rider switches. This approach can be extended and refined for more complex scenarios and larger grids.

