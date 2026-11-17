/**
 * ============================================================================
 * PRINCIPLE 1: SINGLE RESPONSIBILITY PRINCIPLE (SRP) - THE BAD WAY
 * ============================================================================
 * 
 * 📖 WHAT IS THE THEORY?
 * The Single Responsibility Principle says:
 * "A class should have only ONE reason to change."
 * 
 * In simple English:
 * A class should have ONE single job.
 * Think of a person in a restaurant:
 * - A Chef should only cook food.
 * - If you force the Chef to cook food, clean the toilets, manage the accounting,
 *   and serve tables, what happens? The chef gets overwhelmed, makes mistakes,
 *   burns the food, and if accounting rules change, the chef has to stop cooking!
 * 
 * ----------------------------------------------------------------------------
 * 🛑 WHY IS THIS CODE "BAD"? (THE ANTI-PATTERN)
 * Look at the class `Invoice` below. It is doing THREE completely different jobs:
 * 1. Storing invoice data & calculating totals (Business/Accounting logic).
 * 2. Printing the invoice to the screen / paper (Presentation/UI logic).
 * 3. Saving the invoice to a file / database (Storage/Persistence logic).
 * 
 * 💥 WHAT GOES WRONG IN THE REAL WORLD?
 * - If management asks to change how the invoice is displayed (HTML instead of text),
 *   you have to edit the `Invoice` class.
 * - If the database team changes the file format from TXT to JSON, you have to
 *   edit the `Invoice` class.
 * - If tax calculation rules change, you have to edit the `Invoice` class.
 * That means this one class has THREE different reasons to change!
 */

#include <iostream>
#include <string>
#include <vector>

// A simple structure to hold item details: name and price
struct Item {
    std::string name;
    double price;
};

// ❌ BAD CLASS: Doing too many jobs at once (Violates SRP)
class Invoice {
private:
    std::vector<Item> items_;
    double taxRate_;

public:
    // Constructor: initializes the tax rate (e.g., 0.10 for 10% tax)
    Invoice(double taxRate) : taxRate_(taxRate) {}

    // Adds an item to the invoice
    void addItem(const std::string& name, double price) {
        items_.push_back({name, price});
    }

    // JOB 1: Calculation Logic (Accounting)
    double calculateTotal() const {
        double subtotal = 0.0;
        for (const auto& item : items_) {
            subtotal += item.price;
        }
        return subtotal + (subtotal * taxRate_);
    }

    // JOB 2: Printing / Display Logic (Presentation)
    // If the boss says "make it look pretty with borders", we must change this class!
    void printInvoice() const {
        std::cout << "\n--- INVOICE ---" << std::endl;
        for (const auto& item : items_) {
            std::cout << item.name << " : $" << item.price << std::endl;
        }
        std::cout << "Tax Rate: " << (taxRate_ * 100) << "%" << std::endl;
        std::cout << "Final Total: $" << calculateTotal() << std::endl;
        std::cout << "---------------" << std::endl;
    }

    // JOB 3: File Saving / Persistence Logic (Storage)
    // If we switch from saving to a text file to saving in MySQL, we must change this class!
    void saveToFile(const std::string& filename) const {
        std::cout << "[File System] Saving invoice to file: " << filename << std::endl;
        // In real code: std::ofstream file(filename); file << ...
    }
};

int main() {
    std::cout << "=== Running SRP Bad Example ===" << std::endl;

    // Create an invoice with 10% tax
    Invoice invoice(0.10);
    invoice.addItem("Laptop", 1000.0);
    invoice.addItem("Mouse", 50.0);

    // One single object is calculating, printing, and saving!
    invoice.printInvoice();
    invoice.saveToFile("invoice_01.txt");

    return 0;
}
