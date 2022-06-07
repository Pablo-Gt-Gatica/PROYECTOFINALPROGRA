#include <iostream> #include <mysql.h> #include <fstream>

using namespace std;

char serverdb[] = "localhost"; char userdb[] = "root";
char passworddb[] = "pabloGT"; char database[] = "profinal"; string sql;
const char* query; int result;

	void agregarAlu(MYSQL*);
	bool buscarClave(MYSQL*, string);
	void buscarAlu(MYSQL*);
	void mostrarPromedioAl(MYSQL*);
	void borrarAlumno(MYSQL*);
	void modificarAl(MYSQL*);
void listarAl(MYSQL *):




struct Nodo{

string dato;
Nodo *siguiente;
};

struct Cambio{

string nombre;
Cambio *siguiente;

};

Cambio *cimaDeshacer = NULL; Cambio *cimaRehacer = NULL;

bool pilaVaciarDeshacer(){
if (cimaDeshacer == NULL){ return true;
}

return false;

}











void agregarAlu(MYSQL *connection){
string id, edad, nombre, apellido, correo, telefono, grado, seccion;

		
		cout << "*************************************" << endl;
		cout << "*        Registro de Alumnos        *" << endl;
		cout << "************************************* \n" << endl;
		cout << "Clave de Alumno: ";
		cin.ignore(1, '\n');
		getline(cin, id);
		
		bool a = buscarClave(connection, id);
		
		while (a == 1) {
			
			cout << "La clave ingresada ya ha sido registrada!!" << endl;
			cout << "Clave de alumno: ";
			getline(cin, id);
			
			a = buscarClave(connection, id);
		
		}
		
		cout << "Nombre: ";
		getline(cin, nombre);
		cout << "Apellido: ";
		getline(cin, apellido);
		cout << "Edad: ";
		getline(cin, edad);
		cout << "Correo: ";
		getline(cin, correo);
		cout << "Telefono: ";
		getline(cin, telefono);
		cout << "Grado: ";
		getline(cin, grado);
		cout << "Seccion 1 = A, 2 = B, 3 = C: ";
		getline(cin, seccion); 
				
		sql = "insert into alumno (id_alumno, nombre, apellido, edad, correo, telefono, grado_id_grado, seccion_id_seccion) values ('" + id + "', '" + nombre + "', '" + apellido + "', '" + edad + "', '" + correo + "', '" + telefono + "', '" + grado + "', '" + seccion + "')";
				
		query = sql.c_str();
		result = mysql_query(connection, query);
				
		if (result == 0){
					
			cout << "\nRegistro guardado con exito!!\n" << endl;
			
		} else {
					
			cout << "\nNo fue posible guardar el registro!! \n" << mysql_error(connection) << endl;
		}
		
	}


void buscarAlu(MYSQL *connection){
	
		MYSQL_ROW row;
		MYSQL_RES* data;
		string id;

	
		cout << "****************************************" << endl;
		cout << "*            Buscar Alumno             *" << endl;
		cout << "**************************************** \n" << endl;
		cin.ignore(1, '\n');
		cout << "Ingrese clave de alumno: ";
		getline(cin, id);
		cout << "" << endl;
		
		sql = "select al.id_alumno, al.nombre, al.apellido, al.edad, al.correo, al.telefono, gr.grado, se.seccion from alumno as al join grado as gr on al.grado_id_grado = gr.id_grado join seccion as se on al.seccion_id_seccion = se.id_seccion where id_alumno = '" + id + "';";
		query = sql.c_str();
		result = mysql_query(connection, query);
		
		if (result == 0){
			
			data = mysql_store_result(connection);
			int countColumns = mysql_num_fields(data);
			
			while(row = mysql_fetch_row(data)){
				
				for (int i = 0; i < countColumns; i++){
					
					cout << row[i] << ", "; 
				}	
				
				cout << "\n" << endl;
				
			}
			
		} else {
			
			cout << "\nNo fue posible obtener los datos solicitados" << mysql_error(connection) << endl;
			
		}
	}

void borrarAlumno(MYSQL *connection){
		
		string id, sqlII;
		int sel, res; 
		
		cout << "****************************************" << endl;
		cout << "*           Eliminar Alumno            *" << endl;
		cout << "**************************************** \n" << endl;
		cout << "Clave del alumno: ";
		cin.ignore(1, '\n');
		getline(cin, id);
		
		cout << "\nConfirma eliminar alumno? 1. Si, 0. No: ";
		cin >> sel;
		
		if (sel == 1){
			
			sql = "delete from notas where alumno_id_alumno = '" + id + "'";
			query = sql.c_str();
			result = mysql_query(connection, query);
			
			sqlII = "delete from alumno where id_alumno = '" + id + "'";
			query = sqlII.c_str();
			res = mysql_query(connection, query);
			
			if (result == 0 && res == 0){
			
				cout << "\nRegistro eliminado con exito!!\n" << endl;
			
			} else {
			
				cout << "\nNo fue posible eliminar el registro!!\n" << mysql_error(connection) << endl;
			}
					
		} else {
			
			cout << "No se hicieron cambios!!" << endl;
		}
		
	}

void modificarAl(MYSQL *connection){
		
		string id, nuDato;
		int sel;
		
		cout << "****************************************" << endl;
		cout << "*      Modificar datos de Alumno       *" << endl;
		cout << "**************************************** \n" << endl;
		cout << "Clave Alumno: ";
		cin.ignore(1, '\n');
		getline(cin, id);
		
		cout << "Que dato desea modificar?\n " << endl;
		cout << "1. Nombre" << endl;
		cout << "2. Apellido" << endl;
		cout << "3. Edad" << endl;
		cout << "4. Correo" << endl;
		cout << "5. Telefono" << endl;
		cout << "6. Grado" << endl;
		cout << "7. Seccion" << endl;
		cin >> sel;
		
		switch (sel){
			
			case 1:
				//system("cls");
				cout << "\nNuevo nombre: ";
				cin.ignore(1, '\n');
				getline(cin, nuDato);
				sql = "update alumno set nombre = '" + nuDato + "' where id_alumno = '" + id + "'";
				query = sql.c_str();
				result = mysql_query(connection, query);
			
				if (result == 0){
				
					cout << "\nDato actualizado correctamente\n" << endl;
				
				} else {
				
					cout << "\nNo se pudo realizar la actualizacion requerida\n" << mysql_error(connection) << endl;
				}
				break;
				
			case 2:
				//system("cls");
				cout << "\nNuevo apellido: ";
				cin.ignore(1, '\n');
				getline(cin, nuDato);
				sql = "update alumno set apellido = '" + nuDato + "' where id_alumno = '" + id + "'";
				query = sql.c_str();
				result = mysql_query(connection, query);
			
				if (result == 0){
				
					cout << "\nDato actualizado correctamente\n" << endl;
				
				} else {
				
					cout << "\nNo se pudo realizar la actualizacion requerida\n" << mysql_error(connection) << endl;
				}
				break;
			
			case 3:
				//system("cls");
				cout << "\nNueva edad: ";
				cin.ignore(1, '\n');
				getline(cin, nuDato);
				sql = "update alumno set edad = '" + nuDato + "' where id_alumno = '" + id + "'";
				query = sql.c_str();
				result = mysql_query(connection, query);
			
				if (result == 0){
				
					cout << "\nDato actualizado correctamente\n" << endl;
				
				} else {
				
					cout << "\nNo se pudo realizar la actualizacion requerida\n" << mysql_error(connection) << endl;
				}
				break;
				
			case 4:
				//system("cls");
				cout << "\nNuevo correo: ";
				getline(cin, nuDato);
				sql = "update alumno set correo = '" + nuDato + "' where id_alumno = '" + id + "'";
				query = sql.c_str();
				result = mysql_query(connection, query);
			
				if (result == 0){
				
					cout << "\nDato actualizado correctamente\n" << endl;
				
				} else {
				
					cout << "\nNo se pudo realizar la actualizacion requerida\n" << mysql_error(connection) << endl;
				}
				break;
				
			case 5:
				//system("cls");
				cout << "\nNuevo telefono: ";
				cin.ignore(1, '\n');
				getline(cin, nuDato);
				sql = "update alumno set telefono = '" + nuDato + "' where id_alumno = '" + id + "'";
				query = sql.c_str();
				result = mysql_query(connection, query);
			
				if (result == 0){
				
					cout << "\nDato actualizado correctamente\n" << endl;
				
				} else {
				
					cout << "\nNo se pudo realizar la actualizacion requerida\n" << mysql_error(connection) << endl;
				}
				break;
				
			case 6:
				//system("cls");
				cout << "\nNuevo grado: ";
				cin.ignore(1, '\n');
				getline(cin, nuDato);
				sql = "update alumno set grado_id_grado = '" + nuDato + "' where id_alumno = '" + id + "'";
				query = sql.c_str();
				result = mysql_query(connection, query);
			
				if (result == 0){
				
					cout << "\nDato actualizado correctamente\n" << endl;
				
				} else {
				
					cout << "\nNo se pudo realizar la actualizacion requerida\n" << mysql_error(connection) << endl;
				}
				break;
				
			case 7:
				//system("cls");
				cout << "\nNueva seccion: ";
				cin.ignore(1, '\n');
				getline(cin, nuDato);
				sql = "update alumno set seccion_id_seccion = '" + nuDato + "' where id_alumno = '" + id + "'";
				query = sql.c_str();
				result = mysql_query(connection, query);
			
				if (result == 0){
				
					cout << "\nDato actualizado correctamente\n" << endl;
				
				} else {
				
					cout << "\nNo se pudo realizar la actualizacion requerida\n" << mysql_error(connection) << endl;
				}
				break;
				
		}
		
	}


bool pilaVaciarRehacer(){

if (cimaRehacer == NULL){ return true;
}

return false;

}




void pushDeshacer(string str) 
Cambio *cambio = new Cambio(); cambio->nombre = str;
cambio->siguiente = NULL; if (pilaVaciarDeshacer()){
cimaDeshacer = cambio; return;
}

cambio->siguiente = cimaDeshacer; cimaDeshacer = cambio;

}





void pushRehacer(string str){

Cambio *cambio = new Cambio(); cambio->nombre = str;
cambio->siguiente = NULL; if (pilaVaciarRehacer()){
cimaRehacer = cambio; return;
}

cambio->siguiente = cimaRehacer; cimaRehacer = cambio;

}

string popDeshacer(){

if (pilaVaciarDeshacer()){

cout << "No hay elementos para sacar" << endl; return "";
}

Cambio *cambio = cimaDeshacer; cimaDeshacer = cambio->siguiente;

cout << "Se restauro el cambio " << cambio->nombre << endl; string str = cambio->nombre;
//pushRehacer(str); delete(cambio); return str; }

string popRehacer(){

if (pilaVaciarRehacer()){

cout << "No hay elementos para sacar" << endl; return "";
}

Cambio *cambio = cimaRehacer; cimaRehacer = cambio->siguiente;

cout << "Se restauro el cambio " << cambio->nombre << endl; string str = cambio->nombre;
delete(cambio); return str;

}




void escrituraI(){ // Funcion para escribir en el archivo externo

ofstream file("prueba.txt", ios::app); string txt;
cin.ignore(1, '\n');
cout << "Ingresar texto: "; getline(cin, txt);

file << txt << endl; file.close();
}



void insertarLista(Nodo *&lista, string n){

Nodo *nuevo_nodo = new Nodo(); nuevo_nodo->dato = n;

Nodo *aux1 = lista;
Nodo *aux2;
while ((aux1 != NULL) && (aux1->dato < n)){ aux2 = aux1;
aux1 = aux1->siguiente;

}

if (lista == aux1){

lista = nuevo_nodo;
 } else {

aux2->siguiente = nuevo_nodo;

}

nuevo_nodo->siguiente = aux1;

cout << "El elemento " << n << " ha sido insertado correctamente" << endl;
}




void lecturaI(MYSQL *connection){

MYSQL_ROW row; MYSQL_RES* data; Nodo *lista = NULL; string datos;
int count;

sql = "select * from profinal"; query = sql.c_str();
result = mysql_query(connection, query); if (result == 0){
data = mysql_store_result(connection);
int countColumns = mysql_num_fields(data); while (row = mysql_fetch_row(data)){
datos = row[count]; insertarLista(lista, datos); count++;

}

}
}




void borrarLinea(){

fstream archivo; string txt, men;

archivo.open("prueba.txt", ios::in); if (archivo.fail()){
cout << "Error" << endl; exit(1);

}

while (getline(archivo, txt)){ cout << "Linea borrada " << txt << endl; pushDeshacer(txt);

}

archivo.close(); archivo.open("prueba.txt", ios::out); archivo << "" << endl; archivo.close();
men = "borrar"; pushRehacer(men);

}




void rehacerAccion(){ string txt;
txt = popRehacer(); cout << txt << endl; if (txt == "borrar"){
borrarLinea();
}

}



void deshacerAccion(){

ofstream archivo; string txt;

archivo.open("prueba.txt", ios::out); txt = popDeshacer();
cout << "Restaurar : "<< txt << endl; archivo << txt << endl; archivo.close();
}

















int main() {

MYSQL* connection; connection = mysql_init(0);

if (connection){
cout << "La biblioteca Mysql se ha iniciado correctamente" << endl; connection = mysql_real_connect(connection, serverdb, userdb, passworddb,
database, 3306, NULL, 0);

if (connection){ cout << "Conexion exitosa a la base de datos\n" << endl; lecturaI(connection);
do {
					
					cout << "*************************" << endl;
					cout << "*      Bienvenidos      *" << endl;
					cout << "************************* \n" << endl;
					cout << "Elija una opcion \n" << endl;
					cout << "1. Agregar Alumno" << endl;
					cout << "2. Buscar Alumno" << endl;
					cout << "3. Borrar Alumno" << endl;
					cout << "4. Modificar datos de alumno" << endl;
					cout << "5. Listar Alumnos" << endl;
				cout << "6. Deshacer cambios" << endl;
				cout << "7. Rehacer cambios" << endl;
					cout << "0. Salir\n" << endl;
					cin >> sel;
					
					switch(sel){
						
						case 1:
							system("cls");
							agregarAlu(connection);
							system("pause");
							system("cls");
							break;
						
						case 2:
							system("cls");
							buscarAlu(connection);
							system("pause");
							system("cls");
							break;
							

						case 3:
							system("cls");
							BorrarAlumno(connection);
							system("pause");
							system("cls");
							break;
							




						case 4:
							system("cls");
							modificarAl(connection);
							system("pause");
							system("cls");
							break;
						
						case 5:
							system("cls");
							listarAl(connection);
							system("pause");
							system("cls");
							break;
							






							
						case 6:
							system("cls");
							pushRehacer(string str);
							system("pause");
							system("cls");
							break;
							
						case 7:
							system("cls");
							pushDesHacer(connection);
							system("pause");
							system("cls");
							break;
							













							
					}
					
				} while (sel !=0);


} else {

cout << "No fue posible conectar a la base de datos" << mysql_error(connection) << endl;
}

} else {

cout << "No fue posible iniciar la biblioteca Mysql" << endl;
}
return 0;
}
