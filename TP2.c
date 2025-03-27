#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "visual.h"
#include "logic.h"

int main(int argc, char const *argv[])
{
    printf("The program might take time to load, please be patient!\n");
    splash_screen();
    City cities[MAX];
    int city_count = import_data(cities);
    int choice;
    char source[30], dest[30];

    do
    {
        system("cls"); // Clear screen before menu
        menu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            display_graph(cities, city_count);
            pause();
            break;
        case 2:
            printf("\t\t\t\tEnter city name to see reachable cities: ");
            scanf("%s", source);
            show_reachable_cities(cities, city_count, source);
            pause();
            break;
        case 3:
            printf("\t\t\t\tEnter first city: ");
            scanf("%s", source);
            printf("\t\t\t\tEnter second city: ");
            scanf("%s", dest);
            char *visited[VISITED_MAX];
            char *best_path[VISITED_MAX];
            int best_count = 0;
            int min_dist = -1;

            find_path_recursive(cities, city_count, source, dest, visited, 0, 0,
                                best_path, &best_count, &min_dist);

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
            printf("\t\t\t\tEnter source city (Case Sensitive): ");
            scanf("%s", source);
            printf("\t\t\t\tEnter destination city (Case Sensitive) : ");
            scanf("%s", dest);
            find_path(cities, city_count, source, dest);
            pause();
            break;
        case 5:
            add_new_city(cities, &city_count);
            pause();
            break;
        case 6:
            add_new_path(cities, city_count);
            pause();
            break;

        case 7:
            delete_city(cities, &city_count);
            pause();
            break;
        }
    } while (choice != 8);

    return 0;
}
