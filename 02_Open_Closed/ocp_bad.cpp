/**
 * ============================================================================
 * PRINCIPLE 2: OPEN-CLOSED PRINCIPLE (OCP) - THE BAD WAY
 * ============================================================================
 * 
 * 📖 WHAT IS THE THEORY?
 * The Open-Closed Principle says:
 * "Software entities (classes, modules, functions) should be:
 *   - OPEN for EXTENSION (you can add new features easily)
 *   - CLOSED for MODIFICATION (you should not have to change existing working code)"
 * 
 * 🔌 REAL-LIFE ANALOGY: The Electric Wall Socket
 * Think of an electrical wall socket in your room:
 * - When you buy a brand new device (e.g., a gaming console or an electric fan),
 *   do you call an electrician to rip open the wall and rewire your house? NO!
 * - The wall socket is CLOSED for modification (it never changes).
 * - The system is OPEN for extension (any new device with a matching plug can be plugged in).
 * 
 * ----------------------------------------------------------------------------
 * 🛑 WHY IS THIS CODE "BAD"? (THE ANTI-PATTERN)
 * Below, `AreaCalculator` uses an `enum` and a `switch` (or `if-else`) statement
 * to calculate the area of different shapes.
 * 
 * 💥 WHAT HAPPENS WHEN YOU WANT TO ADD A NEW SHAPE (e.g., Triangle)?
 * 1. You MUST modify the `ShapeType` enum to add `Triangle`.
 * 2. You MUST modify the `AreaCalculator` class to add `case ShapeType::Triangle`.
 * 3. In doing so, you risk introducing bugs into the existing Rectangle or Circle code!
 * 4. You have to re-compile, re-test, and re-deploy the calculator code!
 * 
 * This code is NOT closed for modification. Every new shape forces you to MODIFY old code.
 */

#include <iostream>
#include <vector>
#include <string>

// Enum listing shape types
enum class ShapeType {
    Rectangle,
    Circle
    // To add Triangle, we have to edit this enum!
};

// Simple struct to represent a shape
struct Shape {
    ShapeType type;
    double width;  // Used for Rectangle
    double height; // Used for Rectangle
    double radius; // Used for Circle
};

// ❌ BAD CLASS: Must be modified every time a new shape is invented!
class AreaCalculator {
public:
    double calculateArea(const Shape& shape) const {
        switch (shape.type) {
            case ShapeType::Rectangle:
                return shape.width * shape.height;

            case ShapeType::Circle:
                return 3.14159 * shape.radius * shape.radius;

            // PROBLEM: What if tomorrow we want a Triangle?
            // We have to come back into this class and edit this switch statement!
            default:
                std::cerr << "Error: Unknown shape type!" << std::endl;
                return 0.0;
        }
    }

    double calculateTotalArea(const std::vector<Shape>& shapes) const {
        double total = 0.0;
        for (const auto& shape : shapes) {
            total += calculateArea(shape);
        }
        return total;
    }
};

int main() {
    std::cout << "=== Running OCP Bad Example ===" << std::endl;

    Shape rect{ShapeType::Rectangle, 10.0, 5.0, 0.0};
    Shape circ{ShapeType::Circle, 0.0, 0.0, 7.0};

    std::vector<Shape> shapes = {rect, circ};

    AreaCalculator calc;
    std::cout << "Total Area: " << calc.calculateTotalArea(shapes) << std::endl;

    // Imagine having 50 different shapes and 10 different functions doing operations
    // on them (perimeter, draw, area, rotate)... You would have 10 massive switch statements!
    return 0;
}
