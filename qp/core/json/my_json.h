
#ifndef MY_JSON_H
#define MY_JSON_H

#include <QVariant>
#include <QString>
#include <QQueue>
#include <QPair>


#include "../dll_qp_core_global.h"

namespace QtJson
{
typedef QVariantMap JsonObject;

typedef QVariantList JsonArray;

enum JSON_OPTIONS{
    JSON_DEFAULT=1,
    JSON_PRETTY_PRINT =2,
    JSON_UNESCAPED_UNICODE =4

};

static QString escape_unicode(QString str );
static QString sanitizeString(QString str, JSON_OPTIONS options = JSON_DEFAULT);
static QString sanitizeString2(QString str); // экранируем только " (все спецсимволы удаляем и пробелы тоже)

QVariant clone(const QVariant &data);

void insert(QVariant &v, const QString &key, const QVariant &value);

void append(QVariant &v, const QVariant &value);

LIB_PREFIX_QP_CORE QVariant parse1(const QString &json);

LIB_PREFIX_QP_CORE  QVariant parse1(const QString &json, bool &success);

//LIB_PREFIX_QP_CORE QByteArray serialize1(const QVariant &data, JSON_OPTIONS options = JSON_PRETTY_PRINT);

LIB_PREFIX_QP_CORE QByteArray serialize1(const QVariant &data, bool *success=0, JSON_OPTIONS options = JSON_PRETTY_PRINT, int _level=0 );

LIB_PREFIX_QP_CORE QString serializeQVariantMap(const QVariantMap &data , JSON_OPTIONS options = JSON_PRETTY_PRINT);

//LIB_PREFIX_QP_CORE QString serializeStr(const QVariant &data);
LIB_PREFIX_QP_CORE QByteArray& clearLastNulls( QByteArray &ba , int min_precision = 0);
//QString serializeStrWifthOrder(const QtJson::JsonWithOrder &data);

LIB_PREFIX_QP_CORE QString serializeStr(const QVariant &data, bool *success=0, int _level = 0);

void setDateTimeFormat(const QString& format);
void setDateFormat(const QString& format);

LIB_PREFIX_QP_CORE QString getDateTimeFormat();
LIB_PREFIX_QP_CORE QString getDateFormat();

LIB_PREFIX_QP_CORE void setPrettySerialize(bool enabled);
bool isPrettySerialize();

LIB_PREFIX_QP_CORE QByteArray serializeMap(const QVariantMap &map, bool *success, JSON_OPTIONS options = JSON_PRETTY_PRINT, int _level=0);
LIB_PREFIX_QP_CORE QByteArray serializeList(const QVariantList &lst, bool *success, JSON_OPTIONS options = JSON_PRETTY_PRINT, int _level=0);

QByteArray margin( int ii);
LIB_PREFIX_QP_CORE QString makeStringPretty(const QString &str, JSON_OPTIONS options = JSON_PRETTY_PRINT);

class LIB_PREFIX_QP_CORE  Object : public QVariant
{
    template<typename T>
    Object& insertKey(Object* ptr, const QString& key)
    {
        T* p = (T*)ptr->data();
        if (!p->contains(key))
            p->insert(key, QVariant());
        return *reinterpret_cast<Object*>(&p->operator[](key));
    }
    template<typename T>
    void removeKey(Object *ptr, const QString& key)
    {
        T* p = (T*)ptr->data();
        p->remove(key);
    }
public:
    Object() : QVariant() {}
    Object(const Object& ref) : QVariant(ref) {}

    Object& operator=(const QVariant& rhs)
    {
        /** It maybe more robust when running under Qt versions below 4.7 */
        QObject * obj = qvariant_cast<QObject *>(rhs);
        //  setValue(rhs);
        setValue(obj);
        return *this;
    }
    Object& operator[](const QString& key)
    {
        if (type() == QVariant::Map)
            return insertKey<QVariantMap>(this, key);
        else if (type() == QVariant::Hash)
            return insertKey<QVariantHash>(this, key);

        setValue(QVariantMap());

        return insertKey<QVariantMap>(this, key);
    }
    const Object& operator[](const QString& key) const
    {
        return const_cast<Object*>(this)->operator[](key);
    }
    void remove(const QString& key)
    {
        if (type() == QVariant::Map)
            removeKey<QVariantMap>(this, key);
        else if (type() == QVariant::Hash)
            removeKey<QVariantHash>(this, key);
    }
};


class BuilderJsonArray;

class BuilderJsonObject
{

public:
    BuilderJsonObject();
    BuilderJsonObject(JsonObject &json);

    BuilderJsonObject *set(const QString &key, const QVariant &value);
    BuilderJsonObject *set(const QString &key, BuilderJsonObject *builder);
    BuilderJsonObject *set(const QString &key, BuilderJsonArray *builder);
    JsonObject create();

private:
    static QQueue<BuilderJsonObject *> created_list;

    JsonObject obj;
};

class BuilderJsonArray
{

public:
    BuilderJsonArray();
    BuilderJsonArray(JsonArray &json);

    BuilderJsonArray *add(const QVariant &element);
    BuilderJsonArray *add(BuilderJsonObject *builder);
    BuilderJsonArray *add(BuilderJsonArray *builder);
    JsonArray create();

private:
    static QQueue<BuilderJsonArray *> created_list;

    JsonArray array;
};



BuilderJsonObject *objectBuilder();

BuilderJsonObject *objectBuilder(JsonObject &json);

BuilderJsonArray *arrayBuilder();

BuilderJsonArray *arrayBuilder(JsonArray &json);
}

#endif //MY_JSON_H
