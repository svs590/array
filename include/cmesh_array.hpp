#pragma once

#include <array>
#include <memory>
#include <initializer_list>

#ifdef PYTHON_BUILD
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#endif

#if _WIN32
#define CPP_STANDART _MSVC_LANG
#else
#define CPP_STANDART __cplusplus
#endif

#if CPP_STANDART >= 201703L
#define HAS_CPP_17
#endif

template <size_t dim, typename T>
class cmesh_array_default_storage {
    using raw_holder = std::shared_ptr<T[]>;

    raw_holder              m_data = nullptr;
    std::array<size_t, dim> m_size;
    
public:
    cmesh_array_default_storage() { }
    ~cmesh_array_default_storage() { }

    void resize(std::initializer_list<size_t> size) {
        if (size.size() != dim)
            throw std::invalid_argument("Invalid array size");

        std::copy(size.begin(), size.end(), m_size.begin());
#ifndef HAS_CPP_17
        m_data.reset(new T[sizes_product<0>()], default_delete<T[]>());
#else
        m_data.reset(new T[sizes_product<0>()]);
#endif
    }

    template <typename... Ix> 
    T& operator()(Ix... index) {
        static_assert(size_t { sizeof...(Ix) } == dim,
            "Invalid number of indices"
        );
        return m_data[elem_offset<0>(index...)];
    }

    size_t shape(size_t dim) {
        return m_size[dim];
    }

    template <size_t ddim>
    cmesh_array_default_storage &mutable_unchecked() {
        static_assert(ddim == dim, "Invalid use of mutable_unchecked");
        return *this;        
    }

private:
    template <size_t current_dim, typename... Ix>
    size_t elem_offset(size_t current_index, Ix... index) { 
        return current_index * sizes_product<current_dim + 1>() 
        + elem_offset<current_dim + 1>(index...);
    }
    template <size_t current_dim = dim> size_t elem_offset() { return 0; }

    template <size_t current_dim>
    size_t sizes_product() { return m_size[current_dim] * sizes_product<current_dim + 1>(); }
    template <> size_t sizes_product<dim>() { return 1; }
};


template <size_t dim, typename T, class storage>
class cmesh_array_base {
    storage m_storage;
    
public:
    cmesh_array_base() { }
    cmesh_array_base(storage &storage) {
        m_storage = storage;
    }
    
    void resize(std::initializer_list<size_t> size) {
        m_storage.resize(size);
    }
    
    template <typename... Ix>
    T& operator()(Ix... index) {
        return m_storage.mutable_unchecked<dim>().operator()(index...);
    }

    size_t shape(size_t dim) {
        return m_storage.shape(dim);
    }
};

#ifdef PYTHON_BUILD
template <size_t dim, typename T>
using cmesh_array = cmesh_array_base<dim, T, pybind11::array_t<T>>;
#else
template <size_t dim, typename T>
using cmesh_array = cmesh_array_base<dim, T, cmesh_array_default_storage<dim, T>>;
#endif

void hello();