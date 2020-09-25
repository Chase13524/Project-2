#include "friend.h"

Friend::Friend() {
    name = "";
    bday = Date();
}
std::string Friend::get_name()const {
    return name;
}
Date Friend::get_bday()const {
    return bday;
}
bool Friend::operator == (const Friend& other)const {
    return ((name == other.name) && (bday == other.bday));
}
bool Friend::operator != (const Friend& other)const {
    return ((name != other.name) || (bday != other.bday));
}
int* Friend::convertToDate(const std::string &str) {
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
    int tmp = dateArr[0];
    dateArr[0] = dateArr[1];
    dateArr[1] = tmp;
    return dateArr;
}
void Friend::input(std::istream& ins) {
    std::string dateStr;
    while (ins.peek() == '\n')
            ins.ignore();
    getline(ins, name);
    while (ins.peek() == '\n')
            ins.ignore();
    getline(ins, dateStr);
    int * date;
    date = convertToDate(dateStr);
    bday = Date(date[0], date[1], date[2]);
}
void Friend::output(std::ostream& outs)const {
    outs << name;
    outs << '\n';
    outs << bday;
    outs << '\n';
}
std::istream& operator >>(std::istream& ins,Friend& f){
    f.input(ins);
    return ins;
}
std::ostream& operator <<(std::ostream& outs,const Friend& f){
    f.output(outs);
    return outs;
}
