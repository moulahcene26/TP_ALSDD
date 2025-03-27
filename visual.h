#ifndef VISUAL_H
#define VISUAL_H
//===============================================================================
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <windows.h>
//===============================================================================
void splash_screen();
void pause();
void menu();
//===============================================================================
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
//===================================================================================
void splash_screen(){ // skip this
    printf("\n\n\n");
    printf("                 OOOOOOOOOOOOOOOOOO               OOOOOOOOOOOOOOOOOO      "CYAN"  YYYYYYYYYYYYYYYY                  \n"RESET);
    printf("             OOOOOOOOOOOOOOOOOOOOOOOOOO       OOOOOOOOOOOOOOOOOOOOOOOOOO  "CYAN"  YYYYYYYYYYYYYYYY                  \n"RESET);
    printf("            OOOOOOOOOOOOOOOOOOOOOOOOOOOOO   OOOOOOOOOOOOOOOOOOOOOOOOOOOOO  "CYAN" YYYYYYYYYYYYYYYY                  \n"RESET);
    printf("           OOOOOOOOOOOOOO  OOOOOOOOOOOOOO   OOOOOOOOOOOOOO  OOOOOOOOOOOOO  "CYAN" YYYYYYYYYYYYYYYY                  \n"RESET);
    printf("           OOOOOOOOOOOOOO  OOOOOOOOOOOOOO   OOOOOOOOOOOOOO  OOOOOOOOOOOOO "CYAN"  YYYYYYYYYYYYYYYY                  \n"RESET);
    printf("           OOOOOOOOOOOOOO  OOOOOOOOOOOOOO   OOOOOOOOOOOOOO  OOOOOOOOOOOOO  "CYAN"  YYYY       YYYYYY                \n"RESET);
    printf("           OOOOOOOOOOOOOO  OOOOOOOOOOOOOO   OOOOOOOOOOOOOO  OOOOOOOOOOOOO   "CYAN"  YYYYYYYYYYYYYYYYYYYYY           \n"RESET);
    printf("            OOOOOOOOOOOOO  OOOOOOOOOOOOOO   OOOOOOOOOOOOOO  OOOOOOOOOOOOO                                      \n"RESET);
    printf("           OOOOOOOOOOOOOO  OOOOOOOOOOOOOO   OOOOOOOOOOOOOO  OOOOOOOOOOOOO    OOOOOOOOOOOOO                    \n");
    printf("           OOOOOOOOOOOOOO  OOOOOOOOOOOOOO   OOOOOOOOOOOOOO  OOOOOOOOOOOOO    OOOOOOOOOOOOO                    \n");
    printf("           OOOOOOOOOOOOOO  OOOOOOOOOOOOOO   OOOOOOOOOOOOOO  OOOOOOOOOOOOO    OOOOOOOOOOOOO                     \n");
    printf("           OOOOOOOOOOOOOO  OOOOOOOOOOOOOO   OOOOOOOOOOOOOO                   OOOOOOOOOOOOO                    \n");
    printf("           OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO   OOOOOOOOOOOOOOOOOOOOOOOOOOOOO    OOOOOOOOOOOOO                    \n");
    printf("           OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO   OOOOOOOOOOOOOOOOOOOOOOOOOOOOO    OOOOOOOOOOOOO                    \n");
    printf("           OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO   OOOOOOOOOOOOOOOOOOOOOOOOOOOOO    OOOOOOOOOOOOO                    \n");
    printf("           OOOOOOOOOOOOOO                                   OOOOOOOOOOOOO    OOOOOOOOOOOOO                    \n");
    printf("           OOOOOOOOOOOOOO  OOOOOOOOOOOOOO   OOOOOOOOOOOOOO  OOOOOOOOOOOOO    OOOOOOOOOOOOO                    \n");
    printf("           OOOOOOOOOOOOOO  OOOOOOOOOOOOOO   OOOOOOOOOOOOOO  OOOOOOOOOOOOO    OOOOOOOOOOOOO                    \n");
    printf("           OOOOOOOOOOOOOO  OOOOOOOOOOOOOO   OOOOOOOOOOOOOO  OOOOOOOOOOOOO    OOOOOOOOOOOOO                    \n");
    printf("           OOOOOOOOOOOOOO  OOOOOOOOOOOOOO   OOOOOOOOOOOOOO  OOOOOOOOOOOOO    OOOOOOOOOOOOO                    \n");
    printf("           OOOOOOOOOOOOOO  OOOOOOOOOOOOOO   OOOOOOOOOOOOOO  OOOOOOOOOOOOO    OOOOOOOOOOOOO                    \n");
    printf("           OOOOOOOOOOOOOO  OOOOOOOOOOOOOO   OOOOOOOOOOOOOO  OOOOOOOOOOOOO    OOOOOOOOOOOOO                    \n");
    printf("            OOOOOOOOOOOOOOOOOOOOOOOOOOOO     OOOOOOOOOOOOOOOOOOOOOOOOOOOO    OOOOOOOOOOOOO                    \n");
    printf("             OOOOOOOOOOOOOOOOOOOOOOOOOO       OOOOOOOOOOOOOOOOOOOOOOOOOO     OOOOOOOOOOOOO                    \n");
    Sleep(3000); 
    system("cls"); 

     
     printf("\t\t\t\t          "YELLOW"        Algerian Democratic Republic                  \n"RESET);
     printf("\t\t\t\t     "YELLOW"   Ministry of Higher Education and Scientific Research\n\n\n"RESET);
     printf("\t\t\t\t    "GREEN" _______________________________________________________\n"RESET);
     printf("\t\t\t\t   "GREEN" |      "CYAN"  _______     _______     _                    "GREEN"  |\n"RESET);
     printf("\t\t\t\t    "GREEN"|      "CYAN" |  _____|   |  _____|   | | "YELLOW" %ccole nationale  "GREEN"  |\n"RESET, 130);
     printf("\t\t\t\t  "GREEN"  |      "CYAN" | |_____    | |_____    | |                    "GREEN" |\n"RESET);
     printf("\t\t\t\t  "GREEN"  |      "CYAN" |  _____|   |_____  |   | | "YELLOW" sup%crieure       "GREEN"  |\n"RESET, 130);
     printf("\t\t\t\t   "GREEN" |      "CYAN" | |_____     _____| |   | |                    "GREEN" |\n"RESET);
     printf("\t\t\t\t   "GREEN" |      "CYAN" |_______|   |_______|   |_| "YELLOW" d'informatique    "GREEN" |\n"RESET);
     printf("\t\t\t\t   "GREEN" |_______________________________________________________|\n\n\n"RESET);
     Sleep(3000); 
     system("cls"); 
 
     
     printf("\t\t\t\t\t"YELLOW"CPI - First Year - University Year 2024/2025 \n\n\n"RESET);
     printf("\t\t\t\t "GREEN"___________________________________________________________________\n"RESET);
     printf("\t\t\t\t"GREEN"|                                                                   |\n"RESET);
     printf("\t\t\t\t"GREEN"| "RESET"BY          :           MOULAHCENE ABDELMOUNAIM                 "GREEN"  |\n"RESET);
     printf("\t\t\t\t"GREEN"|  "RESET"                       ALEM MOHAMED ADEL                      "GREEN"   |\n"RESET);
     printf("\t\t\t\t"GREEN"|                                                                   |\n"RESET);
     printf("\t\t\t\t"GREEN"|   "RESET"        SECTION : B           GROUPE: 05                 "GREEN"       |\n"RESET);
     printf("\t\t\t\t"GREEN"|___________________________________________________________________|\n\n"RESET);
     Sleep(3000); 
     system("cls");
        printf("\n\n\n\n\n\t\t\t\t\t\t"RED"NAMING CITIES IS CASE SENSITIVE"RESET);
     Sleep(3000); 
     system("cls");
}
//------------------------------------------------------//
void pause() {
    printf("\n\t\t\t\tEnter to Go back to MENU...");
    getchar();
    getchar();
}
//------------------------------------------------------//
void menu(){

    printf("\n\t\t\t\t"GREEN"============================================\n"RESET);
    printf("\t\t\t\t"GREEN"|           "YELLOW"       MAIN MENU     "GREEN"          |\n"RESET);
    printf("\t\t\t\t"GREEN"============================================\n"RESET);
    printf("\t\t\t\t"GREEN"|"YELLOW" 1. "RESET"Display graph               "GREEN"          |\n"RESET);
    printf("\t\t\t\t"GREEN"|"YELLOW" 2. "RESET"Show the cities that can be reached   "GREEN"|\n"RESET);
    printf("\t\t\t\t"GREEN"|"YELLOW" 3. "RESET"Check if path exists         "GREEN"         |\n"RESET);
    printf("\t\t\t\t"GREEN"|"YELLOW" 4. "RESET"Find shortest path          "GREEN"          |\n"RESET);
    printf("\t\t\t\t"GREEN"|"YELLOW" 5. "RESET"Add new city                 "GREEN"         |\n"RESET);
    printf("\t\t\t\t"GREEN"|"YELLOW" 6. "RESET"Add new path                 "GREEN"         |\n"RESET);
    printf("\t\t\t\t"GREEN"|"YELLOW" 7. "RESET"Delete City                  "GREEN"         |\n"RESET);
    printf("\t\t\t\t"GREEN"|"YELLOW" 8. "RESET"Exit                         "GREEN"         |\n"RESET);
    printf("\t\t\t\t"GREEN"============================================\n"RESET);
    printf("\t\t\t\t"YELLOW" Enter choice: "RESET);
}
//------------------------------------------------------//
#endif
