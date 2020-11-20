#include <iostream>

//............................TYPELIST............................//

template<typename T>
struct Unit {
    T _obj;
};

class Nulltype {
};

template<typename ...Args>
struct TypeList {
    using Head = Nulltype;
    using Tail = Nulltype;
};

template<typename H, typename ...T>
struct TypeList<H, T...> {
    using Head = H;
    using Tail = TypeList<T...>;
};

typedef TypeList<> EmptyTypeList;

template<typename H>
struct TypeList<H> {
    using Head = H;
    using Tail = EmptyTypeList;
};

template<size_t ind, typename ...T>
struct TypeAt {
    using res = Nulltype;
};

template<size_t ind, typename ...T>
struct TypeAt<ind, TypeList<T...>> {
    using res = typename TypeAt<ind - 1, typename TypeList<T...>::Tail>::res;
};

template<size_t ind>
struct TypeAt<ind, Nulltype> {
    using res = Nulltype;
};

template<typename ...T>
struct TypeAt<0, TypeList<T...>> {
    using res = typename TypeList<T...>::Head;
};

template<size_t val, size_t deg>
struct Pow {
    static const size_t res = Pow<val, deg - 1>::res * val;
};

template<size_t val>
struct Pow<val, 0> {
    static const size_t res = 1;
};

