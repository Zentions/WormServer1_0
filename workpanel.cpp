#include "workpanel.h"
#include "ui_workpanel.h"

WorkPanel::WorkPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WorkPanel)
{
    ui->setupUi(this);
}

WorkPanel::~WorkPanel()
{
    delete ui;
}
