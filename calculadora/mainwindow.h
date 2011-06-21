#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <QDebug>
#include <QList>
#include "calcu.h"
#include <QMessageBox>
#include <math.h>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTableWidget>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    calcu *c;

    //void obtenerToken(QString data);
    bool comprobarCaracteresValidos(QString data); // obtiene el tokem tambn
    bool comprobarExisteDatoEntreEllos(int pos1,int pos2);
    bool comprobarDatoAntesDespues(int pos1);
    void solveUnitario(int pos);
    bool esNum(QString c);
    QString solve(QString data);
    QString temp;


    // grafico

    int  x;
    int  y;

    QGraphicsScene scene;
    QGraphicsView *view;
    QString funcion;
    void graficar(int x,int y);
    void evaluarGrafica(int de1,int hasta,QString funcion);

private:
    Ui::MainWindow *ui;

private slots:

private slots:
    void on_graficar_clicked();
    void on_actionAbout_triggered();
    void on_Operador_cerrar_clicked();
    void on_Operador_abrir_clicked();
    void on_Operador_seno_clicked();
    void on_Operador_coseno_clicked();
    void on_Operador_elevar_clicked();
    void on_Operador_Clear_clicked();
    void on_Operador_Delete_clicked();
    void on_Operador_Resta_clicked();
    void on_Operador_Suma_clicked();
    void on_Operador_Multiplicacion_clicked();
    void on_operador_Division_clicked();
    void on_Number9_clicked();
    void on_Number8_clicked();
    void on_Number6_clicked();
    void on_Number5_clicked();
    void on_Number4_clicked();
    void on_Number3_clicked();
    void on_Number2_clicked();
    void on_Number1_clicked();
    void on_Number0_clicked();
    void on_Number7_clicked();
    void on_Solve_clicked();
};

#endif // MAINWINDOW_H
