//
//  main.c
//  hw2
//
//  Created by Andy on 2016/5/22.
//  Copyright © 2016年 Andy. All rights reserved.
//
//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int deter3(int data);//判斷數字為質數
int deter5(int data);//判斷數字除了首位非0其餘皆是0
void sort(int data_array[6][100]);//按照由小到大排列
void print_array(int max, int det_amount, int det_num[5], int data_array[6][100]);//輸出矩陣
void print_format( int data );//輸出格式排版( 10 )

int main() {
    int det_amount = 0, data_num = 0, det_num[5] = { 0 };//分類器數量 數字數量 使用的分類器
    int count[6] = { 0 };//計算列數
    int data = 0, data_array[6][100] = { 0 };//亂數 輸出矩陣
    for (int i = 0; i < 100; i++)//矩陣賦值 "-1111" ( 最小 )
        for (int n = 0; n < 6; n++)
            data_array[n][i] = -1111;// end loop
    srand(time(NULL));//取時間亂數
    printf("智慧型分類器\n\n");
    printf("分類器1 奇數\n分類器2 偶數\n分類器3 質數\n分類器4 負數\n分類器5 除最高位數外其餘位數皆為0的數字(例:10、300、1000等)\n");
    printf("\n請輸入要使用的分類器數量(0~5):");
    scanf("%d", &det_amount);
    if ( det_amount == 0 )
        return 0 ;
    printf("請輸入要使用分類器(1~5, 利用空格隔開):");
    for (int i = 0; i < det_amount; i++)//取 “使用的分類器數量” 個的 分類器“號碼”
        scanf("%d", &det_num[i]);
    printf("請輸入數字數量(1~100):");
    scanf("%d", &data_num);
    for (int i = 0; i < data_num; i++) {// 執行 “數字數量” 次
        data = (rand() % 2001) - 1000;// 取 -1000~1000 亂數
        for (int t = 0; t <= det_amount; t++) {//執行 “使用的分類器數量”+1 次
            if (t == det_amount) {// 沒配對進入分類器的放入其他
                data_array[5][count[5]] = data;//數字放入矩陣
                count[5]++;//計算放幾個數值
                break;//跳出loop
            }
            switch (det_num[t]) {// 依照分類器順序配對分類器
                case 1://數字為奇數
                    if ( data % 2 != 0 ) {
                        data_array[0][count[0]] = data;//數字放入矩陣
                        count[0]++;//計算放幾個數值
                        t = det_amount;//補足t跳出loop
                    }
                    break;
                case 2://數字為偶數
                    if ( data % 2 == 0) {
                        data_array[1][count[1]] = data;//數字放入矩陣
                        count[1]++;//計算放幾個數值
                        t = det_amount;//補足t跳出loop
                    }
                    break;
                case 3://數字為質數
                    if (deter3(data) == 1 && data > 0) {
                        data_array[2][count[2]] = data;//數字放入矩陣
                        count[2]++;//計算放幾個數值
                        t = det_amount;//補足t跳出loop
                    }
                    break;
                case 4://數字為負數
                    if (data < 0) {
                        data_array[3][count[3]] = data;//數字放入矩陣
                        count[3]++;//計算放幾個數值
                        t = det_amount;//補足t跳出loop
                    }
                    break;
                case 5://數字除了首位非0其餘皆是0
                    if (deter5(data) == 1) {
                        data_array[4][count[4]] = data;//數字放入矩陣
                        count[4]++;//計算放幾個數值
                        t = det_amount;//補足t跳出loop
                    }
                    break;
            }
        }
    }
    for (int i = 0; i < 6; i++)//計算最大列數
        if (count[0] < count[i])
            count[0] = count[i];
    sort(data_array);//按照由小到大排列
    print_array(count[0], det_amount, det_num, data_array);//輸出矩陣
    system("pause");
    return 0;
}
int deter3(int data) {//判斷數字為質數
    for (int i = 2; i < data; i++)
        if (data%i == 0)
            return 0;
    return 1;
}
int deter5(int data) {//判斷數字除了首位非0其餘皆是0
    for (int i = 10; i <= 1000; i *= 10)
        for (int n = 1; n <= 9; n++)
            if (data == i*n || data*(-1) == i*n)
                return 1;
    return 0;
}
void sort(int data_array[6][100]) {//按照由小到大排列
    int data = 0;
    for (int i = 0; i < 6; i++)// 6個分類器
        for (int j = 99; j > 0; j--)//排序100個數值
            for (int n = 0; n < j; n++)
                if (data_array[i][n] < data_array[i][n + 1]) {//順序不對的互換
                    data = data_array[i][n];
                    data_array[i][n] = data_array[i][n + 1];
                    data_array[i][n + 1] = data;
                }
}
void print_array(int max, int det_amount, int det_num[5], int data_array[6][100]) {//輸出矩陣
    for (int i = max; i >= 0; i--) {// 執行 “最大列數” 次
        for (int n = 0; n < det_amount; n++) {// 執行 “使用的分類器數量” 次
            if (data_array[det_num[n] - 1][i] == -1111)//無數值顯示空格
                printf("          ");
            else
                print_format( data_array[det_num[n] - 1][i] );//顯示數值
        }
        if (data_array[5][i] != -1111)// ”其他“ 分類器中有值時顯示
            print_format( data_array[5][i] );//顯示數值
        printf("\n");
    }
    for (int i = 0; i < det_amount; i++)// 列出下方分類器名稱
        printf("分類器 %d  ", det_num[i]);
    printf("其他\n");
}
void print_format( int data ){//輸出格式排版( 10 )
    if ( data < 0 )
        printf("%-10d", data );
    else
        printf(" %-9d", data );
}