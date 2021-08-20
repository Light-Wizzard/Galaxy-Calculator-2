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

#include "src/3rdparty/io/serializer.hpp"

#include "src/3rdparty/extern/json.hpp"
/************************************************
 * @brief serialize Table.
 * serializeTable
 ***********************************************/
std::string Serializer::serializeTable(const SymbolTable &table)
{
    nlohmann::json j;
    j["version"] = 0;

    std::vector<nlohmann::json> tmp;
    for (auto &p : table.getVariables())
    {
        nlohmann::json t;
        t["name"] = p.first;
        t["value"] = p.second.toString();
        tmp.emplace_back(t);
    }
    j["variables"] = tmp;
    tmp.clear();

    for (auto &p : table.getConstants())
    {
        nlohmann::json t;
        t["name"] = p.first;
        t["value"] = p.second.toString();
        tmp.emplace_back(t);
    }
    j["constants"] = tmp;
    tmp.clear();

    for (auto &p : table.getFunctions())
    {
        nlohmann::json t;
        t["name"] = p.first;
        t["expression"] = p.second.expression;
        t["argumentNames"] = p.second.argumentNames;
        tmp.emplace_back(t);
    }
    j["functions"] = tmp;
    tmp.clear();

    return nlohmann::to_string(j);
}
/************************************************
 * @brief deserialize Table.
 * deserializeTable
 ***********************************************/
SymbolTable Serializer::deserializeTable(const std::string &str, int precision)
{
    nlohmann::json j = nlohmann::json::parse(str);
    SymbolTable ret;

    std::vector<nlohmann::json> tmp = j["variables"].get<std::vector<nlohmann::json>>();
    for (auto &v : tmp)
    {
        std::string name = v["name"];
        ArithmeticType value;
        if (v["value"].is_string())
            value = mpfr::mpreal(v["value"].get<std::string>(), precision, 10, MPFR_RNDN);
        else
            value = mpfr::mpreal(v["value"].get<double>(), precision, MPFR_RNDN); //Backwards compat
        ret.setVariable(name, value);
    }

    tmp = j["constants"].get<std::vector<nlohmann::json>>();
    for (auto &v : tmp)
    {
        std::string name = v["name"];
        ArithmeticType value;
        if (v["value"].is_string())
            value = mpfr::mpreal(v["value"].get<std::string>(), precision, 10, MPFR_RNDN);
        else
            value = mpfr::mpreal(v["value"].get<double>(), precision, MPFR_RNDN); //Backwards compat
        ret.setConstant(name, value);
    }

    tmp = j["functions"].get<std::vector<nlohmann::json>>();
    for (auto &v : tmp)
    {
        std::string name;
        name = v["name"];
        Function f;
        f.expression = v["expression"];
        f.argumentNames = v["argumentNames"].get<std::vector<std::string>>();
        ret.setFunction(name, f);
    }

    return ret;
}
/************************************************
 * @brief serialize Settings.
 * serializeSettings
 ***********************************************/
std::string Serializer::serializeSettings(const Settings &settings)
{
    auto &data = settings.entries();
    nlohmann::json j;
    for (auto &p : data)
    {
        switch (p.second.type())
        {
            case Settings::NONE: //Ignore NONE type values.
                break;
            case Settings::INT:
                j[p.first] = p.second.toInt();
                break;
            case Settings::FLOAT:
                j[p.first] = p.second.toFloat();
                break;
            case Settings::STRING:
                j[p.first] = p.second.toString();
                break;
        }
    }
    return nlohmann::to_string(j);
}
/************************************************
 * @brief deserialize Settings.
 * deserializeSettings
 ***********************************************/
Settings Serializer::deserializeSettings(const std::string &str)
{
    Settings ret;
    nlohmann::json j = nlohmann::json::parse(str);
    for (auto &entry : j.items())
    {
        const std::string &key = entry.key();
        const auto &value = entry.value();
        if (value.is_number_integer())
        {
            ret.setValue(key, entry.value().get<int>());
        }
        else if (value.is_number_float())
        {
            ret.setValue(key, entry.value().get<float>());
        }
        else if (value.is_string())
        {
            ret.setValue(key, entry.value().get<std::string>());
        }
    }
    return ret;
}
/************************************************
 * @brief serialize Set.
 * serializeSet
 ***********************************************/
std::string Serializer::serializeSet(const std::set<std::string> &set)
{
    nlohmann::json j;
    j["data"] = set;
    return nlohmann::to_string(j);
}
/************************************************
 * @brief deserialize Set.
 * deserializeSet
 ***********************************************/
std::set<std::string> Serializer::deserializeSet(const std::string &str)
{
    nlohmann::json j = nlohmann::json::parse(str);
    return j["data"];
}
/************************************************
 * @brief serialize Rounding Mode.
 * serializeRoundingMode
 ***********************************************/
int Serializer::serializeRoundingMode(mpfr_rnd_t mode)
{
    return (int) mode;
}
/************************************************
 * @brief deserialize Rounding Mode.
 * deserializeRoundingMode
 ***********************************************/
mpfr_rnd_t Serializer::deserializeRoundingMode(int mode)
{
    switch (mode)
    {
        default:
        case (int) MPFR_RNDN: return MPFR_RNDN;
        case (int) MPFR_RNDZ: return MPFR_RNDZ;
        case (int) MPFR_RNDU: return MPFR_RNDU;
        case (int) MPFR_RNDD: return MPFR_RNDD;
        case (int) MPFR_RNDA: return MPFR_RNDA;
        case (int) MPFR_RNDF: return MPFR_RNDF;
    }
}
/*** ************************* End of File ***********************************/
