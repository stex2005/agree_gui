#ifndef MATRIXWIDGET_H
#define MATRIXWIDGET_H

#include <QWidget>
#include <ros/ros.h>
#include <ros/network.h>



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



 QVector<QPoint> getPosition() const;

signals:

public slots:
 void LoadData();
 // void getpos();



  // QWidget interface
protected:
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void paintEvent(QPaintEvent *event) override;

private:
  ros::Publisher status_publisher;
};

#endif // MATRIXWIDGET_H
