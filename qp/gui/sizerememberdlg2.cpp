#include "sizerememberdlg2.h"
#include "ui_sizerememberdlg2.h"

#include "qp/qp.h"
#include <QDebug>

SizeRememberDlg2::SizeRememberDlg2(QWidget *parent) :
    SizeRememberDlg(parent),
    ui(new Ui::SizeRememberDlg2)
{
    ui->setupUi(this);


}

SizeRememberDlg2::~SizeRememberDlg2()
{
    delete ui;
}


QString SizeRememberDlg2::getReestrPrefix() const
{
    return "SizeRememberDlg2";
}

QSize SizeRememberDlg2::getMinimumSize() const
{
    //qDebug() << "SizeRememberDlg2::getMinimumSize()"<<minimumSize();

    return SizeRememberDlg2::minimumSize();
}
