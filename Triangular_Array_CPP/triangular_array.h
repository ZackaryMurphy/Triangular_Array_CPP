#ifndef TRIANGULAR_ARRAY_H_INCLUDED
#define TRIANGULAR_ARRAY_H_INCLUDED
#include <iostream>
#include <vector>
#include <stdexcept>

/*
TODO: ADD ITERATOR
*/

template <typename data_type>
class Triangular_Array {
    private:
    protected:
        unsigned int dimension;
        std::vector<std::vector<data_type>> rows;
        void range_check(unsigned int row, unsigned int col) const;
        void row_range_check(unsigned int row) const;
        void column_range_check(unsigned int row, unsigned int col) const;
        class Vector_Guard {
            private:
            protected:
                std::vector<data_type>* guard_vector;
            public:
                Vector_Guard(std::vector<data_type> *source);
                Vector_Guard(const Triangular_Array<data_type>::Vector_Guard& origin);
                ~Vector_Guard();
                Vector_Guard& operator=(const Triangular_Array<data_type>::Vector_Guard& src);
                data_type& operator[](unsigned int index);
        };

    public:
        explicit Triangular_Array(unsigned int desired_dimension = 8);

        data_type get_element(unsigned int row = 0, unsigned int col = 0) const;

        void set_element(unsigned int row, unsigned int col, data_type new_element);

        void resize(unsigned int new_size);

        unsigned int get_dimension();

        void print() const;

        Vector_Guard& operator[](unsigned int index);
};

template <typename data_type>
Triangular_Array<data_type>::Triangular_Array(unsigned int desired_dimension) :
    dimension(desired_dimension), rows(desired_dimension)
{
    for (unsigned int i = 0; i < desired_dimension; i++) {
        rows[i].resize(i+1);
    }
}

template <typename data_type>
void Triangular_Array<data_type>::range_check(unsigned int row, unsigned int col) const {
    if (row >= dimension || col > row) {
        throw std::out_of_range("Triangular Array Out of Range Error: Desired element is out of range\n");
    }
}

template <typename data_type>
void Triangular_Array<data_type>::row_range_check(unsigned int row) const {
    if (row >= dimension) {
        throw std::out_of_range("Triangular Array Out of Range Error: Desired element is out of range\n");
    }
}

template <typename data_type>
void Triangular_Array<data_type>::column_range_check(unsigned int row, unsigned int col) const {
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
            rows[i].resize(i+1);
        }
    }
    dimension = new_size;
}

template <typename data_type>
unsigned int Triangular_Array<data_type>::get_dimension() {
    return dimension;
}

template <typename data_type>
void Triangular_Array<data_type>::print() const {
    for (unsigned int i = 0; i < dimension; i++) {
        for (unsigned int j = 0; j <= i; j++) {
            std::cout<<rows[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

template <typename data_type>
typename Triangular_Array<data_type>::Vector_Guard& Triangular_Array<data_type>::operator[](unsigned int index) {
    row_range_check(index);
    return *(new Vector_Guard(&(rows[index])));
}

template <typename data_type>
Triangular_Array<data_type>::Vector_Guard::Vector_Guard(std::vector<data_type> *source) : guard_vector(source)
{}

template <typename data_type>
Triangular_Array<data_type>::Vector_Guard::Vector_Guard(const Triangular_Array<data_type>::Vector_Guard& origin) {
    guard_vector = origin.guard_vector;
}

template <typename data_type>
Triangular_Array<data_type>::Vector_Guard::~Vector_Guard() {
    guard_vector = NULL;
}

template <typename data_type>
typename Triangular_Array<data_type>::Vector_Guard& Triangular_Array<data_type>::Vector_Guard::operator=(const Triangular_Array<data_type>::Vector_Guard& src) {
    this.guard_vector = src.guard_vector;
    return this;
}

template <typename data_type>
data_type& Triangular_Array<data_type>::Vector_Guard::operator[](unsigned int index) {
    if (index >= guard_vector->size()) {
        throw std::out_of_range("Triangular Array Out of Range Error: Desired element is out of range\n");
    }
    return (*guard_vector)[index];
}

#endif // TRIANGULAR_ARRAY_H_INCLUDED
