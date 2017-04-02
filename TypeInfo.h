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

struct registrar{
    registrar(std::string derived, std::string base){
        if(graph.find(base) == graph.end()){
            graph[base] = std::vector<std::string>();
        }
        graph[base].push_back(derived);
        for(auto i = graph.begin(); i != graph.end(); ++i){
            for( int j = 0; j < i->second.size(); ++j){
                if(i->second[j] == base){
                    graph[i->first].push_back(derived);
                }
            }
        }
    }
};

#define NEW(T, o) new T();                             \
TypeInfoForClasses[std::string(#o)] = TypeInfo(#T);


#define TYPEID(o) TypeInfoForClasses[std::string(#o)]

#define EXTENDS(D, B) D : B { \
registrar r = registrar(#D, #B);

#define MEXTENDS(D, B1, B2) D : B1, B2 { \
registrar r1 = registrar(#D, #B1); \
registrar r2 = registrar(#D, #B2);


#endif //RTTI_TYPEINFO_H
