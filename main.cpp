/* 
    Hola, este codigo esta lleno de comentarios para facilitar la colaboración. Inicialmente tenía comentarios fuera de
    lugar, pero al ver una rúbrica estos se re ajustaron. Para Empezar Nuestros Datos:
    -José Angel Gabriel Carrillo Gamboa A01802775
    -José María Avilez Días A01803596     

    Este código borro muchos de los comentarios de la estructura inicial, para facilitar el entendimiento de nosotros,
    agregamos diferentes comentarios que explican cada bloque. Este código su logica fue:

    (1) Leer Datos -> (2) Libre Manipulación De Cada Dato -> (3) Insertar Datos En Structures -> (4) Crear Archivo Ordenado

    Durante el código abra lineas en comentarios que fueron parte del prueba y error de este código. Mismos están señalados

*/

/*
    Sobre Librerias:
    Libreria que agregamos, La clasica: iostream, ctime: Uso De Tiempos, String: Para Agregar Palabras, Vector: Vectores,
    Algorithm: Método sort y otras cajitas de herramientas.

    NOTA: Agregamos fstream para la manipulación de archivos. Fue fundamental para la manipulación del mismo.
    NOTA 2: Agregamos sstream, esta libreria permite entubar variables para una lectura más optimizada esta 
            misma biblioteca nos permitio que el código estuviera más limpio y se manejara por bloques.
*/
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

//Estos son atajos
using std::cin;
using std::cout;
using std::string;
using std::vector;

// Este es un struct: Clase sin metodos, construye algo parecido a un objeto.
struct ip {
    int o1;
    int o2;
    int o3;
    int o4;
};

// Este es el STRUCT, nos permitira unificar todo de nuevo para su manipulación. (¡Gracias Profesor!)
struct event {
  struct std::tm ts;
  struct ip ip_o;
  string port_o;
  string domain_o;
  struct ip ip_d;
  string port_d;
  string domain_d;
};

//Sobrecarga de operador para un manejo más sencillo de las ips.
std::ostream& operator<<(std::ostream &os, const ip &i) {
    if(i.o1 == 0) {
        os << "-";
    } else {
       os << i.o1 << "." << i.o2 << "." << i.o3 << "." << i.o4;   
    }
    return os;
}

//Sobrecarga de operador para la manipulación final de los datos.
std::ostream& operator<<(std::ostream &os, const event &e) {
    char date_output[20];
    strftime(date_output, 20, "%d-%m-%Y,%T", &e.ts);
    os << date_output << "," << e.ip_o << "," << e.port_o << "," 
		<< e.domain_o << "," << e.ip_d << "," << e.port_d << "," 
		<< e.domain_d;
    return os;
}

/*
    IMPORTANTISIMO "bool operator<(const event &e1, const event &e2) {" 
    es la sobrecarga de un operador que el profesor no modifico. Ahora modificado
    permite que al usar los datos ya esten ordenados en base a que se compararon.

*/
bool operator<(const event &e1, const event &e2) {
    if (e1.ts.tm_year != e2.ts.tm_year) return e1.ts.tm_year < e2.ts.tm_year;
    if (e1.ts.tm_mon != e2.ts.tm_mon) return e1.ts.tm_mon < e2.ts.tm_mon;
    if (e1.ts.tm_mday != e2.ts.tm_mday) return e1.ts.tm_mday < e2.ts.tm_mday;
    if (e1.ts.tm_hour != e2.ts.tm_hour) return e1.ts.tm_hour < e2.ts.tm_hour;
    if (e1.ts.tm_min != e2.ts.tm_min) return e1.ts.tm_min < e2.ts.tm_min;
    return e1.ts.tm_sec < e2.ts.tm_sec;
}

int main() { 
    /*
        Apartadoo Para Trabajar OwO
    */
    vector<event> v{};

    // Paso 1: Abrir El Archivo y Manejo De Errores
    std::ifstream ArchivoDesordenado("equipo3.csv");
    if (!ArchivoDesordenado.is_open()){ //Por si el archivo no esta en la carpeta o hay un error al abrirlo.
        std::cout<< "Ningún archivo se ha encontrado, revisa si lo tienes en la misma carpeta o si no esta corrupto.";
        return 1;
    }
    // Paso 1.5: Lectura De Archivo Linea Por Linea 
    std::string fila_Archivo;
    while(getline(ArchivoDesordenado, fila_Archivo)){
        if (!fila_Archivo.empty() && fila_Archivo.back() == '\r') fila_Archivo.pop_back();
        if (fila_Archivo.empty()) continue;
        //std::cout<<fila_Archivo<<"\n"; //**NOTA: YA LO LEE, SI QUIERES PROBAR USA esta linea
        std::stringstream metodo_separador(fila_Archivo);
        /*  Paso 1.8: Separación Correcta De Variables
            El siguiente paso fue crear variables temporales, lo que hará este bucle será leer, guardar 
            y separar los datos correctamente para usar las bases que nos dejo el profesor.

        */
        std::string fecha, hora, ip_o, puerto_o, nombre_o, ip_d, puerto_d, nombre_d;
        getline(metodo_separador, fecha, ',');
        getline(metodo_separador, hora, ',');
        getline(metodo_separador, ip_o, ',');
        getline(metodo_separador, puerto_o, ',');
        getline(metodo_separador, nombre_o, ',');
        getline(metodo_separador, ip_d, ',');
        getline(metodo_separador, puerto_d, ',');
        getline(metodo_separador, nombre_d, ',');
        //std::cout << "Fecha separada: " << fecha << " | IP de origen: " << ip_o << "\n"; //Esta línea es una prueba aca pa ver si se dividio bonito.

        /*
            Paso 2: Ya partimos los datos por columna, ahora otra partición por operador "-", ".", "etc etc"
        */
        std::stringstream metodo_Separador_2(fecha);

        //Paso 2.2: Creamos De Nuevo Variables Como Antes Pero Para La Variable Fecha
        std::string dia, mes, año;
        getline(metodo_Separador_2, dia,'-');
        getline(metodo_Separador_2, mes,'-');
        getline(metodo_Separador_2, año,'-');
        //std::cout <<"Fecha Separada Por Partes " << dia <<"-" << mes <<"-" << año << "\n"; //Esta línea prueba que la variable este bien separada

        // PASO 3: HACEMOS LO MISMO CON CADA VARIABLE, SE QUE DEBERIA HACER UNA FUNCION PERO LA NETA NO SUPE COMO

        // --- EL TUBO DE LA HORA ---
        std::stringstream tuboHora(hora);
        std::string h, m, s;
        getline(tuboHora, h, ':');
        getline(tuboHora, m, ':');
        getline(tuboHora, s, ':');

        // EL TUBO DE LA IP DE ORIGEN ---
        std::stringstream tuboIP_O(ip_o);
        std::string ip_o1, ip_o2, ip_o3, ip_o4;
        getline(tuboIP_O, ip_o1, '.');
        getline(tuboIP_O, ip_o2, '.');
        getline(tuboIP_O, ip_o3, '.');
        getline(tuboIP_O, ip_o4, '.');
        // EL TUBO DE LA IP DE DESTINO ---
        std::stringstream tuboIP_D(ip_d);
        std::string ip_d1, ip_d2, ip_d3, ip_d4;
        getline(tuboIP_D, ip_d1, '.');
        getline(tuboIP_D, ip_d2, '.');
        getline(tuboIP_D, ip_d3, '.');
        getline(tuboIP_D, ip_d4, '.');
        
        /*
            HUBO UN ERROR AL CORRER EL PROGRAMA CON EL STOI, ENTONCES ESTA ES LA SOLUCIÓN DE EMERGENCIA:
        */
        //Estas 2 lineas en especifico fue por un error que salio en c++, esto lo soluciona.
        if (ip_o == "-" || ip_o == "") { ip_o1 = "0"; ip_o2 = "0"; ip_o3 = "0"; ip_o4 = "0"; }
        if (ip_d == "-" || ip_d == "") { ip_d1 = "0"; ip_d2 = "0"; ip_d3 = "0"; ip_d4 = "0"; }

        // PASO 4: Una vez parametrizado, insertar los datos en el formato del main.
        event eventoNuevo{};
        eventoNuevo.ts.tm_mday = stoi(dia);
        eventoNuevo.ts.tm_mon = stoi(mes) - 1;       
        eventoNuevo.ts.tm_year = stoi(año) - 1900;  
        
        eventoNuevo.ts.tm_hour = stoi(h);
        eventoNuevo.ts.tm_min = stoi(m);
        eventoNuevo.ts.tm_sec = stoi(s);

        // Metemos las IPs
        eventoNuevo.ip_o = {stoi(ip_o1), stoi(ip_o2), stoi(ip_o3), stoi(ip_o4)};
        eventoNuevo.ip_d = {stoi(ip_d1), stoi(ip_d2), stoi(ip_d3), stoi(ip_d4)};
        // Metemos textos directos
        eventoNuevo.port_o = puerto_o;
        eventoNuevo.port_d = puerto_d;
        eventoNuevo.domain_o = nombre_o;
        eventoNuevo.domain_d = nombre_d;

        // Meter todo En Una Nueva Lista Con Evento
        v.push_back(eventoNuevo);
    }
    // PASO 5: Una vez acomodados los datos, hora de aplicar el sort.
    std::sort(v.begin(), v.end());

    // Mensaje de exito de prueba
    std::cout << "\n¡Archivo leido, separado y ordenado con exito! Total de eventos: " << v.size() << "\n";

   // Paso 5.5: ofstream Para Un Archivo Ordenado
   std::ofstream ArchivoOrdenado("equipo3_ordenado.csv");
    if (!ArchivoOrdenado.is_open()) {
        cout << "No se pudo crear el archivo de salida.\n";
        return 1;
    }
    for (const event &ev : v) {
        ArchivoOrdenado << ev << "\n";
    }
    ArchivoOrdenado.close(); 
   // PASO 6: Implementar Find
    int dia_buscado, mes_buscado, año_buscado;
    cout << "Ingresa una fecha (dia mes año): ";
    cin >> dia_buscado >> mes_buscado >> año_buscado;

    int fecha_buscada = año_buscado * 10000 + mes_buscado * 100 + dia_buscado;

    auto it = std::find_if(v.begin(), v.end(), [fecha_buscada](const event &e) {
        int fecha_evento = (e.ts.tm_year + 1900) * 10000
                        + (e.ts.tm_mon + 1) * 100
                        + e.ts.tm_mday;
        return fecha_evento >= fecha_buscada;
    });

    if (it == v.end()) {
        cout << "No hay eventos a partir de esa fecha.\n";
    } else {
        for (; it != v.end(); ++it) {
            cout << *it << "\n";
        }
    }

    return 0;
}