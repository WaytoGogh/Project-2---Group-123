//
// Created by Kush P on 3/23/2026.
//

#ifndef PROJECT_2_GROUP_123_TRIE_H
#define PROJECT_2_GROUP_123_TRIE_H


#include <vector>
#include <string>

struct Song{
    std::string title;
    int popularity;
};

struct TrieNode {
    TrieNode* children[128];
    bool endOfWord;
    std::vector<Song> songs;
    TrieNode();
};

class Trie {
    TrieNode* root;
public:
    Trie();
    void buildTrie(std::string genre, Song song);
    std::vector<Song> search(std::string word);
    //void collect(TrieNode* node, std::vector<Song>& all_songs);
};

#endif //PROJECT_2_GROUP_123_TRIE_H