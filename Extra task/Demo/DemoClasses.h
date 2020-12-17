#ifndef SYMMETRICDISPATCHER_DEMOCLASSES_H
#define SYMMETRICDISPATCHER_DEMOCLASSES_H

#include "iostream"

class Animal {
    virtual void voice() = 0;
};

class Dog : public virtual Animal {
    void voice() override {
        std::cout << "Bark" << std::endl;
    }
};

class Cat : public virtual Animal {
    void voice() override {
        std::cout << "Meow" << std::endl;
    }
};

class CatDog : public virtual Cat,
               public virtual Dog {
    void voice() override {
        std::cout << "Who am I?????" << std::endl;
    }
};

#endif //SYMMETRICDISPATCHER_DEMOCLASSES_H
