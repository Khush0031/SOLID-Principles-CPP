/**
 * ============================================================================
 * PRINCIPLE 3: LISKOV SUBSTITUTION PRINCIPLE (LSP) - THE GOOD WAY
 * ============================================================================
 * 
 * 📖 WHAT IS THE SOLUTION?
 * Do not put behavior in a base class that not all derived classes can support!
 * 
 * 1. Base class `Bird`:
 *    - Only contains features that ALL birds share (e.g., `eat()`, `makeSound()`).
 * 
 * 2. Separate Sub-Hierarchy for flying birds:
 *    - Create `FlyingBird : public Bird` with `fly()`.
 *    - `Sparrow` and `Eagle` inherit from `FlyingBird`.
 * 
 * 3. Flightless birds inherit directly from `Bird`:
 *    - `Penguin` inherits from `Bird` (and can have its own `swim()` method).
 * 
 * 💡 WHY IS THIS SAFER?
 * - If a function needs something that can fly:
 *     `void letBirdFly(const FlyingBird& bird);`
 * - You CAN pass a `Sparrow` or `Eagle`.
 * - If you try to pass a `Penguin`, the C++ compiler rejects it with a **compile-time error**!
 * - Compile-time errors are 1000x better than runtime production crashes!
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// ============================================================================
// 1. BASE CLASS: Only things that ALL birds truly do!
// ============================================================================
class Bird {
public:
    virtual ~Bird() = default;

    // All birds eat food
    virtual void eat() const {
        std::cout << "Bird is eating seeds/fish." << std::endl;
    }
};

// ============================================================================
// 2. FLYING BIRD INTERFACE / CLASS: For birds that actually fly!
// ============================================================================
class FlyingBird : public Bird {
public:
    // Only birds that can actually fly have this method!
    virtual void fly() const = 0;
};

// ============================================================================
// 3. CONCRETE BIRDS
// ============================================================================

// Sparrow is a FlyingBird
class Sparrow : public FlyingBird {
public:
    void fly() const override {
        std::cout << "Sparrow is flying smoothly in the air." << std::endl;
    }

    void eat() const override {
        std::cout << "Sparrow is pecking at grains." << std::endl;
    }
};

// Penguin is a Bird, but NOT a FlyingBird!
class Penguin : public Bird {
public:
    void eat() const override {
        std::cout << "Penguin is eating fresh krill and fish." << std::endl;
    }

    // Penguins have their own special ability: swimming!
    void swim() const {
        std::cout << "Penguin is gliding underwater at high speed!" << std::endl;
    }
};

// ============================================================================
// 4. CLIENT FUNCTIONS RESPECTING CONTRACTS
// ============================================================================

// This function ONLY accepts birds that can genuinely fly!
void makeItFly(const FlyingBird& flyingBird) {
    flyingBird.fly();
}

// This function accepts ANY bird
void feedBird(const Bird& bird) {
    bird.eat();
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main() {
    std::cout << "=== Running LSP Good Example ===" << std::endl;

    Sparrow sparrow;
    Penguin penguin;

    std::cout << "1. Feeding all birds (LSP fully satisfied):" << std::endl;
    feedBird(sparrow); // Works!
    feedBird(penguin); // Works!

    std::cout << "\n2. Flying only birds that can fly:" << std::endl;
    makeItFly(sparrow); // Works!

    // UNCOMMENTING THE LINE BELOW WILL FAIL AT COMPILE-TIME:
    // makeItFly(penguin);
    // Compiler error: cannot convert 'Penguin' to 'const FlyingBird&'
    // The bug is caught by the compiler BEFORE your code ever ships!

    std::cout << "\n3. Calling Penguin's natural ability:" << std::endl;
    penguin.swim();

    return 0;
}
