#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */
	// Usando el logger creado previamente
	logger = iniciar_logger(); 

	//printf("hola");
	//Que logee: Crea un archivo, registra en el archivo.log. Cada cosa que se manda. 
	log_info(logger, "Hola!");
	
	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */
	//Para que el valor que no logueamos no este hardcodeaod en el código, 
	//y podamos configurarlo para que varía sin tener que recompilar todo el proyecto. 
	//Vamos a leerlo de un archivo de configuración y loguamos usando el logger previo. 
	
	config = iniciar_config();
	
	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'
	ip = config_get_String_value(config, "IP");
	puerto = config_get_String_value(config, "PUERTO");
	valor = config_get_String_value(config, "CLAVE");

	// Loggeamos el valor de config
	log_info(logger, "VALOR leido de la config: %s", valor); 
	
	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor, conexion);

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*-----------FIN-----------*/
	printf("\nCLIENTE CERRADO"); 

}


/*t_log * log_create	(	char * 	file,
char * 	process_name,
bool 	is_active_console,
t_log_level 	level 
)		
Crea una instancia de logger.

Parámetros
file	La ruta hacia el archivo donde se van a generar los logs, debe tener extensión .log
process_name	El nombre a ser mostrado en los logs
is_active_console	Si lo que se loguea debe mostrarse por consola
level	El nivel de detalle máximo a loguear (ver definición de t_log_level)
Devuelve
Retorna una instancia de logger, o NULL en caso de error. Debe ser liberada con log_destroy()
Nota
Se debe tener en cuenta que:
si file ya existe, se escribirá al final del archivo
si file no existe, se creará un nuevo archivo en el directorio indicado
si el directorio hacia file no existe, se producirá un error
si file es NULL, no se escribirá en ningún archivo*/

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger = log_create("cliente.log", "CLIENTE_LOGGER", 1, LOG_LEVEL_INFO);
	//1. Creación del log, que devuelve. 
	if(nuevo_logger == NULL){
		perror("No se pudo crear el archivo.");
		exit(EXIT_FAILURE);
	}


	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config = config_create("cliente.config");
	if(nuevo_config == NULL)
	{perror("Error al cargar el config");
	exit(EXIT_FAILURE); }

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	log_info(logger, ">> %s", leido);
	leido = readline("> ");

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
	while(strcmp(leido, " ") != 0 ){
		free(leido)
		leido = readline("> ");
		log_info(logger, ">> %s", leido);
	}
	// ¡No te olvides de liberar las lineas antes de regresar!
	free(leido);
}

void paquete(int conexion)
{
	char* leido == NULL;
	t_paquete* paquete = crear_paquete();

	// Leemos y esta vez agregamos las lineas al paquete
	leido = readline("> ");
	while(strcmp(leido, " ") != 0 ){
		agregar_a_paquete(paquete, ledo, strlen(leido) + 1);
		free(leido);
		leido = readline("> ");
		
	}
	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	free(leido);
	//Enviar Paquete
	enviar_paquete(paquete, conexion);

	//Eliminar paquete
	eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
}
