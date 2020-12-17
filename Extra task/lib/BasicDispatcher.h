#ifndef SYMMETRICDISPATCHER_BASICDISPATCHER_H
#define SYMMETRICDISPATCHER_BASICDISPATCHER_H

#include <iostream>
#include <unordered_map>
#include <typeindex>

struct HashIndex {
    size_t operator()(const std::pair<std::type_index, std::type_index> &pr) const {
        static std::hash<std::type_index> z;
        return z(pr.first) * 31 + z(pr.second);
    }
};

template<class BaseLhs, class BaseRhs, typename ResultType = void, typename CallbackType = ResultType (*)(BaseLhs *,
                                                                                                          BaseRhs *)>
class BasicDispatcher {
    using KeyType = std::pair<std::type_index, std::type_index>;
    using MappedType = CallbackType;
    using MapType = std::unordered_map<KeyType, MappedType, HashIndex>;

    MapType callbackMap;

public:

    template<class TypeLhs, class TypeRhs>
    void add(CallbackType fun) {
        callbackMap.emplace(KeyType(typeid(TypeLhs), typeid(TypeRhs)), fun);
    }

    template<class TypeLhs, class TypeRhs>
    void remove() {
        callbackMap.erase(KeyType(typeid(TypeLhs), typeid(TypeRhs)));
    }

    ResultType Go(BaseLhs *lhs, BaseRhs *rhs) {
        KeyType k(typeid(*lhs), typeid(*rhs));
        typename MapType::iterator it = callbackMap.find(k);
        if (it == callbackMap.end()) {
            std::cerr << "Error. Types not found";
        }

        return (it->second)(lhs, rhs);
    }
};

#endif //SYMMETRICDISPATCHER_BASICDISPATCHER_H
