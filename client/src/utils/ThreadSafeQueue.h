#pragma once

#include <mutex>
#include <queue>
#include <optional>
#include <iostream>

template <class T>
class ThreadSafeQueue{
    private:
        std::queue<T> quere;
        //flag value for who has the queue
        std::mutex mtx;
    public:
        ThreadSafeQueue() {
            std::cout<<"Thread Quere\n";  
        }
        void push(T value){
            std::lock_guard<std::mutex> lock(this->mtx);
            this->quere.push(value);
        }
        //optional in case the queue is empty
        //the ideea come from Option<TYPE> form RUST- which in this case i think is superior (and others)
        std::optional<T> pop() {
            std::lock_guard<std::mutex> lock(this->mtx);
            if (this->quere.empty()) {
                return std::nullopt;
            }
            T value = this->quere.front();
            this->quere.pop();
            return value;
        }


};