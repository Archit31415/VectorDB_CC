//Implements the brute-force exact nearest neighbor search. It includes the optimized squared L2 
//distance metric (skipping the final std::sqrt() to save CPU overhead) and the flat_search loop 
//that maintains a bounded std::priority_queue (max-heap) for top-k selection.