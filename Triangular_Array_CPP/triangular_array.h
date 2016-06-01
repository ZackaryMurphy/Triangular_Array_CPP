#ifndef TRIANGULAR_ARRAY_H_INCLUDED
#define TRIANGULAR_ARRAY_H_INCLUDED

#include <vector>
#include <stdexcept>

template <typename data_type>
class Triangular_Array {
    private:
    protected:
        unsigned int dimension;
        std::vector<std::vector<data_type>> rows;
        void range_check(unsigned int row, unsigned int col);
        void column_range_check(unsigned int row, unsigned int col);
    public:
        Triangular_Array(unsigned int desired_dimension = 8);

        data_type get_element(unsigned int row = 0, unsigned int col = 0) const;

        void set_element(unsigned int row, unsigned int col, data_type new_element);

        void resize(unsigned int new_size);

        unsigned int get_dimension();
};

template <typename data_type>
Triangular_Array<data_type>::Triangular_Array(unsigned int desired_dimension) :
    dimension(desired_dimension), rows(desired_dimension)
{
    for (unsigned int i = 0; i < desired_dimension; i++) {
        rows[i] = new std::vector<data_type>(i+1);
    }
}

template <typename data_type>
void Triangular_Array<data_type>::range_check(unsigned int row, unsigned int col) {
    if (row >= dimension || col > row) {
        throw std::out_of_range("Triangular Array Out of Range Error: Desired element is out of range\n");
    }
}

template <typename data_type>
void Triangular_Array<data_type>::column_range_check(unsigned int row, unsigned int col) {
    if (col > row) {
        throw std::out_of_range("Triangular Array Out of Range Error: Column value can not be greater than Row value\n");
    }
}

template <typename data_type>
data_type Triangular_Array<data_type>::get_element(unsigned int row, unsigned int col) const {
    range_check(row, col);
    return rows[row][col];
}

template <typename data_type>
void Triangular_Array<data_type>::set_element(unsigned int row, unsigned int col, data_type new_element) {
    column_range_check(row, col);
    if (row >= dimension) {
        resize(row-1);
    }
    rows[row][col] = new_element;
}

template <typename data_type>
void Triangular_Array<data_type>::resize(unsigned int new_size) {
    rows.resize(new_size);
    if (new_size > dimension) {
        for (unsigned int i = dimension; i < new_size; i++) {
            rows[i] = new std::vector<data_type>(i+1);
        }
    }
    dimension = new_size;
}

template <typename data_type>
unsigned int Triangular_Array<data_type>::get_dimension() {
    return dimension;
}

#endif // TRIANGULAR_ARRAY_H_INCLUDED