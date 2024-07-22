// rename
#include "s21_vector.h"
#include <algorithm>

using namespace s21;

template <typename T>
void vector<T>::reserve_more_capacity(size_t size)
{
    if (size > m_capacity)
    {
        value_type *buff = new value_type[size];
        for (size_t i = 0; i < m_size && arr != nullptr; ++i)
            buff[i] = std::move(arr[i]);
        delete[] arr;
        arr = buff;
        m_capacity = size;
    }
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items)
{
    arr = new value_type[items.size()];
    int i = 0;
    for (auto it = items.begin(); it != items.end(); it++)
    {
        arr[i] = *it;
        i++;
    }
    m_size = items.size();
    m_capacity = items.size();
};

template <typename T>
T vector<T>::at(size_type i)
{
    if (i >= m_size)
    {
        throw std::out_of_range("Index out of range");
    }
    return arr[i];
}

template <typename T>
T vector<T>::operator[](size_type i)
{
    return arr[i];
}

template <typename T>
T vector<T>::operator[](size_type i) const
{
    return arr[i];
}

template <typename T>
void vector<T>::push_back(T v)
{
    if (m_size == m_capacity)
    {
        reserve_more_capacity(m_capacity == 0 ? 1 : m_capacity * 2);
    }
    arr[m_size++] = v;
}

template <typename T>
void vector<T>::pop_back()
{
    if (m_size > 0)
    {
        m_size--;
    }

    else throw(std::out_of_range("Empty vector"));
}

template <typename T>
void vector<T>::swap(vector<T>& other) {
        std::swap(arr, other.arr);
        std::swap(m_capacity, other.m_capacity);
        std::swap(m_size, other.m_size);
    }

template <typename T>
typename vector<T>::iterator vector<T>::iterator::operator++(int)
{
    iterator tmp = *this;
    ++(*this);
    return tmp;
}

template <typename T>
typename vector<T>::iterator &vector<T>::iterator::operator++()
{
    ++ptr;
    return *this;
}

template <typename T>
typename vector<T>::iterator vector<T>::iterator::operator--(int)
{
    iterator tmp = *this;
    --(*this);
    return tmp;
}

template <typename T>
typename vector<T>::iterator &vector<T>::iterator::operator--()
{
    --ptr;
    return *this;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::const_iterator::operator++(int)
{
    const_iterator tmp = *this;
    ++(*this);
    return tmp;
}

template <typename T>
typename vector<T>::const_iterator &vector<T>::const_iterator::operator++()
{
    ++ptr;
    return *this;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::const_iterator::operator--(int)
{
    const_iterator tmp = *this;
    --(*this);
    return tmp;
}

template <typename T>
typename vector<T>::const_iterator &vector<T>::const_iterator::operator--()
{
    --ptr;
    return *this;
}