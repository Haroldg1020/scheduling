#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#define MAX_TIME 100 // Tiempo máximo de simulación
#define file_path "Examples/example2.txt"

int main() {

    // Abrir el archivo
    std::ifstream file(file_path);
    std::string line;
    std::vector<std::vector<std::string>> data;

    // Extraer datos línea por línea
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;

        // Separa por "; "
        while (std::getline(ss, token, ';')) {
            // Eliminar posibles espacios iniciales
            if (!token.empty() && token[0] == ' ') {
                token.erase(0, 1);
            }
            tokens.push_back(token);
        }
        data.push_back(tokens);
    }
    file.close();

    unsigned int time = 0;
    int burst_time = 0;
    std::vector<std::vector<std::string>> queue;


    std::cout << "|";
    while(1) {
        //Adiciono los procesos a la cola
        if(data.size() > 0) {
            for(unsigned int i = 0; i < data.size(); i++) {
                if(std::stoi(data[i][2]) == time) {
                    queue.push_back(data[i]);
                }
            }
        }
        //Ejecuto los procesos en la cola
        if(queue.size() > 0) {
            if(burst_time == 0){
                // Imprimir el borde izquierdo del proceso
                std::cout << "|";
            }
            burst_time++;
            std::cout << queue[0][0];
            if(burst_time == std::stoi(queue[0][1])) {
                burst_time = 0;
                queue.erase(queue.begin());
                std::cout << "|";
            }
        } else {
            // Si no hay procesos en la cola, imprimir un guion
            std::cout << "-";
        }
        time++;
        if(time > MAX_TIME) {
            break;
        }
    }
    // Finalizo la impresión del diagrama
    std::cout << "|" << std::endl;
    return 0;
}