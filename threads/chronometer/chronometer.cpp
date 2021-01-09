#include <bits/stdint-uintn.h>
#include <iostream>
#include <thread>
#include <iomanip>
#include <chrono>

bool keepRunning{true};

inline void printTime(uint32_t hour, uint32_t minute, uint32_t second) {
    std::cout << std::fixed << std::setfill('0') << std::right;
    std::cout.put(char(13)); // Return to the beginning of the line
    std::cout << std::setw(2) << hour << ':' << std::setw(2) << minute << ':'  << std::setw(2) << second;
    std::cout.flush(); // Send the characters to the screen
}

void chronometerProcess() {
    for (uint32_t hour = 0; hour < 60; ++hour) {
        for (uint32_t minute = 0; minute < 60; ++minute) {
            for (uint32_t second = 0; second < 60; ++second) {
                if (!keepRunning) return;
                printTime(hour, minute, second);
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
    }
}

void stopChronoThread() {
    std::cin.get(); // Input any character will terminate execution
    keepRunning = false;
    std::cout << "Stopping threads..." << std::endl;
}
int main() {
    std::ios_base::sync_with_stdio(false); // Fast IO operations
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cout << "Starting threads... (Press Enter to finish execution.)" << std::endl;

    std::thread chronoThread(chronometerProcess);
    std::thread stopChrono(stopChronoThread);
    chronoThread.join();
    stopChrono.join();
    return 0;
}
