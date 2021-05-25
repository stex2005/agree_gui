#include "../include/agree_gui/matrixwidget.h"
#include "../include/agree_gui/login.h"
#include "../include/agree_gui/fsm_gui_define.h"


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
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <MATio/MATio.hpp>




int16_t dati::command_matrix, dati::command_old_matrix=1;
bool dati::selcount_mat=0;

MatrixXd openData(string fileToOpen);

MatrixWidget::MatrixWidget(QWidget *parent) : QWidget(parent)
{ if(dati::command_old_matrix==SC1_WORKSPACE_ON){
    LoadData();
    qDebug()<<"dati caricati";
  }
  /**********************       DICHIARO NODO                           *********************/
  ros::NodeHandle n;

  /**********************       CREO TOPIC                          *********************/
  status_publisher = n.advertise<std_msgs::Int16>("/gui/status", 1000);
  command_subscriber = n.subscribe("/gui/command", 1000, &MatrixWidget::callback_matrix, this);

}
/**********************       FUNZIONE DI CALLBACK                    *********************/
void MatrixWidget::callback_matrix(const agree_esmacat_pkg::agree_esmacat_command msg_command_matrix) {
  ros::NodeHandle n;
  //dati::command_old_matrix = 1;
  dati::command_matrix = msg_command_matrix.gui_mode;
  ROS_INFO("I heard: %d MATRIX WIDGET, %d %d", dati::command_matrix, msg_command_matrix.exercise, msg_command_matrix.task);

  if((dati::command_old_matrix) != (dati::command_matrix)) {
    dati::command_old_matrix=dati::command_matrix;
    qDebug()<< "matrix";
    if(dati::command_old_matrix==SC1_WORKSPACE_ON){
      LoadData();
     // qDebug()<<"dati caricati";
    }
    if(dati::command_old_matrix == SC1_UPDATE_LED) { //SALVO PARAMETRI DA ROSPARAMETERS

      qDebug()<< "callback_matrix, command_old 8";
      //point0 = {15,3};
      n.setParam("/point0/mat_coordinates", point0);

      n.getParam("/point1/mat_coordinates", point1);
      n.getParam("/point2/mat_coordinates", point2);
      n.getParam ("/point3/mat_coordinates", point3);

      qDebug()<< point1;
      qDebug()<< point2;
      qDebug()<<point3;
      qDebug()<<selCount;
      // qui devo ricolorare i punti




      //if(!(point1.at(0)==0 && point1.at(1)==0) && ) {

      //}


      dati::status1 = SC1_UPDATE_LED;
      //?
      std_msgs::Int16 msg;
      msg.data = dati::status1;
      ROS_INFO ("%d", msg.data);
      status_publisher.publish(msg);

    }
    if(dati::command_old_matrix == SC1_SELECT_FINISH) {
      if(selCount==1)
      {
        Data[point1.at(1)][point1.at(0)].DrawColor = Qt::red;
        qDebug()<< "cisiamoooo";

      }
      else if (selCount==2) {
        Data[point1.at(1)][point1.at(0)].DrawColor = Qt::red;
        Data[point2.at(1)][point2.at(0)].DrawColor = Qt::red;
        qDebug()<< "cisiamoooo2";
      }
      else if (selCount ==3) {
        Data[point1.at(1)][point1.at(0)].DrawColor = Qt::red;
        Data[point2.at(1)][point2.at(0)].DrawColor = Qt::red;
        Data[point3.at(1)][point3.at(0)].DrawColor = Qt::red;
        dati::selcount_mat=1;

        qDebug()<< "cisiamoooo3";
        selCount=0;

      }
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
  if(dati::command_old_matrix == SC1_SELECT_FINISH){
    QPoint p= event->pos(); //dove clicco

    int xindex = p.x()/ bw;
    int yindex = p.y()/ bh;
    qDebug() <<  yindex +1 <<" "<< xindex +1;
    cout << "X "<<15- yindex <<" "<< "Y" << xindex+1 <<endl;
    //get the data point (check se ind non è fuori dalla griglia)
    DataPoint &dp = Data[15-(yindex)][xindex+1 ];

    //MANDO COORDINATE DEL PUNTO DI REST
    point0 = {15,4};
    n.setParam("/point0/mat_coordinates", point0);
    Data[4][15].DrawColor=Qt::black;
    //zero non selezionabile
    if(dp.value ==0 || dp.DrawColor==Qt::black ) return;
    if(dp.isSelected == false)
    {
      if(selCount>2) return;
      dp.DrawColor = Qt::red;
      dp.isSelected = true;
      position.append(QPoint(xindex+1,15-yindex));
      // auto i1 = position.indexOf(QPoint(xindex+1,15-yindex));
      //   if(dati::command_old == 9) {
      if(std::count(point1.begin(), point1.end(), zero_point1)) {
        point1 = {(xindex+1),(15-yindex)};
        point1x = point1.at(0);
        point1y = point1.at(1);
        n.setParam("/point1/mat_coordinates", point1);
        n.setParam("matlab/point1/x", point1x);
        n.setParam("matlab/point1/y", point1y);

        qDebug()<< "riempio point1";
        qDebug()<< point1;
        dati::status1 = SC1_SELECTED;
        std_msgs::Int16 msg;
        msg.data = dati::status1;
        ROS_INFO ("%d", msg.data);
        status_publisher.publish(msg);

      }

      else if (std::count(point2.begin(), point2.end(), zero_point2)) {
        point2 = {(xindex+1),(15-yindex)};
        point2x = point2.at(0);
        point2y = point2.at(1);

        n.setParam("/point2/mat_coordinates", point2);
        n.setParam("matlab/point2/x", point2x);
        n.setParam("matlab/point2/y", point2y);

        qDebug()<< "riempio point2";
        qDebug()<< point2;
        dati::status1 = SC1_SELECTED;
        std_msgs::Int16 msg;
        msg.data = dati::status1;
        ROS_INFO ("%d", msg.data);
        status_publisher.publish(msg);

      }

      else if (std::count(point3.begin(), point3.end(), zero_point3)) {
        point3 = {(xindex+1),(15-yindex)};
        point3x = point3.at(0);
        point3y = point3.at(1);
        n.setParam("/point3/mat_coordinates", point3);
        qDebug()<< "riempio point3";
        qDebug()<< point3;
        dati::status1 = SC1_SELECTED;
        std_msgs::Int16 msg;
        msg.data = dati::status1;
        ROS_INFO ("%d", msg.data);
        status_publisher.publish(msg);
        n.setParam("matlab/point3/x", point3x);
        n.setParam("matlab/point3/y", point3y);

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
      auto i1 = position.indexOf(QPoint((xindex+1),(15-yindex)));
      std::vector<int> deselezione;
      deselezione = {(xindex+1),(15-yindex)};
      //QPoint deletedFromVector = position[i1];
      position.remove(i1);
      if(point1 == deselezione) {
        point1 = {0,0};
        n.setParam("/point1/mat_coordinates", point1);
        dati::status1 = SC1_SELECTED;
        std_msgs::Int16 msg;
        msg.data = dati::status1;
        ROS_INFO ("%d", msg.data);
        status_publisher.publish(msg);

      }
      else if (point2 == deselezione) {
        point2 = {0,0};
        n.setParam("/point2/mat_coordinates", point2);
        dati::status1 = SC1_SELECTED;
        std_msgs::Int16 msg;
        msg.data = dati::status1;
        ROS_INFO ("%d", msg.data);
        status_publisher.publish(msg);
      }
      else if (point3 == deselezione){
        point3 = {0,0};
        n.setParam("/point3/mat_coordinates", point3);
        dati::status1 = SC1_SELECTED;
        std_msgs::Int16 msg;
        msg.data = dati::status1;
        ROS_INFO ("%d", msg.data);
        status_publisher.publish(msg);
      }
    }
    update(); //aggiorna la griglia


    if (selCount==3)
      qDebug()<<position;
    std::vector<int> point_min;

  }
}
void MatrixWidget::paintEvent(QPaintEvent *event)
{  cout << "sono nel paint event 1"<<std::endl;
  QPainter p(this);
  p.drawRect(0,0, width()-1 , height() -1  );
  //-1
  cout << "sono nel paint event"<<std::endl;

  // size of area we have. w = width , h = height , we take 2 pixles for border
  int w = width()-2;
  int h = height()-2 ;
  //tiro fuori quanto dev essere grande ciascuna cella (divido la dimensione per il numero di celle che voglio avere
  bw = w / max_y; // sono le mie colonne
  bh = h / max_x; // sono le mie righe
  // now we loop and drw the boxes, non usiamo 0,0 perchè i dati partono dalla posizione 1

  for (int xi = 0; xi < max_x-1; ++xi) {
     cout << "sono nel I for del paint event"<<std::endl;
    // for (int xi =14; xi >=1; --xi) {
    for (int yi = 0; yi < max_y -1; ++yi) {
      cout << "sono nel II for del paint event"<<std::endl;
      // int new_x= Y-xi;
      p.setBrush(QBrush (Data[Y-xi][yi+1].DrawColor));
      QRect cellRect(yi*bw,xi*bh, bw,bh);
      p.drawRect( cellRect )  ;
      //    p.drawText(cellRect, QString::number(xi + 1) + "," + QString::number(yi+1) ); // the +1 aswe dont want to use first at 0,0
    }
  }



}
void MatrixWidget::LoadData(){  
  cout <<  "Enter Load" << endl;
  qDebug()<<dati::lato;
   MatrixXd matrix_test;
   MatrixXd matrix_test_y;
   MatrixXd matrix_test_en;

  if(dati::lato=="1"){
    cout <<  "Enter Load right" << endl;

     Eigen::MatioFile file_x_right("/home/alice/catkin_ws/data/right_workspace_x.mat");
     const std::vector<std::string> read_x_right {"workspace_x"};


       file_x_right.read_mat("workspace_x", matrix_test);
    //   std::cout<< "destro_x" << std::endl << "workspace_x" << std::endl << matrix_test << std::endl;


       Eigen::MatioFile file_y_right("/home/alice/catkin_ws/data/right_workspace_y.mat");
       const std::vector<std::string> read_y_right {"workspace_y"};


         file_y_right.read_mat("workspace_y", matrix_test_y);
  //       std::cout<< "destro y" << std::endl << "workspace_y" << std::endl << matrix_test_y << std::endl;


         Eigen::MatioFile file_en_right("/home/alice/catkin_ws/data/right_workspace_enabled.mat");
  //       const std::vector<std::string> read_en_right {"workspace_enabled"};


           file_en_right.read_mat("workspace_enabled", matrix_test_en);
  //         std::cout<< " destro en" << std::endl << "workspace_enabled" << std::endl << matrix_test_en << std::endl;




//     MatrixXd matrix;


//   // matrix_test = openData("/home/alice/catkin_ws/src/agree_gui/mat/point_boolean_right.CSV");
//  //  cout <<  matrix_test(0,0)  << " " <<  matrix_test(0,1)  << " " <<  matrix_test(0,2)  << endl;
   for(int i= 1; i<451;i++){

      int x= matrix_test_y(i);
      int y = matrix_test(i);

//    }

//    int  y= matrix_test_y(i,0);
  // cout <<  "ho assegnato righe e colonne"  << endl;
     if(matrix_test_en(i)){

       Data[x][y].DrawColor= Qt::green;

       Data[x][y].value=1;
       cout <<  "VERDE"  << endl;
     }
      else if (!matrix_test_en(i)) {
        Data[x][y].DrawColor= Qt::lightGray;
        Data[x][y].value=0;
       cout <<  "GRIGIO"  << endl;

      }
    //  cout << "sono fuori dall'else if del ciclo for"<<std::endl;
    } //FOR
 //    cout << "sono fuori dal ciclo for"<<std::endl;
  } //DESTRO
 //  cout << "sono fuori dal destro"<<std::endl;
  qDebug()<<Data[13][1].value;
  if(dati::lato== "0") {
  //  cout <<  "Enter Load left" << endl;

    Eigen::MatioFile file_x_left("/home/alice/catkin_ws/data/left_workspace_x.mat");
    const std::vector<std::string> read_x_left{"workspace_x"};


      file_x_left.read_mat("workspace_x", matrix_test);
      std::cout<< "sinistro x" << std::endl << "workspace_x" << std::endl << matrix_test << std::endl;


      Eigen::MatioFile file_y_left("/home/alice/catkin_ws/data/left_workspace_y.mat");
      const std::vector<std::string> read_y_left {"workspace_y"};


        file_y_left.read_mat("workspace_y", matrix_test_y);
        std::cout<< "sinistro y" << std::endl << "workspace_y" << std::endl << matrix_test_y << std::endl;


        Eigen::MatioFile file_en_left("/home/alice/catkin_ws/data/left_workspace_enabled.mat");
        const std::vector<std::string> read_en_left {"workspace_enabled"};


          file_en_left.read_mat("workspace_enabled", matrix_test_en);
          std::cout<< "sinistro en" << std::endl << "workspace_enabled" << std::endl << matrix_test_en << std::endl;
      //              std::cout<< "sinistro en 0 " << std::endl << "workspace_enabled 0" << std::endl << matrix_test_en(0) << std::endl;

   // matrix_test = openData("/home/alice/catkin_ws/src/agree_gui/mat/point_boolean_left.CSV");
   // cout <<  matrix_test(0,0)  << " " <<  matrix_test(0,1)  << " " <<  matrix_test(0,2)  << endl;

//      VectorXd x;
//      x= matrix_test;
//      cout<<"x"<< std::endl << x <<std::endl;

//      int  y= matrix_test_y(i,0);
//      cout <<  "ho assegnato righe e colonne"  << endl;
//      if(matrix_test_en(i,0)){

//        Data[x][y].DrawColor= Qt::green;
//        Data[4][15].DrawColor = Qt::black;
//        Data[x][y].value=1;
//        cout <<  "VERDE"  << endl;
//      }
//      else if (!matrix_test_en(i,0)) {
//        Data[x][y].DrawColor= Qt::lightGray;
//        Data[x][y].value=0;
//        cout <<  "GRIGIO"  << endl;

//      }

//    } //FOR
  } // SINISTRO
 //  cout << "sono fuori fuori dal destro"<<std::endl;
} //LOAD DATA




// FUNCTIONS READ CSV FILE

MatrixXd openData(string fileToOpen)

{


  // the inspiration for creating this function was drawn from here (I did NOT copy and paste the code)

  // https://stackoverflow.com/questions/34247057/how-to-read-csv-file-and-assign-to-eigen-matrix


  // the input is the file: "fileToOpen.csv":

  // a,b,c

  // d,e,f

  // This function converts input file data into the Eigen matrix format




  // the matrix entries are stored in this variable row-wise. For example if we have the matrix:

  // M=[a b c

  //    d e f]

  // the entries are stored as matrixEntries=[a,b,c,d,e,f], that is the variable "matrixEntries" is a row vector

  // later on, this vector is mapped into the Eigen matrix format


  cout << "INFUNCTION" << endl;

  vector<double> matrixEntries;


  cout << "VECTOR CREATED" << endl;


  // in this object we store the data from the matrix

  ifstream matrixDataFile(fileToOpen);

  cout << "OPEN STREAM" << endl;


  // this variable is used to store the row of the matrix that contains commas

  string matrixRowString;

  cout << "CREATE 1ST STRING" << endl;


  // this variable is used to store the matrix entry;

  string matrixEntry;

  cout << "CREATED 2ND STRING" << endl;


  // this variable is used to track the number of rows

  int matrixRowNumber = 0;

  cout << "mCREATED ROW NUMBER" << endl;



  while (getline(matrixDataFile, matrixRowString)) // here we read a row by row of matrixDataFile and store every line into the string variable matrixRowString

  {

    stringstream matrixRowStringStream(matrixRowString); //convert matrixRowString that is a string to a stream variable.


    while (getline(matrixRowStringStream, matrixEntry, ',')) // here we read pieces of the stream matrixRowStringStream until every comma, and store the resulting character into the matrixEntry

    {

      matrixEntries.push_back(stod(matrixEntry));   //here we convert the string to double and fill in the row vector storing all the matrix entries

    }

    matrixRowNumber++; //update the column numbers

  }


  cout << "ROW NUMBER" << matrixRowNumber << endl;

  cout << "OUT WHILE" << endl;


  // here we convet the vector variable into the matrix and return the resulting object,

  // note that matrixEntries.data() is the pointer to the first memory location at which the entries of the vector matrixEntries are stored;

  return Map<Matrix<double, Dynamic, Dynamic, RowMajor>>(matrixEntries.data(), matrixRowNumber, matrixEntries.size() / matrixRowNumber);


}

