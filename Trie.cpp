//Kush Palem
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

std::vector<Song> Trie::search(std::string word) {
    TrieNode* current = root;
    for (char cur: word) {
        if (current->children[cur] == nullptr) {
            return{};
        }
        current = current->children[cur];
    }
    return current->songs;
}