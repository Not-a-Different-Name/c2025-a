#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>//
// Created by 18611 on 2025/9/20.
//

#define MODEL 100

typedef struct {
    char model[MODEL];
    int quantity;
    int condition;
}house_member;

#ifndef C2025_CHALLENGE_WAREHOUSE_H
#define C2025_CHALLENGE_WAREHOUSE_H
#endif //C2025_CHALLENGE_WAREHOUSE_H

int menu(void);

int put_in(const char *model, int quantity);

int take_out(const char *model);
//
int show_list(void);



