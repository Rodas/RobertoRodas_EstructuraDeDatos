#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    PalabraMasLarga = 0;
    NCASILLAS = 180000;
    cuantos = 0;
    this->Elementos = new QList<QString>[NCASILLAS];
}

MainWindow::~MainWindow()
{
    delete []Elementos;
    delete ui;
}
int MainWindow::FunctionSuperHash(const char *v)
{
        int n = strlen(v);
        const char *d = v;
        int h = 0;

        for(int i=0; i<n; i++,d++  )
            h = (h<<2)+ *d;

        return ((h >= 0) ? (h % NCASILLAS) : (-h % NCASILLAS));

}

void MainWindow::on_CagarPalabras_PB_clicked()
{
    QString pal;
    QString path = QFileDialog::getOpenFileName(this,"Cargar Palabras");
    ifstream in(path.toStdString().c_str());
    while (in.good())
        {
         string linea;
         getline(in, linea);
         pal = QString::fromStdString(linea);
         if(pal.count() > PalabraMasLarga)              // este if saca
             this->PalabraMasLarga = pal.count();       // el count de
         const char *s;                                 // la palabra mas grande
         s = pal.toAscii();
         int num = this->FunctionSuperHash(s);
         //int num = this->FunctionSuperHash2(pal);
         bool temporal = false;
         for(int r=0;r<Elementos[num].count();r++)
         {
             if(Elementos[num].at(r) == pal)
             {
               temporal = true;
             }
         }
         if(!temporal)
         Elementos[num].push_back(s);
         temporal = false;

      }


    QMessageBox::about(this,"Exito","Se han cargado Exitosamente");

}

void MainWindow::on_Resolver_PB_clicked()
{
    this->PalabrasEncontradas.clear();
    this->ui->PalabrasListas->clear();

    this->ConteoDelTiempo.start();
    for(int r=0;r<this->cuantos;r++)
    {
        for(int a=0;a<this->cuantos;a++)
        {
            this->YaResolviendo(r,a);
        }
    }
    int t = this->ConteoDelTiempo.elapsed();
    QString tiempo;
    tiempo.append(QString("%1").arg(t));
    QString cuantasPal;
    cuantasPal.append(QString("%1").arg(this->PalabrasEncontradas.count()));


    QMessageBox::about(this,":D","Se han encontrado: "+cuantasPal+" En un lapso de tiempo de: "+tiempo);

    qSort(this->PalabrasEncontradas);
    this->ui->PalabrasListas->addItems(PalabrasEncontradas);
}
void MainWindow::YaResolviendo(int pos1, int pos2)
{   // temporales de avanse para adelante
    int pos2ad = pos2;
    bool terAdelante = false;
    // temporales de avanse para abajo
    int pos1Ab = pos1;
    bool terAbajo = false;
    // temporales de avanse para atras
    int pos2at = pos2;
    bool terAtras = false;
    // temporales de avanse para arriba
    int pos1Arriba = pos1;
    bool terArriba = false;
    // temporales de avanse para D1
    int pos1D1 = pos1;
    int pos2D1 = pos2;
    bool terD1 = false;
    // temporales de avanse para D2
    int pos1D2 = pos1;
    int pos2D2 = pos2;
    bool terD2 = false;
    // temporales de avanse para D2
    int pos1D3 = pos1;
    int pos2D3 = pos2;
    bool terD3 = false;
    // temporales de avanse para D2
    int pos1D4 = pos1;
    int pos2D4 = pos2;
    bool terD4 = false;

    QString Adelante;
    QString Abajo;
    QString Atras;
    QString Arriba;
    QString D1; //arriba derecha
    QString D2; //arriba izquierda
    QString D3; //abajo izquierda
    QString D4; //abajo derecha
    int contador = 0;

    while(contador != PalabraMasLarga){


    if(pos2ad<=cuantos-1 && pos2ad >=0){
    Adelante.append(this->container[pos1][pos2ad]);
    pos2ad++;
    }else
        terAdelante = true;
    if(pos1Ab<=cuantos-1 && pos1Ab >=0){
    Abajo.append(this->container[pos1Ab][pos2]);
    pos1Ab++;
    }else
        terAbajo = true;
    if(pos2at<=cuantos-1 && pos2at >=0){
    Atras.append(this->container[pos1][pos2at]);
    pos2at--;
    }else
        terAtras = true;
    if(pos1Arriba<=cuantos-1 && pos1Arriba >=0){
    Arriba.append(this->container[pos1Arriba][pos2]);
    pos1Arriba--;

    }else
        terArriba = true;

    //Diagonales
    if(pos1D1<=cuantos-1 && pos1D1 >=0 && pos2D1<=cuantos-1 && pos2D1>=0){
    D1.append(this->container[pos1D1][pos2D1]);
    pos1D1--;
    pos2D1++;
    }else
        terD1 = true;
    if(pos1D2<=cuantos-1 && pos1D2 >=0 && pos2D2<=cuantos-1 && pos2D2>=0){
    D2.append(this->container[pos1D2][pos2D2]);
    pos1D2--;
    pos2D2--;
    }else
        terD2 = true;
    if(pos1D3<=cuantos-1 && pos1D3 >=0 && pos2D3<=cuantos-1 && pos2D3>=0){
    D3.append(this->container[pos1D3][pos2D3]);
    pos1D3++;
    pos2D3--;
    }else
        terD3 = true;
    if(pos1D4<=cuantos-1 && pos1D4 >=0 && pos2D4<=cuantos-1 && pos2D4>=0){
    D4.append(this->container[pos1D4][pos2D4]);
    pos1D4++;
    pos2D4++;
    }else
        terD4 = true;



    if(pos2ad >=cuantos && pos1Ab >= cuantos && pos2at <=0 && pos1Arriba >=cuantos
       && pos1D1<=0 && pos2D1 >= cuantos && pos1D2<=0 && pos2D2 <=0
       && pos1D3<=0 && pos2D3>=cuantos && pos1D4>=cuantos && pos1D4>=cuantos){
        break;
    }

    contador++;
        if(contador>=3 && contador<=this->PalabraMasLarga)
        {
            if(this->Existe(Adelante) && !terAdelante){
                this->PalabrasEncontradas.push_back(Adelante+" "+QString::number(pos1)+","+QString::number(pos2ad)+"--Adelante");
            }
            if(this->Existe(Abajo) && !terAbajo){
                this->PalabrasEncontradas.push_back(Abajo+" "+QString::number(pos1Ab)+","+QString::number(pos2)+"--Abajo");
            }
            if(this->Existe(Atras) && !terAtras){
                this->PalabrasEncontradas.push_back(Atras+" "+QString::number(pos1)+","+QString::number(pos2at)+"--Atras");
            }
            if(this->Existe(Arriba) && !terArriba){
                this->PalabrasEncontradas.push_back(Arriba+" "+QString::number(pos1Arriba)+","+QString::number(pos2)+"--Arriba");
            }
            if(this->Existe(D1) && !terD1){
                this->PalabrasEncontradas.push_back(D1+" "+QString::number(pos1D1)+","+QString::number(pos2D1)+"--D1");
            }
            if(this->Existe(D2) && !terD2){
                this->PalabrasEncontradas.push_back(D2+" "+QString::number(pos1D2)+","+QString::number(pos2D2)+"--D2");
            }
            if(this->Existe(D3) && !terD3){
                this->PalabrasEncontradas.push_back(D3+" "+QString::number(pos1D3)+","+QString::number(pos2D3)+"--D3");
            }
            if(this->Existe(D4) && !terD4){
                this->PalabrasEncontradas.push_back(D4+" "+QString::number(pos1D4)+","+QString::number(pos2D4)+"--D4");
            }


        }
    }

}
bool MainWindow::Existe(QString pal)
{
    const char *s;
    s = pal.toAscii();
    int pos = this->FunctionSuperHash(s);
//int pos = this->FunctionSuperHash2(pal);
    for(int r=0;r<Elementos[pos].count();r++)
    {
        if(pal == this->Elementos[pos].at(r))
        {
            return true;
        }
    }
return false;
}
int MainWindow::hash(char *str)
{
     int sum;

     // Make sure a valid string passed in
     if (str==NULL) return -1;

     // Sum up all the characters in the string
     for( ; *str; str++) sum += *str;

     // Return the sum mod the table size
     return sum % NCASILLAS;
 }
int MainWindow::FunctionSuperHash2(QString pal)
{
    unsigned int hash = 0;
    for(int r = 0;r<pal.length();r++)
    {
        hash += pal.at(r).toAscii();
        hash += (hash<< 2);
        hash ^= (hash<< 6);
    }
    hash += (hash<< 1);
    hash ^= (hash<< 2);
    hash += (hash<< 4);

    return (hash % NCASILLAS);
}


void MainWindow::on_CagarSopa_PB_clicked()
{
        int cont=0;
        this->Limpiar();
        int contador=0;

        QString pal;
        QString path = QFileDialog::getOpenFileName(this,"Cargar Sopa");
        ifstream in(path.toStdString().c_str());
        while (in.good())
            {
             string linea;
             getline(in, linea);
             pal = QString::fromStdString(linea);
             if(contador == 0){
                 this->cuantos = pal.count();
                 this->ui->tableWidget->setRowCount(this->cuantos);
                 this->ui->tableWidget->setColumnCount(this->cuantos);

                 container = new QChar*[cuantos];
                 for(int i=0;i<cuantos;i++)
                 {
                     container[i] = new QChar[cuantos];
                 }
                 contador++;
             }

             for(int r=0;r<pal.count();r++)
             {
                // QString dato; dato.setNum((cont,r));
                 QTableWidgetItem *item = new QTableWidgetItem(pal.at(r));
                 this->ui->tableWidget->setItem(cont,r,item);
                 this->container[cont][r] = pal.at(r).toLower();
             }
             cont++;
            }

        for(int r=0;r<cuantos;r++)
        {
            for(int i=0;i<cuantos;i++)
            {
                qDebug()<<container[r][i];
            }
        }

}
void MainWindow::Limpiar()
{
    this->ui->tableWidget->clear();

    for(int r=0;r<cuantos;r++)
    {
        delete[]container[r];
    }
    delete []container;
}
