#ifndef SUMMER_TASK_CRITERIA_SET_H
#define SUMMER_TASK_CRITERIA_SET_H

#include "Set.h"

template<typename T>
using predicate = bool(T el);

template<typename T>
class Criteria_Set : public Set<T> {
public:
    predicate<T> *criteria;

    Criteria_Set(bool (*f)(T el)) : Set<T>(), criteria(f) {};

    Criteria_Set(bool (*f)(T el), int new_elements_count, T *new_elements) {
        Set<T>::elements_count = 0;
        for (int i = 0; i < new_elements_count; i++) {
            if (f(new_elements[i])) {
                Set<T>::elements[Set<T>::elements_count++] = new_elements[i];
            }
        }
    };

    void print() {
        for (int i = 0; i < Set<T>::elements_count; i++) {
            std::cout << Set<T>::elements[i] << std::endl;
        }
    }
    void add_element(T new_element) {
        if (criteria(new_element)) {
            Set<T>::elements[Set<T>::elements_count++] = new_element;
        }
    };

    T get_element_by_id(unsigned int id) { return Set<T>::elements[id]; };

    // TO DO
//    bool element_belongs_to_set(T new_el) override { return new_el == 'a'; };
};


#endif //SUMMER_TASK_CRITERIA_SET_H
