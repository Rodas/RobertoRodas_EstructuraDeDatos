#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->AreaRender = new RenderArea();

    // Crea la red interna, con 6 nodos, con 5 de alcance
    // y los nodos se generan entre 600 a 500 (area )

    this->W = new WireLess(50,0,730,470);



    // Al AreaRender siempre pasarle de parametro solo el grafo y no todo
    // Wireless para no modificar lo que ya se tenia
    this->AreaRender->setGrafo(W->grafo);

    this->ui->gridLayout->addWidget(this->AreaRender,0,0,1,1);

    this->CargarTabladeGrafo();

}


MainWindow::~MainWindow()
{
    delete ui;
    delete this->AreaRender;
    delete this->W;
}

void MainWindow::on_pbAddArista_clicked()
{
    this->W->grafo->addArista(ui->leInicio->text().toInt(),
                           ui->leFinal->text().toInt(),
                           ui->lePeso->text().toFloat());

    this->AreaRender->update();
}

void MainWindow::Floyd()
{
    this->A = new float*[this->W->grafo->getSize()];
    for (int i=0; i<this->W->grafo->getSize();i++)
        this->A[i] = new float[this->W->grafo->getSize()];

    //Copiar la matriz del grafo en A (copia)
    for (int i=0;i<this->W->grafo->getSize();i++)
    {
        for (int j=0; j<this->W->grafo->getSize();j++)
            A[i][j] = this->W->grafo->getPesoArista(i,j);

    }
    // Algoritmo de Floyd
    for (int k =0; k<W->grafo->getSize();k++)
        for (int i =0; i<W->grafo->getSize();i++)
            for (int j =0; j<W->grafo->getSize();j++)
            {
               float peso = A[i][k] + A[k][j];
               if(peso < Grafo::INFINITO)
                   if (peso < A[i][j])
                       A[i][j] = peso ;


             }


    this->CargarTablaFloyd();


}
void MainWindow::CargarTabladeGrafo()
{
    /*this->ui->tableWidget->setRowCount(this->W->grafo->getSize());
    this->ui->tableWidget->setColumnCount(this->W->grafo->getSize());
    // QTableWidgetItem *item = new QTableWidgetItem("X");

    for (int i=0;i<this->W->grafo->getSize();i++)
    {
        for (int j=0; j<this->W->grafo->getSize();j++)
        {
            QString dato;dato.setNum(W->grafo->getPesoArista(i,j));
            QTableWidgetItem *item = new QTableWidgetItem(dato);
            this->ui->tableWidget->setItem(i,j,item);
        }
    }
    for(int i=0;i<W->grafo->getSize();i++)
    {
     QString temp;
     temp.setNum(i);
     ui->tableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(temp));
     ui->tableWidget->setVerticalHeaderItem(i, new QTableWidgetItem(temp));
    }*/
 }




void MainWindow::CargarTablaFloyd()
{
    this->ui->tableWidget->setRowCount(this->W->grafo->getSize());
    this->ui->tableWidget->setColumnCount(this->W->grafo->getSize());

    for (int i=0;i<this->W->grafo->getSize();i++)
    {
        for (int j=0; j<this->W->grafo->getSize();j++)
        {
            QString dato; dato.setNum(A[i][j]);
            QTableWidgetItem *item = new QTableWidgetItem(dato);
            this->ui->tableWidget->setItem(i,j,item);
        }
    }

}


void MainWindow::on_pushButton_clicked()
{
    this->Floyd();
}

void MainWindow::on_Recorrer_PB_clicked()
{
    this->ui->Recorrido_LW->clear();
    this->W->grafo->recorridoEnProfundidad(this->ui->Recorrer_LE->text().toInt(false));
    this->ui->Recorrido_LW->addItems(this->W->grafo->PaQueLosImprima);
    this->W->grafo->Clean();
}
