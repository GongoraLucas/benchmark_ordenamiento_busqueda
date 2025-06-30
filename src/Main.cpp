#include <iostream>
#include <limits>
#include <chrono>
#include <locale.h>
#include <cstdlib>
#include <iomanip>  // <--- NUEVO: para setprecision

#include "GeneradorArreglos.hpp"
#include "Quicksort.hpp"
#include "ShellSort.hpp"
#include "BucketSort.hpp"
#include "RadixSort.hpp"
#include "MezclaNatural.hpp"
#include "MezclaDirecta.hpp"
#include "BusquedaSecuencial.hpp"
#include "BusquedaBinaria.hpp"
#include "TablasHash.hpp"

using namespace std;


void verificarLongitudPromedio(float longitudPromedio, int tamTabla) {
    if (longitudPromedio < 1.0f) {
        cout << "Advertencia: La longitud promedio de listas en la Tabla Hash es muy baja ("
             << fixed << setprecision(3) << longitudPromedio
             << "). Considera reducir el tamaño de la tabla hash (actual: " << tamTabla << ") para mejor aprovechamiento.\n";
    }
}

void compararBusquedasCompleto(int arreglo[], int tam) {
    int posiciones[] = {0, tam / 2, tam - 1};
    const char* descripciones[] = {"INICIO", "MITAD", "FINAL"};

    for (int i = 0; i < 3; i++) {
        int valorBuscar = arreglo[posiciones[i]];

        cout << "\n==== CASO: Valor en la " << descripciones[i] << " ====\n";

        BusquedaSecuencial<int> bs(arreglo, tam);
        bs.ejecutar(valorBuscar);
        cout << "\nBúsqueda Secuencial (valor: " << valorBuscar << ")\n";
        bs.mostrarResultados();

        BusquedaBinaria<int> bb(arreglo, tam);
        bb.ejecutar(valorBuscar);
        cout << "\nBúsqueda Binaria (valor: " << valorBuscar << ")\n";
        bb.mostrarResultados();

        TablaHash<int> th(arreglo, tam, 100);
        th.ejecutar(valorBuscar);
        cout << "\nTabla Hash (valor: " << valorBuscar << ")\n";
        th.mostrarResultados();

        // Verificación agregada:
        verificarLongitudPromedio(th.longitudPromedio, 100);
    }
}

void compararOrdenamientos(int original[], int tam, int repeticiones=10000) {
    QuickSort<int> qCentral(original, tam, 0);
    qCentral.ejecutar(repeticiones);
    cout << "\nQuickSort - Pivote Central\n";
    qCentral.mostrarResultados();

    QuickSort<int> qInicial(original, tam, -1);
    qInicial.ejecutar(repeticiones);
    cout << "\nQuickSort - Pivote Inicial\n";
    qInicial.mostrarResultados();

    QuickSort<int> qFinal(original, tam, 1);
    qFinal.ejecutar(repeticiones);
    cout << "\nQuickSort - Pivote Final\n";
    qFinal.mostrarResultados();

    QuickSort<int> qAleatorio(original, tam, 2);
    qAleatorio.ejecutar(repeticiones);
    cout << "\nQuickSort - Pivote Aleatorio\n";
    qAleatorio.mostrarResultados();

    ShellSort<int> shell(original, tam);
    shell.ejecutar(repeticiones);
    cout << "\nShellSort\n";
    shell.mostrarResultados();

    BucketSort<int> bucketIns(original, tam, 10, 0);
    bucketIns.ejecutar(repeticiones);
    cout << "\nBucketSort - InsertionSort\n";
    bucketIns.mostrarResultados();

    BucketSort<int> bucketBubble(original, tam, 10, 1);
    bucketBubble.ejecutar(repeticiones);
    cout << "\nBucketSort - BubbleSort\n";
    bucketBubble.mostrarResultados();

    RadixSort<int> radix(original, tam);
    radix.ejecutar(repeticiones);
    cout << "\nRadixSort\n";
    radix.mostrarResultados();

    MezclaNatural<int> mezclaNat(original, tam);
    mezclaNat.ejecutar(repeticiones);
    cout << "\nMezcla Natural\n";
    mezclaNat.mostrarResultados();

    MezclaDirecta<int> mezclaDir(original, tam);
    mezclaDir.ejecutar(repeticiones);
    cout << "\nMezcla Directa\n";
    mezclaDir.mostrarResultados();
}

void compararTodo(int tam, int tipoArreglo) {
    cout << "\n\t========= Comparación para tamaño " << tam << " y tipo de arreglo: ";
    if (tipoArreglo == 0) cout << "Aleatorio ======\t\n";
    else if (tipoArreglo == 1) cout << "Casi ordenado =====\t\n";
    else if (tipoArreglo == 2) cout << "Reverso ======\t\n";

    GeneradorArreglos<int> generador(tam, tipoArreglo);
    int* original = generador.obtenerArreglo();

    cout << "\n=============== ORDENAMIENTOS ===============\n";
    if (tam >= 10000){
        compararOrdenamientos(original, tam, 1);
    }else{
         compararOrdenamientos(original, tam);
    }


    cout << "\n=============== BÚSQUEDAS ===================\n";
    compararBusquedasCompleto(original, tam);

    delete[] original;
}

void mostrarMenu() {
    cout << "\n========== MENÚ PRINCIPAL ==========" << endl;
    cout << "1. Comparar todos los algoritmos (100 elementos)" << endl;
    cout << "2. Comparar todos los algoritmos (1000 elementos)" << endl;
    cout << "3. Comparar todos los algoritmos (10000 elementos)" << endl;
    cout << "4. Salir" << endl;
    cout << "Seleccione una opción: ";
}

int main() {
    setlocale(LC_ALL, "");
    int opcion;
    srand(time(0));

    do {
        mostrarMenu();
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (opcion) {
            case 1:
                for (int tipo = 0; tipo < 3; tipo++) compararTodo(100, tipo);
                break;
            case 2:
                for (int tipo = 0; tipo < 3; tipo++) compararTodo(1000, tipo);
                break;
            case 3:
                for (int tipo = 0; tipo < 3; tipo++) compararTodo(10000, tipo);
                break;
            case 4:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opción inválida. Intente nuevamente.\n";
        }

    } while (opcion != 4);

    return 0;
}
