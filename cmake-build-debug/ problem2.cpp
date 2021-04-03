#include <iostream>
using namespace std;

void print_arr(int df[], int dfSize) {
    int j = 0;
    while (j < dfSize - 1) {
        printf("%d,", df[j]);
        j++;
    }
    printf("%d\n", df[dfSize - 1]);
}
void print_tabs(int n) {
    int j = 0;
    while (j < n ) {
        printf("\t");
        j++;
    }

}

pair<int,int>  DivConqMax(int df[], int f,int l){

    pair<int,int> max;
    if(f==l)
        max = {df[f],f};
    else if(f<l) {
        int m = (f+l) / 2;
        pair<int,int> fm= DivConqMax(df, f, m);
        pair<int,int> lm= DivConqMax(df, m+1 , l);

        if(fm>lm)
            max = fm;

        else
            max =lm;
    }
    return max;
}

int main1() {

    printf("question 2. \n");
    int arr2[] = {1, 4, 9, 3, 4, 9, 5, 6, 9, 3, 7};
    int arr2Size = sizeof(arr2) / sizeof(arr2[0]);
    printf("sample input. \n");
    print_arr(arr2, arr2Size);
    pair<int,int>  maxim =DivConqMax(arr2,0,arr2Size-1);
    printf("maximum value in array : %d  accor last at position : %d th (starting from 1)\n",maxim.first,maxim.second+1);

    return 0;
}