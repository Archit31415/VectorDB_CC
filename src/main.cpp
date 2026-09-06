//Serves as the testing and validation entry point. It utilizes the loader to read 
//"siftsmall_base.fvecs" (asserting 10,000 vectors of 128 dimensions), runs the flat_search for 
//100 queries, and compares the reversed priority queue output against the ground truth to 
//validate a Recall@100 of exactly 1.0.