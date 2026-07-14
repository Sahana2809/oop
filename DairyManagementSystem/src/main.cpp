#include "DairyManagementSystem.hpp"
#include <iostream>
#include <sys/stat.h>

void createDataDirectory() {
    // Simple way to ensure data/ directory exists
    #if defined(_WIN32)
        _mkdir("data");
    #else 
        mkdir("data", 0777); 
    #endif
}

int main() {
    createDataDirectory();
    DairyManagementSystem dms;
    dms.run();
    return 0;
}
