#ifndef SUMMER_TASK_SET_H
#define SUMMER_TASK_SET_H

template<typename T>
class Set {
protected:
    int elements_count;
public:
    T* elements;
    Set() {
        elements_count = 0;
        elements = new T[elements_count];
    };
    ~Set() {
        delete[] elements;
    };
//    virtual bool element_belongs_to_set(T new_el) = 0;
};


#endif //SUMMER_TASK_SET_H
