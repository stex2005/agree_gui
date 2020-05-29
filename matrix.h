#ifndef MATRIX_H
#define MATRIX_H

#include <QDialog>

namespace Ui {
class matrix;
}

class matrix : public QDialog
{
  Q_OBJECT

public:
  explicit matrix(QWidget *parent = nullptr);
  ~matrix();

private:
  Ui::matrix *ui;
};

#endif // MATRIX_H
