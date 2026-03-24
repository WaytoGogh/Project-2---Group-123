//
// Created by Kezia Saint-Hilaire on 3/23/2026.
//

#ifndef PROJECT_2___GROUP_123_HASHMAP_H
#define PROJECT_2___GROUP_123_HASHMAP_H




class HashMap {

private:

    std::unordered_map<std::string, std::vector<Song>> map;


public:
    void insert(std::string genre, Song song);


    std::vector<Song> search(std::string genre);
};


#endif //PROJECT_2___GROUP_123_HASHMAP_H