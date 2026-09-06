//Implements the brute-force exact nearest neighbor search. It includes the optimized squared L2 
//distance metric (skipping the final std::sqrt() to save CPU overhead) and the flat_search loop 
//that maintains a bounded std::priority_queue (max-heap) for top-k selection.
#pragma once
#include "DataStructure.h"
#include <vector>
#include <queue>
#include <utility>

inline float sqL2dist(const std::vector<float>&a, const std::vector<float>&b){
    float dist=0.0;
    for(size_t i=0;i<a.size();i++){
        float diff=a[i]-b[i];
        dist+=diff*diff;
    }
    return dist;
}
inline std::vector<int> flat_search(const std::vector<float>& query, const std::vector<VectorRecord<float>>& base, int k){
    std::priority_queue<std::pair<float,int>> pq;

    for(const auto& record : base){
        float dist=sqL2dist(query,record.vector);
        if(pq.size()<k){pq.push({dist,record.id});}
        else if(dist<pq.top().first){
            pq.pop();pq.push({dist,record.id});
        }
    }
    std::vector<int> res(pq.size());
    for(int i=res.size()-1;i>=0;i--){
        res[i]=pq.top().second;
        pq.pop();
    }
    
    return res;

}