#ifndef SYMMETRICDISPATCHER_TESTMEETINGEXECUTOR_H
#define SYMMETRICDISPATCHER_TESTMEETINGEXECUTOR_H

#include "TestClasses.h"

class Meeting {
public:
    static void meet(Dog *one, Dog *two) {
        std::cout << "Bark Bark" << std::endl;
    }

    static void meet(Dog *one, Cat *two) {
        std::cout << "Bark Meow" << std::endl;
    }

    static void meet(Cat *one, Dog *two) {
        std::cout << "Bark Meow" << std::endl;
    }

    static void meet(Cat *one, Cat *two) {
        std::cout << "Meow Meow" << std::endl;
    }

    static void meet(Dog *one, CatDog *two) {
        std::cout << "Who are you?" << std::endl;
    }

    static void meet(CatDog *one, Dog *two) {
        std::cout << "Who are you?" << std::endl;
    }

    static void meet(Cat *one, CatDog *two) {
        std::cout << "Who are you?" << std::endl;
    }

    static void meet(CatDog *one, Cat *two) {
        std::cout << "Who are you?" << std::endl;
    }

    static void meet(CatDog *one, CatDog *two) {
        std::cout << "Who are you?" << std::endl;
    }

    static void meet(...) {
        std::cout << "Something bad happend" << std::endl;
    }
};

#endif //SYMMETRICDISPATCHER_TESTMEETINGEXECUTOR_H
