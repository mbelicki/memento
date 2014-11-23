#ifndef COMMON_H
#define COMMON_H

#include <QDebug>

static inline void memento_log(const char *msg) { qDebug() << msg; }

#define M_CHECK_PTR_ARG(arg, ret) \
    if ((arg) == NULL) { \
        memento_log("Argument '##arg' is null."); \
        return (ret); \
    }

typedef unsigned int entityid_t;

static const entityid_t INVALID_ID = 0;


#endif // COMMON_H
