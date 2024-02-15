#ifndef DB_H
#define DB_H

#include <QString>
#include <QFont>
#include <QColor>
#include <QDebug>
#include <QModelIndex>

class QpSqlTableModel;


namespace qp
{


namespace db
{
// ---------------------------------------------------------------------
static int test( const QpSqlTableModel &mdl, const QString &fldName)
{
    return 0;
}

int indexOf( const QpSqlTableModel * mdl, const QString &fldName );

enum SOME_FIELDS_VAL
{
    UNDEFINED = -1 ,

    COL_UNDEFINED = UNDEFINED,
    ROW_UNDEFINED = UNDEFINED,
    INT_UNDEFINED = UNDEFINED,

    REL_UNDEFINED = 0,

    REL_EMPTY_ID  = REL_UNDEFINED,
    EMPTY_ID      = REL_UNDEFINED,
};


typedef struct CELL_NODES
{

    static const int NODE_UNDEFINED ;

    int left; // 0,1,2
    int right;
    int top;
    int bottom;

    bool visible;

    CELL_NODES( )
        :
          top( NODE_UNDEFINED ),
          bottom( NODE_UNDEFINED ),
          left( NODE_UNDEFINED ),
          right ( NODE_UNDEFINED ),
          visible( false )
    {

    }

    CELL_NODES( int num1 );

    CELL_NODES( int num1, int num2)
        :
          left( num1),
          top( num1),
          right( num2),
          bottom( num1),
          visible( true )
    {

    }

    CELL_NODES( int num1, int num2 , int line1, int line2 )
        :
          left( num1),
          top( line1),
          right( num2),
          bottom( line2),
          visible( true )
    {

    }

    bool isEmpty()
    {
        if( left == NODE_UNDEFINED ||
                top == NODE_UNDEFINED ||
                right == NODE_UNDEFINED ||
                bottom == NODE_UNDEFINED )
        {
            return true;
        }

        return false;
    }



};


typedef struct CELL_STYLE
{
public:
    Qt::Alignment align;

    QFont font;

    QColor color;

    int multipleHeight;

    CELL_STYLE()
        :
          align( Qt::AlignCenter ),
          color(QColor(Qt::gray)),
          font (QFont()),
          multipleHeight(1)
    {

    }


#ifndef QT_NO_DATASTREAM
    //inline QDataStream& operator>>(QDataStream& s, CELL_STYLE& p)
    //{
    //    s >> " align " >> p.align >> " color: " >> p.color  >> " font:" >> p.fnt;
    //    return s;
    //}

    //inline QDataStream& operator<<(QDataStream& s, const CELL_STYLE& p)
    //{
    //    s << " align ";// << p.align << " color: " << p.color  << " font:" <<p.fnt;
    //    return s;
    //}
#endif
private:
#ifndef QT_NO_DATASTREAM
    friend Q_GUI_EXPORT QDataStream &operator<<(QDataStream &, const CELL_STYLE &);
    friend Q_GUI_EXPORT QDataStream &operator>>(QDataStream &, CELL_STYLE &);
#endif

};



typedef enum FIELD_TYPE
{
    LABEL_FLD=-2,
    UNDEFINED_FLD=-1,
    UNKNOWN_VALUE = UNDEFINED_FLD
};

typedef enum SECTION_TYPE
{
    UNKNOWN_TYPE =-1,
    MODEL_TYPE =1,
    LABEL_TYPE
};

typedef struct SECTION_D
{
    qp::db::SECTION_TYPE type;
    int logicalNumber;
    QString txt;

    SECTION_D():
        logicalNumber (qp::db::UNKNOWN_VALUE),
        type ( qp::db::UNKNOWN_TYPE)
    {}

    SECTION_D( const qp::db::SECTION_TYPE &Type,
               const int &sectionNumber,
               const QString &Txt=QString())
        : type( Type ),
          logicalNumber (sectionNumber),
          txt(Txt)
    {}
};

typedef QList < QList< qp::db::SECTION_D > >  SECTIONS_TMPL;

void print_matrix( const qp::db::SECTIONS_TMPL &matrix, QString &header = QString("   print_matrix : ") );



typedef struct SECTION
{
    SECTION_TYPE type;
    QModelIndex idx;

    SECTION() :
        type(MODEL_TYPE),
        idx(QModelIndex())
    {

    }

};

enum SectionEdge { NONE, TOP, RIGHT, BOTTOM, LEFT };

typedef struct aaa
{
    int xNum;
    int line;
    SECTION_TYPE type;
    Qt::Orientation moveOrientation;
    bool handle;
    SectionEdge edge;

    int sectionNum_underCursor;

    aaa()
        :
          xNum( UNKNOWN_VALUE),
          line( UNKNOWN_VALUE),
          sectionNum_underCursor( UNKNOWN_VALUE),
          type( MODEL_TYPE),
          moveOrientation( Qt::Horizontal),
          handle ( false),
          edge( qp::db::NONE)
    {

    }
};




typedef struct CELL
{

    CELL()
        :
          line(qp::db::UNKNOWN_VALUE), xNum(qp::db::UNKNOWN_VALUE) , sectionNum (qp::db::UNKNOWN_VALUE)
    {
    }

    CELL( const int &line, const int &xNum):
        line(line),
        xNum(xNum)
    {
    }

    CELL &operator=(const CELL &other)
    {
        line = other.line;
        xNum = other.xNum;
        sectionNum = other.sectionNum;
        return *this;
    }

    int line;
    int xNum;
    int sectionNum;
};

Q_INLINE_TEMPLATE bool operator==(const CELL &p1, const CELL &p2)
{
    return p1.line == p2.line && p1.xNum == p2.xNum;
}

Q_INLINE_TEMPLATE bool operator!=(const CELL &p1, const CELL &p2)
{
    return !(p1 == p2);
}

Q_INLINE_TEMPLATE bool operator<(const CELL &p1, const CELL &p2)
{
    return p1.line < p2.line || (!(p2.line < p1.line) && p1.xNum < p2.xNum);
}

Q_INLINE_TEMPLATE bool operator>(const CELL &p1, const CELL &p2)
{
    return p2 < p1;
}

Q_INLINE_TEMPLATE bool operator<=(const CELL &p1, const CELL &p2)
{
    return !(p2 < p1);
}

Q_INLINE_TEMPLATE bool operator>=(const CELL &p1, const CELL &p2)
{
    return !(p1 < p2);
}
Q_OUTOFLINE_TEMPLATE CELL qMakePair(const int &x, const int &y)
{
    return CELL(x, y);
}

#ifndef QT_NO_DATASTREAM
inline QDataStream& operator>>(QDataStream& s, CELL& p)
{
    s >> p.line >> p.xNum;
    return s;
}

inline QDataStream& operator<<(QDataStream& s, const CELL& p)
{
    s << p.line << p.xNum;
    return s;
}
#endif


}

}

#endif // DB_H
