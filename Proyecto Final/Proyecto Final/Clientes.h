#pragma once
#include "ConexionBD.h"
#include <iostream>
#include <mysql.h>
#include <string>

using namespace std;

class Clientes {
private:
    int id_Cliente = 0;
    string nombres, apellidos, NIT, telefono, correo_electronico, fecha_ingreso;
    bool genero;

public:
    Clientes() {}

    Clientes(int id, string nom, string ape, string nit, bool gen, string tel, string correo, string fecha)
        : id_Cliente(id), nombres(nom), apellidos(ape), NIT(nit), genero(gen), telefono(tel), correo_electronico(correo), fecha_ingreso(fecha) {
    }


    void setIdCliente(int id) { id_Cliente = id; }
    void setNombres(string n) { nombres = n; }
    void setApellidos(string a) { apellidos = a; }
    void setNIT(string nit) { NIT = nit; }
    void setGenero(bool g) { genero = g; }
    void setTelefono(string t) { telefono = t; }
    void setCorreo(string c) { correo_electronico = c; }
    void setFechaIngreso(string f) { fecha_ingreso = f; }


    int getIdCliente() { return id_Cliente; }
    string getNombres() { return nombres; }
    string getApellidos() { return apellidos; }
    string getNIT() { return NIT; }
    bool getGenero() { return genero; }
    string getTelefono() { return telefono; }
    string getCorreo() { return correo_electronico; }
    string getFechaIngreso() { return fecha_ingreso; }

    void crear() {
        int q_estado;
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string consulta = "INSERT INTO clientes (nombres, apellidos, NIT, genero, telefono, correo_electronico, fechaingreso) VALUES ('"
                + nombres + "', '" + apellidos + "', '" + NIT + "', " + (genero ? "1" : "0") + ", '" + telefono + "', '" + correo_electronico + "', '" + fecha_ingreso + "');";

            const char* c = consulta.c_str();
            q_estado = mysql_query(cn.getConector(), c);

            if (!q_estado) {
                cout << "Cliente agregado exitosamente.\n";
                int id = mysql_insert_id(cn.getConector());
                cout << "Nuevo ID asignado: " << id << endl;
            }
            else {
                cout << "Error al insertar cliente.\n";
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

        if (cn.getConector()) {
            string consulta = "SELECT * FROM clientes ORDER BY fechaingreso DESC;";
            const char* c = consulta.c_str();
            mysql_query(cn.getConector(), c);

            resultado = mysql_store_result(cn.getConector());

            while ((fila = mysql_fetch_row(resultado))) {
                bool gen = fila[4][0] != 0;
                cout << "ID: " << fila[0] << ", Nombres: " << fila[1] << ", Apellidos: " << fila[2]
                    << ", NIT: " << fila[3] << ", Genero: " << (gen ? "Masculino" : "Femenino")
                    << ", Telefono: " << fila[5] << ", Correo: " << fila[6]
                    << ", Fecha Ingreso: " << fila[7] << endl;
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
            string idStr = to_string(id_Cliente);
            string consulta = "UPDATE clientes SET nombres='" + nombres + "', apellidos='" + apellidos + "', NIT='" + NIT +
                "', genero=" + (genero ? "1" : "0") + ", telefono='" + telefono + "', correo_electronico='" + correo_electronico +
                "', fechaingreso='" + fecha_ingreso + "' WHERE idCliente=" + idStr + ";";

            const char* c = consulta.c_str();
            if (!mysql_query(cn.getConector(), c)) {
                cout << "Cliente actualizado correctamente.\n";
            }
            else {
                cout << "Error al actualizar.\n";
            }
        }
        else {
            cout << "Error en la conexion.\n";
        }
        cn.cerrar_conexion();
    }

    void borrar() {
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string idStr = to_string(id_Cliente);
            string consulta = "DELETE FROM clientes WHERE idCliente=" + idStr + ";";
            const char* c = consulta.c_str();

            if (!mysql_query(cn.getConector(), c)) {
                cout << "Cliente eliminado correctamente.\n";
            }
            else {
                cout << "Error al eliminar cliente.\n";
            }
        }
        else {
            cout << "Error en la conexion.\n";
        }
        cn.cerrar_conexion();
    }
};


