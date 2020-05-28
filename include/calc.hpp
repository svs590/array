#pragma once

#include "cmesh_array.hpp"

template <size_t dim>
float array_sum(cmesh_array<dim, float> a);


/**
    —читаем сумму элементов массива в случае трехмерного измерени€
*/
template <>
float array_sum(cmesh_array<3, float> a) {
    float sum = 0;

    for (int i = 0; i < a.shape(0); ++i)
        for (int j = 0; j < a.shape(1); ++j)
            for (int k = 0; k < a.shape(2); ++k)
                sum += a(i, j, k);

    return sum;
}

/**
    —читаем сумму элементов массива в случае двумерного измерени€
*/
template <>
float array_sum(cmesh_array<2, float> a) {
    float sum = 0;

    for (int i = 0; i < a.shape(0); ++i)
        for (int j = 0; j < a.shape(1); ++j)
            sum += a(i, j);

    return sum;
}