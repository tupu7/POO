#include <iostream>
#include <string>
#include <vector>

// --- Definición de la clase Libro (mejorada) ---
class Libro {
public:
    std::string titulo;
    std::string autor;
    int anioPublicacion;
    bool estaDisponible; // Nuevo atributo

    // Constructor para inicializar los valores fácilmente
    Libro() : anioPublicacion(1960), estaDisponible(true) {}

    void mostrarDetallesCompletos() {
        // ... Lógica para imprimir detalles y disponibilidad ...
        std:: cout << "Titulo: " << titulo << std::endl;
		std:: cout << "Autor: " << autor << std::endl;
		std:: cout << "Ano de Publicacion: " << anioPublicacion << std::endl;
		if(estaDisponible) {
			std::cout << "El libro esta disponible" << std::endl;
		} else {
			std::cout << "El libro no esta disponible" << std::endl;
		}
    }
};


// --- Definición de la clase Biblioteca ---
class Biblioteca {
private:
    std::vector<Libro> coleccion;

public:
    void agregarLibro(const Libro &nuevoLibro) {
        for (const Libro &libro : coleccion) {
            if (libro.titulo == nuevoLibro.titulo) {
                std::cout << "No se puede agregar el mismo libro 2 veces" << std::endl;
                return; 
        }
    }
    coleccion.push_back(nuevoLibro);
    std::cout << "Libro agregado con éxito" << std::endl;
    }
      

    void mostrarInventario(){
        for (Libro& libro : coleccion){
            libro.mostrarDetallesCompletos();
        }
    }

    Libro* buscarLibro(const std::string & tituloBuscado){
        for (Libro& libro : coleccion){
            if (libro.titulo == tituloBuscado){
                return &libro;
            }
        }
        return nullptr;
    }

    void prestarLibro(const std::string & tituloPrestamo){
        Libro* libro;
        libro = buscarLibro(tituloPrestamo);
        if (libro == nullptr){
            std::cout << "El titulo no fue encontrado" << std::endl;
        }
        else{
            if((*libro).estaDisponible){
                (*libro).estaDisponible = false;
                std::cout << "El libro ha sido reservado con exito" << std::endl;
            }
            else{
                std::cout << "El libro no esta disponible para ser prestado" << std::endl;
            }
        }
    }

    void devolverLibro(const std::string &tituloDevolucion) {
        Libro* libro = buscarLibro(tituloDevolucion);
        if (libro == nullptr) {
            std::cout << "El titulo no fue encontrado" << std::endl;
        }
        else {
            if (!libro->estaDisponible) {
                libro->estaDisponible = true;
                std::cout << "El libro se ha devuelto con exito" << std::endl;
            }
            else {
                std::cout << "El libro ya estaba disponible, no es necesario devolverlo" << std::endl;
            }
        }
    }
};

// --- Función Principal con el Menú ---
int main() {
    Biblioteca miBiblioteca;
    int opcion = 0;

    // Agregar algunos libros de ejemplo para empezar
    Libro libroInicial;
    libroInicial.titulo = "El Hobbit";
    libroInicial.autor = "J.R.R. Tolkien";
    miBiblioteca.agregarLibro(libroInicial);

    while (opcion != 5) {
        std::cout << "\n--- BIBLIOTECA DIGITAL ---" << std::endl;
        std::cout << "1. Anadir libro" << std::endl;
        std::cout << "2. Mostrar inventario" << std::endl;
        std::cout << "3. Prestar libro" << std::endl;
        std::cout << "4. Devolver libro" << std::endl;
        std::cout << "5. Salir" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;
        
        // Limpiar el buffer de entrada para futuras lecturas de texto
        std::cin.ignore();

        // Usar
        //un switch o if-else para manejar la opción del usuario
        
        if(opcion == 1){
            Libro nuevo_libro;
            std::string name, title;
            int anio;
            std::cout << "Ingrese titulo de libro: " << std::endl;
            std::getline(std::cin, name);
            std::cout << "Ingrese autor del libro: " << std::endl;
            std::getline(std::cin, title);
            std::cout << "Ingrese año de publicacion: " << std::endl;
            std::cin >> anio;
            std::cin.ignore();
            nuevo_libro.titulo = name;
            nuevo_libro.autor = title;
            nuevo_libro.anioPublicacion = anio;
            miBiblioteca.agregarLibro(nuevo_libro);
        }
        else if(opcion == 2){
            miBiblioteca.mostrarInventario(); 
        }
        else if(opcion == 3){
            std::string title;
            std::cout << "Ingrese titulo de libro: " << std::endl;
            std::getline(std::cin, title);
            miBiblioteca.prestarLibro(title);
        }
        else if(opcion == 4){
            std::string title;
            std::cout << "Ingrese titulo de libro: " << std::endl;
            std::getline(std::cin, title);
            miBiblioteca.devolverLibro(title);
            
        }
        
        else if(opcion == 5){
            std::cout << "Adios, que tengas un buen dia" << std::endl;
        }
        
        
        }
    

    return 0;
}
