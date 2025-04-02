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
#define MAX 100
#define VISITED_MAX 100 // maximum number of cities we can visit
//===============================================================================

// structure for a link from one city to another
typedef struct pLink
{
    char dest[30];         // destination city name
    int dist;              // distance to the destination
    struct pLink *newCity; // pointer to the next link in the list
} pLink;

// structure for a city
typedef struct City
{
    char name[30];   // name of the city
    pLink *Links;    // pointer to the list of linked cities
} City;

//===============================================================================
// function declarations
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

// add a new link to a city's list of links
void add_link(City *city, const char *dest, int dist)
{
    pLink *new_link = (pLink *)malloc(sizeof(pLink)); // get memory for a new link
    strcpy(new_link->dest, dest);                     // copy the destination name
    new_link->dist = dist;                            // store the distance
    new_link->newCity = city->Links;                  // point to the existing links
    city->Links = new_link;                           // set this as the new first link
}
//------------------------------------------------------//
// read city data from a file and add cities and their links
int import_data(City cities[])
{
    FILE *data = fopen("data.csv", "r");
    if (!data)
        return 0; // return zero if file could not be opened

    int city_count = 0;
    char line[256];
    char city_name[30];
    char dest[30];
    int dist;

    // go through each line in the file
    while (fgets(line, sizeof(line), data) && city_count < MAX)
    {
        int pos = 0; // current position in the line
        int i = 0;   // position in the city name

        // get the city name (until comma or newline)
        while (line[pos] && line[pos] != ',' && line[pos] != '\n' && i < 29)
        {
            city_name[i++] = line[pos++];
        }
        city_name[i] = '\0'; // end the string

        // save the city name and set links to null
        strcpy(cities[city_count].name, city_name);
        cities[city_count].Links = NULL;

        // skip the comma after the city name, if present
        if (line[pos] == ',')
            pos++;

        // read all connections for this city in the same line
        while (line[pos] && line[pos] != '\n')
        {
            // get the destination city name
            i = 0;
            while (line[pos] && line[pos] != ':' && i < 29)
            {
                dest[i++] = line[pos++];
            }
            dest[i] = '\0'; // end the string

            // skip the colon
            if (line[pos] == ':')
                pos++;

            // read the distance number as a string
            char num[10];
            i = 0;
            while (line[pos] >= '0' && line[pos] <= '9')
            {
                num[i++] = line[pos++];
            }
            num[i] = '\0'; // end the string

            // if we have a number, convert and add the link
            if (i > 0)
            {
                dist = atoi(num);
                add_link(&cities[city_count], dest, dist);
            }

            // skip the comma between connections
            if (line[pos] == ',')
                pos++;
        }

        city_count++; // move to the next city
    }

    fclose(data); // close the file
    return city_count; // return the number of cities read
}
//------------------------------------------------------//
// display the list of cities and their connections
void display_graph(City cities[], int city_count)
{
    for (int i = 0; i < city_count; i++)
    {   
        // print the city name
        printf("\t\t\t\t" YELLOW "%s:\t" RESET, cities[i].name);

        // print each link for this city
        pLink *link = cities[i].Links;
        while (link)
        {
            printf(" " CYAN " -->" RESET " %s:" GREEN " %d\t " YELLOW "| " RESET, link->dest, link->dist);
            link = link->newCity; // move to the next link
        }
        printf("\n\n");
    }
}
//------------------------------------------------------//
// print the path of visited cities with the total distance
void print_path(char *visited[], int visited_count, int total_dist)
{
    // print each city and an arrow between them
    printf("\t\t\t\t");
    for (int i = 0; i < visited_count; i++)
    {
        printf("%s", visited[i]);
        if (i < visited_count - 1)
            printf("" CYAN " -> " RESET);
    }
    printf(" : " GREEN "%d\n" RESET, total_dist);
}
//------------------------------------------------------//
// recursive function to find a path from start to end
void find_path_recursive(City cities[], int city_count, char *start, char *end,
                         char *visited[], int visited_count, int total_dist,
                         char *best_path[], int *best_count, int *min_dist)
{
    // find the current city index
    bool found = false;
    int curr_idx = -1;
    for (int i = 0; i < city_count && !found; i++)
    {
        if (strcmp(cities[i].name, start) == 0)
        {
            found = true;
            curr_idx = i;
        }
    }
    if (!found)
        return; // if city not found, exit

    // add the current city to the visited path
    visited[visited_count++] = start;

    // check if we reached the destination and if this path is better
    bool is_dest = (strcmp(start, end) == 0);
    bool is_better = (*min_dist == -1 || total_dist < *min_dist);

    if (is_dest && is_better)
    {
        *min_dist = total_dist;
        *best_count = visited_count;
        // update the best path found so far
        for (int i = 0; i < visited_count; i++)
        {
            best_path[i] = visited[i];
        }
        return;
    }

    // try each neighbor that has not been visited yet
    pLink *link = cities[curr_idx].Links;
    while (link)
    {
        bool visited_before = false;
        for (int i = 0; i < visited_count && !visited_before; i++)
        {
            if (strcmp(visited[i], link->dest) == 0)
            {
                visited_before = true;
            }
        }

        if (!visited_before)
        {
            find_path_recursive(cities, city_count, link->dest, end,
                                visited, visited_count, total_dist + link->dist,
                                best_path, best_count, min_dist);
        }
        link = link->newCity;
    }
}
//------------------------------------------------------//
// find and print the shortest path from a start city to an end city
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
        printf("\t\t\t\t" YELLOW "Shortest path:\n" RESET);
        print_path(best_path, best_count, min_dist);
    }
}
//------------------------------------------------------//
// add a new city if it does not already exist
void add_new_city(City cities[], int *city_count)
{
    char new_city[30];
    printf("\t\t\t\tEnter new city name: ");
    scanf("%s", new_city);

    // check if the city is already present
    bool city_exists = false;
    for (int i = 0; i < *city_count; i++)
    {
        if (strcmp(cities[i].name, new_city) == 0)
        {
            city_exists = true;
            break;
        }
    }

    if (city_exists)
    {
        printf("\t\t\t\t" RED "City already exists!\n" RESET);
        return;
    }

    // add the new city and set its links to null
    strcpy(cities[*city_count].name, new_city);
    cities[*city_count].Links = NULL;
    (*city_count)++;
    printf("\t\t\t\t" GREEN "City added successfully!\n" RESET);
}
//------------------------------------------------------//
// add a new connection between two cities
void add_new_path(City cities[], int city_count)
{
    char from[30], to[30];
    int distance;
    bool source_exists = false, dest_exists = false;
    int from_index = -1, to_index = -1;

    printf("\t\t\t\tEnter source city: ");
    scanf("%s", from);
    printf("\t\t\t\tEnter destination city: ");
    scanf("%s", to);
    printf("\t\t\t\tEnter distance: ");
    scanf("%d", &distance);

    // check if both cities exist and get their indexes
    for (int i = 0; i < city_count; i++)
    {
        if (strcmp(cities[i].name, from) == 0)
        {
            source_exists = true;
            from_index = i;
        }
        if (strcmp(cities[i].name, to) == 0)
        {
            dest_exists = true;
            to_index = i;
        }
    }

    if (!source_exists || !dest_exists)
    {
        printf("\t\t\t\t" YELLOW "One or both cities don't exist!\n" RESET);
        return;
    }

    // add the link from the source city to the destination city
    add_link(&cities[from_index], to, distance);
    printf("\t\t\t\t" GREEN "Path added successfully!\n" RESET);
}
//------------------------------------------------------//
// remove a city and its associated links
void delete_city(City cities[], int *city_count)
{
    char to_delete[30];
    printf("\t\t\t\tEnter city name to delete: ");
    scanf("%s", to_delete);

    // search for the city to delete
    bool city_found = false;
    int del_idx = -1;
    for (int i = 0; i < *city_count && !city_found; i++)
    {
        if (strcmp(cities[i].name, to_delete) == 0)
        {
            city_found = true;
            del_idx = i;
        }
    }

    if (!city_found)
    {
        printf("\t\t\t\t" RED "City not found!\n" RESET);
        return;
    }

    // free all links from this city
    pLink *temp;
    while (cities[del_idx].Links)
    {
        temp = cities[del_idx].Links;
        cities[del_idx].Links = temp->newCity;
        free(temp);
    }

    // remove links to this city from other cities
    for (int i = 0; i < *city_count; i++)
    {
        if (i == del_idx)
            continue;

        // if the first link matches the city to delete, remove it
        if (cities[i].Links && strcmp(cities[i].Links->dest, to_delete) == 0)
        {
            temp = cities[i].Links;
            cities[i].Links = temp->newCity;
            free(temp);
        }
    }

    // shift remaining cities in the array to fill the gap
    for (int i = del_idx; i < *city_count - 1; i++)
    {
        cities[i] = cities[i + 1];
    }

    (*city_count)--; // update the total count of cities
    printf("\t\t\t\t" GREEN "City deleted successfully!\n" RESET);
}
//----------------------------------------------------------------------------//
// show the cities that can be reached from a given city
void show_reachable_cities(City cities[], int city_count, const char *city_name)
{
    // find the city in the list
    int city_index = -1;
    for (int i = 0; i < city_count; i++)
    {
        if (strcmp(cities[i].name, city_name) == 0)
        {
            city_index = i;
            break;
        }
    }

    // if the city is not found, display a message
    if (city_index == -1)
    {
        printf("\t\t\t\t" RED "City not found!\n" RESET);
        return;
    }

    // print all linked cities
    printf("\t\t\t\t" YELLOW "Cities reachable from " CYAN "%s" RESET ":\n", city_name);
    pLink *link = cities[city_index].Links;
    if (link == NULL)
    {
        printf("\t\t\t\t" RED "No reachable cities.\n" RESET);
        return;
    }

    while (link)
    {
        printf("\t\t\t\t- " GREEN "%s " RESET "(Distance: " CYAN "%d" RESET ")\n", link->dest, link->dist);
        link = link->newCity;
    }
}

//======================================================================
#endif
