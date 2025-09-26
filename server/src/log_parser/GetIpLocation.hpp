#pragma once 
#include <string>
#include <maxminddb.h>


class GetIpData{
    private:
        std::string ip;
        double longitude;
        double latitude;
        std::string city;
        std::string county;
        MMDB_s mmdb;
    public:
        GetIpData();
        ~GetIpData();
        GetIpData& set_ip(const std::string ip);
        std::string get_longitude();
        std::string get_latitude();
        std::string get_city();
        std::string get_county();


};