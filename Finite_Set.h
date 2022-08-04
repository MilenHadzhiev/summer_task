#include "Set.h"

#ifndef SUMMER_TASK_FINITE_SET_H
#define SUMMER_TASK_FINITE_SET_H


template<typename T>
class Finite_Set : public Set<T> {
public:
    Finite_Set() : Set<T>() {};

    Finite_Set(T *array, unsigned int new_el_count) {
        Set<T>::elements = new T[new_el_count];
        Set<T>::elements_count = 0;

        for (int i = Set<T>::elements_count; i < new_el_count; i++) {
            if (!(element_belongs_to_set(array[i]))) {
                Set<T>::elements[i] = array[i];
                Set<T>::elements_count++;
            }
        }
    };

    Finite_Set(Finite_Set<T> &other) {
        Set<T>::elements_count = other.get_elements_count();
        Set<T>::elements = new T[Set<T>::elements_count];
        for (int i = 0; i < Set<T>::elements_count; i++) {
            Set<T>::elements[i] = other.get_element_by_id(i);
        }
    }

    Finite_Set &operator=(Finite_Set<T> const &other) {
        Set<T>::elements_count = other.elements_count;
        Set<T>::elements = new T[Set<T>::elements_count];
        for (int i = 0; i < Set<T>::elements_count; i++) {
            Set<T>::elements[i] = other.get_element_by_id(i);
        }
        return *this;
    }

    void add_element(T &new_element) override {
        std::cout << "This set is immutable";
    }

    void remove_element_at_id(unsigned int id) override {
        std::cout << "This set is immutable";
    };

    bool element_belongs_to_set(T &new_el) override {
        for (int i = 0; i < Set<T>::elements_count; i++) {
            if (new_el == Set<T>::elements[i]) {
                return true;
            }
        }
        return false;
    };
};


#endif //SUMMER_TASK_FINITE_SET_H
