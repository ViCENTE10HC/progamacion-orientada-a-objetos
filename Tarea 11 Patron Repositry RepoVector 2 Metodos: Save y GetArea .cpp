#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iomanip>
#include <sstream>

class DualFloatRepository {
private:
    static const int MAX_ARRAY_SIZE = 1000;
    float arrFloat[MAX_ARRAY_SIZE];      // Array estático de floats
    int arraySize;                       // Tamaño actual del array
    std::vector<float> vectorFloat;      // Vector dinámico de floats
    std::string fileName;
    
    // Enum para identificar el tipo de contenedor
    enum ContainerType {
        ARRAY_CONTAINER,
        VECTOR_CONTAINER,
        BOTH_CONTAINERS
    };

public:
    // Constructor
    DualFloatRepository(const std::string& file = "dual_data.txt") 
        : arraySize(0), fileName(file) {
        // Inicializar array
        for (int i = 0; i < MAX_ARRAY_SIZE; ++i) {
            arrFloat[i] = 0.0f;
        }
        
        loadFromFile();
    }
    
    // Destructor
    ~DualFloatRepository() {
        save(); // Guardar automáticamente
    }
    
    // =================== MÉTODOS DE INSERCIÓN ===================
    
    // Agregar al array
    bool addToArray(float value) {
        if (arraySize >= MAX_ARRAY_SIZE) {
            std::cout << "Error: Array lleno (capacidad máxima: " << MAX_ARRAY_SIZE << ")\n";
            return false;
        }
        
        arrFloat[arraySize] = value;
        arraySize++;
        std::cout << "Valor " << value << " agregado al array (posición " << arraySize-1 << ")\n";
        return true;
    }
    
    // Agregar al vector
    void addToVector(float value) {
        vectorFloat.push_back(value);
        std::cout << "Valor " << value << " agregado al vector (posición " << vectorFloat.size()-1 << ")\n";
    }
    
    // Agregar a ambos contenedores
    void addToBoth(float value) {
        addToArray(value);
        addToVector(value);
    }
    
    // Agregar múltiples valores al array
    void addArrayValues(const std::vector<float>& values) {
        for (float value : values) {
            if (!addToArray(value)) break;
        }
    }
    
    // Agregar múltiples valores al vector
    void addVectorValues(const std::vector<float>& values) {
        for (float value : values) {
            addToVector(value);
        }
    }
    
    // =================== MÉTODOS SAVE ===================
    
    // Save principal - guarda ambos contenedores
    bool save() {
        return saveArray() && saveVector() && saveCombined();
    }
    
    // Save solo array
    bool saveArray() {
        std::string arrayFileName = "array_" + fileName;
        std::ofstream file(arrayFileName);
        
        if (!file.is_open()) {
            std::cout << "Error: No se pudo abrir " << arrayFileName << std::endl;
            return false;
        }
        
        file << "# Array Data (Size: " << arraySize << ")\n";
        file << std::fixed << std::setprecision(6);
        
        for (int i = 0; i < arraySize; ++i) {
            file << arrFloat[i];
            if (i < arraySize - 1) file << "\n";
        }
        
        file.close();
        std::cout << "Array guardado en " << arrayFileName << " (" << arraySize << " elementos)\n";
        return true;
    }
    
    // Save solo vector
    bool saveVector() {
        std::string vectorFileName = "vector_" + fileName;
        std::ofstream file(vectorFileName);
        
        if (!file.is_open()) {
            std::cout << "Error: No se pudo abrir " << vectorFileName << std::endl;
            return false;
        }
        
        file << "# Vector Data (Size: " << vectorFloat.size() << ")\n";
        file << std::fixed << std::setprecision(6);
        
        for (size_t i = 0; i < vectorFloat.size(); ++i) {
            file << vectorFloat[i];
            if (i < vectorFloat.size() - 1) file << "\n";
        }
        
        file.close();
        std::cout << "Vector guardado en " << vectorFileName << " (" << vectorFloat.size() << " elementos)\n";
        return true;
    }
    
    // Save combinado
    bool saveCombined() {
        std::string combinedFileName = "combined_" + fileName;
        std::ofstream file(combinedFileName);
        
        if (!file.is_open()) {
            std::cout << "Error: No se pudo abrir " << combinedFileName << std::endl;
            return false;
        }
        
        file << "# Combined Repository Data\n";
        file << "# Array Size: " << arraySize << ", Vector Size: " << vectorFloat.size() << "\n";
        file << std::fixed << std::setprecision(6);
        
        file << "[ARRAY_DATA]\n";
        for (int i = 0; i < arraySize; ++i) {
            file << arrFloat[i] << "\n";
        }
        
        file << "[VECTOR_DATA]\n";
        for (size_t i = 0; i < vectorFloat.size(); ++i) {
            file << vectorFloat[i] << "\n";
        }
        
        file.close();
        std::cout << "Datos combinados guardados en " << combinedFileName << std::endl;
        return true;
    }
    
    // =================== MÉTODOS GETAREA ===================
    
    // GetArea del array
    float getAreaArray() const {
        if (arraySize < 2) {
            std::cout << "Error: Array necesita al menos 2 elementos para calcular área\n";
            return 0.0f;
        }
        
        float area = 0.0f;
        float dx = 1.0f;
        
        // Regla del trapecio
        for (int i = 0; i < arraySize - 1; ++i) {
            area += (arrFloat[i] + arrFloat[i + 1]) * dx / 2.0f;
        }
        
        std::cout << "Área del array: " << area << std::endl;
        return area;
    }
    
    // GetArea del vector
    float getAreaVector() const {
        if (vectorFloat.size() < 2) {
            std::cout << "Error: Vector necesita al menos 2 elementos para calcular área\n";
            return 0.0f;
        }
        
        float area = 0.0f;
        float dx = 1.0f;
        
        for (size_t i = 0; i < vectorFloat.size() - 1; ++i) {
            area += (vectorFloat[i] + vectorFloat[i + 1]) * dx / 2.0f;
        }
        
        std::cout << "Área del vector: " << area << std::endl;
        return area;
    }
    
    // GetArea combinada (suma de ambas áreas)
    float getAreaCombined() const {
        float arrayArea = (arraySize >= 2) ? getAreaArray() : 0.0f;
        float vectorArea = (vectorFloat.size() >= 2) ? getAreaVector() : 0.0f;
        float combinedArea = arrayArea + vectorArea;
        
        std::cout << "Área combinada (Array + Vector): " << combinedArea << std::endl;
        return combinedArea;
    }
    
    // GetArea con espaciado personalizado para array
    float getAreaArray(float deltaX) const {
        if (arraySize < 2) {
            std::cout << "Error: Array necesita al menos 2 elementos\n";
            return 0.0f;
        }
        
        float area = 0.0f;
        for (int i = 0; i < arraySize - 1; ++i) {
            area += (arrFloat[i] + arrFloat[i + 1]) * deltaX / 2.0f;
        }
        
        std::cout << "Área del array con dx=" << deltaX << ": " << area << std::endl;
        return area;
    }
    
    // GetArea con espaciado personalizado para vector
    float getAreaVector(float deltaX) const {
        if (vectorFloat.size() < 2) {
            std::cout << "Error: Vector necesita al menos 2 elementos\n";
            return 0.0f;
        }
        
        float area = 0.0f;
        for (size_t i = 0; i < vectorFloat.size() - 1; ++i) {
            area += (vectorFloat[i] + vectorFloat[i + 1]) * deltaX / 2.0f;
        }
        
        std::cout << "Área del vector con dx=" << deltaX << ": " << area << std::endl;
        return area;
    }
    
    // GetArea en rango específico para array
    float getAreaArrayRange(int startIndex, int endIndex, float deltaX = 1.0f) const {
        if (startIndex < 0 || endIndex >= arraySize || startIndex >= endIndex) {
            std::cout << "Error: Índices inválidos para el array\n";
            return 0.0f;
        }
        
        float area = 0.0f;
        for (int i = startIndex; i < endIndex; ++i) {
            area += (arrFloat[i] + arrFloat[i + 1]) * deltaX / 2.0f;
        }
        
        std::cout << "Área del array en rango [" << startIndex << ", " << endIndex << "]: " << area << std::endl;
        return area;
    }
    
    // GetArea en rango específico para vector
    float getAreaVectorRange(int startIndex, int endIndex, float deltaX = 1.0f) const {
        if (startIndex < 0 || endIndex >= static_cast<int>(vectorFloat.size()) || startIndex >= endIndex) {
            std::cout << "Error: Índices inválidos para el vector\n";
            return 0.0f;
        }
        
        float area = 0.0f;
        for (int i = startIndex; i < endIndex; ++i) {
            area += (vectorFloat[i] + vectorFloat[i + 1]) * deltaX / 2.0f;
        }
        
        std::cout << "Área del vector en rango [" << startIndex << ", " << endIndex << "]: " << area << std::endl;
        return area;
    }
    
    // =================== MÉTODOS DE VISUALIZACIÓN ===================
    
    // Mostrar contenido del array
    void displayArray() const {
        std::cout << "\n=== CONTENIDO DEL ARRAY ===\n";
        std::cout << "Tamaño: " << arraySize << "/" << MAX_ARRAY_SIZE << std::endl;
        
        if (arraySize == 0) {
            std::cout << "Array vacío\n";
            return;
        }
        
        std::cout << "Valores: ";
        for (int i = 0; i < arraySize; ++i) {
            std::cout << std::fixed << std::setprecision(2) << arrFloat[i];
            if (i < arraySize - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }
    
    // Mostrar contenido del vector
    void displayVector() const {
        std::cout << "\n=== CONTENIDO DEL VECTOR ===\n";
        std::cout << "Tamaño: " << vectorFloat.size() << std::endl;
        
        if (vectorFloat.empty()) {
            std::cout << "Vector vacío\n";
            return;
        }
        
        std::cout << "Valores: ";
        for (size_t i = 0; i < vectorFloat.size(); ++i) {
            std::cout << std::fixed << std::setprecision(2) << vectorFloat[i];
            if (i < vectorFloat.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }
    
    // Mostrar ambos contenedores
    void displayBoth() const {
        displayArray();
        displayVector();
    }
    
    // =================== ESTADÍSTICAS ===================
    
    // Estadísticas del array
    void showArrayStatistics() const {
        if (arraySize == 0) {
            std::cout << "Array vacío - no hay estadísticas\n";
            return;
        }
        
        float sum = 0.0f;
        float minVal = arrFloat[0];
        float maxVal = arrFloat[0];
        
        for (int i = 0; i < arraySize; ++i) {
            sum += arrFloat[i];
            if (arrFloat[i] < minVal) minVal = arrFloat[i];
            if (arrFloat[i] > maxVal) maxVal = arrFloat[i];
        }
        
        float average = sum / arraySize;
        
        std::cout << "\n=== ESTADÍSTICAS DEL ARRAY ===\n";
        std::cout << "Elementos: " << arraySize << std::endl;
        std::cout << "Suma: " << sum << std::endl;
        std::cout << "Promedio: " << average << std::endl;
        std::cout << "Mínimo: " << minVal << std::endl;
        std::cout << "Máximo: " << maxVal << std::endl;
    }
    
    // Estadísticas del vector
    void showVectorStatistics() const {
        if (vectorFloat.empty()) {
            std::cout << "Vector vacío - no hay estadísticas\n";
            return;
        }
        
        float sum = std::accumulate(vectorFloat.begin(), vectorFloat.end(), 0.0f);
        float average = sum / vectorFloat.size();
        float minVal = *std::min_element(vectorFloat.begin(), vectorFloat.end());
        float maxVal = *std::max_element(vectorFloat.begin(), vectorFloat.end());
        
        std::cout << "\n=== ESTADÍSTICAS DEL VECTOR ===\n";
        std::cout << "Elementos: " << vectorFloat.size() << std::endl;
        std::cout << "Suma: " << sum << std::endl;
        std::cout << "Promedio: " << average << std::endl;
        std::cout << "Mínimo: " << minVal << std::endl;
        std::cout << "Máximo: " << maxVal << std::endl;
    }
    
    // Estadísticas combinadas
    void showCombinedStatistics() const {
        std::cout << "\n=== ESTADÍSTICAS COMBINADAS ===\n";
        showArrayStatistics();
        showVectorStatistics();
        
        // Comparación
        std::cout << "\n--- COMPARACIÓN ---\n";
        std::cout << "Total elementos: " << (arraySize + vectorFloat.size()) << std::endl;
        std::cout << "Array vs Vector: " << arraySize << " vs " << vectorFloat.size() << std::endl;
    }
    
    // =================== UTILIDADES ===================
    
    // Limpiar array
    void clearArray() {
        arraySize = 0;
        for (int i = 0; i < MAX_ARRAY_SIZE; ++i) {
            arrFloat[i] = 0.0f;
        }
        std::cout << "Array limpiado\n";
    }
    
    // Limpiar vector
    void clearVector() {
        vectorFloat.clear();
        std::cout << "Vector limpiado\n";
    }
    
    // Limpiar ambos
    void clearBoth() {
        clearArray();
        clearVector();
    }
    
    // Cargar desde archivo
    bool loadFromFile() {
        std::string combinedFileName = "combined_" + fileName;
        std::ifstream file(combinedFileName);
        
        if (!file.is_open()) {
            std::cout << "Archivo " << combinedFileName << " no encontrado. Iniciando repositorio vacío.\n";
            return false;
        }
        
        clearBoth();
        std::string line;
        bool readingArray = false;
        bool readingVector = false;
        
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') continue;
            
            if (line == "[ARRAY_DATA]") {
                readingArray = true;
                readingVector = false;
                continue;
            }
            
            if (line == "[VECTOR_DATA]") {
                readingArray = false;
                readingVector = true;
                continue;
            }
            
            float value;
            std::stringstream ss(line);
            if (ss >> value) {
                if (readingArray) {
                    addToArray(value);
                } else if (readingVector) {
                    addToVector(value);
                }
            }
        }
        
        file.close();
        std::cout << "Datos cargados desde " << combinedFileName << std::endl;
        std::cout << "Array: " << arraySize << " elementos, Vector: " << vectorFloat.size() << " elementos\n";
        return true;
    }
    
    // Getters
    int getArraySize() const { return arraySize; }
    size_t getVectorSize() const { return vectorFloat.size(); }
    bool isArrayEmpty() const { return arraySize == 0; }
    bool isVectorEmpty() const { return vectorFloat.empty(); }
    
    // Acceso a elementos
    float getArrayElement(int index) const {
        if (index >= 0 && index < arraySize) {
            return arrFloat[index];
        }
        throw std::out_of_range("Índice del array fuera de rango");
    }
    
    float getVectorElement(int index) const {
        if (index >= 0 && index < static_cast<int>(vectorFloat.size())) {
            return vectorFloat[index];
        }
        throw std::out_of_range("Índice del vector fuera de rango");
    }
};

// Función para mostrar menú
void showMenu() {
    std::cout << "\n=============== MENÚ REPOSITORIO DUAL ===============\n";
    std::cout << "GESTIÓN DE DATOS:\n";
    std::cout << "1.  Agregar valor al array\n";
    std::cout << "2.  Agregar valor al vector\n";
    std::cout << "3.  Agregar valor a ambos\n";
    std::cout << "4.  Agregar múltiples valores al array\n";
    std::cout << "5.  Agregar múltiples valores al vector\n";
    std::cout << "\nVISUALIZACIÓN:\n";
    std::cout << "6.  Mostrar array\n";
    std::cout << "7.  Mostrar vector\n";
    std::cout << "8.  Mostrar ambos\n";
    std::cout << "9.  Estadísticas combinadas\n";
    std::cout << "\nMÉTODOS SAVE:\n";
    std::cout << "10. Guardar todo (save)\n";
    std::cout << "11. Guardar solo array\n";
    std::cout << "12. Guardar solo vector\n";
    std::cout << "\nMÉTODOS GETAREA:\n";
    std::cout << "13. Calcular área del array\n";
    std::cout << "14. Calcular área del vector\n";
    std::cout << "15. Calcular área combinada\n";
    std::cout << "16. Área con espaciado personalizado\n";
    std::cout << "17. Área en rango específico\n";
    std::cout << "\nUTILIDADES:\n";
    std::cout << "18. Limpiar repositorio\n";
    std::cout << "19. Cargar desde archivo\n";
    std::cout << "0.  Salir\n";
    std::cout << "===================================================\n";
    std::cout << "Seleccione una opción: ";
}

int main() {
    DualFloatRepository repo("repositorio_dual.txt");
    
    // Datos de demostración
    std::cout << "=== DEMOSTRACIÓN DEL REPOSITORIO DUAL ===\n\n";
    
    // Agregar datos de ejemplo
    std::vector<float> ejemplosArray = {1.0f, 2.5f, 4.0f, 3.2f, 5.8f};
    std::vector<float> ejemplosVector = {0.5f, 1.8f, 3.3f, 4.7f, 2.1f, 6.2f};
    
    std::cout << "Agregando datos de ejemplo...\n";
    repo.addArrayValues(ejemplosArray);
    repo.addVectorValues(ejemplosVector);
    
    // Mostrar datos iniciales
    repo.displayBoth();
    
    // Calcular áreas
    std::cout << "\n=== CÁLCULOS DE ÁREA ===\n";
    repo.getAreaArray();
    repo.getAreaVector();
    repo.getAreaCombined();
    
    // Guardar datos
    std::cout << "\n=== GUARDANDO DATOS ===\n";
    repo.save();
    
    // Menú interactivo
    int option;
    do {
        showMenu();
        std::cin >> option;
        
        switch (option) {
            case 1: {
                float valor;
                std::cout << "Ingrese valor para el array: ";
                std::cin >> valor;
                repo.addToArray(valor);
                break;
            }
            case 2: {
                float valor;
                std::cout << "Ingrese valor para el vector: ";
                std::cin >> valor;
                repo.addToVector(valor);
                break;
            }
            case 3: {
                float valor;
                std::cout << "Ingrese valor para ambos contenedores: ";
                std::cin >> valor;
                repo.addToBoth(valor);
                break;
            }
            case 4: {
                int n;
                std::cout << "¿Cuántos valores para el array? ";
                std::cin >> n;
                std::vector<float> valores(n);
                std::cout << "Ingrese los valores:\n";
                for (int i = 0; i < n; ++i) {
                    std::cout << "Valor " << (i+1) << ": ";
                    std::cin >> valores[i];
                }
                repo.addArrayValues(valores);
                break;
            }
            case 5: {
                int n;
                std::cout << "¿Cuántos valores para el vector? ";
                std::cin >> n;
                std::vector<float> valores(n);
                std::cout << "Ingrese los valores:\n";
                for (int i = 0; i < n; ++i) {
                    std::cout << "Valor " << (i+1) << ": ";
                    std::cin >> valores[i];
                }
                repo.addVectorValues(valores);
                break;
            }
            case 6:
                repo.displayArray();
                break;
            case 7:
                repo.displayVector();
                break;
            case 8:
                repo.displayBoth();
                break;
            case 9:
                repo.showCombinedStatistics();
                break;
            case 10:
                repo.save();
                break;
            case 11:
                repo.saveArray();
                break;
            case 12:
                repo.saveVector();
                break;
            case 13:
                repo.getAreaArray();
                break;
            case 14:
                repo.getAreaVector();
                break;
            case 15:
                repo.getAreaCombined();
                break;
            case 16: {
                float dx;
                int tipo;
                std::cout << "Seleccione contenedor (1=Array, 2=Vector): ";
                std::cin >> tipo;
                std::cout << "Ingrese espaciado (deltaX): ";
                std::cin >> dx;
                if (tipo == 1) {
                    repo.getAreaArray(dx);
                } else if (tipo == 2) {
                    repo.getAreaVector(dx);
                }
                break;
            }
            case 17: {
                int tipo, start, end;
                float dx;
                std::cout << "Seleccione contenedor (1=Array, 2=Vector): ";
                std::cin >> tipo;
                std::cout << "Índice inicial: ";
                std::cin >> start;
                std::cout << "Índice final: ";
                std::cin >> end;
                std::cout << "Espaciado (deltaX): ";
                std::cin >> dx;
                if (tipo == 1) {
                    repo.getAreaArrayRange(start, end, dx);
                } else if (tipo == 2) {
                    repo.getAreaVectorRange(start, end, dx);
                }
                break;
            }
            case 18:
                repo.clearBoth();
                break;
            case 19:
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
