#ifndef QP_COMMON_H
#define QP_COMMON_H


#include "qp/db/db.h"
#include "qp/meta/meta.h"
#include "qp/gui/qp_gui.h"
#include "qp/dbg/dbg.h"

namespace qp
{

}

// --------------------------------------------------------------------------------------
Q_CORE_EXPORT void qt_assert(const char *assertion, const char *file, int line);

//  our QP_ASSERT run in release building too !!!
#if !defined(QP_ASSERT)
#    define QP_ASSERT(cond) ((!(cond)) ? qt_assert(#cond,__FILE__,__LINE__) : qt_noop())
#endif
// --------------------------------------------------------------------------------------




#endif // QP_COMMON_H
