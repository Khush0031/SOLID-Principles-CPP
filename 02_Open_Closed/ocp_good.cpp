/**
 * ============================================================================
 * PRINCIPLE 2: OPEN-CLOSED PRINCIPLE (OCP) - THE GOOD WAY
 * ============================================================================
 * 
 * 📖 WHAT IS THE SOLUTION?
 * We use C++ Inheritance and Polymorphism!
 * 
 * 1. We create an abstract base class `Shape`.
 *    - It defines a "contract" with a pure virtual function: `virtual double getArea() const = 0;`
 *    - Any shape MUST know how to calculate its own area.
 * 
 * 2. Each specific shape (`Rectangle`, `Circle`, `Triangle`) inherits from `Shape`
 *    and provides its own formula for `getArea()`.
 * 
 * 3. The `AreaCalculator` class now works with the base class `Shape`.
 *    - It never needs to know whether the shape is a Circle, Rectangle, or Hexagon!
 *    - It simply asks: "Shape, what is your area?"
 * 
 * 💡 WHAT MAKES THIS OPEN-CLOSED?
 * - When your boss says "Add a Triangle!", you just write a NEW class `Triangle : public Shape`.
 * - You do NOT touch or edit a single line of `AreaCalculator`!
 * - `AreaCalculator` is CLOSED for modification, but OPEN for extension!
 */

#include <iostream>
#include <vector>
#include <memory> // For std::unique_ptr (modern safe pointers)

// ============================================================================
// 1. BASE CLASS (THE CONTRACT / INTERFACE)
// ============================================================================
class Shape {
public:
    // IMPORTANT C++ RULE FOR BEGINNERS:
    // Whenever you have virtual functions in a base class, you MUST make the
    // destructor virtual! This ensures proper memory cleanup when derived objects
    // are deleted through a base pointer.
    virtual ~Shape() = default;

    // PURE VIRTUAL FUNCTION:
    // The `= 0` means: "I am an abstract blueprint. I don't know my formula,
    // but every derived class MUST provide their own getArea() implementation!"
    virtual double getArea() const = 0;
};

// ============================================================================
// 2. CONCRETE SHAPES (Derived classes implementing the contract)
// ============================================================================

// Rectangle implements Shape
class Rectangle : public Shape {
private:
    double width_;
    double height_;

public:
    Rectangle(double width, double height) : width_(width), height_(height) {}

    // `override` tells the C++ compiler: "Check that this matches the base class!"
    double getArea() const override {
        return width_ * height_;
    }
};

// Circle implements Shape
class Circle : public Shape {
private:
    double radius_;

public:
    explicit Circle(double radius) : radius_(radius) {}

    double getArea() const override {
        return 3.14159 * radius_ * radius_;
    }
};

// ============================================================================
// 3. NEW EXTENSION: Adding a Triangle!
// Notice: We created this new class WITHOUT changing anything in existing classes!
// ============================================================================
class Triangle : public Shape {
private:
    double base_;
    double height_;

public:
    Triangle(double base, double height) : base_(base), height_(height) {}

    double getArea() const override {
        return 0.5 * base_ * height_;
    }
};

// ============================================================================
// 4. CALCULATOR: 100% CLOSED FOR MODIFICATION
// ============================================================================
class AreaCalculator {
public:
    // Works with any Shape via polymorphism (passing references or pointers)!
    // Notice: NO switch statement, NO if-else chains!
    double calculateTotalArea(const std::vector<std::unique_ptr<Shape>>& shapes) const {
        double total = 0.0;
        for (const auto& shape : shapes) {
            // Polymorphic call: C++ automatically calls the correct getArea()!
            total += shape->getArea();
        }
        return total;
    }
};

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main() {
    std::cout << "=== Running OCP Good Example ===" << std::endl;

    // Create a collection of different shapes using smart pointers (std::unique_ptr)
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Rectangle>(10.0, 5.0)); // Area = 50
    shapes.push_back(std::make_unique<Circle>(7.0));          // Area ~ 153.94
    shapes.push_back(std::make_unique<Triangle>(6.0, 4.0));   // Area = 12 (New shape!)

    AreaCalculator calc;
    double totalArea = calc.calculateTotalArea(shapes);

    std::cout << "Total Area of all shapes: " << totalArea << std::endl;

    return 0;
}
