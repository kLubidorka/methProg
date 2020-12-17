#include <iostream>
#include "StaticAsymmetricDispatcher.h"
#include "StaticSymmetricDispatcher.h"
#include "DemoClasses.h"
#include "DemoExecutor.h"

int main() {
    Animal *cat = new Cat;
    Animal *catdog = new CatDog;

    // Who are you? Meow
    // Meow Who are you?
    StaticAsymmetricDispatcher<Meeting, Animal, TypeList<Dog, Cat, CatDog> >::Go(catdog, cat);
    StaticAsymmetricDispatcher<Meeting, Animal, TypeList<Dog, Cat, CatDog> >::Go(cat, catdog);

    // Who are you? Meow
    // Who are you? Meow
    StaticSymmetricDispatcher<Meeting, Animal, TypeList<Dog, Cat, CatDog> >::Go(catdog, cat);
    StaticSymmetricDispatcher<Meeting, Animal, TypeList<Dog, Cat, CatDog> >::Go(cat, catdog);
}