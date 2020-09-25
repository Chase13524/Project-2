#include <string>
#include "date.h"
#include "fbfriends.h"
#include <iostream>
using namespace std;

int* convertToDate(const std::string &str) {
    std::string num = "";
    int * dateArr = new int[3];
    int index = 0;
    for (size_t i = 0; i < str.length(); i++){
        if (str[i] == '/'){
            dateArr[index] = stoi(num);
            num = "";
            index++;
        } else {
            num += str[i];
        }
    }
    dateArr[2] = stoi(num);
    int tmp;
    tmp = dateArr[0];
    dateArr[0] = dateArr[1];
    dateArr[1] = tmp;
    return dateArr;
}

int main(){
    int * a;
    a = convertToDate("10/16/1999");
    cout << a[0] << '\n';
    cout << a[1] << '\n';
    cout << a[2] << '\n';
    cout << "This might be on a 2 new lines";
}