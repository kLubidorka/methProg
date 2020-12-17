#ifndef SYMMETRICDISPATCHER_TESTCLASSES_H
#define SYMMETRICDISPATCHER_TESTCLASSES_H

#include "iostream"

class Animal
{
    virtual void voice() = 0;
};

class Dog
        :public virtual Animal
{
    virtual void voice() override
    {
        std::cout << "Bark" << std::endl;
    }
};

class Cat
        :public virtual Animal
{
    virtual void voice() override
    {
        std::cout << "Meow" << std::endl;
    }
};

class CatDog
        :public virtual Cat,
         public virtual Dog
{
    virtual void voice() override
    {
        std::cout << "Who am I?????" << std::endl;
    }
};

class Meeting
{
public:
    static void meet(Dog* one, Dog* two)
    {
        std::cout << "Bark Bark" << std::endl;
    }

    static void meet(Dog* one, Cat* two)
    {
        std::cout << "Bark Meow" << std::endl;
    }

    static void meet(Cat* one, Dog* two)
    {
        std::cout << "Bark Meow" << std::endl;
    }

    static void meet(Cat* one, Cat* two)
    {
        std::cout << "Meow Meow" << std::endl;
    }

    static void meet(Dog* one, CatDog* two)
    {
        std::cout << "Who are you?" << std::endl;
    }

    static void meet(CatDog* one, Dog* two)
    {
        std::cout << "Who are you?" << std::endl;
    }
    static void meet(Cat* one, CatDog* two)
    {
        std::cout << "Who are you?" << std::endl;
    }

    static void meet(CatDog* one, Cat* two)
    {
        std::cout << "Who are you?" << std::endl;
    }

    static void meet(CatDog* one, CatDog* two)
    {
        std::cout << "Who are you?" << std::endl;
    }


    static void meet(...)
    {
        std::cout << "Something bad happend" << std::endl;
    }
};

void MeetDog(Animal* one, Animal* two)
{
    std::cout << "Bark Bark" << std::endl;
}

void MeetCatDog(Animal* one, Animal* two)
{
    std::cout << "Meow Bark" << std::endl;
}

void MeetCat(Animal* one, Animal* two)
{
    std::cout << "Meow Meow" << std::endl;
}

#endif //SYMMETRICDISPATCHER_TESTCLASSES_H
