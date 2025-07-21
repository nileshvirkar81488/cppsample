#include <iostream>
#include <string>
#include <cstdlib> // Required for malloc() and free()
#include <cstring> // Required for strcpy()

// A function that allocates memory and "forgets" to free it.
void create_memory_leak() {
    std::string original_data = "This is some sample data.";

    // 1. Allocate a block of memory on the heap.
    char* buffer = (char*)malloc(100);

    // This check is good practice, but not part of the leak itself.
    if (buffer == nullptr) {
        std::cerr << "Memory allocation failed!" << std::endl;
        return;
    }

    // 2. Copy data into the allocated memory.
    // Note: strcpy is unsafe and can cause a buffer overflow if original_data is too long.
    strcpy(buffer, original_data.c_str());

    std::cout << "Buffer allocated and data copied. Function is now ending." << std::endl;

    // 3. The leak happens here.
    // We exit the function without calling free(buffer). The pointer is lost,
    // and the allocated memory can no longer be accessed or freed.

    // DeadStores.deadcode, Check for values stored to variables that are never read afterwards
    int x; x = 1; // warn

    // 4. The function's execution path stops here.
    return;

    // 5. Dead Code: The following code is unreachable.
    // Ironically, the line that would fix the leak is now unreachable.
    std::cout << "This line will never execute." << std::endl;
}

void example_function() {
    try {
        // Some risky operation that might throw an exception
        throw std::runtime_error("Something went wrong!");
    }
    catch (const std::exception& e) {
        // This is an empty catch block - no statements inside
    }
}

int main() {
    create_memory_leak();
    std::cout << "The memory allocated in the function is now leaked." << std::endl;
    // To prove the leak, run this code with a memory analysis tool like Valgrind.
    return 0;
}
