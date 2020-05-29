#include "../include/agree_gui/matrix.h"
#include "ui_matrix.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

#include <QTableView>

matrix::matrix(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::matrix)
{
  ui->setupUi(this);
  // Create a data model for the mapping table from a CSV file
  csvModel = new QStandardItemModel(this);
  csvModel->setColumnCount(3);
  csvModel->setHorizontalHeaderLabels(QStringList() << "x" << "y" << "bool");
  ui->tableView_1->setModel(csvModel);

  // load the .csv file
   QFile file("/home/alice/catkin_ws/src/agree_gui/resources/Punti_tappetino.csv");
   if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
       qDebug() << "File not exists";
   }
   else {
      qDebug() <<  "fatto";
      QTextStream in(&file);

   while (!in.atEnd())
   {
       QString line = in.readLine();
       // Adding to the model in line with the elements
       QList<QStandardItem *> standardItemsList;
       // consider that the line separated by semicolons into columns
       for (QString item : line.split(";")) {
           standardItemsList.append(new QStandardItem(item));
       }
        csvModel->insertRow(csvModel->rowCount(), standardItemsList);
   }
    file.close();
}
}

matrix::~matrix()
{
  delete ui;
}
