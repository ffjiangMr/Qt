#ifndef QQUEUESQLHELPER_GLOBAL_H
#define QQUEUESQLHELPER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QQUEUESQLHELPER_LIBRARY)
#  define QQUEUESQLHELPER_EXPORT Q_DECL_EXPORT
#else
#  define QQUEUESQLHELPER_EXPORT Q_DECL_IMPORT
#endif

#endif // QQUEUESQLHELPER_GLOBAL_H
