#include <iostream>
#include "StaticAsymmetricDispatcher.h"
#include "StaticSymmetricDispatcher.h"
#include "DemoClasses.h"
#include "DemoExecutor.h"

int main() {
    Animal *cat = new Cat;
    Animal *dog = new Dog;
    Animal *catdog = new CatDog;

    //StaticAsymmetricDispatcher<Meeting, Animal, TypeList<Dog, Cat, CatDog>, Animal, TypeList<Cat>>::Go(catdog, cat);

    StaticAsymmetricDispatcher<Meeting, Animal, TypeList<Dog, Cat, CatDog> >::Go(dog, cat);
    StaticAsymmetricDispatcher<Meeting, Animal, TypeList<Dog, Cat, CatDog> >::Go(cat, dog);

    StaticSymmetricDispatcher<Meeting, Animal, TypeList<Dog, Cat, CatDog> >::Go(dog, cat);
    StaticSymmetricDispatcher<Meeting, Animal, TypeList<Dog, Cat, CatDog> >::Go(cat, dog);
}