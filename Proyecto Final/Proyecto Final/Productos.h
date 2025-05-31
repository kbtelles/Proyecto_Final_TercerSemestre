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
                int id = mysql_insert_id(cn.getConector());
                cout << "Nuevo ID asignado: " << id << endl;
            }
            else {
                cout << "Error al insertar producto.\n" << mysql_error(cn.getConector());
            }
        }
        else {
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
    };
    
