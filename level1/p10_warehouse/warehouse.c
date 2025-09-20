//
// Created by 18611 on 2025/9/20.
//

#include "warehouse.h"

#include <conio.h>

int main() {
    printf("warehouse\n");
    printf("press any key to start...\n");
    system("pause");


    while (1)
    {
        system("cls");
        char str[100];
        int quantity;
        menu();
        switch (getch()) {
            case '1':
                show_list();
                break;
            case '2':
                printf("=== PUT IN - START ===\n");
                scanf_s("%s %d", str, (unsigned)sizeof(str), &quantity);
                put_in(str, quantity);
                break;
            case '3':
                printf("=== TAKE OUT - START ===\n");
                scanf_s("%s", str, (unsigned)sizeof(str));
                take_out(str);
                break;
            case '4':
                printf("=== EXIT ===\n");
                exit(0);
            default:
                break;

        }

        system("pause");

    }


    return 0;
}
