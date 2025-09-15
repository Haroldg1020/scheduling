#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#define MAX_TIME 100 // Tiempo máximo de simulación
#define file_path "Examples/example2.txt"

int main() {
    // Abrir el archivo de entrada
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Cannot open input file: " << file_path << std::endl;
        return 1;
    }
    std::string line;
    std::vector<std::vector<std::string>> data;

    // Extraer y parsear cada línea separada por ';'
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;
        while (std::getline(ss, token, ';')) {
            // Eliminar posibles espacios iniciales
            if (!token.empty() && token[0] == ' ') token.erase(0, 1);
            tokens.push_back(token);
        }
        if (!tokens.empty()) data.push_back(tokens);
    }
    file.close();

    // Tiempos restantes y arrival times por índice de proceso
    std::vector<int> rem(data.size(), 0);
    std::vector<int> at(data.size(), 0);
    for (size_t i = 0; i < data.size(); ++i) {
        if (data[i].size() > 1) rem[i] = std::stoi(data[i][1]);
        if (data[i].size() > 2) at[i] = std::stoi(data[i][2]);
    }

    unsigned int time = 0;
    int current = -1; // índice del proceso en ejecución, -1 si idle
    std::cout << "|";

    while (true) {
        // Elegir candidato: proceso con rem>0 y at <= time que tenga menor remaining
        int candidate = -1;
        for (size_t i = 0; i < data.size(); ++i) {
            if (rem[i] > 0 && at[i] <= (int)time) {
                if (candidate == -1 || rem[i] < rem[candidate]) candidate = (int)i;
            }
        }

        // Si cambia el proceso en ejecución, cerrar la porción anterior y abrir la nueva
        if (candidate != current) {
            if (current != -1) {
                // cerrar porción del proceso anterior
                std::cout << "|";
            }
            current = candidate;
            if (current != -1) {
                // abrir porción del nuevo proceso
                std::cout << "|";
            }
        }

        if (current == -1) {
            // CPU idle: imprimir guion
            std::cout << "-";
        } else {
            // Ejecutar una unidad del proceso seleccionado
            std::cout << data[current][0];
            rem[current]--;
            // Si terminó, cerrar porción y marcar idle
            if (rem[current] <= 0) {
                std::cout << "|";
                current = -1;
            }
        }

        time++;

        // Condición de terminación: todos los procesos terminaron
        bool all_done = true;
        for (size_t i = 0; i < rem.size(); ++i) if (rem[i] > 0) { all_done = false; break; }
        if (all_done) break;

        if (time > MAX_TIME) break;
    }

    // Cerrar diagrama
    std::cout << "|" << std::endl;
    return 0;
}