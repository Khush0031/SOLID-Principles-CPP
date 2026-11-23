/**
 * ============================================================================
 * PRINCIPLE 5: DEPENDENCY INVERSION PRINCIPLE (DIP) - THE BAD WAY
 * ============================================================================
 * 
 * 📖 WHAT IS THE THEORY?
 * The Dependency Inversion Principle says:
 * "High-level modules should NOT depend on low-level modules. Both should depend on abstractions."
 * 
 * 🔍 WHAT DOES "HIGH-LEVEL" AND "LOW-LEVEL" MEAN?
 * - High-Level Module: The core business logic (e.g., `UserService`, `OrderService`, `Car`).
 *   This is what your application actually *does* for the user.
 * - Low-Level Module: The technical details (e.g., `MySQLDatabase`, `PetrolEngine`, `DiskWriter`).
 *   These are the tools used behind the scenes.
 * 
 * 🔌 REAL-LIFE ANALOGY: The Light Switch & The Lightbulb
 * - A wall light switch (high-level) should not be hard-soldered to a specific 60W Incandescent bulb (low-level).
 * - If the bulb burns out and you want to replace it with an LED bulb, you shouldn't have to
 *   tear open the wall and rewire the light switch!
 * - Both the switch and the bulb should depend on an abstraction: the bulb socket (e.g. E27 base).
 * 
 * ----------------------------------------------------------------------------
 * 🛑 WHY IS THIS CODE "BAD"? (THE ANTI-PATTERN)
 * Below, `UserService` (high-level) directly instantiates `MySQLDatabase` (low-level).
 * 
 * 💥 WHAT GOES WRONG?
 * 1. Tight Coupling: `UserService` is married to MySQL. If your company switches to
 *    PostgreSQL or MongoDB, you MUST rewrite the `UserService` class!
 * 2. Untestable: How do you test `UserService` on your laptop without installing MySQL? You can't!
 */

#include <iostream>
#include <string>

// LOW-LEVEL CLASS: Specific MySQL Database Driver
class MySQLDatabase {
public:
    void save(const std::string& data) {
        std::cout << "[MySQL Database] Executing SQL: INSERT INTO users VALUES ('" << data << "');" << std::endl;
    }
};

// ❌ HIGH-LEVEL CLASS: Directly tied to the low-level MySQLDatabase!
class UserService {
private:
    MySQLDatabase database_; // ❌ TIGHT COUPLING! Directly hardcoding MySQL!

public:
    void registerUser(const std::string& username) {
        std::cout << "[UserService] Registering new user: " << username << std::endl;

        // Directly using MySQL
        database_.save(username);
    }
};

int main() {
    std::cout << "=== Running DIP Bad Example ===" << std::endl;

    UserService service;
    service.registerUser("Alice");

    // PROBLEM:
    // What if management decides to switch to PostgreSQL tomorrow?
    // We would have to open UserService.h and UserService.cpp and change everything!
    return 0;
}
