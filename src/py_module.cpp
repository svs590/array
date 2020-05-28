#include "cmesh_array.hpp"
#include "calc.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <iostream>

namespace py = pybind11;

PYBIND11_MODULE(py_array, m) {
	m.def("array_sum", 
        [](py::array_t<float> a) {

            // ��� �������� ������� � C++ ������, ������� ������������ � ����������� �������
            // ��� ����� ������������. �� ���� ��� numpy ������, ��������� � C++
            // ����� �������, ���� ������ ��� ������, �� ��� ������� cmesh_array ��� ������� numpy
            // �� �������� �� ����, ��� ��� ������� - � �++ ��� � ������
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
