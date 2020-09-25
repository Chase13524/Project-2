#include "fbfriends.h"

FBFriends::FBFriends(){
    capacity = 5;
    data = new Friend[capacity];
    used = 0;
    current_index = 0;
}
FBFriends::~FBFriends(){
    delete [] data;
}
FBFriends::FBFriends(const FBFriends& other){
    capacity = other.capacity;
    used = other.used;
    current_index = other.current_index;
    
    Friend * tmp = new Friend[capacity];
    data = tmp;
    std::copy(other.data, other.data + used, data);
}
void FBFriends::operator = (const FBFriends& other){
    // capacity, data, used, current_index 
    if (this == &other)
        return;

    capacity = other.capacity;
    used = other.used;
    current_index = other.current_index;
    
    Friend * tmp = new Friend[other.capacity];
    delete [] data;
    data = tmp;
    std::copy(other.data, other.data + other.used, data);

}
void FBFriends::start(){
    current_index = 0;
}
void FBFriends::advance(){
    current_index++;
}
bool FBFriends::is_item(){
    return (current_index >= 0 && current_index < used);
}
Friend FBFriends::current(){
    return data[current_index];
}
void FBFriends::remove_current(){
    if (is_item()){
        for (size_t i = current_index; i <= used; i++){
            data[i] = data[i+1];
        }
        used--;
    }
}
void FBFriends::insert(const Friend& f){
    Friend * newdata = new Friend[capacity];
    if (used == capacity){
        resize();
    }
    if (used == 0){
        data[0] = f;
        used++;
        return;
    }
    for (int i = 0; i < current_index; i++){
        newdata[i] = data[i];
    }
    newdata[current_index] = f;
    for (int i = current_index; i < used; i++){
        newdata[i+1] = data[i];
    }
    delete [] data;
    data = newdata;
}
void FBFriends::attach(const Friend& f){
    Friend * newdata = new Friend[capacity];
    if (used == capacity){
        resize();
    }
    if (used == 0){
        data[0] = f;
        used++;
        return;
    }
    for (int i = 0; i <= current_index; i++){
        newdata[i] = data[i];
    }
    newdata[current_index+1] = f;
    for (int i = current_index+1; i < used; i++){
        newdata[i+1] = data[i];
    }
    delete [] data;
    data = newdata;
}
void FBFriends::show_all(std::ostream& outs)const{
    outs << '\n' << "All Friends: " << "\n";
    for (size_t a = 0; a < used; a++){
        outs << data[a];
    }
    outs << '\n';
}
void swapTwoArrPos(Friend * arr, int pos1, int pos2){
    Friend swap = arr[pos1];
    arr[pos1] = arr[pos2];
    arr[pos2] = swap;
}
void FBFriends::bday_sort(){
    int min_index;
    Friend swap;
    for (int start = 0; start < used-1; start++){
        min_index = start;
        for (int search = start+1; search <= used; search++){
            if (data[min_index].get_bday() < data[search].get_bday()){
                min_index = search;
            }
        }
        if (min_index == start){
            continue;
        } else {
            swapTwoArrPos(data, start, min_index);
        }
    }
}
Friend FBFriends::find_friend(const std::string& name)const{
    for (size_t a = 0; a < used; a++){
        if (data[a].get_name() == name){
            return data[a];
        }
    }
    return Friend();
}
bool FBFriends::is_friend(const Friend& f) const{
    for (size_t a = 0; a < used; a++){
        if (data[a] == f){
            return true;
        }
    }
    return false;
}

void FBFriends::load(std::istream& ins){
    Friend dynFriend;
    size_t index = 0;
    if (ins.peek() == '\n')
        ins.ignore();
    while (!ins.eof()){
        // if (ins.peek() == '\n')
        //     ins.ignore();
            
        if (used == capacity){
            resize();
        }
        ins >> dynFriend;
        data[index] = dynFriend;
        used++;
        index++;
    }
}
void FBFriends::save(std::ostream& outs){
    for (size_t a = 0; a < used; a++){
        outs << data[a].get_name() << '\n';
        outs << data[a].get_bday() << '\n';
    }
}
void FBFriends::resize(){
    capacity += 5;
    Friend * tmp = new Friend[capacity];
    std::copy(data, data+used, tmp);
    delete[] data;
    data = tmp;
}