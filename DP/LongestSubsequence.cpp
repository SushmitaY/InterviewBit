/*
Given an array of integers, find the length of longest subsequence which is first increasing then decreasing.

Example:

For the given array [1 11 2 10 4 5 2 1]

Longest subsequence is [1 2 10 4 2 1]

Return value 6
*/

int Solution::longestSubsequenceLength(const vector<int> &A) {
    
    int size = A.size();
    if( size == 0 ) return 0;
    vector<int> LIS(A.size());
    vector<int> LDS(A.size());

    //Filling LIS array
    LIS[0] = 1;
    for( int i=1; i<A.size(); i++ ){
        int j = i-1;
        int max = 0;
        while( j >= 0 ){
            if( A[j] < A[i] && LIS[j] > max )
                max = LIS[j];
            j--;    
        } 
        LIS[i] = max+1;
    }
    
    //Filling LDS array
    LDS[size-1] = 1;
    for( int i=A.size()-2; i>=0; i-- ){
        int j = i+1;
        int max = 0;
        while( j < A.size() ){
            if( A[j] < A[i] && LDS[j] > max )
                max = LDS[j];
            j++;  
        } 
        LDS[i] = max+1;
    }
    int max_seq = 0;
    for( int i=0; i<A.size(); i++ )
        max_seq = max( max_seq, LIS[i] + LDS[i] - 1);
    return max_seq;
}
