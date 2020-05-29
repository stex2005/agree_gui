#ifndef MATRIX_H
#define MATRIX_H

#include <QDialog>
#include <QStandardItemModel>
#include <QTableView>

namespace Ui {
class matrix;
}

class matrix : public QDialog
{
  Q_OBJECT

public:
  explicit matrix(QWidget *parent = nullptr);
  QStandardItemModel *csvModel;
  ~matrix();

private:
  Ui::matrix *ui;
 // QStandardItemModel *csvModel;
};

#endif // MATRIX_H
