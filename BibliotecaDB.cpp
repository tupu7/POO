// BibliotecaDB.cpp
#include "BibliotecaDB.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <ctime>
#include <random>
#include <algorithm>
#include <cctype>

using namespace std;

// =============================================
// IMPLEMENTACION DE VALIDACIONES
// =============================================

// Verifica si un autor existe por su ID
bool BibliotecaDB::autorExiste(int ID_Autor) {
    for (const auto& autor : autores) {
        if (autor.ID_Autor == ID_Autor) return true;
    }
    return false;
}

// Verifica si un libro existe por su ID
bool BibliotecaDB::libroExiste(int ID_Libro) {
    for (const auto& libro : libros) {
        if (libro.ID_Libro == ID_Libro) return true;
    }
    return false;
}

// Verifica si un estudiante existe por su ID
bool BibliotecaDB::estudianteExiste(int ID_Estudiante) {
    for (const auto& est : estudiantes) {
        if (est.ID_Estudiante == ID_Estudiante) return true;
    }
    return false;
}

// Verifica si un libro esta disponible para prestamo
bool BibliotecaDB::libroDisponible(int ID_Libro) {
    for (const auto& libro : libros) {
        if (libro.ID_Libro == ID_Libro) return libro.Disponible;
    }
    return false;
}

// Obtiene la fecha actual en formato YYYY-MM-DD
string BibliotecaDB::obtenerFechaActual() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << (1900 + ltm->tm_year) << "-" 
       << (1 + ltm->tm_mon) << "-" 
       << ltm->tm_mday;
    return ss.str();
}

// =============================================
// GENERADORES AUTOMATICOS DE IDs
// =============================================

// Genera un nuevo ID para libro buscando el maximo actual y sumando 1
int BibliotecaDB::generarIDLibro() {
    int ultimoID = 0;
    for (const auto& libro : libros) {
        if (libro.ID_Libro > ultimoID) {
            ultimoID = libro.ID_Libro;
        }
    }
    return ultimoID + 1;
}

// Genera un nuevo ID para autor
int BibliotecaDB::generarIDAutor() {
    int ultimoID = 0;
    for (const auto& autor : autores) {
        if (autor.ID_Autor > ultimoID) {
            ultimoID = autor.ID_Autor;
        }
    }
    return ultimoID + 1;
}

// Genera un nuevo ID para estudiante
int BibliotecaDB::generarIDEstudiante() {
    int ultimoID = 0;
    for (const auto& estudiante : estudiantes) {
        if (estudiante.ID_Estudiante > ultimoID) {
            ultimoID = estudiante.ID_Estudiante;
        }
    }
    return ultimoID + 1;
}

// Genera un nuevo ID para prestamo
int BibliotecaDB::generarIDPrestamo() {
    int ultimoID = 0;
    for (const auto& prestamo : prestamos) {
        if (prestamo.ID_Prestamo > ultimoID) {
            ultimoID = prestamo.ID_Prestamo;
        }
    }
    return ultimoID + 1;
}

// Genera un ISBN aleatorio unico en formato 978-XXX-XX-XXXXXX-X
string BibliotecaDB::generarISBN() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 9);
    
    stringstream ss;
    ss << "978-";
    for (int i = 0; i < 3; i++) {
        ss << dis(gen);
    }
    ss << "-";
    for (int i = 0; i < 2; i++) {
        ss << dis(gen);
    }
    ss << "-";
    for (int i = 0; i < 6; i++) {
        ss << dis(gen);
    }
    ss << "-";
    ss << dis(gen);
    
    return ss.str();
}

// =============================================
// PERSISTENCIA DE DATOS
// =============================================

// Carga los datos desde archivos de texto
void BibliotecaDB::cargarDatos() {
    // Cargar libros desde libros.txt
    ifstream fileLibros("libros.txt");
    if (fileLibros.is_open()) {
        string line;
        bool primeraLinea = true;
        while (getline(fileLibros, line)) {
            if (primeraLinea) {
                primeraLinea = false;
                continue; // Saltar encabezado
            }
            try {
                stringstream ss(line);
                Libro l;
                string temp;
                getline(ss, temp, ','); l.ID_Libro = stoi(temp);
                getline(ss, l.Titulo, ',');
                getline(ss, l.ISBN, ',');
                getline(ss, temp, ','); l.AnoPublicacion = stoi(temp);
                getline(ss, temp, ','); l.ID_Autor = stoi(temp);
                getline(ss, temp, ','); l.Disponible = (temp == "1");
                libros.push_back(l);
            } catch (const exception& e) {
                cout << "Error al leer linea de libros.txt: " << line << endl;
            }
        }
        fileLibros.close();
    }

    // Cargar autores desde autores.txt
    ifstream fileAutores("autores.txt");
    if (fileAutores.is_open()) {
        string line;
        bool primeraLinea = true;
        while (getline(fileAutores, line)) {
            if (primeraLinea) {
                primeraLinea = false;
                continue; // Saltar encabezado
            }
            try {
                stringstream ss(line);
                Autor a;
                string temp;
                getline(ss, temp, ','); a.ID_Autor = stoi(temp);
                getline(ss, a.Nombre, ',');
                getline(ss, a.Nacionalidad, ',');
                autores.push_back(a);
            } catch (const exception& e) {
                cout << "Error al leer linea de autores.txt: " << line << endl;
            }
        }
        fileAutores.close();
    }

    // Cargar estudiantes desde estudiantes.txt
    ifstream fileEstudiantes("estudiantes.txt");
    if (fileEstudiantes.is_open()) {
        string line;
        bool primeraLinea = true;
        while (getline(fileEstudiantes, line)) {
            if (primeraLinea) {
                primeraLinea = false;
                continue; // Saltar encabezado
            }
            try {
                stringstream ss(line);
                Estudiante e;
                string temp;
                getline(ss, temp, ','); e.ID_Estudiante = stoi(temp);
                getline(ss, e.Nombre, ',');
                getline(ss, e.Grado, ',');
                estudiantes.push_back(e);
            } catch (const exception& e) {
                cout << "Error al leer linea de estudiantes.txt: " << line << endl;
            }
        }
        fileEstudiantes.close();
    }

    // Cargar prestamos desde prestamos.txt
    ifstream filePrestamos("prestamos.txt");
    if (filePrestamos.is_open()) {
        string line;
        bool primeraLinea = true;
        while (getline(filePrestamos, line)) {
            if (primeraLinea) {
                primeraLinea = false;
                continue; // Saltar encabezado
            }
            try {
                stringstream ss(line);
                Prestamo p;
                string temp;
                getline(ss, temp, ','); p.ID_Prestamo = stoi(temp);
                getline(ss, temp, ','); p.ID_Libro = stoi(temp);
                getline(ss, temp, ','); p.ID_Estudiante = stoi(temp);
                getline(ss, p.FechaPrestamo, ',');
                getline(ss, p.FechaDevolucion, ',');
                prestamos.push_back(p);
            } catch (const exception& e) {
                cout << "Error al leer linea de prestamos.txt: " << line << endl;
            }
        }
        filePrestamos.close();
    }
}

// Guarda los datos en archivos de texto con encabezados
void BibliotecaDB::guardarDatos() {
    // Guardar libros en libros.txt con encabezado
    ofstream fileLibros("libros.txt");
    fileLibros << "ID_Libro,Titulo,ISBN,AnoPublicacion,ID_Autor,Disponible" << endl;
    for (const auto& l : libros) {
        fileLibros << l.ID_Libro << "," << l.Titulo << "," << l.ISBN << "," 
                   << l.AnoPublicacion << "," << l.ID_Autor << "," 
                   << (l.Disponible ? "1" : "0") << endl;
    }
    fileLibros.close();

    // Guardar autores en autores.txt con encabezado
    ofstream fileAutores("autores.txt");
    fileAutores << "ID_Autor,Nombre,Nacionalidad" << endl;
    for (const auto& a : autores) {
        fileAutores << a.ID_Autor << "," << a.Nombre << "," << a.Nacionalidad << endl;
    }
    fileAutores.close();

    // Guardar estudiantes en estudiantes.txt con encabezado
    ofstream fileEstudiantes("estudiantes.txt");
    fileEstudiantes << "ID_Estudiante,Nombre,Grado" << endl;
    for (const auto& e : estudiantes) {
        fileEstudiantes << e.ID_Estudiante << "," << e.Nombre << "," << e.Grado << endl;
    }
    fileEstudiantes.close();

    // Guardar prestamos en prestamos.txt con encabezado
    ofstream filePrestamos("prestamos.txt");
    filePrestamos << "ID_Prestamo,ID_Libro,ID_Estudiante,FechaPrestamo,FechaDevolucion" << endl;
    for (const auto& p : prestamos) {
        filePrestamos << p.ID_Prestamo << "," << p.ID_Libro << "," << p.ID_Estudiante 
                      << "," << p.FechaPrestamo << "," << p.FechaDevolucion << endl;
    }
    filePrestamos.close();
}

// =============================================
// CRUD LIBROS
// =============================================

// Agrega un nuevo libro al sistema
void BibliotecaDB::agregarLibro() {
    Libro l;
    l.ID_Libro = generarIDLibro();
    l.ISBN = generarISBN();
    
    cout << "=== AGREGAR NUEVO LIBRO ===" << endl;
    cout << "ID_Libro asignado: " << l.ID_Libro << endl;
    cout << "ISBN generado: " << l.ISBN << endl;
    
    cout << "Ingrese Titulo: ";
    cin.ignore(); 
    getline(cin, l.Titulo);
    
    cout << "Ingrese Ano de Publicacion: ";
    while (!(cin >> l.AnoPublicacion)) {
        cout << "Error: Ingrese un numero valido: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    cout << "Ingrese ID_Autor: ";
    while (!(cin >> l.ID_Autor)) {
        cout << "Error: Ingrese un numero valido: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    if (!autorExiste(l.ID_Autor)) {
        cout << "Error: Autor no existe." << endl;
        return;
    }
    
    l.Disponible = true;
    libros.push_back(l);
    cout << "Libro agregado exitosamente." << endl;
}

// Muestra todos los libros en el sistema
void BibliotecaDB::listarLibros() {
    if (libros.empty()) {
        cout << "No hay libros registrados." << endl;
        return;
    }
    for (const auto& l : libros) {
        cout << "ID: " << l.ID_Libro << " | Titulo: " << l.Titulo 
             << " | ISBN: " << l.ISBN << " | Ano: " << l.AnoPublicacion
             << " | Autor ID: " << l.ID_Autor << " | Disponible: " 
             << (l.Disponible ? "Si" : "No") << endl;
    }
}

// Actualiza la informacion de un libro existente
void BibliotecaDB::actualizarLibro() {
    int id;
    cout << "Ingrese ID del libro a actualizar: ";
    while (!(cin >> id)) {
        cout << "Error: Ingrese un numero valido: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    for (auto& l : libros) {
        if (l.ID_Libro == id) {
            cout << "Nuevo titulo: ";
            cin.ignore(); 
            getline(cin, l.Titulo);
            
            cout << "Nuevo ano: ";
            while (!(cin >> l.AnoPublicacion)) {
                cout << "Error: Ingrese un numero valido: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            
            cout << "Libro actualizado." << endl;
            return;
        }
    }
    cout << "Libro no encontrado." << endl;
}

// Elimina un libro del sistema
void BibliotecaDB::eliminarLibro() {
    int id;
    cout << "Ingrese ID del libro a eliminar: ";
    while (!(cin >> id)) {
        cout << "Error: Ingrese un numero valido: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    for (auto it = libros.begin(); it != libros.end(); ++it) {
        if (it->ID_Libro == id) {
            libros.erase(it);
            cout << "Libro eliminado." << endl;
            return;
        }
    }
    cout << "Libro no encontrado." << endl;
}

// Busca libros por ID, titulo o ISBN
void BibliotecaDB::buscarLibroPorTituloOISBN() {
    string busqueda;
    cout << "Ingrese titulo, ID o ISBN a buscar: ";
    cin.ignore(); 
    getline(cin, busqueda);
    
    bool encontrado = false;
    
    // Primero intentar buscar por ID (si la busqueda es un numero)
    try {
        int idBuscado = stoi(busqueda);
        for (const auto& l : libros) {
            if (l.ID_Libro == idBuscado) {
                cout << "ID: " << l.ID_Libro << " | Titulo: " << l.Titulo 
                     << " | ISBN: " << l.ISBN << " | Ano: " << l.AnoPublicacion 
                     << " | Autor ID: " << l.ID_Autor << " | Disponible: " 
                     << (l.Disponible ? "Si" : "No") << endl;
                encontrado = true;
                break; // Solo un libro puede tener ese ID
            }
        }
    } catch (const exception& e) {
        // Si no es un numero, continuar con busqueda por texto
    }
    
    // Si no se encontro por ID, buscar por titulo o ISBN
    if (!encontrado) {
        for (const auto& l : libros) {
            // Busqueda exacta en ISBN (case sensitive)
            if (l.ISBN == busqueda) {
                cout << "ID: " << l.ID_Libro << " | Titulo: " << l.Titulo 
                     << " | ISBN: " << l.ISBN << " | Ano: " << l.AnoPublicacion 
                     << " | Autor ID: " << l.ID_Autor << " | Disponible: " 
                     << (l.Disponible ? "Si" : "No") << endl;
                encontrado = true;
            }
            // Busqueda parcial en titulo (case insensitive)
            else {
                string tituloLower = l.Titulo;
                string busquedaLower = busqueda;
                
                // Convertir a minusculas para busqueda case insensitive
                transform(tituloLower.begin(), tituloLower.end(), tituloLower.begin(), ::tolower);
                transform(busquedaLower.begin(), busquedaLower.end(), busquedaLower.begin(), ::tolower);
                
                if (tituloLower.find(busquedaLower) != string::npos) {
                    cout << "ID: " << l.ID_Libro << " | Titulo: " << l.Titulo 
                         << " | ISBN: " << l.ISBN << " | Ano: " << l.AnoPublicacion 
                         << " | Autor ID: " << l.ID_Autor << " | Disponible: " 
                         << (l.Disponible ? "Si" : "No") << endl;
                    encontrado = true;
                }
            }
        }
    }
    
    if (!encontrado) {
        cout << "No se encontraron libros." << endl;
    }
}

// =============================================
// CRUD AUTORES
// =============================================

// Agrega un nuevo autor al sistema
void BibliotecaDB::agregarAutor() {
    Autor a;
    a.ID_Autor = generarIDAutor();
    
    cout << "=== AGREGAR NUEVO AUTOR ===" << endl;
    cout << "ID_Autor asignado: " << a.ID_Autor << endl;
    
    cout << "Ingrese Nombre: ";
    cin.ignore(); 
    getline(cin, a.Nombre);
    
    cout << "Ingrese Nacionalidad: ";
    getline(cin, a.Nacionalidad);
    
    autores.push_back(a);
    cout << "Autor agregado exitosamente." << endl;
}

// Muestra todos los autores en el sistema
void BibliotecaDB::listarAutores() {
    if (autores.empty()) {
        cout << "No hay autores registrados." << endl;
        return;
    }
    for (const auto& a : autores) {
        cout << "ID: " << a.ID_Autor << " | Nombre: " << a.Nombre 
             << " | Nacionalidad: " << a.Nacionalidad << endl;
    }
}

// Actualiza la informacion de un autor existente
void BibliotecaDB::actualizarAutor() {
    int id;
    cout << "Ingrese ID del autor a actualizar: ";
    while (!(cin >> id)) {
        cout << "Error: Ingrese un numero valido: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    for (auto& a : autores) {
        if (a.ID_Autor == id) {
            cout << "Nuevo nombre: ";
            cin.ignore(); 
            getline(cin, a.Nombre);
            cout << "Nueva nacionalidad: ";
            getline(cin, a.Nacionalidad);
            cout << "Autor actualizado." << endl;
            return;
        }
    }
    cout << "Autor no encontrado." << endl;
}
// Elimina un autor del sistema
void BibliotecaDB::eliminarAutor() {
    int id;
    cout << "Ingrese ID del autor a eliminar: ";
    while (!(cin >> id)) {
        cout << "Error: Ingrese un numero valido: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    for (auto it = autores.begin(); it != autores.end(); ++it) {
        if (it->ID_Autor == id) {
            autores.erase(it);
            cout << "Autor eliminado." << endl;
            return;
        }
    }
    cout << "Autor no encontrado." << endl;
}

// =============================================
// CRUD ESTUDIANTES
// =============================================

// Agrega un nuevo estudiante al sistema con validacion de nombre y grado
void BibliotecaDB::agregarEstudiante() {
    Estudiante e;
    e.ID_Estudiante = generarIDEstudiante();
    
    cout << "=== AGREGAR NUEVO ESTUDIANTE ===" << endl;
    cout << "ID_Estudiante asignado: " << e.ID_Estudiante << endl;
    
    cout << "Ingrese Nombre: ";
    cin.ignore(); 
    {
        // Lambda function para validar caracteres del nombre
        auto esCaracterValido = [](unsigned char ch) {
            // Permitir solo letras basicas (a-z, A-Z), espacios y algunos caracteres especiales
            if (isalpha(ch) || ch == ' ' || ch == '.' || ch == ',' || ch == '-') {
                return true;
            }
            return false;
        };
        
        // Lambda function para validar todo el nombre
        auto contieneSoloCaracteresValidos = [&esCaracterValido](const string& texto) {
            if (texto.empty()) return false;
            
            for (char ch : texto) {
                if (!esCaracterValido(static_cast<unsigned char>(ch))) {
                    return false;
                }
            }
            return true;
        };
        
        // Validar nombre hasta que sea correcto
        while (true) {
            getline(cin, e.Nombre);
            
            // Verificar que no este vacio
            if (e.Nombre.empty()) {
                cout << "Error: El nombre no puede estar vacio. Intente de nuevo: ";
                continue;
            }
            
            // Verificar que solo contenga caracteres validos
            if (contieneSoloCaracteresValidos(e.Nombre)) {
                break;
            } else {
                cout << "Error: El nombre contiene caracteres no validos. ";
                cout << "Solo se permiten letras, espacios, puntos, comas y guiones. Intente de nuevo: ";
            }
        }
    }
    
    cout << "Ingrese Grado (ej: '2o Bachillerato'): ";
    {
        // Lambda function para validar caracteres del grado
        auto esCaracterValidoGrado = [](unsigned char ch) {
            // Permitir letras, numeros, espacios y algunos caracteres especiales
            if (isalnum(ch) || ch == ' ' || ch == 'o' || ch == 'O' || ch == '.' || ch == '-') {
                return true;
            }
            return false;
        };
        
        // Lambda function para validar todo el grado
        auto esGradoValido = [&esCaracterValidoGrado](const string& texto) {
            if (texto.empty()) return false;
            
            for (char ch : texto) {
                if (!esCaracterValidoGrado(static_cast<unsigned char>(ch))) {
                    return false;
                }
            }
            return true;
        };
        
        // Validar grado hasta que sea correcto
        while (true) {
            getline(cin, e.Grado);
            
            // Verificar que no este vacio
            if (e.Grado.empty()) {
                cout << "Error: El grado no puede estar vacio. Intente de nuevo: ";
                continue;
            }
            
            // Verificar que no sea solo espacios
            bool soloEspacios = true;
            for (char ch : e.Grado) {
                if (ch != ' ') {
                    soloEspacios = false;
                    break;
                }
            }
            if (soloEspacios) {
                cout << "Error: El grado no puede contener solo espacios. Intente de nuevo: ";
                continue;
            }
            
            // Verificar que solo contenga caracteres validos
            if (esGradoValido(e.Grado)) {
                break;
            } else {
                cout << "Error: El grado contiene caracteres no validos. ";
                cout << "Solo se permiten letras, numeros y espacios. Intente de nuevo: ";
            }
        }
    }
    
    estudiantes.push_back(e);
    cout << "Estudiante agregado exitosamente." << endl;
}

// Muestra todos los estudiantes en el sistema
void BibliotecaDB::listarEstudiantes() {
    if (estudiantes.empty()) {
        cout << "No hay estudiantes registrados." << endl;
        return;
    }
    for (const auto& e : estudiantes) {
        cout << "ID: " << e.ID_Estudiante << " | Nombre: " << e.Nombre 
             << " | Grado: " << e.Grado << endl;
    }
}

// Actualiza la informacion de un estudiante existente
void BibliotecaDB::actualizarEstudiante() {
    int id;
    cout << "Ingrese ID del estudiante a actualizar: ";
    while (!(cin >> id)) {
        cout << "Error: Ingrese un numero valido: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    for (auto& e : estudiantes) {
        if (e.ID_Estudiante == id) {
            // ... el resto del código permanece igual
            // (ya tiene validaciones robustas para nombre y grado)
            cout << "Nuevo nombre: ";
            cin.ignore(); 
            {
                auto esCaracterValido = [](unsigned char ch) {
                    if (isalpha(ch) || ch == ' ' || ch == '.' || ch == ',' || ch == '-') {
                        return true;
                    }
                    return false;
                };
                
                auto contieneSoloCaracteresValidos = [&esCaracterValido](const string& texto) {
                    if (texto.empty()) return false;
                    
                    for (char ch : texto) {
                        if (!esCaracterValido(static_cast<unsigned char>(ch))) {
                            return false;
                        }
                    }
                    return true;
                };
                
                while (true) {
                    getline(cin, e.Nombre);
                    
                    if (e.Nombre.empty()) {
                        cout << "Error: El nombre no puede estar vacio. Intente de nuevo: ";
                        continue;
                    }
                    
                    if (contieneSoloCaracteresValidos(e.Nombre)) {
                        break;
                    } else {
                        cout << "Error: El nombre contiene caracteres no validos. ";
                        cout << "Solo se permiten letras, espacios, puntos, comas y guiones. Intente de nuevo: ";
                    }
                }
            }
            
            cout << "Nuevo grado (ej: '2o Bachillerato'): ";
            {
                auto esCaracterValidoGrado = [](unsigned char ch) {
                    if (isalnum(ch) || ch == ' ' || ch == 'o' || ch == 'O' || ch == '.' || ch == '-') {
                        return true;
                    }
                    return false;
                };
                
                auto esGradoValido = [&esCaracterValidoGrado](const string& texto) {
                    if (texto.empty()) return false;
                    
                    for (char ch : texto) {
                        if (!esCaracterValidoGrado(static_cast<unsigned char>(ch))) {
                            return false;
                        }
                    }
                    return true;
                };
                
                while (true) {
                    getline(cin, e.Grado);
                    
                    if (e.Grado.empty()) {
                        cout << "Error: El grado no puede estar vacio. Intente de nuevo: ";
                        continue;
                    }
                    
                    bool soloEspacios = true;
                    for (char ch : e.Grado) {
                        if (ch != ' ') {
                            soloEspacios = false;
                            break;
                        }
                    }
                    if (soloEspacios) {
                        cout << "Error: El grado no puede contener solo espacios. Intente de nuevo: ";
                        continue;
                    }
                    
                    if (esGradoValido(e.Grado)) {
                        break;
                    } else {
                        cout << "Error: El grado contiene caracteres no validos. ";
                        cout << "Solo se permiten letras, numeros y espacios. Intente de nuevo: ";
                    }
                }
            }
            
            cout << "Estudiante actualizado." << endl;
            return;
        }
    }
    cout << "Estudiante no encontrado." << endl;
}
// Elimina un estudiante del sistema
void BibliotecaDB::eliminarEstudiante() {
    int id;
    cout << "Ingrese ID del estudiante a eliminar: ";
    while (!(cin >> id)) {
        cout << "Error: Ingrese un numero valido: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    for (auto it = estudiantes.begin(); it != estudiantes.end(); ++it) {
        if (it->ID_Estudiante == id) {
            estudiantes.erase(it);
            cout << "Estudiante eliminado." << endl;
            return;
        }
    }
    cout << "Estudiante no encontrado." << endl;
}
// =============================================
// CRUD PRESTAMOS
// =============================================

// Agrega un nuevo prestamo al sistema
void BibliotecaDB::agregarPrestamo() {
    Prestamo p;
    p.ID_Prestamo = generarIDPrestamo();
    
    cout << "=== AGREGAR NUEVO PRESTAMO ===" << endl;
    cout << "ID_Prestamo asignado: " << p.ID_Prestamo << endl;
    
    cout << "Ingrese ID_Libro: ";
    while (!(cin >> p.ID_Libro)) {
        cout << "Error: Ingrese un numero valido: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    if (!libroExiste(p.ID_Libro)) {
        cout << "Error: Libro no existe." << endl;
        return;
    }
    
    if (!libroDisponible(p.ID_Libro)) {
        cout << "Error: Libro no disponible." << endl;
        return;
    }
    
    cout << "Ingrese ID_Estudiante: ";
    while (!(cin >> p.ID_Estudiante)) {
        cout << "Error: Ingrese un numero valido: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    if (!estudianteExiste(p.ID_Estudiante)) {
        cout << "Error: Estudiante no existe." << endl;
        return;
    }
    
    p.FechaPrestamo = obtenerFechaActual();
    p.FechaDevolucion = "";
    
    prestamos.push_back(p);
    
    // Actualizar disponibilidad del libro
    for (auto& l : libros) {
        if (l.ID_Libro == p.ID_Libro) {
            l.Disponible = false;
            break;
        }
    }
    
    cout << "Prestamo registrado exitosamente." << endl;
}

// Marca un prestamo como devuelto
void BibliotecaDB::actualizarPrestamo() {
    int id;
    cout << "Ingrese ID del prestamo a devolver: ";
    while (!(cin >> id)) {
        cout << "Error: Ingrese un numero valido: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    for (auto& p : prestamos) {
        if (p.ID_Prestamo == id && p.FechaDevolucion.empty()) {
            p.FechaDevolucion = obtenerFechaActual();
            
            // Marcar libro como disponible
            for (auto& l : libros) {
                if (l.ID_Libro == p.ID_Libro) {
                    l.Disponible = true;
                    break;
                }
            }
            
            cout << "Prestamo marcado como devuelto." << endl;
            return;
        }
    }
    cout << "Prestamo no encontrado o ya devuelto." << endl;
}

void BibliotecaDB::eliminarPrestamo() {
    int id;
    cout << "Ingrese ID del prestamo a eliminar: ";
    while (!(cin >> id)) {
        cout << "Error: Ingrese un numero valido: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    for (auto it = prestamos.begin(); it != prestamos.end(); ++it) {
        if (it->ID_Prestamo == id) {
            prestamos.erase(it);
            cout << "Prestamo eliminado." << endl;
            return;
        }
    }
    cout << "Prestamo no encontrado." << endl;
}

void BibliotecaDB::buscarPrestamosPorEstudiante() {
    int id;
    cout << "Ingrese ID del estudiante: ";
    while (!(cin >> id)) {
        cout << "Error: Ingrese un numero valido: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    bool encontrado = false;
    for (const auto& p : prestamos) {
        if (p.ID_Estudiante == id) {
            cout << "ID Prestamo: " << p.ID_Prestamo << " | Libro ID: " << p.ID_Libro 
                 << " | Fecha: " << p.FechaPrestamo 
                 << " | Devolucion: " << (p.FechaDevolucion.empty() ? "Pendiente" : p.FechaDevolucion) << endl;
            encontrado = true;
        }
    }
    if (!encontrado) cout << "No se encontraron prestamos para este estudiante." << endl;
}

// Muestra todos los prestamos en el sistema
void BibliotecaDB::listarPrestamos() {
    if (prestamos.empty()) {
        cout << "No hay prestamos registrados." << endl;
        return;
    }
    
    cout << "=== LISTA DE TODOS LOS PRESTAMOS ===" << endl;
    for (const auto& p : prestamos) {
        cout << "ID: " << p.ID_Prestamo 
             << " | Libro ID: " << p.ID_Libro 
             << " | Estudiante ID: " << p.ID_Estudiante 
             << " | Fecha Prestamo: " << p.FechaPrestamo 
             << " | Devolucion: " << (p.FechaDevolucion.empty() ? "Pendiente" : p.FechaDevolucion) 
             << " | Estado: " << (p.FechaDevolucion.empty() ? "ACTIVO" : "DEVUELTO") << endl;
    }
}
// =============================================
// MENUS DEL SISTEMA
// =============================================

// Menu de gestion de libros
void BibliotecaDB::menuLibros() {
    int opcion;
    do {
        cout << "\n--- GESTION DE LIBROS ---" << endl;
        cout << "1. Agregar Libro" << endl;
        cout << "2. Listar Libros" << endl;
        cout << "3. Actualizar Libro" << endl;
        cout << "4. Eliminar Libro" << endl;
        cout << "5. Buscar por Titulo/ISBN" << endl;
        cout << "6. Consultar por rango de anos" << endl;  // Nueva opcion
        cout << "0. Volver" << endl;
        cout << "Seleccione: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1: agregarLibro(); break;
            case 2: listarLibros(); break;
            case 3: actualizarLibro(); break;
            case 4: eliminarLibro(); break;
            case 5: buscarLibroPorTituloOISBN(); break;
            case 6: consultarLibrosPorRangoAnos(); break;  // Nueva consulta
            case 0: break;
            default: cout << "Opcion invalida." << endl;
        }
    } while (opcion != 0);
}
// Menu de gestion de autores
void BibliotecaDB::menuAutores() {
    int opcion;
    do {
        cout << "\n--- GESTION DE AUTORES ---" << endl;
        cout << "1. Agregar Autor" << endl;
        cout << "2. Listar Autores" << endl;
        cout << "3. Actualizar Autor" << endl;
        cout << "4. Eliminar Autor" << endl;
        cout << "5. Autores con mas libros" << endl;  // Nueva opcion
        cout << "0. Volver" << endl;
        cout << "Seleccione: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1: agregarAutor(); break;
            case 2: listarAutores(); break;
            case 3: actualizarAutor(); break;
            case 4: eliminarAutor(); break;
            case 5: consultarAutoresConMasLibros(); break;  // Nueva consulta
            case 0: break;
            default: cout << "Opcion invalida." << endl;
        }
    } while (opcion != 0);
}
// Menu de gestion de estudiantes
void BibliotecaDB::menuEstudiantes() {
    int opcion;
    do {
        cout << "\n--- GESTION DE ESTUDIANTES ---" << endl;
        cout << "1. Agregar Estudiante" << endl;
        cout << "2. Listar Estudiantes" << endl;
        cout << "3. Actualizar Estudiante" << endl;
        cout << "4. Eliminar Estudiante" << endl;
        cout << "5. Estudiantes con mas prestamos" << endl;  // Nueva opcion
        cout << "0. Volver" << endl;
        cout << "Seleccione: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1: agregarEstudiante(); break;
            case 2: listarEstudiantes(); break;
            case 3: actualizarEstudiante(); break;
            case 4: eliminarEstudiante(); break;
            case 5: consultarEstudianteConMasPrestamos(); break;  // Nueva consulta
            case 0: break;
            default: cout << "Opcion invalida." << endl;
        }
    } while (opcion != 0);
}

// Menu de gestion de prestamos
void BibliotecaDB::menuPrestamos() {
    int opcion;
    do {
        cout << "\n--- GESTION DE PRESTAMOS ---" << endl;
        cout << "1. Agregar Prestamo" << endl;
        cout << "2. Listar Prestamos" << endl;
        cout << "3. Devolver Prestamo" << endl;
        cout << "4. Eliminar Prestamo" << endl;
        cout << "5. Buscar por Estudiante" << endl;
        cout << "6. Dias con mas prestamos" << endl;  // Nueva opcion
        cout << "0. Volver" << endl;
        cout << "Seleccione: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1: agregarPrestamo(); break;
            case 2: listarPrestamos(); break;
            case 3: actualizarPrestamo(); break;
            case 4: eliminarPrestamo(); break;
            case 5: buscarPrestamosPorEstudiante(); break;
            case 6: consultarDiasConMasPrestamos(); break;  // Nueva consulta
            case 0: break;
            default: cout << "Opcion invalida." << endl;
        }
    } while (opcion != 0);
}


// =============================================
// CONSULTAS BASICAS POR ENTIDAD
// =============================================

// CONSULTA PARA LIBROS: Libros por rango de años
void BibliotecaDB::consultarLibrosPorRangoAnos() {
    int anoInicio, anoFin;
    cout << "=== CONSULTAR LIBROS POR RANGO DE ANOS ===" << endl;
    cout << "Ingrese ano de inicio: ";
    cin >> anoInicio;
    cout << "Ingrese ano de fin: ";
    cin >> anoFin;
    
    if (anoInicio > anoFin) {
        cout << "Error: El ano de inicio no puede ser mayor al ano de fin." << endl;
        return;
    }
    
    bool encontrados = false;
    cout << "Libros publicados entre " << anoInicio << " y " << anoFin << ":" << endl;
    
    for (const auto& libro : libros) {
        if (libro.AnoPublicacion >= anoInicio && libro.AnoPublicacion <= anoFin) {
            cout << "ID: " << libro.ID_Libro << " | Titulo: " << libro.Titulo 
                 << " | Ano: " << libro.AnoPublicacion << " | Autor ID: " << libro.ID_Autor 
                 << " | Disponible: " << (libro.Disponible ? "Si" : "No") << endl;
            encontrados = true;
        }
    }
    
    if (!encontrados) {
        cout << "No se encontraron libros en ese rango de anos." << endl;
    }
}

// CONSULTA PARA AUTORES: Autores con más libros
void BibliotecaDB::consultarAutoresConMasLibros() {
    cout << "=== AUTORES CON MAS LIBROS ===" << endl;
    
    if (autores.empty() || libros.empty()) {
        cout << "No hay datos suficientes para realizar la consulta." << endl;
        return;
    }
    
    // Contar libros por autor
    vector<pair<int, int>> conteoAutores; // pair<ID_Autor, CantidadLibros>
    
    for (const auto& autor : autores) {
        int contador = 0;
        for (const auto& libro : libros) {
            if (libro.ID_Autor == autor.ID_Autor) {
                contador++;
            }
        }
        conteoAutores.push_back({autor.ID_Autor, contador});
    }
    
    // Ordenar por cantidad de libros (descendente)
    sort(conteoAutores.begin(), conteoAutores.end(), 
         [](const pair<int, int>& a, const pair<int, int>& b) {
             return a.second > b.second;
         });
    
    // Mostrar resultados
    cout << "Ranking de autores por cantidad de libros:" << endl;
    for (const auto& resultado : conteoAutores) {
        if (resultado.second > 0) {
            // Buscar nombre del autor
            string nombreAutor = "Desconocido";
            for (const auto& autor : autores) {
                if (autor.ID_Autor == resultado.first) {
                    nombreAutor = autor.Nombre;
                    break;
                }
            }
            cout << "Autor: " << nombreAutor << " | Libros: " << resultado.second << endl;
        }
    }
}

// CONSULTA PARA ESTUDIANTES: Estudiante con más préstamos
void BibliotecaDB::consultarEstudianteConMasPrestamos() {
    cout << "=== ESTUDIANTES CON MAS PRESTAMOS ===" << endl;
    
    if (estudiantes.empty() || prestamos.empty()) {
        cout << "No hay datos suficientes para realizar la consulta." << endl;
        return;
    }
    
    // Contar préstamos por estudiante
    vector<pair<int, int>> conteoEstudiantes; // pair<ID_Estudiante, CantidadPrestamos>
    
    for (const auto& estudiante : estudiantes) {
        int contador = 0;
        for (const auto& prestamo : prestamos) {
            if (prestamo.ID_Estudiante == estudiante.ID_Estudiante) {
                contador++;
            }
        }
        conteoEstudiantes.push_back({estudiante.ID_Estudiante, contador});
    }
    
    // Ordenar por cantidad de préstamos (descendente)
    sort(conteoEstudiantes.begin(), conteoEstudiantes.end(), 
         [](const pair<int, int>& a, const pair<int, int>& b) {
             return a.second > b.second;
         });
    
    // Mostrar top estudiantes
    cout << "Top estudiantes con mas prestamos:" << endl;
    int contador = 0;
    for (const auto& resultado : conteoEstudiantes) {
        if (resultado.second > 0 && contador < 5) {
            // Buscar nombre del estudiante
            string nombreEstudiante = "Desconocido";
            string gradoEstudiante = "N/A";
            for (const auto& estudiante : estudiantes) {
                if (estudiante.ID_Estudiante == resultado.first) {
                    nombreEstudiante = estudiante.Nombre;
                    gradoEstudiante = estudiante.Grado;
                    break;
                }
            }
            cout << contador + 1 << ". " << nombreEstudiante << " | Grado: " << gradoEstudiante 
                 << " | Prestamos: " << resultado.second << endl;
            contador++;
        }
    }
    
    if (contador == 0) {
        cout << "No se encontraron estudiantes con prestamos." << endl;
    }
}

// CONSULTA PARA PRÉSTAMOS: Días con más préstamos
void BibliotecaDB::consultarDiasConMasPrestamos() {
    cout << "=== DIAS CON MAS PRESTAMOS ===" << endl;
    
    if (prestamos.empty()) {
        cout << "No hay prestamos registrados." << endl;
        return;
    }
    
    // Contar préstamos por fecha
    vector<pair<string, int>> conteoFechas; // pair<Fecha, CantidadPrestamos>
    
    for (const auto& prestamo : prestamos) {
        bool fechaEncontrada = false;
        for (auto& conteo : conteoFechas) {
            if (conteo.first == prestamo.FechaPrestamo) {
                conteo.second++;
                fechaEncontrada = true;
                break;
            }
        }
        if (!fechaEncontrada) {
            conteoFechas.push_back({prestamo.FechaPrestamo, 1});
        }
    }
    
    // Ordenar por cantidad de préstamos (descendente)
    sort(conteoFechas.begin(), conteoFechas.end(), 
         [](const pair<string, int>& a, const pair<string, int>& b) {
             return a.second > b.second;
         });
    
    // Mostrar top días
    cout << "Top dias con mas prestamos:" << endl;
    int contador = 0;
    for (const auto& resultado : conteoFechas) {
        if (contador < 10) {
            cout << contador + 1 << ". Fecha: " << resultado.first 
                 << " | Prestamos: " << resultado.second << endl;
            contador++;
        }
    }
}

