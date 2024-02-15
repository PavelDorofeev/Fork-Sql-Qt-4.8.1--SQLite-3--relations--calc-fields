#ifndef BUTTONICONAUTORESIZE_H
#define BUTTONICONAUTORESIZE_H

#include <QToolButton>

class ButtonIconAutoResize : public QToolButton
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
