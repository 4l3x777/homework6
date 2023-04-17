/*!
    \file
    \brief Single Header realization

    That file contain Matrix class
*/
#pragma once
#include <iostream>
#include <map>
#include <memory>
#include <list>
#include <vector>

/*!
	\brief Matrix class.
    \version 1.0
    \author 4l3x77

	That class contain Matrix's fields & methods & operators

    \defgroup matrix
    @{
*/
template <class T, T Value>
class Matrix
{
    /*!
        \brief MatrixElement class.
        \version 1.0
        \author 4l3x77

        That class contain MatrixElement's fields & methods & operators

        \defgroup matrix_element
        @{
    */
    class MatrixElement 
    {
        /*!
            \brief Field contain MatrixElement's value.
        */
        T _value;

        /*!
            \brief Field contain MatrixElement's index.
        */
        size_t _idx;

        /*!
            \brief Field contain MatrixElement's parent MatrixElement.
        */        
        MatrixElement* _parent;

        /*!
            \brief Field contain MatrixElement's other layer sisters/brothers.
        */           
        std::map<size_t, std::shared_ptr<MatrixElement>> _elements_storage;

        /*!
            \brief Field contain current non-default MatrixElements.
        */ 
        std::shared_ptr<std::list<MatrixElement*>> _elements;


        /*!
            \brief Method for manage _elements.
            \param value is MatrixElement's set value.
        */
        void element_manager(T value)
        {
            for(auto iterator = _elements->begin(); iterator != _elements->end(); ++iterator)
            {
                if (this == *iterator) 
                {
                    if (value == Value) 
                    {
                        *_elements->erase(iterator);
                        return;
                    }
                    return;
                }
            }

            if (value != Value) 
            {
                _elements->push_front(this);
            }
            return;
        }
    public:

        /*!
            \brief Method for get MatrixElement's _parent.
            \returns Pointer to MatrixElement of _parent.
        */        
        MatrixElement* get_parent()
        {
            return _parent;
        }

        /*!
            \brief Method for get MatrixElement's _value.
            \returns MatrixElement's _value.
        */   
        T get_val()
        {
            return _value;
        }

        /*!
            \brief Method for get MatrixElement's _idx.
            \returns MatrixElement's _idx.
        */  
        size_t get_idx()
        {
            return _idx;
        }

        /*!
            \brief MatrixElement's constructor.
            \param value is MatrixElement's value.
            \param idx is MatrixElement's index.
            \param parent is MatrixElement's parent.
            \param elements is container of current non-default MatrixElement.
        */  
        MatrixElement(T value, size_t idx, MatrixElement* parent, std::shared_ptr<std::list<MatrixElement*>> elements) 
        {
            _value = value;
            _idx = idx;
            _parent = parent;
            _elements = elements;
        }

        /*!
            \brief Operator for set MatrixElement's value & return current MatrixElement's reference.
            \param value is MatrixElement's new value.
            \returns Current MatrixElement's reference.
        */  
        MatrixElement& operator= (T value)
        {
           _value = value;
           element_manager(value);
           return *this;
        }

        /*!
            \brief Operator for compare equals of MatrixElement's value & other value.
            \param value is other value.
            \returns True or false.
        */  
        bool operator== (T value)
        {
           return _value == value;
        }

        /*!
            \brief Operator for get MatrixElement's reference by it's index.
            \param index is MatrixElement's index.
            \returns MatrixElement's reference.
        */  
        MatrixElement& operator[] (size_t index)
        {
            try 
            {
                return *_elements_storage.at(index);         
            }
            catch (std::out_of_range e)
            {
                _elements_storage.insert(std::pair<size_t, std::shared_ptr<MatrixElement>>(index, std::make_shared<MatrixElement>(Value, index, this, _elements)));
                return *_elements_storage.at(index); 
            }
        }
    };
    /*! @} */

    /*!
        \brief Field contain MatrixElement's first layer sisters/brothers.
    */   
    std::map<size_t, std::shared_ptr<MatrixElement>> _elements_storage;

    /*!
        \brief Field contain current non-default MatrixElements.
    */ 
    std::shared_ptr<std::list<MatrixElement*>> _elements { std::make_shared<std::list<MatrixElement*>>() };
    
    /*!
        \brief Define type of _elements iterator for Iterator class .
    */     
    using elements_iterator = typename std::list<MatrixElement*>::iterator;
public:

    /*!
        \brief Iterator class.
        \version 1.0
        \author 4l3x77

        That class contain Iterator's fields & methods & operators

        \defgroup matrix_iterator
        @{
    */
    class Iterator 
    {
        /*!
            \brief Method for traversal all MatrixElements from current MatrixElement to current MatrixElement's first root parent.
            \param current_element is current MatrixElement.
            \param elements_list is container with MatrixElements from current MatrixElement to current MatrixElement's first root parent.
        */  
        void recursive_traversal(MatrixElement* current_element, std::shared_ptr<std::list<T>> elements_list) 
        {
            elements_list->push_front(current_element->get_idx());
            if (current_element->get_parent() != nullptr) 
            {
                recursive_traversal(current_element->get_parent(), elements_list);
            }
        }
    public:
        /*!
            \brief Iterator's constructor.
            \param elements_iterator is _elements iterator.
        */  
        Iterator(std::shared_ptr<elements_iterator> elements_iterator) : _elements_iterator(elements_iterator) {};

        /*!
            \brief Operator for get Iterator's value.
            \returns Container with indexes & value.
        */  
        std::vector<T> operator* ()
        {
           auto elements_list = std::make_shared<std::list<T>>();
           elements_list->push_front((**_elements_iterator)->get_val());
           elements_list->push_front((**_elements_iterator)->get_idx());
           recursive_traversal((**_elements_iterator)->get_parent(), elements_list);
           return std::vector<T>(elements_list->begin(), elements_list->end());
        }

        /*!
            \brief Operator for increment current Iterator.
        */  
        void operator++ ()
        {
            (*_elements_iterator)++;
        }

        /*!
            \brief Operator for set current Iterator to other Iterator.
            \param other is other Iterator.
            \returns Const reference to current Iterator.
        */  
        const Iterator& operator= (const Iterator &other) const
        {
            _elements_iterator = other._elements_iterator;
            return *this;
        }

        /*!
            \brief Operator for compare not equals of current Iterator & other Iterator.
            \param other is other value.
            \returns True or false.
        */  
        bool operator!= (const Iterator& other) const
        {
            return *_elements_iterator != *(other._elements_iterator);
        }

    private:
        /*!
            \brief Field contain current _elements_iterator.
        */ 
        std::shared_ptr<elements_iterator> _elements_iterator; 
    };
    /*! @} */

    /*!
        \brief Set Iterator class as friend to Matrix class.
    */     
    friend class Iterator;

    /*!
        \brief Iterator's method for begin.
    */ 
    Iterator begin() 
    {
        return Iterator(std::make_shared<elements_iterator>(_elements->begin()));
    }

    /*!
        \brief Iterator's method for end.
    */ 
    Iterator end() 
    {
        return Iterator(std::make_shared<elements_iterator>(_elements->end()));
    }

    /*!
        \brief Method for get number of non-default avaliable MatrixElements.
        \returns Number of non-default avaliable MatrixElements.
    */  
    size_t size()
    {     
        return _elements->size();
    }

    /*!
        \brief Operator for get created MatrixElement or create new MatrixElement by it's index.
        \param index is MatrixElement's index.
        \returns Reference to MatrixElement.
    */  
    MatrixElement& operator[] (size_t index)
    {
        try 
        {
            return *_elements_storage.at(index);         
        }
        catch (std::out_of_range e)
        {
            _elements_storage.insert(std::pair<size_t, std::shared_ptr<MatrixElement>>(index, std::make_shared<MatrixElement>(Value, index, nullptr, _elements)));
            return *_elements_storage.at(index);
        }
    }
};
/*! @} */
