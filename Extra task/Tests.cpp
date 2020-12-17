#include <iostream>
#include "BasicDispatcher.h"
#include "StaticDispatcher.h"
#include "TestClasses.h"

int main()
{
    Animal* cat1 = new Cat;
    Animal* dog1 = new Dog;
    Animal* dog2 = new Dog;
    Animal* cat2 = new Cat;
    Animal* catdog1 = new CatDog;

    std::cout << std::endl << typeid(*cat1).name() << " " << typeid(Cat).name() << std::endl;
    std::cout << std::endl;

    StaticDispatcher<Meeting, Animal, TypeList< Dog, Cat, CatDog > >::Go(catdog1, cat1);

    BasicDispatcher<Animal, Animal> bdAnim;
    bdAnim.add<Dog, Dog>(MeetDog);
    bdAnim.add<Cat, Dog>(MeetCatDog);
    //bdAnim.add<Dog, Cat>(MeetCatDog);
    bdAnim.add<Cat, Cat>(MeetCat);

    bdAnim.Go(cat1, dog1);
    bdAnim.Go(cat1, cat2);

    // Переписать BasicDispatcher на unordered_map
    // Реализовать симметричный StaticDispatcher

    // TypeList <dog, cat, catdog>
    // meet (d,d), (d,c), (d,cd), (c,c), (c,cd), (cd,cd)
}