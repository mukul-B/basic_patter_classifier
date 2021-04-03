#include <iostream>
using namespace std;

void print_array(int df[], int dfSize) {
    int j = 0;
    while (j < dfSize - 1) {
        printf("%d,", df[j]);
        j++;
    }
    printf("%d\n", df[dfSize - 1]);
}

void getAllNegitivetoleft(int df[], int dfSize){
    int n=0;
    int temp;
    for (int i = 0; i < dfSize; i++) {
        if (df[i] < 0) {
            temp = df[n];
            df[n] = df[i];
            df[i] = temp;
            n++;
        }
    }
}

int main8() {

    printf("\nquestion 3. \n");
    int arr3[] = {4, -3, 9, 8, 7, -4, -2, -1, 0, 6, -5};
    int arr3Size = sizeof(arr3) / sizeof(arr3[0]);
    printf("sample input. \n");
    print_array(arr3, arr3Size);

    getAllNegitivetoleft(arr3,arr3Size);
    printf("getAllNegitivetoleft \n");
    print_array(arr3, arr3Size);

    return 0;
}