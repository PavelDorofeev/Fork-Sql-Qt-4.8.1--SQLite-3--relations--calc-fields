#ifndef SIZEREMEMBERDLG_H
#define SIZEREMEMBERDLG_H

#include <QDialog>
#include <QSettings>
#include <QString>

#include "qp/dll_qp_global.h"

//namespace Ui {
//class SizeRememberDlg;
//}


class LIB_PREFIX_QP SizeRememberDlg : public QDialog
{
    Q_OBJECT
public:
    explicit SizeRememberDlg( QWidget *parent = 0 );

    virtual QString getReestrPrefix()const=0;
    virtual QSize getMinimumSize() const = 0;

    void init();

    //bool event( QEvent *evt);

    void resizeEvent( QResizeEvent *evt);

    //void moveEvent( QMoveEvent *evt);

//    void focusInEvent( QFocusEvent * evt);
//    void focusOutEvent( QFocusEvent * evt);

//    void enterEvent( QEvent *evt);
//    void leaveEvent( QEvent *evt);

    void mouseMoveEvent( QMouseEvent* event);
    void mousePressEvent( QMouseEvent* event);


    void closeEvent(QCloseEvent *);
    void showEvent(QShowEvent *);
    void done(int res);
    void open();
    int exec();
    QSettings reestr_settings;



signals:

    void sig_updateCursor( int );

public slots:

    //void slot_updateCursor( int tt);

private:
    //Ui::SizeRememberDlg *uiSzDlg;
    const QString reestTreeName;
    const QString reestrName;
    QString pathRect;
    QString pathPos;
    bool restoreFromReestr();
    bool saveSizeAndPosToReestr( const QSize & sz, const QPoint & pos);
    bool resizeStoreEnabled;
    QSize changedSize;
    QPoint changedPos;
    QPointF m_mousePoint;
};

#endif // SIZEREMEMBERDLG_H
