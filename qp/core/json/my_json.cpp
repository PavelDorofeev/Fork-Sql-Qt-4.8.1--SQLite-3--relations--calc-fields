#include <QDateTime>
#include <QStringList>
#include "my_json.h"
#include "orderedobj.h"
#include "pair.h"
#include <QDebug>
#include <QLocale>




namespace QtJson
{
//static const QChar ch_n = QChar(0x0A); // "\n";
//static const QChar ch_r = QChar(0x0D); // "\r";
static const QByteArray ch_rn = QByteArray::fromHex("0D0A"); // "\n";
static const QByteArray ch_n = QByteArray::fromHex("0A"); // "\n";
static const QByteArray ch_r = QByteArray::fromHex("0D"); // "\r";
static const QByteArray ch_quote = QByteArray::fromHex("22"); // "\"";
static const QByteArray ch_t = QByteArray::fromHex("09"); // "\t";
static const QByteArray ch_slash = QByteArray::fromHex("2F"); // "/";
static const QByteArray ch_back_slash = QByteArray::fromHex("5C"); // "\\";

static const QByteArray ch2_rn = QByteArray::fromHex("5C725C6E"); //
static const QByteArray ch2_r = QByteArray::fromHex("5C72"); // "\\\r";
static const QByteArray ch2_quote = QByteArray::fromHex("5C22"); // "\\\"";
static const QByteArray ch2_t = QByteArray::fromHex("5C74"); // "\\\t";
static const QByteArray ch2_slash = QByteArray::fromHex("5C2F"); // "\\/";
static const QByteArray ch2_back_slash = QByteArray::fromHex("5C5C"); // "\\\\";

static QString dateFormat, dateTimeFormat;
static bool prettySerialize = true;


static QByteArray join(const QList<QByteArray> &list, const QByteArray &sep);
static QVariant parseValue(const QString &json, int &index, bool &parse_ok);
static QVariant parseObject(const QString &json, int &index, bool &parse_ok);
static QVariant parseArray(const QString &json, int &index, bool &parse_ok);
static QVariant parseString(const QString &json, int &index, bool &parse_ok);
static QVariant parseNumber(const QString &json, int &index);
static int lastIndexOfNumber(const QString &json, int index);
static void eatWhitespace(const QString &json, int &index);
static int lookAhead(const QString &json, int index);
static int nextToken(const QString &json, int &index);

//template<typename T>
QByteArray serializeMap(const QVariantMap &map, bool *success, JSON_OPTIONS options,int level)
{
    QByteArray tabs;
    QByteArray tabsFields;

    bool pretty=false;
    if ( options & JSON_PRETTY_PRINT )
        pretty=true;

    if ( pretty && !map.isEmpty())
    {
        tabs = margin( level);

        tabsFields = margin( level +1 );
    }


    QByteArray ba = "{" + (pretty ? ch_rn : "");

    QList<QByteArray> pairs;

    for (QVariantMap::Iterator it = map.begin(), itend = map.end(); it != itend; ++it)
    {
        //bool otherSuccess = true;
        QByteArray serializedValue = serialize1( it.value(), success, options, level);

        if (serializedValue.isNull())
        {
            if( success != 0)
                *success = false;
            break;
        }
        pairs << tabsFields + sanitizeString( it.key()).toUtf8() + ":" + serializedValue;
    }

    ba += join( pairs , "," + (pretty ? ch_rn : "") ) + (pretty ? ch_rn : "");
    ba += (pretty ? tabs : "") + "}";

    //qDebug() << str;

    //level--;

    return ba;
}

QByteArray serializeList(const QVariantList &lst, bool *success, JSON_OPTIONS options ,int level )
{
    QList<QByteArray> values;

    QByteArray ba;

    QByteArray tabs;

    bool pretty=false;
    if ( options & JSON_PRETTY_PRINT )
        pretty=true;


    QByteArray tabsFields;

    if ( pretty && !lst.isEmpty())
    {
        tabs = margin( level);
        tabsFields = margin( level +1 );
    }

    QByteArray serializedValue;

    Q_FOREACH( const QVariant& var, lst)
    {

        serializedValue = serialize1( var, success, options, level);

        if ( serializedValue.isNull() )
        {
            if( success !=0 )
                *success = false;
            break;
        }
        values << (pretty ? tabs + ch_t : "") + serializedValue;

    }

    if ( ! values.isEmpty())
    {
        //ba = ch_rn + tabs + "[" + ch_rn + join( values, "," + ch_rn ) + ch_rn + tabs +  "]";
        ba = (pretty ? tabs : "") + "[" + (pretty ? ch_rn : "") + join( values, "," + (pretty ? ch_rn : "") ) + (pretty ? ch_rn : "") + tabs +  "]";
    }
    else
    {
        ba = "[]";
    }

    return ba;
}

QByteArray margin( int ii)
{
    QByteArray tabs;

    for ( int ll=1; ll < ii; ll++)
    {
        tabs += "\t";
    }
    return tabs;
}

QString makeStringPretty(const QString &str, JSON_OPTIONS options)
{

    bool ok;
    QVariant jj = QtJson::parse1( str , ok);

    QString prettyJson  = QtJson::serialize1( jj , &ok , options);

    return prettyJson;


}

void insert(QVariant &v, const QString &key, const QVariant &value);
void append(QVariant &v, const QVariant &value);

template<typename T>
void cloneMap(QVariant &json, const T &map)
{
    for (typename T::const_iterator it = map.begin(), itend = map.end(); it != itend; ++it) {
        insert(json, it.key(), (*it));
    }
}

template<typename T>
void cloneList(QVariant &json, const T &list)
{
    for (typename T::const_iterator it = list.begin(), itend = list.end(); it != itend; ++it)
    {
        append(json, (*it));
    }
}

/**
            * parse
            */
QVariant parse1(const QString &json)
{
    bool parse_ok = true;
    return parse1(json, parse_ok);
}

/**
            * parse
            */
QVariant parse1(const QString &json, bool &parse_ok)
{
    parse_ok = true;

    // Return an empty QVariant if the JSON data is either null or empty

    if (!json.isNull() || !json.isEmpty())
    {
        QString data = json;
        // We'll start from index 0
        int index = 0;

        // Parse the first value
        QVariant value = parseValue( data, index, parse_ok);

        // Return the parsed value
        return value;
    }
    else
    {
        // Return the empty QVariant
        return QVariant();
    }
}

/**
            * clone
            */
QVariant clone(const QVariant &data)
{
    QVariant v;

    if (data.type() == QVariant::Map)
    {
        cloneMap(v, data.toMap());
    }
    else if (data.type() == QVariant::Hash)
    {
        cloneMap(v, data.toHash());
    }
    else if (data.type() == QVariant::List)
    {
        cloneList(v, data.toList());
    }
    else if (data.type() == QVariant::StringList)
    {
        cloneList(v, data.toStringList());
    }
    else
    {
        v = QVariant(data);
    }

    return v;
}

/**
            * insert value (map case)
            */
void insert(QVariant &v, const QString &key, const QVariant &value)
{
    if (!v.canConvert<QVariantMap>())
        v = QVariantMap();

    QVariantMap *p = (QVariantMap *)v.data();
    p->insert(key, clone(value));
}

/**
            * append value (list case)
            */
void append(QVariant &v, const QVariant &value)
{
    if (!v.canConvert<QVariantList>())
        v = QVariantList();

    QVariantList *p = (QVariantList *)v.data();
    p->append(value);
}


//QByteArray serialize1(const QVariant &data, JSON_OPTIONS options)
//{
//    bool success = true;
//    return serialize1(data, success );
//}

QByteArray serialize1(const QVariant &data, bool *success, JSON_OPTIONS options,int level /*= 0*/)
{

    QByteArray tabs;

    bool pretty=false;
    if ( options & JSON_PRETTY_PRINT )
        pretty=true;

    //    if( success != 0)
    //        *success = true;

    level++;

    if ( pretty )
    {
        tabs = margin( level );
    }

    QByteArray ba;

    //bool local_ok = false;

    if ( ! data.isValid())
    { // invalid or null?
        ba = "null";
    }

    else if ((data.type() == QVariant::List) || (data.type() == QVariant::StringList))
    {
        // variant is a list?

        const QVariantList list = data.toList();

        ba = serializeList( list , success, options, level );
    }
    else if (data.type() == QVariant::Hash)
    { // variant is a hash?
        //str = serializeMap(data.toHash(), success, _level+1);
    }
    else if (data.type() == QVariant::Map)
    {
        // variant is a map?
        ba = serializeMap( data.toMap(), success, options, level);
    }
    else if (data.type() == QVariant::String  )  // a string
    {
        //        qDebug() << "String in : " << data;

        ba = sanitizeString( data.toString() , options).toUtf8();

        //        qDebug() << "String out : " << ba;

    }
    else if (data.type() == QVariant::ByteArray)
    {
        ba = data.toString().toUtf8();
    }
    else if (data.type() == QVariant::Double)
    {
        // double?

        bool ok1;
        double value = data.toDouble( &ok1 );


        if ( ok1 )
        {
            //ba = QByteArray::number(value, 'g' ); ! так не делай 20455.9 т.е. округляет до 6 значков
            ba = QByteArray::number(value, 'f' ); // 20455.870000

            if ( ! ba.contains(".") && ! ba.contains("e") )
            {
                ba += ".0";
            }
            clearLastNulls( ba );
        }
    }
    else if (data.type() == QVariant::Bool)
    {
        ba = data.toBool() ? "true" : "false";
    }
    else if (data.type() == QVariant::ULongLong)
    {
        ba = QByteArray::number(data.value<qulonglong>());
    }
    else if (data.canConvert<qlonglong>())
    {
        ba = QByteArray::number(data.value<qlonglong>());
    }
    else if (data.canConvert<long>())
    {
        ba = QString::number(data.value<long>()).toUtf8();
    }
    else if (data.type() == QVariant::DateTime)
    {
        ba = sanitizeString(dateTimeFormat.isEmpty()
                            ? data.toDateTime().toString()
                            : data.toDateTime().toString(dateTimeFormat)).toUtf8();
    }
    else if (data.type() == QVariant::Date)
    {
        ba = sanitizeString(dateTimeFormat.isEmpty()
                            ? data.toDate().toString()
                            : data.toDate().toString(dateFormat)).toUtf8();
    }
    else if (data.canConvert<QString>())
    {
        // this will catch QUrl, ... (all other types which can be converted to string)
        ba = sanitizeString(data.toString()).toUtf8();
    }
    else if (data.type() == QVariant::UserType)
    {
        // ----------------------------------------------
        //          Variant is a OrderedObj
        // ----------------------------------------------

        QString tn = data.typeName();

        if( tn == "OrderedObj" )
        {
            OrderedObj obj = data.value<OrderedObj>();


            QList<QByteArray> values;

            //            const QVariantList list = data.toList();

            QByteArray serializedValue;


            Q_FOREACH(const Pair2& pair, obj.lst)
            {
                bool local_ok2 = true;

                if ( pair.val.type() != QVariant::UserType) // Pair?
                {

                    // ----------------------------------------------
                    //          value is standart type
                    // ----------------------------------------------

                    serializedValue = serialize1(pair.val , &local_ok2, options, level);

                    if ( serializedValue.isNull() )
                    {
                        if( success !=0 )
                            success = false;
                        break;
                    }

                    QByteArray ba2 =  (pretty ? tabs  : "") + ch_quote + pair.key.toUtf8() + ch_quote + " : " +serializedValue;

                    //qDebug() << "ba2 " << ba2;

                    values << ( pretty ? tabs : "" ) + ba2;
                }
                else
                {
                    // ----------------------------------------------
                    //          value is user type
                    // ----------------------------------------------

                    QString tn = pair.val.typeName();

                    if( tn == "OrderedObj" ) // вложенный OrderedObj
                    {
                        OrderedObj obj2 = pair.val.value<OrderedObj>();

                        serializedValue = serialize1(pair.val , &local_ok2, options, level);

                        if ( serializedValue.isNull() )
                        {
                            if( success != 0)
                                *success = false;
                            break;
                        }
                        QByteArray ba2 =  ( pretty ? tabs : "" ) + ch_quote+ pair.key.toUtf8() + ch_quote + " : " +serializedValue;

                        qDebug() << "ba2 " << ba2;

                        values << ( pretty ? tabs : "" ) + ba2;

                    }

                }

            }

            if ( ! values.isEmpty())
            {
                ba = "{" + ( pretty ? ch_rn : "" ) + join( values, "," + ( pretty ? ch_rn : "" ) ) + ( pretty ? ch_rn + tabs : "" ) +   "}";
            }
            else
            {
                ba = "{}";
            }
        }

    }
    else
    {
        if( success != 0)
            *success = false;
    }

    level--;


    //    if( success != 0 && ! * success )
    //        return QByteArray("3453245234543 ?????????/");


    return ba;

}

QByteArray& clearLastNulls( QByteArray &ba , int min_precision )
{
    // --------------------------------------------------------------
    // можно после 'f' подчистить после точки не нужные нули в конце
    // но чистим не до знаков после запятой = min_precision
    // --------------------------------------------------------------

    int dot = ba.indexOf(".");

    if( dot >=0 )
    {
        for( int pos = ba.length() -1 ; pos > dot; pos--)
        {
            if( ba.at( pos ) != '0')
                break;

            if( pos <= ( dot + min_precision ) )
                break;

            else
                ba.remove( pos , 1  ); // удаляем лишний не значащий ноль в конце
        }
    }

    return ba;
}

//QString serializeStr(const QVariant &data)
//{
//    //setPrettySerialize(true);

//    bool ok;

//    return QString::fromUtf8(serialize1(data , &ok , options) );
//}

//QString serializeStrWifthOrder(const QtJson::JsonWithOrder &data)
//{
//    setPrettySerialize(true);

//    QString str="{\n";

//    int count=0;
//    foreach( Pair pair, data)
//    {
//        if(count>0)
//            str.append(",\n");

//        str.append( QString("\t\"%1\":%2")
//                    .arg(pair.first)
//                    .arg( QString::fromUtf8( serialize1( pair.second  )) )
//                    );
//        count++;
//    }

//    return str+"\n}";
//}

QString serializeQVariantMap(const QVariantMap &map, JSON_OPTIONS options)
{
    bool success=false;
    int _level=0;
    return serializeMap(map, &success, options, _level+1);
}

QString serializeStr(const QVariant &data, bool *success)
{
    return QString::fromUtf8(serialize1(data, success));
}


/**
            * \enum JsonToken
            */
enum JsonToken {
    JsonTokenNone = 0,
    JsonTokenCurlyOpen = 1,
    JsonTokenCurlyClose = 2,
    JsonTokenSquaredOpen = 3,
    JsonTokenSquaredClose = 4,
    JsonTokenColon = 5,
    JsonTokenComma = 6,
    JsonTokenString = 7,
    JsonTokenNumber = 8,
    JsonTokenTrue = 9,
    JsonTokenFalse = 10,
    JsonTokenNull = 11
};

QString sanitizeString2(QString str)
{
    /*
        По спецификации JSON в строке после символа \ не может стоять число 4. После \ допустимо использовать только:

        " - кавычка, просто экранирование кавычки
        \ - обратный слеш - экранирование для самого себя для однозначного распознавания символьных последовательностей с особым значением в строках
        / - прямой
        b - символ backspace
        n - символ line feed (перевод строки)
        r - символ carriage return (возврат каретки)
        t - символ табуляции
        u с последующими 4 HEX символами, обозначает соответствующий символ Unicode (этой формой записи допустимо заменить вышеуказанные символы, впрочем)
    */
    // 1. C:/Arcus тут засада была  / (экранируем \/)
    // 2. ООО /МКТ\ ТЕСТ тут засада была  \ (экранируем \\) И ПОТОМ НА СЕPВЕPЕ json_decode еще раз
    // $postData = str_replace('\\', '\\\\', file_get_contents('php://input').PHP_EOL );

    // ----------------------------------------------------------------------
    //                      ОЧЕНЬ ВАЖНО
    // ----------------------------------------------------------------------

    // сначала заэкранируем все \ ( это сработает для \b \f \n \r \t )
    // и сработает в.т.ч. и для просто aa\bb

    //qDebug() << "sanitizeString "<<str;
    //    if(str.indexOf( ch_back_slash ) >=0)
    //    {
    //        // ascii  \  0x5C
    //        str.replace( ch_back_slash ,ch2_back_slash ); // \u005c=5C7530303543

    //    }
    // потом отдельно экранируем / и "
    //    if(str.indexOf( ch_slash ) >=0 )
    //    {
    //        // \/   2F
    //        str.replace(ch_slash, ch2_slash);

    //    }
    if(str.indexOf( ch_quote ) >=0 )
    {
        // \"
        //        if( str.contains("МКТ") ||str.contains("MKT") ||str.contains("ООО"))
        //            qDebug() << "4564354 str " << str;
        str.replace(ch_quote ,ch2_quote);

    }
    str.remove( ch_r);
    str.remove( ch_n);
    str.remove( ch_t);
    //    if(str.indexOf( ch_rn ) >=0 )  //????
    //    {
    //        // \n
    //        str.replace( ch_rn , ch2_rn);

    //    }

    //    if(str.indexOf( ch_r ) >=0 )
    //    {
    //        // \r
    //        str.replace(ch_r , ch2_r);

    //    }
    //    if(str.indexOf( ch_t ) >=0 )
    //    {
    //        // \t
    //        str.replace(ch_t , ch2_t);

    //    }
    //    str.replace(QLatin1String("\b"), QLatin1String("\\b"));
    //    str.replace(QLatin1String("\f"), QLatin1String("\\f"));
    //    str.replace(QLatin1String("\n"), QLatin1String("\\n"));
    //    str.replace(QLatin1String("\r"), QLatin1String("\\r"));
    //    str.replace(QLatin1String("\t"), QLatin1String("\\t"));

    // вот так на выходе экранировано будет {\"comPort\":\"COM129\"}

    //qDebug() << "sanitizeString res :  "<<str;

    return QString(QLatin1String("\"%1\"")).arg(str);
}

QString escape_unicode(QString input )
{
    std::wstring output;
    QString result;

    //    //QTextCodec::setCodecForLocale ( QTextCodec::codecForName ( "UTF-8" ) );

    //    for( uint i = 0; wcslen( input.constData() ) > i; ++i )
    //    {
    //        if( isascii( input[ i ] ) )
    //        {
    //            output.reserve( output.size() + 1 );
    //            output += input[ i ];
    //        }
    //        else
    //        {
    //            wchar_t code[ 7 ];

    //            swprintf( code, 7, L"\\u%0.4X", input[ i ] );

    //            output.reserve( output.size() + 7 ); // "\u"(2) + 5(uint max digits capacity)

    //            output += code;
    //        }
    //    }

    //    result.reserve( output.size() );
    //    result.append( QString::fromStdWString( output ) );

    return result;

}

QString sanitizeString(QString str , JSON_OPTIONS options)
{

    //qDebug() << "sanitizeString in" << str;
    //    if( options & JSON_UNESCAPED_UNICODE)
    //    {
    //        QStdWString str1  = str.toStdWString();
    //        str1.
    //        qDebug() << "str1 sdfdsfd " <<str;
    //    }

    /*
        По спецификации JSON в строке после символа \ не может стоять число 4. После \ допустимо использовать только:

        " - кавычка, просто экранирование кавычки
        \ - обратный слеш - экранирование для самого себя для однозначного распознавания символьных последовательностей с особым значением в строках
        / - прямой
        b - символ backspace
        n - символ line feed (перевод строки)
        r - символ carriage return (возврат каретки)
        t - символ табуляции
        u с последующими 4 HEX символами, обозначает соответствующий символ Unicode (этой формой записи допустимо заменить вышеуказанные символы, впрочем)
    */
    // 1.1 C:/Arcus тут засада была  / (экранируем \/) php json_decode
    // 1.2 C:\Arcus тут засада была  \ (экранируем \\) php json_decode
    // 2. ООО /МКТ\ ТЕСТ тут засада была  \ (экранируем \\) И ПОТОМ НА СЕPВЕPЕ json_decode еще раз
    // $postData = str_replace('\\', '\\\\', file_get_contents('php://input').PHP_EOL );

    // ----------------------------------------------------------------------
    //                      ОЧЕНЬ ВАЖНО
    // ----------------------------------------------------------------------

    // сначала заэкранируем все \ ( это сработает для \b \f \n \r \t )
    // и сработает в.т.ч. и для просто aa\bb

    //qDebug() << "sanitizeString "<<str;
    if(str.indexOf( ch_back_slash ) >=0)
    {
        // ascii  \  0x5C
        str.replace( ch_back_slash ,ch2_back_slash ); // \u005c=5C7530303543

    }
    //потом отдельно экранируем /
//    if(str.indexOf( ch_slash ) >=0 )
//    {
//        // \/   2F
//        str.replace(ch_slash, ch2_slash);

//    }

    // потом отдельно экранируем /
    if(str.indexOf( ch_quote ) >=0 )
    {
        // \"
        if( str.contains("МКТ") ||str.contains("MKT") ||str.contains("ООО"))
            qDebug() << "4564354 str " << str;

        str.replace(ch_quote ,ch2_quote);

    }
    //    if(str.indexOf( ch_rn ) >=0 )  //????
    //    {
    //        // \n
    //        str.replace( ch_rn , ch2_rn);

    //    }
    //    if(str.indexOf( ch_r ) >=0 )
    //    {
    //        // \r
    //        str.replace(ch_r , ch2_r);

    //    }
    //    if(str.indexOf( ch_t ) >=0 )
    //    {
    //        // \t
    //        str.replace(ch_t , ch2_t);

    //    }
    //    str.replace(QLatin1String("\b"), QLatin1String("\\b"));
    //    str.replace(QLatin1String("\f"), QLatin1String("\\f"));
    //    str.replace(QLatin1String("\n"), QLatin1String("\\n"));
    //    str.replace(QLatin1String("\r"), QLatin1String("\\r"));
    //    str.replace(QLatin1String("\t"), QLatin1String("\\t"));

    // вот так на выходе экранировано будет {\"comPort\":\"COM129\"}

    //qDebug() << "sanitizeString res :  "<<str;

    return QString(QLatin1String("\"%1\"")).arg(str);
}

static QByteArray join(const QList<QByteArray> &list, const QByteArray &sep)
{
    QByteArray res;

    Q_FOREACH(const QByteArray &i, list)
    {
        if ( !res.isEmpty() )
        {
            res += sep;
        }
        res += i;
    }
    return res;
}

static QVariant parseValue(const QString &json, int &index, bool &parse_ok)
{

    // Determine what kind of data we should parse by
    // checking out the upcoming token
    switch(lookAhead( json, index ))
    {
    case JsonTokenString:
        return parseString(json, index, parse_ok);
    case JsonTokenNumber:
        return parseNumber(json, index);
    case JsonTokenCurlyOpen:
        return parseObject(json, index, parse_ok);
    case JsonTokenSquaredOpen:
        return parseArray(json, index, parse_ok);
    case JsonTokenTrue:
        nextToken(json, index);
        return QVariant(true);
    case JsonTokenFalse:
        nextToken(json, index);
        return QVariant(false);
    case JsonTokenNull:
        nextToken(json, index);
        return QVariant();
    case JsonTokenNone:
        break;
    }

    // If there were no tokens, flag the failure and return an empty QVariant
    parse_ok = false;
    return QVariant();
}

/**
            * parseObject
            */
static QVariant parseObject(const QString &json, int &index, bool &parse_ok)
{
    QVariantMap map;
    int token;

    // Get rid of the whitespace and increment index
    nextToken(json, index);

    // Loop through all of the key/value pairs of the object
    bool done = false;
    while (!done)
    {
        // Get the upcoming token
        token = lookAhead(json, index);

        if (token == JsonTokenNone)
        {
            parse_ok = false;
            return QVariantMap();
        }
        else if (token == JsonTokenComma)
        {
            nextToken(json, index);
        }
        else if (token == JsonTokenCurlyClose)
        {
            nextToken(json, index);
            return map;
        }
        else
        {
            // Parse the key/value pair's name
            QString name = parseString(json, index, parse_ok).toString();

            if (!parse_ok)
            {
                return QVariantMap();
            }

            // Get the next token
            token = nextToken(json, index);

            // If the next token is not a colon, flag the failure
            // return an empty QVariant
            if (token != JsonTokenColon)
            {
                parse_ok = false;
                return QVariant(QVariantMap());
            }

            // Parse the key/value pair's value
            QVariant value = parseValue(json, index, parse_ok);

            if (!parse_ok)
            {
                return QVariantMap();
            }

            // Assign the value to the key in the map
            map[name] = value; // упорядочивает по ключу
            //map.insert(name,  value);

            //qDebug() <<QtJson::serialize1( map );
        }
    }

    // Return the map successfully
    return QVariant(map);
}

/**
            * parseArray
            */
static QVariant parseArray(const QString &json, int &index, bool &parse_ok)
{
    QVariantList list;

    nextToken(json, index);

    bool done = false;

    while(!done)
    {
        int token = lookAhead(json, index);

        if (token == JsonTokenNone)
        {
            parse_ok = false;
            return QVariantList();
        }
        else if (token == JsonTokenComma)
        {
            nextToken(json, index);
        }
        else if (token == JsonTokenSquaredClose)
        {
            nextToken(json, index);
            break;
        }
        else
        {
            QVariant value = parseValue(json, index, parse_ok);
            if (!parse_ok) {
                return QVariantList();
            }
            list.push_back(value);
        }
    }

    return QVariant(list);
}

/**
            * parseString
            */

static QVariant parseString(const QString &json, int &index, bool &parse_ok)
{
    QString s;
    QChar c;

    eatWhitespace(json, index);

    c = json[index++];

    bool complete = false;

    while(!complete)
    {
        if (index == json.size())
        {
            break;
        }

        c = json[index++];

        if ( c == '\"')
        {
            complete = true;
            break;
        }
        else if (c == '\\')
        {
            if (index == json.size())
            {
                break;
            }

            c = json[index++];

            if (c == '\"')
            {
                s.append('\"');
            }
            else if (c == '\\')
            {
                s.append('\\');
            } else if (c == '/')
            {
                s.append('/');
            }
            else if (c == 'b')
            {
                s.append('\b');
            }
            else if (c == 'f')
            {
                s.append('\f');
            }
            else if (c == 'n')
            {
                //s.append('\n');
                s.append('\r\n'); // windows
            }
            else if (c == 'r')
            {
                s.append('\r');
            }
            else if (c == 't')
            {
                s.append('\t');
            }
            else if (c == 'u')
            {
                int remainingLength = json.size() - index;

                if ( remainingLength >= 4)
                {
                    QString unicodeStr = json.mid(index, 4);

                    int symbol = unicodeStr.toInt(0, 16);

                    s.append(QChar(symbol));

                    index += 4;
                }
                else
                {
                    break;
                }

            }
        }
        else
        {
            s.append(c);
        }
    }

    if ( !complete )
    {
        parse_ok = false;
        return QVariant();
    }

    return QVariant(s);
}


static QVariant parseNumber(const QString &json, int &index)
{
    eatWhitespace(json, index);

    int lastIndex = lastIndexOfNumber(json, index);

    int charLength = (lastIndex - index) + 1;

    QString numberStr;


    numberStr = json.mid( index, charLength );

    index = lastIndex + 1;

    bool ok;

    if ( numberStr.contains('.'))
    {

        double tmp = numberStr.toDouble( &ok );
        //        QVariant vv(tmp); //  numberStr "20455.87" vv QVariant(double, 20455.9) как такое может быть !!!!!
        //        QVariant vv1 = QVariant::fromValue( tmp );
        //        qDebug() << "tmp" << tmp << "vv"<<vv << QVariant::fromValue( tmp );
        //        qDebug() << "numberStr" << numberStr << "ok"<< ok<<numberStr.toDouble( &ok );
        //        qDebug() << "   toFloat" << numberStr.toFloat( &ok ) << "ok"<< ok;
        Q_ASSERT ( ok );
        return tmp;
    }
    else if ( numberStr.startsWith('-') )
    {
        int i = numberStr.toInt(&ok);

        if (!ok)
        {
            qlonglong ll = numberStr.toLongLong(&ok);
            return ok ? ll : QVariant(numberStr);
        }
        return i;
    }
    else
    {
        uint u = numberStr.toUInt(&ok);

        if (!ok)
        {
            qulonglong ull = numberStr.toULongLong(&ok);
            return ok ? ull : QVariant(numberStr);
        }
        return u;
    }
}

/**
            * lastIndexOfNumber
            */
static int lastIndexOfNumber(const QString &json, int index) {
    int lastIndex;

    for(lastIndex = index; lastIndex < json.size(); lastIndex++) {
        if (QString("0123456789+-.eE").indexOf(json[lastIndex]) == -1) {
            break;
        }
    }

    return lastIndex -1;
}

static void eatWhitespace(const QString &json, int &index)
{
    for(; index < json.size(); index++)
    {
        if (QString(" \t\r\n").indexOf(json[index]) == -1)
        {
            break;
        }
    }
}

static int lookAhead(const QString &json, int index)
{
    int saveIndex = index;
    return nextToken(json, saveIndex);
}

static int nextToken(const QString &json, int &index)
{
    eatWhitespace(json, index);

    if (index == json.size()) {
        return JsonTokenNone;
    }

    QChar c = json[index];
    index++;
    switch(c.toLatin1()) {
    case '{': return JsonTokenCurlyOpen;
    case '}': return JsonTokenCurlyClose;
    case '[': return JsonTokenSquaredOpen;
    case ']': return JsonTokenSquaredClose;
    case ',': return JsonTokenComma;
    case '"': return JsonTokenString;
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    case '-': return JsonTokenNumber;
    case ':': return JsonTokenColon;
    }
    index--; // ^ WTF?

    int remainingLength = json.size() - index;

    // True
    if (remainingLength >= 4) {
        if (json[index] == 't' && json[index + 1] == 'r' &&
                json[index + 2] == 'u' && json[index + 3] == 'e') {
            index += 4;
            return JsonTokenTrue;
        }
    }

    // False
    if (remainingLength >= 5) {
        if (json[index] == 'f' && json[index + 1] == 'a' &&
                json[index + 2] == 'l' && json[index + 3] == 's' &&
                json[index + 4] == 'e') {
            index += 5;
            return JsonTokenFalse;
        }
    }

    // Null
    if (remainingLength >= 4) {
        if (json[index] == 'n' && json[index + 1] == 'u' &&
                json[index + 2] == 'l' && json[index + 3] == 'l') {
            index += 4;
            return JsonTokenNull;
        }
    }

    return JsonTokenNone;
}

void setDateTimeFormat(const QString &format) {
    dateTimeFormat = format;
}

void setDateFormat(const QString &format) {
    dateFormat = format;
}

QString getDateTimeFormat() {
    return dateTimeFormat;
}

QString getDateFormat() {
    return dateFormat;
}

void setPrettySerialize(bool enabled) {
    prettySerialize = enabled;
}

bool isPrettySerialize() {
    return prettySerialize;
}



QQueue<BuilderJsonObject *> BuilderJsonObject::created_list;

BuilderJsonObject::BuilderJsonObject() {
    // clean objects previous "created"
    while (!BuilderJsonObject::created_list.isEmpty()) {
        delete BuilderJsonObject::created_list.dequeue();
    }
}

BuilderJsonObject::BuilderJsonObject(JsonObject &json) {
    BuilderJsonObject();

    obj = json;
}

BuilderJsonObject *BuilderJsonObject::set(const QString &key, const QVariant &value) {
    obj[key] = value;

    return this;
}

BuilderJsonObject *BuilderJsonObject::set(const QString &key, BuilderJsonObject *builder) {
    return set(key, builder->create());
}

BuilderJsonObject *BuilderJsonObject::set(const QString &key, BuilderJsonArray *builder) {
    return set(key, builder->create());
}

JsonObject BuilderJsonObject::create() {
    BuilderJsonObject::created_list.enqueue(this);

    return obj;
}


QQueue<BuilderJsonArray *> BuilderJsonArray::created_list;

BuilderJsonArray::BuilderJsonArray() {
    // clean objects previous "created"
    while (!BuilderJsonArray::created_list.isEmpty()) {
        delete BuilderJsonArray::created_list.dequeue();
    }
}

BuilderJsonArray::BuilderJsonArray(JsonArray &json) {
    BuilderJsonArray();

    array = json;
}

BuilderJsonArray *BuilderJsonArray::add(const QVariant &element) {
    array.append(element);

    return this;
}

BuilderJsonArray *BuilderJsonArray::add(BuilderJsonObject *builder) {
    return add(builder->create());
}

BuilderJsonArray *BuilderJsonArray::add(BuilderJsonArray *builder) {
    return add(builder->create());
}

JsonArray BuilderJsonArray::create() {
    BuilderJsonArray::created_list.enqueue(this);

    return array;
}




BuilderJsonObject *objectBuilder() {
    return new BuilderJsonObject();
}

BuilderJsonObject *objectBuilder(JsonObject &json) {
    return new BuilderJsonObject(json);
}

BuilderJsonArray *arrayBuilder() {
    return new BuilderJsonArray();
}

BuilderJsonArray *arrayBuilder(JsonArray &json) {
    return new BuilderJsonArray(json);
}

} //end namespace

