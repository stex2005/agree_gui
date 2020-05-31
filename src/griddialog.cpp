#include "../include/agree_gui/griddialog.h"
#include "ui_griddialog.h"
#include "../include/agree_gui/matrixwidget.h"

GridDialog::GridDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::GridDialog)
{
  ui->setupUi(this);
  MatrixWidget * m = new MatrixWidget (this);
     ui->verticalLayout->addWidget(m);
}

GridDialog::~GridDialog()
{
  delete ui;
}
