#include "Ayuda.h"

void inicializar()
{   
    cout << "Descripción general del comando: " <<endl;
    cout << "Inicializa la partida, se encarga de iniciar el juego al pedir la cantidad de jugadores y sus nombres." <<endl;
    cout<<endl;
    cout << "Posibles mensajes:" <<endl;
    cout << "(Juego en curso) El juego ya ha sido inicializado." <<endl;
    cout << "(Inicialización satisfactoria) El juego se ha inicializado correctamente." <<endl;
    cout << endl;
    cout << "Como ejecutar el comando:" <<endl;
    cout << "Escribir en consola: $ inicializar" <<endl;
    cout << endl;
}

void turno()
{
    cout << "Descripción general del comando: " <<endl;
    cout << "El código gestiona las acciones de un jugador en su turno:"<<endl;
    cout << "Indica cuántas unidades adicionales puede obtener."<<endl;
    cout << "Permite asignar unidades a sus territorios."<<endl;
    cout << "Facilita configurar ataques entre territorios, mostrando resultados de dados y cambios de unidades."<<endl;
    cout << "Pide al jugador fortificar territorios vecinos, especificando la cantidad de unidades a trasladar." <<endl;
    cout << endl;
    cout << "Posibles mensajes:" <<endl;
    cout << "(Juego no inicializado) Esta partida no ha sido inicializada correctamente." <<endl;
    cout << "(Juego terminado) Esta partida ya tuvo un ganador." <<endl;
    cout << "(Jugador no válido) El jugador <id_jugador> no forma parte de esta partida." <<endl;
    cout << "(Jugador fuera de turno) No es el turno del jugador <id_jugador>." <<endl;
    cout << "(Turno terminado correctamente) El turno del jugador <id_jugador> ha terminado." <<endl;
    cout << endl;
    cout << "Como ejecutar el comando:" <<endl;
    cout << "Escribir en consola: $ turno <id_jugador> " <<endl;
    cout << endl;
}

void guardar()
{
    cout << "Descripción general del comando: " <<endl;
    cout << "Se va a guardar en un archivo plano, sin deocodificacion la informacion actual del juego." <<endl;
    cout<<endl;
    cout << "Posibles mensajes:" <<endl;
    cout << "(Juego no inicializado) Esta partida no ha sido inicializada correctamente." <<endl;
    cout << "(Comando correcto) La partida ha sido guardada correctamente." <<endl;
    cout << "(Error al guardar) La partida no ha sido guardada correctamente." <<endl;
    cout << endl;
    cout << "Como ejecutar el comando:" <<endl;
    cout << "Escribir en consola: $ guardar <nombre_archivo> " <<endl;
    cout << endl;
}

void guardar_comprimido()
{   
    cout << "Descripción general del comando: " <<endl;
    cout << "Se va a guardar en un archivo binario, utilizando la codificación de Huffman y va a estar la informacion actual del juego." <<endl;
    cout<<endl;
    cout << "(Juego no inicializado) Esta partida no ha sido inicializada correctamente." <<endl;
    cout << "(Comando correcto) La partida ha sido codificada y guardada correctamente." <<endl;
    cout << "(Error al codificar y/o guardar) La partida no ha sido codificada ni guardada correctamente." <<endl;
    cout << endl;
    cout << "Como ejecutar el comando:" <<endl;
    cout << "Escribir en consola: $ guardar_comprimido <nombre_archivo> " <<endl;
    cout << endl;
}

void inicializar_nombre_archivo()
{
    cout << "Descripción general del comando: " <<endl;
    cout << "Inicializa la partida con la información que se encuentra en un archivo." <<endl;
    cout<<endl;
    cout << "(Juego en curso) El juego ya ha sido inicializado." <<endl;
    cout << "(Archivo vacío o incompleto) “nombre_archivo” no contiene información válida para inicializar el juego." <<endl;
    cout << endl;
    cout << "Como ejecutar el comando:" <<endl;
    cout << "Escribir en consola: $ inicializar <nombre_archivo> " <<endl;
    cout << endl;
}

void costo_conquista()
{   
    cout << "Descripción general del comando: " <<endl;
    cout << "El programa calcula cómo conquistar el territorio deseado por el jugador. Inicia el ataque desde su territorio más cercano al objetivo. Esto se hace desde la perspectiva del jugador actual." <<endl;
    cout<<endl;
    cout << "(Juego no inicializado) Esta partida no ha sido inicializada correctamente." <<endl;
    cout << "(Juego terminado) Esta partida ya tuvo un ganador." <<endl;
    cout << "(Comando correcto) Para conquistar el territorio <territorio>, debe atacar desde <territorio_1>, pasando por los territorios <territorio_2>, <territorio_3>, ..., <territorio_m>. Debe conquistar <n> unidades de ejército." <<endl;
    cout << endl;
    cout << "Como ejecutar el comando:" <<endl;
    cout << "Escribir en consola: $ costo_conquista <territorio> " <<endl;
    cout << endl;
}

void conquista_mas_barata()
{
    cout << "Descripción general del comando: " <<endl;
    cout << "El programa calcula  el territorio que pueda implicar un menor número de unidades de ejército perdidas. Esto se hace desde la perspectiva del jugador actual." <<endl;
    cout<<endl;
    cout << "(Juego no inicializado) Esta partida no ha sido inicializada correctamente." <<endl;
    cout << "(Juego terminado) Esta partida ya tuvo un ganador." <<endl;
    cout << "(Jugador no válido) La conquista más barata es avanzar sobre el territorio <territorio_1> desde el territorio <territorio_2>. Para conquistar el territorio <territorio_1>, debe atacar desde <territorio_2>, pasando por los territorios <territorio_3>, <territorio_4>, ..., <territorio_m>. Debe conquistar <n> unidades de ejército." <<endl;
    cout << endl;
    cout << "Como ejecutar el comando:" <<endl;
    cout << "Escribir en consola: $ conquista_mas_barata " <<endl;
    cout << endl;
}
