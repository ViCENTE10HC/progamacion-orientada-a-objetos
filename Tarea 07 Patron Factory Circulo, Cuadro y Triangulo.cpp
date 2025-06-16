#include <iostream>
#include <memory>
#include <string>
#include <cmath>

using namespace std;

// Clase base abstracta
class FiguraGeometrica {
public:
    virtual void dibujar() = 0;
    virtual double area() = 0;
    virtual ~FiguraGeometrica() {}
};

// Clase Círculo
class Circulo : public FiguraGeometrica {
    double radio;
public:
    Circulo(double r) : radio(r) {}
    void dibujar() override {
        cout << "Dibujando un Círculo\n";
    }
    double area() override {
        return 3.1416 * radio * radio;
    }
};

// Clase Cuadro (Cuadrado)
class Cuadro : public FiguraGeometrica {
    double lado;
public:
    Cuadro(double l) : lado(l) {}
    void dibujar() override {
        cout << "Dibujando un Cuadro\n";
    }
    double area() override {
        return lado * lado;
    }
};

// Clase Triángulo
class Triangulo : public FiguraGeometrica {
    double base, altura;
public:
    Triangulo(double b, double h) : base(b), altura(h) {}
    void dibujar() override {
        cout << "Dibujando un Triángulo\n";
    }
    double area() override {
        return (base * altura) / 2;
    }
};

// Fábrica de figuras
class FiguraFactory {
public:
    static unique_ptr<FiguraGeometrica> crearFigura(const string& tipo, double a, double b = 0) {
        if (tipo == "circulo") {
            return make_unique<Circulo>(a);
        } else if (tipo == "cuadro") {
            return make_unique<Cuadro>(a);
        } else if (tipo == "triangulo") {
            return make_unique<Triangulo>(a, b);
        } else {
            return nullptr;
        }
    }
};

// Función principal
int main() {
    auto figura1 = FiguraFactory::crearFigura("circulo", 5);
    auto figura2 = FiguraFactory::crearFigura("cuadro", 4);
    auto figura3 = FiguraFactory::crearFigura("triangulo", 3, 6);

    figura1->dibujar();
    cout << "Área del círculo: " << figura1->area() << "\n\n";

    figura2->dibujar();
    cout << "Área del cuadro: " << figura2->area() << "\n\n";

    figura3->dibujar();
    cout << "Área del triángulo: " << figura3->area() << "\n";

    return 0;
}
