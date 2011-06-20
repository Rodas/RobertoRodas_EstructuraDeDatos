#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Rodas Calculator.");
    c = new calcu();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::obtenerToken(QString data){
    c->tokens.clear();
    c->operadores.clear();
    c->postfijo.clear();
    int cont = 0;
    c->tokens.push_back("");

    for(int r=0;r<data.count();r++)
    {
        if(data.at(r)!= '+' && data.at(r)!= '-' && data.at(r) != '^'&&
           data.at(r)!= '/' && data.at(r)!= '*' && data.at(r) != 'SEN' &&
           data.at(r) != 'COS' && data.at(r)!= '(' && data.at(r) != ')')
        {
            c->tokens[cont]+=data.at(r);
        }else
        {
            if(data.at(r) != 'COS' && data.at(r) != 'SEN'){
            cont += 2;
            c->tokens.push_back(data.at(r));
            c->tokens.push_back("");
        }else{
            cont += 2;
            c->tokens.push_back("*");
            c->tokens.push_back(data.at(r));
            c->tokens.push_back("");

        }

        }
    }
    for(int r=0;r<c->tokens.count();r++)
    {
        if(c->tokens.at(r)=="")
        {
            c->tokens.removeAt(r);
            r--;
        }
    }
    for(int r=0;r<c->tokens.count();r++)
    {
        qDebug()<<c->tokens.at(r);
    }
}
void MainWindow::on_Solve_clicked()
{
    this->ui->postfijo_LE->clear();
    QString data = this->ui->LineaDeComandos->text();
    this->obtenerToken(data);
  //  if(this->comprobar()){
    for(int r=1;r<c->tokens.count();r++)
    {
        if(this->c->tokens.at(r) == "("){
            if(this->c->tokens.at(r-1) == ")" || !c->esOperador(this->c->tokens.at(r-1))){
            c->tokens.insert(r,"*");
            r++;
            }

        }
    }
    c->cambiar_Postfijo();
    QString post;
    for(int r=0;r<c->postfijo.count();r++)
    {
        post.append(c->postfijo.at(r));
    }
    this->ui->LineaDeComandos->setText(post);
  //  }else
    //{
      //  QMessageBox::about(this,"Error","SintaxError: porfavor compruebe la sintaxis");
   // }
}
bool MainWindow::comprobar()
{
    return true;
  /*  int cont1=0;
    int cont2=0;
    for(int r=0;r<c->tokens.count()-1;r++)
    {
     qDebug()<<r;
        if(c->tokens.at(r) == "(" && c->tokens.at(r+1)==")"){
            qDebug()<<"entraaaaaaaaaaaaaaaaaaaaaaaaaaaa";
            return false;
        }
      // if(c->esOperador(c->tokens.at(r)) && c->esOperador(c->tokens.at(r+1)) && c->tokens.at(r+1) != "(" && c->tokens.at(r-1)!=")")
      //  {
      //      return false;
      //  }




}
    for(int r=0;r<c->tokens.count();r++)
    {
        if(c->tokens.at(r) == "(")
            cont1++;
        if(c->tokens.at(r) == ")")
            cont2++;
    }
        if(cont1 == cont2)
        return true;
        else
        return false;*/
}

// desde aki estan los botones!!

void MainWindow::on_Number0_clicked()
{
    this->ui->LineaDeComandos->setText(this->ui->LineaDeComandos->text()+"0");
}

void MainWindow::on_Number1_clicked()
{
    this->ui->LineaDeComandos->setText(this->ui->LineaDeComandos->text()+"1");
}

void MainWindow::on_Number2_clicked()
{
    this->ui->LineaDeComandos->setText(this->ui->LineaDeComandos->text()+"2");
}

void MainWindow::on_Number3_clicked()
{
    this->ui->LineaDeComandos->setText(this->ui->LineaDeComandos->text()+"3");
}

void MainWindow::on_Number4_clicked()
{
    this->ui->LineaDeComandos->setText(this->ui->LineaDeComandos->text()+"4");
}

void MainWindow::on_Number5_clicked()
{
    this->ui->LineaDeComandos->setText(this->ui->LineaDeComandos->text()+"5");
}

void MainWindow::on_Number6_clicked()
{
    this->ui->LineaDeComandos->setText(this->ui->LineaDeComandos->text()+"6");
}

void MainWindow::on_Number7_clicked()
{
    this->ui->LineaDeComandos->setText(this->ui->LineaDeComandos->text()+"7");
}

void MainWindow::on_Number8_clicked()
{
    this->ui->LineaDeComandos->setText(this->ui->LineaDeComandos->text()+"8");
}

void MainWindow::on_Number9_clicked()
{
    this->ui->LineaDeComandos->setText(this->ui->LineaDeComandos->text()+"9");
}

void MainWindow::on_operador_Division_clicked()
{
    this->ui->LineaDeComandos->setText(this->ui->LineaDeComandos->text()+"/");
}

void MainWindow::on_Operador_Multiplicacion_clicked()
{
    this->ui->LineaDeComandos->setText(this->ui->LineaDeComandos->text()+"*");
}

void MainWindow::on_Operador_Suma_clicked()
{
    this->ui->LineaDeComandos->setText(this->ui->LineaDeComandos->text()+"+");
}

void MainWindow::on_Operador_Resta_clicked()
{
    this->ui->LineaDeComandos->setText(this->ui->LineaDeComandos->text()+"-");
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
    this->ui->LineaDeComandos->setText(this->ui->LineaDeComandos->text()+"^");
}

void MainWindow::on_Operador_coseno_clicked()
{
    this->ui->LineaDeComandos->setText(this->ui->LineaDeComandos->text()+"COS()");
    this->ui->LineaDeComandos->setCursorPosition(this->ui->LineaDeComandos->text().count()-2);
}

void MainWindow::on_Operador_seno_clicked()
{
    this->ui->LineaDeComandos->setText(this->ui->LineaDeComandos->text()+"SEN()");
    this->ui->LineaDeComandos->setCursorPosition(this->ui->LineaDeComandos->text().count()-2);

}
