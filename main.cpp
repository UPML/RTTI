#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <map>

struct TypeInfo{
    TypeInfo(std::string _name) {
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

template <typename T>
struct MetaTypeInfo
{
    static TypeInfo getTypeInfo()
    {
        return T::TYPE_NOT_REGISTERED__USE_RTTR_DECLARE_META_TYPE();
    }
};

TypeInfo registerOrGetType(const char* _name){
    std::string name = std::string(_name);
    return TypeInfo(name);
}

#define RTTR_DECLARE_META_TYPE(T)                       \
template<>                                              \
struct MetaTypeInfo< T >                                \
{                                                       \
  static TypeInfo getTypeInfo()                   \
  {                                                     \
       static const TypeInfo val = registerOrGetType(#T);  \
       return val;      \
  }                                                     \
};


RTTR_DECLARE_META_TYPE(int)
RTTR_DECLARE_META_TYPE(bool)

template<typename T>
static TypeInfo getTypeInfoFromInstance(const T*)
{
    return MetaTypeInfo<T>::getTypeInfo();
}

int main() {
    int *k;
    bool *b;
    std::cout << getTypeInfoFromInstance(k).name << "\n";
    std::cout << getTypeInfoFromInstance(k).GetHash() << "\n";
    std::cout << std::to_string( getTypeInfoFromInstance(k) == getTypeInfoFromInstance(b) ) << "\n";
    return 0;
}