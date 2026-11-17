/**
 * ============================================================================
 * PRINCIPLE 1: SINGLE RESPONSIBILITY PRINCIPLE (SRP) - THE GOOD WAY
 * ============================================================================
 * 
 * 📖 WHAT IS THE SOLUTION?
 * We take the "overworked" class and divide its responsibilities among
 * specialized classes. Each class now has ONE single job and ONE single
 * reason to change:
 * 
 * 1. `Invoice`: ONLY holds items and calculates total.
 *    -> Reason to change: Business/calculation rules change.
 * 
 * 2. `InvoicePrinter`: ONLY formats and displays the invoice.
 *    -> Reason to change: UI/display styling changes.
 * 
 * 3. `InvoiceSaver`: ONLY writes invoice data to storage.
 *    -> Reason to change: File format or database technology changes.
 * 
 * 💡 BENEFITS FOR BEGINNERS:
 * - Easy to read: Each class is tiny (10-20 lines).
 * - Easy to test: You can test `calculateTotal()` without touching any printers or files!
 * - Reusable: You can print the same invoice to Console, or to HTML, or to PDF
 *   by simply creating a new printer class, without breaking the `Invoice` class!
 */

#include <iostream>
#include <string>
#include <vector>

// Simple data structure for an item
struct Item {
    std::string name;
    double price;
};

// ============================================================================
// CLASS 1: `Invoice`
// RESPONSIBILITY: Only manage invoice items and calculate financial totals.
// ============================================================================
class Invoice {
private:
    std::vector<Item> items_;
    double taxRate_;

public:
    explicit Invoice(double taxRate) : taxRate_(taxRate) {}

    void addItem(const std::string& name, double price) {
        items_.push_back({name, price});
    }

    // Calculation logic
    double calculateTotal() const {
        double subtotal = 0.0;
        for (const auto& item : items_) {
            subtotal += item.price;
        }
        return subtotal + (subtotal * taxRate_);
    }

    // Getters so other classes can read data without modifying it
    const std::vector<Item>& getItems() const { return items_; }
    double getTaxRate() const { return taxRate_; }
};

// ============================================================================
// CLASS 2: `InvoicePrinter`
// RESPONSIBILITY: Only handle display and formatting.
// ============================================================================
class InvoicePrinter {
public:
    // Takes a reference to an Invoice (`const Invoice&`) to read its data safely
    void printToConsole(const Invoice& invoice) const {
        std::cout << "\n===============================" << std::endl;
        std::cout << "         OFFICIAL INVOICE      " << std::endl;
        std::cout << "===============================" << std::endl;

        for (const auto& item : invoice.getItems()) {
            std::cout << " - " << item.name << ": $" << item.price << std::endl;
        }

        std::cout << "-------------------------------" << std::endl;
        std::cout << "Tax: " << (invoice.getTaxRate() * 100) << "%" << std::endl;
        std::cout << "TOTAL: $" << invoice.calculateTotal() << std::endl;
        std::cout << "===============================" << std::endl;
    }
};

// ============================================================================
// CLASS 3: `InvoiceSaver`
// RESPONSIBILITY: Only handle saving to disk or database.
// ============================================================================
class InvoiceSaver {
public:
    void saveToFile(const Invoice& invoice, const std::string& filename) const {
        std::cout << "[Storage] Saving Invoice (Total: $" << invoice.calculateTotal() 
                  << ") to file: " << filename << std::endl;
        // In real code, you would write items to a file here
    }
};

// ============================================================================
// MAIN FUNCTION: Demonstrating how clean and modular everything is
// ============================================================================
int main() {
    std::cout << "=== Running SRP Good Example ===" << std::endl;

    // 1. Create the Invoice (Business Data)
    Invoice myInvoice(0.10); // 10% tax
    myInvoice.addItem("Mechanical Keyboard", 120.0);
    myInvoice.addItem("Wireless Mouse", 40.0);

    // 2. Print it using the Printer (Presentation)
    InvoicePrinter printer;
    printer.printToConsole(myInvoice);

    // 3. Save it using the Saver (Persistence)
    InvoiceSaver saver;
    saver.saveToFile(myInvoice, "my_order.txt");

    return 0;
}
