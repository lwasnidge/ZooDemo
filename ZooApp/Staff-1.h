#pragma once
#include <iostream>
#include<map>
#include<set>
#include<string>

using namespace std;

class Staff {
protected:
	string fName;
	string lName;
	string type; // type of employee
	string pron; //gender pronoun Just for he/she
	int salary; //salary of an employee
	int ID;
public:
	Staff(string fName, string lName, int ID, string type, string pron) {  //
		this->fName = fName;
		this->lName = lName;
		this->ID = ID;
		this->pron = pron;
	}
	//~Staff() {
	//	cout << "Firing staff" << endl;  //Was meant for when I figured out how to destroyed objects from a vectore, but I couldn't get it done.
	//}
	int getID() {
		return ID;
	}
	string getName() {  //Combines first and last name to get the staff's full name
		string name = fName + " " + lName;
		return name;
	}
	int getSalary() {
		return salary;
	}
	string description() {
		string result = "Employee ID: " + to_string(ID) + " named " + getName() + " is a " + type + " and " + pron + work();
		return result;
	}
	virtual string work() = 0;

};
class Vet : public Staff {
private:
	int expire; //Year Vet liscence expires
public:
	Vet(string fName, string lName, int ID, int expire, string pron) : Staff(fName, lName, ID, "Vetrinarian", pron) {
		this->fName = fName;
		this->lName = lName;
		this->ID = ID;
		this->expire = expire;  //Special  case just for Vets. This is just when their liscence expires.
		this->pron = pron;
		type = "Vetrinarian";
		salary = 75000;
		cout << "Hiring Vet" << endl;
	}
	int getExpire() {
		return expire;
	}
	string work() {
		return " treats animals.";
	}
	//Vet& operator+=(int raise) { Second attempt at operator overloading. As you can tell, I don't have a huge grasp on how it works.  This was supposed to be for a raise.
	//	salary += raise;
	//	return *this;
	//}
};
class Zoologist : public Staff {
private:
	string degree; //Degree type that the Zoologist has

public:
	Zoologist(string fName, string lName, int ID, string degree, string pron) : Staff(fName, lName, ID, "Zoologist", pron) {
		this->fName = fName;
		this->lName = lName;
		this->ID = ID;
		this->degree = degree; //Type of degree.
		this->pron = pron;
		type = "Zoologist";
		salary = 45000;
		cout << "Hiring Zoologist" << endl;
	}
	string getDegree() {
		return degree;
	}
	string work() {
		return " studies animals.";
	}
	Zoologist& operator+=(int raise) {
		salary += raise;
		return *this;
	}
};
class Janitor : public Staff {
public:
	Janitor(string fName, string lName, int ID, string pron) : Staff(fName, lName, ID, "Janitor", pron) {
		this->fName = fName;
		this->lName = lName;
		this->ID = ID;
		this->pron = pron;
		type = "Janitor";
		salary = 20000;
		cout << "Hiring Janitor" << endl;
	}
	virtual string work() {
		return " cleans facilities";
	}
	//Janitor& operator+=(int raise) {
	//	salary += raise;
	//	return *this;
	//}
};
class Maintenance : public Janitor {
private:
	int yearsOfExperience;
public:
	Maintenance(string fName, string lName, int ID, string pron, int yearsOfExperience) : Janitor(fName, lName, ID, pron) {
		this->yearsOfExperience = yearsOfExperience; //This allows a minimun years of experience for a maintenance worker. This was orignially for promotion purposes, but I don't know how to 'promote' within a class, if thats even possible.
		this->fName = fName;
		this->lName = lName;
		this->ID = ID;
		this->pron = pron;
		type = "Maintenance Worker";
		salary = 30000;
		cout << "Hiring Maintenance worker" << endl;
	}
	string work() {
		return " cleans and maintains facilities";
	}
	//Maintenance& operator+=(int raise) {
	//	salary += raise;
	//	return *this;
	//}
};
class Keeper : public Staff {
private:
	string preferredAnimalTypes;//types of animals the keeper wishes to take care of
public:
	Keeper(string fName, string lName, int ID, string pron,string preferredAnimalTypes) : Staff(fName, lName, ID, "Keeper", pron) {
		this->preferredAnimalTypes = preferredAnimalTypes;  //Animals the keeper prefers to work with. This was to assign keepers to habitats, but I was unsure of how to do that too.
		this->fName = fName;
		this->lName = lName;
		this->ID = ID;
		this->pron = pron;
		type = "Keeper";
		salary = 22000;
		cout << "Hiring Keeper" << endl;
	}
	string getAnimalPref() {
		return preferredAnimalTypes;
	}
	string work() {
		return " takes care of the animals";
	}
	Keeper& operator+=(int raise) {
		salary += raise;
		return *this;
	}
};
class StoreWorker : public Staff {  //Facility workers, like food and giftshop facilities
protected:
	string preferredStore;//types of animals the keeper wishes to take care of
public:
	StoreWorker(string fName, string lName, int ID, string pron, string preferredStore) : Staff(fName, lName, ID, "Keeper", pron) {
		this->preferredStore = preferredStore; //store that the worker wishes to work at. You probably won't be working at too many stores.
		this->fName = fName;
		this->lName = lName;
		this->ID = ID;
		this->pron = pron;
		salary = 12000;
		cout << "Store Worker" << endl;
	}
	string getStorePref() {
		return preferredStore;
	}
	virtual string work() {
		return " works at the stores";
	}
	StoreWorker& operator+=(int raise) {
		salary += raise;
		return *this;
	}
};
class Manager : public StoreWorker {  //Facility workers, like food and giftshop facilities
protected:
	int yoe;
public:
	Manager(string fName, string lName, int ID, string pron, string preferredStore, int yoe) : StoreWorker(fName, lName,  ID,  pron, preferredStore) {
		this->preferredStore = preferredStore; //Preferred store
		this->fName = fName;
		this->lName = lName;
		this->ID = ID;						//at least 5 years of experience to be a manager
		this->pron = pron;
		this->yoe = yoe;
		type = "Manager";
		salary = 20000;
		cout << "Hiring Keeper" << endl;
	}
	string getStorePref() {
		return preferredStore;
	}
	string work() {
		return " manages the stores";
	}
	Manager& operator+=(int raise) {
		salary += raise;
		return *this;
	}
};