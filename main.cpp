/****************************

    Program 4: IMDB
    Course: CS 141, Fall 2022.
    System: Windows 10 using Clion
    Starter Code Author: Dr. Sara Riazi
    Student Author: Alexander Arroyo

*****************************/



#include <iostream> //for the use of cin and cout
#include <cctype> //for the use of character handling functions
#include <vector> //for the use of vectors
#include <sstream> //for the use of stringstream
#include <fstream> //for the use of fstream to read files

using namespace std;


/*********************************************** Helper functions ***************************************/

//The splitString function takes a line and split it on the delimiter and push the parts into items
void splitString(string line, char delimiter, vector<string>& items ) {
    stringstream s_stream(line);
    while (s_stream.good()) {
        string item;
        getline(s_stream, item, delimiter);
        items.push_back(item);
    }
}

/**********************************************************************************************************/

//creates Struct called TitleRecord that holds information about a movie
struct TitleRecord{
    string titleID;
    string primaryTitle;
    string startYear;
    string genres;
};

//creates Struct called NameRecord that holds information about an actor/actress
struct NameRecord{
    string nameID;
    string primaryName;
    string birthYear;
    string deathYear;
    string primaryProfession;
};

//creates Struct called PrincipleRecord that holds information about movie rolls
struct PrincipleRecord{
    string titleID;
    string nameID;
    string character;
};

//runs the program
int run(string titlesFile, string namesFile, string principalsFile) {

    //counter variables
    int i;
    int j;

    //counts rows of files
    int totalRows1 = 0;
    int totalRows2 = 0;
    int totalRows3 = 0;

    //counts columns of files
    int totalColumns1 = 9;
    int totalColumns2 = 6;
    int totalColumns3 = 6;

    //holds number of movies or actors found that match the seach phrase
    int casesFound = 0;

    //holds number of user-inputted search phrase words found in a movie title
    int wordsFound = 0;

    //holds user choices
    int choice1 = 0;
    int choice2 = 0;

    //creates vectors of specific structs
    vector<TitleRecord> titles(0);
    vector<NameRecord> names(0);
    vector<PrincipleRecord> principles(0);

    //creates vectors of
    vector<TitleRecord> matchingMovies(0);
    vector<NameRecord> matchingActors(0);

    //holds all the information of the files in vectors
    vector<string> temp1;
    vector<string> temp2;
    vector<string> temp3;

    //holds all the words found in the user-inputted search phrase
    vector<string> searchWords;

    //the current line read in a file
    string currLine;

    //holds the user-inputted search phrase
    string searchPhrase;

    //holds movie or actor that was turned into all lowercase
    string tempLine;

    //holds movie genre that replaced commas with spaces
    string tempGenres;

    ifstream myFile1(titlesFile); //opens file 1 to be looked at

    //if file 1 is opened
    if (myFile1.is_open()){

        //while a new line can still be found, hold that line in currLine
        while (getline(myFile1, currLine)){

            totalRows1++; //increases totals rows of file 1 by 1
            splitString(currLine, '\t', temp1); //split currLine between tabs and holds in temp1
        }
    }
    myFile1.close(); //closes file 2

    ifstream myFile2(namesFile); //opens file 2 to be looked at

    //if file 2 is opened
    if (myFile2.is_open()){

        //while a new line can still be found, hold that line in currLine
        while (getline(myFile2, currLine)){

            totalRows2++; //increases totals rows of file 2 by 1
            splitString(currLine, '\t', temp2); //split currLine between tabs and holds in temp2
        }
    }
    myFile2.close(); //closes file 2

    ifstream myFile3(principalsFile); //opens file 3 to be looked at

    //if file 3 is opened
    if (myFile3.is_open()){

        //while a new line can still be found, hold that line in currLine
        while (getline(myFile3, currLine)){

            totalRows3++; //increases totals rows of file 3 by 1
            splitString(currLine, '\t', temp3); //split currLine between tabs and holds in temp3
        }
    }
    myFile3.close(); //closes file 3

    titles.resize(totalRows1); //resize the titles vector to the number of rows of file 1

    //for every row found in file 1
    for (i = 1; i < totalRows1; i++){

        //for every column found in file 1
        for (j = 0; j < totalColumns1; j++){

            //if column is equal to 0, hold that information in a title struct
            if (j == 0){
                titles.at(i).titleID = temp1.at(j + (i * totalColumns1));
            }

            //if column is equal to 2, hold that information in a title struct
            else if (j == 2){
                titles.at(i).primaryTitle = temp1.at(j + (i * totalColumns1));
            }

            //if column is equal to 5, hold that information in a title struct
            else if (j == 5){
                titles.at(i).startYear = temp1.at(j + (i * totalColumns1));
            }

            //if column is equal to 8, hold that information in a title struct
            else if (j == 8){
                titles.at(i).genres = temp1.at(j + (i * totalColumns1));
            }
        }
    }

    names.resize(totalRows2); //resize the titles vector to the number of rows of file 1

    //for every row found in file 2
    for (i = 1; i < totalRows2; i++){

        //for every column found in file 2
        for (j = 0; j < totalColumns2; j++){

            //if column is equal to 0, hold that information in a name struct
            if (j == 0){
                names.at(i).nameID = temp2.at(j + (i * totalColumns2));
            }

            //if column is equal to 1, hold that information in a name struct
            else if (j == 1){
                names.at(i).primaryName = temp2.at(j + (i * totalColumns2));
            }

            //if column is equal to 2, hold that information in a name struct
            else if (j == 2){
                names.at(i).birthYear = temp2.at(j + (i * totalColumns2));
            }

            //if column is equal to 3, hold that information in a name struct
            else if (j == 3){
                names.at(i).deathYear = temp2.at(j + (i * totalColumns2));
            }

            //if column is equal to 4, hold that information in a name struct
            else if (j == 4){
                names.at(i).primaryProfession = temp2.at(j + (i * totalColumns2));
            }
        }
    }

    principles.resize(totalRows3); //resize the titles vector to the number of rows of file 1

    //for every row found in file 3
    for (i = 1; i < totalRows3; i++){

        //for every column found in file 3
        for (j = 0; j < totalColumns3; j++){

            //if column is equal to 0, hold that information in a principle struct
            if (j == 0){
                principles.at(i).titleID = temp3.at(j + (i * totalColumns3));
            }

            //if column is equal to 2, hold that information in a principle struct
            else if (j == 2){
                principles.at(i).nameID = temp3.at(j + (i * totalColumns3));
            }

            //if column is equal to 5, hold that information in a principle struct
            else if (j == 5){
                principles.at(i).character = temp3.at(j + (i * totalColumns3));
            }
        }
    }

    //while choice1 is not 3
    while (choice1 != 3){

        //show menu options
        cout << "Select a menu option:" << endl;
        cout << "   1. Search for movies" << endl << "   2. Search for actors/actresses" << endl << "   3. Exit" << endl;

        //take in user-inputted choice 1
        cout << "Your choice --> ";
        cin >> choice1;
        if (cin.fail()){
            break;
        }

        //if choice is 1
        if (choice1 == 1){

            cout << "Enter search phrase: "; //ask for search phrase

            //while searchPhrase is not equal to "done"
            while (searchPhrase != "done") {

                //take in user-inputted search phrase
                cin >> searchPhrase;
                if (cin.fail()){
                    break;
                }

                //if searchPhrase is not equal to "done"
                if (searchPhrase != "done") {

                    //turns searchPhrase into lowercase
                    for (j = 0; j < searchPhrase.size(); j++) {
                        searchPhrase.at(j) = tolower(searchPhrase.at(j));
                    }

                    //splits currLine between '+' and holds in searchWords
                    splitString(searchPhrase, '+', searchWords);

                    //for all titles
                    for (i = 0; i < titles.size(); i++) {

                        //turns current title into lowercase
                        tempLine = titles.at(i).primaryTitle;
                        for (j = 0; j < tempLine.size(); j++) {
                            tempLine.at(j) = tolower(tempLine.at(j));
                        }

                        //for all searchWords
                        for (j = 0; j < searchWords.size(); j++) {

                            //if title is equal to a search word, increases wordsFound by 1
                            if (tempLine.find(searchWords.at(j)) != string::npos) {
                                wordsFound++;
                            }
                        }

                        //if title contains all search words
                        if (wordsFound == searchWords.size()) {

                            //add title to matchingMovies
                            matchingMovies.push_back(titles.at(i));

                            //turns current title genre into lowercase
                            tempGenres = titles.at(i).genres;
                            for (j = 0; j < tempGenres.size(); j++) {
                                if (tempGenres.at(j) == ',') {
                                    tempGenres.replace(j, 1, " ");
                                }
                            }

                            //displays title information
                            cout << casesFound++ << ":" << endl;
                            cout << "Title: " << titles.at(i).primaryTitle << endl;
                            cout << "Year: " << titles.at(i).startYear << endl;
                            cout << "Genre: " << tempGenres << endl;
                            cout << "---------------" << endl;
                        }
                        wordsFound = 0; //reset wordsFound to 0
                    }

                    casesFound = 0; //reset casesFound to 0

                    //if no movies were found, display "No match found!"
                    if (matchingMovies.size() == 0) {
                        cout << "No match found!" << endl;
                    }

                    //if movies were found,
                    else if (matchingMovies.size() > 0) {

                        //while choice does not equal -1
                        while (choice2 != -1) {

                            //ask user if they want to see a movies actors/actresses
                            cout << "Select a movie to see its actors/actresses (-1 to go back to the previous menu): ";

                            //take in user-inputted choice 2
                            cin >> choice2;
                            if (cin.fail()){
                                break;
                            }

                            //if choice2 does not equal -1
                            if (choice2 != -1) {

                                //display actor/actress roles
                                for (i = 0; i < principles.size(); i++) {
                                    if ((principles.at(i).titleID == matchingMovies.at(choice2).titleID) &&
                                        (principles.at(i).character != "\\N")) {
                                        for (j = 0; j < names.size(); j++) {
                                            if (names.at(j).nameID == principles.at(i).nameID) {
                                                cout << names.at(j).primaryName << " ";
                                                cout << principles.at(i).character << endl;
                                            }
                                        }
                                    }
                                }
                                choice2 = -1; //exit display for actor/actress roles
                            }

                            //if choice2 does equal -1, go back to main menu
                            else{
                                searchPhrase = "done";
                            }
                        }
                        choice2 = 0; //resets choice2
                    }
                }

                cout << "Enter search phrase (type done to go back to the previous menu): "; //asks for search phrase again
            }
            searchPhrase = ""; //resets searchPhrase
            searchWords.resize(0); //resets searchWords
            matchingMovies.resize(0); //resets matchingMovies
        }
        //if choice 1 is 2
        if (choice1 == 2){

            cout << "Enter search phrase: "; //ask for search phrase

            //while searchPhrase is not equal to "done"
            while (searchPhrase != "done") {

                //take in user-inputted search phrase
                cin >> searchPhrase;
                if (cin.fail()){
                    break;
                }

                //if searchPhrase is not equal to "done"
                if (searchPhrase != "done") {

                    //turns searchPhrase into lowercase
                    for (j = 0; j < searchPhrase.size(); j++) {
                        searchPhrase.at(j) = tolower(searchPhrase.at(j));
                    }

                    //splits currLine between '+' and holds in searchWords
                    splitString(searchPhrase, '+', searchWords);

                    //for all actors
                    for (i = 0; i < names.size(); i++) {

                        //turns current actor into lowercase
                        tempLine = names.at(i).primaryName;
                        for (j = 0; j < tempLine.size(); j++) {
                            tempLine.at(j) = tolower(tempLine.at(j));
                        }

                        //for all searchWords
                        for (j = 0; j < searchWords.size(); j++) {

                            //if actor/actress is equal to a search word, increase wordsFound by 1
                            if (tempLine.find(searchWords.at(j)) != string::npos) {
                                wordsFound++;
                            }
                        }

                        //if actor/actress contains all search words
                        if (wordsFound == searchWords.size()) {

                            //add actor/actress to matchingActors
                            matchingActors.push_back(names.at(i));

                            //display actor/actress information
                            cout << casesFound++ << ":" << endl;
                            cout << names.at(i).primaryName << endl;
                            cout << names.at(i).primaryProfession << endl;
                            cout << "(" << names.at(i).birthYear << "-" << names.at(i).deathYear << ")" << endl;
                            cout << "---------------" << endl;
                        }

                        wordsFound = 0; //reset wordsFound
                    }

                    casesFound = 0; //resets casesFound

                    //if no actors/actresses were found, display "No match found!"
                    if (matchingActors.size() == 0) {
                        cout << "No match found!" << endl;
                    }

                    //if actors/actresses were found
                    else if (matchingActors.size() > 0) {

                        //while choice2 does not equal -1
                        while (choice2 != -1) {

                            //ask user if they want to see an actors/actresses movies
                            cout << "Select an actor/actress to see movies (-1 to go back to the previous menu): ";

                            //takes in user-inputted choice2
                            cin >> choice2;
                            if (cin.fail()){
                                break;
                            }

                            //if choice2 does not equal -1
                            if (choice2 != -1) {

                                //display actor roles in movies
                                for (i = 0; i < principles.size(); i++) {
                                    if (principles.at(i).nameID == matchingActors.at(choice2).nameID) {
                                        for (j = 0; j < titles.size(); j++) {
                                            if (titles.at(j).titleID == principles.at(i).titleID) {
                                                cout << titles.at(j).primaryTitle << " ";
                                                cout << titles.at(j).startYear << " ";
                                                cout << principles.at(i).character << endl;
                                            }
                                        }
                                    }
                                }

                                choice2 = -1; //exit display for actor/actress roles
                            }

                            //if choice2 does not equal -1, go back to main menu
                            else{
                                searchPhrase = "done";
                            }
                        }

                        choice2 = 0; //reset choice2
                    }
                }

                //ask user for search phrase again
                cout << "Enter search phrase (type done to go back to the previous menu): ";
            }

            searchPhrase = ""; //reset searchPhrase
            searchWords.resize(0); //reset searchWords
            matchingActors.resize(0); //reset matchingActors
        }
    }

    return 0; //end run function
}

int main() {
    //Change these addresses according to your local machine
    string titlesFile =	"movie.titles.tsv";
    string namesFile = "movie.names.tsv";
    string principalsFile = "movie.principals.tsv";

    //DO NOT change the main function. The main function will be removed by the autograder
    run(titlesFile, namesFile, principalsFile);
    return 0;
}
