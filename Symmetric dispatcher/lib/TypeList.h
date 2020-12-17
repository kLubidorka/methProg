#ifndef SYMMETRICDISPATCHER_TYPELIST_H
#define SYMMETRICDISPATCHER_TYPELIST_H

class Nulltype {
};

template<typename ...Args>
struct TypeList {
    using Head = Nulltype;
    using Tail = Nulltype;
};

typedef TypeList<> EmptyTypeList;

template<typename H, typename ...T>
struct TypeList<H, T...> {
    using Head = H;
    using Tail = TypeList<T...>;
};


template<typename H>
struct TypeList<H> {
    using Head = H;
    using Tail = EmptyTypeList;
};

template <typename U, typename ...T>
struct IndexOf
{
    static const size_t value = 1;
};

//////////////////////////////// IndexOf ////////////////////////////////

template <typename ...K, typename U>
struct IndexOf<U, TypeList<K...>>
{
    static const size_t value = 1 + IndexOf<U, typename TypeList<K...>::Tail>::value;
};

template <typename T, typename ...K>
struct IndexOf<TypeList<T, K...>, T>
{
    static const size_t value = 0;
};
#endif //SYMMETRICDISPATCHER_TYPELIST_H
