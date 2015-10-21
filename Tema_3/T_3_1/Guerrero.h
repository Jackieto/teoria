/* 
 * File:   Guerrero.h
 * Author: algarcia
 *
 * Created on 20 de octubre de 2015, 13:58
 */

#ifndef GUERRERO_H
#define	GUERRERO_H

#include <string>

using namespace std;

class Guerrero
{
   private:
      string nombre;
      int energia;
      Arma *armamento;
      
   public:
      Guerrero ( );
      Guerrero ( string nNombre );
      Guerrero ( const Guerrero& orig );
      virtual ~Guerrero ( );
      void setArmamento ( Arma* nArmamento );
      Arma* getArmamento ( ) const;
      void setEnergia ( int nEnergia );
      int getEnergia ( ) const;
      void setNombre ( string nNombre );
      string getNombre ( ) const;
      int ataque ();
      string info ();
};

#endif	/* GUERRERO_H */

