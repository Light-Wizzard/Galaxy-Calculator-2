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

#include "3rdparty/cpython/modules/exprtkmodule.hpp"

/******************************************************************************
* \fn evaluate
*******************************************************************************/
PyObject *evaluate(PyObject *self, PyObject *args)
{
    MODULE_FUNC_TRY
    Q_UNUSED(self)
    PyObject *pyExpression;
    PyObject *pySymTable;

    if (!PyArg_ParseTuple(args, "OO:", &pyExpression, &pySymTable))
    {
        return PyNull;
    }

    const char *expression = PyUnicode_AsUTF8(pyExpression);
    if (expression == PyNull)
    {
        return PyNull;
    }

    SymbolTable symTable = SymbolTableConverter::Convert(pySymTable);

    ArithmeticType value = ExpressionParser::evaluate(expression, symTable);

    PyObject *ret = PyTuple_New(2);

    PyTuple_SetItem(ret, 0, PyFloat_FromDouble(value.toDouble()));
    PyTuple_SetItem(ret, 1, SymbolTableConverter::New(symTable));

    SymbolTableConverter::Cleanup(symTable);

    return ret;

    MODULE_FUNC_CATCH
}
/******************************************************************************
* \fn get_global_symtable
*******************************************************************************/
PyObject *get_global_symtable(PyObject *self, PyObject *args)
{
    Q_UNUSED(self)
    Q_UNUSED(args)
    return SymbolTableConverter::New(mainWindow->getSymbolTable());
}
/******************************************************************************
* \fn set_global_symtable
*******************************************************************************/
PyObject *set_global_symtable(PyObject *self, PyObject *args)
{
    Q_UNUSED(self)
    PyObject *pysym = PyNull;
    if (!PyArg_ParseTuple(args, "O:", &pysym))
    {
        return PyNull;
    }
    mainWindow->onSymbolTableChanged(SymbolTableConverter::Convert(pysym));
    return PyLong_FromLong(0);
}
/******************************************************************************
* \fn MethodDef
*******************************************************************************/
static PyMethodDef MethodDef[] =
{
    {"evaluate",            evaluate,            METH_VARARGS, "."},
    {"get_global_symtable", get_global_symtable, METH_NOARGS,  "."},
    {"set_global_symtable", set_global_symtable, METH_VARARGS, "."},
    {PyNull, PyNull, 0, PyNull}
};
/******************************************************************************
* \fn ModuleDef
*******************************************************************************/
static PyModuleDef ModuleDef =
{
    PyModuleDef_HEAD_INIT,
    MODULE_NAME,
    PyNull,
    -1,
    MethodDef,
    PyNull, PyNull, PyNull, PyNull
};
/******************************************************************************
* \fn PyInit
*******************************************************************************/
static PyObject *PyInit()
{
    PyObject *m;

    m = PyModule_Create(&ModuleDef);
    if (m == PyNull)
        return PyNull;

    if (!PyMpReal_Initialize(m))
    {
        Py_DECREF(m);
        return PyNull;
    }

    return m;
}
/******************************************************************************
* \fn initialize
*******************************************************************************/
void ExprtkModule::initialize(MainWindow &w)
{
    mainWindow = &w;
    PyImport_AppendInittab(MODULE_NAME, PyInit);
}
/*** ************************* End of File ***********************************/
