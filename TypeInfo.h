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


const bool operator <(const std::pair<std::string, int> &a, const std::pair<std::string, int>& b) {
    if( a.first != b.first){
        return  a.first < b.first;
    }
    return a.second < b.second;
}

static std::map<std::string, TypeInfo> TypeInfoForClasses;
static std::map<std::string, std::map< std::string, int > > graph;

struct registrar{
    registrar(std::string derived, std::string base, int offset ){
        if(graph.find(derived) == graph.end()){
            graph[derived] = std::map< std::string, int >();
        }
        if(graph.find(base) == graph.end()){
            graph[base] = std::map< std::string, int >();
            graph[base][base] = 0;
        }
        graph[derived][derived] = 0;
        for( auto i = graph[base].begin(); i != graph[base].end(); ++i ){
            graph[derived][i->first] = -offset;
        }
    }
};

#define NEW(B, T, o) new T();                             \
TypeInfoForClasses[std::string(#o)] = TypeInfo(#T);


#define TYPEID(o) TypeInfoForClasses[std::string(#o)]

#define EXTENDS(D, B) D : B { \
registrar r = registrar(#D, #B, 0);

#define MEXTENDS(D, B1, B2) D : B1, B2 { \
registrar r1 = registrar(#D, #B1, 0); \
registrar r2 = registrar(#D, #B2, sizeof(B1) );

#define DYNAMIC_CAST(R, T, a) (assert( graph.find(TYPEID(a).name) != graph.end() ),  \
assert( graph[TYPEID(a).name].find(#T) != graph[TYPEID(a).name].end() ),\
static_cast<T*>( static_cast< R *>(a)))//(char*)(a) + graph[TYPEID(a).name][#R]))


#endif //RTTI_TYPEINFO_H
