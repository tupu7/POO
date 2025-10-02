// BibliotecaDB.h
#ifndef BIBLIOTECADB_H
#define BIBLIOTECADB_H

#include <vector>
#include <string>

using namespace std;

struct Libro {
    int ID_Libro;
    string Titulo;
    string ISBN;
    int AnoPublicacion;
    int ID_Autor;
    bool Disponible;
};

struct Autor {
    int ID_Autor;
    string Nombre;
    string Nacionalidad;
};

struct Estudiante {
    int ID_Estudiante;
    string Nombre;
    string Grado;
};

struct Prestamo {
    int ID_Prestamo;
    int ID_Libro;
    int ID_Estudiante;
    string FechaPrestamo;
    string FechaDevolucion;
};

class BibliotecaDB {
public:
    vector<Libro> libros;
    vector<Autor> autores;
    vector<Estudiante> estudiantes;
    vector<Prestamo> prestamos;

private:
    // Generadores automaticos
    int generarIDLibro();
    int generarIDAutor();
    int generarIDEstudiante();
    int generarIDPrestamo();
    string generarISBN();

    // Validaciones
    bool autorExiste(int ID_Autor);
    bool libroExiste(int ID_Libro);
    bool estudianteExiste(int ID_Estudiante);
    bool libroDisponible(int ID_Libro);
    string obtenerFechaActual();

public:
    // Persistencia
    void cargarDatos();
    void guardarDatos();

    // CRUD Libros
    void agregarLibro();
    void listarLibros();
    void actualizarLibro();
    void eliminarLibro();
    void buscarLibroPorTituloOISBN();
    void consultarLibrosPorRangoAnos();  // Consulta para Libros

    // CRUD Autores
    void agregarAutor();
    void listarAutores();
    void actualizarAutor();
    void eliminarAutor();
    void consultarAutoresConMasLibros();  // Consulta para Autores

    // CRUD Estudiantes
    void agregarEstudiante();
    void listarEstudiantes();
    void actualizarEstudiante();
    void eliminarEstudiante();
    void consultarEstudianteConMasPrestamos();  // Consulta para Estudiantes

    // CRUD Prestamos
    void agregarPrestamo();
    void listarPrestamos();
    void actualizarPrestamo();
    void eliminarPrestamo();
    void buscarPrestamosPorEstudiante();
    void consultarDiasConMasPrestamos();  // Consulta para Prestamos

    // Submenus
    void menuLibros();
    void menuAutores();
    void menuEstudiantes();
    void menuPrestamos();
};

#endif