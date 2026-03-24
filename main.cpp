// Kezia Saint-Hilaire
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <Trie.h>
#include <HashMap.h>
using namespace std;

//function sorts popularity from high to low only

bool compareSongs(Song a, Song b) {



    return a.popularity > b.popularity;

}



int main() {


    Trie trie; // creating the Trie object, this will store everythingg
    HashMap hashmap;



    ifstream file("data/dataset.csv");


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
        //use stringstream to split the row


        stringstream ss(line);
        string temp; // used to skip columns that arent relevant


        string track_name;
        string popularityStr;
        string genre;

        getline(ss, temp, ','); // the trackid(x)
        getline(ss, temp, ','); //artists(x)

        getline(ss, temp, ','); //album_names(x)
        getline(ss, track_name, ','); //track_name (!!)

        getline(ss, popularityStr, ','); //popularity (!!)

        //skip everything now, only until the very last column.
        //all the columns in the middle, a necessary step


        for (int i=0; i <14; i++) {


            getline(ss, temp, ',');
        }
        //last column is the genre
        getline( ss, genre, ',');

        // popularity to integer
        int popularity = 0;

        try {
            popularity = stoi(popularityStr);
        } catch(...) {
            //sometimes the data might be weird, so we skip the bbad rows!
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
        vector<Song> trieResults = trie.search(input);


        vector<Song> hashResults = hashmap.search(input);


        // nothing happens to be found, tell the user

        if (results.size() == 0 ) {

            cout << "no songs were found." << endl;
        }
        else {
            //then sort before you print, populr songs show up at the beginning
            sort(results.begin(), results.end(), compareSongs);

            cout<<"\nsongs found:\n";

            for (int i =0; i < results.size()&& i < 10; i++) {

            cout << results[i].title

                << " (popularity: "

                << results[i].popularity << ")"


                <<endl;
        }

    }
    cout << "finished"<<endl;
    return 0;
}
