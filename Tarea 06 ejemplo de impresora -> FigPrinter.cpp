#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

class FigPrinter {
private:
    // Mapa de caracteres ASCII art (5x7)
    std::map<char, std::vector<std::string>> charMap;
    
    void initializeCharMap() {
        // Letra A
        charMap['A'] = {
            "  ###  ",
            " #   # ",
            "#     #",
            "#######",
            "#     #",
            "#     #",
            "       "
        };
        
        // Letra B
        charMap['B'] = {
            "######ă",
            "#     #",
            "######ă",
            "######ă",
            "#     #",
            "######ă",
            "       "
        };
        
        // Letra C
        charMap['C'] = {
            " ##### ",
            "#     #",
            "#      ",
            "#      ",
            "#     #",
            " ##### ",
            "       "
        };
        
        // Letra D
        charMap['D'] = {
            "######ă",
            "#     #",
            "#     #",
            "#     #",
            "#     #",
            "######ă",
            "       "
        };
        
        // Letra E
        charMap['E'] = {
            "#######",
            "#      ",
            "####   ",
            "####   ",
            "#      ",
            "#######",
            "       "
        };
        
        // Letra H
        charMap['H'] = {
            "#     #",
            "#     #",
            "#######",
            "#######",
            "#     #",
            "#     #",
            "       "
        };
        
        // Letra L
        charMap['L'] = {
            "#      ",
            "#      ",
            "#      ",
            "#      ",
            "#      ",
            "#######",
            "       "
        };
        
        // Letra O
        charMap['O'] = {
            " ##### ",
            "#     #",
            "#     #",
            "#     #",
            "#     #",
            " ##### ",
            "       "
        };
        
        // Letra R
        charMap['R'] = {
            "######ă",
            "#     #",
            "######ă",
            "# #    ",
            "#  #   ",
            "#   #  ",
            "       "
        };
        
        // Espacio
        charMap[' '] = {
            "   ",
            "   ",
            "   ",
            "   ",
            "   ",
            "   ",
            "   "
        };
        
        // Caracter desconocido
        charMap['?'] = {
            " ##### ",
            "#     #",
            "    ## ",
            "   ##  ",
            "       ",
            "  ##   ",
            "       "
        };
    }
    
public:
    FigPrinter() {
        initializeCharMap();
    }
    
    void printText(const std::string& text) {
        if (text.empty()) return;
        
        // Convertir a mayúsculas
        std::string upperText = text;
        std::transform(upperText.begin(), upperText.end(), upperText.begin(), ::toupper);
        
        // Imprimir línea por línea
        for (int line = 0; line < 7; line++) {
            for (char c : upperText) {
                if (charMap.find(c) != charMap.end()) {
                    std::cout << charMap[c][line];
                } else {
                    std::cout << charMap['?'][line];
                }
            }
            std::cout << std::endl;
        }
    }
    
    void printBanner(const std::string& text, char borderChar = '*') {
        std::string upperText = text;
        std::transform(upperText.begin(), upperText.end(), upperText.begin(), ::toupper);
        
        // Calcular ancho del banner
        int width = 0;
        for (char c : upperText) {
            if (charMap.find(c) != charMap.end()) {
                width += charMap[c][0].length();
            } else {
                width += charMap['?'][0].length();
            }
        }
        
        // Imprimir borde superior
        std::cout << std::string(width + 4, borderChar) << std::endl;
        
        // Imprimir texto con bordes laterales
        for (int line = 0; line < 7; line++) {
            std::cout << borderChar << " ";
            for (char c : upperText) {
                if (charMap.find(c) != charMap.end()) {
                    std::cout << charMap[c][line];
                } else {
                    std::cout << charMap['?'][line];
                }
            }
            std::cout << " " << borderChar << std::endl;
        }
        
        // Imprimir borde inferior
        std::cout << std::string(width + 4, borderChar) << std::endl;
    }
    
    void printCentered(const std::string& text, int totalWidth = 80) {
        std::string upperText = text;
        std::transform(upperText.begin(), upperText.end(), upperText.begin(), ::toupper);
        
        // Calcular ancho del texto
        int textWidth = 0;
        for (char c : upperText) {
            if (charMap.find(c) != charMap.end()) {
                textWidth += charMap[c][0].length();
            } else {
                textWidth += charMap['?'][0].length();
            }
        }
        
        int padding = (totalWidth - textWidth) / 2;
        if (padding < 0) padding = 0;
        
        // Imprimir línea por línea centrado
        for (int line = 0; line < 7; line++) {
            std::cout << std::string(padding, ' ');
            for (char c : upperText) {
                if (charMap.find(c) != charMap.end()) {
                    std::cout << charMap[c][line];
                } else {
                    std::cout << charMap['?'][line];
                }
            }
            std::cout << std::endl;
        }
    }
    
    void addCustomChar(char ch, const std::vector<std::string>& pattern) {
        if (pattern.size() == 7) {
            charMap[ch] = pattern;
        }
    }
};

// Función de demostración
int main() {
    FigPrinter printer;
    
    std::cout << "=== DEMO FigPrinter ===" << std::endl << std::endl;
    
    // Texto simple
    std::cout << "Texto simple:" << std::endl;
    printer.printText("HELLO");
    std::cout << std::endl;
    
    // Banner con borde
    std::cout << "Banner con borde:" << std::endl;
    printer.printBanner("C++", '#');
    std::cout << std::endl;
    
    // Texto centrado
    std::cout << "Texto centrado:" << std::endl;
    printer.printCentered("CODE", 60);
    std::cout << std::endl;
    
    // Agregar caracter personalizado
    std::vector<std::string> customPattern = {
        "   #   ",
        "  ###  ",
        " ##### ",
        "#######",
        " ##### ",
        "  ###  ",
        "   #   "
    };
    printer.addCustomChar('@', customPattern);
    
    std::cout << "Caracter personalizado:" << std::endl;
    printer.printText("@");
    
    return 0;
}
