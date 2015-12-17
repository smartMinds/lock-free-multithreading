#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <istream>      // std::istream
#include <string>       // std::stof
#include <set>          // std::set
#include <iomanip>      // std::setprecision
#include <chrono>       // std::chrono (Time calculation)
#include <thread>       // std::thead
#include <atomic>       // std::atomic

#define CIRCULAR_BUFFER_SIZE    64
#define BUFFER_INDEX_MASK       0b00111111
#define FILE_NAME               "file.csv"

int main()
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    // Timer start
    float *circularBuffer = new float[CIRCULAR_BUFFER_SIZE];
    std::atomic<unsigned int> count(0);
    std::atomic<bool> endOfFileFlag(false);
    std::set<float> sortedResult;

    std::thread readingThread([&count, &endOfFileFlag, circularBuffer](){
        std::ifstream inputFile(FILE_NAME);
        std::string stringValue;
        float floatValue = 0;
        unsigned char tail = 0;

        while (inputFile.good()){
            std::getline(inputFile, stringValue, ';');
            floatValue = std::stof(stringValue);

            while ( count == CIRCULAR_BUFFER_SIZE )  { /*buffer is full*/ }

            // push value to the circularBuffer and shift the tail pointer
            circularBuffer[(tail & BUFFER_INDEX_MASK)] = floatValue;
            tail++;
            count++;
        }
        endOfFileFlag = true;
        inputFile.close();
    });

    std::thread sortingThread([&count, &endOfFileFlag, circularBuffer, &sortedResult](){
        unsigned char head = 0;
        for (;;) {
            while ( count == 0 ) { /*buffer is empty*/ }

            // pull value from the circularBuffer and shift the head pointer
            sortedResult.insert(circularBuffer[head & BUFFER_INDEX_MASK]);
            head++;
            count--;

            if ( endOfFileFlag && count == 0 ) {
                break;
            }
        }
    });

    readingThread.detach();
    sortingThread.join();

    // Timert stop
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << std::fixed;
    std::cout << "Spent time = " << std::setprecision(6) << elapsed_seconds.count() << "s\n";
    std::cout << std::setprecision(1);

    for ( auto &result : sortedResult ){
        std::cout << result << ';';
    }

    std::cout << std::endl;

    delete [] circularBuffer;

    return 0;
}
