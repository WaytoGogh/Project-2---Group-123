//
// Created by Kush P on 3/23/2026.
//
#include "Trie.h"

TrieNode::TrieNode(){
    endOfWord = false;
    for (int i = 0; i < 128; i++) {
        children[i] = nullptr;
    }
};
Trie::Trie() {
    root = new TrieNode();
}
void Trie::buildTrie(std::string genre, Song song) {
    TrieNode* current = root;
    for (char cur: genre) {
        if (current->children[cur] == nullptr) {
            current->children[cur] = new TrieNode();
        }
        current = current->children[cur];
    }
    current->endOfWord = true;
    current->songs.push_back(song);
}
/*void Trie::collect(TrieNode* node, std::vector<Song>& all_songs) {
    all_songs.insert(all_songs.end(),node->songs.begin(),node->songs.end());
    for (int i = 0; i < 128; i++) {
        if (node->children[i] != nullptr) {
            collect(node->children[i], all_songs);
        }
    }
}*/
std::vector<Song> Trie::search(std::string word) {
    TrieNode* current = root;
    for (char cur: word) {
        if (current->children[cur] == nullptr) {
            return{};
        }
        current = current->children[cur];
    }
    //std::vector<Song> all_songs;
    //collect(current, all_songs);
    return current->songs;
}