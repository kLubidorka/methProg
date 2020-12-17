#pragma once


class Nulltype {};

template <typename ...Args>
struct TypeList
{
    using Head = Nulltype;
    using Tail = Nulltype;
};

typedef TypeList<> EmptyTypeList;

template <typename H, typename ...T>
struct TypeList<H, T...>
{
    using Head = H;
    using Tail = TypeList<T...>;
};


template <typename H>
struct TypeList<H>
{
    using Head = H;
    using Tail = EmptyTypeList;
};
