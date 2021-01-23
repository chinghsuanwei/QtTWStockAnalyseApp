#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile file("D:\\Stock\\Investments\\20210122.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    in.setCodec("Big5");

    in.readLine(); //ignore first line
    in.readLine(); //ignore second line
    while (!in.atEnd()) {
        QString line = in.readLine();
        //" ","2303  ","聯電            ","7,322,000","201,000","7,121,000",
        int start = line.indexOf("\"");
        int end = line.indexOf("\"", start+1);
        QString none = line.mid(start+1, end - start);

        start = line.indexOf("\"", end+1);
        end = line.indexOf("\"", start+1);
        QString stock_code = line.mid(start+1, end - start - 1).trimmed();

        if(stock_code.isEmpty()) continue;

        start = line.indexOf("\"", end+1);
        end = line.indexOf("\"", start+1);
        QString company_name = line.mid(start+1, end - start - 1);

        start = line.indexOf("\"", end+1);
        end = line.indexOf("\"", start+1);
        QString shares_bought = line.mid(start+1, end - start - 1);

        start = line.indexOf("\"", end+1);
        end = line.indexOf("\"", start+1);
        QString shares_sold = line.mid(start+1, end - start - 1);

        start = line.indexOf("\"", end+1);
        end = line.indexOf("\"", start+1);
        QString difference = line.mid(start+1, end - start - 1);

        ui->tableWidget->insertRow( ui->tableWidget->rowCount() );
        ui->tableWidget->setItem( ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(stock_code));
        ui->tableWidget->setItem( ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(company_name));
        ui->tableWidget->setItem( ui->tableWidget->rowCount()-1, 2, new QTableWidgetItem(shares_bought));
        ui->tableWidget->setItem( ui->tableWidget->rowCount()-1, 3, new QTableWidgetItem(shares_sold));
        ui->tableWidget->setItem( ui->tableWidget->rowCount()-1, 4, new QTableWidgetItem(difference));

    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

