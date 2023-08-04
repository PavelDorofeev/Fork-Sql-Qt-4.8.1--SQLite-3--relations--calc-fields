#ifndef PBLFIELD_H
#define PBLFIELD_H

#include <QSqlField>

class QSqlField;
class QSqlFieldPrivate;

class PblSqlField : public QSqlField
{

public:

    enum FLD_TYPE
    {
        FLD_BASED=0,
        FLD_RELATIOB,
        FLD_CALC
    };

    explicit PblSqlField(const PblSqlField::FLD_TYPE &type,
                      const QString& fieldName = QString());

    PblSqlField& operator=(const QSqlField& other);

    friend class QSqlField;

signals:
    
public slots:

private:


    FLD_TYPE type;

    
};

#endif // PBLFIELD_H
