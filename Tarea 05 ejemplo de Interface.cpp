#include <iostream>
#include <cmath>

using namespace std;

// Interfaz (clase abstracta pura)
class IFigura {
public:
    virtual void dibujar() = 0;           // Método para dibujar la figura
    virtual double calcularArea() = 0;    // Método para calcular el área
    virtual ~IFigura() {}                 // Destructor virtual
};

// Implementación de Círculo
class Circulo : public IFigura {
private:
    double radio;
public:
    Circulo(double r) : radio(r) {}
    
    void dibujar() override {
        cout << "Dibujando un círculo." << endl;
    }
    
    double calcularArea() override {
        return 3.1416 * radio * radio;
    }
};

// Implementación de Rectángulo
class Rectangulo : public IFigura {
private:
    double base, altura;
public:
    Rectangulo(double b, double h) : base(b), altura(h) {}
    
    void dibujar() override {
        cout << "Dibujando un rectángulo." << endl;
    }
    
    double calcularArea() override {
        return base * altura;
    }
};

// Función principal
int main() {
    IFigura* f1 = new Circulo(5);
    IFigura* f2 = new Rectangulo(4, 6);

    f1->dibujar();
    cout << "Área del círculo: " << f1->calcularArea() << endl;

    f2->dibujar();
    cout << "Área del rectángulo: " << f2->calcularArea() << endl;

    // Liberar memoria
    delete f1;
    delete f2;

    return 0;
}
