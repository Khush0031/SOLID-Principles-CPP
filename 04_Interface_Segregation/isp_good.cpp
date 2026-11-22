/**
 * ============================================================================
 * PRINCIPLE 4: INTERFACE SEGREGATION PRINCIPLE (ISP) - THE GOOD WAY
 * ============================================================================
 * 
 * 📖 WHAT IS THE SOLUTION?
 * Break down the fat, bloated interface into small, focused, role-based interfaces!
 * 
 * 1. `IPrinter`: Contains only `print()`
 * 2. `IScanner`: Contains only `scan()`
 * 3. `IFax`: Contains only `fax()`
 * 
 * 💡 HOW DOES C++ HANDLE THIS?
 * C++ supports **Multiple Inheritance of Interfaces**:
 * - `SimplePrinter` only inherits from `IPrinter`. (Zero wasted methods!)
 * - `OfficeAllInOne` inherits from `IPrinter, IScanner, IFax`. (Supports all three!)
 * 
 * 💡 BENEFITS FOR BEGINNERS:
 * - A client that only prints (`void doPrinting(IPrinter& p)`) cannot accidentally
 *   call `scan()` or `fax()`.
 * - No classes are forced to write empty dummy functions or throw errors.
 * - Clean, modular, and easy to maintain.
 */

#include <iostream>
#include <string>

// ============================================================================
// 1. SMALL, SEGREGATED ROLE INTERFACES
// ============================================================================

// Interface for anything that can print
class IPrinter {
public:
    virtual ~IPrinter() = default;
    virtual void print(const std::string& document) = 0;
};

// Interface for anything that can scan
class IScanner {
public:
    virtual ~IScanner() = default;
    virtual void scan(const std::string& document) = 0;
};

// Interface for anything that can fax
class IFax {
public:
    virtual ~IFax() = default;
    virtual void fax(const std::string& document, const std::string& number) = 0;
};

// ============================================================================
// 2. CONCRETE CLASSES IMPLEMENTING ONLY WHAT THEY NEED
// ============================================================================

// Device A: Budget Printer (Only implements IPrinter)
class SimplePrinter : public IPrinter {
public:
    void print(const std::string& document) override {
        std::cout << "[SimplePrinter] Printing: " << document << std::endl;
    }
};

// Device B: High-End Office All-In-One (Implements IPrinter AND IScanner)
class OfficeMultiMachine : public IPrinter, public IScanner {
public:
    void print(const std::string& document) override {
        std::cout << "[Office Machine] High-speed laser printing: " << document << std::endl;
    }

    void scan(const std::string& document) override {
        std::cout << "[Office Machine] Scanning document to PDF: " << document << std::endl;
    }
};

// ============================================================================
// 3. CLIENT FUNCTIONS THAT ASK ONLY FOR WHAT THEY NEED
// ============================================================================

// This function only needs to print something
void printDailyReport(IPrinter& printer, const std::string& reportName) {
    std::cout << "\n[Report Task] Starting print job..." << std::endl;
    printer.print(reportName);
}

// This function only needs to scan something
void digitizePaperwork(IScanner& scanner, const std::string& docName) {
    std::cout << "\n[Archival Task] Starting scan job..." << std::endl;
    scanner.scan(docName);
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main() {
    std::cout << "=== Running ISP Good Example ===" << std::endl;

    SimplePrinter basicPrinter;
    OfficeMultiMachine officeMachine;

    // Both machines can print:
    printDailyReport(basicPrinter, "Employee_List.txt");
    printDailyReport(officeMachine, "Quarterly_Financials.pdf");

    // Only the office machine can scan:
    digitizePaperwork(officeMachine, "Signed_Contract.pdf");

    // UNCOMMENTING THE LINE BELOW WILL NOT COMPILE:
    // digitizePaperwork(basicPrinter, "Signed_Contract.pdf");
    // -> Compiler error: cannot convert 'SimplePrinter' to 'IScanner&'
    // Impossible to trigger runtime crashes because the compiler enforces the contract!

    return 0;
}
