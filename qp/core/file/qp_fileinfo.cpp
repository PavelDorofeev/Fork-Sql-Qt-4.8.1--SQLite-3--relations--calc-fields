#include "qp_fileinfo.h"
#include <QDir>
#include <QDebug>
#include <sys/stat.h>

#pragma comment(lib, "version.lib") // для GetFileVersionInfoSize и т.д

QpFileInfo::QpFileInfo(const QString &FullName):
    fullName(FullName)
{

    iscorrectFileName(  );

}

bool QpFileInfo::iscorrectFileName() const
{
    if( fullName.isNull() || fullName.isEmpty() )
        return false;

    //qDebug() << "fullName" << fullName;

    if( ! dir.exists( ) )
    {
         return false;
    }

    if( ! dir.exists( fullName ) )
    {
        qCritical() << "файл "+fullName +" не существует";

        return false;
    }


    return true;
}

bool QpFileInfo::get_dll_version( QpFileVersion &vv) const
{
    vv.clear();

    WCHAR fileName[_MAX_PATH];

    HMODULE hFile = 0;

    if( ! iscorrectFileName( ) )
    {
        return false;
    }


    LPCWSTR fullPathNameWin = (const wchar_t*) fullName.utf16();

    DWORD size = GetFileVersionInfoSize( fullPathNameWin , 0); // надо полное имя

    BYTE* versionInfo = new BYTE[size];

    if ( ! GetFileVersionInfo( fullPathNameWin, 0, size, versionInfo) )
    {
        delete[] versionInfo;
        return false;
    }

    UINT                len = 0;
    VS_FIXEDFILEINFO*   vsfi = NULL;

    VerQueryValue(versionInfo, L"\\", (void**)&vsfi, &len);


    vv.vv1 = HIWORD(vsfi->dwFileVersionMS);
    vv.vv2 = LOWORD(vsfi->dwFileVersionMS);
    vv.vv3 = HIWORD(vsfi->dwFileVersionLS);
    vv.vv4 = LOWORD(vsfi->dwFileVersionLS);

    delete[] versionInfo;


    return true;
}


bool QpFileInfo::get_dll_arch( qp::file::DLL_ARCH &arch) const
{
    if ( ! iscorrectFileName( ))
    {
      return false;
    }

    struct stat fi;

    qDebug() << "fullName"<<fullName;

    QByteArray ba = fullName.toLocal8Bit(); // именно так
    const char *c_str2 = ba.data();

    const char * ff = c_str2;

    qDebug() << "ff"<<ff;

    stat ( ff , &fi);

    arch = qp::file::DLL_ARCH_UNKNOWN;

    char buff [3];

    FILE *file = fopen (ff, "rb");

    if (file == NULL)
        goto err;

    bool found = false;

    for (int i = 0; i < fi.st_size; i ++)
    {
        if (getc (file) == 'P')
        {
            if (getc (file) == 'E')
            {
                getc (file);
                getc (file);
                buff [0] = getc (file);
                buff [1] = 0;

                if (buff [0] == 'd')
                {
                    arch = qp::file::DLL_ARCH_X64;
                    found  = true;
                }

                else if (buff [0] == 'L')
                {
                    arch = qp::file::DLL_ARCH_X86;
                    found = true;
                }
            }
        }
    }

    if( ! found )
        goto err2;

    int res = fclose (file);

    return true;

err2:

    int res2 =fclose (file);

err:

    return false;

}

const QString QpFileInfo::getArchToStr( const qp::file::DLL_ARCH archIn) const
{
    switch( archIn)
    {
    case qp::file::DLL_ARCH_X86:
        return "x32";
    case qp::file::DLL_ARCH_X64:
        return "x64";
    case qp::file::DLL_ARCH_UNKNOWN:
    default:
        return "unknown";
    }
}
