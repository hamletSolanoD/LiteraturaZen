#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <map>

#define STRING(num) #num
/*clase libro*/
using namespace std;
string TextoModificar;
string usuario;
char* paresado;
class Libro{
private:
	string TituloDelLibro;
	string Descripcion;
	string Autor;
	string NumeroDePaginas;
	string EstimadoHorasLeidas;
	map<int,string> PreguntaRespuestas;
	string GeneroDelLibro;
	string TipoDePlanta;
public:
	 Libro(){};
	 Libro(string titulo,string descripcion,string autor,string paginas,string horasLeidas){
	 TituloDelLibro = titulo;
	 Descripcion = descripcion;
	 Autor = autor;
	 NumeroDePaginas = paginas;
	 EstimadoHorasLeidas = horasLeidas;
	}
	
	char* getTitulo(){return &TituloDelLibro[0];}
	char* getDescripcion(){return &Descripcion[0];}
	char* getAutor(){return &Autor[0];}
	char* getNumeroDePaginas(){return  &EstimadoHorasLeidas[0];}
	char* getEstimadoHorasLeidas(){return  &NumeroDePaginas[0];}
	char* getGeneroDelLibro(){return &GeneroDelLibro[0];}
	char* getTipoDePlanta(){return &TipoDePlanta[0];}
	void renderizarLibro(){
		cout<<"|--------------\n";
		if(TituloDelLibro != "")
		cout<<"|Titulo del Libro: "<<TituloDelLibro<<"\n";
		if(Descripcion != "")
		cout<<"|Descripcion del Libro: "<<Descripcion<<"\n";
		if(Autor != "")
		cout<<"|Autor del Libro: "<<Autor<<"\n";
		if(NumeroDePaginas != "")
		cout<<"|Numero De Paginas del Libro: "<<NumeroDePaginas<<"\n";
		if(GeneroDelLibro != "")
		cout<<"|Genero Del Libro del Libro: "<<GeneroDelLibro<<"\n";
		if(TipoDePlanta != "")
		cout<<"|Tipo De Planta: "<<TipoDePlanta<<"\n";
		cout<<"|--------------\n";
	}

};
///////////////////USUARIO 	/////////////////	
class Usuario{
	public:
		string nombre;
		string clave;
		map<int,Libro> bibliotecaPersonal;
	public: 
	usuario(string Nombre, string Clave){nombre = Nombre;clave =Clave;}
	void CargarLibro(Libro nuevoLibro){
		int libroACargar = bibliotecaPersonal.size();
		bibliotecaPersonal[libroACargar] = nuevoLibro;
	}
};
////////////////////////////////////
char respuesta;

 void InicioRegistro();
 int CrearNuevoArchivo();
 int SeleccionarArchivoCargado();
 void leerLibroTXT(string Texto);
 int leerArchivoGuardado(string,string,string,bool);
 void panelUsuario();
 void guardarLibro(Libro,string);

Usuario* UsuarioEnUso;
int main(int argc, char** argv) {
		
	
	InicioRegistro();
	return 0;
}
 void InicioRegistro(){
	bool repetir;
	do{	
	repetir = false;
	cout<<"Bienvenido a tu jardin de literatura ZEN\n";
	cout<<"Carga el archivo de registros con tu usuario y datos: \n";
	cout<<"a) Crear nuevo usuario\n";
	cout<<"b) Cargar archivo existente\n";
	cin>>respuesta;
	switch(respuesta){
		case 'A':
		case 'a':
		repetir = CrearNuevoArchivo() == 0? true:true;
		 break;
		case 'b':
		case 'B':
		repetir = SeleccionarArchivoCargado() == 0? true:false;
		 break;
		default: repetir = true; break;
	}
	}while(repetir);
	panelUsuario();
	

}
void panelUsuario(){
	bool repetir = true;
	do{
	system("pause");
	system("cls");
	cout<<"BIenvenido al usaurio "<<usuario<<":\n";
	cout<<"a)Guardar nuevo registro de libro "<<"\n";
	cout<<"b)Visitar libros previamente leidos "<<"\n";
	cout<<"c)Terminar el programa"<<"\n";
	char opciones;
	cin>>opciones;
	cin.ignore();
	switch(opciones){
		case 'a':{
		
			system("pause");
			system("cls");
			cout<<"Introducir los datos del libro: ";
			cout<<"\nNombre del libro: ";
			string nombre;
			getline(cin,nombre);
			cout<<"\nDescripcion: ";
			string Descripcion;
			getline(cin,Descripcion);
			
			cout<<"\nNombre del Autor: ";
			string Autor;
			getline(cin,Autor);
			
			cout<<"\nNumero de paginas: ";
			string paginas;
			getline(cin,paginas);
			
			cout<<"\nNumero de horas leidas: ";
			string leidas;
			getline(cin,leidas);
			
			
			Libro libro(nombre,Descripcion,Autor,paginas,leidas);
			guardarLibro(libro,usuario);
		 break;}
		case 'b': {
		FILE* registro2;
		registro2 = fopen(paresado,"r");
		string texto2 = "";
		if (registro2)
		{
			int c;
			while ((c = getc(registro2)) != EOF)
				texto2 += (char)(c);
			fclose(registro2);
		}
		
		leerArchivoGuardado("dfd","dfdf",texto2,true);
		fclose(registro2);
		break;}
		default:
		
		repetir = false; break;}

	}
	while(repetir);
}


 int SeleccionarArchivoCargado(){
	
	
	try{
		FILE* registro;
  		string texto;
		string nombreArchivo;
		
		cout<<"Introduce el nombre exactamente como se registro la primera vez  el usuario: \n";
		cin.ignore();
		getline(cin,nombreArchivo);
		string ArchivoALeer = nombreArchivo.append(".invernaderoZEN");
		usuario = ArchivoALeer;
		paresado = &ArchivoALeer[0];
		
		registro = fopen(paresado,"r+");
		if(registro == NULL) throw "No Encontrado el archivo";
		if (registro)
		{
			int c;
			while ((c = getc(registro)) != EOF)
				texto += (char)(c);
			fclose(registro);
		}
		cout<<"Introducir la clave del archivo/usuario\n";
		string Clave;
		getline(cin,Clave);
		int leerExitoso;
		leerExitoso = leerArchivoGuardado(nombreArchivo,Clave,texto,false);
		if(leerExitoso == 0) throw 1;

		
		return 1;
		
	}
	catch(...){
		system("cls");
		cout<<"Error al leer el archivo o es inexistente, volver a intentarlo\n";
		system("pause");
		system("cls");
		return 0;
	}
	

	
}
 int CrearNuevoArchivo(){
 	
 	
 	try{
	string nombreUsuario;
	string clave,clave2;
	system("cls");
	cout<<"Introducir el nombre del usuario que esta por registrar\n";
	cin.ignore();
    getline(cin,nombreUsuario);
	do{
	cout<<"Introduce la clave que usara\n";
	getline(cin,clave);
	cout<<"Introduce la clave que usara nuevamente\n";
	getline(cin,clave2);
	if(clave.compare(clave2) != 0){
		cout<<"Clave no coincidente, vuelva a intentarlo\n";
		system("pause");
		system("cls");
	}
	}while(clave.compare(clave2) != 0);
 	FILE*  myfile;
	nombreUsuario.append(".invernaderoZEN");
 	myfile = fopen(&nombreUsuario[0], "w+");
 	clave2.append(";");
 	fputs(&clave2[0],myfile);
  	fclose(myfile);
 	return 1;}
 	catch(...){
		system("cls");
 		cout<<"Error al cargar el archivo, vuelva a intentarlo\n";
 		return 0;
 		system("pause");
		system("cls");
	 }

}
string leerHastaMarca(char Limite1,char Limite2, bool encapsulamiento){
	int contador = -1;
	int posicionInicio;
	int posicionFin;
	//cout<<"Texto a modificar: "<<TextoModificar;
	
	for(int e = 0; e < TextoModificar.size(); e++){
			//cout<<TextoModificar[e];
			//system("pause");
		if(TextoModificar[e] == Limite1){
			//cout<<"entro limite 1";
			if(contador == -1){	contador = 0;
			posicionInicio = e;
			}
			if(encapsulamiento){
			 	contador++;
				}
			else{
			//cout<<"entro limite real";
			string resultado = TextoModificar.substr(0,e);
			TextoModificar = TextoModificar.substr(e, TextoModificar.size());
			return 	resultado;
			break;
			}
		}
		if(TextoModificar[e] == Limite2){
		contador--;		
		}
		if(contador ==0){
		//	cout<<"logrado";
			posicionFin = e;
			string resultado = TextoModificar.substr(posicionInicio+1,posicionFin-3);
			TextoModificar = TextoModificar.substr(posicionFin+1, TextoModificar.size()-1);
			return resultado;
			break;
		}
	}
}
void guardarLibro(Libro libroGuardar,string archivo){

	FILE* registro = fopen(&archivo[0],"a+");
	fputs("\n{",registro);
	fputs(libroGuardar.getTitulo(),registro);
	fputs(";\n",registro);
	fputs(libroGuardar.getDescripcion(),registro);
	fputs(";\n",registro);
	fputs(libroGuardar.getAutor(),registro);
	fputs(";\n",registro);
	fputs(libroGuardar.getEstimadoHorasLeidas(),registro);
	fputs(";\n",registro);
	fputs(libroGuardar.getNumeroDePaginas(),registro);
	fputs(";\n}",registro);
	fclose(registro);
}
int leerArchivoGuardado(string nombre,string claveIngresada,string Texto,bool leerBiblioteca){
	system("pause");
	system("cls");
	TextoModificar= Texto;
	string clave=leerHastaMarca(';',';',false);
	if(clave.compare(claveIngresada) == 0){
	 cout<<"\nArchivo exitosamente cargado\n";
		return 1;
	}
    else if(leerBiblioteca){
			cout<<"Archivos almacenados por este usuario: \n";
			string libro;
		while(libro == ""){
			 libro = leerHastaMarca('{','}',true);
			cout<<libro<<"\n";	
		}
			return 1;
	
	}
	else{
		cout<<"clave no coincidente, volver a intentarlo\n";
		system("pause");
		return 0;
	}

	
	
	
}
