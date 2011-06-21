#include "calcu.h"

calcu::calcu()
{
    total = 0;
    posicionar = 0;

}
float calcu::solve(QString num1, QString num2, QString operador)
{
 float respuesta;
    if(operador == "*")
           respuesta = num1.toFloat(0)*num2.toFloat(0);
    if(operador == "/")
           respuesta = num1.toFloat(0)/num2.toFloat(0);
    if(operador == "-")
           respuesta = num1.toFloat(0)-num2.toFloat(0);
    if(operador == "+")
           respuesta = num1.toFloat(0)+num2.toFloat(0);
    if(operador == "^")
           respuesta = pow(num1.toFloat(0),num2.toFloat(0));

    return respuesta;

}
void calcu::cambiar_Postfijo()
{
    int cont1=0;
    int cont2=0;
    int r=0;

    for(int r=0;r<this->tokens.count();r++)
    {
        this->postfijo.push_back("");
    }
    while(this->tokens.count()!=0)
    {
        if(this->esOperador(tokens.at(0)))
        {
            if(this->operadores.count()!=0){
                if((this->tablaDePrioridad(this->tokens.at(0))) <= (this->tablaDePrioridad(this->operadores.last())))
                {
                    qDebug()<<"entro siiiiiiiiiii";

                    if(tokens.at(0) == ")")
                    {
                        tokens.removeFirst();
                        while(this->operadores.count()!=0){
                                if(this->operadores.last() == "(")
                                {
                                    this->operadores.removeLast();
                                    break;

                                }else
                                {
                                    this->postfijo[r] = this->operadores.takeLast();
                                    r++;
                                }
                        }//while
                    }else{
                        if(this->tokens.at(0) != "("){
                            this->postfijo[r] = this->operadores.takeLast();
                            this->operadores.push_back(tokens.takeAt(0));
                            r++;
                        }else{
                            this->operadores.push_back(tokens.takeAt(0));
                        }
                    }

             }else
                {
                    this->operadores.push_back(tokens.takeAt(0));
                }
            }else{
                this->operadores.push_back(tokens.takeAt(0));
                }



        }
        else
        {
            this->postfijo[r] = tokens.takeAt(0);
            r++;
        }
    }
    while(this->operadores.count()!=0){
    this->postfijo[r] = this->operadores.takeLast();
    r++;
}

    for(int q=0;q<this->postfijo.count();q++){
     if(this->postfijo.at(q)=="")
    {
        this->postfijo.takeAt(q);
        q--;
    }
}
    for(int i=0;i<this->postfijo.count();i++){
        this->post.append(this->postfijo.at(i));
    }


    this->enviarDatosParaResolver();
}

void calcu::enviarDatosParaResolver()
{
    for(int r=0;r<this->postfijo.count();r++)
    {
        if(esOperador(this->postfijo.at(r)))
        {
            total = this->solve(this->postfijo[r-2],this->postfijo[r-1],this->postfijo[r]);
            this->postfijo.removeAt(r-2);
            this->postfijo.removeAt(r-1);
            this->postfijo[r-2] = QString::number(total);
            r = r-2;

        }
    }
    qDebug()<<total;
}
bool calcu::esOperador(QString dato)
{
    if(dato == "+" ||dato == "-" ||dato == "*" ||dato == "/" || dato == "^"||dato == "(" || dato == ")")
        return true;
    else
        return false;

}
int calcu::tablaDePrioridad(QString data)
{
    if(data == "(")
        return 1;
    if(data=="+"||data=="-")
        return 2;
    if(data=="/"||data=="*")
        return 3;
    if(data=="^")
        return 4;
    if(data == ")")
        return 0;
    return -1;
}
