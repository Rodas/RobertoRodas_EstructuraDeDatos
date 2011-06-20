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

    void obtenerToken(QString data);
    bool comprobar();
    bool comprobar2();
    QString temp;

private:
    Ui::MainWindow *ui;

private slots:

private slots:
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
