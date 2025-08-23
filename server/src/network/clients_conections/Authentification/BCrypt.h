#pragma once

#include <bcrypt.h>
#include <iostream>
#include <string>

class Bcrypt{
    public:
        std::string hashPassword(const std::string password) {
            char salt[BCRYPT_HASHSIZE];
            char hash[BCRYPT_HASHSIZE];

            if (bcrypt_gensalt(12, salt) != 0) {
                throw std::runtime_error("Salt Error");
            }
            if (bcrypt_hashpw(password.c_str(), salt, hash) != 0) {
                throw std::runtime_error("Hash Error");
            }
            return std::string(hash);
        }
        bool checkPassword(const std::string password, const std::string storedHash) {
            return bcrypt_checkpw(password.c_str(), storedHash.c_str()) == 0;
        }

};