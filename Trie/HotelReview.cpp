/*
Given a set of reviews provided by the customers for different hotels and a string containing “Good Words”,
you need to sort the reviews in descending order according to their “Goodness Value” (Higher goodness value first). 
We define the “Goodness Value” of a string as the number of “Good Words” in that string.

Note: Sorting should be stable. If review i and review j have the same “Goodness Value” 
then their original order would be preserved.

Constraints:

1.   1 <= No.of reviews <= 200
2.   1 <= No. of words in a review <= 1000
3.   1 <= Length of an individual review <= 10,000
4.   1 <= Number of Good Words <= 10,000
5.   1 <= Length of an individual Good Word <= 4
6.   All the alphabets are lower case (a - z)

Input:

S : A string S containing "Good Words" separated by  "_" character. (See example below)
R : A vector of strings containing Hotel Reviews. Review strings are also separated by "_" character.
Output:

A vector V of integer which contain the original indexes of the reviews in the sorted order of reviews. 

V[i] = k  means the review R[k] comes at i-th position in the sorted order. (See example below)
In simple words, V[i]=Original index of the review which comes at i-th position in the sorted order. (Indexing is 0 based)

Example:

Input: 
S = "cool_ice_wifi"
R = ["water_is_cool", "cold_ice_drink", "cool_wifi_speed"]

Output:
ans = [2, 0, 1]
Here, sorted reviews are ["cool_wifi_speed", "water_is_cool", "cold_ice_drink"]
*/

struct TrieNode{
    struct TrieNode *child[26];
    bool isEndOfWord;
};

struct TrieNode* newNode(){
    TrieNode* p = new TrieNode;
    p->isEndOfWord = false;
    for(int i=0; i<26; i++)
        p->child[i] = NULL;
    return p;
}

void insertWord( TrieNode* root, string word ){
    
    for( int i=0; i<word.length(); i++ ){
        if( !root->child[word[i]-'a'] )
            root->child[word[i]-'a'] = newNode();
        root = root->child[word[i]-'a'];
    }    
    root->isEndOfWord = true;
}

bool isGoodWord( TrieNode* root, string word ){
    
    for( int i=0; i<word.length(); i++ ){
        if( !root->child[word[i]-'a'])  return false;
        root = root->child[word[i]-'a'];
    }
    return (root != NULL && root->isEndOfWord);
}

void insertGoodWords( TrieNode *trieRoot, string goodwords){
    int start_idx = 0;
    int len = 0;
    for( int i=0; i<goodwords.length(); i++ ){
        if( goodwords[i] == '_' ){
            insertWord(trieRoot, goodwords.substr(start_idx, len) );
            len = 0;
            start_idx = i+1;
        }
        else
            len++;
    }
    insertWord(trieRoot, goodwords.substr(start_idx, len) );
}

int goodWordCount( TrieNode *trieRoot, string review ){

    int count = 0;
    int start_idx = 0;
    int len = 0;
    
    for( int i=0; i<review.length(); i++ ){
        if( review[i] == '_' ){
            if(isGoodWord(trieRoot, review.substr(start_idx, len) )) count++;
            len = 0;
            start_idx = i+1;
        }
        else
            len++;
    }
    if(isGoodWord(trieRoot, review.substr(start_idx, len) )) count++;
    return count;
}

bool sortDes(const pair<int, int> &a, const pair<int, int> &b){
    
    if (a.first > b.first)  
        return true;
    else if ( a.first == b.first && a.second < b.second )   return true;
    return false;
}

vector<int> Solution::solve(string A, vector<string> &B) {
    
    TrieNode *trieRoot = newNode();
    insertGoodWords(trieRoot, A);
    vector<pair<int, int>> goodWordFrequency; 
    for( int i=0; i<B.size(); i++ ){
        pair<int, int> p = make_pair(goodWordCount(trieRoot, B[i]), i);
        goodWordFrequency.push_back(p);
    }
    sort( goodWordFrequency.begin(), goodWordFrequency.end(), sortDes );
    
    vector<int> sortedReview;
    for( auto it:goodWordFrequency )
        sortedReview.push_back(it.second);
    return sortedReview;
}
