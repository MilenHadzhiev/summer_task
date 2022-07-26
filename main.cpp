#include <iostream>
#include "Set.h"
#include "Criteria_Set.h"
#include <cstring>
bool is_bigger_than_5(int n) {
    return n > 5;
}

bool s2(std::string s){
    return s.length() > 2;
}

int main() {
//    Criteria_Set<std::string> string_set(&s2);
//    string_set.add_element("asd");

    Criteria_Set<int> integers_set(is_bigger_than_5);
    integers_set.add_element(67);
    integers_set.add_element(6);
    integers_set.add_element(672);
    integers_set.add_element(467);
    integers_set.print();
    //    std::string as;
//    std::cin >> as;
//    string_set.add_element(as);
    int x;
    return 0;
}
