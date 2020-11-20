#include <iostream>

///............................TYPELIST............................///

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

///............................AUXILARY_INSTRUMENTS............................///

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

template<size_t line>
struct NodesUnderThisLine {
    static const size_t res = NodesUnderThisLine<line - 1>::res + Pow<3, static_cast<size_t>(0.5 * (line + 1))>::res;
};

template<>
struct NodesUnderThisLine<1> {
    static const size_t res = 3;
};

template<>
struct NodesUnderThisLine<0> {
    static const size_t res = 0;
};

template<size_t line, size_t triplet_idx>
struct NextIndexForEven {
    static const size_t value = triplet_idx * 3 + Pow<3, static_cast<size_t>(0.5 * (line + 1))>::res
                                - NodesUnderThisLine<line - 1>::res * 2;
};

enum LineEvenness {
    EVEN,
    ODD
};

///............................CUSTOM_HIERARCHY............................///

template<typename T>
struct Unit {
    T _obj;
};

template<typename Tlist, typename Type, size_t line, size_t triplet_idx, LineEvenness evenness, template<class> class Unit>
struct Generator {
};

template<typename ...T, size_t line, size_t triplet_idx, template<class> class Unit>
struct Generator<TypeList<T...>, Nulltype, line, triplet_idx, LineEvenness::EVEN, Unit> {
    using unittype = Nulltype;
};

template<typename ...T, size_t line, size_t triplet_idx, template<class> class Unit>
struct Generator<TypeList<T...>, Nulltype, line, triplet_idx, LineEvenness::ODD, Unit> {
    using unittype = Nulltype;
};

template<typename ...T, typename Type, size_t line, size_t triplet_idx, template<class> class Unit>
struct Generator<TypeList<T...>, Type, line, triplet_idx, LineEvenness::EVEN, Unit> :
        public Unit<Type>,
        public Generator<TypeList<T...>,
                typename TypeAt<NextIndexForEven<line, triplet_idx>::value, TypeList<T...>>::res,
                line + 1, NextIndexForEven<line, triplet_idx>::value, LineEvenness::ODD, Unit>,
        public Generator<TypeList<T...>,
                typename TypeAt<NextIndexForEven<line, triplet_idx>::value + 1, TypeList<T...>>::res,
                line + 1, NextIndexForEven<line, triplet_idx>::value + 1, LineEvenness::ODD, Unit>,
        public Generator<TypeList<T...>,
                typename TypeAt<NextIndexForEven<line, triplet_idx>::value + 2, TypeList<T...>>::res,
                line + 1, NextIndexForEven<line, triplet_idx>::value + 2, LineEvenness::ODD, Unit> {
    using unittype = Unit<Type>;

    using left = Generator<TypeList<T...>,
            typename TypeAt<NextIndexForEven<line, triplet_idx>::value, TypeList<T...>>::res,
            line + 1, NextIndexForEven<line, triplet_idx>::value, LineEvenness::ODD, Unit>;
    using mid = Generator<TypeList<T...>,
            typename TypeAt<NextIndexForEven<line, triplet_idx>::value + 1, TypeList<T...>>::res,
            line + 1, NextIndexForEven<line, triplet_idx>::value + 1, LineEvenness::ODD, Unit>;
    using right = Generator<TypeList<T...>,
            typename TypeAt<NextIndexForEven<line, triplet_idx>::value + 2, TypeList<T...>>::res,
            line + 1, NextIndexForEven<line, triplet_idx>::value + 2, LineEvenness::ODD, Unit>;
};

template<typename ...T, typename Type, size_t line, size_t triplet_idx, template<class> class Unit>
struct Generator<TypeList<T...>, Type, line, triplet_idx, LineEvenness::ODD, Unit> :
        public Unit<Type>,
        public Generator<TypeList<T...>, typename TypeAt<
                triplet_idx + Pow<3, static_cast<size_t>(0.5 * (line + 1))>::res, TypeList<T...>>::res,
                line + 1, triplet_idx + Pow<3, static_cast<size_t>(0.5 * (line + 1))>::res, LineEvenness::EVEN, Unit> {

    using unittype = Unit<Type>;
    using next = Generator<TypeList<T...>, typename TypeAt<
            triplet_idx + Pow<3, static_cast<size_t>(0.5 * (line + 1))>::res, TypeList<T...>>::res,
            line + 1, triplet_idx + Pow<3, static_cast<size_t>(0.5 * (line + 1))>::res, LineEvenness::EVEN, Unit>;
};


template<typename TList, template<class> class Unit>
struct GenCustomHierarchy {
};

template<typename ...TList, template<class> class Unit>
struct GenCustomHierarchy<TypeList<TList...>, Unit> :
        public Generator<TypeList<TList...>,
                typename TypeAt<0, TypeList<TList...>>::res, 1, 0, LineEvenness::ODD, Unit>,
        public Generator<TypeList<TList...>,
                typename TypeAt<1, TypeList<TList...>>::res, 1, 1, LineEvenness::ODD, Unit>,
        public Generator<TypeList<TList...>,
                typename TypeAt<2, TypeList<TList...>>::res, 1, 2, LineEvenness::ODD, Unit> {

    using left = Generator<TypeList<TList...>,
            typename TypeAt<0, TypeList<TList...>>::res, 1, 0, LineEvenness::ODD, Unit>;
    using mid = Generator<TypeList<TList...>,
            typename TypeAt<1, TypeList<TList...>>::res, 1, 1, LineEvenness::ODD, Unit>;
    using right = Generator<TypeList<TList...>,
            typename TypeAt<2, TypeList<TList...>>::res, 1, 2, LineEvenness::ODD, Unit>;
};

///............................TESTS............................///

template<size_t T>
struct Test {
    const static size_t idx = T;
};


int main() {
    GenCustomHierarchy<TypeList<
            Test<1>, Test<2>, Test<3>, Test<4>, Test<5>, Test<6>, Test<7>, Test<8>, Test<9>, Test<10>, Test<11>, Test<12>,
            Test<13>, Test<14>, Test<15>, Test<16>, Test<17>, Test<18>, Test<19>, Test<20>, Test<21>, Test<22>, Test<23>, Test<24>>, Unit>
    ::left::unittype sample1;
    std::cout << sample1._obj.idx << std::endl; // 1

    GenCustomHierarchy<TypeList<
            Test<1>, Test<2>, Test<3>, Test<4>, Test<5>, Test<6>, Test<7>, Test<8>, Test<9>, Test<10>, Test<11>, Test<12>,
            Test<13>, Test<14>, Test<15>, Test<16>, Test<17>, Test<18>, Test<19>, Test<20>, Test<21>, Test<22>, Test<23>, Test<24>>, Unit>
    ::left::next::right::unittype sample9;
    std::cout << sample9._obj.idx << std::endl; // 9

    GenCustomHierarchy<TypeList<
            Test<1>, Test<2>, Test<3>, Test<4>, Test<5>, Test<6>, Test<7>, Test<8>, Test<9>, Test<10>, Test<11>, Test<12>,
            Test<13>, Test<14>, Test<15>, Test<16>, Test<17>, Test<18>, Test<19>, Test<20>, Test<21>, Test<22>, Test<23>, Test<24>>, Unit>
    ::mid::next::mid::unittype sample11;
    std::cout << sample11._obj.idx << std::endl; // 11

    GenCustomHierarchy<TypeList<
            Test<1>, Test<2>, Test<3>, Test<4>, Test<5>, Test<6>, Test<7>, Test<8>, Test<9>, Test<10>, Test<11>, Test<12>,
            Test<13>, Test<14>, Test<15>, Test<16>, Test<17>, Test<18>, Test<19>, Test<20>, Test<21>, Test<22>, Test<23>, Test<24>>, Unit>
    ::right::next::left::next::unittype sample22;
    std::cout << sample22._obj.idx << std::endl; // 22

    GenCustomHierarchy<TypeList<
            Test<1>, Test<2>, Test<3>, Test<4>, Test<5>, Test<6>, Test<7>, Test<8>, Test<9>, Test<10>, Test<11>, Test<12>,
            Test<13>, Test<14>, Test<15>, Test<16>, Test<17>, Test<18>, Test<19>, Test<20>, Test<21>, Test<22>, Test<23>, Test<24>>, Unit>
    ::right::next::right::next::unittype sample24;

    std::cout << sample24._obj.idx << std::endl; // 24
}