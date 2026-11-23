/**
 * ============================================================================
 * PRINCIPLE 5: DEPENDENCY INVERSION PRINCIPLE (DIP) - THE GOOD WAY
 * ============================================================================
 * 
 * 📖 WHAT IS THE SOLUTION?
 * Introduce an Abstraction (an abstract base class / interface) in the middle!
 * 
 * 1. Create an abstract interface: `IDatabase`.
 *    - It defines a pure virtual function: `virtual void save(const std::string& data) = 0;`
 * 
 * 2. High-level class (`UserService`) depends on `IDatabase` (the abstraction).
 *    - It doesn't care whether the database is MySQL, PostgreSQL, or a simple text file!
 * 
 * 3. Low-level classes (`MySQLDatabase`, `PostgreSQLDatabase`) implement `IDatabase`.
 * 
 * 4. DEPENDENCY INJECTION (DI):
 *    - Instead of `UserService` creating `new MySQLDatabase()`, we PASS (inject) the
 *      database into the constructor of `UserService`!
 * 
 * 💡 WHY IS THIS A SUPERPOWER?
 * - Switching from MySQL to PostgreSQL takes ONE line in `main()`!
 * - Writing unit tests is effortless: you can create a `MockDatabase` that runs in memory
 *   in 0.001 milliseconds without installing or running any database software!
 */

#include <iostream>
#include <string>
#include <memory>
#include <vector>

// ============================================================================
// 1. THE ABSTRACTION (INTERFACE)
// ============================================================================
class IDatabase {
public:
    virtual ~IDatabase() = default;
    virtual void save(const std::string& data) = 0;
};

// ============================================================================
// 2. CONCRETE IMPLEMENTATIONS (LOW-LEVEL MODULES)
// ============================================================================

// Low-level option A: MySQL
class MySQLDatabase : public IDatabase {
public:
    void save(const std::string& data) override {
        std::cout << "  [MySQL] Executing: INSERT INTO users VALUES ('" << data << "');" << std::endl;
    }
};

// Low-level option B: PostgreSQL
class PostgreSQLDatabase : public IDatabase {
public:
    void save(const std::string& data) override {
        std::cout << "  [PostgreSQL] Executing: INSERT INTO users VALUES ('" << data << "') RETURNING id;" << std::endl;
    }
};

// Low-level option C: In-Memory Fake Database for FAST UNIT TESTING!
class MockDatabase : public IDatabase {
public:
    std::vector<std::string> savedRecords;

    void save(const std::string& data) override {
        savedRecords.push_back(data);
        std::cout << "  [Mock DB] Saved in RAM! No server needed. Records count: " 
                  << savedRecords.size() << std::endl;
    }
};

// ============================================================================
// 3. HIGH-LEVEL MODULE: UserService
// ============================================================================
class UserService {
private:
    // Depends on the ABSTRACTION (IDatabase), NOT on MySQL or PostgreSQL!
    IDatabase& database_;

public:
    // CONSTRUCTOR DEPENDENCY INJECTION:
    // The caller gives us the database we should use.
    explicit UserService(IDatabase& db) : database_(db) {}

    void registerUser(const std::string& username) {
        std::cout << "[UserService] Processing user signup: " << username << std::endl;
        
        // Business logic here (e.g. validate username, hash password...)
        
        // Save using the injected database:
        database_.save(username);
    }
};

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main() {
    std::cout << "=== Running DIP Good Example ===" << std::endl;

    // SCENARIO 1: Testing locally with Mock DB (Super fast, offline)
    std::cout << "\n--- 1. Testing with In-Memory Mock Database ---" << std::endl;
    MockDatabase testDb;
    UserService testService(testDb);
    testService.registerUser("test_user_bob");

    // SCENARIO 2: Production running with MySQL
    std::cout << "\n--- 2. Production Deployment with MySQL ---" << std::endl;
    MySQLDatabase prodMySqlDb;
    UserService mySqlService(prodMySqlDb);
    mySqlService.registerUser("alice_enterprise");

    // SCENARIO 3: Switching to PostgreSQL without touching UserService!
    std::cout << "\n--- 3. Smooth Migration to PostgreSQL (Zero edits to UserService!) ---" << std::endl;
    PostgreSQLDatabase prodPostgreSqlDb;
    UserService postgresService(prodPostgreSqlDb);
    postgresService.registerUser("charlie_postgres");

    return 0;
}
