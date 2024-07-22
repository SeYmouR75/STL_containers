#ifndef S21_LIST
#define S21_LIST

#include <iostream>
#include <limits>

namespace s21
{
    template <typename T>
    class list
    {
    public:
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using size_type = size_t;

        list();
        explicit list(size_type n);
        list(std::initializer_list<value_type> const &items);
        list(const list &other);
        list(list &&other);

        ~list();
        void push_front(const_reference data);
        void push_back(const_reference data);
        void pop_front();
        void pop_back();
        const_reference front() const;
        const_reference back() const;
        void swap(list &other);
        void sort();
        void merge(list &other);
        void reverse();
        void unique();
        size_type size() const;
        size_type max_size() const;
        bool empty() const;
        void clear();

        list<T> &operator=(const list<T> &other);
        list<T> &operator=(list<T> &&other);

    private:
        typedef struct Node_
        {
            value_type value_;
            Node_ *ptr_next_;
            Node_ *ptr_prev_;
            explicit Node_(value_type value)
                : value_(value), ptr_next_(nullptr), ptr_prev_(nullptr) {}
        } Node_;

        Node_ *head_;
        Node_ *tail_;
        Node_ *virtual_;
        size_type size_;

        void Initvirtual_();
        void MergeSort_(list<T> &left, list<T> &right, list<T> &result);

        class const_iterator
        {
        public:
            const_iterator() { ptr_ = nullptr; };
            explicit const_iterator(list::Node_ *node) { ptr_ = node; };
            const_iterator(const const_iterator &other) { ptr_ = other.ptr_; };
            ~const_iterator() = default;

            bool operator!=(const const_iterator &other) const
            {
                return ptr_ != other.ptr_;
            }

            bool operator==(const const_iterator &other) const
            {
                return ptr_ == other.ptr_;
            }

            const_iterator &operator=(const const_iterator &other)
            {
                if (this != &other)
                    ptr_ = other.ptr_;
                return *this;
            }

            const_reference operator*() { return ptr_->value_; }

            const_iterator operator++(int)
            {
                const_iterator tmp(*this);
                Operation_(true);
                return tmp;
            }

            const_iterator &operator++()
            {
                Operation_(true);
                return *this;
            }

            const_iterator operator--(int)
            {
                const_iterator tmp(*this);
                Operation_(false);
                return tmp;
            }

            const_iterator &operator--()
            {
                Operation_(false);
                return *this;
            }

            const_iterator operator+(size_type n)
            {
                auto it_tmp = *this;
                while (n-- > 0)
                    it_tmp.Operation_(true);
                return it_tmp;
            }

            const_iterator operator-(size_type n)
            {
                auto it_tmp = *this;
                while (n-- > 0)
                    it_tmp.Operation_(false);
                return it_tmp;
            }


            Node_ *GetNode_() const { return ptr_; }

        protected:
            Node_ *ptr_;
            void Operation_(bool isPlus)
            {
                if (isPlus)
                    ptr_ = ptr_->ptr_next_;
                else
                    ptr_ = ptr_->ptr_prev_;
            }
        };

        class iterator : public const_iterator
        {
        public:
            iterator() : const_iterator(){};
            explicit iterator(Node_ *node) : const_iterator(node){};
            iterator(const iterator &other) : const_iterator(other){};
            ~iterator() = default;

            iterator &operator=(const iterator &other)
            {
                if (this != &other)
                    this->ptr_ = other.ptr_;
                return *this;
            }

            reference operator*() { return (reference)this->ptr_->value_; }
        };

    public:
        iterator begin() const { return iterator(head_ ? head_ : virtual_); }
        iterator end() const { return iterator(virtual_); }
        iterator insert(iterator pos, const_reference value);

        template <typename... Args>
        iterator emplace(const_iterator pos, Args &&...args)
        {
            Node_ *pos_node = GetiteratorNode_(pos);
            iterator it(pos_node);
            for (auto elem : {std::forward<Args>(args)...})
            {
                insert(it, elem);
            }
            --it;
            return it;
        }

        template <typename... Args>
        void emplace_back(Args &&...args)
        {
            const_iterator it = end();
            emplace(it, std::forward<Args>(args)...);
        }

        template <typename... Args>
        void emplace_front(Args &&...args)
        {
            for (auto elem : {std::forward<Args>(args)...})
            {
                push_front(elem);
            }
        }

        void erase(iterator pos);
        void splice(iterator pos, list &other);

    private:
        Node_ *GetiteratorNode_(const_iterator iter) const
        {
            return iter.GetNode_();
        }
    };

    
} 

#include "s21_list.cpp"

#endif