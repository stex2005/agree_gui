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
#include <QMouseEvent>
MatrixWidget::MatrixWidget(QWidget *parent) : QWidget(parent)
{
  LoadData();

}
void MatrixWidget::mousePressEvent(QMouseEvent *event)
{
  QPoint p= event->pos(); //dove clicco

  int xindex = p.x()/ bw;
  int yindex = p.y()/ bh;
  qDebug() <<yindex +1 <<" "<< xindex +1;
  //get the data point (check se ind non è fuori dalla griglia)
  DataPoint &dp = Data[yindex+1][xindex +1];

  //zero non selezionabile
  if(dp.value ==0 || dp.DrawColor==Qt::black) return;
  if(dp.isSelected == false)
  {
     if(selCount>2) return;
     dp.DrawColor = Qt::cyan;
     dp.isSelected = true;
     position.append(QPoint(yindex+1,xindex+1));
     auto i1 = position.indexOf(QPoint(yindex+1,xindex+1));
  // position.append(QPoint(yindex+1,xindex+1));


     selCount++;
  }
  else {
    dp.DrawColor = Qt::green;
    dp.isSelected = false;
    selCount--;
    auto i1 = position.indexOf(QPoint(yindex+1,xindex+1));
    QPoint deletedFromVector = position[i1];
    position.remove(i1);
  }
  update(); //aggiorna la griglia


if (selCount==3)
qDebug()<<position;


//   QFile file_1("/home/alice/catkin_ws/src/agree_gui/resources/posizioni.txt");
//   file_1.open(QIODevice::WriteOnly);
//   QDataStream out(&file_1);
//   out << position ;
//   file_1.close();



}
void MatrixWidget::paintEvent(QPaintEvent *event)
{
  QPainter p(this);


  p.drawRect(0,0, width() -1, height() -1);



   // size of area we have. w = width , h = height , we take 2 pixles for border
  int w = width() -2;
  int h = height() - 2;
  //tiro fuori quanto dev essere grande ciascuna cella (divido la dimensione per il numero di celle che voglio avere
   bw = w / max_y; // sono le mie colonne
   bh = h / max_x; // sono le mie righe
     //  loop and drw the boxes, non uso 0,0 perchè i dati partono dalla posizione 1

     for (int xi = 0; xi < max_x-1; ++xi) {

        for (int yi = 0; yi < max_y -1; ++yi) {
                  p.setBrush(QBrush (Data[xi+1][yi+1].DrawColor));
           QRect cellRect(yi*bw,xi*bh, bw,bh);

             p.drawRect( cellRect )  ;
        //    p.drawText(cellRect, QString::number(xi + 1) + "," + QString::number(yi+1) ); // the +1 aswe dont want to use first at 0,0


         }
     }

}
void MatrixWidget::LoadData()
{
  QFile file("/home/alice/catkin_ws/src/agree_gui/resources/Punti_tappetino.csv");
 // QFile file("/home/alice/Desktop/Punti_tappetino2.csv");
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



      if(x<max_x && y<max_y) {
        Data[x][y].value = value; // e fintanto che scorro il file vado a riempire nelle posizioni che seleziono mentre leggo il file quello che trovo nella 3 colonna
        Data[x][y].isSelected = false;
        if (Data[x][y].value ==0)
          Data[x][y].DrawColor = Qt::lightGray;
       else {
          Data[x][y].DrawColor = Qt::green;
          Data[1][3].DrawColor = Qt::black;
        }

      }
      else
       qDebug()<< "x or y bigger than matrix!";
      }

  }
   file.close();
}


QVector<QPoint>position() {
  return position();
}
