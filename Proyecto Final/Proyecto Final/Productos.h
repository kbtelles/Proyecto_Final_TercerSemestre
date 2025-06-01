#pragma once
#include "ConexionBD.h"
#include <iostream>
#include <mysql.h>
#include <string>

using namespace std;

class Productos {
private:
    int idProducto = 0;
    string producto, descripcion, imagen, fecha_ingreso;
    int idMarca = 0;
    double precio_costo = 0.0, precio_venta = 0.0;
    int existencias = 0;

public:
    Productos() {}

    Productos(int id, string prod, int marcaId, string desc, string img, double pc, double pv, int ex, string fecha)
        : idProducto(id), producto(prod), idMarca(marcaId), descripcion(desc), imagen(img),
        precio_costo(pc), precio_venta(pv), existencias(ex), fecha_ingreso(fecha) {
    }

    void setIdProducto(int id) { idProducto = id; }
    void setProducto(string p) { producto = p; }
    void setIdMarca(int m) { idMarca = m; }
    void setDescripcion(string d) { descripcion = d; }
    void setImagen(string i) { imagen = i; }
    void setPrecioCosto(double pc) { precio_costo = pc; }
    void setPrecioVenta(double pv) { precio_venta = pv; }
    void setExistencias(int e) { existencias = e; }
    void setFechaIngreso(string f) { fecha_ingreso = f; }

    int getIdProducto() { return idProducto; }
    string getProducto() { return producto; }
    int getIdMarca() { return idMarca; }
    string getDescripcion() { return descripcion; }
    string getImagen() { return imagen; }
    double getPrecioCosto() { return precio_costo; }
    double getPrecioVenta() { return precio_venta; }
    int getExistencias() { return existencias; }
    string getFechaIngreso() { return fecha_ingreso; }



  
    void crear() {
        int q_estado;
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string consulta = "INSERT INTO productos (producto, idMarca, descripcion, imagen, precio_costo, precio_venta, existencia, fecha_ingreso) VALUES ('"
                + producto + "', " + to_string(idMarca) + ", '" + descripcion + "', '" + imagen + "', " + to_string(precio_costo)
                + ", " + to_string(precio_venta) + ", " + to_string(existencias) + ", now());";


            const char* c = consulta.c_str();
            q_estado = mysql_query(cn.getConector(), c);

            if (!q_estado) {
                cout << "Producto agregado exitosamente.\n";
                leer_puerto();

                int id = mysql_insert_id(cn.getConector());
                cout << "Nuevo ID asignado: " << id << endl;
            }
            else {
                cout << "Error al insertar producto.\n" << mysql_error(cn.getConector());
            }
        }
        else {
            //leer_puerto();
            cout << "Error en la conexión a la base de datos.\n";
        }
        cn.cerrar_conexion();
    }


    void leer() {
        ConexionBD cn;
        cn.abrir_conexion();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cout << "________________Datos de los Productos__________________\n" << endl;
        if (cn.getConector()) {
            string consulta = "SELECT p.idProducto, p.producto, m.marca, p.descripcion, p.imagen, p.precio_costo, p.precio_venta, p.existencia, p.fecha_ingreso "
                "FROM productos p INNER JOIN marcas m ON p.idMarca = m.idMarca "
                "ORDER BY p.fecha_ingreso DESC;";

            const char* c = consulta.c_str();
            mysql_query(cn.getConector(), c);
            resultado = mysql_store_result(cn.getConector());

            while ((fila = mysql_fetch_row(resultado))) {
                cout << "\nID: " << fila[0]
                    << ", Producto: " << fila[1]
                    << ", Marca: " << fila[2]
                    << ", Descripción: " << fila[3]
                    << ", Imagen: " << fila[4]
                    << ", Precio Costo: " << fila[5]
                    << ", Precio Venta: " << fila[6]
                    << ", Existencias: " << fila[7]
                    << ", Fecha Ingreso: " << fila[8] << 
                    "\n-------------------------------------------------------------------" << endl;
            }
        }
        else {
            cout << "Error en la conexión.\n";
        }
        cn.cerrar_conexion();
    }

  
    void actualizar() {
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string idStr = to_string(idProducto);
            string consulta = "UPDATE productos SET producto='" + producto + "', idMarca=" + to_string(idMarca)
                + ", descripcion='" + descripcion + "', imagen='" + imagen + "', precio_costo=" + to_string(precio_costo)
                + ", precio_venta=" + to_string(precio_venta) + ", existencia=" + to_string(existencias)
                + ", fecha_ingreso='" + fecha_ingreso + "' WHERE idProducto=" + idStr + ";";

            const char* c = consulta.c_str();
            if (!mysql_query(cn.getConector(), c)) {
                cout << "Producto actualizado correctamente.\n";
            }
            else {
                cout << "Error al actualizar producto.\n";
            }
        }
        else {
            cout << "Error en la conexión.\n";
        }
        cn.cerrar_conexion();
    }

 
    void borrar() {
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string idStr = to_string(idProducto);
            string consulta = "DELETE FROM productos WHERE idProducto=" + idStr + ";";
            const char* c = consulta.c_str();

            if (!mysql_query(cn.getConector(), c)) {
                cout << "Producto eliminado correctamente.\n";
            }
            else {
                cout << "Error al eliminar producto.\n";
            }
        }
        else {
            cout << "Error en la conexión.\n";
        }
        cn.cerrar_conexion();
    }

    int leer_puerto()
    {
        HANDLE hSerial = CreateFile(
            L"COM3",              // Nombre del puerto
            GENERIC_WRITE,       // habitar solo escritura en el puerto
            0,                   // No se comparte el puerto
            NULL,                // Seguridad predeterminada
            OPEN_EXISTING,       // Abrir el puerto solo si ya existe
            0,                   // Sin banderas adicionales
            NULL);               // Sin plantilla de archivo

        // 2. Se abrió correctamente el puerto
        if (hSerial == INVALID_HANDLE_VALUE) {
            std::cerr << "Error abriendo el puerto COM" << std::endl;
            return 1;  // Salir con código de error
        }

        // 3. Estructura para configurar el puerto serie
        DCB dcbSerialParams = { 0 };              // Estructura para parámetros del puerto
        dcbSerialParams.DCBlength = sizeof(dcbSerialParams);  // Tamaño de la estructura

        // 4. Obtener configuración actual del puerto
        if (!GetCommState(hSerial, &dcbSerialParams)) {
            std::cerr << "No se pudo obtener la configuración del puerto" << std::endl;
            CloseHandle(hSerial);  // Cerramos el puerto antes de salir
            return 1;
        }

        // 5. Configurar parámetros del puerto (deben coincidir con Serial.begin(9600))
        dcbSerialParams.BaudRate = CBR_9600;    // Velocidad de transmisión (baudios)
        dcbSerialParams.ByteSize = 8;           // 8 bits por byte
        dcbSerialParams.StopBits = ONESTOPBIT;  // 1 bit de parada
        dcbSerialParams.Parity = NOPARITY;    // Sin paridad

        // 6. Se aplica configuración
        if (!SetCommState(hSerial, &dcbSerialParams)) {
            std::cerr << "No se pudo configurar el puerto" << std::endl;
            CloseHandle(hSerial);
            return 1;
        }

        // 7. Configurar timeouts de escritura
        COMMTIMEOUTS timeouts = { 0 };
        timeouts.WriteTotalTimeoutConstant = 50;  // Tiempo máximo total para escritura
        SetCommTimeouts(hSerial, &timeouts);

        // 8. Preparar el dato a enviar
        DWORD bytesWritten;            // Variable que almacenará cuántos bytes se escribieron
        char data[] = "1";             // Este es el carácter que enviamos al Arduino

        // 9. Enviar el dato por el puerto serial
        if (!WriteFile(hSerial, data, sizeof(data) - 1, &bytesWritten, NULL)) {
            std::cerr << "Error escribiendo en el puerto" << std::endl;
            CloseHandle(hSerial);
            return 1;
        }

       
        // 11. Cerrar el puerto COM al terminar
        CloseHandle(hSerial);


    };
   

    };
    
