#ifndef WORKPANEL_H
#define WORKPANEL_H

#include <QDialog>

namespace Ui {
class WorkPanel;
}

class WorkPanel : public QDialog
{
    Q_OBJECT

public:
    explicit WorkPanel(QWidget *parent = 0);
    ~WorkPanel();

private:
    Ui::WorkPanel *ui;
};

#endif // WORKPANEL_H
