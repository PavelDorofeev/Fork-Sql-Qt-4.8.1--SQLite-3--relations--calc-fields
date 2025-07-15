#ifndef QP_COMMON_H
#define QP_COMMON_H

//#include "qp/core/qp_core.h"
//#include "qp/gui/qp_gui.h"

/*
#include "qp/sql/qp_sql.h"
#include "qp/core/meta/meta.h"
#include "qp/ntw/ntw.h"
#include "qp/core/cont/qp_cont.h"
#include "qp/gui/delegates/qp_delegates.h"
#include "qp/evt/qp_evt.h"
*/

#include "qp/core/dbg/dbg.h"

// --------------------------------------------------------------------------------------
Q_CORE_EXPORT void qt_assert(const char *assertion, const char *file, int line);

//  our QP_ASSERT run in release building too !!!
#if !defined(QP_ASSERT)
#    define QP_ASSERT(cond) ((!(cond)) ? qt_assert(#cond,__FILE__,__LINE__) : qt_noop())
#endif
// --------------------------------------------------------------------------------------



#endif // QP_COMMON_H
