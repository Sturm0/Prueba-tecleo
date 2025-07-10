#include <string>
#include <stdlib.h> //esto es necesario para obtener números aleatorios y también para limpiar la pantalla
#include <ctime>
#include <ncurses.h>
#include <iostream>


void mostrar_lista(const std::wstring conjunto[],std::string estado[],unsigned short &mostrar, const int valor = 0){
	for (short int i = mostrar-25; i <= mostrar ;i++){
		for (int j = 0; j < conjunto[i].size(); j++)
		{
			switch(estado[i][j]){
				case 'N':
					printw("%lc",conjunto[i][j]);
					refresh();
					break;
				case 'T':
					attron(COLOR_PAIR(1));
					printw("%lc",conjunto[i][j]);
					attroff(COLOR_PAIR(1));
					refresh();
					break;
				default:
					attron(COLOR_PAIR(2));
					printw("%lc",conjunto[i][j]);
					attroff(COLOR_PAIR(2));
					refresh();
					break;
			}
		}
		printw(" ");
	}
	printw("\n");
	refresh();
	if (valor == mostrar-1) mostrar += 25;
}

int main(){	
	setlocale(LC_ALL, "");
	initscr();
	noecho(); //evita el eco de funciones como getch()
	start_color();
	init_pair(1,COLOR_GREEN,COLOR_BLACK);
	init_pair(2,COLOR_RED,COLOR_BLACK);
	std::wstring array[200] = {L"de", L"Y", L"el", L"la", L"en", L"a", L"que", L"los", L"se", L"que", L"un", L"las", L"con", L"no", L"por", L"una", L"para", L"su", L"es", L"como", L"me", L"más", L"le", L"lo", L"o", L"pero", L"sus", L"si", L"este", L"sobre", L"entre", L"cuando", L"también", L"todo", L"era", L"fue", L"esta", L"ya", L"son", L"mi", L"sin", L"la", L"años", L"ser", L"nos", L"te", L"qué", L"dos", L"está", L"muy", L"desde", L"porque", L"yo", L"hasta", L"había", L"hay", L"tiene", L"ese", L"todos", L"hacer", L"donde", L"eso", L"puede", L"parte", L"vida", L"uno", L"esa", L"tiempo", L"él", L"ella", L"sólo", L"dijo", L"cada", L"vez", L"ni", L"otro", L"después", L"otros", L"mismo", L"hace", L"ahora", L"les", L"estaba", L"así", L"bien", L"e", L"día", L"año", L"aunque", L"durante", L"país", L"siempre", L"otra", L"tres", L"algo", L"ver", L"mundo", L"los", L"tan", L"antes", L"sí", L"cómo", L"casa", L"nada", L"trabajo", L"estos", L"momento", L"quien", L"están", L"gran", L"esto", L"forma", L"mayor", L"personas", L"ellos", L"nacional", L"gobierno", L"sino", L"primera", L"unos", L"hacia", L"tenía", L"entonces", L"hoy", L"lugar", L"ante", L"luego", L"estado", L"otras", L"días", L"tener", L"pues", L"va", L"contra", L"nunca", L"casi", L"tienen", L"según", L"algunos", L"una", L"manera", L"nuevo", L"además", L"hombre", L"millones", L"dar", L"mucho", L"veces", L"menos", L"todas", L"primer", L"presidente", L"decir", L"mujer", L"tu", L"solo", L"mientras", L"cosas", L"mí", L"debe", L"tanto", L"aquí", L"estas", L"ciudad", L"fueron", L"historia", L"más", L"sinembargo", L"toda", L"tras", L"pueden", L"dice", L"tipo", L"las", L"grupo", L"cual", L"social", L"gente", L"sistema", L"desarrollo", L"mejor", L"noche", L"misma", L"estar", L"lado", L"muchos", L"sea", L"cuenta", L"mujeres", L"agua", L"importante", L"aún", L"dentro", L"cuatro", L"información", L"mis", L"madre", L"salud", L"nuestro", L"será"};
	std::string estado[200]; //contiene el estado del array desordenado, esto determina en que color se va a mostrar

	wint_t respuesta;
	int tiempo_inicial = time(NULL);
	int tiempo_limite = tiempo_inicial+60;
	unsigned short mostrar = 25; //esta variable es usada para decidir que palabras mostrar y cuales no
	
	/* inicializar semilla para número aleatorio: */
	srand (time(NULL));

	for (uint8_t i = 0; i < 200 ;i++){
	 	//esta sección es para aleatorizar el array
	 	/* generar número aleatorio entre 0 y 200: */
	 	uint8_t num_rand1 = rand() % 200;
	 	uint8_t num_rand2 = rand() % 200;
		std::swap(array[num_rand1],array[num_rand2]);
	}
	
	for (uint8_t i = 0; i < 200;i++){ //estoy usando uint8_t porque total i nunca va a tomar un valor mayor a 255
		for (int j = 0; j < array[i].size(); j++)
		{
			estado[i].push_back('N');
		}
	}
	mostrar_lista(array,estado,mostrar); 

	printw("Ingresar texto: ");
	refresh();
	int pos_cursor_x; //guarda la posición del cursor que va a estar en algún lugar después de "Ingresar texto: "
	int pos_cursor_y;
	cbreak();
	short int palabras_correctas = 0;
	int pulsaciones_correctas = 0; //cantidad total de pulsaciones correctas
	for (uint8_t i = 0; i < 200 and time(NULL) < tiempo_limite;i++){
		int cant_car_correct = 0; //cantidad de pulsaciones correctas en la actual palabra
		for (int j = 0; j < array[i].size()+1; j++)
		{
			get_wch(&respuesta);
			
			if (respuesta == KEY_BACKSPACE or respuesta == 127 or respuesta == '\b') {
				if (j==0) {
					j--;
					continue;
				}
				getyx(stdscr,pos_cursor_y,pos_cursor_x);
				mvdelch(pos_cursor_y,pos_cursor_x-1);
				j--;
				estado[i][j] = 'N';
				j--;
				
			} else if (j < array[i].size()+1 && respuesta == array[i][j]) {
				printw("%lc",respuesta);
				estado[i][j] = 'T';
				cant_car_correct++;
				pulsaciones_correctas++;
			} else if (j < array[i].size()+1) {
				printw("%lc",respuesta);
				estado[i][j] = 'F';
			}
			getyx(stdscr,pos_cursor_y,pos_cursor_x);
			move(0,0);
			mostrar_lista(array,estado,mostrar,i);
			move(pos_cursor_y,pos_cursor_x);
			refresh();
		}
		move(pos_cursor_y,0);
		clrtoeol();
		printw("Ingresar texto: ");
		refresh();
		if (cant_car_correct == array[i].size()) palabras_correctas++;
	}
	endwin();
	int tiempo_transcurrido = time(NULL)-tiempo_inicial;
	int palabras_por_minuto = (60*palabras_correctas)/tiempo_transcurrido;
	int pulsaciones_por_minuto = (60*pulsaciones_correctas)/tiempo_transcurrido;
	std::cout << "\nPalabras por minuto: " << palabras_por_minuto << std::endl;
	std::cout << "\nPulsaciones por minuto: " << pulsaciones_correctas << std::endl;
}
