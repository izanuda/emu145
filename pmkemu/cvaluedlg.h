#ifndef CVALUEDLG_H
#define CVALUEDLG_H

#include <QDialog>

namespace Ui {
class cValueDlg;
}

class cValueDlg : public QDialog
{
    Q_OBJECT

public:
    explicit cValueDlg(QWidget *parent = 0);
    ~cValueDlg();

    void setReg(QString str, unsigned char val);


    int changed;
    int newval;

private slots:
    void on_cancelBtn_clicked();

    void on_okBtn_clicked();

private:
    Ui::cValueDlg *ui;
};

#endif // CVALUEDLG_H
