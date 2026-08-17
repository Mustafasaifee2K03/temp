#include <iostream>
#include <cstring>
#include <cstdlib>

void runVulnerableFunctions(const char* userInput) {
    
    // 1. Buffer Overflow (Unsafe strcpy)
    // We allocate a small buffer, but copyuserInput of arbitrary size into it.
    char buffer[16];
    std::strcpy(buffer, userInput); 
    std::cout << "Buffer contents: " << buffer << std::endl;

    // 2. Memory Leak (malloc without free / new without delete)
    // We allocate memory on the heap, but never call free() or delete, leaking it.
    int* leak1 = (int*)malloc(100 * sizeof(int));
    double* leak2 = new double[50];
    
    // Do some work with leaked memory
    leak1[0] = 42;
    leak2[0] = 3.14;
    std::cout << "Leaked memory set: " << leak1[0] << ", " << leak2[0] << std::endl;
    
    // Missing: free(leak1); and delete[] leak2;

    // 3. Format String Vulnerability (Unsafe printf)
    // Directly passing userInput to printf allows attackers to read or write memory.
    std::printf(userInput); 
    std::printf("\n");
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <input_string>" << std::endl;
        return 1;
    }

    std::cout << "Running vulnerability tests..." << std::endl;
    runVulnerableFunctions(argv[1]);
    
    return 0;
}
