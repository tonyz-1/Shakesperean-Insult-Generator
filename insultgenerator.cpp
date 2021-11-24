//  Shakespearean Insult Generator
//
//  Created by Tony Zheng on 2021-09-29.
//

#include <fstream>
#include "insultgenerator.h"

InsultGenerator::InsultGenerator() : length(0) {}

void InsultGenerator::initialize() {
    length = 0;
    string word1, word2, word3;
    ifstream fileIn("InsultsSource.txt");
    if(fileIn.fail()){
        throw FileException("Invalid File");
        return;
    }
    while(fileIn >> word1 >> word2 >> word3){
        col1.push_back(word1);
        col2.push_back(word2);
        col3.push_back(word3);
        length++;
    }
    fileIn.close();
}

int InsultGenerator::randNumber(const int max) const{
    int number = rand() % max;
    return number;
}

string InsultGenerator::talkToMe() const{
    int num1 = randNumber(length);
    int num2 = randNumber(length);
    int num3 = randNumber(length);
    return "Thou " + col1[num1] + " " + col2[num2] + " " + col3[num3] + "!";
}

vector<string> InsultGenerator::generate(const int size) const{
    if(size < 1 || size > 10000){
        throw NumInsultsOutOfBounds("The size must be between 1 and 10000");
        return vector<string>();
    }
    set<string> insults;
    while(insults.size() < size){
        insults.insert(talkToMe());
    }
    vector<string> copy(insults.begin(), insults.end());
    return copy;
}

void InsultGenerator::generateAndSave(string fileName, const int size) const{       //method generateAndSave does not call generate to maximize efficiency
    ofstream fileOut(fileName);
    set<string> insults;
    if(size < 1 || size > 10000){
        throw NumInsultsOutOfBounds("The size must be between 1 and 10000");
        return;
    }
    while(insults.size() < size){
        string insult = talkToMe();
        insults.insert(insult);
        fileOut << insult << "\n";
    }
}

FileException::FileException(const string& m) : message(m) {}

string FileException::what() const{
    return message;
}

NumInsultsOutOfBounds::NumInsultsOutOfBounds(const string& m) : message(m) {}

string NumInsultsOutOfBounds::what() const{
    return message;
}
/*
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
*/
int main() {

    InsultGenerator ig;
    vector<string> insults;
    clock_t start=0, finish=0;

    // The initialize() method should load all the source phrases from the InsultsSource.txt file into the attributes.
    // If the file cannot be read, the method should throw an exception.
    try {
        ig.initialize();
    } catch (FileException& e) {
        cerr << e.what() << endl;
        return 1;
    }

    // talkToMe() returns a single insult, generated at random.
    cout << "A single insult:" << endl;
    cout << ig.talkToMe() << endl;

    // Check number to generate limits.
    try {
        insults = ig.generate(-100);
    } catch (NumInsultsOutOfBounds& e) {
        cerr << e.what() << endl;
    }
    try {
        insults = ig.generate(40000);
    } catch (NumInsultsOutOfBounds& e) {
        cerr << e.what() << endl;
    }

    // generate() generates the requested number of unique insults.
    cout << "\n100 insults, all different:" << endl;
    insults = ig.generate(100);
    if (insults.size() > 0)
        for (int i = 0; i < 100; i++)
            cout << insults[i] << endl;
    else
        cerr << "Insults could not be generated!" << endl;

    // generateAndSave() generates the requested number of unique insults and saves them to the filename
    // supplied.  If the file cannot be written, the method should throw an exception.  Note that the
    // insults in the file should be in alphabetical order!
    // Check the number to generate limits first:
    try {
        ig.generateAndSave("Nothing.txt", 40000);
    } catch (NumInsultsOutOfBounds& e) {
        cerr << e.what() << endl;
    }
    cout << "\nSaving 1000 unique insults to a file...";
    try {
        ig.generateAndSave("SavedInsults.txt", 1000);
    } catch (FileException& e) {
        cerr << e.what() << endl;
        return 1;
    }
    cout << "done." << endl;

    // Test ability to generate the maximum number of insults and how long it takes.
    try {
        start = clock();
        insults = ig.generate(10000);
        finish = clock();
    } catch (NumInsultsOutOfBounds& e) {
        cerr << e.what() << endl;
    }
    cout << "\n" << insults.size() << " insults generated." << endl;
    cout << (1e3 * (finish - start)/CLOCKS_PER_SEC) << " msec to complete." << endl;

    return 0;

} // end main
