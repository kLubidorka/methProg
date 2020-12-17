#include <iostream>
#include "StaticDispatcher.h"
#include "StaticSymmetricDispatcher.h"
#include "TestClasses.h"
#include "TestMeetingExecutor.h"

int main() {
    Animal *cat = new Cat;
    Animal *dog = new Dog;
    Animal *catdog = new CatDog;

    //StaticDispatcher<Meeting, Animal, TypeList<Dog, Cat, CatDog>, Animal, TypeList<Cat>>::Go(catdog, cat);

    StaticDispatcher<Meeting, Animal, TypeList<Dog, Cat, CatDog> >::Go(dog, cat);
    StaticDispatcher<Meeting, Animal, TypeList<Dog, Cat, CatDog> >::Go(cat, dog);

    StaticSymmetricDispatcher<Meeting, Animal, TypeList<Dog, Cat, CatDog> >::Go(dog, cat);
    StaticSymmetricDispatcher<Meeting, Animal, TypeList<Dog, Cat, CatDog> >::Go(cat, dog);
}