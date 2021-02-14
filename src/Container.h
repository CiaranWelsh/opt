//
// Created by Ciaran on 13/02/2021.
//

#ifndef SRES_CONTAINER_H
#define SRES_CONTAINER_H

#include <vector>

namespace opt {

    template <class T>
    class Container {

    public:
        Container() = default;

        explicit Container(int size):
            contents_(std::vector<T>(size)){};

        explicit Container(std::vector<T> contents)
            : contents_(contents) {};

        explicit Container(std::vector<std::vector<T>> contents)
            : contents_(contents) {};

        Container(std::initializer_list<T> contents)
            : contents_(std::vector<T>(contents.begin(), contents.end())){};

        T& operator[](int index){
            return contents_[index];
        }

        Container<T> slice(int start, int end){
            return Container<T>(std::vector<T>(contents_.begin()+start, contents_.begin()+end));
        }

        typename std::vector<T>::iterator begin(){
            return contents_.begin();
        }

        typename std::vector<T>::iterator end(){
            return contents_.end();
        }

        bool operator==(const Container &rhs) const {
            return contents_ == rhs.contents_;
        }

        bool operator!=(const Container &rhs) const {
            return rhs != *this;
        }

        virtual ~Container() = default;

        T* data(){
            return contents_.data();
        }

        const std::vector<T> &getContents() const {
            return contents_;
        }

        void setContents(const std::vector<T> &contents) {
            contents_ = contents;
        }

        int size(){
            return contents_.size();
        }

    protected:
        std::vector<T> contents_;


    };
}


#endif //SRES_CONTAINER_H
