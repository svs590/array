#include "cmesh_array.hpp"
#include "calc.hpp"

#include <iostream>

using namespace std;

void test_2d() {
    cmesh_array<2, float> a;
    a.resize({ 2, 5 });

    a(0, 0) = 1.f;
    a(0, 1) = 2.f;
    a(0, 2) = 3.f;
    a(0, 3) = 4.f;
    a(0, 4) = 5.f;
    a(1, 0) = 6.f;
    a(1, 1) = 7.f;
    a(1, 2) = 8.f;
    a(1, 3) = 9.f;
    a(1, 4) = 10.f;

    cout << "2d array sum: " << array_sum(a) << endl;
}

void test_3d() {
    cmesh_array<3, float> a;
    a.resize({ 3, 3, 3 });

    a(0, 0, 0) = 1.f;
    a(0, 0, 1) = 1.f;
    a(0, 0, 2) = 1.f;

    a(0, 1, 0) = 1.f;
    a(0, 1, 1) = 1.f;
    a(0, 1, 2) = 1.f;

    a(0, 2, 0) = 1.f;
    a(0, 2, 1) = 1.f;
    a(0, 2, 2) = 1.f;

    a(1, 0, 0) = 1.f;
    a(1, 0, 1) = 1.f;
    a(1, 0, 2) = 1.f;
      
    a(1, 1, 0) = 1.f;
    a(1, 1, 1) = 1.f;
    a(1, 1, 2) = 1.f;
      
    a(1, 2, 0) = 1.f;
    a(1, 2, 1) = 1.f;
    a(1, 2, 2) = 1.f;

    a(2, 0, 0) = 1.f;
    a(2, 0, 1) = 1.f;
    a(2, 0, 2) = 1.f;

    a(2, 1, 0) = 1.f;
    a(2, 1, 1) = 1.f;
    a(2, 1, 2) = 1.f;

    a(2, 2, 0) = 1.f;
    a(2, 2, 1) = 1.f;
    a(2, 2, 2) = 1.f;

    cout << "3d array sum: " << array_sum(a) << endl;
}

int main() {
    cout << "========== C++ array storage ==========" << endl;
    test_2d();
    test_3d();

    system("pause");
    return 0;
}