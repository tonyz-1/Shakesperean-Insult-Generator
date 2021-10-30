//
//  insultgenerator_19az12.h
//  Shakespearean Insult Generator
//
//  Created by Tony Zheng on 2021-09-29.
//

#ifndef insultgenerator_19az12_h
#define insultgenerator_19az12_h

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <set>

using namespace std;

class FileException{                //file exception class
public:                             //public members
    FileException(const string&);   //constructor that takes in a string parameter
    string what() const;            //method that returns a string message
private:                            //private members
    string message;                 //string message variable
};

class NumInsultsOutOfBounds{        //number of insults out of bounds exception class
public:                                     //public members
    NumInsultsOutOfBounds(const string&);
    string what() const;
private:                                    //private members
    string message;
};

class InsultGenerator{                      //insult generator class
public:                                     //public members
    InsultGenerator();                              //constructor
    void initialize();                              //initialize method
    string talkToMe() const;                        //method to return single randomly generator insult
    vector<string> generate(const int size) const;                  //method to generate a certain requested number of insults
    void generateAndSave(string fileName, const int size) const;    //method to generate a certain requested number of insults and save them to a specified file
private:                                            //private members
    int length;                                     //length variable
    vector<string> col1;                            //column variables
    vector<string> col2;
    vector<string> col3;
    int randNumber(const int max) const;            //method to generate random number
};


#endif /* insultgenerator_19az12_h */
