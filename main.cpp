#include "friend.h"
#include <iostream>
#include <string>
#include <fstream>
#include <istream>
using namespace std;

int* convertToDate(const std::string &str);

int main(){
    Friend a;
    cin >> a;

}

int* convertToDate(const std::string &str) {
    std::string num = "";
    int * dateArr = new int[3];
    int index = 0;
    for (const char& element : str){
        if (element == '/'){
            dateArr[index] = std::stoi(num);
            num = "";
            index++;
            continue;
        } else if (element == '\n'){
            break;
        } else {
            num += element;
        }
    }
    dateArr[2] = std::stoi(num);
    return dateArr;
}
