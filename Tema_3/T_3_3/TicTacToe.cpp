/**
 * @file TicTacToe.cpp
 * Archivo con la implementación de la clase TicTacToe, para gestionar una
 * partida de tres en raya clásico
 * @author algarcia
 * @date 2015-12-17
 */

#include <stdexcept>
#include <sstream>

#include "TicTacToe.h"

/**
 * Inicializa los nombres de los jugadores a "p1" y "p2", y crea un nuevo
 * tablero
 * @brief Constructor por defecto
 */
TicTacToe::TicTacToe ( ): _jugadores{"p1","p2"}, _t(new Tablero()), _turno(0)
{
   // NOTA: si la inicialización del array _jugadores da errores al compilar,
   // ha de incluirse aquí. Es una característica reciente de C++ que algunos
   // compiladores no soportan todavía
   
   /*
    * _jugadores[0] = "p1";
    * _jugadores[1] = "p2";
    */
}

/**
 * Copia los nombres de los jugadores y a quién le corresponde el siguiente
 * turno, pero no copia el puntero al tablero, sino que crea un tablero nuevo
 * @brief Constructor de copia
 * @param orig
 */
TicTacToe::TicTacToe ( const TicTacToe& orig ): _jugadores{orig._jugadores[0],
                                                           orig._jugadores[1]},
                                                _t( new Tablero(*orig._t) ),
                                                _turno(orig._turno)
{
   // NOTA: si la inicialización del array _jugadores da errores al compilar,
   // ha de incluirse aquí. Es una característica reciente de C++ que algunos
   // compiladores no soportan todavía

   /*
    * _jugadores[0] = orig.jugadores[0];
    * _jugadores[1] = orig.jugadores[1];
    */
}

/**
 * Asigna a los jugadores los nombres que se le pasan como parámetros. Crea
 * también el tablero
 * @brief Constructor parametrizado
 * @param jugador1 Nombre del primer jugador
 * @param jugador2 Nombre del segundo jugador
 */
TicTacToe::TicTacToe ( const string& jugador1,
                       const string& jugador2 ): _jugadores{jugador1, jugador2},
                                                 _t( new Tablero()), _turno(0)
{
   // NOTA: si la inicialización del array _jugadores da errores al compilar,
   // ha de incluirse aquí. Es una característica reciente de C++ que algunos
   // compiladores no soportan todavía

   /*
    * _jugadores[0] = jugador1;
    * _jugadores[1] = jugador2;
    */
}

/**
 * Destruye el tablero, que había sido creado en memoria dinámica por el
 * constructor
 * @brief Destructor
 */
TicTacToe::~TicTacToe ( )
{
   delete _t;
   _t = 0;
}

/**
 * @brief Método para cambiar el nombre del primer jugador
 * @param j1 Nombre del nuevo jugador
 */
void TicTacToe::setJugador1 ( const string& j1 )
{
   _jugadores[0] = j1;
}

/**
 * @brief Método para cambiar el nombre del segundo jugador
 * @param j2 Nombre del nuevo jugador
 */
void TicTacToe::setJugador2 ( const string& j2 )
{
   _jugadores[1] = j2;
}

/**
 * @brief Método para consultar el nombre del primer jugador
 * @return El nombre del primer jugador
 */
const string TicTacToe::getJugador1 ()
{
   return ( _jugadores[0] );
}

/**
 * @brief Método para consultar el nombre del segundo jugador
 * @return El nombre del segundo jugador
 */
const string TicTacToe::getJugador2 ()
{
   return ( _jugadores[1] );
}

/**
 * @brief Método para consultar el nombre del jugador al que le toca mover en
 *        la partida
 * @return El nombre del jugador en cuestión
 */
const string TicTacToe::getSiguiente ()
{
   return ( _jugadores[_turno] );
}

/**
 * @brief Método para consultar el nombre del jugador que acaba de realizar el
 *        último movimiento
 * @return El nombre del jugador en cuestión
 */
const string TicTacToe::getAnterior ()
{
   if ( _turno == 0 )
   {
      return ( _jugadores[1] );
   }

   return ( _jugadores[0] );
}

/**
 * @brief Método para consultar visualmente el estado del tablero
 * @return Una representación en modo texto del estado del tablero, en la que
 *         las posiciones libres están señaladas con '-', las ocupadas por el
 *         jugador 1 con 'X', y las ocupadas por el jugador 2 con 'O'
 */
const string TicTacToe::getInfoTablero ()
{
   return ( _t->info () );
}

/**
 * Según a qué jugador le toque hacer el movimiento, aplica la jugada
 * correspondiente, colocando una 'X' o una 'O' en el tablero
 * @brief Método para llevar a cabo una jugada
 * @param f Fila del tablero donde el jugador correspondiente quiere hacer el
 *        movimiento
 * @param c Columna del tablero donde el jugador correspondiente quiere hacer el
 *        movimiento
 * @retval true Si la jugada es ganadora; por tanto, acaba la partida
 * @retval false Si la jugada no es ganadora
 * @throws std::out_of_range Si la posición indicada por f y c no es correcta
 *         (se sale del tablero)
 * @throws std::invalid_argument Si se intenta realizar el movimiento en una
 *         posición del tablero que no está libre
 */
bool TicTacToe::movimiento ( int f, int c )
{
   char marca;
   bool resultado;
   int turnoAnterior;
   std::stringstream mensaje;

   // Dependiendo de a quién le toca mover, cambia la marca y el siguiente turno
   turnoAnterior = _turno;
   if ( _turno == 0 )
   {
      marca = 'X';
      _turno = 1;
   }
   else
   {
      marca = 'O';
      _turno = 0;
   }

   try
   {
      resultado = _t->setPos ( f, c, marca );
   }
   catch ( std::out_of_range oor )
   {
      // El turno no puede avanzar, porque la jugada ha sido incorrecta
      _turno = turnoAnterior;

      // Ya que la marca va a ser 'X' o 'O', la excepción out_of_range sólo
      // puede deberse a un valor no válido de fila y/o columna
      mensaje << "TicTacToe::movimiento: posición incorrecta en el tablero"
              << oor.what ();
      throw std::out_of_range ( mensaje.str () );
   }
   catch ( std::invalid_argument ia )
   {
      // El turno no puede avanzar, porque la jugada ha sido incorrecta
      _turno = turnoAnterior;

      throw std::invalid_argument ( "TicTacToe::movimiento: la posición ya está"
                                    " ocupada" );
   }

   return ( resultado );
}