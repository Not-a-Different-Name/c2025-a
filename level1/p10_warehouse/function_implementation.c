//
// Created by 18611 on 2025/9/20.
//

#include "warehouse.h"

int menu(void) {
    system("cls");
    printf("\t\tWarehouse menu\n");
    printf("\t1.show the list\n");
    printf("\t2.put in\n");
    printf("\t3.take out\n");
    printf("\t4.exit\n");
    return 0;
}

int put_in(const char *model, int quantity) {
    system("cls");


    FILE *fp = NULL;
    errno_t err;

    if ((err = fopen_s(&fp, "house.txt", "a")) != 0) // 改为 "a" 追加模式
    {
        printf("error: can't open\n");
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    // 指向末尾

    fprintf(fp, "%20s\t%d\n", model, quantity);
    // 确保字符串以null结尾
    fclose(fp);
    fp = NULL;

    printf("=== PUT IN - COMPLETED ===\n");
    return 0;
}

int show_list(void) {
    system("cls");
    printf("=== SHOW LIST - START ===\n");

    FILE *fp = NULL;
    errno_t err;

    if ((err = fopen_s(&fp, "house.txt", "r")) != 0) {
        printf("error: can't open\n");
        exit(1);
    }

    fseek(fp, 0, SEEK_SET);
    // 指向头

    house_member member;
    while (fscanf_s(fp, "%s %d",
                    member.model, (unsigned) sizeof(member.model),
                    &member.quantity) == 2) {
        printf("model: %s\nquantity: %d\n\n", member.model, member.quantity);
    }

    printf("finished\n");


    // 确保字符串以null结尾
    fclose(fp);
    fp = NULL;

    printf("=== SHOW LIST - COMPLETED ===\n");
    return 0;
}


int take_out(const char *model) {
    system("cls");


    FILE *fp = NULL;
    FILE *dest = NULL;
    errno_t err;

    if ((err = fopen_s(&fp, "house.txt", "r")) != 0) {
        printf("error: can't open\n");
        exit(1);
    }

    fseek(fp, 0, SEEK_SET);

    // 创建临时文件
    char tempFilename[L_tmpnam]; //此为整形常量

    tmpnam(tempFilename);
    dest = fopen(tempFilename, "wb");
    if (dest == NULL) {
        perror("无法创建临时文件");
        fclose(fp);
        return -1;
    }

    while (!feof(fp)) {
        house_member member;
        fscanf_s(fp, "%s %d",
                 member.model, (rsize_t) sizeof(member.model),
                 &member.quantity);

        if (feof(fp))
            break;

        if (member.quantity == 0 || strcmp(member.model, model) == 0) {
            // 改为字符串比较
            continue;
        }
            fprintf(dest, "%s %d\n", member.model, member.quantity);


    }

    fclose(fp);
    fclose(dest);

    // 删除原文件并将临时文件重命名为原文件名
    remove("house.txt");
    if (rename(tempFilename, "house.txt") != 0) {
        perror("无法重命名文件");
        return -1;
    }

    printf("=== TAKE OUT - COMPLETED ===\n");
    return 0;
}
