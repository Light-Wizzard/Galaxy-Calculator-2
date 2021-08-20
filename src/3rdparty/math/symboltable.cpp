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

#include "src/3rdparty/math/symboltable.hpp"

/************************************************
 * @brief SymbolTable Static default Constructor.
 * SymbolTable
 ***********************************************/
SymbolTable::SymbolTable() = default;
/************************************************
 * @brief get Constants.
 * getConstants
 ***********************************************/
const std::map<std::string, ArithmeticType> &SymbolTable::getConstants() const
{
    return myConstants;
}
/************************************************
 * @brief get Functions.
 * getFunctions
 ***********************************************/
const std::map<std::string, Function> &SymbolTable::getFunctions() const
{
    return myFunctions;
}
/************************************************
 * @brief get Scripts.
 * getScripts
 ***********************************************/
const std::map<std::string, Script> &SymbolTable::getScripts() const
{
    return myScripts;
}
/************************************************
 * @brief get Variables.
 * getVariables
 ***********************************************/
const std::map<std::string, ArithmeticType> &SymbolTable::getVariables() const
{
    return myVariables;
}
/************************************************
 * @brief set Variable.
 * setVariable
 ***********************************************/
void SymbolTable::setVariable(const std::string &name, ArithmeticType value)
{
    if (name.empty())
        throw std::runtime_error("Symbol name cannot be empty.");

    myConstants.erase(name);
    myFunctions.erase(name);
    myScripts.erase(name);
    myVariables[name] = value;
}
/************************************************
 * @brief set Constant.
 * setConstant
 ***********************************************/
void SymbolTable::setConstant(const std::string &name, ArithmeticType value)
{
    if (name.empty())
        throw std::runtime_error("Symbol name cannot be empty.");

    myVariables.erase(name);
    myFunctions.erase(name);
    myScripts.erase(name);
    myConstants[name] = value;
}
/************************************************
 * @brief set Function.
 * setFunction
 ***********************************************/
void SymbolTable::setFunction(const std::string &name, const Function &value)
{
    if (name.empty())
        throw std::runtime_error("Symbol name cannot be empty.");

    myVariables.erase(name);
    myConstants.erase(name);
    myScripts.erase(name);
    myFunctions[name] = value;
}
/************************************************
 * @brief set Script.
 * setScript
 ***********************************************/
void SymbolTable::setScript(const std::string &name, const Script &value)
{
    if (name.empty())
        throw std::runtime_error("Symbol name cannot be empty.");

    myVariables.erase(name);
    myConstants.erase(name);
    myFunctions.erase(name);
    myScripts[name] = value;
}
/************************************************
 * @brief has Variable.
 * hasVariable
 ***********************************************/
bool SymbolTable::hasVariable(const std::string &name)
{
    return myVariables.find(name) != myVariables.end();
}
/************************************************
 * @brief has Constant.
 * hasConstant
 ***********************************************/
bool SymbolTable::hasConstant(const std::string &name)
{
    return myConstants.find(name) != myConstants.end();
}
/************************************************
 * @brief has Function.
 * hasFunction
 ***********************************************/
bool SymbolTable::hasFunction(const std::string &name)
{
    return myFunctions.find(name) != myFunctions.end();
}
/************************************************
 * @brief has Script.
 * hasScript
 ***********************************************/
bool SymbolTable::hasScript(const std::string &name)
{
    return myScripts.find(name) != myScripts.end();
}
/************************************************
 * @brief remove.
 * remove
 ***********************************************/
void SymbolTable::remove(const std::string &name)
{
    if (name.empty())
        throw std::runtime_error("Symbol name cannot be empty.");

    myVariables.erase(name);
    myConstants.erase(name);
    myFunctions.erase(name);
    myScripts.erase(name);
}
/************************************************
 * @brief clear.
 * clear
 ***********************************************/
void SymbolTable::clear()
{
    myVariables.clear();
    myConstants.clear();
    myFunctions.clear();
    myScripts.clear();
}
/*** ************************* End of File ***********************************/
