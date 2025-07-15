#ifndef SIZEREMEMBERDLG2_H
#define SIZEREMEMBERDLG2_H

#include <QDialog>
#include "sizerememberdlg.h"

namespace Ui {
class SizeRememberDlg2;
}


#include "qp/gui/dll_qp_gui_global.h"

class LIB_PREFIX_QP_GUI SizeRememberDlg2 : public SizeRememberDlg
{
    Q_OBJECT
    
public:
    explicit SizeRememberDlg2(QWidget *parent = 0);
    ~SizeRememberDlg2();


    virtual QString getReestrPrefix() const;
    QSize getMinimumSize() const;

    
private:
    Ui::SizeRememberDlg2 *ui;
};

#endif // SIZEREMEMBERDLG2_H
