#include <iostream>
#include <cstdio> //actualmente únicamente estoy logrando sacar cadenas con color utilizando códigos de escape ANSI y funcionan únicamente mediante "printf" que pertenece a este módulo
#include <string>
#include <stdlib.h> //esto es necesario para obtener números aleatorios y también para limpiar la pantalla
#include <ctime>

#ifdef _WIN32 || _WIN64
const char os_name = 'W';
#elif __linux__ || __unix
const char os_name = 'L';
#else
const char os_name = 'O'; //other
#endif


void limpiar_pantalla(){
	//esta función no parece estar funcionando del todo bien
	if (os_name == 'W'){
		system("CLS");
	}
	else {

		system("clear");
	}
	
}
void cambiar_asignacion(bool VF){
	if (os_name == 'L'){
		if(VF)
		{
			system("xmodmap -e \"keycode 36 = space\" && xmodmap -e \"keycode 65 = Return\"");
		} 
		else 
		{
			system("xmodmap -e \"keycode 65 = space\" && xmodmap -e \"keycode 36 = Return\"");
		}	
	}
	
}

void mostrar_lista(std::string conjunto[],char estado[],unsigned short &mostrar, const int valor = 0){
	for (short int i = mostrar-25; i <= mostrar ;i++){
		switch(estado[i]){
			case 'N':
				printf("%c[%dm%s ", 0x1B, 37,conjunto[i].c_str());
				break;
			case 'T':
				printf("%c[%dm%s ", 0x1B, 32,conjunto[i].c_str());
				break;
			default:
				printf("%c[%dm%s ", 0x1B, 31,conjunto[i].c_str());
				break;
		}
	}
	if (valor == mostrar-1) mostrar += 25;
}

int main(){
	const std::string array[200] = {"de", "Y", "el", "la", "en", "a", "que", "los", "se", "que", "un", "las", "con", "no", "por", "una", "para", "su", "es", "como", "me", "más", "le", "lo", "o", "pero", "sus", "si", "este", "sobre", "entre", "cuando", "también", "todo", "era", "fue", "esta", "ya", "son", "mi", "sin", "la", "años", "ser", "nos", "te", "qué", "dos", "está", "muy", "desde", "porque", "yo", "hasta", "había", "hay", "tiene", "ese", "todos", "hacer", "donde", "eso", "puede", "parte", "vida", "uno", "esa", "tiempo", "él", "ella", "sólo", "dijo", "cada", "vez", "ni", "otro", "después", "otros", "mismo", "hace", "ahora", "les", "estaba", "así", "bien", "e", "día", "año", "aunque", "durante", "país", "siempre", "otra", "tres", "algo", "ver", "mundo", "los", "tan", "antes", "sí", "cómo", "casa", "nada", "trabajo", "estos", "momento", "quien", "están", "gran", "esto", "forma", "mayor", "personas", "ellos", "nacional", "gobierno", "sino", "primera", "unos", "hacia", "tenía", "entonces", "hoy", "lugar", "ante", "luego", "estado", "otras", "días", "tener", "pues", "va", "contra", "nunca", "casi", "tienen", "según", "algunos", "una", "manera", "nuevo", "además", "hombre", "millones", "dar", "mucho", "veces", "menos", "todas", "primer", "presidente", "decir", "mujer", "tu", "solo", "mientras", "cosas", "mí", "debe", "tanto", "aquí", "estas", "ciudad", "fueron", "historia", "más", "sin embargo", "toda", "tras", "pueden", "dice", "tipo", "las", "grupo", "cual", "social", "gente", "sistema", "desarrollo", "mejor", "noche", "misma", "estar", "lado", "muchos", "sea", "cuenta", "mujeres", "agua", "importante", "aún", "dentro", "cuatro", "información", "mis", "madre", "salud", "nuestro", "será"};
	std::string array_desordenado[200];
	char estado[200]; //contiene el estado del array desordenado, esto determina en que color se va a mostrar
	std::string respuesta;
	int tiempo_inicial = time(NULL);
	int tiempo_limite = tiempo_inicial+60;
	unsigned short mostrar = 25; //esta variable es usada para decidir que palabras mostrar y cuales no

	cambiar_asignacion(true);

	for (int i = 0; i < 200;i++){
		estado[i] = 'N';
	}
	/* inicializar semilla para número aleatorio: */
	 srand (time(NULL));

	 for (int i = 0; i < 200 ;i++){
	 	/* generar número aleatorio entre 0 y 200: */
	 	int num_rand = rand() % 200;
		array_desordenado[i] = array[num_rand];
	}

	mostrar_lista(array_desordenado,estado,mostrar); 

	
	for (unsigned short i = 0; i < 200 and time(NULL) < tiempo_limite;i++){
		
		
		//std::cout << "\nActual: " << time(NULL) << "\n";
		//std::cout << "Limite: " << tiempo_limite << "\n";
		std::cout << "\nPalabra: ";
		std::cin >> respuesta;
		
		if (respuesta == array_desordenado[i]){ 
			estado[i] = 'T';
		} 
		else if (respuesta == "salir" or respuesta == "exit"){
			cambiar_asignacion(false);
			exit(0);
		}
		else {
			estado[i] = 'F';
		}
		limpiar_pantalla();
		mostrar_lista(array_desordenado,estado,mostrar,i);
		
	}

	unsigned short palabras_correctas = 0;
	unsigned short pulsaciones = 0;
	for (unsigned short i = 0; i<200;i++){
		if (estado[i] == 'T') {
			palabras_correctas += 1;
			pulsaciones += array_desordenado[i].length();

		}
	}
	cambiar_asignacion(false);
	std::cout << "\nPalabras por minuto: " << palabras_correctas << "\n";
	std::cout << "Pulsaciones por minuto: " << pulsaciones << "\n";
	
}
