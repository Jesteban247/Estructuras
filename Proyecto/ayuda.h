#include <iostream>
using namespace std;

void inicializar()
{
    cout << "(Juego en curso) El juego ya ha sido inicializado." <<endl;
    cout << "(Inicialización satisfactoria) El juego se ha inicializado correctamente." <<endl;
}

void turno()
{
    cout << "(Juego no inicializado) Esta partida no ha sido inicializada correctamente." <<endl;
    cout << "(Juego terminado) Esta partida ya tuvo un ganador." <<endl;
    cout << "(Jugador no válido) El jugador <id_jugador> no forma parte de esta partida." <<endl;
    cout << "(Jugador fuera de turno) No es el turno del jugador <id_jugador>." <<endl;
    cout << "(Turno terminado correctamente) El turno del jugador <id_jugador> ha terminado." <<endl;
}

void guardar()
{
    cout << "(Juego no inicializado) Esta partida no ha sido inicializada correctamente." <<endl;
    cout << "(Comando correcto) La partida ha sido guardada correctamente." <<endl;
    cout << "(Error al guardar) La partida no ha sido guardada correctamente." <<endl;
}

void guardar_comprimido()
{
    cout << "(Juego no inicializado) Esta partida no ha sido inicializada correctamente." <<endl;
    cout << "(Comando correcto) La partida ha sido codificada y guardada correctamente." <<endl;
    cout << "(Error al codificar y/o guardar) La partida no ha sido codificada ni guardada correctamente." <<endl;
}

void inicializar_nombre_archivo()
{
    cout << "(Juego en curso) El juego ya ha sido inicializado." <<endl;
    cout << "(Archivo vacío o incompleto) “nombre_archivo” no contiene información válida para inicializar el juego." <<endl;
}

void costo_conquista()
{
    cout << "(Juego no inicializado) Esta partida no ha sido inicializada correctamente." <<endl;
    cout << "(Juego terminado) Esta partida ya tuvo un ganador." <<endl;
    cout << "(Comando correcto) Para conquistar el territorio <territorio>, debe atacar desde <territorio_1>, pasando por los territorios <territorio_2>, <territorio_3>, ..., <territorio_m>. Debe conquistar <n> unidades de ejército." <<endl;
}

void conquista_mas_barata()
{
    cout << "(Juego no inicializado) Esta partida no ha sido inicializada correctamente." <<endl;
    cout << "(Juego terminado) Esta partida ya tuvo un ganador." <<endl;
    cout << "(Jugador no válido) La conquista más barata es avanzar sobre el territorio <territorio_1> desde el territorio <territorio_2>. Para conquistar el territorio <territorio_1>, debe atacar desde <territorio_2>, pasando por los territorios <territorio_3>, <territorio_4>, ..., <territorio_m>. Debe conquistar <n> unidades de ejército." <<endl;
}