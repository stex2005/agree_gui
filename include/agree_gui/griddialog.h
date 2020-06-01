#ifndef GRIDDIALOG_H
#define GRIDDIALOG_H

#include <QDialog>
#include "matrixwidget.h"


namespace Ui {
class GridDialog;
}

class GridDialog : public QDialog
{
  Q_OBJECT

public:
  explicit GridDialog(QWidget *parent = nullptr);
  ~GridDialog();

private:
  Ui::GridDialog *ui;
};

#endif // GRIDDIALOG_H
