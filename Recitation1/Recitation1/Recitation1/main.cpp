//
//  main.cpp
//  Recitation1
//
//  Created by David Kopala on 1/24/18.
//  Copyright © 2018 davidkopala. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

//Struct representing a car
struct CarData {
    string make;
    string model;
    string year;
    
    //Instantiates an object from a line in the source file
    CarData(string line) {
        stringstream ss(line);
        ss>>make;
        ss>>model;
        ss>>year;
    }
};

int main(int argc, const char * argv[]) {
    
    string inFilename;
    int length;
    string outFilename;
    if (argc != 4) {
        //Enable easy running in Xcode
        cout<<"Incorrect Usage!"<<endl;
        cout<<"Using default values."<<endl;
        inFilename = "/Users/davidkopala/Documents/CUBoulder/CSCI2270/Recitation1/carfile.txt";
        length = 100;
        outFilename = "/Users/davidkopala/Documents/CUBoulder/CSCI2270/Recitation1/carfile_OUT.txt";
    } else {
        //Parse the command line inputs
        inFilename = argv[1];
        length = atoi(argv[2]);
        outFilename = argv[3];
    }
    
    //Open the input file
    ifstream in(inFilename);
    //Make sure it's open
    if (!in.is_open()) {
        cout<<"BAD INPUT FILE!"<<endl;
        return -1;
    }
    //Open the output file
    ofstream out(outFilename);
    
    string line;
    
    //Create an array of pointers for the CarData objects
    CarData *data[length];
    int index = 0;
    //Iterate through the file line by line
    while (!in.eof()) {
        getline(in, line);
        
        //Add the new CarData object to the array
        data[index++] = new CarData(line);
    }
    
    //Print out the data to the output file
    for (int i = 0; i < index; i++) {
        CarData *car = data[i];
        out<<car->make<<"\t"<<car->model<<"\t"<<car->year<<endl;
    }
    
    //Close the files
    in.close();
    out.close();
    
    return 0;
}
