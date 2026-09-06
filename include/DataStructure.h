//Defines the flexible Metadata struct using std::unordered_map<std::string, std::any> to hold 
//arbitrary payloads. This file also defines the templated VectorRecord<T> struct, which stores 
//the internal id, the std::vector<T> data, and the dimension() helper method.

#pragma once

#include <any>
#include <string>
#include <unordered_map>
#include <vector>

struct Metadata {
    std::unordered_map<std::string, std::any> payload;
};

template <typename T>
struct VectorRecord {
    int id;
    std::vector<T> vector;

    Metadata metadata;

    size_t dimension() const {
        return vector.size();
    }
};