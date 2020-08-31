#ifndef MATRIXWIDGET_H
#define MATRIXWIDGET_H

#include <QWidget>
#include <ros/ros.h>
#include <ros/network.h>
#include<std_msgs/Int8.h>
#include "agree_gui/agree_gui_command.h"



struct DataPoint {
    int x;
    int y;
    bool value;
    QColor DrawColor{Qt::gray}; // we change this from selected / not selected.
    bool isSelected;
};


const int max_x = 15;
const int max_y = 22;


class MatrixWidget : public QWidget
{
  Q_OBJECT
  DataPoint Data[max_x][max_y]; // this is where we want to load the data to
// QVector<QPoint>position;





  int bw=0;
  int bh=0;
  int selCount= 0;
public:
  explicit MatrixWidget(QWidget *parent = nullptr);
 QVector<QPoint>position;


 /***************          DEFINISCO ROS PARAMETERS          ******************/
 std::vector<int> point1;
  int zero_point1 = 0;
 std::vector<int> point2;
  int zero_point2 = 0;
 std::vector<int> point3;
  int zero_point3 = 0;
std::vector<int> points;


 QVector<QPoint> getPosition() const;

signals:

public slots:
 void LoadData();

 void callback_matrix(const agree_gui::agree_gui_command msg_command_matrix);
 // void getpos();



  // QWidget interface
protected:
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void paintEvent(QPaintEvent *event) override;

private:
  ros::Publisher status_publisher;
   ros::Subscriber command_subscriber;
};

#endif // MATRIXWIDGET_H
