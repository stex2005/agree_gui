#include "../include/agree_gui/matrixwidget.h"

#include <QFile>
#include <QDebug>

#include <QTableView>

#include <iostream>
#include <fstream>
#include <sstream>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QPainter>
MatrixWidget::MatrixWidget(QWidget *parent) : QWidget(parent)
{
}
void MatrixWidget::mousePressEvent(QMouseEvent *event)
{}
void MatrixWidget::paintEvent(QPaintEvent *event)
{
  QPainter p(this);
  p.drawRect(0,0, width() -1, height() -1);

   // size of area we have. w = width , h = height , we take 2 pixles for border
  int w = width() -2;
  int h = height() - 2;
   // now we loop and drw the boxes
  int bw = w / max_x;
     int bh = h / max_y;
     // now we loop and drw the boxes
     for (int xi = 0; xi < max_x; ++xi) {
         for (int yi = 0; yi < max_x; ++yi) {
             p.drawRect( QRect( xi * bw, yi * bh, bw, bh  ) )  ;
             p.drawText(QRect( xi * bw, yi * bh, bw, bh  ),
                                  QString::number(xi + 1) + "," + QString::number(yi+1) ); // the +1 aswe dont want to use first at 0,0
         }
     }
}
void MatrixWidget::LoadData()
{
  QFile file("/home/alice/catkin_ws/src/agree_gui/resources/Punti_tappetino.csv");
  if(!file.open(QFile::ReadOnly | QFile::Text))
  {
    qDebug()<< "FIle not exist";


  }
  else {
    QTextStream in(&file);
    while (!in.atEnd())
    {
      QString line = in.readLine();
      QStringList list = line.split(";");
      int x = list.at(0).toInt(); //mi riferisco alla prima colonna
      int y = list.at(1).toInt(); // alla seconda
      bool value = list.at(2).toInt(); // ai valori presenti nella 3 (bool)
      if(x<max_x && y<max_y)
        Data[x][y].value = value; // e fintanto che scorro il file vado a riempire nelle posizioni che seleziono mentre leggo il file quello che trovo nella 3 colonna
      else
       qDebug()<< "x or y bigger than matrix!";
      }

  }
   file.close();
}
