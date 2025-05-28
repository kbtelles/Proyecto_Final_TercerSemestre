#pragma once
#include "ConexionBD.h"
#include <iostream>
#include <mysql.h>
#include <string>

using namespace std;

class Proveedores {
private:
    int idProveedor = 0;
    string proveedor, nit, direccion, telefono;

public:
    Proveedores() {}

    Proveedores(int id, string prov, string n, string dir, string tel)
        : idProveedor(id), proveedor(prov), nit(n), direccion(dir), telefono(tel) {
    }

    // Setters
    void setIdProveedor(int id) { idProveedor = id; }
    void setProveedor(string p) { proveedor = p; }
    void setNIT(string n) { nit = n; }
    void setDireccion(string d) { direccion = d; }
    void setTelefono(string t) { telefono = t; }

    // Getters
    int getIdProveedor() { return idProveedor; }
    string getProveedor() { return proveedor; }
    string getNIT() { return nit; }
    string getDireccion() { return direccion; }
    string getTelefono() { return telefono; }

    // CRUD
    void crear() {
        int q_estado;
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string consulta = "INSERT INTO proveedores (proveedor, nit, direccion, telefono) VALUES ('"
                + proveedor + "', '" + nit + "', '" + direccion + "', '" + telefono + "');";

            const char* c = consulta.c_str();
            q_estado = mysql_query(cn.getConector(), c);

            if (!q_estado) {
                cout << "Proveedor agregado exitosamente.\n";
                int id = mysql_insert_id(cn.getConector());
                cout << "ID asignado: " << id << endl;
            }
            else {
                cout << "Error al insertar proveedor.\n" << mysql_error(cn.getConector());
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
        cout << "________________Datos de los Proveedores__________________\n" << endl;
        if (cn.getConector()) {
            string consulta = "SELECT * FROM proveedores;";
            const char* c = consulta.c_str();
            mysql_query(cn.getConector(), c);

            resultado = mysql_store_result(cn.getConector());

            while ((fila = mysql_fetch_row(resultado))) {
                cout << "ID: " << fila[0] << ", Proveedor: " << fila[1] << ", NIT: " << fila[2]
                    << ", Direccion: " << fila[3] << ", Telefono: " << fila[4] << "\n-------------------------------------------------------------------" << endl;
            }
        }
        else {
            cout << "Error en la conexion.\n";
        }
        cn.cerrar_conexion();
    }

    void actualizar() {
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string idStr = to_string(idProveedor);
            string consulta = "UPDATE proveedores SET proveedor='" + proveedor + "', nit='" + nit +
                "', direccion='" + direccion + "', telefono='" + telefono +
                "' WHERE idProveedor=" + idStr + ";";

            const char* c = consulta.c_str();
            if (!mysql_query(cn.getConector(), c)) {
                cout << "Proveedor actualizado correctamente.\n";
            }
            else {
                cout << "Error al actualizar proveedor.\n";
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
            string idStr = to_string(idProveedor);
            string consulta = "DELETE FROM proveedores WHERE idProveedor=" + idStr + ";";
            const char* c = consulta.c_str();

            if (!mysql_query(cn.getConector(), c)) {
                cout << "Proveedor eliminado correctamente.\n";
            }
            else {
                cout << "Error al eliminar proveedor.\n";
            }
        }
        else {
            cout << "Error en la conexión.\n";
        }
        cn.cerrar_conexion();
    }
};
