#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "visual.h"
#include "logic.h"

int main(int argc, char const *argv[])
{
    // Show loading message
    printf("The program might take time to load, please be patient!\n");
    splash_screen(); // Show opening screen

    // Load cities from file
    City cities[MAX];
    int city_count = import_data(cities);

    int choice; // Store user input
    char source[30], dest[30]; // Store city names

    do
    {
        system("cls"); // Clear screen
        menu(); // Show menu options
        scanf("%d", &choice); // Read user choice

        switch (choice)
        {
        case 1:
            // Show all cities and connections
            display_graph(cities, city_count);
            pause();
            break;
        case 2:
            // Show all reachable cities from a given city
            printf("\t\t\t\tEnter city name to see reachable cities: ");
            scanf("%s", source);
            show_reachable_cities(cities, city_count, source);
            pause();
            break;
        case 3:
            // Check if a path exists between two cities
            printf("\t\t\t\tEnter first city: ");
            scanf("%s", source);
            printf("\t\t\t\tEnter second city: ");
            scanf("%s", dest);

            char *visited[VISITED_MAX]; // check visited cities
            char *best_path[VISITED_MAX]; // Store best path
            int best_count = 0; // Best path length
            int min_dist = -1; // Minimum distance

            // Find shortest path
            find_path_recursive(cities, city_count, source, dest, visited, 0, 0,
                                best_path, &best_count, &min_dist);

            // Show result
            if (min_dist != -1)
            {
                printf("\t\t\t\t" GREEN "Path exists between %s and %s\n" RESET, source, dest);
            }
            else
            {
                printf("\t\t\t\t" RED "No path exists between %s and %s\n" RESET, source, dest);
            }
            pause();
            break;
        case 4:
            // Find shortest path
            printf("\t\t\t\tEnter source city (Case Sensitive): ");
            scanf("%s", source);
            printf("\t\t\t\tEnter destination city (Case Sensitive): ");
            scanf("%s", dest);
            find_path(cities, city_count, source, dest);
            pause();
            break;
        case 5:
            // Add a city
            add_new_city(cities, &city_count);
            pause();
            break;
        case 6:
            // Add a path
            add_new_path(cities, city_count);
            pause();
            break;
        case 7:
            // Remove a city
            delete_city(cities, &city_count);
            pause();
            break;
        }
    } while (choice != 8); 

    return 0; 
}
