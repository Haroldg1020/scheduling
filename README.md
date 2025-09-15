# Scheduling Algorithms: FCFS, SJF, RR & STCF

Este proyecto implementa varios algoritmos de planificación de procesos (scheduling):

- FCFS (First Come, First Served)  
- SJF (Shortest Job First, no expropiativo)  
- RR (Round Robin, con quantum configurable)  
- STCF / PSJF (Shortest Time‑to‑Completion First — preemptive SJF)

## Breve explicación de cada algoritmo

- FCFS: los procesos se sirven en estricto orden de llegada (arrival time). No hay expropiación: un proceso que comienza a ejecutarse lo hace hasta completar su burst time. Sencillo y justo por orden temporal, pero puede provocar tiempos de espera largos para procesos cortos si llegan detrás de procesos largos.

- SJF (no expropiativo): entre los procesos que ya han llegado se selecciona el que tiene menor burst time total. Una vez seleccionado, se ejecuta hasta completarse. Minimiza el tiempo medio de espera en escenarios ideales, pero requiere conocer o estimar el burst time y puede causar inanición de procesos largos.

- RR (Round Robin): cada proceso recibe un quantum configurable de CPU; si no finaliza en ese quantum se reencola al final de la ready. Es preemptivo por diseño y produce tiempos de respuesta razonables.

- STCF / PSJF: versión expropiativa de SJF. En cada unidad de tiempo se ejecuta el proceso con menor tiempo restante (remaining time) entre los ya llegados; si llega uno con remaining menor se preemite inmediatamente. Ofrece buena latencia para procesos cortos.

## Estructura del proyecto

```
scheduling/
│
├── Examples/           # Archivos de prueba con procesos
│   ├── example1.txt
│   ├── example2.txt
│   ├── example3.txt
│   └── example4.txt
│
├── FCFS.cpp            # Implementación FCFS
├── SJF.cpp             # Implementación SJF (no expropiativo)
├── RR.cpp              # Implementación Round Robin (quantum configurable)
└── STCF.cpp            # Implementación Shortest Time‑to‑Completion First (preemptivo)
```

## Formato de los archivos de entrada

Cada línea tiene el formato:
ID; BT; AT; Q; PR

- ID: etiqueta del proceso (ej. A)  
- BT: burst time (duración total)  
- AT: arrival time (tiempo de llegada)  
- Q: queue / cola 
- PR: prioridad (mayor número = mayor prioridad, si aplica)

Ejemplo (Examples/example2.txt):
```
A; 5; 0; 1; 3
B; 12; 2; 1; 4
C; 7; 4; 2; 2
D; 20; 6; 2; 5
E; 9; 8; 3; 1
```

## Compilación y ejecución

Compilar:

```bash
g++ FCFS.cpp -o fcfs
g++ SJF.cpp -o sjf
g++ RR.cpp  -o rr
g++ STCF.cpp -o stcf
```

Ejecutar (usa el archivo por defecto definido en los fuentes: Examples/example2.txt):

- FCFS / SJF / STCF:
  - Linux/macOS: ./fcfs  ./sjf  ./stcf
  - Windows:     fcfs.exe  sjf.exe  stcf.exe

- RR (quantum configurable):
  - Linux/macOS: ./rr 4    (quantum = 4)
  - Windows:     rr.exe 4

## Notas

- Los fuentes imprimen un diagrama sencillo: '|' marca límites de porciones (inicio/fin de ejecución de un proceso) y '-' indica CPU idle.
