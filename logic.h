#ifndef LOGIC_H
#define LOGIC_H
//===============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "visual.h"
//===============================================================================
#define MAX 100
#define VISITED_MAX 100 // Maximum number of cities we can visit
//===============================================================================
typedef struct pLink
{                          // Link to city
    char dest[30];         // Destination name
    int dist;              // Distance from Source
    struct pLink *newCity; // recursive structure to create however much new links
} pLink;

typedef struct City
{ // Structure of City
    char name[30];
    pLink *Links; // Pointers to Cities associated with this city
} City;
//===============================================================================
int import_data(City cities[]);
void display_graph(City cities[], int city_count);
void add_link(City *city, const char *dest, int dist);
void add_new_city(City cities[], int *city_count);
void delete_city(City cities[], int *city_count);
void add_new_path(City cities[], int city_count);
void print_path(char *visited[], int visited_count, int total_dist);
void find_path(City cities[], int city_count, char *start, char *end);
void find_path_recursive(City cities[], int city_count, char *start, char *end,
                         char *visited[], int visited_count, int total_dist,
                         char *best_path[], int *best_count, int *min_dist);
//===============================================================================
void add_link(City *city, const char *dest, int dist)
{
    pLink *new_link = (pLink *)malloc(sizeof(pLink)); // Allocate memory for new link
    strcpy(new_link->dest, dest);                     // Copy destination city name
    new_link->dist = dist;                            // get distance
    new_link->newCity = city->Links;                  // Link the new link to the existing list of links for the city
    city->Links = new_link;                           // assign city to point to new link
}
//------------------------------------------------------//
int import_data(City cities[])
{
    FILE *data = fopen("data.csv", "r");
    if (!data)
        return 0;

    int city_count = 0;
    char line[256];
    char city_name[30];
    char dest[30];
    int dist;

    // Read each line from file
    while (fgets(line, sizeof(line), data) && city_count < MAX)
    {
        int pos = 0; // Position in line
        int i = 0;   // Position in name buffer

        // Get city name (read until comma or newline)
        while (line[pos] && line[pos] != ',' && line[pos] != '\n' && i < 29)
        {
            city_name[i++] = line[pos++];
        }
        city_name[i] = '\0';

        // Save city and initialize its links
        strcpy(cities[city_count].name, city_name);
        cities[city_count].Links = NULL;

        // Skip comma after city name
        if (line[pos] == ',')
            pos++;

        // Read all connections for this city
        while (line[pos] && line[pos] != '\n')
        {
            // Get destination city name
            i = 0;
            while (line[pos] && line[pos] != ':' && i < 29)
            {
                dest[i++] = line[pos++];
            }
            dest[i] = '\0';

            // Skip colon
            if (line[pos] == ':')
                pos++;

            // Read the distance number
            char num[10];
            i = 0;
            while (line[pos] >= '0' && line[pos] <= '9')
            {
                num[i++] = line[pos++];
            }
            num[i] = '\0';

            if (i > 0)
            { // If we found a number
                dist = atoi(num);
                add_link(&cities[city_count], dest, dist);
            }

            // Skip comma between connections
            if (line[pos] == ',')
                pos++;
        }

        city_count++;
    }

    fclose(data);
    return city_count;
}
//------------------------------------------------------//
void display_graph(City cities[], int city_count)
{
    for (int i = 0; i < city_count; i++)
    {                                                            // Loop through all cities
        printf("\t\t\t\t" YELLOW "%s:\t" RESET, cities[i].name); // write city name

        pLink *link = cities[i].Links; // Get first link
        while (link)
        { // go through linked list
            printf(" " CYAN " -->" RESET " %s:"GREEN" %d\t " YELLOW "| " RESET, link->dest, link->dist);
            link = link->newCity; // Move to the next link
        }
        printf("\n\n");
    }
}
//------------------------------------------------------//
void print_path(char *visited[], int visited_count, int total_dist)
{
    // Print arrow between cities
    printf("\t\t\t\t");
    for (int i = 0; i < visited_count; i++)
    {
        printf("%s", visited[i]);
        if (i < visited_count - 1)
            printf("" CYAN " -> " RESET);
    }
    printf(" : "GREEN"%d\n"RESET, total_dist);
}
//------------------------------------------------------//
void find_path_recursive(City cities[], int city_count, char *start, char *end,
                         char *visited[], int visited_count, int total_dist,
                         char *best_path[], int *best_count, int *min_dist)
{

    // Find current city in array
    int current_city_index = -1;
    for (int i = 0; i < city_count; i++)
    {
        if (strcmp(cities[i].name, start) == 0)
        {
            current_city_index = i;
            break;
        }
    }

    if (current_city_index == -1)
        return;

    // Add current city to path
    visited[visited_count++] = start;

    // If we reached destination, check if this path is shorter
    if (strcmp(start, end) == 0)
    {
        if (*min_dist == -1 || total_dist < *min_dist)
        {
            *min_dist = total_dist;
            *best_count = visited_count;
            // Save current path as best path
            for (int i = 0; i < visited_count; i++)
            {
                best_path[i] = visited[i];
            }
        }
        return;
    }

    // Try each connection
    pLink *link = cities[current_city_index].Links;
    while (link)
    {
        // Check if not already visited
        int already_visited = 0;
        for (int i = 0; i < visited_count; i++)
        {
            if (strcmp(visited[i], link->dest) == 0)
            {
                already_visited = 1;
                break;
            }
        }

        if (!already_visited)
        {
            find_path_recursive(cities, city_count, link->dest, end,
                                visited, visited_count, total_dist + link->dist,
                                best_path, best_count, min_dist);
        }
        link = link->newCity;
    }
}
//------------------------------------------------------//
void find_path(City cities[], int city_count, char *start, char *end)
{
    char *visited[VISITED_MAX];
    char *best_path[VISITED_MAX];
    int best_count = 0;
    int min_dist = -1;

    find_path_recursive(cities, city_count, start, end, visited, 0, 0,
                        best_path, &best_count, &min_dist);

    if (min_dist != -1)
    {
        printf("\t\t\t\t"YELLOW"Shortest path:\n"RESET);
        print_path(best_path, best_count, min_dist);
    }
}
//------------------------------------------------------//
void add_new_city(City cities[], int *city_count)
{
    char new_city[30];

    // Get city name
    printf("\t\t\t\tEnter new city name: ");
    scanf("%s", new_city);

    // Check if city already exists
    for (int i = 0; i < *city_count; i++)
    {
        int match = 1;
        for (int j = 0; new_city[j] != '\0'; j++)
        {
            if (new_city[j] != cities[i].name[j])
            {
                match = 0;
                break;
            }
        }
        if (match)
        {
            printf("\t\t\t\tCity already exists!\n");
            return;
        }
    }

    // Add new city
    strcpy(cities[*city_count].name, new_city);
    cities[*city_count].Links = NULL;
    (*city_count)++;
    printf("\t\t\t\t" GREEN "City added successfully!\n" RESET);
}
//------------------------------------------------------//
void add_new_path(City cities[], int city_count)
{
    char from[30], to[30];
    int distance;
    int from_index = -1, to_index = -1;

    // Get path details
    printf("\t\t\t\tEnter source city: ");
    scanf("%s", from);
    printf("\t\t\t\tEnter destination city: ");
    scanf("%s", to);
    printf("\t\t\t\tEnter distance: ");
    scanf("%d", &distance);

    // Find cities in array
    for (int i = 0; i < city_count; i++)
    {
        int match = 1;
        for (int j = 0; from[j] != '\0'; j++)
        {
            if (from[j] != cities[i].name[j])
            {
                match = 0;
                break;
            }
        }
        if (match)
            from_index = i;

        match = 1;
        for (int j = 0; to[j] != '\0'; j++)
        {
            if (to[j] != cities[i].name[j])
            {
                match = 0;
                break;
            }
        }
        if (match)
            to_index = i;
    }

    // Check if both cities exist
    if (from_index == -1 || to_index == -1)
    {
        printf("\t\t\t\t" YELLOW "One or both cities don't exist!\n" RESET);
        return;
    }

    // Add path
    add_link(&cities[from_index], to, distance);
    printf("\t\t\t\t" GREEN "Path added successfully!\n" RESET);
}
//------------------------------------------------------//
void delete_city(City cities[], int *city_count)
{
    char to_delete[30];
    printf("\t\t\t\tEnter city name to delete: ");
    scanf("%s", to_delete);

    // Find city index
    int del_idx = -1;
    for (int i = 0; i < *city_count; i++)
    {
        if (strcmp(cities[i].name, to_delete) == 0)
        {
            del_idx = i;
            break;
        }
    }

    if (del_idx == -1)
    {
        printf("\t\t\t\t " RED "City not found!\n" RESET);
        return;
    }

    // Delete paths from the city
    while (cities[del_idx].Links)
    {
        pLink *temp = cities[del_idx].Links;
        cities[del_idx].Links = temp->newCity;
        free(temp);
    }

    // Delete paths to the city from all other cities
    for (int i = 0; i < *city_count; i++)
    {
        if (i != del_idx)
        {
            pLink *prev = NULL;
            pLink *curr = cities[i].Links;

            while (curr)
            {
                if (strcmp(curr->dest, to_delete) == 0)
                {
                    if (prev)
                    {
                        prev->newCity = curr->newCity;
                    }
                    else
                    {
                        cities[i].Links = curr->newCity;
                    }
                    free(curr);
                    break;
                }
                prev = curr;
                curr = curr->newCity;
            }
        }
    }

    // Shift remaining cities left
    for (int i = del_idx; i < *city_count - 1; i++)
    {
        cities[i] = cities[i + 1];
    }

    (*city_count)--;
    printf("\t\t\t\t " RED "City deleted!\n" RESET);
}
//----------------------------------------------------------------------------//
void show_reachable_cities(City cities[], int city_count, const char *city_name) {
    // Find the city in the array
    int city_index = -1;
    for (int i = 0; i < city_count; i++) {
        if (strcmp(cities[i].name, city_name) == 0) {
            city_index = i;
            break;
        }
    }

    // If the city is not found, print an error message
    if (city_index == -1) {
        printf("\t\t\t\t" RED "City not found!\n" RESET);
        return;
    }

    // Print reachable cities
    printf("\t\t\t\t"YELLOW"Cities reachable from "CYAN"%s"RESET":\n", city_name);
    pLink *link = cities[city_index].Links;
    if (link == NULL) {
        printf("\t\t\t\t"RED"No reachable cities.\n"RESET);
        return;
    }

    while (link) {
        printf("\t\t\t\t- "GREEN"%s "RESET"(Distance: "CYAN"%d"RESET")\n", link->dest, link->dist);
        link = link->newCity;
    }
}

//======================================================================
#endif