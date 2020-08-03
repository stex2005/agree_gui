#include "../include/agree_gui/matrixwidget.h"
#include "../include/agree_gui/login.h"


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
  /**********************       DICHIARO NODO                           *********************/
    ros::NodeHandle n;

  /**********************       CREO TOPIC                          *********************/
  status_publisher = n.advertise<std_msgs::Int8>("/gui/status", 1000);
   command_subscriber = n.subscribe("/gui/command", 1000, &MatrixWidget::callback_matrix, this);

}
void MatrixWidget::callback_matrix(const std_msgs::Int8 msg_command_matrix) {
 //  ros::NodeHandle n;
   dati::command = msg_command_matrix.data;
    if((dati::command_old) != (dati::command)) {
      dati::command_old=dati::command;
      ROS_INFO("I heard: %d MATRIX WIDGET", dati::command);
//      if(dati::command_old == 8) {
//qDebug()<< "callback_matrix, command_old 8";
//        n.getParam("/point1/mat_coordinates", point1);
//        n.getParam("/point2/mat_coordinates", point2);
//        n.getParam ("/point3/mat_coordinates", point3);
//        dati::status1 = 8;

//            std_msgs::Int8 msg;
//            msg.data = dati::status1;
//            ROS_INFO ("%d", msg.data);
//            status_publisher.publish(msg);

//      }
//      if(dati::command_old == 9) {
//        n.setParam("/point1/mat_coordinates", point1);
//        n.setParam("/point2/mat_coordinates", point2);
//        n.setParam("/point3/mat_coordinates", point3);
//      }
    }

}
QVector<QPoint> MatrixWidget::getPosition() const
{
  return position;
}
void MatrixWidget::mousePressEvent(QMouseEvent *event)
{ ros::NodeHandle n;
  QPoint p= event->pos(); //dove clicco

  int xindex = p.x()/ bw;
  int yindex = p.y()/ bh;
  qDebug() <<yindex +1 <<" "<< xindex +1;
  //get the data point (check se ind non è fuori dalla griglia)
  DataPoint &dp = Data[yindex+1][xindex +1];

  //zero non selezionabile
  if(dp.value ==0 || dp.DrawColor==Qt::black ) return;
  if(dp.isSelected == false)
  {
     if(selCount>2) return;
     dp.DrawColor = Qt::blue;
     dp.isSelected = true;
     position.append(QPoint(yindex+1,xindex+1));
     auto i1 = position.indexOf(QPoint(yindex+1,xindex+1));
if(std::count(point1.begin(), point1.end(), zero_point1)) {
  point1 = {(yindex+1),(xindex+1)};

}
 qDebug()<<point1;
 if (std::count(point2.begin(), point2.end(), zero_point1)) {
   point2 = {(yindex+1),(xindex+1)};

}
  qDebug()<<point2;
 if (std::count(point2.begin(), point2.end(), zero_point1)) {
 point3 = {(yindex+1),(xindex+1)};

}
  qDebug()<< point3;
//     dati::status1 = 9;

//         std_msgs::Int8 msg;
//         msg.data = dati::status1;
//         ROS_INFO ("%d", msg.data);
//         status_publisher.publish(msg);
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
     // now we loop and drw the boxes, non usiamo 0,0 perchè i dati partono dalla posizione 1

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
{ QFile file("/home/alice/Desktop/Punti_pad.CSV");
 // QFile file("/home/alice/catkin_ws/src/agree_gui/resources/Punti_tappetino.csv");
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

        else{
          Data[x][y].DrawColor = Qt::green;
          Data[14][19].DrawColor = Qt::black;

        }

      }
      else
       qDebug()<< "x or y bigger than matrix!";
      }

  }
   file.close();

}

//void MatrixWidget::getpos(){
//  if (selCount==3)
//  qDebug()<<position;

//}
