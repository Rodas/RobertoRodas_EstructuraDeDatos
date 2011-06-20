#ifndef CALCU_H
#define CALCU_H

#include <QList>
#include <QString>
#include <qdebug.h>
#include <math.h>

class calcu
{
public:
    calcu();
     void cambiar_Postfijo();
    // bool revisarData(QString data);
     QList<QString> tokens;
     QList <QString> operadores;
     QList <QString> postfijo;
     float solve(QString num1,QString num2,QString operador);
     void enviarDatosParaResolver();
     bool esOperador(QString dato);
     float total;
     int cuantosOp;
     int tablaDePrioridad(QString data);
     int posicionar;
};

#endif // CALCU_H




