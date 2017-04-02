//
// Created by kagudkov on 02.04.17.
//

#ifndef RTTI_TYPEINFO_H
#define RTTI_TYPEINFO_H

#include <cstdio>
#include <stdlib.h>
#include <map>
#include <vector>
#include <set>
#include <assert.h>


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
static std::map<std::string, std::set<std::string> > graph;

struct registrar{
    registrar(std::string derived, std::string base){
        if(graph.find(derived) == graph.end()){
            graph[derived] = std::set<std::string>();
        }
        if(graph.find(base) == graph.end()){
            graph[base] = std::set<std::string>();
            graph[base].insert(base);
        }
        graph[derived].insert(derived);
        for( auto i = graph[base].begin(); i != graph[base].end(); ++i ){
            graph[derived].insert(*i);
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

#define DYNAMIC_CAST(T, a) (assert( graph.find(TYPEID(a).name) != graph.end() ),  \
assert( graph[TYPEID(a).name].find(#T) != graph[TYPEID(a).name].end() ),\
reinterpret_cast<T*>(a) )


#endif //RTTI_TYPEINFO_H
