#ifndef BUTTONICONAUTORESIZE_H
#define BUTTONICONAUTORESIZE_H

#include <QToolButton>

#include "qp/sql/dll_qp_sql_global.h"
class LIB_PREFIX_QP_SQL ButtonIconAutoResize : public QToolButton
{
    Q_OBJECT
public:
    explicit ButtonIconAutoResize(QWidget *parent = 0);

    ButtonIconAutoResize(const QString &text, QWidget *parent=0);

    ~ButtonIconAutoResize();

    QSize sizeHint() const;

private:
    void paintEvent(QPaintEvent *event);

    int pad;
    int minSize;
    int maxSize;
    QSize iconSize;
    QImage image;

signals:

public slots:

};

#endif // BUTTONICONAUTORESIZE_H
