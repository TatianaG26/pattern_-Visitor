#include <iostream>
#include <vector>
using namespace std;

/*Добавить в иерархию посетителей ещё один класс посетителя DrawVisitor. 
Он должен уметь рисовать фигуры (для Circle просто в виде сообщения “Drawing Circle”)*/

class Square;
class Circle;
class Rectangle;

// Абстрактный класс посетителя
class Visitor {
public:
    virtual void visit(Square& square) = 0;
    virtual void visit(Circle& circle) = 0;
    virtual void visit(Rectangle& rectangle) = 0;
};
// Абстрактный класс фигуры
class Shape {
public:
    virtual void accept(Visitor& visitor) = 0;
};
// Конкретные классы фигур
class Square : public Shape {
public:
    Square(double side) : m_side(side) {}

    double area() const { return m_side * m_side; }

    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }
    double getM_side()
    {
        return m_side;
    }
private:
    double m_side;
};
class Circle : public Shape {
public:
    Circle(double radius) : m_radius(radius) {}

    double area() const { return 3.14159265359 * m_radius * m_radius; }

    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }
    double getM_radius()
    {
        return m_radius;
    }

private:
    double m_radius;
};
class Rectangle : public Shape {
public:
    Rectangle(double width, double height) : m_width(width), m_height(height) {}

    double area() const { return m_width * m_height; }

    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }
    double getM_width()
    {
        return m_width;
    }

    double getM_height()
    {
        return m_height;
    }
private:
    double m_width;
    double m_height;
};
// Конкретный класс посетителя, реализующий операцию расчета периметра для каждой фигуры
class PerimeterVisitor : public Visitor {
public:
    void visit(Square& square) override {
        m_perimeter += 4 * square.getM_side();
    }

    void visit(Circle& circle) override {
        m_perimeter += 2 * 3.14159265359 * circle.getM_radius();
    }

    void visit(Rectangle& rectangle) override {
        m_perimeter += 2 * (rectangle.getM_width() + rectangle.getM_height());
    }
    double perimeter() const { return m_perimeter; }

private:
    double m_perimeter = 0.0;
};
// Конкретный класс посетителя, реализующий операцию рисования каждой фигуры
class DrawVisitor : public Visitor {
public:
    void visit(Square& square) override
    {
        for (int i = 0; i < square.getM_side(); i++)
        {
            for (int j = 0; j < square.getM_side(); j++)
                if (i == 0 || i == square.getM_side() - 1 || j == 0 || j == square.getM_side() - 1)
                    cout << "* ";
                else cout << "  ";
            cout << endl;
        }
    }
    void visit(Circle& circle) override
    {
        cout << "Drawing Circle\n";
    }
    void visit(Rectangle& rectangle) override
    {
        for (int i = 0; i < rectangle.getM_height(); i++)
        {
            for (int j = 0; j < rectangle.getM_width(); j++)
                if (i == 0 || i == rectangle.getM_height() - 1 || j == 0 || j == rectangle.getM_width() - 1)
                    cout << "* ";
                else cout << "  ";
            cout << endl;
        }
    }
};
// Пример использования паттерна посетитель
int main()
{    
    vector<Shape*> shapes = { new Square(3), new Circle(2), new Rectangle(4, 5) };

    PerimeterVisitor perimeterVisitor;
    DrawVisitor drawVisitor;

    for (auto shape : shapes) {
        shape->accept(perimeterVisitor);
        shape->accept(drawVisitor);
    }

    cout << "Total perimeter: " << perimeterVisitor.perimeter() << endl;

    // Очистка памяти
    for (auto shape : shapes) 
    {
        delete shape;
    }
    return 0;
}
/**/