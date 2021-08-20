/**
 *  QCalc - Extensible programming calculator
 *  Copyright (C) 2021  Julian Zampiccoli
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef QCALC_EXPRTKMODULE_HPP
#define QCALC_EXPRTKMODULE_HPP

#include "src/3rdparty/cpython/pyutil.hpp"
#include "src/3rdparty/cpython/pythoninclude.hpp"
#include "src/3rdparty/cpython/symboltableconverter.hpp"
#include "src/3rdparty/cpython/modules/modulecommon.hpp"
#include "src/3rdparty/cpython/types/pympreal.hpp"

#include "src/MainWindow.h"

#include "src/3rdparty/math/expressionparser.hpp"

#define MODULE_NAME "qc_native_exprtk"

class MainWindow;
MainWindow *mainWindow = nullptr;
/************************************************
 * @brief ExprtkModule.
 * \namespace ExprtkModule
 ***********************************************/
namespace ExprtkModule
{
    void initialize(MainWindow &wnd);
}
#endif //QCALC_EXPRTKMODULE_HPP
/*** ************************* End of File ***********************************/
