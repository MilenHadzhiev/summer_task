#ifndef SUMMER_TASK_UNION_SET_H
#define SUMMER_TASK_UNION_SET_H

#include "Set.h"
#include "Finite_Set.h"
#include "Criteria_Set.h"

template<typename T>
class Union_Set : public Set<T> {
    unsigned int criteria_count = 0;
    predicate<T> *criteria_arr[];

    void copy_set_elements(Set<T> &set) {
//        unsigned int n = set.get_elements_count();
        for (int i = 0; i < set.get_elements_count(); i++) {
            if (!(element_belongs_to_set(set.get_element_by_id(i)))) {
                this->elements[this->elements_count] = set.get_element_by_id(i);
                this->elements_count++;
            }
        }
    }

public:

    Union_Set() = delete;

    Union_Set(Finite_Set<T> &first_set, Finite_Set<T> &second_set) {
        Set<T>::elements = new T[first_set.elements_count + second_set.elements_count];
        copy_set_elements(first_set);
        copy_set_elements(second_set);
    }

    Union_Set(Finite_Set<T> &first_set, Criteria_Set<T> &second_set) {
        criteria_arr[criteria_count++] = second_set.criteria;
        copy_set_elements(first_set);
        copy_set_elements(second_set);
    }

    Union_Set(Criteria_Set<T> &first_set, Criteria_Set<T> &second_set) {
        criteria_arr[criteria_count++] = first_set.criteria;
        criteria_arr[criteria_count++] = second_set.criteria;
        copy_set_elements(first_set);  // for some stupid reason second_set.elements_count changes when
        copy_set_elements(second_set); // copy_set_elements is invoked the first time
    }

    Union_Set(Union_Set<T> &first_set, Criteria_Set<T> &second_set) {
        // since this is a union it includes all elements that fulfill both sets' criteria,
        // so we need to keep track of all criteria(function) pointers
        // every criteria_set has only one criteria pointer

        criteria_arr[criteria_count++] = second_set.criteria;

        for (int i = 0; i < first_set.criteria_count; i++) {
            criteria_arr[criteria_count++] = first_set.criteria_arr[i];
        }
        copy_set_elements(first_set);
        copy_set_elements(second_set);
    }

    Union_Set(Union_Set<T> &first_set, Union_Set<T> &second_set) {
        // since this is a union it includes all elements that fulfill both sets' criteria,
        // so we need to keep track of all criteria(function) pointers
        // union sets could have multiple criteria pointers
        for (int i = 0; i < first_set.criteria_count; i++) {
            criteria_arr[criteria_count++] = first_set.criteria_arr[i];
        }
        for (int i = 0; i < second_set.criteria_count; i++) {
            criteria_arr[criteria_count++] = second_set.criteria_arr[i];
        }
        copy_set_elements(first_set);
        copy_set_elements(second_set);
    }

    bool element_belongs_to_set(T &new_el) {
        for (int i = 0; i < Set<T>::elements_count; i++) {
            if (new_el == Set<T>::elements[i]) {
                return true;
            }
        }
        return false;
    }
};

#endif //SUMMER_TASK_UNION_SET_H
