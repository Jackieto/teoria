/** 
 * @brief Usuario que puede publicar una entrada en Facebook
 * @file Usuario.h
 * @author Victor M. Rivas Santos <vrivas@ujaen.es>
 * @date 27 de octubre de 2015, 18:17
 */
#ifndef USUARIO_H
#define	USUARIO_H

#include <string>

class Usuario {
public:
    Usuario(std::string nombre = "anonymous");
    Usuario(const Usuario& orig);
    virtual ~Usuario();
    void setNombre(std::string nombre);
    std::string getNombre() const;
private:
    std::string nombre;
};

#endif	/* USUARIO_H */

