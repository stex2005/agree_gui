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

int8_t dati::command_matrix, dati::command_old_matrix=1;
MatrixWidget::MatrixWidget(QWidget *parent) : QWidget(parent)
{ if(dati::command_old_matrix==7){
  LoadData();
  qDebug()<<"dati caricati";
  }
  /**********************       DICHIARO NODO                           *********************/
    ros::NodeHandle n;

  /**********************       CREO TOPIC                          *********************/
  status_publisher = n.advertise<std_msgs::Int8>("/gui/status", 1000);
   command_subscriber = n.subscribe("/gui/command", 1000, &MatrixWidget::callback_matrix, this);

}
 /**********************       FUNZIONE DI CALLBACK                    *********************/
void MatrixWidget::callback_matrix(const agree_gui::agree_gui_command msg_command_matrix) {
   ros::NodeHandle n;
   //dati::command_old_matrix = 1;
   dati::command_matrix = msg_command_matrix.mode;
     ROS_INFO("I heard: %d MATRIX WIDGET, %d %d", dati::command_matrix, msg_command_matrix.exercise, msg_command_matrix.task);

    if((dati::command_old_matrix) != (dati::command_matrix)) {
      dati::command_old_matrix=dati::command_matrix;
qDebug()<< "matrix";
if(dati::command_old_matrix==7){
  LoadData();
  qDebug()<<"dati caricati";
  }
      if(dati::command_old_matrix == 8) { //SALVO PARAMETRI DA ROSPARAMETERS
qDebug()<< "callback_matrix, command_old 8";
        n.getParam("/point1/mat_coordinates", point1);
        n.getParam("/point2/mat_coordinates", point2);
        n.getParam ("/point3/mat_coordinates", point3);
        qDebug()<< point1;
        qDebug()<< point2;
        qDebug()<<point3;
        dati::status1 = 8;
//?
            std_msgs::Int8 msg;
            msg.data = dati::status1;
            ROS_INFO ("%d", msg.data);
            status_publisher.publish(msg);

      }
      if(dati::command_old_matrix == 9) {
//        n.setParam("/point1/mat_coordinates", point1);
//        n.setParam("/point2/mat_coordinates", point2);
//        n.setParam("/point3/mat_coordinates", point3);
        qDebug()<< point1;
        qDebug()<< point2;
        qDebug()<<point3;

      }
    }

}
QVector<QPoint> MatrixWidget::getPosition() const
{
  return position;
}
void MatrixWidget::mousePressEvent(QMouseEvent *event)
{ ros::NodeHandle n;
  if(dati::command_old_matrix == 9){
  QPoint p= event->pos(); //dove clicco

  int xindex = p.x()/ bw;
  int yindex = p.y()/ bh;
  qDebug() <<yindex +1 <<" "<< xindex +1;
  //get the data point (check se ind non è fuori dalla griglia)
  DataPoint &dp = Data[Y-yindex][xindex+1 ];

  //zero non selezionabile
  if(dp.value ==0 || dp.DrawColor==Qt::black ) return;
  if(dp.isSelected == false)
  {
     if(selCount>2) return;
     dp.DrawColor = Qt::blue;
     dp.isSelected = true;
     position.append(QPoint(xindex+1,16-yindex));
     auto i1 = position.indexOf(QPoint(xindex+1,16-yindex));
  //   if(dati::command_old == 9) {
if(std::count(point1.begin(), point1.end(), zero_point1)) {
  point1 = {(xindex+1),(16-yindex)};
  n.setParam("/point1/mat_coordinates", point1);
  qDebug()<< "riempio point1";
  qDebug()<< point1;
  dati::status1 = 9;
           std_msgs::Int8 msg;
           msg.data = dati::status1;
           ROS_INFO ("%d", msg.data);
           status_publisher.publish(msg);

}

else if (std::count(point2.begin(), point2.end(), zero_point2)) {
   point2 = {(xindex+1),(16-yindex)};
   n.setParam("/point2/mat_coordinates", point2);
   qDebug()<< "riempio point2";
   qDebug()<< point2;
   dati::status1 = 9;
            std_msgs::Int8 msg;
            msg.data = dati::status1;
            ROS_INFO ("%d", msg.data);
            status_publisher.publish(msg);

}

else if (std::count(point3.begin(), point3.end(), zero_point3)) {
 point3 = {(xindex+1),(16-yindex)};
 n.setParam("/point3/mat_coordinates", point3);
 qDebug()<< "riempio point3";
 qDebug()<< point3;
 dati::status1 = 9;
          std_msgs::Int8 msg;
          msg.data = dati::status1;
          ROS_INFO ("%d", msg.data);
          status_publisher.publish(msg);

}

  //   }
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
    auto i1 = position.indexOf(QPoint((xindex+1),(16-yindex)));
    std::vector<int> deselezione;
    deselezione = {(xindex+1),(16-yindex)};
    QPoint deletedFromVector = position[i1];
    position.remove(i1);
    if(point1 == deselezione) {
      point1 = {0,0};
      n.setParam("/point1/mat_coordinates", point1);
      dati::status1 = 9;
               std_msgs::Int8 msg;
               msg.data = dati::status1;
               ROS_INFO ("%d", msg.data);
               status_publisher.publish(msg);

    }
    else if (point2 == deselezione) {
      point2 = {0,0};
      n.setParam("/point2/mat_coordinates", point2);
      dati::status1 = 9;
               std_msgs::Int8 msg;
               msg.data = dati::status1;
               ROS_INFO ("%d", msg.data);
               status_publisher.publish(msg);
    }
    else if (point3 == deselezione){
      point3 = {0,0};
      n.setParam("/point3/mat_coordinates", point3);
      dati::status1 = 9;
               std_msgs::Int8 msg;
               msg.data = dati::status1;
               ROS_INFO ("%d", msg.data);
               status_publisher.publish(msg);
    }
   }
  update(); //aggiorna la griglia


if (selCount==3)
qDebug()<<position;
std::vector<int> point_min;



//// devo ordinare i punti selezionati
//if(point1[1]<point2[1] && point1[1]< point3[1]) {
//  point_min = point1;
//  if (point2[1]< point3[1]) {
//    //point1 , point2 , point 3
//    point1 = point_min;
//    point2= point2;
//    point3 = point3;
//    if(dati::command_old == 9){
//      n.setParam("point1/mat_cooridnates", point1);
//      n.setParam("point2/mat_cooridnates", point2);
//      n.setParam("point3/mat_cooridnates", point3);
//    }
//  }
//  else {
//    // point1, point3, point2
//    point1 = point_min;
//    point2 = point3;
//    point3 = point2;
//    if(dati::command_old == 9){
//      n.setParam("point1/mat_cooridnates", point1);
//      n.setParam("point2/mat_cooridnates", point2);
//      n.setParam("point3/mat_cooridnates", point3);
//    }
//  }

//}
//else if (point2[1]< point1[1] && point2[1]< point3[2]) {
//  point_min = point2;
//  if (point1[1]< point3[1]){
//    // point2, point1, point3
//    point1 = point_min;
//    point2 = point1;
//    point3 = point3;
//    if(dati::command_old == 9){
//      n.setParam("point1/mat_cooridnates", point1);
//      n.setParam("point2/mat_cooridnates", point2);
//      n.setParam("point3/mat_cooridnates", point3);
//    }

//  }
//  else if (point3[1]< point1[1]){
//    // point2, point3, point1
//    point1 = point_min;
//    point2 = point3;
//    point3 = point1;
//    if(dati::command_old == 9){
//      n.setParam("point1/mat_cooridnates", point1);
//      n.setParam("point2/mat_cooridnates", point2);
//      n.setParam("point3/mat_cooridnates", point3);
//    }
//  }

//}
//else if (point3[1]< point1[1] && point3[1]< point2[1]) {
//  point_min = point3;
//  if(point1[1]<point2[1]) {
//     point1 = point_min;
//    point2 = point1;
//    point3 = point2;
//    if(dati::command_old == 9){
//      n.setParam("point1/mat_cooridnates", point1);
//      n.setParam("point2/mat_cooridnates", point2);
//      n.setParam("point3/mat_cooridnates", point3);
//    }
//  }
//  else if (point2[1]< point1[1]) {
//    point1 = point_min;
//    point2 = point2;
//    point3 = point1;
//    if(dati::command_old == 9){
//      n.setParam("point1/mat_cooridnates", point1);
//      n.setParam("point2/mat_cooridnates", point2);
//      n.setParam("point3/mat_cooridnates", point3);
//    }

//  }
//}

//   QFile file_1("/home/alice/catkin_ws/src/agree_gui/resources/posizioni.txt");
//   file_1.open(QIODevice::WriteOnly);
//   QDataStream out(&file_1);
//   out << position ;
//   file_1.close();


  }
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
// for (int xi =14; xi >=1; --xi) {
        for (int yi = 0; yi < max_y -1; ++yi) {
          int new_x= Y-xi;
                  p.setBrush(QBrush (Data[new_x][yi+1].DrawColor));
           QRect cellRect(yi*bw,xi*bh, bw,bh);
             p.drawRect( cellRect )  ;
        //    p.drawText(cellRect, QString::number(xi + 1) + "," + QString::number(yi+1) ); // the +1 aswe dont want to use first at 0,0
         }
     }

}
void MatrixWidget::LoadData()
{ qDebug()<< dati::lato;
  // LATO DESTRO
if(dati::lato=="1"){
    qDebug() <<"matrice lato destro";
     QFile file("/home/alice/Desktop/Point_boolean_rigth.CSV");
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
         int x = list.at(1).toInt(); //mi riferisco alla prima colonna
         int y = list.at(0).toInt(); // alla seconda
         bool value = list.at(2).toInt(); // ai valori presenti nella 3 (bool)



         if(x<max_x && y<max_y) {
           Data[x][y].value = value; // e fintanto che scorro il file vado a riempire nelle posizioni che seleziono mentre leggo il file quello che trovo nella 3 colonna
           Data[x][y].isSelected = false;
           if (Data[x][y].value ==0)
             Data[x][y].DrawColor = Qt::lightGray;

           else{
             Data[x][y].DrawColor = Qt::green;
             Data[1][31].DrawColor = Qt::black;

           }

         }
         else
          qDebug()<< "x or y bigger than matrix!";
         }

     }
      file.close();

}
  //LATO SINISTRO
  else if(dati::lato=="0")
  { QFile file("/home/alice/Desktop/Point_boolean_left.CSV");
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
        int x = list.at(1).toInt(); //mi riferisco alla prima colonna
        int y = list.at(0).toInt(); // alla seconda
        bool value = list.at(2).toInt(); // ai valori presenti nella 3 (bool)



        if(x<max_x && y<max_y) {
          Data[x][y].value = value; // e fintanto che scorro il file vado a riempire nelle posizioni che seleziono mentre leggo il file quello che trovo nella 3 colonna
          Data[x][y].isSelected = false;
          if (Data[x][y].value ==0)
            Data[x][y].DrawColor = Qt::lightGray;

          else{
            Data[x][y].DrawColor = Qt::green;
            Data[1][1].DrawColor = Qt::black;

          }

        }
        else
         qDebug()<< "x or y bigger than matrix!";
        }

    }
     file.close();}
}

