#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), valueA(0), valueB(0), newInput(true), hasTwoValues(false), equalsButtonClicked(false), mathAction(0)
{
    ui->setupUi(this);

    for (int i = 0; i < 10; i++)
    {
        QString buttonName = "button" + QString::number(i);
        connect(MainWindow::findChild<QPushButton*>(buttonName), SIGNAL(clicked()), this, SLOT(on_numberButton_clicked()));
    }

    connect(ui->buttonComma, SIGNAL(clicked()), this, SLOT(on_commaButton_clicked()));

    connect(ui->buttonDivide, SIGNAL(clicked()), this, SLOT(on_mathButton_clicked()));
    connect(ui->buttonMultiply, SIGNAL(clicked()), this, SLOT(on_mathButton_clicked()));
    connect(ui->buttonSubtract, SIGNAL(clicked()), this, SLOT(on_mathButton_clicked()));
    connect(ui->buttonAdd, SIGNAL(clicked()), this, SLOT(on_mathButton_clicked()));

    connect(ui->buttonEquals, SIGNAL(clicked()), this, SLOT(on_equalsButton_clicked()));
    connect(ui->buttonBack, SIGNAL(clicked()), this, SLOT(on_backButton_clicked()));
    connect(ui->buttonClear, SIGNAL(clicked()), this, SLOT(on_clearButton_clicked()));
    connect(ui->buttonNegate, SIGNAL(clicked()), this, SLOT(on_negateButton_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_numberButton_clicked()
{
    QPushButton* button = (QPushButton*)sender();

    if (equalsButtonClicked)
        on_clearButton_clicked();

    if (!newInput)
        ui->result->setText("");

    if (ui->result->text() == "0")
        ui->result->setText("");
    ui->result->setText(ui->result->text() + button->text());

    newInput = true;
    equalsButtonClicked = false;
}

void MainWindow::on_commaButton_clicked()
{
    if (ui->result->text() == "0")
        ui->result->setText("0.");
    else
        ui->result->setText(ui->result->text() + ".");

    newInput = true;
    equalsButtonClicked = false;
}

void MainWindow::on_mathButton_clicked()
{
    QPushButton* button = (QPushButton*)sender();

    if (newInput)
    {
        if (!hasTwoValues)
        {
            mathAction = button->text()[0];
            valueA = ui->result->text().toDouble();
            ui->calculations->setText(ui->result->text() + " " + mathAction);
            hasTwoValues = true;
        }
        else
        {
            valueB = ui->result->text().toDouble();
            valueA = doMathAction();

            mathAction = button->text()[0];

            ui->calculations->setText(ui->calculations->text() + " " + QString::number(valueB) + " " + mathAction);
            ui->result->setText(QString::number(valueA, 'g', 11));
        }
    }
    else if (equalsButtonClicked)
    {
        valueB = ui->result->text().toDouble();

        mathAction = button->text()[0];

        ui->calculations->setText(QString::number(valueA) + " " + mathAction);
        ui->result->setText(QString::number(valueA, 'g', 11));
    }
    else
    {
        mathAction = button->text()[0];

        QString newText = ui->calculations->text();
        newText[newText.length() - 1] = mathAction;
        ui->calculations->setText(newText);
    }

    newInput = false;
    equalsButtonClicked = false;
}

void MainWindow::on_equalsButton_clicked()
{
    if (!equalsButtonClicked)
    {
        valueB = ui->result->text().toDouble();
        valueA = doMathAction();
        ui->calculations->setText(ui->calculations->text() + " " + QString::number(valueB) + " =");
        ui->result->setText(QString::number(valueA, 'g', 11));
    }
    else
    {
        ui->calculations->setText(QString::number(valueA) + " " + mathAction + " " + QString::number(valueB) + " =");
        valueA = doMathAction();
        ui->result->setText(QString::number(valueA, 'g', 11));
    }

    newInput = false;
    equalsButtonClicked = true;
}

void MainWindow::on_backButton_clicked()
{
    if (newInput)
    {
        QString newText = ui->result->text();
        newText.chop(1);
        ui->result->setText(newText);

        if (ui->result->text() == "")
            ui->result->setText("0");
    }
}

void MainWindow::on_clearButton_clicked()
{
    valueA = 0.0;
    valueB = 0.0;

    ui->calculations->setText("");
    ui->result->setText("0");

    newInput = true;
    hasTwoValues = false;
    equalsButtonClicked = false;
}

void MainWindow::on_negateButton_clicked()
{
    QString newText;
    if (ui->result->text()[0] == "-")
        newText = ui->result->text().remove(0, 1);
    else
        newText = "-" + ui->result->text();

    ui->result->setText(newText);
}

double MainWindow::doMathAction()
{
    if (mathAction == '/')
    {
        if (valueB == 0.0)
        {
            on_clearButton_clicked();
        }
        else
        {
            return valueA / valueB;
        }
    }
    else if (mathAction == '*')
    {
        return valueA * valueB;
    }
    else if (mathAction == '-')
    {
        return valueA - valueB;
    }
    else if (mathAction == '+')
    {
        return valueA + valueB;
    }

    return 0.0;
}
