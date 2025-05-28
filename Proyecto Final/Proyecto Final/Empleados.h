
#pragma once
#include "Puestos.h"
#include "ConexionBD.h"
#include <iostream>
#include <mysql.h>
#include <string>

using namespace std;

class Empleados : public Puestos {
private:
    int IdEmpleado = 0;
    string nombres, apellidos, direccion, telefono, DPI, FechaNacimiento, FechaInicioLabores, FechaIngreso;
    bool genero;

public:
    Empleados() {}

    Empleados(int id_puesto, string puesto, int id_e, string nom, string ape, string dire, string tel, string dpi, bool g, string fn, string fil, string fi)
        : Puestos(id_puesto, puesto) {

        IdEmpleado = id_e;
        nombres = nom;
        apellidos = ape;
        direccion = dire;
        telefono = tel;
        DPI = dpi;
        FechaNacimiento = fn;
        FechaInicioLabores = fil;
        FechaIngreso = fi;
        genero = g;

    }


    //METODOS SET (MODIFICIAR UN ATRIBUTO)
    
    void setPuestos(string p) { Puesto = p; }
    void setidPuestos(short ip) { idPuestos = ip; }
    void setId_empleado(int e) { IdEmpleado = e; }
    void setNombres(string n) { nombres = n; }
    void setApellidos(string a) { apellidos = a; }
    void setDireccion(string d) { direccion = d; }
    void setTelefono(string t) { telefono = t; }
    void setDPi(string dp) { DPI = dp; }
    void setFecha_Nacimiento(string f) { FechaNacimiento = f; }
    void setFechaInicioLabores(string fil) { FechaInicioLabores = fil; } 
    void setFecha_Ingreso(string fi) { FechaIngreso = fi; }
    void setGenero (bool g) { genero = g; }

        //METODOS GET (MOSTRAR EL CONTENIDO DE UN ATRIBUTO)
    string getPuestos() { return Puesto; }
    short getidPuestos() { return idPuestos ; }
    int getId_empleado() { return IdEmpleado; }
    string getNombres() { return nombres; }
    string getApellidos() { return apellidos; }
    string getDireccion() { return  direccion ; }
    string getTelefono() { return telefono ; }
    string getDPi() { return DPI ; }
    string getFecha_Nacimiento() { return FechaNacimiento ; }
    string getFechaInicioLabores() { return FechaInicioLabores ; }
    string getFecha_Ingreso() { return FechaIngreso ; }
    bool getGenero() { return genero ; }

 


    // Método crear en Empleados
    void crear() {
        int q_estado = 0;
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (cn.getConector()) {
            string idI = to_string(idPuestos);

            string consulta = "INSERT INTO empleados (nombres, apellidos, direccion, telefono, DPI, genero, fecha_nacimiento, idPuesto, fecha_inicio_labores, fechaingreso) VALUES ('"
                + nombres + "', '" + apellidos + "', '" + direccion + "', '" + telefono + "', '" + DPI + "', "
                + (genero ? "1" : "0") + ", '" + FechaNacimiento + "', " + idI + ", '" + FechaInicioLabores + "', now());"; 

            const char* c = consulta.c_str();
            q_estado = mysql_query(cn.getConector(), c);

            if (!q_estado) {
                cout << "Ingreso de datos exitoso .... " << endl;
                int id = mysql_insert_id(cn.getConector());
                cout << "Id de Empleado asignado: " << id << endl;
            }
            else {
                cout << "Consulta fallida: " << endl;
                
            }
        }
        else {
            cout << "Conexion fallida"  << endl;
        }
        cn.cerrar_conexion();
    }
    


    void leer() {
        int q_estado = 0;
        ConexionBD cn = ConexionBD();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrir_conexion();
        if (cn.getConector()) {
            cout << "________________Datos de los Empleados__________________\n" << endl;
            string consulta = "SELECT e.idEmpleado, e.nombres, e.apellidos, e.direccion, e.telefono, e.DPI, e.genero, e.fecha_nacimiento, e.fecha_inicio_labores, e.fechaingreso, p.puesto "
                "FROM empleados AS e "
                "INNER JOIN puestos AS p ON e.idPuesto = p.idPuesto "
                "ORDER BY e.fechaingreso DESC;";

            const char* c = consulta.c_str();
            q_estado = mysql_query(cn.getConector(), c);

            if (!q_estado) {
                resultado = mysql_store_result(cn.getConector());
                while ((fila = mysql_fetch_row(resultado))) {
                    bool genero = false;
                    if (fila[6] != nullptr) {
                        // fila[6] es un puntero a char, el primer byte contiene el valor del bit
                        genero = fila[6][0] != 0;
                    }
                    cout << "ID: " << fila[0] << ", Nombres: " << fila[1] << ", Apellidos: " << fila[2]
                        << ", Direccion: " << fila[3] << ", Telefono: " << fila[4]
                        << ", DPI: " << fila[5] << ", Genero: "<<(genero ? "Masculino" : "Femenino") 
                        << ", Fecha de Nacimiento: " << fila[7] << ", Puesto: " << fila[8]
                        << ", Fecha de Inicio de Labores: " << fila[9] << ", Fecha de Ingreso: " << fila[10] << 
                        "\n-------------------------------------------------------------------" << endl;
                    
                }
            }
            else {
                cout << "Consulta fallida" << endl;
            }
        }
        else {
            cout << "Fallo la conexion" << endl;
        }
        cn.cerrar_conexion();
    }


    void actualizar() {
        int q_estado = 0;
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (cn.getConector()) {
            string idI = to_string(idPuestos);
            string id_e = to_string(IdEmpleado);
            string consulta = "UPDATE empleados SET "
                "nombres='" + nombres + "', "
                "apellidos='" + apellidos + "', "
                "direccion='" + direccion + "', "
                "telefono='" + telefono + "', "
                "DPI='" + DPI + "', "
                "genero=" + (genero ? "1" : "0") + ", "
                "fecha_nacimiento='" + FechaNacimiento + "', "
                "idPuesto=" + idI + ", "
                "fecha_inicio_labores='" + FechaInicioLabores + "', "
                "fechaingreso='" + FechaIngreso + "' "
                "WHERE idEmpleado=" + id_e + ";";

            const char* c = consulta.c_str();
            q_estado = mysql_query(cn.getConector(), c);

            if (!q_estado) {
                cout << "Ingreso de datos exitoso .... " << endl;
            }
            else {
                cout << "Consulta fallida" << endl;
            }
        }
        else {
            cout << "Conexion fallida" << endl;
        }
        cn.cerrar_conexion();

    }

    void borrar() {
        int q_estado = 0;
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (cn.getConector()) {
            string idI = to_string(idPuestos);
            string id_e = to_string(IdEmpleado);
            string consulta = "delete from empleados WHERE idEmpleado=" + id_e + ";";
            const char* c = consulta.c_str();
            q_estado = mysql_query(cn.getConector(), c);

            if (!q_estado) {
                cout << "Eliminacion de datos exitoso .... " << endl;
            }
            else {
                cout << "Eliminacion fallida" << endl;
            }
        }
        else {
            cout << "Conexion fallida" << endl;
        }
        cn.cerrar_conexion();

    }

};


