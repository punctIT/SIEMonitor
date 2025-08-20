#pragma once

#include <mutex>
#include <queue>
#include <optional>
#include <iostream>

template <class T>
class ThreadSafeQueue{
    private:
        std::queue<T> quere;
        std::mutex mtx;
    public:
        ThreadSafeQueue() {
            std::cout<<"ThreadQuere\n";  
        }
        void push(T value){
            std::lock_guard<std::mutex> lock(this->mtx);
            this->quere.push(value);
        }
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