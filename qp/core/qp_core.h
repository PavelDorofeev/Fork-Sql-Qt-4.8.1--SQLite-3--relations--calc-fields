#ifndef QP_CORE_H
#define QP_CORE_H


#include "qp/core/meta/meta.h"
#include "qp/core/dbg/dbg.h"
#include "qp/core/dbg/dbg_core.h"
#include "qp/core/cont/qp_cont.h"
#include "qp/core/evt/qp_evt.h"


// --------------------------------------------------------------------------------------
Q_CORE_EXPORT void qt_assert(const char *assertion, const char *file, int line);

//  our QP_ASSERT run in release building too !!!
#if !defined(QP_ASSERT)
#    define QP_ASSERT(cond) ((!(cond)) ? qt_assert(#cond,__FILE__,__LINE__) : qt_noop())
#endif
// --------------------------------------------------------------------------------------



#endif // QP_CORE_H
