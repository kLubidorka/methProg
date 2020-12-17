#ifndef SYMMETRICDISPATCHER_STATICDISPATCHER_H
#define SYMMETRICDISPATCHER_STATICDISPATCHER_H

#include "TypeList.h"
#include <typeinfo>

/**
 * Асимметричный статический диспетчер. Его задача состоит в реализации механизма вызова различных функций в
 * зависимости он динамического типа нескольких объектов, участвующих в вызове. Другими словами обеспечивается
 * динамический мультиобъектный полиморфизм.
 * Под асимметрией в данном случае понимается тот факт, что порядок аргументов важен для полиморфной функции.
 * f(A, B) != f(B, A)
 *
 * @tparam Executor -- объект, который выполняет полезную работу, в нем определены реализации полиморного
 * метода meet, для всех необходимых комбинаций параметров
 *
 * @tparam BaseLhs -- базовые типы аргументов левого операнда
 * @tparam TypesLhs -- список типов, состоящий из возможных производных классов типов аргументов левого операнда
 * @tparam BaseRhs -- базовые типы аргументов правого операнда
 * @tparam TypesRhs -- список типов, состоящий из возможных производных классов типов аргументов правого операнда
 * @tparam ResultType -- тип результата двойной диспетчеризации
 */
template<
        class Executor,
        class BaseLhs,
        class TypesLhs,
        class BaseRhs = BaseLhs,
        class TypesRhs = TypesLhs,
        typename ResultType = void>
class StaticDispatcher {
    typedef typename TypesLhs::Head Head;
    typedef typename TypesLhs::Tail Tail;
public:
    static ResultType Go(BaseLhs *lhs, BaseRhs *rhs) {
        if (typeid(Head) == typeid(*lhs)) {
            Head *p1 = dynamic_cast<Head *>(lhs);
            return StaticDispatcher<Executor, BaseLhs, TypesLhs, BaseRhs, TypesRhs, ResultType>::DispatchRhs(p1, rhs);
        } else {
            return StaticDispatcher<Executor, BaseLhs, Tail, BaseRhs, TypesRhs, ResultType>::Go(lhs, rhs);
        }
    }

    template<class SomeLhs>
    static ResultType DispatchRhs(SomeLhs *lhs, BaseRhs *rhs) {
        typedef typename TypesRhs::Head Head;
        typedef typename TypesRhs::Tail Tail;
        if (typeid(Head) == typeid(*rhs)) {
            Head *p2 = dynamic_cast<Head *>(rhs);
            return Executor::meet(lhs, p2);
        } else {
            return StaticDispatcher<Executor, SomeLhs, TypesLhs, BaseRhs, Tail, ResultType>::DispatchRhs(lhs, rhs);
        }
    }
};

template<
        class Executor,
        class BaseLhs,
        class BaseRhs,
        class TypesRhs,
        typename ResultType>
class StaticDispatcher<Executor, BaseLhs, Nulltype, BaseRhs, TypesRhs, ResultType> {
public:
    static ResultType Go(BaseLhs *lhs, BaseRhs *rhs) {
        return ResultType();
    }

    template<class SomeLhs>
    static ResultType DispatchRhs(SomeLhs *lhs, BaseRhs *rhs) {
        return ResultType();
    }
};

template<
        class Executor,
        class BaseLhs,
        class TypesLhs,
        class BaseRhs,
        typename ResultType>
class StaticDispatcher<Executor, BaseLhs, TypesLhs, BaseRhs, Nulltype, ResultType> {
    typedef typename TypesLhs::Head Head;
    typedef typename TypesLhs::Tail Tail;
public:
    static ResultType Go(BaseLhs *lhs, BaseRhs *rhs) {
        return ResultType();
    }

    template<class SomeLhs>
    static ResultType DispatchRhs(SomeLhs *lhs, BaseRhs *rhs) {
        return ResultType();
    }
};

#endif //SYMMETRICDISPATCHER_STATICDISPATCHER_H
