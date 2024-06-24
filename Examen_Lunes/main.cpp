#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <list>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <filesystem>

namespace fs = std::filesystem;

// Autor: Karla Cornejo
struct Node {
    int location;
    int capacity;
    int intValue;
    std::string varcharValue;
    Node* next;

    // Constructor para ubicación y capacidad
    Node(int loc, int cap) : location(loc), capacity(cap), intValue(0), varcharValue(""), next(nullptr) {}

    // Constructor para valores enteros
    Node(int loc, int val, bool isInt) : location(loc), capacity(4), intValue(val), varcharValue(""), next(nullptr) {}

    // Constructor para valores varchar
    Node(int loc, std::string val, int cap) : location(loc), capacity(cap), intValue(0), varcharValue(val), next(nullptr) {}
};
// Autor: Karla Cornejo
class LinkedList {
private:
    Node* head;
    Node* varcharHead;
    int locationCounter;

public:
    LinkedList() : head(nullptr), varcharHead(nullptr), locationCounter(1) {}

    void addLocationCapacity(int location, int capacity) {
        Node* newNode = new Node(location, capacity);
        newNode->next = head;
        head = newNode;
    }

    void addIntValue(int value) {
        Node* newNode = new Node(locationCounter, value, true);
        locationCounter += 4;
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }

    void addVarcharValue(std::string value, int capacity) {
        Node* newNode = new Node(locationCounter, value, capacity);
        locationCounter += capacity;
        if (!varcharHead) {
            varcharHead = newNode;
        } else {
            Node* temp = varcharHead;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }

    void saveToFile(const std::string& filename) {
        std::ofstream file(filename, std::ios::app);  // Abrir en modo append
        if (!file.is_open()) {
            std::cout << "Error al abrir el archivo!" << std::endl;
            return;
        }

        int currentLocation = 1;

        // Guardar ubicaciones y capacidades de varchar
        Node* temp = varcharHead;
        while (temp) {
            file << "(" << currentLocation << ") " << temp->location << "," << temp->capacity << " ";
            currentLocation += 1;
            temp = temp->next;
        }

        // Guardar valores int
        temp = head;
        while (temp) {
            if (temp->varcharValue.empty() && temp->intValue != 0) {
                file << "(" << currentLocation << ") " << temp->intValue << " ";
                currentLocation += 4;
            }
            temp = temp->next;
        }

        // Guardar valores varchar
        temp = varcharHead;
        while (temp) {
            file << "(" << currentLocation << ") " << temp->varcharValue << " ";
            currentLocation += temp->capacity;
            temp = temp->next;
        }

        file << std::endl;  // Agregar una nueva línea después de cada registro
        file.close();
    }

    void printList() {
        int currentLocation = 1;

        // Imprimir ubicaciones y capacidades de varchar
        Node* temp = varcharHead;
        while (temp) {
            std::cout << "(" << currentLocation << ") " << temp->location << "," << temp->capacity << " ";
            currentLocation += 1;
            temp = temp->next;
        }

        // Imprimir valores int
        temp = head;
        while (temp) {
            if (temp->varcharValue.empty() && temp->intValue != 0) {
                std::cout << "(" << currentLocation << ") " << temp->intValue << " ";
                currentLocation += 4;
            }
            temp = temp->next;
        }

        // Imprimir valores varchar
        temp = varcharHead;
        while (temp) {
            std::cout << "(" << currentLocation << ") " << temp->varcharValue << " ";
            currentLocation += temp->capacity;
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};
// Autor: Karla Cornejo
std::vector<std::pair<std::string, std::string>> parseSchema(const std::string& schemaFile) {
    std::ifstream file(schemaFile);
    std::vector<std::pair<std::string, std::string>> schema;
    std::string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            std::stringstream ss(line);
            std::string token;
            while (getline(ss, token, '#')) {
                std::string name = token;
                getline(ss, token, '#');
                std::string type = token;
                schema.push_back({name, type});
            }
        }
        file.close();
    } else {
        std::cout << "Error al abrir el archivo esquema!" << std::endl;
    }

    return schema;
}

// Autor: Lizardo Castillo
class Disco {
private:
    int nroPlato;
    int nroSuperficie;
    int nroPistaxSuperficie;
    int nroSectorxPista;
    int byteSector;
    int capacidadDisco;
public:
    Disco(int nroPlato, int nroSuperficie, int nroPistaxSuperficie, int nroSectorxPista, int byteSector) {
        this->nroPlato = nroPlato;
        this->nroSuperficie = nroSuperficie;
        this->nroPistaxSuperficie = nroPistaxSuperficie;
        this->nroSectorxPista = nroSectorxPista;
        this->byteSector = byteSector;
        this->capacidadDisco = byteSector * nroSectorxPista * nroPistaxSuperficie * nroSuperficie * nroPlato;
    }

    void verCapacidadDisco() {
        std::cout << "Capacidad del disco: ";
        long long capacidadDiscoGB = capacidadDisco / (1024 * 1024 * 1024);
        if (capacidadDiscoGB > 1) {
            std::cout << capacidadDiscoGB << " GB" << std::endl;
        } else {
            std::cout << capacidadDisco << " bytes" << std::endl;
        }
    }

    void crearDisco () {
        std::string carpetaRaiz = "disco";

        fs::create_directory(carpetaRaiz);

        for(int i = 0; i < nroPlato; i++) {
            std::stringstream carpetaPlatoSS;
            carpetaPlatoSS << carpetaRaiz << "/plato" << i + 1;
            std::string carpetaPlato = carpetaPlatoSS.str();
            fs::create_directory(carpetaPlato);

            for(int j = 0; j < 2; j++) {
                std::stringstream carpetaSuperficieSS;
                carpetaSuperficieSS << carpetaPlato << "/superficie" << j + 1;
                std::string carpetaSuperficie = carpetaSuperficieSS.str();
                fs::create_directory(carpetaSuperficie);

                for(int k = 0; k < nroPistaxSuperficie; k++) {
                    std::stringstream carpetaPistaSS;
                    carpetaPistaSS << carpetaSuperficie << "/pista" << k + 1;
                    std::string carpetaPista = carpetaPistaSS.str();
                    fs::create_directory(carpetaPista); 

                    for(int l = 0; l < nroSectorxPista; l++) {
                        std::stringstream archivoSS;
                        archivoSS << carpetaPista << "/sector" << l + 1 << ".txt";
                        std::string archivo = archivoSS.str();
                        
                        std::ofstream outFile(archivo);
                        if (outFile.is_open()) {
                            outFile << "D#PL" << i + 1 << "#SU" << j + 1 << "#PI" << k + 1 << "#SE" << l + 1 << std::endl;
                            outFile.close();
                        } else {
                            std::cerr << "Error al crear el archivo " << archivo << std::endl;
                        }
                    }
                }
            }
        }
    }
};

// Autor: Karla Cornejo y Lizardo Castillo
// Clase para representar una página
class Pagina {
private:
    std::string nombre;  // Nombre de la página (e.g., "1.txt")
    std::string rutaCompleta;  // Ruta completa del archivo
    int almacenamientoTotal;  // Almacenamiento total de la página en bytes
    int almacenamientoUsado;  // Almacenamiento usado actualmente en bytes

public:
    // Autor: Karla Cornejo y Lizardo Castillo
    Pagina(const std::string& nombre, int almacenamientoTotal)
        : nombre(nombre), almacenamientoTotal(almacenamientoTotal), almacenamientoUsado(0) {
        rutaCompleta = "Paginas/" + nombre;
        std::string rutaCompletaBloque = "Bloques/" + nombre;
        // Crear archivo vacío para la página
        std::ofstream archivoPagina(rutaCompleta);
        archivoPagina.close();

        // Crear archivo vacío para el bloque
        std::ofstream archivoBloque(rutaCompletaBloque);
        archivoBloque.close();
    }

    // Autor: Karla Cornejo
    // Función para añadir información a la página
    void agregarInformacion(const std::string& informacion) {
        std::ofstream archivo(rutaCompleta, std::ios::app);
        archivo << informacion << std::endl;
        almacenamientoUsado += informacion.length();  // Suponiendo que 1 byte por carácter
        archivo.close();
    }

    // Autor: Karla Cornejo
    // Función para calcular el porcentaje de almacenamiento usado
    double porcentajeAlmacenamientoUsado() const {
        if (almacenamientoTotal == 0) {
            return 100.0;  // Si la página no tiene almacenamiento, está llena
        } else {
            return static_cast<double>(almacenamientoUsado) / almacenamientoTotal * 100.0;
        }
    }
    // Autor: Karla Cornejo
    // Getter para el nombre de la página
    std::string obtenerNombre() const {
        return nombre;
    }
    // Autor: Karla Cornejo
    // Getter para la ruta completa de la página
    std::string obtenerRutaCompleta() const {
        return rutaCompleta;
    }
};

// Autor: Karla Cornejo y Lizardo Castillo
// Clase para manejar la lista de páginas
class GestorPaginas {
private:
    std::vector<Pagina> paginas;  // Lista de páginas

public:
    // Autor: Karla Cornejo y Lizardo Castillo
    // Función para crear la carpeta "Paginas"
    void crearCarpetas() {
        fs::create_directory("Bloques");
        fs::create_directory("Paginas");
    }

    // Autor: Karla Cornejo y Lizardo Castillo
    // Función para crear las páginas según la cantidad y almacenamiento especificados por el usuario
    void crearPaginas(int cantidadPaginas, int almacenamientoPorPagina) {
        for (int i = 1; i <= cantidadPaginas; ++i) {
            std::string nombrePagina = std::to_string(i) + ".txt";
            Pagina pagina(nombrePagina, almacenamientoPorPagina);
            paginas.push_back(pagina);
        }
    }
    // Autor: Karla Cornejo y Lizardo Castillo
    // Función para añadir información a una página específica
    void agregarInformacionAPagina(int indicePagina, const std::string& informacion) {
        if (indicePagina >= 0 && indicePagina < paginas.size()) {
            paginas[indicePagina].agregarInformacion(informacion);
            std::cout << "Informacion agregada a la pagina " << indicePagina + 1 << "." << std::endl;
        } else {
            std::cout << "Indice de página invalido." << std::endl;
        }
    }
    // Autor: Karla Cornejo y Lizardo Castillo
    // Función para mostrar el porcentaje de almacenamiento disponible de cada página
    void FileSpaceMap() const {
        std::cout << "Porcentaje de disponibilidad de cada pagina:" << std::endl;
        for (size_t i = 0; i < paginas.size(); ++i) {
            std::cout << "Pagina " << i + 1 << ": ";
            double porcentajeUsado = paginas[i].porcentajeAlmacenamientoUsado();
            if (porcentajeUsado == 100.0) {
                std::cout << "100% (llena)" << std::endl;
            } else {
                std::cout << std::fixed << std::setprecision(2) << porcentajeUsado << "% usado, "
                          << 100.0 - porcentajeUsado << "% disponible." << std::endl;
            }
        }
    }
    // Autor: Karla Cornejo
    // Función principal para manejar todo el proceso
    void ejecutar() {
        crearCarpetas();

        int cantidadPaginas;
        int almacenamientoPorPagina;
        std::cout << "Cuantas paginas desea? ";
        std::cin >> cantidadPaginas;
        std::cout << "Cuanto sera el almacenamiento de cada pagina (en bytes)? ";
        std::cin >> almacenamientoPorPagina;

        crearPaginas(cantidadPaginas, almacenamientoPorPagina);

    }

    friend class BufferManager;
};
// Autor: Karla Cornejo y Lizardo Castillo
// Estructura para almacenar la información de cada campo del esquema
struct Campo {
    std::string nombre;
    std::string tipo_dato;
    int cantidad_bytes;
};
// Autor: Karla Cornejo
// Función para leer el esquema desde el archivo "esquema.txt"
std::vector<Campo> leerEsquema(const std::string& archivo_esquema) {
    std::vector<Campo> campos;
    std::ifstream file(archivo_esquema);
    if (file.is_open()) {
        std::string linea;
        std::getline(file, linea);
        std::istringstream ss(linea);
        std::string token;
        while (std::getline(ss, token, '#')) {
            Campo campo;
            campo.nombre = token;
            std::getline(ss, campo.tipo_dato, '#');
            ss >> campo.cantidad_bytes;
            // Saltar el espacio en blanco después de la cantidad de bytes
            ss.ignore();
            campos.push_back(campo);
        }
        file.close();
    } else {
        std::cerr << "No se pudo abrir el archivo de esquema." << std::endl;
    }
    return campos;
}
// Autor: Karla Cornejo y Lizardo Castillo
class BufferPool {
private:
    struct Frame {
        int frameID;
        int pageID;
        bool dirtyBit;
        bool pinned;
        int pinCount;
        bool refBit;
    };

    std::vector<Frame> frames;
    std::string tablaFilename;

public:
    BufferPool() : tablaFilename("TablaBufferPool.txt") {}
    // Autor: Lizardo Castillo
    void MenuBufferPool() {
        int numFrames;
        std::cout << "Ingrese la cantidad de frames que tendra el buffer: ";
        std::cin >> numFrames;
        frames.resize(numFrames);

        for (int i = 0; i < numFrames; ++i) {
            frames[i] = {i, 0, false, false, 0, false};
        }
        CrearTabla();
    }

    // Autor: Karla Cornejo y Lizardo Castillo
    void CrearTabla() {
        std::ofstream tablaFile(tablaFilename);
        if (tablaFile.is_open()) {
            tablaFile << "Frame ID\tPage ID\t\tDirty Bit\tPinned\t\tPin Count\tRef Bit\n";
            for (const auto& frame : frames) {
                tablaFile << frame.frameID << "\t\t"
                          << frame.pageID << "\t\t"
                          << frame.dirtyBit << "\t\t"
                          << frame.pinned << "\t\t"
                          << frame.pinCount << "\t\t"
                          << frame.refBit << "\n";
            }
            tablaFile.close();
            std::cout << "Tabla creada exitosamente en " << tablaFilename << std::endl;
        } else {
            std::cerr << "No se pudo crear el archivo: " << tablaFilename << std::endl;
        }
    }
    // Autor: Karla Cornejo y Lizardo Castillo
    void MostrarTabla() {
        std::ifstream tablaFile(tablaFilename);
        if (tablaFile.is_open()) {
            std::string line;
            while (std::getline(tablaFile, line)) {
                std::cout << line << std::endl;
            }
            tablaFile.close();
        } else {
            std::cerr << "No se pudo abrir el archivo: " << tablaFilename << std::endl;
        }
    }
    // Autor: Karla Cornejo y Lizardo Castillo
    void ActualizarTabla() {
        CrearTabla();
        MostrarTabla();
    }

    friend class BufferManager;
};
// Autor: Karla Cornejo y Lizardo Castillo
class BufferManager {
private:
    struct Consulta {
        int pageID;
        char accion;
        std::string contenido;
        bool completada;
    };
    GestorPaginas& gestorPaginas;
    BufferPool& bufferPool;
    bool usarLRU;
    int punteroReloj;
    std::list<int> listaLRU;
    std::unordered_map<int, std::list<int>::iterator> mapaLRU;
    std::unordered_map<int, std::queue<Consulta>> colasDeConsultas;

public:
    // Autor: Karla Cornejo y Lizardo Castillo
    BufferManager(BufferPool& pool, GestorPaginas& gestor) : bufferPool(pool), gestorPaginas(gestor), punteroReloj(0)  {
        int opcion;
        do {
            std::cout << "Algoritmo de reemplazo (1 = LRU, 0 = Clock): ";
            std::cin >> opcion;
            switch (opcion) {
                case 1:
                    std::cout << "Algoritmo seleccionado: LRU" << std::endl;
                    usarLRU = true;
                    break;
                case 0:
                    std::cout << "Algoritmo seleccionado: Clock" << std::endl;
                    usarLRU = false;
                    break;
                default:
                    std::cout << "Opcion no valida. Por favor, ingrese una opcion valida (1 o 0)." << std::endl;
                    break;
            }
        } while (opcion != 1 && opcion != 0);
    }
    // Autor: Lizardo Castillo
    void MenuBufferManager() {
        while (true) {
            ConsultarPagina();
        }
    }
    // Autor: Karla Cornejo y Lizardo Castillo
    void ConsultarPagina() {
        int pageID;
        std::cout << "Que pagina desea consultar? ";
        std::cin >> pageID;

        std::string nombrePagina = "Paginas/" + std::to_string(pageID) + ".txt";
        std::string nombreBloque = "Bloques/" + std::to_string(pageID) + ".txt";
        std::ifstream archivoBloque(nombreBloque);
        std::ifstream archivoPagina(nombrePagina);
        if (!archivoPagina.is_open()) {
            std::cerr << "No se pudo abrir el archivo de la pagina: " << nombrePagina << std::endl;
            return;
        }

        BufferPool::Frame* frame = BuscarFramePorPagina(pageID);
        if (!frame) {
            frame = BuscarFrameVacio();
            if (!frame) {
                if (usarLRU) {
                    LRU(pageID);
                    return;
                } else {
                    AlgoritmoClock(pageID);
                    return;
                }
                frame = BuscarFramePorPagina(pageID);
            } else {
                frame->pageID = pageID;
                frame->pinCount = 0;
                frame->dirtyBit = false;
                bufferPool.ActualizarTabla();
            }
        }

        std::string respuesta;
        if (!frame->pinned) {
            std::cout << "Desea pinear (anclar) la pagina? (si/no): ";
            std::cin >> respuesta;
            if (respuesta == "si") {
                frame->pinned = true;
            }
        } else if (frame->pinned && frame->pageID == pageID) {
            std::cout << "La pagina ya esta pineada." << std::endl;
        }

        frame->pinCount++;
        if (usarLRU) {
            ActualizarLRU(pageID);
        } else {
            frame->refBit = true;
        }
        bufferPool.ActualizarTabla();

        char accion;
        std::string contenido;
        while (true) {
            std::cout << "Desea escribir (e) o leer (l) la pagina? ";
            std::cin >> accion;
            if (accion == 'l') {
                std::string line;
                while (std::getline(archivoPagina, line)) {
                    std::cout << line << std::endl;
                }
                archivoPagina.clear();
                archivoPagina.seekg(0, std::ios::beg);
            } else if (accion == 'e') {
                int opcion;
                std::cout << "Longitud Fija (1) o Longitud Variable (2)? ";
                std::cin >> opcion;
                if (opcion == 1) {
                    if (longitudFija("esquemaF.txt", nombrePagina, nombreBloque, *frame, bufferPool)) {
                        std::cout << "Contenido guardado exitosamente." << std::endl;
                    }
                } else if (opcion == 2) {
                    longitudVariable("esquemaV.txt", nombrePagina, nombreBloque, *frame, bufferPool);
                }
            } else {
                std::cerr << "Acción no valida." << std::endl;
                continue;
            }

            std::cout << "Desea liberar la pagina? (si/no): ";
            std::cin >> respuesta;
            if (respuesta == "si") {
                frame->pinCount--;
                ActualizarDirtyBit(pageID);
                bufferPool.ActualizarTabla();
            } else {
                Consulta consulta = {pageID, accion, contenido, false};
                colasDeConsultas[pageID].push(consulta);
                ActualizarDirtyBit(pageID);
                bufferPool.ActualizarTabla();
            }

            if (frame->pinned) {
                std::cout << "Desea despinear (desanclar) la pagina? (si/no): ";
                std::cin >> respuesta;
                if (respuesta == "si") {
                    frame->pinned = false;
                    bufferPool.ActualizarTabla();
                }
            }
            break;
        }

        //bufferPool.MostrarTabla();

        std::cout << "Desea ver el porcentaje de disponibilidad de cada pagina? (s/n) ";
        std::cin >> respuesta;
        if (respuesta == "s") {
            gestorPaginas.FileSpaceMap();
        }

        std::cout << "Desea mostrar los datos de la tabla de algun frame? (si/no): ";
        std::cin >> respuesta;
        if (respuesta == "si") {
            int frameID;
            std::cout << "Ingrese el ID del frame: ";
            std::cin >> frameID;
            imprimirFrame(frameID);
        }

        std::cout << "Desea imprimir las colas de consultas? (si/no): ";
        std::cin >> respuesta;
        if (respuesta == "si") {
            ImprimirColasDeConsultas();
        }

        std::cout << "Desea liberar o despinear algun frame? (si/no): ";
        std::cin >> respuesta;
        if (respuesta == "si") {
            PreguntarLiberarODespinear();
        }

    }
    // Autor: Karla Cornejo
    void ImprimirColasDeConsultas() {
        std::cout << "Colas de Consultas:\n";
        for (const auto& entry : colasDeConsultas) {
            int pageID = entry.first;
            BufferPool::Frame* frame = BuscarFramePorPagina(pageID);
            if (frame) {
                std::cout << "Pagina ID: " << pageID << "\n";
                std::queue<Consulta> copiaCola = entry.second;
                while (!copiaCola.empty()) {
                    const Consulta& consulta = copiaCola.front();
                    std::cout << "  Accion: " << consulta.accion 
                            << ", Contenido: " << (consulta.contenido.empty() ? "(vacio)" : consulta.contenido)
                            << ", Completada: " << (consulta.completada ? "Si" : "No") << "\n";
                    copiaCola.pop();
                }
            }
        }
    }
    // Autor: Karla Cornejo y Lizardo Castillo
    void imprimirFrame(int frameID) {
        BufferPool::Frame* frame = BuscarFrame(frameID);
        if (frame) {
            std::cout << "Frame ID: " << frame->frameID << std::endl;
            std::cout << "Page ID: " << frame->pageID << std::endl;
            std::cout << "Dirty Bit: " << frame->dirtyBit << std::endl;
            std::cout << "Pinned: " << frame->pinned << std::endl;
            std::cout << "Pin Count: " << frame->pinCount << std::endl;
            std::cout << "Ref Bit: " << frame->refBit << std::endl;
        } else {
            std::cout << "No se encontro el frame con ID " << frameID << std::endl;
        }
    }
    // Autor: Karla Cornejo
    bool longitudFija(const std::string& esquemaArchivo, const std::string& nombrePagina, const std::string& nombreBloque, BufferPool::Frame& frame, BufferPool& bufferPool) {
        // Leer el esquema desde el archivo
        std::vector<Campo> esquema = leerEsquema(esquemaArchivo);
        std::string contenido;
        std::string respuesta;

        for (const Campo& campo : esquema) {
            std::string valor;
            std::cout << "Ingrese el valor para " << campo.nombre << " (" << campo.tipo_dato << ", " << campo.cantidad_bytes << " bytes): ";
            std::cin >> valor;

            // Aseguramos que el valor ocupe exactamente campo.cantidad_bytes caracteres
            valor.resize(campo.cantidad_bytes, ' ');
            contenido += valor;
        }

        std::cout << "Desea guardar el contenido? (si/no): ";
        std::cin >> respuesta;

        if (respuesta == "si") {
            frame.dirtyBit = true;
            bufferPool.ActualizarTabla();
            gestorPaginas.agregarInformacionAPagina(frame.pageID - 1, contenido);
            std::ofstream outFileB(nombreBloque, std::ios::app);

            if (outFileB.is_open()) {
                outFileB << contenido;
                outFileB << std::endl;
                outFileB.close();
                return true;
            } else {
                std::cerr << "No se pudo escribir en el archivo de la pagina." << std::endl;
            }
        }

        return false;
    }
    // Autor: Karla Cornejo
    void longitudVariable(const std::string& esquemaArchivo, std::string nombrePagina, std::string nombreBloque, BufferPool::Frame& frame, BufferPool& bufferPool) {
        LinkedList list;
        std::vector<std::pair<std::string, std::string>> schema = parseSchema("esquemaV.txt");

        for (const auto& field : schema) {
            std::string name = field.first;
            std::string type = field.second;

            if (type == "varchar") {
                int capacity;
                std::cout << "Ingrese la capacidad de almacenamiento para " << name << ": ";
                std::cin >> capacity;
                std::string value;
                std::cout << "Ingrese el valor para " << name << ": ";
                std::cin.ignore();
                std::getline(std::cin, value);
                list.addVarcharValue(value, capacity);
            } else if (type == "int") {
                int value;
                std::cout << "Ingrese el valor para " << name << ": ";
                std::cin >> value;
                list.addIntValue(value);
            }
        }

        std::cout << "Desea guardar el contenido? (si/no): ";
        std::string respuesta;

        std::cin >> respuesta;
        if (respuesta == "si") {
            frame.dirtyBit = true;
            bufferPool.ActualizarTabla();
            list.saveToFile(nombrePagina);
            list.saveToFile(nombreBloque);
            //gestorPaginas.agregarInformacionAPagina(frame.pageID - 1, nombreBloque);
        }

        // Imprimir lista para verificación
        list.printList();
    }
    // Autor: Karla Cornejo y Lizardo Castillo
    void ActualizarLRU(int pageID) {
        if (mapaLRU.find(pageID) != mapaLRU.end()) {
            listaLRU.erase(mapaLRU[pageID]);
        }
        listaLRU.push_front(pageID);
        mapaLRU[pageID] = listaLRU.begin();
    }
    // Autor: Karla Cornejo y Lizardo Castillo
    void LRU(int pageID) {
        while (!listaLRU.empty()) {
            int lruPageID = listaLRU.back();
            listaLRU.pop_back();
            mapaLRU.erase(lruPageID);
            BufferPool::Frame* frame = BuscarFramePorPagina(lruPageID);
            if (frame && !frame->pinned && frame->pinCount == 0) {
                frame->pageID = pageID;
                frame->pinCount = 0;
                frame->dirtyBit = false;
                frame->pinned = false;
                frame->refBit = false;
                ActualizarLRU(pageID);
                bufferPool.ActualizarTabla();
                return;
            }
        }
        std::cerr << "No se pudo encontrar una pagina no anclada para reemplazar." << std::endl;
        PreguntarLiberarODespinear();
    }
// Autor: Karla Cornejo y Lizardo Castillo
    void AlgoritmoClock(int pageID) {
        int framesChecked = 0;
        while (framesChecked < bufferPool.frames.size()) {
            BufferPool::Frame& frame = bufferPool.frames[punteroReloj];
            if (!frame.refBit && !frame.pinned && frame.pinCount == 0) {
                frame.pageID = pageID;
                frame.dirtyBit = false;
                frame.pinned = false;
                frame.pinCount = 0;
                frame.refBit = true;
                bufferPool.ActualizarTabla();
                punteroReloj = (punteroReloj + 1) % bufferPool.frames.size();
                return;
            } else {
                frame.refBit = false;
                punteroReloj = (punteroReloj + 1) % bufferPool.frames.size();
                framesChecked++;
            }
        }
        std::cerr << "Frame actual no disponibles para reemplazar, consulta el siguiente frame." << std::endl;
        PreguntarLiberarODespinear();
    }
    // Autor: Karla Cornejo y Lizardo Castillo
    BufferPool::Frame* BuscarFrame(int frameId) {
        for (auto& frame : bufferPool.frames) {
            if (frame.frameID == frameId) {
                return &frame;
            }
        }
        return nullptr;
    }
    // Autor: Karla Cornejo y Lizardo Castillo
    BufferPool::Frame* BuscarFramePorPagina(int pageID) {
        for (auto& frame : bufferPool.frames) {
            if (frame.pageID == pageID) {
                return &frame;
            }
        }
        return nullptr;
    }
    // Autor: Karla Cornejo y Lizardo Castillo
    BufferPool::Frame* BuscarFrameVacio() {
        for (auto& frame : bufferPool.frames) {
            if (frame.pageID == 0) {
                return &frame;
            }
        }
        return nullptr;
    }
    // Autor: Lizardo Castillo
    void PreguntarLiberarODespinear() {
        std::string respuesta;
        std::cout << "Desea liberar algun frame? (si/no): ";
        std::cin >> respuesta;
        if (respuesta == "si") {
            int frameID;
            std::cout << "Ingrese el ID del frame: ";
            std::cin >> frameID;
            BufferPool::Frame* frame = BuscarFrame(frameID);
            if (frame && frame->pinCount > 0) {
                frame->pinCount--;
                colasDeConsultas[frame->pageID].pop();
                bufferPool.ActualizarTabla();
            } else {
                std::cerr << "Frame no encontrado o pinCount ya es 0." << std::endl;
            }
        }

        std::cout << "Desea despinear (desanclar) algun frame? (si/no): ";
        std::cin >> respuesta;
        if (respuesta == "si") {
            int frameID;
            std::cout << "Ingrese el ID del frame: ";
            std::cin >> frameID;
            BufferPool::Frame* frame = BuscarFrame(frameID);
            if (frame && frame->pinned) {
                frame->pinned = false;
                bufferPool.ActualizarTabla();
            } else {
                std::cerr << "Frame no encontrado o no esta pineado." << std::endl;
            }
        }
    }
    // Autor: Karla Cornejo y Lizardo Castillo
    void ActualizarDirtyBit(int pageID) {
        BufferPool::Frame* frame = BuscarFramePorPagina(pageID);
        if (!frame) return;

        std::queue<Consulta>& cola = colasDeConsultas[pageID];
        std::queue<Consulta> copiaCola = cola;
        bool tieneEscritura = false;
        while (!copiaCola.empty()) {
            if (copiaCola.front().accion == 'e') {
                tieneEscritura = true;
                break;
            }
            copiaCola.pop();
        }
        frame->dirtyBit = tieneEscritura;
        bufferPool.ActualizarTabla();
    }
};

// Autor: Lizardo Castillo
void menuDisco() {
    int opcionDisco;
    int nroPlato, nroSuperficie, nroPistaxSuperficie, nroSectorxPista, byteSector;
    int capacidadDisco;
    std::cout << "Especificaciones del Disco:" << std::endl;
    do {
        std::cout << "(1) Disco por Defecto" << std::endl;
        std::cout << "(2) Disco Personalizado" << std::endl;
        std::cout << "(0) Salir" << std::endl;
        std::cout << "Ingrese su opcion: ";
        std::cin >> opcionDisco;
        switch (opcionDisco) {
            case 1:
                nroPlato = 8;
                nroSuperficie = 2;
                nroPistaxSuperficie = 8192;
                nroSectorxPista = 128;
                byteSector = 4096;
                std::cout << "Disco por Defecto..." << std::endl;
                opcionDisco = 0;
                break;
            case 2:
                std::cout << "Nro de Platos: ";
                std::cin >> nroPlato;
                nroSuperficie = 2;
                std::cout << "Nro de Pistas x Superficie: ";
                std::cin >> nroPistaxSuperficie;
                std::cout << "Nro de Sectores x Pista: ";
                std::cin >> nroSectorxPista;
                std::cout << "Byte por Sector: ";
                std::cin >> byteSector;
                std::cout << "Disco Personalizado..." << std::endl;
                opcionDisco = 0;
                break;
            case 0:
                std::cout << "Saliendo del programa..." << std::endl;
                break;
            default:
                std::cout << "Opcion invalida. Por favor ingrese una opcion valida" << std::endl;
        }
    } while (opcionDisco != 0);
    Disco disco(nroPlato, nroSuperficie, nroPistaxSuperficie, nroSectorxPista, byteSector);
    disco.crearDisco();
    disco.verCapacidadDisco();
}
// Autor: Lizardo Castillo
void menu() {
    std::cout << "Megatron..." << std::endl;
    std::cout << "Menu:" << std::endl;
    int opcionMenu;
    do {
        std::cout << "(1) Crear Disco" << std::endl;
        std::cout << "(0) Salir" << std::endl;
        std::cout << "Ingrese su opcion: ";
        std::cin >> opcionMenu;
        switch (opcionMenu) {   
            case 1:
                std::cout << "Disco..." << std::endl;
                menuDisco();
                opcionMenu = 0;
            case 0:
                std::cout << "Saliendo del programa..." << std::endl;
                break;
            default:
                std::cout << "Opcion invalida. Por favor ingrese una opcion valida" << std::endl;
        }
    } while (opcionMenu != 0);
}

int main() {
    menu();
    GestorPaginas gestor;
    gestor.ejecutar();
    BufferPool bufferPool;
    bufferPool.MenuBufferPool();
    bufferPool.MostrarTabla();
    BufferManager bufferManager(bufferPool, gestor);
    bufferManager.MenuBufferManager();
    return 0;
}
