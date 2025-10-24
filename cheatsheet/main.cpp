#include <iostream>  // Include standard I/O library
#include <string>    // Include string library
using namespace std; // Use the standard namespace

// Example function declaration
int add(int x, int y) {  // Function that takes two integers and returns their sum
    return x + y;        // Return the sum
}

// Example structure
struct RobotData {
    string name;
    int id;
    double battery;
};

// Example class
class Robot {
private: // Private variables (accessible only within this class)
    string name;
    int id;
public:  // Public functions (accessible from outside)
    Robot(string n, int i) { // Constructor
        name = n;
        id = i;
    }
    void sayHello() { // Method (function in class)
        cout << "Hello! I am " << name << " with ID " << id << endl;
    }
};

int main() {
    cout << "=== C++ CHEATSHEET DEMO ===" << endl << endl;

    // 1. Variables and Basic Arithmetic
    int a = 10, b = 3;
    cout << "a = " << a << ", b = " << b << endl;
    cout << "a + b = " << a + b << endl;   // Addition
    cout << "a - b = " << a - b << endl;   // Subtraction
    cout << "a * b = " << a * b << endl;   // Multiplication
    cout << "a / b = " << a / b << endl;   // Integer division
    cout << "a % b = " << a % b << endl;   // Modulus
    cout << endl;

    // 2. Assignment & Increment / Decrement
    a += 2; // Same as a = a + 2
    cout << "After a += 2, a = " << a << endl;
    a++; // Increment
    cout << "After a++, a = " << a << endl;
    b--; // Decrement
    cout << "After b--, b = " << b << endl << endl;

    // 3. Logical and Relational Operators
    bool result = (a > b) && (b > 0);
    cout << "(a > b) && (b > 0): " << result << endl;
    cout << "(a == b): " << (a == b) << endl;
    cout << "(a != b): " << (a != b) << endl;
    cout << endl;

    // 4. Bitwise Operators
    int x = 5, y = 3; // Binary 0101 and 0011
    cout << "x & y = " << (x & y) << endl; // AND
    cout << "x | y = " << (x | y) << endl; // OR
    cout << "x ^ y = " << (x ^ y) << endl; // XOR
    cout << "~x = " << (~x) << endl;       // NOT
    cout << "x << 1 = " << (x << 1) << endl; // Left shift
    cout << "x >> 1 = " << (x >> 1) << endl; // Right shift
    cout << endl;

    // 5. If-Else and Switch
    if (a > b)
        cout << "a is greater than b" << endl;
    else if (a == b)
        cout << "a equals b" << endl;
    else
        cout << "a is less than b" << endl;

    int choice = 2;
    switch (choice) {
        case 1: cout << "Option 1 selected" << endl; break;
        case 2: cout << "Option 2 selected" << endl; break;
        default: cout << "Invalid option" << endl;
    }
    cout << endl;

    // 6. Loops
    cout << "For loop: ";
    for (int i = 0; i < 5; i++) { // i increments each time
        cout << i << " ";
    }
    cout << endl;

    cout << "While loop: ";
    int i = 0;
    while (i < 5) { // Runs as long as condition true
        cout << i << " ";
        i++;
    }
    cout << endl;

    cout << "Do-While loop: ";
    int j = 0;
    do {
        cout << j << " ";
        j++;
    } while (j < 5);
    cout << endl << endl;

    // 7. Functions
    cout << "Function add(5, 7): " << add(5, 7) << endl << endl;

    // 8. Arrays
    int nums[5] = {1, 2, 3, 4, 5};
    cout << "1D Array: ";
    for (int i = 0; i < 5; i++) cout << nums[i] << " ";
    cout << endl;

    int matrix[2][3] = {{1,2,3},{4,5,6}};
    cout << "2D Array: " << endl;
    for (int row = 0; row < 2; row++) {
        for (int col = 0; col < 3; col++)
            cout << matrix[row][col] << " ";
        cout << endl;
    }
    cout << endl;

    // 9. Pointers
    int num = 10;
    int *ptr = &num;  // Pointer stores address of num
    cout << "num = " << num << ", address = " << &num << endl;
    cout << "ptr points to = " << ptr << ", *ptr = " << *ptr << endl << endl;

    // 10. Struct and Class
    RobotData r1 = {"AlphaBot", 1, 78.5};
    cout << "Struct -> Name: " << r1.name << ", Battery: " << r1.battery << "%" << endl;

    Robot robo("RoboX", 101);
    robo.sayHello();

    cout << endl << "=== END OF CHEATSHEET ===" << endl;
    return 0; // End of program
}
