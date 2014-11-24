/*
 * Copyright 2014 Mateusz Belicki
 *
 * free.software@belickim.net
 *
 * This file is part of Memento (Sailfish OS todo app).
 *
 * Memento is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * Memento is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Memento. If not, see <http://www.gnu.org/licenses/>.
 */

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
