
#include <iostream>
#include "GetIpLocation.hpp"

GetIpData::GetIpData(){
    city=county="NONE";
    longitude=latitude=0;

    const char* mmdb_path = "./GeoLite2-City.mmdb";
    int status = MMDB_open(mmdb_path, MMDB_MODE_MMAP, &mmdb);
    if (MMDB_SUCCESS != status) {
        throw std::runtime_error( "Cannot open database (LOC): ");
    }
}
GetIpData ::~GetIpData(){
    MMDB_close(&mmdb);
}
GetIpData& GetIpData::set_ip(const std::string ip){
    this->ip=ip;
    //this->ip="8.8.8.8";
     int gai_error, mmdb_error;
    MMDB_lookup_result_s result = MMDB_lookup_string(&mmdb, this->ip.c_str(), &gai_error, &mmdb_error);
    if (gai_error != 0 || mmdb_error != MMDB_SUCCESS || !result.found_entry) {
        //std::cout<<"ip: "<<ip<<std::endl;
        throw std::runtime_error("Ip lookup  failed");
    }

    MMDB_entry_data_s entry_data;
    int ok = MMDB_get_value(&result.entry, &entry_data, "city", "names", "en", NULL);
    if (ok == MMDB_SUCCESS && entry_data.has_data && entry_data.type == MMDB_DATA_TYPE_UTF8_STRING) {
        city = std::string(entry_data.utf8_string, entry_data.data_size);
    } else {
        city = "UNKNOWN";
    }

    ok = MMDB_get_value(&result.entry, &entry_data, "country", "iso_code", NULL);
    if (ok == MMDB_SUCCESS && entry_data.has_data && entry_data.type == MMDB_DATA_TYPE_UTF8_STRING) {
        county = std::string(entry_data.utf8_string, entry_data.data_size);
    } else {
        county = "UNKNOWN";
    }

    ok = MMDB_get_value(&result.entry, &entry_data, "location", "latitude", NULL);
    if (ok == MMDB_SUCCESS && entry_data.has_data && entry_data.type == MMDB_DATA_TYPE_DOUBLE) {
        latitude = entry_data.double_value;
    } else {
        latitude = 0;
    }

    ok = MMDB_get_value(&result.entry, &entry_data, "location", "longitude", NULL);
    if (ok == MMDB_SUCCESS && entry_data.has_data && entry_data.type == MMDB_DATA_TYPE_DOUBLE) {
        longitude = entry_data.double_value;
    } else {
        longitude = 0;
    }
    return *this;
}
std::string GetIpData::get_longitude(){
    return std::to_string(longitude);
}
std::string GetIpData::get_latitude(){
    return std::to_string(latitude);
}
std::string GetIpData::get_city(){
    return city;
}
std::string GetIpData::get_county(){
    return county;
}
