//Serves as the testing and validation entry point. It utilizes the loader to read 
//"siftsmall_base.fvecs" (asserting 10,000 vectors of 128 dimensions), runs the flat_search for 
//100 queries, and compares the reversed priority queue output against the ground truth to 
//validate a Recall@100 of exactly 1.0.

#include <iostream>
#include <cassert>
#include <set>
#include <vector>
#include "DataStructure.h"
#include "VectorStoreIO.h"
#include "FlatSearch.h"

int main() {
    

    std::string base_path = "../data/siftsmall_base.fvecs";
    std::string query_path = "../data/siftsmall_query.fvecs";
    std::string gt_path = "../data/siftsmall_groundtruth.ivecs";

    
    std::cout<<"Starting\n\n";
    std::vector<VectorRecord<float>> base_vectors;
    
    try {
        base_vectors = VectorStoreIO::read_vecs<float>(base_path);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\nUnable to open the file (base)\n";
        return 1;
    }


    if (base_vectors.size() != 10000) {
        std::cerr << "\nERROR!!! : Dataset size mismatch! Expected 10,000 vectors, but loaded " 
        << base_vectors.size() << "\n";
        return 1;
    }

    for (size_t i = 0; i < base_vectors.size(); ++i) {
        if (base_vectors[i].dimension() != 128) {
            std::cerr << " \nERROR: Dimension mismatch at vector index " << i+1 
            << "! Expected 128, but got " << base_vectors[i].dimension() << "\n";
            return 1; 
        }
    }

    std::cout << "\nLoaded 10,000 vectors (128 dimensions each)\n";


    // =========================================================================
    // SECTION 3.4: Recall Validation
    // =========================================================================
    std::vector<VectorRecord<float>> queries;
    std::vector<VectorRecord<int>> ground_truth;

    try {
        queries = VectorStoreIO::read_vecs<float>(query_path);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\nUnable to open the file (query)\n";
        return 1;
    }
    try {
        ground_truth = VectorStoreIO::read_vecs<int>(gt_path);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\nUnable to open the file (ground truth)\n";
        return 1;
    }

    if(queries.size()!=100)
    {
        std::cerr<<"\nERROR : Query dataset must have 100 vectors\n";
        return 1;
    }
    if(ground_truth.size()!=100)
    {
        std::cerr<<"\nError : ground truth dataset must have 100 vectors\n";
        return 1;
    }

    int k = 100;

    std::cout << "Running flat_search\n";

    for (size_t i = 0; i < queries.size(); i++) {

        std::vector<int> retrieved_ids = flat_search(queries[i].vector, base_vectors, k);

        const std::vector<int> gt_ids = ground_truth[i].vector;
        

        std::set<int> gt_set(gt_ids.begin(), gt_ids.begin() + k);

        // Calculate intersection
        int match = 0;
        for (int id : retrieved_ids) {
            if (gt_set.find(id) != gt_set.end()) {
                match++;
            }
        }

        if(match!=k)
        {
            std::cerr<<"Recall != 1 for "<<i+1<<" vector\n";
            return 1;
        }
        
    }

    std::cout<<"\nDONE : Recall = 1 for all queries\n";
    return 0;
}