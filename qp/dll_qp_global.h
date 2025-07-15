#ifndef DLL_QP_GLOBAL_H
#define DLL_QP_GLOBAL_H

//#include <QtCore/QtGlobal>

#if defined(USING_LIB_QP)

#if defined(LIB_IS_EXPORTED_QP)
#define LIB_PREFIX_QP Q_DECL_EXPORT // тут идея в том ,
// что здесь мы собираем именно саму библиотеку для использования как внешнюю
#else
#define LIB_PREFIX_QP Q_DECL_IMPORT // тут идея в том, что здесь мы уже используем
// собранную библиотеку в своем проекте, т.е. импортируем как бы
#endif
#else
#  define LIB_PREFIX_QP
// 1. этот вариант подходит, когда просто собираем все исходники в составе своего проекта
// 2. а также при статической сборке
#endif

#endif // DLL_QP_GLOBAL_H
