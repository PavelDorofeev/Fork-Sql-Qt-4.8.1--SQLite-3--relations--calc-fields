#ifndef QP_FILEINFO_H
#define QP_FILEINFO_H

#include <windows.h>
#include <QString>
#include <QDir>

#include "qp/core/file/qp_fileversion.h"

namespace qp{

namespace file{

typedef enum DLL_ARCH
{
    DLL_ARCH_UNKNOWN=-1,
    DLL_ARCH_X86 = 1,
    DLL_ARCH_X64 = 2
}DLL_ARCH;

}
}

#include "qp/core/dll_qp_core_global.h"
class LIB_PREFIX_QP_CORE QpFileInfo
{
public:


    QpFileInfo(const QString &fullName);

    bool get_dll_version( QpFileVersion &vv) const;
    bool iscorrectFileName() const;
    bool get_dll_arch( qp::file::DLL_ARCH &arch) const;

    const QString getArchToStr(const qp::file::DLL_ARCH arch) const ;

private:

    const QString fullName;
    QDir dir;

};

#endif // QP_FILEINFO_H
