// Logan Wasnidge
// CSII-Project-Zoo.cpp 
// 5/16/2020
//Manage a Zoo system; Simplistic

#include <iostream>
#include<map>
#include<set>
#include<string>
#include<vector>
#include"Animal.h"
#include"Facility.h"
#include"Staff.h"
#include"Calculate.h"

using namespace std;

int iAnimal, iFacility, iStaff; //Iterator Numbers for IDs

void manageFacility(vector<Facility*>& ourFacilities);
void manageAnimal(vector<Animal*>& ourAnimals);
void manageStaff(vector<Staff*>& ourStaff);
int main()
{
	long profit;
	long animalPrice = 0;
	long staffPrice = 0;
	long priceBuild = 0, profitFac = 0;
	vector<Facility*> ourFacilities;  //Vector holding all facilities made from the Facility class
	vector<Animal*> ourAnimals;		//Vector holding Animal objects from animal class
	vector<Staff*> ourStaff;		//Vector holding staff objects from Staff class
	
	cout << "Welcome to your new Zoo!" << endl;

	string exit;
	int select;

	do {
		cout << "Would you like to (1) Manage Facilities, (2) Manage Animals, or (3) Manage Staff ";
		
		cin >> select;		
		switch (select) {		//Switch statement to all you to choose which function you wish to enter
		case 1:manageFacility(ourFacilities);
			break;
		case 2:manageAnimal(ourAnimals);
			break;
		case 3:manageStaff(ourStaff);
			break;
		default:		//In case user does not choose number, it defaults to invalid choice
			cout << "Invalid choice." << endl;
		}

		cout << "Do you wish to continue with the zoo?(Y for yes, otherwise exit) ";
		cin >> exit;


	} while (exit == "Y" || exit == "y");

	for (unsigned int i = 0; i < ourFacilities.size(); i++) {		//Here i store the values of the price to build all facilities, and the average profit of all facilites
		profitFac += ourFacilities[i]->getAverageProfit();
		priceBuild += ourFacilities[i]->getPriceToBuild();
	}
	

	for (unsigned int i = 0; i < ourAnimals.size(); i++) {		//Store the price of all the animals
		animalPrice += ourAnimals[i]->getPrice();
	}

	
	for (unsigned int i = 0; i < ourStaff.size(); i++) {		//store the price of the yearly Salaries of all employees.
		staffPrice += ourStaff[i]->getSalary();
	}

	Calculate BuildingProfit(profitFac);		//I made a calculate class specifically to do operator overloading since I was having a hard time doing so with my other class;
	Calculate BuildingBuild(priceBuild);

	Calculate AnimalPrice(animalPrice);

	Calculate StaffPrice(staffPrice);


	profitFac = profitFac * 20;
	staffPrice = staffPrice * 20;
	profit = profitFac - staffPrice - priceBuild - animalPrice; // Here I calculate the total price over 20 years. The facility profits and staff prices would rise while the building and animal price would not increase since it is a one time fee.  The resulting numbers are not real numbers;


	Calculate totalProfit = BuildingProfit - BuildingBuild - AnimalPrice - StaffPrice;



	cout << "Total profit for the first year is " << totalProfit.getNumber() << endl;
	cout << "If you were to stay open for 20 years, your profit would be " << profit << endl;  //This number will depend on how you set up your zoo. IF you set it up to have a lot more staff and animals than facilities, then you will get far into the negatives. Ideally, you will have around a 4:1 ratio of facilites to some employees.

	system("pause");
	return 0;
}

void manageFacility(vector<Facility*>& ourFacilities) {
	int facSelect, intSelect;
	unsigned int foodType, location, habitatType, des;
	int totalBuild, totalProf;
	string name;
	string exit;
	
	
	do {
		cout << "Would you like to (1) add a facility, (2) check all facilities? ";  //These Funtions were going to include a function that invokes the destructor and decrememnts the incrementor while also using operator overloading to 
																					//decrement all objects that had an ID greater than that of the deleted item. I scrapped this idea becuse the vector size did not change. I could, in theory, make a new vector, 
																					//but if I did that, then I would have to create a vector of vectors and change the vector within the vector everytime the user deleted and readd to the new vector. This would make things too messy.
																					//That being said, I left the operator overloading within the classes, but I do not know how to properly use them in this program
		cin >> facSelect;
		cout << "\n" << endl;
		switch (facSelect) {
		case 1:

			cout << "What kind of Facility do you want to make?" << endl;
			cout << "(1) Food Facility, (2) Bathroom, (3) Habitat, (4) Gift Shop. ";


			cin >> intSelect;
			cout << "\n" << endl;

			switch (intSelect) {
			case 1:
				iFacility++;  //Iterator for Faculty ID

				cout << "Choose food facility type" << endl;		//These loops show the facility types along with the cost to build and the profit per year for each facility.
				for (map<FoodFacility::FoodType, string>::iterator it = FoodFacility::FoodTypeMap.begin(); it != FoodFacility::FoodTypeMap.end(); it++) {
					cout << "\t" << it->first << ": " << it->second << endl;
				}
				cout << "With the corresponding price to build" << endl;
				for (map<FoodFacility::FoodType, long>::iterator it = FoodFacility::PriceToBuildFoodMap.begin(); it != FoodFacility::PriceToBuildFoodMap.end(); it++) {
					cout << "\t" << it->first << ": $" << it->second << endl;
				}
				cout << "And with the corresponding profit per year" << endl;
				for (map<FoodFacility::FoodType, long>::iterator it = FoodFacility::AverageProfitMap.begin(); it != FoodFacility::AverageProfitMap.end(); it++) {
					cout << "\t" << it->first << ": $" << it->second << endl;
				}
				cin >> foodType;


				try { // exception handling
					if (foodType > FoodFacility::FoodTypeMap.size() || foodType < 1 || !cin) {
						string a = "Quantity must be > 0 and less than " + to_string(FoodFacility::FoodTypeMap.size() + 1);
						throw invalid_argument(a);
					}
				}
				catch (invalid_argument & a) {
					while (foodType > FoodFacility::FoodTypeMap.size() || foodType < 1 || !cin) {
						cin.clear();
						cin.ignore(1000, '\n');
						cout << a.what() << endl;
						cin >> foodType;
					}
				}


				cout << "What do you want to name this food facility? ";
				cin >> name;		//Allow user to name facility for our constructor
				cout << "\n" << endl;
			

				ourFacilities.push_back(new FoodFacility(name, FoodFacility::FoodType(foodType), iFacility));
				cout << "\n" << endl;
				break;


			case 2:
				iFacility++;
				cout << "Bathrooms have a profit of -$2500 a year, and price at $10000 to build." << endl;
				cout << "Choose location of bathroom facility" << endl;		//Only some facilities did I allow you to choose the location. This was for ease mainly.  This shows the locations that you can put the facilties.
				for (map<Facility::Location, string>::iterator it = Facility::LocationMap.begin(); it != Facility::LocationMap.end(); it++) {
					cout << "\t" << it->first << ": " << it->second << endl;
				}
				cin >> location;

				try { // exception handling
					if (location > Facility::LocationMap.size() || location < 1 || !cin) {
						string b = "Quantity must be > 0 and less than " + to_string(Facility::LocationMap.size() + 1);
						throw invalid_argument(b);
					}
				}
				catch (invalid_argument & b) {
					while (location > Facility::LocationMap.size() || location < 1 || !cin) {
						cin.clear();
						cin.ignore(1000, '\n');
						cout << b.what() << endl;
						cin >> location;
					}
				}

				ourFacilities.push_back(new Bathroom(iFacility,Bathroom::Location(location)));

				break;


			case 3:
				iFacility++;

				cout << "Choose type of Habitat you wish to make." << endl;
				cout << "Each habitat costs $22,500 to build, and profit $7500 a year." << endl;  //Shows the types of habitats you could make. 
				for (map<Habitat::HabitatType, string>::iterator it = Habitat::HabitatTypeMap.begin(); it != Habitat::HabitatTypeMap.end(); it++) {
					cout << "\t" << it->first << ": " << it->second << endl;
				}
				
				cin >> habitatType;

				try { // exception handling
					if (habitatType > Habitat::HabitatTypeMap.size() || habitatType < 1 || !cin) {
						string e = "Quantity must be > 0 and less than " + to_string(Habitat::HabitatTypeMap.size() + 1);
						throw invalid_argument(e);
					}
				}
				catch (invalid_argument & e) {
					while (habitatType > Habitat::HabitatTypeMap.size() || habitatType < 1 || !cin) {
						cin.clear();
						cin.ignore(1000, '\n');
						cout << e.what() << endl;
						cin >> habitatType;
					}
				}

				cout << "Choose location of your habitat facility" << endl;  //More habitat location showing
				for (map<Facility::Location, string>::iterator it = Facility::LocationMap.begin(); it != Facility::LocationMap.end(); it++) {
					cout << "\t" << it->first << ": " << it->second << endl;
				}

				cin >> location;

				try { // exception handling
					if (location > Facility::LocationMap.size() || location < 1 || !cin) {
						string c = "Quantity must be > 0 and less than " + to_string(Facility::LocationMap.size() + 1);
						throw invalid_argument(c);
					}
				}
				catch (invalid_argument & c) {
					while (location > Facility::LocationMap.size() || location < 1 || !cin) {
						cin.clear();
						cin.ignore(1000, '\n');
						cout << c.what() << endl;
						cin >> location;
					}
				}

				ourFacilities.push_back(new Habitat(iFacility, Habitat::Location(location), Habitat::HabitatType(habitatType)));

					break;
			case 4:
				iFacility++;
				cout << "Gift shops cost $25000 to build and profit $7500 a year." << endl;
				cout << "What do you want to name this facility? ";
				cin >> name;

				cout << "Choose location of your Gift Shop" << endl; //Locations
				for (map<Facility::Location, string>::iterator it = Facility::LocationMap.begin(); it != Facility::LocationMap.end(); it++) {
					cout << "\t" << it->first << ": " << it->second << endl;
				}

				cin >> location;

				try { // exception handling
					if (location > Facility::LocationMap.size() || location < 1 || !cin) {
						string d = "Quantity must be > 0 and less than " + to_string(Facility::LocationMap.size() + 1);
						throw invalid_argument(d);
					}
				}
				catch (invalid_argument & d) {
					while (location > Facility::LocationMap.size() || location < 1 || !cin) {
						cin.clear();
						cin.ignore(1000, '\n');
						cout << d.what() << endl;
						cin >> foodType;
					}
				}

				ourFacilities.push_back(new GiftShop(name, Habitat::Location(location), iFacility));

				break;

			default:
				cout << "Invalid choice." << endl;
			}
			break;
		

		case 2:
			totalBuild = 0;  //This case(2) shows the description of all Facilites, followed by a seperate list for each facilities cost to build, and average Profit per year.  These numbers were then compounded into a total of all facilites to build, and a total profit 
			totalProf = 0;
			for (unsigned int i = 0; i < ourFacilities.size(); i++) {
				cout << ourFacilities[i]->description() << endl;
			}
			cout << "Cost of all facilities to build: " << endl;
			for (unsigned int i = 0; i < ourFacilities.size(); i++) {
				cout << i << ". " << ourFacilities[i]->getPriceToBuild() << endl;
				totalBuild += ourFacilities[i]->getPriceToBuild();
			}
			
			cout << "\nYearly profit from all facilities: " << endl;
			for (unsigned int i = 0; i < ourFacilities.size(); i++) {
				cout << i +1 << ". " << ourFacilities[i]->getAverageProfit() << endl;
				totalProf += ourFacilities[i]->getAverageProfit();
			}

			cout << "\nTotal to build all Facilities: " << totalBuild << endl;
			cout << "Total yearly profit from all Facilities: " << totalProf << endl;
			cout << "\n" << endl;

			break;
		default:
			cout << "Invalid choice." << endl;
		}
		



		cout << "Do you wish to continue managing your facilities?(Y for yes, otherwise exit) ";
		cin >> exit;

	} while (exit == "Y" || exit == "y");

}
void manageAnimal(vector<Animal*>& ourAnimals) {
	int aSelect, tSelect;
	unsigned int animalType;
	double aPrice;
	string exit, name;

	do {
		cout << "Would you like to (1) Add an Animal or (2) See current animals? ";

		cin >> aSelect;
		switch (aSelect) {
		case 1:
			cout << "\nWhat kind of animal do you wish to add?" << endl;
			cout << "(1) A land animal, (2) A aquatic animal, or (3) a flying animal? ";  //3 types of animals the user can add

			cin >> tSelect;

			switch (tSelect) {

			case 1:
				iAnimal++;
				cout << "Choose an Animal Species" << endl;
				for (map<Land::landAnimal, string>::iterator it = Land::LandAnimalMap.begin(); it != Land::LandAnimalMap.end(); it++) {
					cout << "\t" << it->first << ": " << it->second << endl;
				}		//shows the species I included of the animls of the Land type

				cout << "With corresponding prices: " << endl;
				for (map<Land::landAnimal, double>::iterator it = Land::LandAnimalPriceMap.begin(); it != Land::LandAnimalPriceMap.end(); it++) {
					cout << "\t" << it->first << ": " << it->second << endl;
				}  //list of prices for each animal done seperatly.
				cin >> animalType;

				try { // exception handling
					if (animalType > Land::LandAnimalMap.size() || animalType < 1 || !cin) {
						string f = "Quantity must be > 0 and less than " + to_string(Land::LandAnimalMap.size() + 1);
						throw invalid_argument(f);
					}
				}
				catch (invalid_argument & f) {
					while (animalType > Land::LandAnimalMap.size() || animalType < 1 || !cin) {
						cin.clear();
						cin.ignore(1000, '\n');
						cout << f.what() << endl;
						cin >> animalType;
					}
				}

				cout << "Name your new animal " << endl;
				cin >> name;

				ourAnimals.push_back(new Land(iAnimal, name, Land::landAnimal(animalType)));
				break;



			case 2:

				iAnimal++;
				cout << "Choose an Animal Species" << endl;
				for (map<Sea::seaAnimal, string>::iterator it = Sea::SeaAnimalMap.begin(); it != Sea::SeaAnimalMap.end(); it++) {
					cout << "\t" << it->first << ": " << it->second << endl;
				} //shows the species I included of the animls of the Sea type. Sea isn't specifcally sea animals, but aquatic animals in general.

				cout << "With corresponding prices: " << endl;
				for (map<Sea::seaAnimal, double>::iterator it = Sea::SeaAnimalPriceMap.begin(); it != Sea::SeaAnimalPriceMap.end(); it++) {
					cout << "\t" << it->first << ": " << it->second << endl;
				} //prices for each animal type
				cin >> animalType;

				try { // exception handling
					if (animalType > Sea::SeaAnimalMap.size() || animalType < 1 || !cin) {
						string g = "Quantity must be > 0 and less than " + to_string(Sea::SeaAnimalMap.size() + 1);
						throw invalid_argument(g);
					}
				}
				catch (invalid_argument & g) {
					while (animalType > Sea::SeaAnimalMap.size() || animalType < 1 || !cin) {
						cin.clear();
						cin.ignore(1000, '\n');
						cout << g.what() << endl;
						cin >> animalType;
					}
				}

				cout << "Name your new animal " << endl;
				cin >> name;

				ourAnimals.push_back(new Sea(iAnimal, name, Sea::seaAnimal(animalType)));
				break;



			case 3:

				iAnimal++;
				cout << "Choose an Animal Species" << endl;
				for (map<Sky::skyAnimal, string>::iterator it = Sky::SkyAnimalMap.begin(); it != Sky::SkyAnimalMap.end(); it++) {
					cout << "\t" << it->first << ": " << it->second << endl;
				} //shows the species I included of the animals of the Sky type

				cout << "With corresponding prices: " << endl;
				for (map<Sky::skyAnimal, double>::iterator it = Sky::SkyAnimalPriceMap.begin(); it != Sky::SkyAnimalPriceMap.end(); it++) {
					cout << "\t" << it->first << ": " << it->second << endl;
				} //Price for each sky animal type
				cin >> animalType;

				try { // exception handling
					if (animalType > Sky::SkyAnimalMap.size() || animalType < 1 || !cin) {
						string h = "Quantity must be > 0 and less than " + to_string(Sky::SkyAnimalMap.size() + 1);
						throw invalid_argument(h);
					}
				}
				catch (invalid_argument & h) {
					while (animalType > Sky::SkyAnimalMap.size() || animalType < 1 || !cin) {
						cin.clear();
						cin.ignore(1000, '\n');
						cout << h.what() << endl;
						cin >> animalType;
					}
				}

				cout << "Name your new animal " << endl;
				cin >> name;

				ourAnimals.push_back(new Sky(iAnimal, name, Sky::skyAnimal(animalType)));
				break;


			default:
				cout << "Invalid Choice" << endl;
			}
		
			break;


		case 2:
			for (unsigned int i = 0; i < ourAnimals.size(); i++) {
				cout << ourAnimals[i]->description() << endl;
			}  //Displayed a description of each animal we made
			cout << "Total cost for all animals is: ";
			aPrice = 0;

			for (unsigned int i = 0; i < ourAnimals.size(); i++) {
				aPrice += ourAnimals[i]->getPrice();
			}

			cout << aPrice << endl;  //Gets the total cost for all animals we have.
			break;


		default:
			cout << "Invalid Choice" << endl;
		}

		cout << "Do you wish to continue managing your animals?(Y for yes, otherwise exit)";
		cin >> exit;

	} while (exit == "Y" || exit == "y");

};
void manageStaff(vector<Staff*>& ourStaff) {
	string exit;
	int sSelect, eSelect, rSelect;
	string fName, lName, pron, degree, pref;
	int expire, yoe, raise;


	do {
		cout << "Would you like to (1) add an employee or (2) check all employees ";

		cin >> sSelect;
		switch (sSelect) {
		case 1:
			iStaff++;
			

			cout << "\nEnter Staff Member first name ";
			cin >> fName;

			cout << "\nEnter Staff Memmber last name ";
			cin >> lName;

			cout << "\nEnter the pronoun the staff member goes by ";
			cin >> pron;												//Allow the user to set the name and pronoun of each staff memeber before going into class specific variables

			cout << "\nWhat kind of staff member do you wish to hire?" << endl;

			cout << "Positions:				Starting Salary:" << endl;
			cout << "1.  Vet					$75000	" << endl;
			cout << "2.  Zoologist				$45000	" << endl;
			cout << "3.  Janitor				$20000 " << endl;
			cout << "4.  Maintenance Worker			$30000 " << endl;
			cout << "5.  Keeper				$22000 " << endl;
			cout << "6.  StoreWorker				$12000 " << endl;
			cout << "7.  Manager				$20000 " << endl;

			cin >> eSelect;

			try { // exception handling
				if (eSelect > 6 || eSelect < 0 || !cin) {
					string i = "Quantity must be greater than 0 and less than or equal to 7";
					throw invalid_argument(i);
				}
			}
			catch (invalid_argument & i) {
				while (eSelect > 6 || eSelect < 0 || !cin) {
					cin.clear();
					cin.ignore(1000, '\n');
					cout << i.what() << endl;
					cin >> eSelect;
				}
			}

			switch (eSelect){

			case 1:
				cout << "Enter expiration year of " << fName << "'s liscense" << endl;
				cin >> expire;

				try { // exception handling
					if (expire < 2020 || !cin) {		//This exception is so we don't hire on someone with an expired liscense
						string j = "We are in the year 2020! "+ fName +"'s liscense couldn't have expired already.";
						throw invalid_argument(j);
					}
				}
				catch (invalid_argument & j) {
					while (expire < 2020 || !cin) {
						cin.clear();
						cin.ignore(1000, '\n');
						cout << j.what() << endl;
						cin >> expire;
					}
				}

				ourStaff.push_back(new Vet(fName, lName, iStaff, expire, pron));

				break;


			case 2:
				cout << "Enter the type of Degree the Zoologist has" << endl;
				cin >> degree;		// since oologists could have different types of degrees, I choose to inlude degree as a constructor so that they were different

				ourStaff.push_back(new Zoologist(fName, lName, iStaff, degree, pron));
				break;

			case 3:
				ourStaff.push_back(new Janitor(fName, lName, iStaff, pron));  //Janitor is plain and simple. No special skills required to be a Janitor
				break;

			case 4:
				cout << "Enter years of experience "<< fName << " has.(Must be at least 5) ";
				cin >> yoe;

				try { // exception handling
					if (yoe < 5 || yoe >= 107 || !cin) {  //This exception was so that we could hire people who had enough years of experience to be a mintenance person, while also making sure they weren't impossibly old.
						string k = "\nThe longest living peson lived to be 122, so they can't have over 107 years of experience. " + fName + " must also have a minimum of 5 years of experience under their belt to be promoted to Maintenance";
						throw invalid_argument(k);
					}
				}
				catch (invalid_argument & k) {
					while (yoe < 5 || yoe >= 107 || !cin) {
						cin.clear();
						cin.ignore(1000, '\n');
						cout << k.what() << endl;
						cin >> yoe;
					}
				}

				ourStaff.push_back(new Maintenance(fName, lName, iStaff, pron, yoe));
				break;

			case 5:
				cout << "What kind of animals does " << fName << " prefer to handle?";
				cin >> pref;				//I let my keepers choose their specific type of animals.

				ourStaff.push_back(new Keeper(fName, lName, iStaff, pron, pref));
				break;

			case 6:
				cout << "What kind of store does " << fName << " prefer to work at?";
				cin >> pref;			//Store workers would probably only work at 1 store at a given time.
				cout << "\n";

				ourStaff.push_back(new StoreWorker(fName, lName, iStaff, pron, pref));
				break;

			case 7:
				cout << "What kind of store does " << fName << " prefer to work at?";
				cin >> pref; //Managers would only manage 1 type of store.

				cout << "\nEnter years of experience " << fName << " has.(Must be at least 5) ";
				cin >> yoe;

				try { // exception handling
					if (yoe < 5 || yoe >= 107 || !cin) {
						string l = "\nThe longest living peson lived to be 122, so they can't have over 107 years of experience. " + fName + " must also have a minimum of 5 years of experience under their belt to be promoted to Manager";
						throw invalid_argument(l);
					}
				}
				catch (invalid_argument & l) {
					while (yoe < 5 || yoe >= 107 || !cin) {
						cin.clear();
						cin.ignore(1000, '\n');
						cout << l.what() << endl;
						cin >> yoe;
					}
				}

				ourStaff.push_back(new Manager(fName, lName, iStaff, pron, pref, yoe));
				break;

			default:
				cout << "Invalid Choice" << endl;
				break;
			}

			break;


		case 2:

			//Shows staff descriptions as well as how much they make.
			for (unsigned int i = 0; i < ourStaff.size(); i++) {
				cout << ourStaff[i]->description() << endl;
				cout << "Salary: " << ourStaff[i]->getSalary() << endl;
			}
			break;
		}

		

		cout << "Do you wish to continue managing staff?(Y for yes, otherwise exit) ";
		cin >> exit;

	} while (exit == "Y" || exit == "y");
	

};