#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iomanip>

class FloatRepository {
private:
    std::vector<float> arrFloat;
    std::string fileName;
    int maxCapacity;
    
public:
    // Constructor
    FloatRepository(const std::string& file = "data.txt", int capacity = 1000) 
        : fileName(file), maxCapacity(capacity) {
        arrFloat.reserve(capacity);
        loadFromFile();
    }
    
    // Destructor
    ~FloatRepository() {
        save(); // Guardar automáticamente al destruir
    }
    
    // Agregar un valor float al repositorio
    bool addValue(float value) {
        if (arrFloat.size() >= maxCapacity) {
            std::cout << "Error: Repositorio lleno (capacidad máxima: " << maxCapacity << ")\n";
            return false;
        }
        
        arrFloat.push_back(value);
        std::cout << "Valor " << value << " agregado exitosamente\n";
        return true;
    }
    
    // Agregar múltiples valores
    void addValues(const std::vector<float>& values) {
        for (float value : values) {
            if (!addValue(value)) break;
        }
    }
    
    // Método save - Guardar datos en archivo
    bool save() {
        std::ofstream file(fileName);
        if (!file.is_open()) {
            std::cout << "Error: No se pudo abrir el archivo " << fileName << " para escritura\n";
            return false;
        }
        
        file << std::fixed << std::setprecision(6);
        for (size_t i = 0; i < arrFloat.size(); ++i) {
            file << arrFloat[i];
            if (i < arrFloat.size() - 1) {
                file << "\n";
            }
        }
        
        file.close();
        std::cout << "Datos guardados exitosamente en " << fileName << std::endl;
        std::cout << "Total de valores guardados: " << arrFloat.size() << std::endl;
        return true;
    }
    
    // Método save con nombre de archivo personalizado
    bool save(const std::string& customFileName) {
        std::string originalFileName = fileName;
        fileName = customFileName;
        bool result = save();
        fileName = originalFileName;
        return result;
    }
    
    // Cargar datos desde archivo
    bool loadFromFile() {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            std::cout << "Archivo " << fileName << " no encontrado. Iniciando repositorio vacío.\n";
            return false;
        }
        
        arrFloat.clear();
        float value;
        int count = 0;
        
        while (file >> value && count < maxCapacity) {
            arrFloat.push_back(value);
            count++;
        }
        
        file.close();
        std::cout << "Cargados " << arrFloat.size() << " valores desde " << fileName << std::endl;
        return true;
    }
    
    // Método getArea - Calcular área bajo la curva (aproximación trapezoidal)
    float getArea() const {
        if (arrFloat.size() < 2) {
            std::cout << "Error: Se necesitan al menos 2 puntos para calcular el área\n";
            return 0.0f;
        }
        
        float area = 0.0f;
        float dx = 1.0f; // Espaciado entre puntos (puedes modificar esto)
        
        // Regla del trapecio
        for (size_t i = 0; i < arrFloat.size() - 1; ++i) {
            area += (arrFloat[i] + arrFloat[i + 1]) * dx / 2.0f;
        }
        
        std::cout << "Área calculada (regla del trapecio): " << area << std::endl;
        return area;
    }
    
    // Método getArea con espaciado personalizado
    float getArea(float deltaX) const {
        if (arrFloat.size() < 2) {
            std::cout << "Error: Se necesitan al menos 2 puntos para calcular el área\n";
            return 0.0f;
        }
        
        float area = 0.0f;
        
        for (size_t i = 0; i < arrFloat.size() - 1; ++i) {
            area += (arrFloat[i] + arrFloat[i + 1]) * deltaX / 2.0f;
        }
        
        std::cout << "Área calculada con dx=" << deltaX << ": " << area << std::endl;
        return area;
    }
    
    // Método getArea para un rango específico
    float getArea(int startIndex, int endIndex, float deltaX = 1.0f) const {
        if (startIndex < 0 || endIndex >= static_cast<int>(arrFloat.size()) || startIndex >= endIndex) {
            std::cout << "Error: Índices inválidos para el cálculo del área\n";
            return 0.0f;
        }
        
        float area = 0.0f;
        for (int i = startIndex; i < endIndex; ++i) {
            area += (arrFloat[i] + arrFloat[i + 1]) * deltaX / 2.0f;
        }
        
        std::cout << "Área calculada en rango [" << startIndex << ", " << endIndex << "]: " << area << std::endl;
        return area;
    }
    
    // Métodos auxiliares
    void displayData() const {
        if (arrFloat.empty()) {
            std::cout << "Repositorio vacío\n";
            return;
        }
        
        std::cout << "\n=== DATOS EN EL REPOSITORIO ===\n";
        std::cout << "Total de elementos: " << arrFloat.size() << std::endl;
        std::cout << "Valores: ";
        
        for (size_t i = 0; i < arrFloat.size(); ++i) {
            std::cout << std::fixed << std::setprecision(2) << arrFloat[i];
            if (i < arrFloat.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }
    
    // Estadísticas del repositorio
    void showStatistics() const {
        if (arrFloat.empty()) {
            std::cout << "No hay datos para mostrar estadísticas\n";
            return;
        }
        
        float sum = std::accumulate(arrFloat.begin(), arrFloat.end(), 0.0f);
        float average = sum / arrFloat.size();
        float minVal = *std::min_element(arrFloat.begin(), arrFloat.end());
        float maxVal = *std::max_element(arrFloat.begin(), arrFloat.end());
        
        std::cout << "\n=== ESTADÍSTICAS ===\n";
        std::cout << "Cantidad de elementos: " << arrFloat.size() << std::endl;
        std::cout << "Suma total: " << sum << std::endl;
        std::cout << "Promedio: " << average << std::endl;
        std::cout << "Valor mínimo: " << minVal << std::endl;
        std::cout << "Valor máximo: " << maxVal << std::endl;
    }
    
    // Limpiar repositorio
    void clear() {
        arrFloat.clear();
        std::cout << "Repositorio limpiado\n";
    }
    
    // Obtener tamaño
    size_t size() const {
        return arrFloat.size();
    }
    
    // Verificar si está vacío
    bool isEmpty() const {
        return arrFloat.empty();
    }
    
    // Operador para acceso por índice
    float& operator[](size_t index) {
        if (index >= arrFloat.size()) {
            throw std::out_of_range("Índice fuera de rango");
        }
        return arrFloat[index];
    }
    
    const float& operator[](size_t index) const {
        if (index >= arrFloat.size()) {
            throw std::out_of_range("Índice fuera de rango");
        }
        return arrFloat[index];
    }
};

// Función para mostrar menú
void showMenu() {
    std::cout << "\n========== MENÚ REPOSITORIO FLOAT ==========\n";
    std::cout << "1. Agregar valor único\n";
    std::cout << "2. Agregar múltiples valores\n";
    std::cout << "3. Mostrar datos\n";
    std::cout << "4. Guardar en archivo (save)\n";
    std::cout << "5. Calcular área (getArea)\n";
    std::cout << "6. Calcular área con espaciado personalizado\n";
    std::cout << "7. Calcular área en rango específico\n";
    std::cout << "8. Mostrar estadísticas\n";
    std::cout << "9. Limpiar repositorio\n";
    std::cout << "10. Cargar desde archivo\n";
    std::cout << "0. Salir\n";
    std::cout << "============================================\n";
    std::cout << "Seleccione una opción: ";
}

int main() {
    // Crear repositorio
    FloatRepository repo("mi_repositorio.txt", 100);
    
    // Datos de ejemplo para demostración
    std::cout << "=== DEMOSTRACIÓN DEL REPOSITORIO FLOAT ===\n\n";
    
    // Agregar algunos datos de ejemplo
    std::vector<float> ejemplos = {1.5f, 2.8f, 4.2f, 3.1f, 5.7f, 2.9f, 6.3f, 4.8f};
    std::cout << "Agregando datos de ejemplo...\n";
    repo.addValues(ejemplos);
    
    // Mostrar datos
    repo.displayData();
    
    // Calcular área
    std::cout << "\nCalculando área bajo la curva:\n";
    float area1 = repo.getArea();
    
    // Calcular área con espaciado personalizado
    float area2 = repo.getArea(0.5f);
    
    // Calcular área en un rango
    float area3 = repo.getArea(2, 5, 1.0f);
    
    // Mostrar estadísticas
    repo.showStatistics();
    
    // Guardar datos
    std::cout << "\nGuardando datos...\n";
    repo.save();
    
    // Menú interactivo
    int option;
    do {
        showMenu();
        std::cin >> option;
        
        switch (option) {
            case 1: {
                float valor;
                std::cout << "Ingrese el valor: ";
                std::cin >> valor;
                repo.addValue(valor);
                break;
            }
            case 2: {
                int n;
                std::cout << "¿Cuántos valores desea agregar? ";
                std::cin >> n;
                std::vector<float> valores(n);
                std::cout << "Ingrese los valores:\n";
                for (int i = 0; i < n; ++i) {
                    std::cout << "Valor " << (i+1) << ": ";
                    std::cin >> valores[i];
                }
                repo.addValues(valores);
                break;
            }
            case 3:
                repo.displayData();
                break;
            case 4:
                repo.save();
                break;
            case 5:
                repo.getArea();
                break;
            case 6: {
                float dx;
                std::cout << "Ingrese el espaciado (deltaX): ";
                std::cin >> dx;
                repo.getArea(dx);
                break;
            }
            case 7: {
                int start, end;
                float dx;
                std::cout << "Ingrese índice inicial: ";
                std::cin >> start;
                std::cout << "Ingrese índice final: ";
                std::cin >> end;
                std::cout << "Ingrese espaciado (deltaX): ";
                std::cin >> dx;
                repo.getArea(start, end, dx);
                break;
            }
            case 8:
                repo.showStatistics();
                break;
            case 9:
                repo.clear();
                break;
            case 10:
                repo.loadFromFile();
                break;
            case 0:
                std::cout << "Saliendo del programa...\n";
                break;
            default:
                std::cout << "Opción inválida\n";
        }
    } while (option != 0);
    
    return 0;
}
