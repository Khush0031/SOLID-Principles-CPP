/**
 * ============================================================================
 * PRINCIPLE 3: LISKOV SUBSTITUTION PRINCIPLE (LSP) - THE BAD WAY
 * ============================================================================
 * 
 * 📖 WHAT IS THE THEORY?
 * The Liskov Substitution Principle says:
 * "Derived classes must be substitutable for their base classes without breaking
 * the correctness of the program."
 * 
 * In simple English:
 * If class `Dog` inherits from class `Animal`, anywhere in your code where an `Animal`
 * is expected, you should be able to pass a `Dog` without the program crashing or
 * producing weird, unexpected behavior!
 * 
 * 🐧 CLASSIC EXAMPLE: The Flightless Bird (from Oleksandra Shershen's article)
 * - In the real world, a Penguin is a Bird.
 * - But in software, if the base class `Bird` has a method `fly()`, what does
 *   a `Penguin` do?
 * - If `Penguin` inherits from `Bird` and throws an exception or does nothing in `fly()`,
 *   any function that takes a `Bird` and expects it to fly will CRASH!
 * 
 * ----------------------------------------------------------------------------
 * 🛑 WHY IS THIS CODE "BAD"? (THE ANTI-PATTERN)
 * Look at the code below:
 * 1. `Bird` has `fly()`.
 * 2. `Sparrow` can fly -> Works fine.
 * 3. `Penguin` CANNOT fly -> Throws `std::logic_error`!
 * 4. A function `makeBirdFly(Bird& b)` crashes when given a Penguin!
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

// Base class representing a Bird
class Bird {
public:
    virtual ~Bird() = default;

    // The base class promises that ALL birds can fly!
    virtual void fly() const {
        std::cout << "Bird is flying in the sky!" << std::endl;
    }
};

// Sparrow is a flying bird -> perfectly fine
class Sparrow : public Bird {
public:
    void fly() const override {
        std::cout << "Sparrow is flapping its wings and flying high!" << std::endl;
    }
};

// ❌ BAD SUBCLASS: Penguin violates the contract of Bird!
// Biologically it's a bird, but behavioral subtyping is BROKEN!
class Penguin : public Bird {
public:
    void fly() const override {
        // BREAKS LSP: Callers expect fly() to work, but it throws an error!
        throw std::logic_error("Penguins cannot fly! They can only swim!");
    }
};

// Client function that takes any generic Bird and makes it fly
void letBirdFly(const Bird& bird) {
    // The programmer who wrote this function assumed ALL birds can fly!
    bird.fly(); 
}

int main() {
    std::cout << "=== Running LSP Bad Example ===" << std::endl;

    Sparrow sparrow;
    std::cout << "Testing Sparrow:" << std::endl;
    letBirdFly(sparrow); // Works!

    Penguin penguin;
    std::cout << "\nTesting Penguin:" << std::endl;
    try {
        letBirdFly(penguin); // 💥 CRASHES! Violates LSP!
    } catch (const std::exception& e) {
        std::cerr << "CRITICAL ERROR: " << e.what() << std::endl;
        std::cerr << "The program crashed because Penguin is not a proper substitute for Bird!" << std::endl;
    }

    return 0;
}
