#include <iostream>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include "City.h"
using namespace std;
const float NUM_SECONDS = 0.5;

int main() {
    City myCity(time(0)); // Seed for city random
    int numSteps = 1; // Number of time steps taken

    // Timer variables
    double time_counter = 0;
    clock_t this_time = clock();
    clock_t last_time = this_time;
    while(true)
    {
        this_time = clock();
        time_counter += (double)(this_time - last_time);
        last_time = this_time;
        if(time_counter > (double)(NUM_SECONDS * CLOCKS_PER_SEC))
        {
            time_counter -= (double)(NUM_SECONDS * CLOCKS_PER_SEC);
            myCity.step();
            // Comment out the next two lines when displaying the end scenario
            myCity.displayCity();
            cout << "STEPS: " << numSteps << endl;
            numSteps++;
            if(myCity.isExtinct())
                break;
        }
    }
    // Uncomment this to display the end scenario
//    myCity.displayCity();
//    cout << "STEPS: " << numSteps << endl;
    return 0;
}