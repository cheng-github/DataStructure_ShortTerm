#include <stdio.h>
#include <stdlib.h>
#include "cars.h"

enum {
    CarEnter = 1,
    CarLeave = 2,
    CheckInnerPlace = 3,
    CheckOuterPlace = 4,
    CheckLeavePlace = 5,
    CheckAllPalce = 6,
    ExitProgram = -1
};

void showMenu();

int main(int argc, char *args[]){
    int chooseMenuNumber = 0;

    while(chooseMenuNumber != -1){
        showMenu();
        scanf("%d", &chooseMenuNumber);
        getchar();
        printf("\n");
        switch (chooseMenuNumber)
        {
        case CarEnter:
            HandleCarEnter();
            break;
        case CarLeave:
            HandleCarLeave();
            break;
        case CheckInnerPlace:
            CheckInnerStatus(1);
            break;
        case CheckOuterPlace:
            CheckOuterStatus(1);
            break;
        case CheckLeavePlace:
            CheckLeaveStatus();
            break;
        case CheckAllPalce:
            CheckAllStatus();
            break;
        default:
            printf("\n\t输入了错误的选择，请重新输入");
            system("pause");
            system("cls");
            break;
        }
    }
    return 0;
}

void showMenu(){
    printf("\t--------------- 停车管理 ---------------\n");
    printf("\t1. 车辆进入\n");
    printf("\t2. 车辆离开\n");
    printf("\t3. 查看停车场停放信息\n");
    printf("\t4. 查看便道停放信息\n");  
    printf("\t5. 查看已经离开的车辆\n");
    printf("\t6. 查看所有停放信息\n");
    printf("\t输入-1退出程序\n");
    printf("\t请输入选项编号进行操作(用Enter键结束输入): ");
    // printf("\n");
}