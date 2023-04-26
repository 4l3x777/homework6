#pragma once
#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include <array>

template <class T, T Value, size_t N>
class Matrix
{
    std::map<std::array<T, N>, T> _elements_storage;

    using elements_iterator = typename std::map<std::array<T, N>, T>::iterator;

    class Proxy
    {
    public:
        Matrix* _matrix;
        std::vector<int> _indexes;

        Proxy(Matrix* matrix, std::vector<int> indexes)
        {
            _matrix = matrix;
            _indexes = indexes;
        }

        Proxy operator[] (int index)
        {
            _indexes.push_back(index);
            if (_indexes.size() > N)
            {
                _indexes.pop_back();
                throw std::runtime_error("Matrix is N=" + std::to_string(N) + " size!");
            }
            else return *this;
        }

        Proxy operator= (T value)
        {
            set(value);
            return *this;
        }

        bool operator== (T value)
        {
           return get() == value;
        }

        void set(T value)
        {
            if (_indexes.size() != N) throw std::runtime_error("Matrix is N=" + std::to_string(N) + " size!");

            std::array<T, N> key;
            std::move(_indexes.begin(), _indexes.end(), key.begin());

            if (value == Value)
            {
                 try
                {
                    _matrix->_elements_storage.erase(key);
                }
                catch (std::out_of_range e)
                {
                    return;
                }
            }
            else
            {
                try
                {
                    _matrix->_elements_storage.at(key) = value;
                }
                catch (std::out_of_range e)
                {
                    _matrix->_elements_storage.insert(std::pair<std::array<T, N>, T>(key, value));
                }
            }
        }

        T get()
        {
            if (_indexes.size() != N) throw std::runtime_error("Matrix is N=" + std::to_string(N) + " size!");

            std::array<T, N> key;
            std::move(_indexes.begin(), _indexes.end(), key.begin());

            try
            {
                return _matrix->_elements_storage.at(key);
            }
            catch (std::out_of_range e)
            {
                return Value;
            }
        }
    };

public:

    class Iterator
    {
    public:

        Iterator(std::shared_ptr<elements_iterator> elements_iterator) : _elements_iterator(elements_iterator) {};

        std::array<T, N+1> operator* ()
        {
            std::array<T, N+1> return_value;
            std::move((**_elements_iterator).first.begin(), (**_elements_iterator).first.end(), return_value.begin());
            return_value[N] = (**_elements_iterator).second;
            return return_value;
        }

        void operator++ ()
        {
            (*_elements_iterator)++;
        }

        const Iterator& operator= (const Iterator &other) const
        {
            _elements_iterator = other._elements_iterator;
            return *this;
        }

        bool operator!= (const Iterator& other) const
        {
            return *_elements_iterator != *(other._elements_iterator);
        }

    private:

        std::shared_ptr<elements_iterator> _elements_iterator;
    };

    friend class Iterator;

    void set(std::array<T, N> index, T value)
    {
        try
        {
            _elements_storage.at(index) = value;
        }
        catch (std::out_of_range e)
        {
            _elements_storage.insert(std::pair<std::array<T, N>, T>(index, value));
        }
    }

    T get(std::array<T, N> index)
    {
        try
        {
            return _elements_storage.at(index);
        }
        catch (std::out_of_range e)
        {
            return Value;
        }
    }

    Proxy operator[] (size_t index)
    {
        std::vector<int> indexes;
        indexes.push_back(index);
        return Proxy(this, indexes);
    }

    Iterator begin()
    {
        return Iterator(std::make_shared<elements_iterator>(_elements_storage.begin()));
    }


    Iterator end()
    {
        return Iterator(std::make_shared<elements_iterator>(_elements_storage.end()));
    }

    size_t size()
    {
        return _elements_storage.size();
    }

};