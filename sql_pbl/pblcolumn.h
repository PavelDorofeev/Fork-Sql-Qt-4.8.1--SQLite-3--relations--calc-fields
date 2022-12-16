#ifndef PBLCOLUMN_H
#define PBLCOLUMN_H

#include <QString>

class PblColumn
{

public:
    enum COLUMN_TYPE
    {
        COLUMN_TYPE_UNKNOUWN=-1,
        COLUMN_TYPE_RELATION_TEXT = 1,
        COLUMN_TYPE_RELATION_ID = 2,
        COLUMN_TYPE_CALCULATION = 3
    };

    PblColumn();

    PblColumn(
            COLUMN_TYPE type,
            const QString &exTableName,
            const QString &indexFieldFrom,
            const QString &fieldFrom,
            const QString &funcName,
            int origCol,
            int exCol,
            const QString fieldNameTo=QString());

    int origCol;
    int exCol;

    COLUMN_TYPE type;

    QString exTableName;
    QString exIndexFieldName;
    QString exTextFieldName; //
    QString exFuncName;
    QString renamedField_As;

    char cFormat;
    int precision;



    bool isValid();

    void setFormat(const char &format, const int &precision_)
    {
        cFormat = format;
        precision = precision_;
    }

    void setAlignment(Qt::Alignment align = Qt::AlignLeft)
    {
        alignment = align;
    }
    Qt::Alignment alignment;

private:


};


#endif // PBLCOLUMN_H
