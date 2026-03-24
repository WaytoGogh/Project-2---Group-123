//
// Created by Kezia Saint-Hilaire
//


#include "HashMap.h"
// insert the song into hashmap using genre.

//if the genre doesnt texit the map will create the genre

void HashMap::insert(std::string genre, Song song) {


    map[genre].push_back(song);


}

// search for songs by the genre
std::vector<Song> HashMap::search(std::string genre) {


    // if the genre happenss to exit, return the songs


    if (map.find(genre) != map.end()) {
        return map[genre];

    }

    // if not return empty!!
    return {};
}