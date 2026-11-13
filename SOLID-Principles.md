# The Complete Notes For SOLID Principles in CPP/C++.
### Understanding SOLID Principles in C++ is crucial for writing clean, maintainable, and scalable code. SOLID is an acronym that stands for five design principles intended to make software designs more understandable, flexible, and maintainable.
### Understand Every Principles from Scratch with Real-World Analogies & Cleand Code

> **References & Inspirations:**
> - *SOLID principles: implementation and examples in C++* by Oleksandra Shershen
> - *SOLID Principles in C++ with Real Life Examples* by Bhawna Gurjar

---

## 📚 Table of Contents
1. [Introduction: Why Do We Need SOLID Principles?](#1-introduction-why-do-we-need-solid-principles)
2. [C++ Important Concepts Must Know Before Learning SOLID Principles](#2-c++-important-concepts-must-know-before-learning-solid-principles)
   - [What is an Abstract Class / Interface?](#what-is-an-interface)
   - [What is `virtual` and `override`?](#what-is-virtual)
   - [Why do we need `virtual ~Base() = default;`?](#why-virtual-destructor)
   - [What is Object Slicing and Why do we use References (`&`)?](#what-is-slicing)
   - [What is `std::unique_ptr`?](#what-is-unique-ptr)
3. [S: Single Responsibility Principle (SRP)](#3-s-single-responsibility-principle-srp)
4. [O: Open-Closed Principle (OCP)](#4-o-open-closed-principle-ocp)
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
- **Easy to test** without needing live databases or network cables.

---
