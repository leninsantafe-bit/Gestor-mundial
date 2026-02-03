#include <cstdio>// este para los archivos
#include <cstdlib>// este para la aleatoridad
#include <cstring>// para cortar la linea y el enter
#include <ctime>// ayuda para la aleatoridad como pivote
#include <clocale>//para las tildes la ñ y asi 
using namespace std; 

// ARREGLOS 
// 32 selecciones, 5 campos(ID,Bombo,Nombre,Confederacion,ID_DT), 30 letras max
char selecciones[32][5][30]; 

// 1000 jugadores para que quepan todos auque solo carge como 120 jajaj, 5 campos(ID,Nombre,Posicion,Titular,ID_Seleccion), 30 letras max
char jugadores[1000][5][30]; 

// 50 directores tecnicos auqe se supone que son 32 xd, 4 campos(ID,Nombre,Nacionalidad,ID_Seleccion), 30 letras max
char dts[50][4][30];

// Indices para el torneo
int indicesTorneo[32]; 
bool gruposSorteados = false;
// para eleminora datos
char papelera[1000][5][30]; 
int totalPapelera = 0;

// Contadores globales
int totalSelecciones = 0;
int totalJugadores = 0;
int totalDTs = 0;

// UTIL para que el fgets no lea el enter que hay
void quitarSaltoLinea(char* cadena) {
    char* p = strchr(cadena, '\n');
    if (p) *p = '\0';
}

//CARGA DE DATOS (CSV)
void cargarDesdeExcel() {
    FILE* f;
    char linea[200];
    char* aux;

    // 1. CARGAR SELECCIONES
    f = fopen("selecciones.csv", "r");
    if (f) {
        fgets(linea, 200, f); // saltar la primera linea que era de el formato que puse xd
        while (fgets(linea, 200, f) && totalSelecciones < 32) {
            quitarSaltoLinea(linea);
            aux = strtok(linea, ","); if(aux) strcpy(selecciones[totalSelecciones][0], aux);
            aux = strtok(NULL, ",");  if(aux) strcpy(selecciones[totalSelecciones][1], aux);
            aux = strtok(NULL, ",");  if(aux) strcpy(selecciones[totalSelecciones][2], aux);
            aux = strtok(NULL, ",");  if(aux) strcpy(selecciones[totalSelecciones][3], aux);
            aux = strtok(NULL, ",");  if(aux) strcpy(selecciones[totalSelecciones][4], aux);
            totalSelecciones++;
        }
        fclose(f);
        printf("Selecciones cargadas: %d\n", totalSelecciones);
    } else {
        printf("Falta archivo selecciones.csv\n");
    }

    // 2. CARGAR DTs
    f = fopen("directores_tecnicos.csv", "r");
    if (f) {
        fgets(linea, 200, f);
        while (fgets(linea, 200, f) && totalDTs < 50) {
            quitarSaltoLinea(linea);
            aux = strtok(linea, ","); if(aux) strcpy(dts[totalDTs][0], aux);
            aux = strtok(NULL, ",");  if(aux) strcpy(dts[totalDTs][1], aux);
            aux = strtok(NULL, ",");  if(aux) strcpy(dts[totalDTs][2], aux);
            aux = strtok(NULL, ",");  if(aux) strcpy(dts[totalDTs][3], aux);
            totalDTs++;
        }
        fclose(f);
        printf("DTs cargados: %d\n", totalDTs);
    }

    // 3. CARGAR JUGADORES
    f = fopen("jugadores.csv", "r");
    if (f) {
        fgets(linea, 200, f);
        while (fgets(linea, 200, f) && totalJugadores < 1000) {
            quitarSaltoLinea(linea);// ya sabes par que no lea el enter
            aux = strtok(linea, ","); if(aux) strcpy(jugadores[totalJugadores][0], aux);//la funcion strtok toma la linea y la lee hasta encontrar la coma y la guarda en el token
            aux = strtok(NULL, ",");  if(aux) strcpy(jugadores[totalJugadores][1], aux);
            aux = strtok(NULL, ",");  if(aux) strcpy(jugadores[totalJugadores][2], aux);
            aux = strtok(NULL, ",");  if(aux) strcpy(jugadores[totalJugadores][3], aux);
            aux = strtok(NULL, ",");  if(aux) strcpy(jugadores[totalJugadores][4], aux);
            totalJugadores++;
        }
        fclose(f);
        printf("Jugadores cargados: %d\n", totalJugadores);
    }
}

void guardarCSV() {
    FILE* f = fopen("selecciones.csv", "w");
    if (f) {
        fprintf(f, "ID,Bombo,Nombre,Confederacion,ID Director tecnico\n");
        for (int i = 0; i < totalSelecciones; ++i)
            fprintf(f, "%s,%s,%s,%s,%s\n", selecciones[i][0], selecciones[i][1], selecciones[i][2], selecciones[i][3], selecciones[i][4]);
        fclose(f);
    }else{
    	printf("El archivo no fue abierto\n");
	}
    printf("Cambios guardados en selecciones.csv \n");
}

//  LOGICA BASICA 
int buscarSeleccion(char id_seleciones[]) {
    for (int i = 0; i < totalSelecciones; ++i){
        if (strcmp(selecciones[i][0], id_seleciones) == 0){		
		return i;// la funcion para comparar por id por el char ya sabes
		}
	}
    return -1;
}
int buscarJugador(char id_jugador[]) {
    for (int i = 0; i < totalJugadores; ++i){
        if (strcmp(jugadores[i][0], id_jugador) == 0){		
		return i;// la funcion para comparar por id por el char ya sabes
		}
	}
    return -1;
}
int buscarDirector(char id_director[]) {
    for (int i = 0; i < totalDTs; ++i){
        if (strcmp(dts[i][0], id_director) == 0){		
		return i;// la funcion para comparar por id por el char ya sabes
		}
	}
    return -1;
}
void listarSelecciones() {
    for (int i = 0; i < totalSelecciones; ++i) {
        printf("ID:%s  Nombre:%s  Conf:%s\n", selecciones[i][0], selecciones[i][2], selecciones[i][3]);
    }
}

void ingresarSeleccion() { 
    if (totalSelecciones >= 32)return;
    printf("ID: "); scanf("%29s", selecciones[totalSelecciones][0]);
    printf("Bombo: "); scanf("%29s", selecciones[totalSelecciones][1]);
    printf("Nombre: "); scanf("%29s", selecciones[totalSelecciones][2]);
    printf("Conf: "); scanf("%29s", selecciones[totalSelecciones][3]);
    strcpy(selecciones[totalSelecciones][4], "0");
    totalSelecciones++;
}
void ingresarDirectores() { //ID,Nombre,Nacionalidad,ID_Seleccion
    if (totalSelecciones >= 32)return;
    printf("ID: "); scanf("%29s", dts[totalDTs][0]);
    printf("Nombre: "); scanf("%29s", dts[totalDTs][1]);
    printf("Nacionalidad: "); scanf("%29s", dts[totalDTs][2]);
    printf("ID_Seleccion: "); scanf("%29s", dts[totalDTs][3]);
    totalDTs++;
}
void ingresarJugadores() {
    char salida = 'S';
    do {
        if (totalJugadores >= 1000) {
            printf("Error: Lista de jugadores llena.\n");
            return;
        }
        printf("\n Ingresando Jugadores %d \n", totalJugadores + 1);
        printf("ID: "); 
        scanf("%29s", jugadores[totalJugadores][0]);
        printf("Nombre: "); 
        scanf("%29s", jugadores[totalJugadores][1]);
        printf("Posicion: "); 
        scanf("%29s", jugadores[totalJugadores][2]);
        printf("Titular (1) o Suplente (0): "); 
        scanf("%29s", jugadores[totalJugadores][3]);
        printf("ID de seleccion: "); 
        scanf("%29s", jugadores[totalJugadores][4]);
        totalJugadores++;
        printf("Desea continuar (S/N)?: ");
        scanf(" %c", &salida); 
    } while (salida == 'S' || salida == 's'); 
}
void listarJugadores() {
    for (int i = 0; i < totalJugadores; ++i) {
        printf("%s - %s (%s)\n", jugadores[i][0], jugadores[i][1], jugadores[i][2]);
    }
}

void listarDTs() {
    for (int i = 0; i < totalDTs; ++i) {
        printf("%s - %s (Nac: %s)\n", dts[i][0], dts[i][1], dts[i][2]);
    }
}

// TORNEO Y GRUPOS 
void mezclarIndices(int numero_torneo[], int n) {
    srand(time(0));
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int aux = numero_torneo[i];
        numero_torneo[i] = numero_torneo[j];
        numero_torneo[j] = aux;
    }
}

void sortearGrupos() {
    if (totalSelecciones < 32) {
        printf("Necesitas 32 selecciones exactas.\n");
        return;
    }
    // Llenar indices 0 al 31 
    for(int i=0; i<32; i++) indicesTorneo[i] = i;
    
    // Revolver
    mezclarIndices(indicesTorneo, 32);
    gruposSorteados = true;

    char letra = 'A';
    for (int i = 0; i < 32; i += 4) {
        printf("\nGRUPO %c:\n", letra);
        for (int j = 0; j < 4; j++) {
            int idx = indicesTorneo[i + j];
            printf("  - %s\n", selecciones[idx][2]);
        }
        letra++;
    }
}

void jugarFaseDeGrupos() {
    if (!gruposSorteados) {
        printf("Primero sortea los grupos!\n");
        return;
    }
    char letra = 'A';
    for (int i = 0; i < 32; i += 4) {
        printf("\n--- GRUPO %c ---\n", letra);
        int puntos[4] = {0,0,0,0};
        int eq[4] = { indicesTorneo[i], indicesTorneo[i+1], indicesTorneo[i+2], indicesTorneo[i+3] };

        // Todos contra todos
        for (int x = 0; x < 4; x++) {
            for (int y = x + 1; y < 4; y++) {
                int g1 = rand() % 5;
                int g2 = rand() % 5;
                
                if (g1 > g2) puntos[x] += 3;
                else if (g2 > g1) puntos[y] += 3;
                else { puntos[x]++; puntos[y]++; }

                printf("%s %d - %d %s\n", selecciones[eq[x]][2], g1, g2, selecciones[eq[y]][2]);
            }
        }
        // Tabla simple
        printf("\nTabla %c (Puntos):\n", letra);
        for(int k=0; k<4; k++) printf("%s: %d pts\n", selecciones[eq[k]][2], puntos[k]);
        
        letra++;
    }
}
void listarSeleccioneBuscada(char i) {
        printf("ID:%s  Nombre:%s  Conf:%s\n", selecciones[i][0], selecciones[i][2], selecciones[i][3]);
}
void listarJugadorBuscado(char i) { //ID,Nombre,Posicion,Titular,ID_Seleccion
        printf("ID:%s  Nombre:%s  Posicion:%s\n", jugadores[i][0], jugadores[i][2], jugadores[i][3]);
}
void listarDirectorBuscado(char i) { //ID,Nombre,Nacionalidad,ID_Seleccion
        printf("ID:%s  Nombre:%s  Nacionalidad:%s\n", dts[i][0], dts[i][2], dts[i][3]);
}
void pivoteDeBusqueda(char destino[]) {
    printf("Ingrese Id : ");
    scanf("%s", destino);
}

void moverAPapeleraSelecciones(char id[]) { // id de seleciones solo para selecciones  
    int i = buscarSeleccion(id);
    if (i == -1) {
        printf("Error: ID no encontrado.\n");
        return;
    }
// estoy copiando el contenido de una papelera a la otra
    strcpy(papelera[totalPapelera][0], selecciones[i][0]);
    strcpy(papelera[totalPapelera][1], selecciones[i][1]);
    strcpy(papelera[totalPapelera][2], selecciones[i][2]);
    strcpy(papelera[totalPapelera][3], selecciones[i][3]);
    strcpy(papelera[totalPapelera][4], selecciones[i][4]);
    totalPapelera++; 
// poniendo en blanco el espacio del arreglo
    strcpy(selecciones[i][0], ""); 
    strcpy(selecciones[i][1], "");
    strcpy(selecciones[i][2], "");
    strcpy(selecciones[i][3], "");
    strcpy(selecciones[i][4], "");
    printf("Seleccion movida a la papelera.\n", i);
}
void moverAPapeleraJugadores(char id[]) { // id de jugadores solo para selecciones  
    int i = buscarJugador(id);
    if (i == -1) {
        printf("Error: ID no encontrado.\n");
        return;
    }
// estoy copiando el contenido de una papelera a la otra
    strcpy(papelera[totalPapelera][0], jugadores[i][0]);
    strcpy(papelera[totalPapelera][1], jugadores[i][1]);
    strcpy(papelera[totalPapelera][2], jugadores[i][2]);
    strcpy(papelera[totalPapelera][3], jugadores[i][3]);
    strcpy(papelera[totalPapelera][4], jugadores[i][4]);
    totalPapelera++; 
// poniendo en blanco el espacio del arreglo
    strcpy(jugadores[i][0], ""); 
    strcpy(jugadores[i][1], "");
    strcpy(jugadores[i][2], "");
    strcpy(jugadores[i][3], "");
    strcpy(jugadores[i][4], "");
    printf("Jugador movido a la papelera .\n", i);
}
void moverAPapeleraDirectores(char id[]) { // id de jugadores solo para selecciones  
    int i = buscarDirector(id);
    if (i == -1) {
        printf("Error: ID no encontrado.\n");
        return;
    }
// estoy copiando el contenido de una papelera a la otra
    strcpy(papelera[totalPapelera][0], dts[i][0]);
    strcpy(papelera[totalPapelera][1], dts[i][1]);
    strcpy(papelera[totalPapelera][2], dts[i][2]);
    strcpy(papelera[totalPapelera][3], dts[i][3]);
    totalPapelera++; 
// poniendo en blanco el espacio del arreglo
    strcpy(dts[i][0], ""); 
    strcpy(dts[i][1], "");
    strcpy(dts[i][2], "");
    strcpy(dts[i][3], "");
    printf("Director movido a la papelera .\n", i);
}
int main() {
	setlocale(LC_ALL, "spanish");
    cargarDesdeExcel();

    int op,op1,aux;
    char buscador[10];
    do {
        printf("\n=== MUNDIAL ===\n");
        printf("1. Gestionar Selecciones\n");
        printf("2. Gestionar Jugadores\n");
        printf("3. Gestionar Directores tecnicos\n");
        printf("4. SORTEAR GRUPOS\n");
        printf("5. JUGAR GRUPOS\n");

        printf("Opcion: ");
        scanf("%d", &op);

       switch (op) {
            case 1: 
            do{
                printf("\n Gestionar Selecciones \n");
                printf("1. listar Selecciones\n");
                printf("2. buscar por id de Selecciones\n");
                printf("3. eliminar por id de seleccion\n");
                printf("4. Ingresar Seleccion Manual\n");
                printf("5. Guardar y Salir\n\n");
                printf("opcion \n");
                scanf("%d", &op1);
                switch(op1){
                	case 1:
                     	listarSelecciones(); 	
                	    break;
					case 2:
				    	pivoteDeBusqueda(buscador);
                     	aux=buscarSeleccion(buscador); 
                	if(aux != -1) {
                                listarSeleccioneBuscada(aux);
                            } else {
                                printf("Seleccion no encontrada.\n");
                            }
                	break;
					case 3:
				    	pivoteDeBusqueda(buscador);
                        moverAPapeleraSelecciones(buscador);
					break;	
					case 4:
                    	ingresarSeleccion(); 	
                	break;	
                	case 5: 
                        guardarCSV(); 
                    break;
                    default:
                        printf("Opcion no valida, intente de nuevo.\n");
                    break;
				}
            }while(op1!=5);
            break;
            case 2: 
            do{
                printf("\n Gestionar Jugadores \n");
                printf("1. Listar Jugadores\n");
                printf("2. Buscar por id de Jugadores\n");
                printf("3. Eliminar por id de Jugadores\n");
                printf("4. Ingresar Jugadores Manual\n");
                printf("5. Guardar y Salir\n\n");
                printf("opcion \n");
                scanf("%d", &op1);
                switch(op1){
                	case 1:
                     	listarJugadores(); 	
                	    break;
					case 2:
				    	pivoteDeBusqueda(buscador);
                     	aux=buscarJugador(buscador); 
                	if(aux != -1) {
                                listarJugadorBuscado(aux);
                            } else {
                                printf("Jugador no encontrado.\n");
                            }
                	break;
					case 3:
				    	pivoteDeBusqueda(buscador);
                        moverAPapeleraJugadores(buscador);
					break;	
					case 4:
                    	ingresarJugadores(); 	
                	break;	
                	case 5: 
                        guardarCSV(); 
                    break;
                    default:
                        printf("Opcion no valida, intente de nuevo.\n");
                    break;
				}
            }while(op1!=5);
                break;
            case 3: 
            do{
                printf("\n Gestionar Directores tecnicos \n");
                printf("1. Listar Directores tecnicos\n");
                printf("2. Buscar por id de Directores tecnicos\n");
                printf("3. Eliminar por id de Directores tecnicos\n");
                printf("4. Ingresar Directores tecnicos Manual\n");
                printf("5. Guardar y Salir\n\n");
                printf("opcion \n");
                scanf("%d", &op1);
                switch(op1){
                	case 1:
                     	listarDTs(); 	
                	    break;
					case 2:
				    	pivoteDeBusqueda(buscador);
                     	aux=buscarDirector(buscador) ; 
                	if(aux != -1) {
                                listarDirectorBuscado(aux);
                            } else {
                                printf("Jugador no encontrado.\n");
                            }
                	break;
					case 3:
				    	pivoteDeBusqueda(buscador);
                        moverAPapeleraDirectores(buscador);
					break;	
					case 4:
                    	ingresarDirectores();
                	break;	
                	case 5: 
                        guardarCSV(); 
                    break;
                    default:
                        printf("Opcion no valida, intente de nuevo.\n");
                    break;
				}
            }while(op1!=5);
                break;
            case 4: 
                sortearGrupos(); 
                break;
            case 5: 
                jugarFaseDeGrupos(); 
                break;
            default:
                printf("Opcion no valida, intente de nuevo.\n");
                break;
        }

    } while (op != 6);


    return 0;
}

