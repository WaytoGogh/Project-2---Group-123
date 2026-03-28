// Kezia Saint-Hilaire
//DEBUGGED - Kush Palem
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include "Trie.h"
#include "HashMap.h"
using namespace std;
using namespace std::chrono;

//Correctly parse all column - takes commas within track names into account
std::vector<string> parseLine(string& line) {
    std::vector<string> columns;
    std::string column;
    bool has_quotations = false;
    for (int i = 0; i < line.size(); i++) {
        char cur = line[i];
        if (cur == '"') {
            //This will put the column in and out of quotations mode
            //If the second pair of quotations are reached, it will toggle off.
            has_quotations = !has_quotations;
        }
        if (cur == ',' && !has_quotations) {
            columns.push_back(column);
            column = "";
        }
        else {
            column += cur;
        }
    }
    columns.push_back(column);
    return columns;
}

//function sorts popularity from high to low only

bool compareSongs(Song a, Song b) {



    return a.popularity > b.popularity;

}



int main() {


    Trie trie; // creating the Trie object, this will store everythingg
    HashMap hashmap;



    ifstream file("dataset.csv");


    //error check

//tries opening  the dataset file. and then an error check if that file path is wrong or the file is missing overall
    if (!file.is_open()) {




        cout << "file wasn't able to open. check file path" << endl;

        return 1;

    }
    //skipped the first line and then went on to read the file line by line
    string line;


//skip header

    getline(file, line);


    // go through each row
    while (getline(file, line)) {

        //Parse lines

        std::vector<string> columns = parseLine(line);
        //There are 20 indexes
        if (columns.size() < 21) {
            continue;
        }
        string track_name = columns[4];
        string popularityStr = columns[5];
        //The genre is in the last column/index
        string genre = columns[20];


        // popularity to integer
        int popularity = 0;

        try {
            popularity = stoi(popularityStr);
        } catch(...) {
            //sometimes the data might be weird, so we skip the bad rows!
            continue;
        }

        Song song; //create the song object to store more info
        song.title = track_name;


        song.popularity = popularity;


        //insert into the trie using the genre


        trie.buildTrie(genre, song);
        hashmap.insert(genre, song);
    }
//done reading that file
    file.close();

    cout<<"data was loaded into trie and hashmap."<<endl;


    // the search loop for the users
    while (true) {
        string input;


        cout << "\nenter genre ( or type 'exit'): ";
        cin >>input;

        if (input == "exit") {
            break;

        }
        //search the trie using input genres
        //Measure time for each search
        auto t_Start = high_resolution_clock::now();
        vector<Song> trieResults = trie.search(input);
        auto t_End = high_resolution_clock::now();
        auto t_Duration = duration_cast<microseconds>(t_End - t_Start);

        auto h_Start = high_resolution_clock::now();
        vector<Song> hashResults = hashmap.search(input);
        auto h_End = high_resolution_clock::now();
        auto h_Duration = duration_cast<microseconds>(h_End - h_Start);

        // nothing happens to be found, tell the user

        if (trieResults.size() == 0 ) {

            cout << "no songs were found." << endl;
        }
        else {
            //then sort before you print, populr songs show up at the beginning
            sort(trieResults.begin(), trieResults.end(), compareSongs);

            cout<<"\nsongs found:\n";

            for (int i =0; i < trieResults.size()&& i < 10; i++) {

                cout << trieResults[i].title

                    << " (popularity: "

                    << trieResults[i].popularity << ")"


                    <<endl;
            }
            cout << "\nPerformance Comparison:" << endl;
            cout << "Trie search time: " << t_Duration.count() << " microseconds" << endl;
            cout << "HashMap search time: " << h_Duration.count() << " microseconds" << endl;
        }
    }
    cout << "finished"<<endl;
    return 0;
}
