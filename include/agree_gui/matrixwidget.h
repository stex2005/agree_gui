#ifndef MATRIXWIDGET_H
#define MATRIXWIDGET_H

#include <QWidget>


struct DataPoint {
    int x;
    int y;
    bool value;
    QColor DrawColor; // we change this from selected / not selected.
    bool isSelected;
};

const int max_x = 15;
const int max_y = 22;

class MatrixWidget : public QWidget
{
  Q_OBJECT
  DataPoint Data[max_x][max_y];  /// this is where we want to load the data to
public:
  explicit MatrixWidget(QWidget *parent = nullptr);




signals:

public slots:
  void LoadData();


  // QWidget interface
protected:
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void paintEvent(QPaintEvent *event) override;
};

#endif // MATRIXWIDGET_H
