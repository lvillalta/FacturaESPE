//Nombre: Ricardo Benitez
//Declaramos todas las librerías necesarias
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <ctime>
//Estructura Cliente 
struct cliente{
	char nombre[20];
	char direccion[30];
	int telefono;
	int ruc;

};
//Estructura Producto
struct producto{	
	char nombre[30];
	int cantidad;
	float precioUnitario;
};
//Estructura fecha
struct fecha{
	int anio;
	int mes;
	int dia;
};
//Estructura factura 
struct factura{
	int numero;
	float subtotal;
	float iva;
	float total;
	fecha date;
	cliente client;
	producto productos;
};




//declaramos un tipo de dato enumerado con las diferentes opciones que tendrá en menú 
enum opciones{
	datos=1, //la opción 1 es para el ingreso de los datos
	recuperar=2,// la opción 2 es para ver la lista de las facturas creadas y mostrar en pantalla la que se elija 
	salir=3 // salir de la aplicación 
};

//declaramos los prototipos de las funciones
void ingresoDatos();// ingresa los valores necesarios para crear la factura 
void imprimirFactura(); // muestra en pantalla la factura seleccionada
void listadeFacturas(char a[5]); //agrega en la lista las facturas que se van creando
bool imprimirListaFactura();	// muestra en pantalla la lista de las facturas creadas 
int recuperarFactura(); //recupera la última factura para poder generar la siguiente
int validarNumero();// valida los que solo se ingresen valores numéricos 
float validarNumeroDecimal(); //validar numero con decimales
using namespace std;

//función principal
int main(){
	 	int opcion; //variable utilizada para la selección de una opción
	do{
		system("cls");//limpiamos la pantalla
		//imprimimos las diferentes opciones del menú	
		printf("\n\t\tMenu\n");
		printf("1.-Ingreso de datos\n"); //Ingresar los datos del cliente y llenar la factura
		printf("2.-Listar Facturas\n"); //Mostrar en pantalla todas las facturas
		printf("3.-Salir\n"); //salir
		printf("\nSeleccione una opcion: ");
		opcion=validarNumero();//leemos por teclado las opciones, pero primero llamamos al método Validar para comprobar que es un número
		
		switch(opcion){
			case datos:// caso para ingresar datos en la factura 
				system("cls");//limpiamos la pantalla
				ingresoDatos();// llamada al método para crear datos en la factura 
				system("pause");
				break;
			case recuperar://caso para mostrar en pantalla una factura ya creada
				system("cls");//limpiamos la pantalla
				imprimirFactura();// Llamada al método para mostrar una factura en pantalla
				system("pause");
				break;
			case salir:
				system("cls");//limpiamos la pantalla
				printf("Gracias por utilizar nuestro programa\n");//mostramos un mensaje de finalización del programa
				system("pause");
				break;
			default:
				system("cls");//limpiamos la pantalla
				printf("Opcion no valida\n"); //opción en caso de que el usuario ingrese un carácter invalido
				system("pause");
				break;
			}	
	}while(opcion!=3); //el bucle se ejecuta hasta el que usuario ingrese la opción 3 que es salir
		return 0;
}

// Método para ingresar los datos de la factura 
void ingresoDatos(){
	srand(time(NULL));//para generar un numero aleatorio
	int numeroVendedor;	 //variable utilizada para contener el número del vendedor
	numeroVendedor=1+rand()%(5-1);//creamos un numero aleatorio que será el vendedor que atienda al cliente
	int entero1;// indicara el número de factura
	entero1=recuperarFactura(); //obtenemos la factura
	entero1 = entero1 +1; //aumentamos el número de factura en uno
	
	//Para crear la factura con su respectivo nombre
	char str1[]="Factura"; 
 	char str2[5];
    char str3[]=".txt";
      
    itoa(entero1, str2, 10);//convierte el número a char
	//concatenar char para unir todo el nombre del archivo de la factura
    strcat(str1, str2);
    strcat(str1, str3);
    //fin concatenar char
    
	//Ingresar datos del cliente 
	factura facturas;
	//cliente client;
	printf("\t\tDatos del cliente\n");
	printf("\nIngrese el nombre del cliente: "); //ingresamos el nombre del cliente
	scanf("%s",&facturas.client.nombre); //leemos el nombre del cliente 
	printf("\nIngrese el ruc del cliente: ");//ingresamos el ruc del cliente
	facturas.client.ruc=validarNumero();//leemos el ruc del cliente 
	printf("\nIngrese la direccion del cliente: ");//ingresamos la dirección del cliente
	scanf("%s",&facturas.client.direccion);//leemos la dirección del cliente 
	printf("\nIngrese el telefono del cliente: ");//ingresamos el teléfono del cliente
	facturas.client.telefono=validarNumero();//leemos el teléfono del cliente 
	//fin ingresar datos del cliente 
	
	ofstream write_fich (str1);// crea la factura y abrir factura.txt

	listadeFacturas(str2);// crea la lista de facturas 
	time_t t = time(NULL); //para obtener la fecha
	tm* timePtr = localtime(&t); //obtenemos la fecha actual
    facturas.date.anio=timePtr->tm_year+1900; //variable que contiene el año actual
    facturas.date.mes=timePtr->tm_mon+1; //variable que contiene el mes actual
    facturas.date.dia=timePtr->tm_mday;//variable que contiene el día actual	
	char continuar='s'; //variable para generar un bucle que al pulsar la letra s finalice
		if ( ! write_fich)// verifica si ocurrió un error de la factura 
		printf("\nOcurrio un error al generar la factura"); 
		else{
			// Escribe los datos de la factura y de la persona en el txt creado 
			write_fich<<"\t\t\tFactura Numero "<<entero1;
			write_fich<<"\nFecha: "<<facturas.date.dia<<"/"<<facturas.date.mes<<"/"<<facturas.date.anio<<"\n\n";
			write_fich<<"Datos del cliente: ";
			write_fich<<"\nNombre del cliente: "<<facturas.client.nombre;
			write_fich<<"\nRuc: "<<facturas.client.ruc;
			write_fich<<"\nDireccion:"<<facturas.client.direccion;
			write_fich<<"\nTelefono:"<<facturas.client.telefono<<"\n\n";
			write_fich<<"\nDetalles de la compra:";
			write_fich<<"\nNombre Producto\t\tCantidad\tPrecio unitario\tPrecioTotal";			
			//bucle utilizado para escribir los datos de la compra
			do{
				system("cls");//limpiamos la pantalla
				printf("\t\tLista de Productos\n");
				// escribir en el txt los detalles de los productos a comprar 
				printf("\nIngrese el nombre del producto: ");
				scanf("%s",&facturas.productos.nombre);
				if(strlen(facturas.productos.nombre)>7){	
					write_fich <<"\n"<< facturas.productos.nombre<<"\t\t"; //comprueba si el nombre del producto es mayor a 6 para dar menos espacios
				}else{
					write_fich <<"\n"<< facturas.productos.nombre<<"\t\t\t";
				}
				printf("\nIngrese la cantidad del producto: ");
				facturas.productos.cantidad=validarNumero();
				write_fich << facturas.productos.cantidad<<"\t\t";
			
				printf("\nIngrese el precio del producto: ");
				facturas.productos.precioUnitario=validarNumeroDecimal();
				write_fich << facturas.productos.precioUnitario<<"\t\t";
		
				write_fich <<facturas.productos.cantidad*facturas.productos.precioUnitario<<"\t";
				facturas.subtotal+=(facturas.productos.cantidad*facturas.productos.precioUnitario);//calcuamos el subtotal de la compra y lo aumentamos mientras siga comprando más productos
				printf("\nDesea ingresar mas productos s/n: ");
				scanf("%s",&continuar);	
				//fin escribir en el txt los detalles de los productos a comprar 
					
			}while(continuar!='n');// verificar si se desea continuar ingresando datos

		}
	// calcular y escribir datos en el txt
	write_fich<<"\n\n Subtotal: $"<<facturas.subtotal;
	facturas.iva=facturas.subtotal*0.12; //calculamos el IVA
	write_fich<<"\n Iva: $"<<facturas.iva;
	facturas.total=facturas.subtotal+facturas.iva; //calculamos el total
	write_fich<<"\n Total: $"<<facturas.total;
	write_fich<<"\n\n\t------------- \t"<<" -------------";
	//seleccionamos un vendedor dependiendo del número aleatorio 
	if(numeroVendedor==1){
		write_fich<<"\n\t    Julian"<<"\t    "<<facturas.client.nombre; //vendedor 1 Julian
	}else if(numeroVendedor==2){
		write_fich<<"\n\t    Marixa"<<"\t    "<<facturas.client.nombre; //vendedor 2 Marix
	}else{
		write_fich<<"\n\t    Felipe"<<"\t    "<<facturas.client.nombre;//vendedor 3 Felipe
	}
	write_fich<<"\n\t   vendedor"<<"\t"<<"   cliente\n\n";
	// fin calcular y escribir datos en el txt
	write_fich.close();// cerrar el txt 
}
//método para imprimir factura
void imprimirFactura(){
	char factura[3]; //variable que contiene el número de la factura
	bool hayFacturas=imprimirListaFactura(); //variable que comprueba si hay facturas anteriores
	if(hayFacturas==true){ //si hay facturas permite seleccionar una factura para mostrar
		printf("\nIngrese el numero de la factura \n");
		scanf("%s",&factura);
		system("cls");//limpiamos la pantalla
		// Para unir todo 
		char str1[]="Factura";
	    char str3[]=".txt";
	    
		//concatenar char con el nombre de la factura a mostrar, se guarda en str1
	    strcat(str1,factura);
	    strcat(str1, str3);
	    // fin concatenar char
		
		
		ifstream leer_fich; // inicializar variable para leer archivo
		string contenido;
		leer_fich.open (str1,ios::in);// abrir archivo en lectura
		
		if(leer_fich.fail()){
			printf ("No se pudo encontrar la factura"); //en caso de no poder encontrar la factura
			exit(1);
			
		}else{
			while(!leer_fich.eof()){
				getline(leer_fich,contenido);
				printf("%s\n",contenido.c_str()); //se imprime el contenido de la factura
			
			}
		}
		leer_fich.close();
		}
}

//método para colocar la factura en una lista de facturas
void listadeFacturas(char a[5]){
	//Para listar la factura con su respectivo nombre
	char str1[]="Factura";
    char str3[]=".txt";
      
    //concatenar char 
    strcat(str1, a);
    strcat(str1, str3);

    // fin concatenar char
	ofstream lista;// inicializar archivo para escritura 
	lista.open("Lista.txt",ios::app);//abrir el archivo en modo que permita aumentar el nombre de la factura sin borrar lo anterior 
		if(lista.fail()){// verifica si ocurrió un error en el archivo 	
			printf ("No se pudo encontrar la factura"); //en caso de que no se encuentre la factura seleccionada
			exit(1);
		}else{
			lista<<"\n"<<a<<"   "<<str1;// escribir en el archivo
		}
	lista.close();// cerrar el archivo
	
}

//método para recuperar la última factura
int recuperarFactura(){
	char numero[25]; //obtenemos la lista completa
	char nombre[2]; //obtenemos solo el número de la factura
	int numeroFactura=0; //almacena el número de factura ya en formato entero
	ifstream leer_fich ("Lista.txt");
	if ( ! leer_fich){
	numeroFactura=1; //en caso de que no existan factura, retorna el uno como primera factura
	}
	else{
		while (! leer_fich.eof() ){
			leer_fich.getline(numero, 25);
		}
	}
	memcpy( nombre, &numero[0], 2 );//obtiene los dos primeros dígitos del arreglo de char, en esto dos dígitos están los números de la factura
	numeroFactura=atoi(numero); //convertimos el char a int, ya que es el número de la factura 
	leer_fich.close();
	return numeroFactura;
}

//método para imprimir lista de factura
bool imprimirListaFactura(){
	bool bandera=false; //para comprobar si hay una lista de factura
	ifstream leer_fich;
	string contenido; //contiene la información de la lista de la factura
	leer_fich.open ("Lista.txt",ios::in);// abrir archivo en lectura
	
	if(leer_fich.fail()){// verifica si ocurrió un error en el archivo 
		printf ("Todavia no hay facturas creadas\n");
		//exit(1);
	}else{
	
		while(!leer_fich.eof()){// verificar que no sea el final del archivo escrito 
			getline(leer_fich,contenido);
			printf("%s\n",contenido.c_str());
			//cout<<contenido<<endl;// imprimir en pantalla los datos del archivo 
		}
		leer_fich.close();// cerrar archivo 
		bandera=true;
	}
	return bandera;
}
//método utilizado para validar un número
int validarNumero(){
	char entrada[30];//variable utilizada para el ingreso de un dato
	bool bandera=false; //variable utilizada para controlar el bucle
	int contador=0; //variable que revisara si hay caracteres o solo números
	do{
   	contador=0;//iniciamos el contador en 0 en cada entrada de un nuevo numero
    scanf("%s", &entrada); //leemos el ingreso del dato
    for(int i=0;i<strlen(entrada);i++){ //recorremos la entrada ingresada
    	if(entrada[i]<48||entrada[i]>57){ //preguntamos si hay algún carácter en el dato ingresasdo
    		contador++;//si encuentra algún carácter aumenta el contador en uno
		}
	}
	 if(contador>0){//si el contador es mayor que uno significa que el dato ingresado no es un número
	 	 	printf("\nIngrese un numero valido: ");
	 } else{
	 	bandera=true;//caso contrario el dato es un numero
	 }
   }while (bandera==false);//finaliza cuando el dato ingresado es un número
   contador=atoi(entrada);//convierte el dato ingresado a un variable de tipo numérico
   return contador;
}


//validar numero flotantes
float validarNumeroDecimal(){
 	float numero; //variable que leerá el carácter ingresado por teclado
   float entrada_valida; //variable utilizada para ejecutar un bucle en caso de que el usuario no ingrese un número
   float ch;
   
   do {
      fflush(stdout);
      if ((entrada_valida = scanf("%f", &numero)) == EOF){ //comprobación para ver si el carácter que se ingresa es un número;
	  return EXIT_FAILURE;
	  }else{
	  		printf("\nIngrese una precio correcto: ");
	  }
      while ((ch = getchar()) != EOF && ch != '\n');
      
   }while (!entrada_valida);//finaliza cuando el carácter ingresado es un número
   return numero;
}


