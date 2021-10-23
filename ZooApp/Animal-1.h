#pragma once
#include <iostream>
#include<map>
#include<set>
#include<string>
#include"Facility.h"

using namespace std;

class Animal {
private:
    string type;
public:
    Animal(string type) {
        this->type = type;
    }
    string getType() { 
        return type;
    }
    virtual double getPrice() = 0; //Gives price of each animal
    virtual string getSpecies() = 0; //Gives animal species
    virtual string getName() = 0; //gives animal name
    virtual string description() = 0; //Abstract class methods. These probably could've been done in this class instead of all of them being = 0. When I started, this is where I started and I was still shakey on doing abstraction. 
};
class Land : public Animal {
public:
    enum landAnimal{Monkey = 1, Lion, Penguin, Alligator, Camel, Wolf};
    static map<landAnimal, string> LandAnimalMap;
    static map<landAnimal, Habitat::HabitatType> LandAnimalHabitatMap;//Mapped types of habitats based on the Facility habitats to each animal. Was surprised when it actually worked.
    static map<landAnimal, double> LandAnimalPriceMap;//Mapped an animal to a price for each animal.
private:
    int animalID;
    string name;
    landAnimal animal;
public:
    Land(int animalID, string name, landAnimal animal) : Animal("Land Animal"){

        this->animalID = animalID;
        this->name = name;
        this->animal = animal;
        cout << "Creating Land Animal" << endl;
    }
    double getPrice() {
        return LandAnimalPriceMap[animal];
    }
    string getSpecies() {
        return LandAnimalMap[animal];
    }
    string getName() {
        return name;
    }
    string description() {
        string results = name + " is a " + LandAnimalMap[animal] + " that's habitat is " + Habitat::HabitatTypeMap[LandAnimalHabitatMap[animal]];  //Animals name, followed by the type it is and what type of habitat it lives in.
        return results;
    }
};

class Sea : public Animal {
public: 
    enum seaAnimal{Shark=1, Whale, Dolphin, Guppy, Plecostomus, Rainbow};
    static map<seaAnimal, string> SeaAnimalMap;
    static map<seaAnimal, Habitat::HabitatType> SeaHabitatMap; //Mapped types of habitats based on the Facility habitats to each animal.
    static map<seaAnimal, double> SeaAnimalPriceMap;//Mapped an animal to a price for each animal.
private:
    int animalID;
    string name;
    seaAnimal animal;
public:
    Sea(int animalID, string name, seaAnimal animal) : Animal("Sea Animal") {
        this->animalID = animalID;
        this->name = name;
        this->animal = animal;
        cout << "Creating Sea Animal" << endl;
    }
    double getPrice() {
        return SeaAnimalPriceMap[animal];
    }
    string getSpecies() {
        return SeaAnimalMap[animal];
    }
    string getName() {
        return name;
    }
    string description() {
        string results = name + " is a " + SeaAnimalMap[animal] + " that's habitat is " + Habitat::HabitatTypeMap[SeaHabitatMap[animal]];//Animals name, followed by the type it is and what type of habitat it lives in.
        return results;
    }
};

class Sky : public Animal {
public:
    enum skyAnimal { Eagle=1, Hawk, Condor, Bat, Flamingo, Bee};
    static map<skyAnimal, string> SkyAnimalMap;
    static map<skyAnimal, Habitat::HabitatType> SkyHabitatMap;//Mapped types of habitats based on the Facility habitats to each animal.
    static map<skyAnimal, double> SkyAnimalPriceMap;//Mapped an animal to a price for each animal. Added bee colony instead of just a bee since a bee would cost signifigantly less.
private:
    int animalID;
    string name;
    skyAnimal animal;
public:
    Sky(int animalID, string name, skyAnimal animal) : Animal("sky Animal") {
        this->animalID = animalID;
        this->name = name;
        this->animal = animal;
        cout << "Creating Sea Animal" << endl;
    }
    double getPrice() {
        return SkyAnimalPriceMap[animal];
    }
    string getSpecies() {
        return SkyAnimalMap[animal];
    }
    string getName() {
        return name;
    }
    string description() {
        string results = name + " is a " + SkyAnimalMap[animal] + " that's habitat is " + Habitat::HabitatTypeMap[SkyHabitatMap[animal]];//Animals name, followed by the type it is and what type of habitat it lives in.
        return results;
    }
};


map<Land::landAnimal, string> Land::LandAnimalMap{ {Monkey, "Monkey"}, {Lion,"Lion"}, {Penguin, "Penguin"}, {Alligator, "Alligator"}, {Camel, "Camel"}, {Wolf, "Wolf"} };
map<Land::landAnimal, Habitat::HabitatType> Land::LandAnimalHabitatMap{ {Monkey, Habitat::Forest}, {Lion,Habitat::Grasslands}, {Penguin, Habitat::Artic}, {Alligator, Habitat::Wetland}, {Camel, Habitat::Desert}, {Wolf, Habitat::Tundra} };
map<Land::landAnimal, double> Land::LandAnimalPriceMap{ {Monkey, 5000}, {Lion, 7500}, {Penguin, 10000}, {Alligator,3000}, {Camel, 10000}, {Wolf, 2000} }; 

map<Sea::seaAnimal, string> Sea::SeaAnimalMap{ {Shark, "Shark"},{Whale, "Whale"}, {Dolphin,"Dolphin"}, {Guppy, "Guppy"}, {Plecostomus, "Plecostomus"}, {Rainbow, "Rainbow Fish"} };
map<Sea::seaAnimal, Habitat::HabitatType> Sea::SeaHabitatMap{ {Shark, Habitat::Salt},{Whale, Habitat::Salt}, {Dolphin, Habitat::Salt}, {Guppy, Habitat::Fresh}, {Plecostomus, Habitat::Fresh}, {Rainbow, Habitat::Fresh} };
map<Sea::seaAnimal, double> Sea::SeaAnimalPriceMap{ {Shark, 15000},{Whale, 30000}, {Dolphin, 20000}, {Guppy, 25}, {Plecostomus, 6}, {Rainbow, 12} };

map<Sky::skyAnimal, string> Sky::SkyAnimalMap{ { Eagle, "Eagle"}, {Hawk, "Hawk"}, {Condor, "Condor"}, {Bat, "Bat"}, {Flamingo, "Flamingo"}, {Bee,"Bees Colony" } };
map<Sky::skyAnimal, Habitat::HabitatType> Sky::SkyHabitatMap{ {Eagle, Habitat::Air},{Hawk, Habitat::Air}, {Condor, Habitat::Air}, {Bat, Habitat::Cave}, {Flamingo, Habitat::Grasslands}, {Bee, Habitat::Hive} };
map<Sky::skyAnimal, double> Sky::SkyAnimalPriceMap{ {Eagle, 1500},{Hawk, 75}, {Condor, 200}, {Bat, 1000}, {Flamingo , 150}, {Bee, 200} };
