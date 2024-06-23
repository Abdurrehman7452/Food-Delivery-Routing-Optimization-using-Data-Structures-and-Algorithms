#include <iostream>
#include <fstream>

using namespace std;

// Define the maximum number of nodes
#define MAX_NODES 50
#define MAX_RESTAURANTS 10

struct Order
{
    string name;
    int location;
    int deliveryTime;
};

struct Restaurant
{
    string name;
    int location;
    int numOrders;
    Order orders[MAX_RESTAURANTS];
};

struct Rider
{
    int id;
    int location;
};

struct Graph
{
    int V; // Number of vertices
    int adj[MAX_NODES][MAX_NODES]; // Adjacency matrix

    // Constructor
    Graph(int vertices)
    {
        V = vertices;
        // Initialize adjacency matrix to 0
        for (int i = 0; i < V; ++i)
        {
            for (int j = 0; j < V; ++j)
            {
                adj[i][j] = 0;
            }
        }
    }

    // add an edge between two vertices
    void addEdge(int u, int v, int weight)
    {
        adj[u][v] = weight;
        adj[v][u] = weight; // assuming undirected graph
    }

    // get adjacency list of a vertex
    int* getAdjList(int v)
    {
        return adj[v];
    }
};

// perform BFS and calculate shortest distance


void calculateShortestTime(Graph& graph, int source, int destination, int& totalDeliveryTime, bool print = true)
{
    bool visited[MAX_NODES] = { false };
    int distance[MAX_NODES] = { 0 };
    int parent[MAX_NODES] = { -1 };

    int queue[MAX_NODES];
    int front = -1, rear = -1;

    queue[++rear] = source;
    visited[source] = true;

    bool found = false;

    while (front != rear)
    {
        int node = queue[++front];

        if (node == destination)
        {
            found = true;
            break;
        }

        int* adjList = graph.getAdjList(node);

        for (int i = 0; i < graph.V; ++i)
        {
            if (adjList[i] != 0 && !visited[i])
            {
                distance[i] = distance[node] + 1;
                parent[i] = node;
                queue[++rear] = i;
                visited[i] = true;
            }
        }
    }

    if (print)
    {
        cout << "Edge between " << source << " and " << destination << ": ";
    }

    if (found)
    {
        if (print)
        {
            cout << "Shortest time is " << distance[destination] << endl;
            cout << "Traversal Path: ";

            int current = destination;
            while (current != source)
            {
                cout << current << "<-";
                current = parent[current];
            }
            cout << source << endl;
        }
        totalDeliveryTime += distance[destination];
    }
    else
    {
        if (print)
        {
            cout << "Destination is unreachable" << endl;
        }
    }
    if (print)
    {
        cout << endl;
    }
}



void printGrid(int N)   // print the grid
{
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            cout << (i - 1) * N + j << "\t";
        }
        cout << endl;
    }
}


// print the grid with restaurant and order locations
void printLocation(int N, Restaurant restaurants[], int numRestaurants)
{
    char** grid = new char* [N];

    for (int i = 0; i < N; ++i)
    {
        grid[i] = new char[N];
    }


    for (int i = 0; i < N; ++i)    // Initialize grid with empty spaces
    {
        for (int j = 0; j < N; ++j)
        {
            grid[i][j] = '.';
        }
    }

    // Mark restaurant locations
    for (int i = 0; i < numRestaurants; ++i)
    {
        if (restaurants[i].location < 1 || restaurants[i].location > N * N)
        {
            cout << "Error: Restaurant location out of bounds!" << endl;
            return;
        }

        int row = (restaurants[i].location - 1) / N;
        int col = (restaurants[i].location - 1) % N;
        grid[row][col] = 'R';
    }

    // Mark order locations
    for (int i = 0; i < numRestaurants; ++i)
    {
        for (int j = 0; j < restaurants[i].numOrders; ++j)
        {
            if (restaurants[i].orders[j].location < 1 || restaurants[i].orders[j].location > N * N)
            {
                cout << "Error: Order location out of bounds!" << endl;
                return;
            }

            int row = (restaurants[i].orders[j].location - 1) / N;
            int col = (restaurants[i].orders[j].location - 1) % N;
            grid[row][col] = 'O';
        }
    }

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cout << grid[i][j] << "  ";
        }
        cout << endl;
    }


    for (int i = 0; i < N; ++i)
    {
        delete[] grid[i];
    }
    delete[] grid;
}


void sortOrders(int distances[], int orderIndices[], int numOrders) 
{
    for (int i = 0; i < numOrders - 1; ++i) 
    {
        for (int j = 0; j < numOrders - i - 1; ++j) 
        {
            if (distances[j] > distances[j + 1]) 
            {
                // Swap distances
                int tempDist = distances[j];
                distances[j] = distances[j + 1];
                distances[j + 1] = tempDist;

                // Swap order indices
                int tempIndex = orderIndices[j];
                orderIndices[j] = orderIndices[j + 1];
                orderIndices[j + 1] = tempIndex;
            }
        }
    }
}


bool shouldChangeRider(int distances[], int numOrders, int threshold) {
    // Calculate the total distance for the current rider
    int total_distance = 0;
    for (int i = 0; i < numOrders; ++i) {
        if (distances[i] != INT_MAX) {
            total_distance += distances[i];
        }
    }

    // Check if the total distance exceeds the threshold
    return total_distance >= threshold;
}





int main()
{
    cout << "\033[34m";
    cout << " ____  ______  _____  ______        _______     _____                               _____  ______            " << endl;
    cout << "|     |      ||     ||      |      |       |   |      |         |  \\          /   |       |     | \\    /  " << endl;
    cout << "|     |      ||     ||      |      |       |   |      |         |   \\        /    |       |     |  \\  /    " << endl;
    cout << "|____ |      ||     ||      |      |       |   |_____ |         |    \\      /     |_____  |_____|   \\/   " << endl;
    cout << "|     |      ||     ||      |      |       |   |      |         |     \\    /      |       |\\        |         " << endl;
    cout << "|     |      ||     ||      |      |       |   |      |         |      \\  /       |       | \\       |              " << endl;
    cout << "|     |______||_____||______/      |_______/   |_____ |_______  |       \\/        |_____  |  \\      |              " << endl;
    ifstream inputFile("D:\\Uni Work\\SEM4\\DSA\\Project\\i221963_i222046_i221935\\input.txt");
    cout << "\033[0m";
    cout << "\033[32m";
    if (!inputFile.is_open())
    {
        cout << "Error: Unable to open input file!" << endl;
        return 1;
    }

    int numTestCases;
    if (!(inputFile >> numTestCases) || numTestCases <= 0)
    {
        cout << "Error: Invalid number of test cases!" << endl;
        return 1;
    }

    for (int t = 0; t < numTestCases; ++t)
    {
        int N, I, R;
        if (!(inputFile >> N >> I >> R) || N <= 0 || I <= 0 || R <= 0)
        {
            cout << "Error: Invalid input for grid size, number of riders, or number of restaurants!" << endl;
            return 1;
        }

        if (N > MAX_NODES)
        {
            cout << "Error: Grid size exceeds maximum limit!" << endl;
            return 1;
        }

        if (R > MAX_RESTAURANTS)
        {
            cout << "Error: Number of restaurants exceeds maximum limit!" << endl;
            return 1;
        }

        Restaurant restaurants[MAX_RESTAURANTS];
        Rider* riders = new Rider[I]; // Array of riders 


        // Read data for each restaurant
        cout << endl << "TEST CASE " << t + 1 << " :" << endl;
        cout << "Grid Size: " << N << ", Number of Riders: " << I << ", Number of Restaurants: " << R << endl << endl;

        // Print the grid
        cout << "Graph:" << endl;
        printGrid(N);
        cout << endl << endl;


        for (int i = 0; i < R; ++i)
        {
            inputFile >> restaurants[i].name >> restaurants[i].location >> restaurants[i].numOrders;

            if (restaurants[i].location < 1 || restaurants[i].location > N * N)
            {
                cout << "Error: Restaurant location out of bounds!" << endl;
                return 1;
            }

            cout << "Restaurant " << i + 1 << ": " << restaurants[i].name << ", Location: " << restaurants[i].location << ", Number of Orders: " << restaurants[i].numOrders << endl;

            if (restaurants[i].numOrders <= 0)
            {
                cout << "Error: Invalid number of orders for restaurant " << restaurants[i].name << "!" << endl;
                return 1;
            }

            // Read data for each order
            for (int j = 0; j < restaurants[i].numOrders; ++j)
            {
                inputFile >> restaurants[i].orders[j].name >> restaurants[i].orders[j].location >> restaurants[i].orders[j].deliveryTime;

                if (restaurants[i].orders[j].location < 1 || restaurants[i].orders[j].location > N * N || restaurants[i].orders[j].deliveryTime <= 0)
                {
                    cout << "Error: Invalid input for order " << restaurants[i].orders[j].name << "!" << endl;
                    return 1;
                }

                cout << "Order " << j + 1 << ": " << restaurants[i].orders[j].name << ", Location: " << restaurants[i].orders[j].location << ", Delivery Time Limit: " << restaurants[i].orders[j].deliveryTime << endl;
            }

            cout << endl;
        }

        cout << endl;

        Graph graph(N * N);  // Constructing the graph


        // Print the grid with restaurant and order locations
        cout << "Grid:" << endl;
        printLocation(N, restaurants, R);
        cout << endl;

        // Add edges in the grid-like graph
        for (int i = 1; i <= N; ++i)
        {
            for (int j = 1; j <= N; ++j)
            {
                int node = (i - 1) * N + j; // Calculate node number


                if (j < N)    // Connect to right neighbor (if exists)
                {
                    int rightNeighbor = node + 1;
                    graph.addEdge(node, rightNeighbor, 1);
                }


                if (i < N)    // Connect to bottom neighbor (if exists)
                {
                    int bottomNeighbor = node + N;
                    graph.addEdge(node, bottomNeighbor, 1);
                }
            }
        }
        cout << "\033[0m";

        // Assign deliveries to riders
        int currentRider = 1; // Rider ID starts from 1
        int totalDeliveryTime = 0; // Total delivery time for the test case

        for (int i = 0; i < R; ++i) {
            int restaurant_location = restaurants[i].location;

            if (currentRider > I) {
                currentRider = 1;
            }

            if (restaurants[i].numOrders > 1) {
                // Dynamic memory allocation for distances and orderIndices arrays
                int* distances = new int[restaurants[i].numOrders];
                int* orderIndices = new int[restaurants[i].numOrders];

                // Initialize distances and orderIndices arrays
                for (int j = 0; j < restaurants[i].numOrders; ++j) {
                    distances[j] = 0;
                    orderIndices[j] = j;
                }

                int orders_delivered = 0; // Counter for orders delivered by the current rider
                int current_location = restaurant_location; // Current location for the rider

                // Iterate through each order
                while (orders_delivered < restaurants[i].numOrders) {

                    // Calculate distances to each order
                    for (int k = 0; k < restaurants[i].numOrders; ++k) {
                        if (orderIndices[k] != -1) { // Check if order is not already delivered
                            int order_location = restaurants[i].orders[orderIndices[k]].location;
                            calculateShortestTime(graph, current_location, order_location, distances[k], false);
                        }
                        else {
                            distances[k] = INT_MAX; // Set a large value for already delivered orders
                        }
                    }

                    // Find the next nearest order that hasn't been delivered yet
                    int min_distance = INT_MAX;
                    int min_index = -1;
                    for (int k = 0; k < restaurants[i].numOrders; ++k) {
                        if (orderIndices[k] != -1 && distances[k] < min_distance) {
                            min_distance = distances[k];
                            min_index = k;
                        }
                    }

                    // Deliver the next nearest order
                    if (min_index != -1) {
                        int order_location = restaurants[i].orders[orderIndices[min_index]].location;

                        cout << "Rider " << currentRider << " goes from " << (orders_delivered == 0 ? "Restaurant " : "Order ") << (orders_delivered == 0 ? restaurants[i].name : restaurants[i].orders[orderIndices[min_index]].name) << " to deliver Order " << restaurants[i].orders[orderIndices[min_index]].name << endl;

                        calculateShortestTime(graph, current_location, order_location, totalDeliveryTime);

                        // Update the current location to the new order location
                        current_location = order_location;
                        orders_delivered++; // Increment orders delivered counter
                        orderIndices[min_index] = -1; // Mark this order as delivered

                        // Check if we should switch to the next rider
                        if (orders_delivered < restaurants[i].numOrders) {
                            // Recalculate distances from the new location to remaining orders
                            for (int k = 0; k < restaurants[i].numOrders; ++k) {
                                if (orderIndices[k] != -1) { // Check if order is not already delivered
                                    int order_location = restaurants[i].orders[orderIndices[k]].location;
                                    calculateShortestTime(graph, current_location, order_location, distances[k], false);
                                }
                                else {
                                    distances[k] = INT_MAX; // Set a large value for already delivered orders
                                }
                            }

                            int next_min_distance = INT_MAX;
                            for (int k = 0; k < restaurants[i].numOrders; ++k) {
                                if (orderIndices[k] != -1 && distances[k] < next_min_distance) {
                                    next_min_distance = distances[k];
                                }
                            }
                            // Switch rider if the next nearest order is far or all riders have delivered at least one order
                            if (next_min_distance > min_distance || currentRider < I && shouldChangeRider(distances, restaurants[i].numOrders, next_min_distance)) {
                                currentRider++;
                                if (currentRider > I) {
                                    currentRider = 1;
                                }
                            }
                        }
                    }
                }

                // Free dynamically allocated memory
                delete[] distances;
                delete[] orderIndices;
            }
            else {
                // Handle the case when the restaurant has only one order
                for (int j = 0; j < restaurants[i].numOrders; ++j) {
                    int order_location = restaurants[i].orders[j].location;
                    cout << "Rider " << currentRider << " goes from Restaurant " << restaurants[i].name << " to deliver Order " << restaurants[i].orders[j].name << endl;
                    calculateShortestTime(graph, restaurant_location, order_location, totalDeliveryTime);
                    currentRider++;
                }
            }
        }





        // Display total delivery time for the test case
        cout << "Total delivery time for Test Case " << t + 1 << ": " << totalDeliveryTime << endl << endl;

        // Free the dynamically allocated memory for riders
        delete[] riders;
    }
    cout << "\033[0m";
    return 0;
}