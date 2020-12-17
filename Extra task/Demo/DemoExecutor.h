#ifndef SYMMETRICDISPATCHER_DEMOEXECUTOR_H
#define SYMMETRICDISPATCHER_DEMOEXECUTOR_H

#include "DemoClasses.h"

class Meeting {
public:
    static void meet(Dog *one, Dog *two) {
        std::cout << "Bark Bark" << std::endl;
    }

    static void meet(Dog *one, Cat *two) {
        std::cout << "Bark Meow" << std::endl;
    }

    static void meet(Cat *one, Dog *two) {
        std::cout << "Meow Bark" << std::endl;
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

#endif //SYMMETRICDISPATCHER_DEMOEXECUTOR_H
