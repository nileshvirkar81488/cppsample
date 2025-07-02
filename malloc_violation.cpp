#include <iostream>
#include <stdlib.h> // Required for malloc() and free()
#include <string>

/**
 * A simple class with a constructor and destructor to show when objects are
 * properly created and destroyed.
 */
class Resource {
public:
    // Constructor: Called when an object is properly created.
    Resource() {
        std::cout << "  [SUCCESS] Constructor called: Resource has been created." << std::endl;
    }

    // Destructor: Called when an object is properly destroyed.
    ~Resource() {
        std::cout << "  [SUCCESS] Destructor called: Resource has been cleaned up." << std::endl;
    }

    void use() {
        std::cout << "  -> Using the resource." << std::endl;
    }
};

void test() 
{ 
    int *p = malloc(1); 
    free(p); 
    free(p); // warn: attempt to free released memory 
}

int main() {
    int *p = malloc(1); 
    free(p); 
    free(p); // warn: attempt to free released memory 
    
    std::cout << "--- 1. VIOLATION: Using C-style malloc() and free() ---" << std::endl;

    // Allocate memory for a Resource object using malloc().
    // This is a VIOLATION because the Resource constructor will NOT be called.
    std::cout << "Allocating with malloc()..." << std::endl;
    Resource* res_c = (Resource*) malloc(sizeof(Resource));

    // if (res_c == NULL) {
    //     std::cerr << "Memory allocation failed!" << std::endl;
    //     return 1;
    // }

    // At this point, memory is allocated, but the object is not properly initialized.
    res_c->use();

    // Deallocate the memory using free().
    // This is a VIOLATION because the Resource destructor will NOT be called,
    // which can lead to resource leaks in more complex classes.
    std::cout << "Deallocating with free()..." << std::endl;
    free(res_c);

    std::cout << "\nNotice above that no constructor or destructor messages appeared.\n" << std::endl;

    std::cout << "--- 2. CORRECT: Using C++ 'new' and 'delete' ---" << std::endl;

    // Allocate and initialize a Resource object using new.
    // The 'new' operator correctly allocates memory AND calls the constructor.
    std::cout << "Allocating with new..." << std::endl;
    Resource* res_cpp = new Resource();

    // The object is guaranteed to be properly initialized.
    res_cpp->use();

    // Deallocate and destroy the object using delete.
    // The 'delete' operator correctly calls the destructor AND deallocates the memory.
    std::cout << "Deallocating with delete..." << std::endl;
    delete res_cpp;

    std::cout << "\nNotice that 'new' and 'delete' correctly called the constructor and destructor.\n" << std::endl;

    return 0;
}
