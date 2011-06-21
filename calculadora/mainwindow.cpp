#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->x=150;
    this->y=150;
    this->scene.setSceneRect(0,0,300,400);
    this->scene.addRect(0,0,300,400);

    this->view = new QGraphicsView(&scene);
    scene.addLine(this->x,0,this->x,this->scene.height(),QPen(Qt::red));
    scene.addLine(0,this->y,this->scene.width(),this->y,QPen(Qt::red));
    this->scene.setBackgroundBrush(QBrush(Qt::darkBlue));
    this->ui->grid->addWidget(this->view);

    this->setWindowTitle("Rodas Calculator.");
    c = new calcu();
}

MainWindow::~MainWindow()
{
    delete ui;
}
QString MainWindow::solve(QString data)
{
    if(this->comprobarCaracteresValidos(data.toLower())){
    int c1=0;
    int c2=0;
    int t1=0;
    int t2=0;
for(int r=0;r<c->tokens.count();r++)
{
  if(r!=0){
     if(c->tokens.at(r) == "cos"){
         this->solveUnitario(r);
         qDebug()<<"si parece q si";
         c->tokens[r]= QString::number(cos(c->tokens.at(r+2).toFloat()));

         c->tokens.removeAt(r+1);
         c->tokens.removeAt(r+1);
         c->tokens.removeAt(r+1);
         if(!c->esOperador(c->tokens.at(r-1)))
         c->tokens.insert(r,"*");
         for(int i=0;i<c->tokens.count();i++)
         {
             qDebug()<<c->tokens.at(i)<<"asiiiiiiiiipapaaaaa";
         }
         r--;

     }else if(c->tokens.at(r) == "sin"){
         this->solveUnitario(r);
         qDebug()<<"si parece q si";
         c->tokens[r]= QString::number(sin(c->tokens.at(r+2).toFloat()));

         c->tokens.removeAt(r+1);
         c->tokens.removeAt(r+1);
         c->tokens.removeAt(r+1);
         if(!c->esOperador(c->tokens.at(r-1)))
         c->tokens.insert(r,"*");
         for(int i=0;i<c->tokens.count();i++)
         {
             qDebug()<<c->tokens.at(i)<<"asiiiiiiiiipapaaaaa";
         }
         r--;

     }
}if(r==0)
  {
     if(c->tokens.at(r) == "cos"){
         this->solveUnitario(r);
         qDebug()<<"si parece q si el otro";
         c->tokens[r]= QString::number(cos(c->tokens.at(r+2).toFloat()));
         c->tokens.removeAt(r+1);
         c->tokens.removeAt(r+1);
         c->tokens.removeAt(r+1);
         r--;

    }else if(c->tokens.at(r) == "sin"){
        this->solveUnitario(r);
        qDebug()<<"si parece q si el otro";
        c->tokens[r]= QString::number(sin(c->tokens.at(r+2).toFloat()));
        c->tokens.removeAt(r+1);
        c->tokens.removeAt(r+1);
        c->tokens.removeAt(r+1);
        r--;

}

  }
}
    for(int r=0;r<c->tokens.count();r++)
    {
        if(this->c->tokens.at(r)=="("){
            c1++;
            t1=r;

        }if(this->c->tokens.at(r)==")"){
            c2++;
            t2=r;
        }
        if(c1!=0 && c1==c2)
        {
            if(!comprobarExisteDatoEntreEllos(t1,t2))
            {
                QMessageBox::about(this,"Error","SintaxError: () dato invalido ");
                return "() dato invalido";
            }

        }
        if(c->tokens.at(r)!="(" && c->tokens.at(r)!=")" && this->c->esOperador(c->tokens.at(r)))
        {
            if(!this->comprobarDatoAntesDespues(r))
            {
                QMessageBox::about(this,"Error","SintaxError: no se puede resolver sin 2 argumentos entre el operador");
                return "no valid * without arguments :)";
            }
        }
    }
    if(c1!=c2)
    {
        qDebug()<<"desde akiiii";
        for(int r=0;r<c->tokens.count();r++)
        {
            qDebug()<<c->tokens.at(r);
        }
        QMessageBox::about(this,"Error","SintaxError: missing ( or ) ");
        return " missing()";
    }


    for(int r=1;r<c->tokens.count();r++)
    {
        if(this->c->tokens.at(r) == "("){
            if(this->c->tokens.at(r-1) == ")" || !c->esOperador(this->c->tokens.at(r-1))){
            c->tokens.insert(r,"*");
            r--;
        }
        }else{
            if(r < c->tokens.count()-1){
            if(this->c->tokens.at(r) == ")" && this->c->tokens.at(r+1) != "("){
                  if(!c->esOperador(this->c->tokens.at(r+1))){
                  c->tokens.insert(r+1,"*");
                   r--;
                 }
             }

        }else
            break;
        }
    }
    c->cambiar_Postfijo();
    QString post;
    for(int r=0;r<c->postfijo.count();r++)
    {
        post.append(c->postfijo.at(r));
    }
    this->ui->LineaDeComandos->setText(post);
    return post;
  //  }else
    //{
      //  QMessageBox::about(this,"Error","SintaxError: porfavor compruebe la sintaxis");
   // }
}else
    QMessageBox::about(this,"Error","SintaxError: Caracteres no validos");

}

void MainWindow::on_Solve_clicked()
{
    c->tokens.clear();
    c->operadores.clear();
    c->postfijo.clear();
    c->post.clear();
    this->ui->postfijo_LE->clear();
    QString data = this->ui->LineaDeComandos->text().trimmed();
    this->solve(data);
    this->ui->postfijo_LE->setText(c->post);
}
void MainWindow::solveUnitario(int pos)
{
    QString dataAEnviar;
    int cont1=1;
    int cont2=0;
    int otro = pos+1;
    int r=pos+2;
    if(c->tokens.at(pos) == "cos" || c->tokens.at(pos) == "sin")
    {
        dataAEnviar.append("(");
        while(cont1 != cont2)
        {
            otro++;
            qDebug()<<"entraotro";
            if(c->tokens.at(r)=="(")
            {
                qDebug()<<"entra1";
                dataAEnviar.append(c->tokens.at(r));
                r++;
                cont1++;

            }
            else if(c->tokens.at(r)==")")
            {
                qDebug()<<"entra2";
                dataAEnviar.append(c->tokens.at(r));
                r++;
                cont2++;
            }else
            {
                qDebug()<<"entra3";
                dataAEnviar.append(c->tokens.at(r));
                r++;
            }

        }
        qDebug()<<"entra4";
        QList<QString> temp;
        for(int i=0;i<c->tokens.count();i++)
        {
            temp.push_back(c->tokens.at(i));
        }
        c->tokens.clear();
        QString datoTemp = this->solve(dataAEnviar);
        qDebug()<<datoTemp<<"este";
        c->tokens.clear();

        for(int i=0;i<temp.count();i++)
        {
            c->tokens.push_back(temp.at(i));
        }
        for(int i=0;i<c->tokens.count();i++)
        {
            qDebug()<<c->tokens.at(i)<<".."<<i<<pos<<otro;
        }
        for(int i=pos+2;i<otro;i++)
        {
            c->tokens.removeAt(pos+2);
        }
        for(int i=0;i<c->tokens.count();i++)
        {
            qDebug()<<c->tokens.at(i)<<"asi keda";
        }
        c->tokens.insert(pos+2,datoTemp);

        for(int i=0;i<c->tokens.count();i++)
        {
            qDebug()<<c->tokens.at(i)<<"......"<<c->tokens.count()<<otro;
        }






    }
   /* if(c->tokens.at(pos) == "sen")
    {   // aki hacer parecido al coseno!!

    }*/
}

bool MainWindow::comprobarCaracteresValidos(QString data)
{
    int cont = 0;
    int contmalas = 0;
    QString tok;
    for(int r=0;r<data.count();r++)
    {
        if(data.at(r) == '1' || data.at(r) == '2' || data.at(r) == '3' || data.at(r) == '4' ||
           data.at(r) == '5' || data.at(r) == '6' || data.at(r) == '7' || data.at(r) == '8' ||
           data.at(r) == '9' || data.at(r) == '0' || data.at(r) == '*' | data.at(r) == '/'  ||
           data.at(r) == '+' || data.at(r) == '-' || data.at(r) == '^' || data.at(r) == '(' ||
           data.at(r) == ')' || data.at(r) == '.' || data.at(r) == 'c' || data.at(r) == 'o' ||
           data.at(r) == 's' || data.at(r) == 'i' || data.at(r) == 'n')
        {
            if(data.at(r)=='c')
            {
                if(data.at(r+1)=='o')
                {
                    if(data.at(r+2) == 's'){
                        qDebug()<<"siiiiiiiiiii";
                    cont+=3;
                    r+=2;
                    if(r == 0)
                    c->tokens.push_back("cos");
                    else{
                    c->tokens.push_back(tok);
                    c->tokens.push_back("cos");
                    tok.clear();
                    }
                    }else
                    {

                        return false;
                    }
                }else
                {
                    return false;
                }
            }else if(data.at(r)== 's')
            {
                if(data.at(r+1)=='i')
                {
                    if(data.at(r+2) == 'n'){
                     cont+=3;
                     r+=2;
                    if(r == 0)
                    c->tokens.push_back("sin");
                    else{
                    c->tokens.push_back(tok);
                    c->tokens.push_back("sin");
                    tok.clear();
                    }
                    }else
                    {
                        return false;
                    }
                }else
                {
                    return false;
                }


            }else
            {
                if(c->esOperador(data.at(r)))
                {
                    if(tok != "")
                    {
                        c->tokens.push_back(tok);
                        c->tokens.push_back(data.at(r));
                        tok.clear();
                    }else
                    {
                        c->tokens.push_back(data.at(r));
                    }

                }else if(this->esNum(data.at(r)))
                {
                    qDebug()<<"entra"<<r;
                    tok.append(data.at(r));
                    if(r == data.count()-1)
                    {
                        c->tokens.push_back(tok);
                    }
                }
                cont++;
            }

        }
    }
    for(int i=0;i<c->tokens.count();i++)
    {
        if(c->tokens.at(i)=="")
        {
            c->tokens.removeAt(i);
            i--;
        }
    }
    for(int i=0;i<c->tokens.count();i++)
    {
        qDebug()<<c->tokens.at(i)<<"estoakiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii";
    }
    qDebug()<<cont<<"buenas"<<contmalas<<"malas"<<"total:"<<data.count();
    if(cont == data.count())
        return true;
    else
        return false;
}

bool MainWindow::comprobarExisteDatoEntreEllos(int pos1, int pos2)
{
    if((pos2-pos1)==1)
        return false;
    return true;

}
bool MainWindow::comprobarDatoAntesDespues(int pos1)
{
    if(pos1!=0 && pos1!=c->tokens.count()-1)
    {
        if(c->tokens.at(pos1-1) == ")" && c->tokens.at(pos1+1)=="(")
            return true;
        else if(c->tokens.at(pos1-1) == ")" && !c->esOperador(c->tokens.at(pos1+1)))
            return true;
        else if(!c->esOperador(c->tokens.at(pos1-1)) && c->tokens.at(pos1+1)=="(")
            return true;

        if(!c->esOperador(c->tokens.at(pos1-1))&&!c->esOperador(c->tokens.at(pos1+1)))
        {
            return true;
        }else
            return false;
    }else
        return false;
}

// desde aki estan los botones!!

void MainWindow::on_Number0_clicked()
{
    this->ui->LineaDeComandos->insert("0");
}

void MainWindow::on_Number1_clicked()
{
    this->ui->LineaDeComandos->insert("1");
}

void MainWindow::on_Number2_clicked()
{
    this->ui->LineaDeComandos->insert("2");
}

void MainWindow::on_Number3_clicked()
{
    this->ui->LineaDeComandos->insert("3");
}

void MainWindow::on_Number4_clicked()
{
    this->ui->LineaDeComandos->insert("4");
}

void MainWindow::on_Number5_clicked()
{
    this->ui->LineaDeComandos->insert("5");
}

void MainWindow::on_Number6_clicked()
{
    this->ui->LineaDeComandos->insert("6");
}

void MainWindow::on_Number7_clicked()
{
    this->ui->LineaDeComandos->insert("7");
}

void MainWindow::on_Number8_clicked()
{
    this->ui->LineaDeComandos->insert("8");
}

void MainWindow::on_Number9_clicked()
{
    this->ui->LineaDeComandos->insert("9");
}

void MainWindow::on_operador_Division_clicked()
{
    this->ui->LineaDeComandos->insert("/");
}

void MainWindow::on_Operador_Multiplicacion_clicked()
{
    this->ui->LineaDeComandos->insert("*");
}

void MainWindow::on_Operador_Suma_clicked()
{
    this->ui->LineaDeComandos->insert("+");
}

void MainWindow::on_Operador_Resta_clicked()
{
    this->ui->LineaDeComandos->insert("-");
}

void MainWindow::on_Operador_Delete_clicked()
{
    this->ui->LineaDeComandos->backspace();
}

void MainWindow::on_Operador_Clear_clicked()
{
    this->ui->LineaDeComandos->clear();
}

void MainWindow::on_Operador_elevar_clicked()
{
    this->ui->LineaDeComandos->insert("^");
}

void MainWindow::on_Operador_coseno_clicked()
{
    this->ui->LineaDeComandos->insert("cos()");
    this->ui->LineaDeComandos->setCursorPosition(this->ui->LineaDeComandos->text().count()-1);
}

void MainWindow::on_Operador_seno_clicked()
{
    this->ui->LineaDeComandos->insert("sin()");
    this->ui->LineaDeComandos->setCursorPosition(this->ui->LineaDeComandos->text().count()-1);

}
bool MainWindow::esNum(QString c)
{
    if(c == "1" || c == "2" || c == "3" || c == "4" || c == "5" || c == "6" || c == "7" || c == "8" || c == "9" ||
       c == "0" || c == ".")
        return true;
    else
        return false;
}

void MainWindow::on_Operador_abrir_clicked()
{
    this->ui->LineaDeComandos->insert("(");
}

void MainWindow::on_Operador_cerrar_clicked()
{
    this->ui->LineaDeComandos->insert(")");
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this,"info","                Calculadora\nCreador: Roberto Armando Rodas\nCatedratico: ing. Rogger Vasquez\nProyecto n°2");
}

void MainWindow::on_graficar_clicked()
{
    int de = this->ui->intervale1->text().trimmed().toFloat();
    int a = this->ui->intervalo2->text().trimmed().toFloat();
    QString funcion = this->ui->funcion_graf->text().trimmed();

    this->evaluarGrafica(de,a,funcion);
}
void MainWindow::evaluarGrafica(int de1, int hasta,QString funcion)
{
    for(int r=de1;r<hasta;r++){
   this->solve(funcion); // aki graficar
}

}
