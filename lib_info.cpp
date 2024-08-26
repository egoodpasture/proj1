// Eric Goodpasture and Travis Tyimok
// Project 1: Organizing a music library
// Last Modified: 
// Citations:
// 1: https://bytes.com/topic/c/140538-how-replace-underscore-space-std-string
// 2: ChatGPT - Iterators and converting iterators to integers
#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<algorithm>
#include<string>

using namespace std;

string sum_times(int artist, vector<vector<vector<string>>>& songs);
string album_times(string album, int artist, vector<vector<vector<string>>>& songs);
int album_count(string album, int artist, vector<vector<vector<string>>>& songs);

string replace_underscores(string s) {
	replace(s.begin(), s.end(), '_', ' '); // citation 1
	return s;
}

int main(int argc, char* argv[]) {

	// Confirm proper usage of command line args
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
	vector<vector<vector<string>>> songs; // Will serve as the container for the entire library

	// The 'artists' vector and 'songs' vector are parallel such that the index of the
	// 'artists' index corresponds to the appropriate first index of the 'songs' vector.
	//
	// The index format for the 'songs' vector is: songs[artist][song][data]
	//
	// The data index will always be the same piece of information depending on the index
	// 0 : title
	// 1 : time
	// 2 : album
	// 3 : genre
	// 4 : track number
	//
	// Number of songs per artist: songs[artist].size()

	// Read in and store the library
	while(getline(fin, line)){
		stringstream ss;
		string title, time, artist, album, genre, track;
		
		ss.str(line);
		ss >> title >> time >> artist >> album >> genre >> track;
		ss.str("");
		ss.clear();
		ss.str(title + ' ' + time + ' ' + album + ' ' + genre + ' ' + track);
		
		artist = replace_underscores(artist);

		// Check if we have already stored the artist
		auto it = find(artists.begin(), artists.end(), artist); // Citation 2
		string val;
		vector<string> temp1;
		vector<vector<string>> temp2;
		
		// If we have not already stored artist
		if (it == artists.end()) {
			artists.push_back(artist); 
			
			while(ss >> val) temp1.push_back(replace_underscores(val)); // Store the data
			temp2.push_back(temp1); // Store the data vector in the song
			songs.push_back(temp2); // Store the song in the artist (this also initilizes the artist's 'bin')
		}
		// If we have already stored artist
		else {
			int idx = distance(artists.begin(), it); // Citation 2
			while(ss >> val) temp1.push_back(replace_underscores(val)); // Store the data
			songs[idx].push_back(temp1); //Store the song in the already created artist's 'bin'
		}	

	}

	// Create a sorted vector of artists. This will allow us to print in the correct order
	vector<string> sortedArtists;
	for (int i = 0 ; i < (int)artists.size() ; i++) sortedArtists.push_back(artists[i]);			
    sort(sortedArtists.begin(), sortedArtists.end());

	// Begin printing the library by artist
	for (string sortedArtist : sortedArtists) {
		
		// Find the artist we want to print based on the sorted list and store its index
		int artistIndex = distance(artists.begin(), find(artists.begin(), artists.end(), sortedArtist));

		// Print the artist's heading
		cout << artists[artistIndex] << ": " << (int)songs[artistIndex].size() << ", " << sum_times(artistIndex, songs) << endl;
		
		// Create a sorted vector of albums. This will allow us to print in the correct order
		vector<string> albums;
		for (auto& song : songs[artistIndex]) {
			string album = song[2];
			if (find(albums.begin(), albums.end(), album) == albums.end()) {
				albums.push_back(album);
			}
		}
		sort(albums.begin(), albums.end());

		// Begin printing the albums
		for (int album = 0 ; album < (int)albums.size() ; album++) {
			// Print the album's heading
			cout << "        " << albums[album] << ": " << album_count(albums[album], artistIndex, songs) 
				<< ", " << album_times(albums[album], artistIndex, songs) << endl;
			
			// Sort the songs based on their track listing --------> CITATION NEEDED TRAVIS <-----------
			sort(songs[artistIndex].begin(), songs[artistIndex].end(),
					[] (const vector<string>& a, const vector<string>& b) {return stoi(a[4]) < stoi(b[4]);});

			// Begin printing tracks
			for (int song = 0 ; song < (int)songs[artistIndex].size() ; song++) {
				if (albums[album] == songs[artistIndex][song][2])
					cout << "                " << songs[artistIndex][song][4] << ". " 
						<< songs[artistIndex][song][0] << ": " << songs[artistIndex][song][1] << endl;
			}
		}
	}

	return 0;
}

string sum_times(int artist, vector<vector<vector<string>>>& songs) {
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

string album_times(string album, int artist, vector<vector<vector<string>>>& songs) {
    int totalSeconds = 0;
    for (const auto& song : songs[artist]) {
		if (album == song[2]) {
			// Assuming song[1] is the time in "MM:SS" format
			stringstream timeStream(song[1]);
			string minutes, seconds;
			getline(timeStream, minutes, ':');
			getline(timeStream, seconds);
			totalSeconds += stoi(minutes) * 60 + stoi(seconds); 
		}
    }
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    return to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + to_string(seconds);
}

int album_count(string album, int artist, vector<vector<vector<string>>>& songs) {
    int count;
	for (const auto& song : songs[artist]) {
		// Only count the song if its in the album we are looking at
		if (album == song[2]) {
			count++;
		}
    }

	return count;
}
