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

#ifndef QCALC_SYMBOLTABLE_HPP
#define QCALC_SYMBOLTABLE_HPP

#include <map>
#include <string>

#include "../math/function.hpp"
#include "../math/script.hpp"
#include "../math/arithmetictype.hpp"

/************************************************
 * @brief SymbolTable.
 * The symbol table is responsible for managing 4 map objects.
 * Each symbol(Variable, Constant, Function and Script) is identified by a name.
 *
 * A variable name cannot be a empty string.
 *
 * Only one symbol type per name may exist.
 * When setting a symbol of an existing name with different type the original symbol is deleted.
 * \class SymbolTable
 ***********************************************/
class SymbolTable
{
    public:
        SymbolTable();

        const std::map<std::string, ArithmeticType> &getVariables() const;

        const std::map<std::string, ArithmeticType> &getConstants() const;

        const std::map<std::string, Function> &getFunctions() const;

        const std::map<std::string, Script> &getScripts() const;

        void setVariable(const std::string &name, ArithmeticType value);

        void setConstant(const std::string &name, ArithmeticType value);

        void setFunction(const std::string &name, const Function &value);

        void setScript(const std::string &name, const Script &value);

        bool hasVariable(const std::string &name);

        bool hasConstant(const std::string &name);

        bool hasFunction(const std::string &name);

        bool hasScript(const std::string &name);

        void remove(const std::string &name);

        void clear();

    private:
        std::map<std::string, ArithmeticType> myVariables;
        std::map<std::string, ArithmeticType> myConstants;
        std::map<std::string, Function> myFunctions;
        std::map<std::string, Script> myScripts;
};

#endif //QCALC_SYMBOLTABLE_HPP
/*** ************************* End of File ***********************************/
