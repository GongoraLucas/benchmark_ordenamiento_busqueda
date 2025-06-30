#ifndef MEZCLANATURAL_HPP
#define MEZCLANATURAL_HPP

#include <iostream>
#include <chrono>
using namespace std;

template<typename T>
struct MezclaNatural {
private:
    T* arreglo;
    int tam;
    int comparaciones;
    int asignaciones;
    int runsDetectados;
    std::chrono::milliseconds tiempoEjecucion;

    void dividirEnRuns(T* F1, int& tamF1, T* F2, int& tamF2) {
        bool alternar = true;
        tamF1 = 0;
        tamF2 = 0;
        runsDetectados = 0;

        T anterior = arreglo[0];
        if (alternar) F1[tamF1++] = anterior;
        else F2[tamF2++] = anterior;

        for (int i = 1; i < tam; i++) {
            comparaciones++;
            if (arreglo[i] < anterior) {
                alternar = !alternar;
                runsDetectados++;
            }

            if (alternar) {
                F1[tamF1++] = arreglo[i];
            } else {
                F2[tamF2++] = arreglo[i];
            }

            anterior = arreglo[i];
        }

        runsDetectados++;
    }

    void fusionarRuns(T* F1, int tamF1, T* F2, int tamF2) {
        T* resultado = new T[tam];
        int i = 0, j = 0, k = 0;

        while (i < tamF1 && j < tamF2) {
            comparaciones++;
            if (F1[i] <= F2[j]) {
                resultado[k++] = F1[i++];
            } else {
                resultado[k++] = F2[j++];
            }
            asignaciones++;
        }

        while (i < tamF1) {
            resultado[k++] = F1[i++];
            asignaciones++;
        }

        while (j < tamF2) {
            resultado[k++] = F2[j++];
            asignaciones++;
        }

        for (int m = 0; m < tam; m++) {
            arreglo[m] = resultado[m];
            asignaciones++;
        }

        delete[] resultado;
    }

    void sort() {
        bool terminado = false;

        T* F1 = new T[tam];
        T* F2 = new T[tam];
        int tamF1 = 0, tamF2 = 0;

        while (!terminado) {
            dividirEnRuns(F1, tamF1, F2, tamF2);

            if (tamF2 == 0) {
                terminado = true;
            } else {
                fusionarRuns(F1, tamF1, F2, tamF2);
            }
        }

        delete[] F1;
        delete[] F2;
    }

public:
    MezclaNatural(T* datos, int t)
        : tam(t), comparaciones(0), asignaciones(0), runsDetectados(0) {
        arreglo = new T[tam];
        for (int i = 0; i < tam; i++) {
            arreglo[i] = datos[i];
        }
    }

    ~MezclaNatural() {
        delete[] arreglo;
    }

    void ejecutar(int repeticiones = 1000) {
        comparaciones = 0;
        asignaciones = 0;
        runsDetectados = 0;

        int comparacionesReal = 0;
        int asignacionesReal = 0;
        int runsDetectadosReal = 0;


        auto inicio = chrono::high_resolution_clock::now();

        for (int r = 0; r < repeticiones; r++) {
            sort();
            if (r == 0){
                comparacionesReal = comparaciones;
                asignacionesReal = asignaciones;
                runsDetectadosReal  = runsDetectados;
            }

        }

        auto fin = chrono::high_resolution_clock::now();
        tiempoEjecucion = chrono::duration_cast<chrono::milliseconds>(fin - inicio);

        comparaciones = comparacionesReal;
        asignaciones = asignacionesReal;
        runsDetectados = runsDetectadosReal;
    }

    void mostrarResultados() const {
        cout << "Comparaciones: " << comparaciones << endl;
        cout << "Asignaciones: " << asignaciones << endl;
        cout << "Runs detectados: " << runsDetectados << endl;
        cout << "Tiempo de ejecución: " << tiempoEjecucion.count() << " milisegundos" << endl;
    }
};

#endif // MEZCLANATURAL_HPP
