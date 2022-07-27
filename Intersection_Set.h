#ifndef SUMMER_TASK_INTERSECTION_SET_H
#define SUMMER_TASK_INTERSECTION_SET_H

#include "Set.h"

template<typename T>
class Intersection_Set : public Set<T> {
public:
    Intersection_Set() = delete;

    Intersection_Set(Set<T> &first_set, Set<T> &second_set) {
        Set<T>::elements_count = 0;
        unsigned int counter = 0; // this variable does the same job as the one above, but improves readability
                                  // a little at virtually no cost
        Set<T>::elements = new T[first_set.get_elements_count() + second_set.get_elements_count()];

        for (int i = 0; i < first_set.get_elements_count(); i++) {
            if (!(this->element_belongs_to_set(first_set.get_element_by_id(i)))) {
                for (int j = 0; j < second_set.get_elements_count(); j++) {
                    if (first_set.get_element_by_id(i) == second_set.get_element_by_id(j)) {
                        Set<T>::elements[counter++] = first_set.get_element_by_id(i);
                        Set<T>::elements_count++;
                        break;
                    }
                }
            }
        }
    };

    bool element_belongs_to_set(T new_el) override {
        for (int i = 0; i < Set<T>::elements_count; i++) {
            if (new_el == Set<T>::elements[i]) {
                return true;
            }
        }
        return false;
    };
};


#endif //SUMMER_TASK_INTERSECTION_SET_H
