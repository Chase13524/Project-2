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
    if (used == capacity){
        resize();
    }
    // Nothing in it
    if (used == 0){
        data[0] = f;
        used++;
        return;
    }
    Friend * newdata = new Friend[capacity];
    //Copy everything from 0 to < current index
    int index = 0;
    for (size_t i = 0; i < current_index; i++){
        newdata[index] = data[i];
        index++;
    }
    //Insert new item at current index
    newdata[index] = f;
    index++;
    //Copy everything from current index over
    for (size_t i = current_index; i < used; i++){
        newdata[index] = data[i];
        index++;
    }
    delete [] data;
    data = newdata;
}
void FBFriends::attach(const Friend& f){
    if (used == capacity){
        resize();
    }
    // Possible situations
    // Nothing in it
    if (used == 0){
        data[0] = f;
        used++;
        return;
    }
    // Adding to the end of the list
    if (current_index == used-1){
        data[used + 1] = f;
        used++;
        return;
    }
    // Everything else
    Friend * newdata = new Friend[capacity];
    int index = 0;
    // Copy everything up to the current index
    for (size_t i = 0; i <= current_index; i++){
        cout << data[i].get_name() << '\n';
        newdata[index] = data[i];
        index++;
    }
    // Insert new friend
    newdata[index] = f;
    index++;
    // Copy everything from current_index + 1
    for (size_t i = current_index+1; i < used; i++){
        cout << data[i].get_name() << '\n';
        newdata[index] = data[i];
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
    size_t min_index;
    Friend swap;
    for (size_t start = 0; start < used-1; start++){
        min_index = start;
        for (size_t search = start+1; search < used; search++){
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
    while (!ins.eof()){
        if (used == capacity){
            resize();
        }
        while (ins.peek() == '\n')
            ins.ignore();
        if (ins.eof())
            break;
            
        ins >> dynFriend;
        data[used] = dynFriend;
        used++;
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