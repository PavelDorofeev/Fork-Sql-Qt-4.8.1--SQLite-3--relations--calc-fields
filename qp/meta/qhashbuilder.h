#ifndef QHASHBUILDER_H
#define QHASHBUILDER_H
#include <QHash>

template <class T, class U>

class QHashBuilder
{
public:
    QHashBuilder & add(const T & key, const U & value)
    {
        _hash.insert(key,value);
        return *this;
    }

    QHash<T,U> build()
    {
        return _hash;
    }

private:
    QHash<T,U> _hash;
};

#endif // QHASHBUILDER_H
