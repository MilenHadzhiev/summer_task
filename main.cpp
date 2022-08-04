#include <iostream>
#include "Set.h"
#include "Criteria_Set.h"
#include "Finite_Set.h"
#include "Union_Set.h"
#include "Intersection_Set.h"
#include <fstream>

void read_file_names(int *files_count, std::string *files_arr, std::ifstream &file) {
    std::string current;
    file >> current;
    if (file.is_open()) {
        while (!current.empty()) {
            files_arr[(*files_count)++] = current;
            if (file.eof()) break;
            file >> current;
        }
    }
}

void read_bin_file_data(int* int_arr, std::string filename) {
    std::ifstream bin_file(filename, std::ios::binary);
    bin_file.seekg(0, std::ios::end);
    int bin_file_size = bin_file.tellg();
    bin_file.seekg(0, std::ios::beg);
    int data[bin_file_size];
    bin_file.read((char*) &data, bin_file_size);
}



int main() {
    std::string filenames[100];
    int files_count = 0;

    std::ifstream file("../input.txt");
    read_file_names(&files_count, filenames, file);

    file.close();
    for (int i = 0; i < files_count; i++) {
        int *data_bin_file = new int[34];
        read_bin_file_data(data_bin_file, filenames[i]);
        int *elements = new int[32];
        for (int j = 2; i < data_bin_file[0]; i++) { // n = data_bin_file[0] - the amount of numbers < 32
            elements[j-2] = data_bin_file[j];
        }
        if (data_bin_file[1] == 0) {
            // united with result
            Finite_Set<int> current_set(elements, data_bin_file[0]);
        } else if (data_bin_file[1] == 1) {
            // infinite criteria set - elements are divisible by all numbers in elements - united with result
        } else if (data_bin_file[1] == 2) {
            // infinite criteria set - elements are divisible by one number in elements - united with result
        } else if (data_bin_file[1] == 8) {
            // intersected with result
        } else if (data_bin_file[1] == 9) {
            // infinite criteria set - elements are divisible by all numbers in elements - intersected with result
        } else if (data_bin_file[1] == 10) {
            // infinite criteria set - elements are divisible by one number in elements - intersected with result
        }

        delete[] elements;
        delete[] data_bin_file;
    }

    return 0;
}
