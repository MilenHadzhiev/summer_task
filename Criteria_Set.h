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

    Criteria_Set(bool (*f)(T el), int new_elements_count, T *new_elements) : Set<T>(new_elements, new_elements_count) {
        criteria = f;
    };

    Criteria_Set(Criteria_Set<T> &other) : Set<T>(other) {
        criteria = other.criteria;
        std::cout << "criteria copy\n";
    }

    void add_element(T new_element) override {
        if(criteria(new_element)) {
            Set<T>::elements[Set<T>::elements_count++] = new_element;
        }
    }

    bool element_belongs_to_set(T new_el) override {
        for (int i = 0; i < Set<T>::elements_count; i++) {
            if (new_el == Set<T>::elements[i]) {
                return true;
            }
        }
        return false;
    };
};


#endif //SUMMER_TASK_CRITERIA_SET_H
