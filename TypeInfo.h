//
// Created by kagudkov on 02.04.17.
//

#ifndef RTTI_TYPEINFO_H
#define RTTI_TYPEINFO_H

#include <cstdio>
#include <stdlib.h>
#include <map>
#include <vector>


struct TypeInfo{
    TypeInfo(std::string _name = "") {
        name = _name;
    }
    bool operator==(const TypeInfo& other) const{
        return name == other.name;
    }
    bool operator!=(const TypeInfo& other) const{
        return name != other.name;
    }
    std::string name;
    int GetHash(){
        return std::hash<std::string>()(name);
    }
};

static std::map<std::string, TypeInfo> TypeInfoForClasses;
static std::map<std::string, std::vector<std::string> > graph;

#define NEW(T, o) new T();                             \
TypeInfoForClasses[std::string(#o)] = TypeInfo(#T); \


#define TYPEID(o) TypeInfoForClasses[std::string(#o)]

#endif //RTTI_TYPEINFO_H
