#pragma once

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    double valueA;
    double valueB;
    bool newInput;
    bool hasTwoValues;
    bool equalsButtonClicked;
    QChar mathAction;

private slots:
    void on_numberButton_clicked();
    void on_commaButton_clicked();
    void on_mathButton_clicked();
    void on_equalsButton_clicked();
    void on_backButton_clicked();
    void on_clearButton_clicked();
    void on_negateButton_clicked();

private:
    double doMathAction();
};
