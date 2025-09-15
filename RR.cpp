#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#define MAX_TIME 100 // Tiempo máximo de simulación
#define file_path "Examples/example2.txt"

int main(int argc, char** argv) {
    // Quantum configurable via primer argumento; por defecto 4
    int quantum = 4;
    if (argc > 1) {
        try { quantum = std::max(1, std::stoi(argv[1])); } catch(...) { quantum = 4; }
    }

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

    // Tiempos restantes por índice de proceso
    std::vector<int> rem(data.size(), 0);
    for (size_t i = 0; i < data.size(); ++i) {
        if (data[i].size() > 1) rem[i] = std::stoi(data[i][1]);
    }

    unsigned int time = 0;
    std::vector<int> queue; // Cola ready que almacena índices a data
    std::cout << "|";

    int slice_elapsed = 0; // tiempo consumido en la porción actual (<= quantum)
    // Si hay un proceso en ejecución, su índice será queue[0]
    while (true) {
        // Añadir procesos que llegan en este instante al final de la cola
        for (size_t i = 0; i < data.size(); ++i) {
            if (data[i].size() > 2 && std::stoi(data[i][2]) == (int)time) {
                queue.push_back((int)i);
            }
        }

        // Si hay procesos listos, ejecutar siguiendo Round Robin
        if (!queue.empty()) {
            // Si empezamos una nueva porción (slice), imprimir borde izquierdo
            if (slice_elapsed == 0) std::cout << "|";

            int cur = queue[0];
            // Ejecutar una unidad del proceso actual
            std::cout << data[cur][0];
            rem[cur]--;
            slice_elapsed++;

            // Si el proceso terminó completamente, cerramos la porción y lo removemos de la cola
            if (rem[cur] <= 0) {
                std::cout << "|";
                queue.erase(queue.begin());
                slice_elapsed = 0;
            } else if (slice_elapsed == quantum) {
                // expiró el quantum: mover el proceso al final de la cola
                std::cout << "|";
                queue.erase(queue.begin());
                queue.push_back(cur);
                slice_elapsed = 0;
            }
        } else {
            // CPU idle: imprimir guion
            std::cout << "-";
        }

        time++;

        // Terminar si todos los procesos finalizaron
        bool all_done = true;
        for (size_t i = 0; i < rem.size(); ++i) if (rem[i] > 0) { all_done = false; break; }
        if (all_done) break;

        if (time > MAX_TIME) break;
    }

    // Cerrar diagrama
    std::cout << "|" << std::endl;
    return 0;
}