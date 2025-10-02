// main.cpp
#include "BibliotecaDB.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    BibliotecaDB biblioteca;
    
    // Cargar datos al iniciar
    biblioteca.cargarDatos();
    
    int opcion;
    while (true) {
        cout << "\n=== SISTEMA DE GESTION DE BIBLIOTECA ===" << endl;
        cout << "1. Gestion de Libros" << endl;
        cout << "2. Gestion de Autores" << endl;
        cout << "3. Gestion de Estudiantes" << endl;
        cout << "4. Gestion de Prestamos" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opcion: ";
        
        while (!(cin >> opcion)) {
            cout << "Error: Ingrese un numero valido: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        switch (opcion) {
            case 1:
                biblioteca.menuLibros();
                break;
            case 2:
                biblioteca.menuAutores();
                break;
            case 3:
                biblioteca.menuEstudiantes();
                break;
            case 4:
                biblioteca.menuPrestamos();
                break;
            case 0:
                // Guardar datos antes de salir
                biblioteca.guardarDatos();
                cout << "Datos guardados. Hasta luego!" << endl;
                return 0;
            default:
                cout << "Opción invalida. Intente nuevamente." << endl;
        }
    }
    
    return 0;
}