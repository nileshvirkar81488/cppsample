#include <iostream>
#include <memory>

// Base class with virtual destructor
class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
};

// Derived classes
class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a circle\n";
    }
    
    void setRadius(double r) {
        radius = r;
    }
    
    double getRadius() const {
        return radius;
    }
    
private:
    double radius = 1.0;
};

class Rectangle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a rectangle\n";
    }
    
    void setDimensions(double w, double h) {
        width = w;
        height = h;
    }
    
private:
    double width = 1.0;
    double height = 1.0;
};

// Function that violates the dynamic_cast rule
void processShape(Shape* shape) {
    // RULE VIOLATION: Using dynamic_cast
    // The DynamicCast_checker would flag this line
    Circle* circle = dynamic_cast<Circle*>(shape);
    
    if (circle) {
        std::cout << "This is a circle with radius: " << circle->getRadius() << std::endl;
        circle->setRadius(5.0);
    } else {
        // Another dynamic_cast violation
        Rectangle* rect = dynamic_cast<Rectangle*>(shape);
        if (rect) {
            std::cout << "This is a rectangle\n";
            rect->setDimensions(10.0, 20.0);
        }
    }
}

// Alternative approach without dynamic_cast (recommended)
class ShapeProcessor {
public:
    virtual void processCircle(Circle& circle) {
        std::cout << "Processing circle with radius: " << circle.getRadius() << std::endl;
    }
    
    virtual void processRectangle(Rectangle& rect) {
        std::cout << "Processing rectangle\n";
    }
};

// Better design using visitor pattern or virtual functions
class ImprovedShape {
public:
    virtual ~ImprovedShape() = default;
    virtual void draw() const = 0;
    virtual void accept(ShapeProcessor& processor) = 0;
};

class ImprovedCircle : public ImprovedShape {
public:
    void draw() const override {
        std::cout << "Drawing improved circle\n";
    }
    
    void accept(ShapeProcessor& processor) override {
        processor.processCircle(*this);
    }
    
    double getRadius() const { return radius; }
    
private:
    double radius = 1.0;
};

int main() {
    // Create shapes
    std::unique_ptr<Shape> circle = std::make_unique<Circle>();
    std::unique_ptr<Shape> rectangle = std::make_unique<Rectangle>();
    
    // This function contains dynamic_cast violations
    // The DynamicCast_checker would report issues for these calls
    processShape(circle.get());    // Line with dynamic_cast violation
    processShape(rectangle.get()); // Line with dynamic_cast violation
    
    return 0;
}
