#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void encryptFile(int key, string inputFile, string outputFile); //need to  work on calcs
void decryptFile(int key, string inputFile, string outputFile); // need to work on calcs 

bool encrypt = false;
bool decrypt = false;
const int MAX_LOWER = int('z'); // 122
const int MIN_LOWER = int('a'); // 97
const int MAX_UPPER = int('Z'); // 90
const int MIN_UPPER = int('A'); // 65

// command line arguments
// -e encrypt --test
// -d decrypt --test
// -k key --done
// -i input file --done
// -o output file --done 

int main(int argc, char* argv[]){
    // check for command line arguments
    bool input = false;
    bool out = false;
    bool keyExists = false;
    int key = 0;
    string inputName = "input"; // input file name
    string outputName = "output"; // output file name
    if(argc > 1){
        for(int i = 1; i < argc; i++){
            if(argv[i][0] == '-'){
                if(argv[i][1] == 'e'){
                encrypt = true;
            }
            else if(argv[i][1] == 'd'){
                decrypt = true;
            }
            else if(argv[i][1] == 'k'){
                // key
                int j = i;
                while(!isdigit(argv[i][j])){
                    j++;
                }
                key = stoi(argv[j]);
                if(key > 26){
                    key = key % 26;
                }
                key = true;
                cout << "Key: " << key << endl;
            }
            else if(argv[i][1] == 'i'){
                // input file
                inputName = argv[i+1];
                if(inputName.find(".txt") == string::npos){
                    inputName.append(".txt");
                }
                 input = true;
            }
            else if(argv[i][1] == 'o'){
                // output file
                outputName = argv[i+1];
                if(outputName.find(".txt") == string::npos){
                    outputName.append(".txt");
                }
                out = true;
            }
            }
        }
        if(!input || !out || !key){
            cout << "Missing command line arguments" << endl;
            return 0;
        }
        
        if(encrypt){
            encryptFile(key, inputName, outputName);
        } else if(decrypt){
            decryptFile(key, inputName, outputName);
        }
    }

    return 0; 
}

void encryptFile(int key, string inputFile, string outputFile){
    cout << "Encrypting file with key: " << key << endl;
    // open input file
    ifstream inFile;
    inFile.open(inputFile);

    // open output file
    ofstream outFile;
    outFile.open(outputFile);

    // read input file
    string line;
    while(getline(inFile, line)){
        // encrypt line based on ascii values
        for(int i = 0; i < line.length(); i++){
            if(isalpha(line[i])){
                if(isupper(line[i]) && int(line[i]) + key > MAX_UPPER){
                    line[i] = char(MIN_UPPER + (int(line[i]) + key - MAX_UPPER) - 1);
                } else if (islower(line[0]) && int(line[i]) + key > MAX_LOWER){
                    line[i] = char(MIN_LOWER + (int(line[i]) + key - MAX_LOWER) - 1);
                } else{
                    line[i] = char(int(line[i]) + key); 
                }
                
            }
        }
        // write to output file
        outFile << line << endl;
    }

    // close files
    inFile.close();
    outFile.close();
}

void decryptFile(int key, string inputFile, string outputFile){
    cout << "Decrypting file.." << endl;
    // open input file
    ifstream inFile;
    inFile.open(inputFile);

    // open output file
    ofstream outFile;
    outFile.open(outputFile);

    // read input file
    string line;
    while(getline(inFile, line)){
        // decrypt line based on ascii values
        for(int i = 0; i < line.length(); i++){
            if(isalpha(line[i])){
                if(isupper(line[i])){
                    if(int(line[i]) - key < MIN_UPPER){
                        line[i] = char(MAX_UPPER - (MIN_UPPER - (int(line[i]) - key)) + 1);
                    } else if(int(line[i]) - key > MAX_UPPER){
                        line[i] = char(MIN_UPPER + (int(line[i]) - key - MAX_UPPER) - 1);
                    } else{
                        line[i] = char(int(line[i]) - key);
                    }
                }
            }
        }
        // write to output file
        outFile << line << endl;
    }

    // close files
    inFile.close();
    outFile.close();
}