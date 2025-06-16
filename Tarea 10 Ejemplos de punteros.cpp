#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Clase de ejemplo para demostrar punteros a objetos
class Persona {
private:
    std::string nombre;
    int edad;
    
public:
    Persona(const std::string& n, int e) : nombre(n), edad(e) {
        std::cout << "Constructor: Persona " << nombre << " creada\n";
    }
    
    ~Persona() {
        std::cout << "Destructor: Persona " << nombre << " destruida\n";
    }
    
    void mostrarInfo() const {
        std::cout << "Nombre: " << nombre << ", Edad: " << edad << std::endl;
    }
    
    void setEdad(int nuevaEdad) { edad = nuevaEdad; }
    std::string getNombre() const { return nombre; }
    int getEdad() const { return edad; }
};

// Clase para demostrar punteros inteligentes
class SmartPointerDemo {
public:
    // Demostración de unique_ptr
    static void demoUniquePtr() {
        std::cout << "\n=== UNIQUE_PTR DEMO ===\n";
        
        // Crear unique_ptr
        std::unique_ptr<Persona> persona1 = std::make_unique<Persona>("Ana", 25);
        persona1->mostrarInfo();
        
        // Transferir ownership
        std::unique_ptr<Persona> persona2 = std::move(persona1);
        
        if (persona1 == nullptr) {
            std::cout << "persona1 ahora es nullptr después del move\n";
        }
        
        persona2->mostrarInfo();
        // persona2 se destruye automáticamente al salir del scope
    }
    
    // Demostración de shared_ptr
    static void demoSharedPtr() {
        std::cout << "\n=== SHARED_PTR DEMO ===\n";
        
        std::shared_ptr<Persona> persona1 = std::make_shared<Persona>("Carlos", 30);
        std::cout << "Contador de referencias: " << persona1.use_count() << std::endl;
        
        {
            std::shared_ptr<Persona> persona2 = persona1;
            std::cout << "Contador después de copiar: " << persona1.use_count() << std::endl;
            persona2->mostrarInfo();
        } // persona2 sale del scope
        
        std::cout << "Contador después de que persona2 salga del scope: " << persona1.use_count() << std::endl;
    }
};

// Funciones para demostrar diferentes usos de punteros
void demoBasicPointers() {
    std::cout << "\n=== PUNTEROS BÁSICOS ===\n";
    
    // Puntero básico
    int valor = 42;
    int* ptr = &valor;
    
    std::cout << "Valor: " << valor << std::endl;
    std::cout << "Dirección de valor: " << &valor << std::endl;
    std::cout << "Puntero ptr apunta a: " << ptr << std::endl;
    std::cout << "Valor apuntado por ptr: " << *ptr << std::endl;
    
    // Modificar valor a través del puntero
    *ptr = 100;
    std::cout << "Después de modificar con puntero - Valor: " << valor << std::endl;
}

void demoArrayPointers() {
    std::cout << "\n=== PUNTEROS Y ARRAYS ===\n";
    
    int arr[] = {10, 20, 30, 40, 50};
    int* ptr = arr; // El nombre del array es un puntero al primer elemento
    
    std::cout << "Array usando índices:\n";
    for (int i = 0; i < 5; i++) {
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
    }
    
    std::cout << "\nArray usando aritmética de punteros:\n";
    for (int i = 0; i < 5; i++) {
        std::cout << "*(ptr + " << i << ") = " << *(ptr + i) << std::endl;
    }
}

void demoFunctionPointers() {
    std::cout << "\n=== PUNTEROS A FUNCIONES ===\n";
    
    // Definir funciones
    auto suma = [](int a, int b) -> int { return a + b; };
    auto resta = [](int a, int b) -> int { return a - b; };
    auto multiplicacion = [](int a, int b) -> int { return a * b; };
    
    // Puntero a función
    int (*operacion)(int, int);
    
    // Array de punteros a funciones
    int (*operaciones[])(int, int) = {suma, resta, multiplicacion};
    std::string nombres[] = {"Suma", "Resta", "Multiplicación"};
    
    int a = 15, b = 5;
    
    for (int i = 0; i < 3; i++) {
        operacion = operaciones[i];
        int resultado = operacion(a, b);
        std::cout << nombres[i] << "(" << a << ", " << b << ") = " << resultado << std::endl;
    }
}

void demoPointerToPointer() {
    std::cout << "\n=== PUNTERO A PUNTERO ===\n";
    
    int valor = 123;
    int* ptr1 = &valor;
    int** ptr2 = &ptr1; // Puntero a puntero
    
    std::cout << "Valor: " << valor << std::endl;
    std::cout << "Valor a través de ptr1: " << *ptr1 << std::endl;
    std::cout << "Valor a través de ptr2: " << **ptr2 << std::endl;
    
    std::cout << "\nDirecciones:\n";
    std::cout << "Dirección de valor: " << &valor << std::endl;
    std::cout << "Dirección almacenada en ptr1: " << ptr1 << std::endl;
    std::cout << "Dirección de ptr1: " << &ptr1 << std::endl;
    std::cout << "Dirección almacenada en ptr2: " << ptr2 << std::endl;
}

void demoDynamicMemory() {
    std::cout << "\n=== MEMORIA DINÁMICA ===\n";
    
    // Asignación dinámica simple
    int* ptr = new int(42);
    std::cout << "Valor dinámico: " << *ptr << std::endl;
    delete ptr; // Importante: liberar memoria
    
    // Array dinámico
    int size = 5;
    int* arr = new int[size];
    
    // Inicializar array
    for (int i = 0; i < size; i++) {
        arr[i] = (i + 1) * 10;
    }
    
    std::cout << "Array dinámico: ";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    
    delete[] arr; // Importante: liberar memoria del array
    
    // Objeto dinámico
    Persona* personaPtr = new Persona("Luis", 28);
    personaPtr->mostrarInfo();
    delete personaPtr;
}

// Función que modifica un valor usando puntero (paso por referencia simulado)
void modificarValor(int* ptr) {
    if (ptr != nullptr) {
        *ptr = *ptr * 2;
    }
}

// Función que intercambia dos valores usando punteros
void intercambiar(int* a, int* b) {
    if (a != nullptr && b != nullptr) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }
}

void demoFunctionParameters() {
    std::cout << "\n=== PUNTEROS COMO PARÁMETROS ===\n";
    
    int x = 10, y = 20;
    
    std::cout << "Antes - x: " << x << ", y: " << y << std::endl;
    
    modificarValor(&x);
    std::cout << "Después de modificar x: " << x << std::endl;
    
    intercambiar(&x, &y);
    std::cout << "Después de intercambiar - x: " << x << ", y: " << y << std::endl;
}

// Clase para demostrar this pointer
class MiClase {
private:
    int valor;
    
public:
    MiClase(int v) : valor(v) {}
    
    MiClase& setValor(int v) {
        this->valor = v;
        return *this; // Retorna referencia al objeto actual
    }
    
    MiClase& incrementar() {
        this->valor++;
        return *this;
    }
    
    void mostrar() const {
        std::cout << "Valor: " << this->valor 
                  << " (dirección del objeto: " << this << ")" << std::endl;
    }
};

void demoThisPointer() {
    std::cout << "\n=== THIS POINTER ===\n";
    
    MiClase obj(10);
    obj.mostrar();
    
    // Encadenamiento de métodos gracias al this pointer
    obj.setValor(5).incrementar().incrementar().mostrar();
}

int main() {
    std::cout << "========================================\n";
    std::cout << "       DEMOSTRACIÓN DE PUNTEROS C++     \n";
    std::cout << "========================================\n";
    
    // Ejecutar todas las demostraciones
    demoBasicPointers();
    demoArrayPointers();
    demoFunctionPointers();
    demoPointerToPointer();
    demoDynamicMemory();
    demoFunctionParameters();
    demoThisPointer();
    
    // Punteros inteligentes
    SmartPointerDemo::demoUniquePtr();
    SmartPointerDemo::demoSharedPtr();
    
    std::cout << "\n========================================\n";
    std::cout << "           FIN DE LA DEMOSTRACIÓN       \n";
    std::cout << "========================================\n";
    
    return 0;
}
