#include <iostream>

/**
 * @brief Demonstrates a potential division by zero.
 * * This function checks if the input integer 'z' is zero. If it is, it
 * attempts to perform an integer division by 'z', which will cause a
 * runtime error.
 * * @param z The integer to use as the divisor.
 */
void test(int z) {
    if (z == 0) {
        // This line will cause a warning from static analyzers and a
        // floating-point exception (crash) at runtime.
        int x = 1 / z;
        std::cout << "This will not be printed." << std::endl;
    }
}

/**
 * @brief Main entry point of the program.
 * * Calls the test function with 0 to trigger the divide-by-zero error.
 */
int main() {
    std::cout << "Calling the test function with an argument of 0..." << std::endl;
    
    // This function call will cause the program to crash.
    test(0);

    // This line will not be reached.
    std::cout << "Program finished successfully." << std::endl;
    
    return 0;
}
