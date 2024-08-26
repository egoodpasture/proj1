// Eric Goodpasture and Travis Tyimok
// Project 1: Organizing a music library
// Last Modified: 
// Citations:
// 1: https://bytes.com/topic/c/140538-how-replace-underscore-space-std-string
#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<algorithm>
#include<string>

using namespace std;

string sum_times(int artist, vector<vector<vector<string>>>& songs);
string album_times(vector<vector<string>>& albumsData);

string replace_underscore(string s) {
	replace(s.begin(), s.end(), '_', ' '); // citation 1
	return s;
}

int main(int argc, char* argv[]) {

	if (argc < 2) {
        cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    // Get the filename from the command line argument
    string filename = argv[1];
    ifstream fin(filename);

    // Check if the file was opened successfully
    if (!fin.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return 1;
    }

	string line;
	vector<string> artists;
	vector<vector<vector<string>>> songs;

	while(getline(fin, line)){
		stringstream ss;
		string title, time, artist, album, genre, track;
		
		ss.str(line);
		ss >> title >> time >> artist >> album >> genre >> track;
		ss.str("");
		ss.clear();
		//ss << title << time << album << genre << track;
		ss.str(title + ' ' + time + ' ' + album + ' ' + genre + ' ' + track);
		
		// if we have not already stored artist
		auto it = find(artists.begin(), artists.end(), artist);
		string val;
		vector<string> temp1;
		vector<vector<string>> temp2;
		
		if (it == artists.end()) {
			artists.push_back(replace_underscore(artist)); 
			
			while(ss >> val) temp1.push_back(replace_underscore(val));
			temp2.push_back(temp1);
			songs.push_back(temp2);
		}
		// if we have already stored artist
		else {
			int idx = distance(artists.begin(), it);
			while(ss >> val) temp1.push_back(replace_underscore(val));
			songs[idx].push_back(temp1);
		}	

	}

	//Print the library
		//	For each artist (sorted lexicographically), the program will print out the artist name, followed by a colon and space, then the number of songs that have that artist's name, followed by a comma and a space, and then the total time of all songs that have that artist's name.	
		// After each artist, you will print out each album by that artist, sorted lexicographically (and indented by eight spaces), followed again by the number of songs and total time for that album.
		// After each album, you will print out the title of each song on that album, sorted by track number. The format of each of these lines will be 16 spaces, the track number, a period, a space, the song's name, a colon, a space and the song's time.
	
	// the 'artists' vector and 'songs' vector are parallel such that the index of the
	// 'artists' index corresponds to the appropriate first index of the 'songs' vector.
	//
	// the index format for the 'songs' vector is: songs[artist][song][data]
	//
	// the data index will always be the same piece of information depending on the index
	// 0 : title
	// 1 : time
	// 2 : album
	// 3 : genre
	// 4 : track number
	//
	// number of songs per artist: songs[artist].size()
	
	// alphabetize the artists
	//sort(artists.begin(), artists.end());

    // Print the library
    for (int artistIndex = 0; artistIndex < (int)artists.size(); artistIndex++) {
        cout << artists[artistIndex] << ": " << (int)songs[artistIndex].size() << ", " << sum_times(artistIndex, songs) << endl;
		
        for (const auto& song : songs[artistIndex]) {
            string album = song[2];
            if (find(albums.begin(), albums.end(), album) == albums.end()) {
                albums.push_back(album);
            }
		}
        sort(albums.begin(), albums.end());
		
		for (int album = 0 ; i < (int)albums.size() ; album++) {
			//print album
			for (int song = 0 ; song < songs[artistIndex].size() ; song++) {
				if (abums[album] == songs[artistIndex][song][2])

			}
		}
	}

        // Sort albums for the current artist
/*
        vector<string> albums;
        vector<vector<vector<string>>> albumsData;
        for (const auto& song : songs[artistIndex]) {
            string album = song[2];
            if (find(albums.begin(), albums.end(), album) == albums.end()) {
                albums.push_back(album);
                albumsData.push_back(vector<vector<string>>());
            }
            int albumIndex = find(albums.begin(), albums.end(), album) - albums.begin();
            albumsData[albumIndex].push_back(song);
        }

        sort(albums.begin(), albums.end());

        for (int albumIndex = 0; albumIndex < (int)albums.size(); albumIndex++) {
            //for(int i = 0 ; i < (int)albums.size() ; i ++) { 
			cout << "        " << albums[albumIndex] << ": " << albumsData[albumIndex].size() << ", " << album_times(albumsData[albumIndex]) << endl;
			//}
            // Sort songs within the current album
            sort(albumsData[albumIndex].begin(), albumsData[albumIndex].end(), [](const vector<string>& a, const vector<string>& b) {
                return stoi(a[4]) < stoi(b[4]);
            });

            for (const auto& song : albumsData[albumIndex]) {
                cout << "                " << song[4] << ". " << song[0] << ": " << song[1] << endl;
            }
        }
    }

*/
	/*sort(artists.begin(), artists.end());
	for (const auto& lexArtist : artists) {
		for (int artist = 0; artist < (int)artists.size(); artist++) {
			cout << lexArtist << ": " << (int)songs[artist].size() << ", " << sum_times(artist, songs) << endl; // ** The song count is incorrect **
		}
	}*/

	/*for (int artist = 0 ; artist < (int)artists.size() ; artist++) {
		//cout << "artist: " << artists[artist] << endl;
		printf("%s: %d, %s\n",
				artists[artist].c_str(), (int)songs[artist].size(), sum_times(artist, songs).c_str());
		for (int song = 0 ; song < (int)songs[artist].size() ; song++){
			cout << "     ";
			for(int data = 0 ; data < (int)songs[artist][song].size() ; data++)
				cout << songs[artist][song][data] << ' ';
		}
		cout << "\n\n";
	}*/

	return 0;
}
string sum_times(int artist, vector<vector<vector<string>>>& songs) {
	/*int time = 0;

	return "[total time yippee!]";*/

	  int totalSeconds = 0;
    for (const auto& song : songs[artist]) {
        // Assuming song[1] is the time in "MM:SS" format
        stringstream timeStream(song[1]);
        string minutes, seconds;
        getline(timeStream, minutes, ':');
        getline(timeStream, seconds);
        totalSeconds += stoi(minutes) * 60 + stoi(seconds);
    }
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    return to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + to_string(seconds);
}

string album_times(vector<vector<string>>& albumsData) {
    int totalSeconds = 0;
    for (const auto& song : albumsData) {
        // Assuming song[1] is the time in "MM:SS" format
        stringstream timeStream(song[1]);
        string minutes, seconds;
        getline(timeStream, minutes, ':');
        getline(timeStream, seconds);
        totalSeconds += stoi(minutes) * 60 + stoi(seconds);
    }
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    return to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + to_string(seconds);
}
