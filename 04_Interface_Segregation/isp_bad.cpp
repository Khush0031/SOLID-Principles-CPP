/**
 * ============================================================================
 * PRINCIPLE 4: INTERFACE SEGREGATION PRINCIPLE (ISP) - THE BAD WAY
 * ============================================================================
 * 
 * 📖 WHAT IS THE THEORY?
 * The Interface Segregation Principle says:
 * "Clients should not be forced to depend upon interfaces (or methods) they do not use."
 * 
 * In simple English:
 * Instead of creating ONE giant, bloated interface that does 50 things ("Fat Interface"),
 * create smaller, specialized interfaces with only 1 or 2 related methods.
 * 
 * 🖨️ REAL-LIFE ANALOGY: The Supermarket Cashier Printer (from Bhawna Gurjar's article)
 * - Think of a tiny receipt printer at a grocery store checkout.
 * - It has only ONE job: print black-and-white paper receipts.
 * - Imagine if the manufacturer gave it a software driver that forces it to support:
 *   - Printing
 *   - Color Scanning
 *   - Sending Faxes
 *   - Automatic Stapling
 * - The tiny printer can't scan, can't fax, and can't staple! It has to leave those methods
 *   empty or throw errors.
 * 
 * ----------------------------------------------------------------------------
 * 🛑 WHY IS THIS CODE "BAD"? (THE ANTI-PATTERN)
 * Below, `IMultiFunctionDevice` is a "Fat Interface".
 * It forces `SimplePrinter` to implement `scan()` and `fax()`, which it physically cannot do!
 */

#include <iostream>
#include <string>
#include <stdexcept>

// ❌ FAT INTERFACE: Bundles too many unrelated features together!
class IMultiFunctionDevice {
public:
    virtual ~IMultiFunctionDevice() = default;

    virtual void print(const std::string& document) = 0;
    virtual void scan() = 0;
    virtual void fax(const std::string& number) = 0;
};

// ❌ BAD IMPLEMENTATION: A simple budget printer forced to implement scan & fax!
class SimplePrinter : public IMultiFunctionDevice {
public:
    void print(const std::string& document) override {
        std::cout << "[SimplePrinter] Printing: " << document << std::endl;
    }

    // FORCED DUMMY IMPLEMENTATIONS:
    void scan() override {
        // Simple printer has no scanner! What can it do?
        // Either do nothing (silent bug) or throw an exception!
        throw std::logic_error("Hardware Error: SimplePrinter cannot scan!");
    }

    void fax([[maybe_unused]] const std::string& number) override {
        throw std::logic_error("Hardware Error: SimplePrinter cannot fax!");
    }
};

int main() {
    std::cout << "=== Running ISP Bad Example ===" << std::endl;

    SimplePrinter printer;
    printer.print("Daily Sales Report.pdf");

    // Because printer implements IMultiFunctionDevice, someone might accidentally call scan:
    try {
        std::cout << "Attempting to scan with SimplePrinter..." << std::endl;
        printer.scan(); // 💥 CRASH!
    } catch (const std::exception& e) {
        std::cerr << "CRASH: " << e.what() << std::endl;
        std::cerr << "Violates ISP: SimplePrinter was forced to implement methods it cannot use!" << std::endl;
    }

    return 0;
}
