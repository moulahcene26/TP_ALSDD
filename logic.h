#ifndef LOGIC_H 
#define LOGIC_H 
//===============================================================================
#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h>
#include <string.h>
#include <windows.h> 
#include "visual.h" 
//===============================================================================
#define MAX 100 // the maximum number of cities 
#define VISITED_MAX 100 // the maximum number of cities in a path
#define NOT_FOUND -1   
//===============================================================================


typedef struct pLink // Define a structure for a city connection (a road to another city)
{
    char dest[30];         // Name of the destination city this link connects to
    int dist;              // Distance to travel to the destination city
    struct pLink *newCity; // Pointer to the next connection in the list
} pLink; // this struct allows for unlimited cities


typedef struct City // Define a structure to represent a city
{
    char name[30];   // name of this city (like "City1", "City2", etc.)
    pLink *Links;    // pointer to the first connection this city has (linked list)
} City; // 

//===============================================================================
int import_data(City cities[]); // read city data from our csv file
void display_graph(City cities[], int city_count); // show all cities and their connections
void add_link(City *city, const char *dest, int dist); // add a new connection from one city to another
void add_new_city(City cities[], int *city_count); // add a new city
void delete_city(City cities[], int *city_count); // remove a city and all its connections
void add_new_path(City cities[], int city_count);  // create a new path between existing cities
void print_path(char *visited[], int visited_count, int total_dist); // display a path with its total distance
void find_path(City cities[], int city_count, char *start, char *end); // find the shortest path between two cities
void find_path_recursive(City cities[], int city_count, char *start, char *end,
                         char *visited[], int visited_count, int total_dist,
                         char *best_path[], int *best_count, int *min_dist); // try all possible paths recursively
void show_reachable_cities(City cities[], int city_count, const char *city_name); // show all places you can go from a city                       
//===============================================================================

int import_data(City cities[]) // Function definition for importing data from CSV
{
    FILE *data = fopen("data.csv", "r"); // Open the data file for reading
    if (!data) 
    return 0; // Check if file opening failed
    
    int city_count = 0; // Initialize counter for how many cities we've read
    char line[256]; // hold each line we read from the file
    char origin[30]; // hold the source city name
    char destination[30]; // hold the destination city name
    int distance; //var to store the distance between cities
    
    
    fgets(line, sizeof(line), data); // Read the first line and ignore it (skip the header line)
    
    // go through each remaining line in the file one by one
    while (fgets(line, sizeof(line), data)) // Keep reading lines until end of file
    {
        // read lines with format: origin,destination,distance
        if (sscanf(line, "%29[^,],%29[^,],%d", origin, destination, &distance) != 3) // store 3 items from the line
        continue; // skip this line if it doesn't have all three informations
        
        int origin_index = NOT_FOUND; // propose we haven't found this origin city
        for (int i = 0; i < city_count; i++) { // Loop through all cities we already know about
            if (strcmp(cities[i].name, origin) == 0) { // Compare city names (==0 means they match exactly)
                origin_index = i; // Remember where we found this city
                break; // stop searching, we found what we needed
            }
        }
        
        if (origin_index == NOT_FOUND) { // If this origin city isn't in our list yet we need to add this new city to our list
            if (city_count >= MAX) // Check if we have space for more cities
            continue; // skip if full 
            
            strcpy(cities[city_count].name, origin); // copy the city name to our list
            cities[city_count].Links = NULL; // initialize with no connections
            origin_index = city_count; // remember where we put this new city
            city_count++; // increment city counter
        }
        
        
        add_link(&cities[origin_index], destination, distance); // Add a connection from origin city to destination city
    }
    
    fclose(data); // close file 
    return city_count; // return number of found cities
}
//------------------------------------------------------//
void display_graph(City cities[], int city_count) 
{
    for (int i = 0; i < city_count; i++) // Loop through each city we know about
    {   
        
        printf("\t\t\t\t" YELLOW "%s:\t" RESET, cities[i].name); // Print city name in yellow

        // Print each connection from this city to other cities
        pLink *link = cities[i].Links; // Start with the first connection
        while (link) // Keep going as long as there's another connection (looping through the linked list)
        {
            printf(" " CYAN " -->" RESET " %s:" GREEN " %d\t " YELLOW "| " RESET, link->dest, link->dist); // Print destination and distance
            link = link->newCity; // Move to the next connection in the list
        }
        printf("\n\n"); 
    }
}
//------------------------------------------------------//
void add_link(City *city, const char *dest, int dist) 
{
    pLink *new_link = (pLink *)malloc(sizeof(pLink)); // allocate space in memory for new connection
    strcpy(new_link->dest, dest);                     // Copy the destination city name to this connection
    new_link->dist = dist;                            // Store the distance to this destination
    new_link->newCity = city->Links;                  // Connect this new link to the existing linked list
    city->Links = new_link;                           // make new header (start of list)
}
//------------------------------------------------------//
void add_new_city(City cities[], int *city_count) 
{
    char new_city[30]; // hold the new city name
    printf("\t\t\t\tEnter new city name: "); 
    scanf("%s", new_city); // read the user input for a city name

    // Check if this city already exists in our list
    bool city_exists = false; // Start by assuming it's not repeated
    for (int i = 0; i < *city_count; i++) // Loop through all existing cities
    {
        if (strcmp(cities[i].name, new_city) == 0) // Compare this city with the new name
        {
            city_exists = true; // mark as repeated if names are the same
            break; // Stop checking once we find a match
        }
    }

    if (city_exists) // If we found this city already exists
    {
        printf("\t\t\t\t" RED "City already exists!\n" RESET); // Tell user we can't add existing cities
        return; 
    }

    // Add the new city to our list
    strcpy(cities[*city_count].name, new_city); // Copy the name to our city list
    cities[*city_count].Links = NULL; // Start with no connections
    (*city_count)++; // Increase the count of cities
    printf("\t\t\t\t" GREEN "City added successfully!\n" RESET); // Tell user it worked
}
//------------------------------------------------------//
void delete_city(City cities[], int *city_count) 
{
    char to_delete[30]; //hold the name of city to delete
    printf("\t\t\t\tEnter city name to delete: "); 
    scanf("%s", to_delete); // read the user input for a city name to delete

    // Search for the city in our list
    bool city_found = false; // Start by assuming we haven't found it
    int del_idx = NOT_FOUND; // Initialize index as not found
    for (int i = 0; i < *city_count && !city_found; i++) // Check each city until we find it
    {
        if (strcmp(cities[i].name, to_delete) == 0) // Compare city names
        {
            city_found = true; // Mark that we found the city
            del_idx = i; // Remember where it is in the list
        }
    }

    if (!city_found) // If we didn't find the city
    {
        printf("\t\t\t\t" RED "City not found!\n" RESET); // Tell user city doesn't exist
        return; 
    }

    // Free all connections leaving from this city
    pLink *temp; // temp pointer 
    while (cities[del_idx].Links) // when there are connections to delete
    {
        temp = cities[del_idx].Links; // Save the current connection
        cities[del_idx].Links = temp->newCity; // Move to the next connection
        free(temp); // Delete the saved connection
    }

    // Remove connections TO this city from all other cities
    for (int i = 0; i < *city_count; i++) // Check each city
    {
        if (i == del_idx) // Skip the city we're deleting
            continue; // Move to next city

        // Check if the first connection is to the city we're deleting
        if (cities[i].Links && strcmp(cities[i].Links->dest, to_delete) == 0) // If first link points to deleted city
        {
            temp = cities[i].Links; // Save the connection
            cities[i].Links = temp->newCity; // skip this connection
            free(temp); // Free the memory of this connection
        }
    }

    // Shift all cities after this one up in the array (to fill the gap)
    for (int i = del_idx; i < *city_count - 1; i++) // For each city after the deleted one
    {
        cities[i] = cities[i + 1]; // Move the next city into this position
    }

    (*city_count)--; // decrement count of cities by one
    printf("\t\t\t\t" GREEN "City deleted successfully!\n" RESET); // Tell user it worked
}
//----------------------------------------------------------------------------//
void print_path(char *visited[], int visited_count, int total_dist)
{
    // Print each city name with arrows between them to show the path
    printf("\t\t\t\t"); 
    for (int i = 0; i < visited_count; i++) // For each city in the path
    {
        printf("%s", visited[i]); // Print the city name
        if (i < visited_count - 1) // If this isn't the last city
            printf("" CYAN " -> " RESET); // Add an arrow to the next city
    }
    printf(" : " GREEN "%d\n" RESET, total_dist); // Show the total distance
}
//------------------------------------------------------//
void add_new_path(City cities[], int city_count) 
{
    char from[30], to[30]; // names of cities to connect
    int distance; // var for the distance between them
    bool source_exists = false, dest_exists = false; // to check if both cities exist
    int from_index = NOT_FOUND, to_index = NOT_FOUND; // to remember where the cities are in our list

    printf("\t\t\t\tEnter source city: "); // Ask for the starting city
    scanf("%s", from); 
    printf("\t\t\t\tEnter destination city: "); // Ask for the ending city
    scanf("%s", to); 
    printf("\t\t\t\tEnter distance: "); // Ask for how far apart they are
    scanf("%d", &distance); 

    // Check if both cities exist in data
    for (int i = 0; i < city_count; i++) 
    {
        if (strcmp(cities[i].name, from) == 0) // If this is the same as  our source city
        {
            source_exists = true; // Mark that source exists
            from_index = i; // Remember where we found it
        }
        if (strcmp(cities[i].name, to) == 0) // If this matches our destination city
        {
            dest_exists = true; // Mark that destination exists
            to_index = i; // Remember where we found it
        }
    }

    if (!source_exists || !dest_exists) // If any of the cities do not exist
    {
        printf("\t\t\t\t" YELLOW "One or both cities don't exist!\n" RESET); // Tell user there's a problem
        return; 
    }

  
    add_link(&cities[from_index], to, distance); // Add the new connection from source to destinatio
    printf("\t\t\t\t" GREEN "Path added successfully!\n" RESET); // Tell user it worked
}
//------------------------------------------------------//
void find_path(City cities[], int city_count, char *start, char *end) 
{
    char *visited[VISITED_MAX]; // Array to check cities in current path
    char *best_path[VISITED_MAX]; // Array to remember the best path found
    int best_count = 0; // Counter for how many cities are in the best path
    int min_dist = NOT_FOUND; // check the shortest distance found (NOT_FOUND means none yet)

    // Call recursive function to try all possible paths
    find_path_recursive(cities, city_count, start, end, visited, 0, 0,
                        best_path, &best_count, &min_dist);

    if (min_dist != NOT_FOUND) // If we found at least one path
    {
        printf("\t\t\t\t" YELLOW "Shortest path:\n" RESET); 
        print_path(best_path, best_count, min_dist); // Display the best path
    }
}
//------------------------------------------------------//
void find_path_recursive(City cities[], int city_count, char *start, char *end,
                         char *visited[], int visited_count, int total_dist,
                         char *best_path[], int *best_count, int *min_dist)
{
    // Find the current city in our list
    bool found = false; // propose we haven't found it
    int curr_idx = NOT_FOUND; // Initialize index as not found
    for (int i = 0; i < city_count && !found; i++) // Look through all cities
    {
        if (strcmp(cities[i].name, start) == 0) // Compare city names
        {
            found = true; // Mark that we found it
            curr_idx = i; // Remember where it is
        }
    }
    if (!found) // Stop this search path if we couldn't find this city
        return; 

    // Add current city to our path
    visited[visited_count++] = start; // Add city to visited list and increase count

    // Check if we've reached our destination
    bool is_dest = (strcmp(start, end) == 0); // True if current city is our destination
    bool is_better = (*min_dist == NOT_FOUND || total_dist < *min_dist); // True if this path is shorter than last best

    if (is_dest && is_better) // If we reached destination with a better path
    {
        *min_dist = total_dist; // Update shortest distance
        *best_count = visited_count; // Update count of cities in best path
        // Save this path as our new best path
        for (int i = 0; i < visited_count; i++) // For each city in the path
        {
            best_path[i] = visited[i]; // Copy to best path array
        }
        return; 
    }

    // Try each neighbor city that we haven't visited yet
    pLink *link = cities[curr_idx].Links; // Start with first connection
    while (link) // For each connection from current city
    {
        bool visited_before = false; // Assume we haven't visited the destination
        for (int i = 0; i < visited_count && !visited_before; i++) // Check our visited list
        {
            if (strcmp(visited[i], link->dest) == 0) // If this city is already in our path
            {
                visited_before = true; // Mark it as visited
            }
        }

        if (!visited_before) // If this is a new city we haven't been to yet
        {
            // Try going to this next city (recursive call)
            find_path_recursive(cities, city_count, link->dest, end,
                                visited, visited_count, total_dist + link->dist,
                                best_path, best_count, min_dist);
        }
        link = link->newCity; // Move to next connection
    }
}
//------------------------------------------------------//
void show_reachable_cities(City cities[], int city_count, const char *city_name) 
{
    // Find the city in our list
    int city_index = NOT_FOUND; // Start with not found
    for (int i = 0; i < city_count; i++) // Look through all cities
    {
        if (strcmp(cities[i].name, city_name) == 0) // Compare city names
        {
            city_index = i; // Remember where we found it
            break; 
        }
    }

    // If the city is not in our list
    if (city_index == NOT_FOUND) // If city wasn't found
    {
        printf("\t\t\t\t" RED "City not found!\n" RESET); // Tell user city doesn't exist
        return; // Exit the function
    }

    // Print all cities connected to this one
    printf("\t\t\t\t" YELLOW "Cities reachable from " CYAN "%s" RESET ":\n", city_name); 
    pLink *link = cities[city_index].Links; // Start with first connection
    if (link == NULL) // If there are no connections
    {
        printf("\t\t\t\t" RED "No reachable cities.\n" RESET); // Tell user this city has no neighbors
        return; 
    }

    while (link) // For each connection
    {
        printf("\t\t\t\t- " GREEN "%s " RESET "(Distance: " CYAN "%d" RESET ")\n", link->dest, link->dist); // Print city and distance
        link = link->newCity; // Move to next connection
    }
}

//======================================================================
#endif 