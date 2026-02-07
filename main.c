/*
 ██████████    ███                    █████████            ████   ███   █████   
▒▒███▒▒▒▒███  ▒▒▒                    ███▒▒▒▒▒███          ▒▒███  ▒▒▒   ▒▒███    
 ▒███   ▒▒███ ████   █████   ██████ ▒███    ▒▒▒  ████████  ▒███  ████  ███████  
 ▒███    ▒███▒▒███  ███▒▒   ███▒▒███▒▒█████████ ▒▒███▒▒███ ▒███ ▒▒███ ▒▒▒███▒   
 ▒███    ▒███ ▒███ ▒▒█████ ▒███ ▒▒▒  ▒▒▒▒▒▒▒▒███ ▒███ ▒███ ▒███  ▒███   ▒███    
 ▒███    ███  ▒███  ▒▒▒▒███▒███  ███ ███    ▒███ ▒███ ▒███ ▒███  ▒███   ▒███ ███
 ██████████   █████ ██████ ▒▒██████ ▒▒█████████  ▒███████  █████ █████  ▒▒█████ 
▒▒▒▒▒▒▒▒▒▒   ▒▒▒▒▒ ▒▒▒▒▒▒   ▒▒▒▒▒▒   ▒▒▒▒▒▒▒▒▒   ▒███▒▒▒  ▒▒▒▒▒ ▒▒▒▒▒    ▒▒▒▒▒  
                                                 ▒███                           
                                                 █████                          
                                                ▒▒▒▒▒                           
                                made by remy
*/
#include "MergeFiles/mergeFiles.h"

void menu() {
    int action;
    printf(red"0. Exit\n"reset);
    printf(blue"1. Split a file\n"reset);
    printf(green"2. Merge a file\n"reset);
    printf(blue"Choose the number: "reset);
        
    scanf("%d", &action);
    getchar(); //used for taking \n from scanf

    switch (action) {
        case 0:
            exit(0);
            break;
        case 1:
            char filename[150];
            printf(blue"Enter a filename: "reset);
            fgets(filename, sizeof(filename), stdin);
            filename[strcspn(filename, "\n")] = '\0';
            printf(blue"---------\n"reset);
            separateFile(filename);
            printf(blue"---------\n"reset);
            break;
        case 2:
            char buffer[150];
            printf(blue"Enter filesnames (file0.txt ...): "reset);
            fgets(buffer, sizeof(buffer), stdin); 
            buffer[strcspn(buffer, "\n")] = '\0';
            printf(blue"---------\n"reset);
            mergeFiles(buffer);
            printf(blue"---------\n"reset);
            break;
        default:
            printf(red"[You entered something wrong]\n"reset);
            break;
    }
}

int main(void) {
    printf(blue"╔══════════════════════════════╗\n"reset);
    printf(blue"║         ⚙️  DiscSplit         ║\n"reset);
    printf(blue"╚══════════════════════════════╝\n"reset);

    while (1) {
        menu();
    }
    return 0;
}