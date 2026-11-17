# The Complete Notes For SOLID Principles in CPP/C++.
### Understanding SOLID Principles in C++ is crucial for writing clean, maintainable, and scalable code. SOLID is an acronym that stands for five design principles intended to make software designs more understandable, flexible, and maintainable.
### Understand Every Principles from Scratch with Real-World Analogies & Cleand Code

> **References & Inspirations:**
> - *SOLID principles: implementation and examples in C++* by Oleksandra Shershen
> - *SOLID Principles in C++ with Real Life Examples* by Bhawna Gurjar

---

## 📚 Table of Contents
1. [Introduction: Why Do We Need SOLID Principles?](#1-introduction-why-do-we-need-solid-principles)
2. [C++ Important Concepts Must Know Before Learning SOLID Principles](#2-c-important-concepts-must-know-before-learning-solid-principles)
   - [What is an Abstract Class / Interface?](#what-is-an-interface)
   - [What is `virtual` and `override`?](#what-is-virtual)
   - [Why do we need `virtual ~Base() = default;`?](#why-virtual-destructor)
   - [What is Object Slicing and Why do we use Reference (`&`)?](#what-is-slicing)
   - [What is `std::unique_ptr`?](#what-is-unique-ptr)
3. [S: Single Responsibility Principle (SRP)](#3-s-single-responsibility-principle-srp)
4. [O: Open-CLosed Principle (OCP)](#4-o-open-closed-principle-ocp)
5. [L: Liskov Substitution Principle (LSP)](#5-l-liskov-substitution-principle-lsp)
6. [I: Interface Segregation Principle (ISP)](#6-i-interface-segregation-principle-isp)
7. [D: Dependency Inversion Principle (DIP)](#7-d-dependency-inversion-principle-dip)
8. [Quick Reference Cheat Sheet](#8-quick-reference-cheat-sheet)
---

## 1. Introduction: Why Do We Need SOLID Principles?

When non-experienced developers start programming, they usually write all their code inside a single fucntion or class. It works! But at the software grows:
- Adding one new feature breaks three unrelated fearures.
- Fixing a bug causes another new bugs.
- Nobody can understand which line of code does what.

This is called  **spaghetti code**. or **software rot**. 

In the early 2000s, software engineer Robert C. Martin ("Uncle Bob") compiled **5 foundational principles** of good Object-Oriented Design. The acronym **SOLID** stands for:

```
+------------------------------------------------------------------------+
|                               S . O . L . I . D                        |
+------------------------------------------------------------------------+
|  S  |  Single Responsibility Principle                                 |
|  O  |  Open-Closed Principle                                           |
|  L  |  Liskov Substitution Principle                                   |
|  I  |  Interface Segregation Principle                                 |
|  D  |  Dependency Inversion Principle                                  |
+------------------------------------------------------------------------+
```


These principles teach you how to write code that is:
- **Easy to understand** by any teammate.
- **Easy to extend** when your manager asks for new features.
- **Easy to test** without needing live databases or network.

---

## 2. C++ Important Concepts Must Know Before Learning SOLID Principles

Before learning SOLID, here are the essential C++ features you will see in professional code.

<a id="what-is-an-interface"></a>
### 1. What is an Interface / Abstract Class?
In C++, an "Interface" is an abstract class that has **no implementation**—it only defines a list of actions (contracts) that child classes must fulfill.
We write pure virtual functions using `= 0`:
```cpp
class Animal {
public:
    virtual ~Animal() = default;
    virtual void makeSound() const = 0; // Child classes MUST implement this!
};
```

<a id="what-is-virtual"></a>
### 2. What is `virtual` and `override`?
- `virtual`: Tells the C++ compiler: *"When someone calls this method through a pointer or reference, do not call the base version—look up and call the child class version!"* (This is called **Polymorphism**).
- `override`: A safety keyword on child classes. It tells the compiler: *"Please verify that I spelled this function correctly and that it really exists in the base class."*

<a id="why-virtual-destructor"></a>
### 3. Why do we need `virtual ~Base() = default;`?
When you delete an object of a derived class through a pointer to the base class:
```cpp
Base* obj = new Derived();
delete obj;
```
If the base class destructor is NOT `virtual`, C++ will only run `~Base()` and will **skip** `~Derived()`. This causes memory leaks and dangling resources! Making it `virtual` ensures the derived destructor runs first.

<a id="what-is-slicing"></a>
### 4. What is Object Slicing and Why do we pass by Reference (`&`)?
If you pass a polymorphic object **by value**:
```cpp
void printShape(Shape s); // BAD: Copies only the Shape part! Slices off derived data!
```
The compiler "slices off" everything specific to the derived class (`Circle` or `Rectangle`), breaking virtual function calls.
**The Golden Rule**: Always pass polymorphic objects by reference (`const Shape&`) or pointer (`Shape*`).

<a id="what-is-unique-ptr"></a>
### 5. What is `std::unique_ptr`?
A smart pointer from `<memory>`. It owns a heap object and automatically deletes it when it goes out of scope. You never need to write `delete` manually!
```cpp
std::unique_ptr<Shape> myShape = std::make_unique<Rectangle>(10, 5);
// Cleaned up automatically! No memory leaks!
```

---

## 3. S: Single Responsibility Principle (SRP)

> *"A class should have one, and only one, reason to change."*

### 🍽️ Real-Life Analogy: The Restaurant Chef
Imagine you own a restaurant. You hire a talented Chef.
- If you ask the Chef to **cook meals**, **wash the dishes**, **manage the financial accounts**, and **serve customers**, what happens?
- The chef gets burnt out, burns the food, and makes mistakes in the accounting ledger.
- If tax laws change, the chef has to stop cooking to study tax accounting!
- **The Solution**: The Chef cooks, the Dishwasher cleans, and the Accountant does the taxes. Each person has **ONE responsibility**.

---

### ❌ The Bad Code (One Class Doing Everything)
Look at [`01_Single_Responsibility/srp_bad.cpp`](./01_Single_Responsibility/srp_bad.cpp):
The class `Invoice` is doing three completely separate jobs:
1. Managing invoice items and calculating totals.
2. Formatting and printing to the screen.
3. Writing the invoice to a text file.

```cpp
// ❌ BAD: One class has 3 different reasons to change!
class Invoice {
    std::vector<Item> items_;
    double taxRate_;
public:
    double calculateTotal() const { /* ... */ } // Job 1: Financial math
    void printInvoice() const { /* ... */ }     // Job 2: UI Presentation
    void saveToFile(string filename) { /* ... */}// Job 3: Storage/File I/O
};
```
#### Why this fails:
- If your manager says *"change the invoice format to HTML"*, you have to modify `Invoice`.
- If your DBA says *"save to database instead of text file"*, you have to modify `Invoice`.
- If tax rules change, you have to modify `Invoice`.

---

### ✓ The Good Code (Separation of Concerns)
Look at [`01_Single_Responsibility/srp_good.cpp`](./01_Single_Responsibility/srp_good.cpp):
We split the responsibilities into 3 small, focused classes:

```cpp
// 1. ONLY manages data and calculations
class Invoice {
    std::vector<Item> items_;
    double taxRate_;
public:
    double calculateTotal() const;
    const std::vector<Item>& getItems() const;
};

// 2. ONLY manages printing / presentation
class InvoicePrinter {
public:
    void printToConsole(const Invoice& invoice) const {
        // Formats and prints to screen
    }
};

// 3. ONLY manages saving to files or databases
class InvoiceSaver {
public:
    void saveToFile(const Invoice& invoice, const std::string& filename) const {
        // Writes data to disk
    }
};
```

#### Why this is better:
- You can change how invoices look without touching calculation code.
- You can test `calculateTotal()` without creating any files on disk.
- Each class is simple, readable, and under 25 lines of code!

---

## 4. O: Open-Closed Principle (OCP)

> *"Software entities should be open for extension, but closed for modification."*

### 🔌 Real-Life Analogy: The Wall Socket
Look at an electrical wall socket in your room:
- When you buy a brand-new smartphone or gaming console, do you cut open the wall and rewire your house? **No!**
- The wall socket is **CLOSED for modification** (it never changes).
- The system is **OPEN for extension** (any new gadget with the right plug can plug right in).

---

### ❌ The Bad Code (Massive `switch` / `if-else` Statements)
Look at [`02_Open_Closed/ocp_bad.cpp`](./02_Open_Closed/ocp_bad.cpp):
`AreaCalculator` checks an `enum` using a `switch` statement:

```cpp
enum class ShapeType { Rectangle, Circle };

class AreaCalculator {
public:
    double calculateArea(const Shape& shape) const {
        switch (shape.type) {
            case ShapeType::Rectangle: return shape.width * shape.height;
            case ShapeType::Circle:    return 3.14159 * shape.radius * shape.radius;
            // What if we want to add Triangle tomorrow?
            // We HAVE to modify this file and edit this switch statement!
        }
    }
};
```
#### Why this fails:
Every time you introduce a new shape (Triangle, Hexagon, Pentagon), you must open, modify, and re-test `AreaCalculator`. This breaks the rule: **Closed for modification**.

---

### ✓ The Good Code (Polymorphism with Abstract Base Class)
Look at [`02_Open_Closed/ocp_good.cpp`](./02_Open_Closed/ocp_good.cpp):

```cpp
// 1. The Contract (Abstract Base Class)
class Shape {
public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0; // Pure virtual function
};

// 2. Concrete Shapes
class Rectangle : public Shape {
    double width_, height_;
public:
    Rectangle(double w, double h) : width_(w), height_(h) {}
    double getArea() const override { return width_ * height_; }
};

class Circle : public Shape {
    double radius_;
public:
    Circle(double r) : radius_(r) {}
    double getArea() const override { return 3.14159 * radius_ * radius_; }
};

// 3. Calculator is CLOSED for modification!
class AreaCalculator {
public:
    double calculateTotalArea(const std::vector<std::unique_ptr<Shape>>& shapes) const {
        double total = 0.0;
        for (const auto& shape : shapes) {
            total += shape->getArea(); // Polymorphism in action!
        }
        return total;
    }
};

// 4. NEW EXTENSION: Adding a Triangle requires ZERO edits to AreaCalculator!
class Triangle : public Shape {
    double base_, height_;
public:
    Triangle(double b, double h) : base_(b), height_(h) {}
    double getArea() const override { return 0.5 * base_ * height_; }
};
```

#### Why this is better:
`AreaCalculator` works with *any* shape that inherits from `Shape`. You can add 100 new shapes without changing a single line of the calculator!

---

## 5. L: Liskov Substitution Principle (LSP)

> *"Derived classes must be substitutable for their base classes without breaking the program."*

### 🐧 Real-Life Analogy: The Flightless Penguin
Biologically, a **Penguin** is a bird.
- If a programmer designs a base class `Bird` with a method `virtual void fly()`, what happens when they create a `Penguin` class?
- A penguin cannot fly! If the `Penguin` class throws an error inside `fly()`, any function expecting a `Bird` to fly will **crash the entire program**!
- In software, a child class must NOT promise things it cannot do.

---

### ❌ The Bad Code (Subclass Throws Runtime Errors)
Look at [`03_Liskov_Substitution/lsp_bad.cpp`](./03_Liskov_Substitution/lsp_bad.cpp):

```cpp
class Bird {
public:
    virtual ~Bird() = default;
    virtual void fly() const {
        std::cout << "Flying high!" << std::endl;
    }
};

class Sparrow : public Bird { /* Flies fine */ };

// ❌ BAD: Penguin violates the contract of Bird!
class Penguin : public Bird {
public:
    void fly() const override {
        throw std::logic_error("Penguins cannot fly!"); // 💥 CRASH!
    }
};

void letBirdFly(const Bird& bird) {
    bird.fly(); // Will crash if passed a Penguin!
}
```

---

### ✓ The Good Code (Proper Behavioral Hierarchy)
Look at [`03_Liskov_Substitution/lsp_good.cpp`](./03_Liskov_Substitution/lsp_good.cpp):
Only put things in `Bird` that **ALL** birds do (like `eat()`). Create a separate `FlyingBird` class for birds that actually fly:

```cpp
// 1. Base class: Things all birds do
class Bird {
public:
    virtual ~Bird() = default;
    virtual void eat() const { std::cout << "Eating food..." << std::endl; }
};

// 2. Only for birds that can truly fly
class FlyingBird : public Bird {
public:
    virtual void fly() const = 0;
};

// 3. Sparrow can fly
class Sparrow : public FlyingBird {
public:
    void fly() const override { std::cout << "Sparrow is flying!" << std::endl; }
};

// 4. Penguin is a Bird, but NOT a FlyingBird!
class Penguin : public Bird {
public:
    void swim() const { std::cout << "Penguin is swimming!" << std::endl; }
};

// This function ONLY accepts birds that can fly!
void makeItFly(const FlyingBird& bird) {
    bird.fly();
}
```

#### Why this is better:
If you try to pass `penguin` to `makeItFly(penguin)`, the C++ compiler will **refuse to compile**. The bug is caught at compile-time instead of crashing in production!

---

## 6. I: Interface Segregation Principle (ISP)

> *"Clients should not be forced to depend on interfaces they do not use."*

### 🖨️ Real-Life Analogy: The Grocery Store Receipt Printer
- In a giant corporate office, they have a massive all-in-one printer that can **Print**, **Scan**, **Fax**, and **Staple**.
- In a small grocery store checkout, the cashier only has a tiny receipt printer.
- If the software driver forces the tiny receipt printer to implement scanning, faxing, and stapling, it has to write empty dummy functions or throw errors.
- **The Solution**: Don't build one giant "Fat Interface". Split it into small, specific interfaces: `IPrinter`, `IScanner`, `IFax`.

---

### ❌ The Bad Code (The Fat Interface)
Look at [`04_Interface_Segregation/isp_bad.cpp`](./04_Interface_Segregation/isp_bad.cpp):

```cpp
// ❌ FAT INTERFACE: Forces all devices to support printing, scanning, and faxing!
class IMultiFunctionDevice {
public:
    virtual void print(const std::string& doc) = 0;
    virtual void scan() = 0;
    virtual void fax(const std::string& number) = 0;
};

// A cheap receipt printer is forced to implement things it cannot do!
class SimplePrinter : public IMultiFunctionDevice {
public:
    void print(const std::string& doc) override { std::cout << "Printing..." << std::endl; }
    void scan() override { throw std::logic_error("Cannot scan!"); } // Dummy stub!
    void fax(const std::string&) override { throw std::logic_error("Cannot fax!"); }
};
```

---

### ✓ The Good Code (Fine-Grained Role Interfaces)
Look at [`04_Interface_Segregation/isp_good.cpp`](./04_Interface_Segregation/isp_good.cpp):

```cpp
// 1. Small, focused interfaces
class IPrinter {
public:
    virtual ~IPrinter() = default;
    virtual void print(const std::string& doc) = 0;
};

class IScanner {
public:
    virtual ~IScanner() = default;
    virtual void scan(const std::string& doc) = 0;
};

// 2. Simple printer only inherits IPrinter! Zero dead code!
class SimplePrinter : public IPrinter {
public:
    void print(const std::string& doc) override {
        std::cout << "Printing receipt: " << doc << std::endl;
    }
};

// 3. High-end machine inherits both using C++ Multiple Inheritance!
class OfficeMultiMachine : public IPrinter, public IScanner {
public:
    void print(const std::string& doc) override { /* Prints */ }
    void scan(const std::string& doc) override { /* Scans */ }
};
```

#### Why this is better:
Functions that only need printing accept `IPrinter&`. They cannot accidentally call `scan()` on a printer that doesn't have a scanner!

---

## 7. D: Dependency Inversion Principle (DIP)

> *"1. High-level modules should not depend on low-level modules. Both should depend on abstractions.*  
> *2. Abstractions should not depend on details. Details should depend on abstractions."*

### 💡 Real-Life Analogy: The Lightbulb and the Wall Switch
- Think of a wall light switch.
- The switch is NOT directly soldered to a specific 60-watt incandescent lightbulb.
- Instead, there is an **abstraction**: the lightbulb socket (the E27 screw thread).
- The wall switch operates the socket.
- You can screw in an incandescent bulb, an LED bulb, or a colored smart bulb. You don't have to rewire the switch when you change the bulb!

---

### ❌ The Bad Code (High-Level Service Tightly Tied to Low-Level Database)
Look at [`05_Dependency_Inversion/dip_bad.cpp`](./05_Dependency_Inversion/dip_bad.cpp):

```cpp
// Low-level database driver
class MySQLDatabase {
public:
    void save(const std::string& data) { /* Writes SQL */ }
};

// ❌ BAD: High-level business class directly creates a MySQLDatabase!
class UserService {
private:
    MySQLDatabase database_; // TIGHT COUPLING! Hardcoded to MySQL!
public:
    void registerUser(const std::string& username) {
        database_.save(username);
    }
};
```
#### Why this fails:
1. If your company moves from MySQL to PostgreSQL, you have to tear open and rewrite `UserService`.
2. You cannot test `UserService` without installing and configuring a real MySQL server on your computer!

---

### ✓ The Good Code (Dependency Injection with an Interface)
Look at [`05_Dependency_Inversion/dip_good.cpp`](./05_Dependency_Inversion/dip_good.cpp):

```cpp
// 1. The Abstraction (Interface)
class IDatabase {
public:
    virtual ~IDatabase() = default;
    virtual void save(const std::string& data) = 0;
};

// 2. Concrete implementations depend on the abstraction
class MySQLDatabase : public IDatabase {
public:
    void save(const std::string& data) override {
        std::cout << "[MySQL] Saving: " << data << std::endl;
    }
};

class PostgreSQLDatabase : public IDatabase {
public:
    void save(const std::string& data) override {
        std::cout << "[PostgreSQL] Saving: " << data << std::endl;
    }
};

// 3. Fake in-memory database for testing (Runs in 0.001 ms!)
class MockDatabase : public IDatabase {
public:
    std::vector<std::string> savedData;
    void save(const std::string& data) override {
        savedData.push_back(data);
    }
};

// 4. High-level class depends ONLY on the abstraction!
class UserService {
private:
    IDatabase& database_; // Injected reference to abstraction!

public:
    // CONSTRUCTOR DEPENDENCY INJECTION:
    explicit UserService(IDatabase& db) : database_(db) {}

    void registerUser(const std::string& username) {
        database_.save(username);
    }
};
```

#### Why this is better:
- To switch to PostgreSQL, you only change **one line** in `main()`!
- To test your business logic offline, you can inject `MockDatabase` without needing any database software installed!

---

## 8. Quick Reference Cheat Sheet

| Principle | Plain English Meaning | Real-Life Analogy | Beginner Tip |
| :--- | :--- | :--- | :--- |
| **S** (Single Responsibility) | A class should have only **one job**. | Chef cooks, accountant does taxes. | If your class does calculation *and* printing *and* file saving, split it! |
| **O** (Open-Closed) | **Add new code** instead of editing old code. | Wall socket accepts any new appliance. | Use an abstract base class (`Shape`) instead of giant `switch(type)` statements. |
| **L** (Liskov Substitution) | Subclasses must **not break** base class rules. | A Penguin is a bird, but it shouldn't inherit a `fly()` method. | If a subclass throws `NotSupportedException` in an inherited method, LSP is broken. |
| **I** (Interface Segregation) | Keep interfaces **small and focused**. | Cashier printer only prints; doesn't need scan or fax buttons. | Prefer multiple small interfaces (`IPrinter`, `IScanner`) over one fat interface. |
| **D** (Dependency Inversion) | Depend on **interfaces**, not concrete classes. | Phone charger plugs into socket standard, not bare wires. | Pass dependencies into constructors (**Dependency Injection**) so you can mock them! |

---

## 🚀 How to Run the Code Examples

Open PowerShell in this directory:
```powershell
# Compile and run any good example:
cd "01_Single_Responsibility"
g++ -std=c++20 srp_good.cpp -o srp_good.exe
.\srp_good.exe

cd "..\02_Open_Closed"
g++ -std=c++20 ocp_good.cpp -o ocp_good.exe
.\ocp_good.exe

cd "..\03_Liskov_Substitution"
g++ -std=c++20 lsp_good.cpp -o lsp_good.exe
.\lsp_good.exe

cd "..\04_Interface_Segregation"
g++ -std=c++20 isp_good.cpp -o isp_good.exe
.\isp_good.exe

cd "..\05_Dependency_Inversion"
g++ -std=c++20 dip_good.cpp -o dip_good.exe
.\dip_good.exe
```

