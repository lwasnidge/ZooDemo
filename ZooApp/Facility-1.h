#pragma once
#include <iostream>
#include<map>
#include<set>
#include<string>
#include"Animal.h"

using namespace std;

class Facility { //base Class
public:
	enum Location { North=1, South, East, West }; 
	static map <Location, string> LocationMap; //maps for location to a string
private:
	string type;
public:
	Facility(string type) {
		this->type = type;
	}
	~Facility() {
		cout << "Facility Destroyed." << endl;
	}
	string getType() {
		return type;
	}
	virtual long getPriceToBuild() = 0;
	virtual long getAverageProfit() = 0;
	virtual string getID() = 0; //getID is a simpler form of description. Gives a brief description of the Facilities for deletion purposes. (Deletion was removed due to complexity)
	virtual string description() = 0;
	
};
class FoodFacility : public Facility {  //Food Facilities
public:
	enum FoodType{BurgerDog = 1, Pizza, Sweet, Mexican, FoodCourt};
	static map <FoodType, string> FoodTypeMap;  //Food to strings
	static map <FoodType, long> PriceToBuildFoodMap; //Price to build each of the facilities
	static map <FoodType, long> AverageProfitMap;  //Profit made per year for each facility, does not include price to build subtraction in it.
private:
	string name;
	FoodType foodType;
	int foodID;
public:
	FoodFacility(string name, FoodType foodType, int foodID) : Facility("Food") {
		this->name = name;
		this -> foodType = foodType;
		this->foodID = foodID; //facility ID, just made unique for each constructor
		cout << "Creating Food Facility" << endl;
	}
	long getPriceToBuild() {
		return PriceToBuildFoodMap[foodType];
	}
	long getAverageProfit() {
		return AverageProfitMap[foodType];
	}
	string getID() {
		string result =  to_string(foodID) + ". Food facility '" + name + "'";
		return result;
	}
	string description() {
		string result = "Facility ID: " + to_string(foodID) + " named " + name + " is a " + FoodTypeMap[foodType] + " food facility at the zoo!";
		return result;
	}
	/*FoodFacility operator--(int){			My first attempt at operator overloading. Was going to be for deletion, but I removed it due to complexity
		foodID--;
		return *this;
	}
	FoodFacility& operator--() {
		foodID--;
		return *this;
	}*/
}; 
class Bathroom : public Facility {
public:
	static const long PriceOfBathroom = 10000; //const price to build a bathroom facility
private:
	Location location;
	int bathID;
public:
	Bathroom(int bathID, Location location) : Facility("Bathroom") {
		this->bathID = bathID;
		this->location = location;
		cout << "Creating Bathroom Facility" << endl;
	}
	long getPriceToBuild() {
		return PriceOfBathroom;
	}
	long getAverageProfit() {
		return -2500;  //bathrooms don't make profit, so they average a negative profit
	}
	string getID() {
		string result =  to_string(bathID) + ". Bathroom in the " + LocationMap[location];
		return result;
	}
	string description() {
		string result = "Facility ID: " + to_string(bathID) + " is a bathroom located in the " + LocationMap[location] + " part of the zoo.";
		return result;
	}
	/*Bathroom operator--(int) {
		bathID--;
		return *this;
	}
	Bathroom& operator--() {
		bathID--;
		return *this;
	}*/
};
class Habitat : public Facility {
	friend class Animal;
public:
	static const long HabitatPriceToBuild = 22500;  //Easier to just do standard price to build for each habitat.
	enum HabitatType {Forest = 1, Grasslands, Artic, Wetland, Desert, Tundra, Salt, Fresh, Air, Hive, Cave};
	static map<HabitatType, string> HabitatTypeMap; //Each type of habitat to string value.
private:
	Location location;
	HabitatType habitatType;
	int habitatID;
public:
	Habitat(int habitatID, Location location, HabitatType habitatType) : Facility("Habitat") {
		this->habitatID = habitatID;
		this->location = location;
		this->habitatType = habitatType;
		cout << "Creating Habitat Facility" << endl;
	}
	long getPriceToBuild() {
		return HabitatPriceToBuild;
	}
	long getAverageProfit() { //profit from having habitats. Is not an actual value.
		return 7500;
	}
	string getID() {
		string result =  to_string(habitatID) + ". " + HabitatTypeMap[habitatType] + " habitat in the " + LocationMap[location];
		return result;
	}
	string description() {
		string result = "Facility ID: " + to_string(habitatID) + " is a " + HabitatTypeMap[habitatType] + " habitat in the " + LocationMap[location] + " part of the zoo.";
		return result;
	}
	/*Habitat operator--(int) {
		habitatID--;
		return *this;
	}
	Habitat& operator--() {
		habitatID--;
		return *this;
	}*/
};
class GiftShop : public Facility {
private:
	Location location; 
	string name;
	int giftID;
public:
	GiftShop(string name, Location location, int giftID) : Facility("Gift Shop") {
		this->name = name;
		this->location = location;
		this->giftID = giftID; //even though each facility has its own ID name, they all represent the same thing
		cout << "Creating Gift Shop" << endl;
	}
	long getPriceToBuild() {
		return 25000;
	}
	long getAverageProfit() {
		return 10000;
	}
	string getID() {
		string result =  to_string(giftID) + ". Gift shop facility in the " + LocationMap[location] ;
		return result;
	}
	string description() {
		string result = "Facility ID: " + to_string(giftID) + " is a giftshop named " + name + " and is a located in the " + LocationMap[location] + " part of the zoo!";
			return result;
	}
	/*GiftShop operator--(int) {
		giftID--;
		return *this;
	}
	GiftShop& operator--() {
		giftID--;
		return *this;
	}*/
};




map <Facility::Location, string>Facility::LocationMap{ {North, "North"}, {South, "South"}, {East, "East"}, {West, "West"} };

map <FoodFacility::FoodType, string> FoodFacility::FoodTypeMap { {BurgerDog, "Burger and Hot Dog"}, {Pizza, "Pizza"}, {Sweet, "Sweet Treat"}, {Mexican, "Mexican Food"}, {FoodCourt, "Food Court"} };
map <FoodFacility::FoodType, long> FoodFacility::PriceToBuildFoodMap{ {BurgerDog, 20000}, {Pizza, 30000}, {Sweet, 25000}, {Mexican, 35000}, {FoodCourt, 38500} };
map <FoodFacility::FoodType, long> FoodFacility::AverageProfitMap{ {BurgerDog, 15000}, {Pizza, 17000}, {Sweet, 13000}, {Mexican, 18000}, {FoodCourt, 22000} };

map<Habitat::HabitatType, string> Habitat::HabitatTypeMap{ {Forest,"Forest"}, {Grasslands, "Grasslands"},{Artic, "Artic"}, {Wetland, "Wetland"} ,{Desert, "Desert"},{Tundra, "Tundra"}, {Salt, "Salt Water"}, {Fresh, "Fresh Water" }, {Air, "Bird Sanctuary"}, {Hive, "Bee Hive"}, {Cave, "Cave"} };
