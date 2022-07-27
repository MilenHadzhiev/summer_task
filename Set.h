#ifndef SUMMER_TASK_SET_H
#define SUMMER_TASK_SET_H

template<typename T>
class Set {
protected:
    unsigned int elements_count;
public:
    T *elements;

    Set() {
        elements_count = 0;
        elements = new T[elements_count];
    };

    Set(T *arr, unsigned int new_el_count) {
        elements = new T[new_el_count];
        elements_count = new_el_count;
        for (int i = 0; i < elements_count; i++) {
            elements[i] = arr[i];
        }
    }

    Set(Set<T> &other) {
        elements_count = other.elements_count;
        elements = new T[elements_count];
        for (int i = 0; i < elements_count; i++) {
            elements[i] = other.elements[i];
        }

    }

    ~Set() {
        delete[] elements;
    };

    unsigned int get_elements_count() { return elements_count; };

    T get_element_by_id(unsigned int id) {
        if (id >= 0 && id < elements_count) {
            return Set<T>::elements[id];
        }
    };

    void remove_element_at_id(unsigned int id) {
        if (id < 0 || id >= elements_count) {
            std::cout << "No element found at that index";
            return;
        }
        for (unsigned int i = id; i < elements_count; i++) {
            elements[i] = elements[i + 1];
        }
        elements_count--;
    }

    virtual bool element_belongs_to_set(T new_el) = 0;
};


#endif //SUMMER_TASK_SET_H
