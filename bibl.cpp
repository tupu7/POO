#include <iostream>
#include <string>
#include <vector>
#include <fstream>

//--- DefiniciC3n de la clase Libro (mejorada) ---
class Libro {
public:
	std::string titulo;
	std::string autor;
	int anioPublicacion;
	bool estaDisponible; // Nuevo atributo

	// Constructor para inicializar los valores fC!cilmente
	Libro() : anioPublicacion(0), estaDisponible(true) {

	}

	void mostrarDetallesCompletos() {
		// ... LC3gica para imprimir detalles y disponibilidad ...
		std:: cout << "Titulo " << titulo << std::endl;
		std:: cout << "autor " << autor << std::endl;
		std:: cout << "ano de Publicacion " << anioPublicacion << std::endl;
		if(estaDisponible) {
			std::cout << "El libro esta disponible";
		} else {
			std::cout << "El libro no esta disponible";
		}
	}
};



// --- DefiniciC3n de la clase Biblioteca ---
class Biblioteca {
    private:
	std::vector<Libro> coleccion;

    public:
	// ... Implementar mC)todos aquC- (agregar, mostrar, buscar, etc.) ...

	void agregarLibro(const Libro & nuevoLibro) {
		coleccion.push_back(nuevoLibro);


	};
	void mostrarInventario() {
		for(int i = 0; i < coleccion.size(); i++) {
			coleccion[i].mostrarDetallesCompletos();
		}
	}

	Libro* buscarLibro(const std::string& tituloBuscado) {
		for(int i = 0; i < coleccion.size(); i++) {
			if(coleccion[i].titulo == tituloBuscado) {
				return &coleccion[i];

			}

		}
		std::cout << "nullptr" << std::endl;

	};

	void prestarLibro(const std::string& tituloPrestamo) {
		for(int i = 0; i < coleccion.size(); i++) {

		}
	};
	void devolverLibro(const std::string & tituloDevolucion) {
		miBiblioteca.buscarLibro() {
			if(&coleccion[i])
			}



	};

};


// --- FunciC3n Principal con el MenC: ---
int main()
{
	Biblioteca miBiblioteca;
	int opcion = 0;

	// Agregar algunos libros de ejemplo para empezar
	Libro libroInicial;
	libroInicial.titulo = "El Hobbit";
	libroInicial.autor = "J.R.R. Tolkien";
	miBiblioteca.agregarLibro(libroInicial);

	while (opcion != 5)
	{
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

		if (opcion == 1) {

		}
		else if (opcion == 2) {


		}
		else if (opcion == 3) {



		}
		else if (opcion == 4) {

		}
		else if (opcion == 5) {
			std::cout << "salu" << std::endl;
		}
		else {
			std::cout << "NO" <<std::endl;
		}
	};

	// Usar un switch o if-else para manejar la opciC3n del usuario
	// ... LC3gica del menC: aquC- ...

}
