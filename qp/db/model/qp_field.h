#ifndef QP_FIELD_H
#define QP_FIELD_H

#include <QSqlField>

class QSqlField;
class QSqlFieldPrivate;

class QpSqlField : public QSqlField
{

public:

    enum FLD_TYPE
    {
        FLD_BASED=0,
        FLD_RELATIOB,
        FLD_CALC
    };

    explicit QpSqlField(const QpSqlField::FLD_TYPE &type,
                      const QString& fieldName = QString());

    QpSqlField& operator=(const QSqlField& other);

    friend class QSqlField;

signals:
    
public slots:

private:


    FLD_TYPE type;

    
};

#endif // QP_FIELD_H
