/*
Find shortest unique prefix to represent each word in the list.

Example:

Input: [zebra, dog, duck, dove]
Output: {z, dog, du, dov}
where we can see that
zebra = z
dog = dog
duck = du
dove = dov

NOTE : Assume that no word is prefix of another. In other words, the representation is always possible.  
*/

struct TrieNode{
    int count;
    struct TrieNode *child[26];
};

TrieNode* getNode(){
    
    TrieNode *node = new TrieNode;
    node->count = 1;
    for( int i=0; i<26; i++ )
        node->child[i] = NULL;
    return node;
}

void insertWord( TrieNode *root, string word ){
    
    TrieNode *t = root;
    for( int i=0; i<word.length(); i++ ){
        if( t->child[word[i]-'a']){
            t = t->child[word[i]-'a'];
            t->count = t->count + 1;
        }
        else{
            t->child[word[i]-'a'] = getNode();
            t = t->child[word[i]-'a'];
        }
    }
}

string uniquePrefix( TrieNode *root, string word){
    TrieNode *t = root;
    string prefix = "";
    for( int i=0; i<word.length(); i++ ){
        prefix.push_back(word[i]);
        if( t->child[word[i]-'a']->count == 1 )
            return prefix;
        t = t->child[word[i]-'a'];
    }
    return prefix;
}
vector<string> Solution::prefix(vector<string> &A) {
    vector<string> res;
    TrieNode* root = getNode();
    
    for( int i=0; i<A.size(); i++ )
        insertWord(root, A[i]);
        
    for( int i=0; i<A.size(); i++ )
        res.push_back( uniquePrefix(root, A[i]) );
    return res;
}
