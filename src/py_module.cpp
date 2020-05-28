#include "cmesh_array.hpp"
#include "calc.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <iostream>

namespace py = pybind11;

PYBIND11_MODULE(py_array, m) {
	m.def("array_sum", 
        [](py::array_t<float> a) {

            // Для проверки создаем в C++ массив, который аллоцируется и управляется Питоном
            // Его можно использовать. По сути это numpy массив, созданный в C++
            // Таким образом, если сборка для Питона, то все массивы cmesh_array это массивы numpy
            // не зависимо от того, где они созданы - в С++ или в Питоне
            cmesh_array<2, float> c;
            c.resize({1, 1 });
            c(0, 0);

            if (a.ndim() == 2)
                return array_sum(cmesh_array<2, float>(a));
            else
                return array_sum(cmesh_array<3, float>(a));
        }
    );
}
