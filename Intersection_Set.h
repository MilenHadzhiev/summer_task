#ifndef SUMMER_TASK_INTERSECTION_SET_H
#define SUMMER_TASK_INTERSECTION_SET_H

#include "Set.h"
#include "Finite_Set.h"
#include "Criteria_Set.h"
#include "Union_Set.h"


template<typename T>
class Intersection_Set : public Set<T> {
    unsigned int criteria_count = 0;
    predicate<T> *criteria_arr[];
public:
    Intersection_Set() = delete;

    Intersection_Set(Finite_Set<T> &first_set, Finite_Set<T> &second_set) {
        int n = first_set.get_elements_count();
        int m = second_set.get_elements_count();
        Set<T>::elements_count = 0;
        Set<T>::elements = new T[n + m];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (first_set.get_element_by_id(i) == second_set.get_element_by_id(j) &&
                    !(element_belongs_to_set(first_set.get_element_by_id(i)))) {
                    Set<T>::elements[Set<T>::elements_count++] = i;
                    break;
                }
            }
        }
    };

    Intersection_Set(Finite_Set<T> &first_set, Criteria_Set<T> &second_set) {
        if (second_set.get_elements_count() > 0) {
            // second set is finite => just intersect the sets
            int n = first_set.get_elements_count();
            int m = second_set.get_elements_count();
            Set<T>::elements_count = 0;
            Set<T>::elements = new T[n + m];
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (first_set.get_element_by_id(i) == second_set.get_element_by_id(j) &&
                        !(element_belongs_to_set(first_set.get_element_by_id(i)))) {
                        Set<T>::elements[Set<T>::elements_count++] = first_set.get_element_by_id(i);
                        break;
                    }
                }
            }
        } else {
            // second set is infinite => intersection is a set of the elements of the first set
            // that pass the second set's criteria
            int n = first_set.get_elements_count();
            Set<T>::elements_count = 0;
            Set<T>::elements = new T[n];
            for (int i = 0; i < n; i++) {
                if (second_set.criteria(first_set.get_element_by_id(i)) &&
                    !(element_belongs_to_set(first_set.get_element_by_id(i)))) {
                    Set<T>::elements[Set<T>::elements_count++] = first_set.get_element_by_id(i);
                    break;
                }
            }
        }
    }

//    Intersection_Set(Finite_Set<T> &first_set, Union_Set<T> &second_set) {}

    Intersection_Set(Finite_Set<T> &first_set, Intersection_Set<T> &second_set) {
        int n = first_set.get_elements_count();
        int m = second_set.get_elements_count();
        int ss_cc = second_set.criteria_count;
        Set<T>::elements_count = 0;
        Set<T>::elements = new T[n + m];

        if (m == 0) {
            // second set is infinite => intersection contains all first_set elements fulfilling all second_set criteria
            for (int i = 0; i < n; i++) {
                bool flag = false;
                for (int j = 0; j < ss_cc; j++) {
                    if (second_set.criteria_arr[j](first_set.get_element_by_id(i))) {
                        flag = true;
                    } else {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    Set<T>::elements[Set<T>::elements_count++] = first_set.get_element_by_id(i);
                }
            }
        } else if (m > 0) {
            // second_set is finite => just intersect them
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (first_set.get_element_by_id(i) == second_set.get_element_by_id(i) &&
                    !(element_belongs_to_set(first_set.get_element_by_id(i)))) {
                        Set<T>::elements[Set<T>::elements_count++] = first_set.get_element_by_id(i);
                    }
                }
            }
        }
    }

    Intersection_Set(Criteria_Set<T> &first_set, Criteria_Set<T> &second_set) {
        int n = first_set.get_elements_count();
        int m = second_set.get_elements_count();
        if (n == 0 && m == 0) {
            // both sets are infinite so their intersection is the infinite set of element
            // fulfilling both criteria // or they are empty
            criteria_arr[criteria_count++] = first_set.criteria;
            criteria_arr[criteria_count++] = second_set.criteria;
        } else if (n == 0 && m > 0) {
            // only first set is infinite => intersection is all elements of the second set
            // that pass the first set's criteria
            delete[] Set<T>::elements;
            Set<T>::elements = new T[m];
            for (int i = 0; i < m; i++) {
                if (first_set.criteria(second_set.get_element_by_id(i)) &&
                    !(element_belongs_to_set(second_set.get_element_by_id(i)))) {
                    Set<T>::elements[Set<T>::elements_count++] = second_set.get_element_by_id(i);
                    break;
                }
            }
        } else if (n > 0 && m == 0) {
            // only second set is infinite => same as above
            delete[] Set<T>::elements;
            Set<T>::elements = new T[m];
            for (int i = 0; i < n; i++) {
                if (second_set.criteria(first_set.get_element_by_id(i)) &&
                    !(element_belongs_to_set(first_set.get_element_by_id(i)))) {
                    Set<T>::elements[Set<T>::elements_count++] = first_set.get_element_by_id(i);
                    break;
                }
            }
        } else if (n > 0 && m > 0) {
            // both sets are finite => just have to intersect them
            Set<T>::elements_count = 0;
            Set<T>::elements = new T[n + m];
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (first_set.get_element_by_id(i) == second_set.get_element_by_id(j) &&
                        !(element_belongs_to_set(first_set.get_element_by_id(i)))) {
                        Set<T>::elements[Set<T>::elements_count++] = first_set.get_element_by_id(i);
                        break;
                    }
                }
            }
        }
    }

    //    Intersection_Set(Criteria_Set<T> &first_set, Union_Set<T> &second_set) {}

    Intersection_Set(Criteria_Set<T> &first_set, Intersection_Set<T> &second_set) {
        int n = first_set.get_elements_count();
        int m = second_set.get_elements_count();
        if (n == 0 && m == 0) {
            // both sets are infinite/empty
            criteria_arr[criteria_count++] = first_set.criteria;
            int ss_cc = second_set.criteria_count;
            for (int i = 0; i < ss_cc; i++) {
                criteria_arr[criteria_count++] = second_set.criteria_arr[i];
            }
        } else if (n == 0 && m > 0) {
            // only first_set is infinite

            delete[] Set<T>::elements;
            Set<T>::elements_count = 0;
            Set<T>::elements = new T[m];
            for (int i = 0; i < m; i++) {
                // not checking if element is unique because second_set is object of the intersection_set class
                // and every constructor of intersection_set already checks that
                if (first_set.criteria(second_set.get_element_by_id(i))) {
                    Set<T>::elements[Set<T>::elements_count++] = second_set.get_element_by_id(i);
                }
            }
        } else if (n > 0 && m == 0) {
            // only second_set is infinite
            int ss_cc = second_set.criteria_count;
            Set<T>::elements_count = 0;
            Set<T>::elements = new T[n];
            for (int i = 0; i < n; i++) {
                bool flag = false;
                for (int j = 0; j < ss_cc; j++) {
                    // iterate over all second_set criteria to check if first_set's elements fulfill them
                    if (second_set.criteria_arr[j](first_set.get_element_by_id(i))) {
                        flag = true;
                    } else {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    Set<T>::elements[Set<T>::elements_count++] = first_set.get_element_by_id(i);
                }
            }
        } else if (n > 0 && m > 0) {
            // both sets are finite
            Set<T>::elements_count = 0;
            Set<T>::elements = new T[n + m];
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (first_set.get_element_by_id(i) == second_set.get_element_by_id(j) &&
                        !(element_belongs_to_set(first_set.get_element_by_id(i)))) {
                        Set<T>::elements[Set<T>::elements_count++] = first_set.get_element_by_id(i);
                        break;
                    }
                }
            }
        }
    }

    Intersection_Set(Intersection_Set<T> &first_set, Intersection_Set<T> &second_set) {
        int n = first_set.get_elements_count();
        int m = second_set.get_elements_count();
        int fs_cc = first_set.criteria_count;
        int ss_cc = second_set.criteria_count;
        if (n == 0 && m == 0) {
            // both sets are infinite/empty
            for (int i = 0; i < fs_cc; i++) {
                criteria_arr[criteria_count++] = first_set[i];
            }
            for (int i = 0; i < ss_cc; i++) {
                criteria_arr[criteria_count++] = second_set[i];
            }
        } else if (n == 0 && m > 0) {
            // first_set is infinite/empty
            // check which elements of second_set fulfill all first_set criteria
            Set<T>::elements_count = 0;
            Set<T>::elements = new T[m];
            for (int i = 0; i < m; i++) {
                bool flag = false;
                for (int j = 0; j < fs_cc; j++) {
                    if (first_set.criteria_arr[j](second_set.get_element_by_id(i))) {
                        flag = true;
                    } else {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    Set<T>::elements[Set<T>::elements_count++] = second_set.get_element_by_id(i);
                }
            }
        } else if (n > 0 && m == 0) {
            // second_set is infinite
            Set<T>::elements_count = 0;
            Set<T>::elements = new T[n];
            for (int i = 0; i < n; i++) {
                bool flag = false;
                for (int j = 0; j < ss_cc; j++) {
                    if (second_set.criteria_arr[j](first_set.get_element_by_id(i))) {
                        flag = true;
                    } else {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    Set<T>::elements[Set<T>::elements_count++] = first_set.get_element_by_id(i);
                }
            }
        } else if (n > 0 && m > 0) {
            // both are finite => just intersect them
            Set<T>::elements_count = 0;
            Set<T>::elements = new T[n + m];
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (first_set.get_element_by_id(i) == second_set.get_element_by_id(j) &&
                        !(element_belongs_to_set(first_set.get_element_by_id(i)))) {
                        Set<T>::elements[Set<T>::elements_count++] = first_set.get_element_by_id(i);
                        break;
                    }
                }
            }
        }
    }

//    Intersection_Set(Union_Set<T> &first_set, Union_Set<T> &second_set) {}
//
//    Intersection_Set(Union_Set<T> &first_set, Intersection_Set<T> &second_set) {}


    bool element_belongs_to_set(T &new_el) override {
        for (int i = 0; i < Set<T>::elements_count; i++) {
            if (new_el == Set<T>::elements[i]) {
                return true;
            }
        }
        return false;
    };

};

#endif //SUMMER_TASK_INTERSECTION_SET_H
