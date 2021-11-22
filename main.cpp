#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <map>
/*clase libro*/
using namespace std;
FILE* registro;;
class Libro{
private:
	string TituloDelLibro;
	string Descripcion;
	string Autor;
	int NumeroDePaginas;
	float EstimadoHorasLeidas;
	map<int,string> PreguntaRespuestas;
	string GeneroDelLibro;
	string TipoDePlanta;
public:
	 Libro(){};
	 Libro(string titulo,string descripcion,string autor,int paginas,int horasLeidas){
	 TituloDelLibro = titulo;
	 Descripcion = descripcion;
	 Autor = autor;
	 NumeroDePaginas = paginas;
	 EstimadoHorasLeidas = horasLeidas;
	}
	
	char* getTitulo(){return &TituloDelLibro[0];}
	char* getDescripcion(){return &Descripcion[0];}
	char* getAutor(){return &Autor[0];}
	int getNumeroDePaginas(){return NumeroDePaginas;}
	float getEstimadoHorasLeidas(){return EstimadoHorasLeidas;}
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
		if(NumeroDePaginas != 0)
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
	private:
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
 void leerArchivoGuardado(string,string,string);

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

}


 int SeleccionarArchivoCargado(){
	
	
	try{
		registro;
  		string texto;
		string nombreArchivo;
		
		cout<<"Introduce el nombre exactamente como se registro la primera vez  el usuario: \n";
		cin.ignore();
		getline(cin,nombreArchivo);
		string ArchivoALeer = nombreArchivo.append(".invernaderoZEN");
		char* paresado = &ArchivoALeer[0];
		
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
		cin.ignore();
		getline(cin,Clave);
		leerArchivoGuardado(nombreArchivo,Clave,texto);

		
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
string leerHastaMarca(string Texto, char Limite1,char Limite2, bool encapsulamiento){
	int contador = -1;
	int posicionInicio;
	int posicionFin;
	for(int e = 0; e < sizeof(Texto)/ sizeof(char); e++){
		cout<<Texto[e];
		if(Texto[e] == Limite1){
			if(contador == -1){	contador = 0;
			posicionInicio = e;
			}
		
			if(encapsulamiento){
			
			 	contador++;
				}
			else{
			string resultado = Texto.substr(0,e);
			Texto = Texto.substr(e,(sizeof(Texto)/sizeof(char))-1 );
			return 	resultado;}
		}
		if(Texto[e] == Limite2){
		contador--;		
		}
		if(contador =0){
			posicionFin = e;
			string resultado = Texto.substr(posicionInicio,posicionFin);
				Texto = Texto.substr(posicionFin,(sizeof(Texto)/sizeof(char))-1 );
			return Texto.substr(posicionInicio,posicionFin);
		}
	}
}
void guardarLibro(Libro libroGuardar){

	fputs("\n",registro);
	fputs(libroGuardar.getTitulo(),registro);
	fputs("\n",registro);
	fputs(libroGuardar.getDescripcion(),registro);
	fputs("\n",registro);
	fputs(libroGuardar.getAutor(),registro);
}
void leerArchivoGuardado(string nombre,string claveIngresada,string Texto){
	string clave=leerHastaMarca(Texto,';',';',false);
	
	string tituloDelLibro = leerHastaMarca(Texto,';',';',false);
	
	cout<<clave< "fin";
	string Nombre;
	
	
}
