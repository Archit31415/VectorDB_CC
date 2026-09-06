//Houses the VectorStoreIO class containing the static templated read_vecs method. It implements 
//the strict binary parsing loop, reading the 4-byte little-endian dimension integers and 
//extracting the corresponding vector bytes until EOF.
#pragma once
#include "DataStructure.h"
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <cstdint>
class VectorStoreIO{
  public:
    template<typename T>
    static std::vector<VectorRecord<T>> read_vecs(const std::string& file_path){
      std::vector<VectorRecord<T>> dataset;
      std::ifstream file(file_path,std::ios::binary);
      if(!file.is_open()){
        throw std::runtime_error("Failed to open file");
      }
      int32_t dim;
      int curr=0;
      while(file.read(reinterpret_cast<char*>(&dim),sizeof(dim))){
        VectorRecord<T> record;
        record.id =curr;
        curr++;
        record.vector.resize(dim);
        file.read(reinterpret_cast<char*>(record.vector.data()),dim*sizeof(T));
        dataset.push_back(record);
      }
      return dataset;
    }
};
