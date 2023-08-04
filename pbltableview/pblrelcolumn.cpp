#include "pblrelcolumn.h"
#include <QDebug>
#include <QMessageBox>


PblRelColumn::PblRelColumn()
//    /:
      //relation.col(-1)
{
    qDebug() << "ctor ExColumns";

    QMessageBox::warning( 0,
                          "Error",
                          "Call ctor PblColumn::PblColumn(), this is wrong");

}

PblRelColumn::PblRelColumn(const PblSqlRelation &Relation,
                     int exCol_)

//    /:

     //type(COLUMN_TYPE_RELATION_ID),

      //relation(Relation)


{
    //??origCol = Relation.col;

    exCol = exCol_;

    //relation = &Relation;

}

PblRelColumn PblRelColumn::operator=(const PblRelColumn &other)

{
    qDebug() << "PblColumn::operator=";

    //relation = other.relation;

    //origCol = other.origCol;

    //exCol = other.exCol;

    //type = other.type;

    //calc = other.calc;

    //renamedHeaderCol;


    return *this;

};

