// credits: followed tutorial by CoffeeBeforeArch
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class CacheSimulator {
    public:

        CacheSimulator(string pathToFile, unsigned block, unsigned ass, unsigned cpc){ // constructor for cache simulator
            in.open(pathToFile); // opening path to file
            blockSize = block;
            associate = ass;
            cap = cpc;

            int qntBlocks = (double)cap/blockSize;

            tags.resize(qntBlocks);

            int bitsBlock = __popcount(blockSize-1);
            offsetSet = bitsBlock;
            int sets = (double) cap/(blockSize*ass);
            maskSet = sets-1;
            int bitsSet = __popcount(maskSet);

            offsetTag = bitsBlock + bitsSet;
        }

        void run() { // running the simulator
            string line;
            
            while (getline(in, line)){ // while there are still lines in the input file, keep running
                extractLine(line);
            }
        }

        ~CacheSimulator() { // destructor for cache simulator
            in.close(); // closing file
        }

    private:

        ifstream in; // file will be inputted in stream

        unsigned blockSize;
        unsigned associate;
        unsigned cap;
        unsigned offsetSet;
        unsigned offsetTag;
        unsigned maskSet;

        vector<string> tags;

    
        void extractLine(string lineFromFile){ // method takes in a line from trace file and returns 
            stringstream ss(lineFromFile);
            char type;
            uint64_t address;
            int instructions;
            ss >> type >> hex >> address >> instructions;
            cout << type << ", " << hex << address << endl;
        }

        int getSet(uint64_t address){
            int shift = address >> offsetSet;
            return shift & maskSet;
        }

        int getTag(uint64_t address){
            return address >> offsetTag;
        }
        

};

int main(){
    CacheSimulator simulator("gcc.trace", 4, 0, 14); //FILL THIS IN WITH TRACE FILE
    simulator.run();
}