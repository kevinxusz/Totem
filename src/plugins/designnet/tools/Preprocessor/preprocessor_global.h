#ifndef PREPROCESSOR_GLOBAL_H
#define PREPROCESSOR_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef PREPROCESSOR_LIB
# define PREPROCESSOR_EXPORT Q_DECL_EXPORT
#else
# define PREPROCESSOR_EXPORT Q_DECL_IMPORT
#endif

#endif // PREPROCESSOR_GLOBAL_H
