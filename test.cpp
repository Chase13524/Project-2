#include <string>
#include <iostream>
using namespace std;

int main(){
    int * arr = new int[5];
    int used = 0;
    for (int i = 0; i < 5; i++){
        arr[i] = i;
        used++;
    }
    int * tmp = new int[10];
    copy(arr, arr + used, tmp);
    delete [] arr;
    arr = tmp;
    for (int i = 5; i < 10; i++){
        arr[i] = i;
        used++;
    }
    for (int i = 0; i < 10; i++){
        cout << arr[i];
    }
}