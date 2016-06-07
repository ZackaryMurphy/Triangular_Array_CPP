#include <string>
#include "triangular_array.h"
void init_test();

int main() {

    init_test();
    return 0;
}

void init_test() {
    //Test default constructor
    Triangular_Array<int> i_test_array;
    //Test non-default constructor for floats
    Triangular_Array<float> f_test_array(20);
    //Test non-default constructor for doubles
    Triangular_Array<double> d_test_array(100);
    //Test setting
    for (unsigned int i = 0; i < i_test_array.get_dimension(); i++) {
        for (unsigned int j = 0; j <= i; j++) {
            i_test_array.set_element(i, j, 99);
        }
    }
    for (unsigned int i = 0; i < f_test_array.get_dimension(); i++) {
        for (unsigned int j = 0; j <= i; j++) {
            f_test_array.set_element(i, j, 137.7f);
        }
    }
    for (unsigned int i = 0; i < d_test_array.get_dimension(); i++) {
        for (unsigned int j = 0; j <= i; j++) {
            d_test_array.set_element(i, j, 99.99);
        }
    }
    i_test_array.print();
    //f_test_array.print();
    //d_test_array.print();
    i_test_array.resize(15);
    for (unsigned int i = 0; i < i_test_array.get_dimension(); i++) {
        for (unsigned int j = 0; j <= i; j++) {
            i_test_array.set_element(i, j, i+j);
        }
    }
    i_test_array.print();
    i_test_array.resize(8);
    i_test_array.print();

    try {
        i_test_array.get_element(9, 0);
    }
    catch (std::out_of_range& e) {
        std::cout<<e.what()<<std::endl;
    }

    try {
        i_test_array.get_element(0, 9);
    }
    catch (std::out_of_range& e) {
        std::cout<<e.what()<<std::endl;
    }

    try {
        i_test_array.set_element(0, 9, 9);
    }
    catch (std::out_of_range& e) {
        std::cout<<e.what()<<std::endl;
    }

    std::cout<<i_test_array[0][0]<<std::endl;

    i_test_array[0][0] = 99;

    std::cout<<i_test_array[0][0]<<std::endl;

    try {
        std::cout<<i_test_array[0][9]<<std::endl;
    }
    catch (std::exception& e) {
        std::cout<<e.what()<<std::endl;
    }

    try {
        std::cout<<i_test_array[-1][-1]<<std::endl;
    }
    catch (std::exception& e) {
        std::cout<<e.what()<<std::endl;
    }
}
