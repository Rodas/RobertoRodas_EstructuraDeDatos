#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <iostream>
#include <fstream>
#include <string>
#include <QList>
#include <QMessageBox>
#include <QTime>
#include <QFileDialog>

using namespace std;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int PalabraMasLarga; // este guarda el count de la palabra mas larga!
    int cuantos;
    int FunctionSuperHash(char const*v);
    int FunctionSuperHash2(QString pal);
    int NCASILLAS;
    int ContadorDeEncontradas;
    QChar **container;
    QList<QString> *Elementos;
    QString lementos[180000];
    QTime ConteoDelTiempo;
    QList<QString> PalabrasEncontradas;
    int funcionVistaEnClase(QString Data);
    int hash(char *str);
    void Limpiar();


private:
    Ui::MainWindow *ui;
    void YaResolviendo(int pos1,int pos2);
    bool Existe(QString pal);

private slots:
    void on_CagarSopa_PB_clicked();
    void on_Resolver_PB_clicked();
    void on_CagarPalabras_PB_clicked();
};

#endif // MAINWINDOW_H
