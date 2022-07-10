#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;


/**
This structure is to store the date and it has three integer fields
**/
struct Date{
	int day;
	int month;
	int year;
};
/**
This structure is to store the size of the boat and it has three int fields
**/
struct SizeOfBoat{
    int length;
    int	width;
    int height;
};
/**
This structure is to store name of the diver
**/
struct Name{
    string firstName;
    string lastName;
};
/**
This structure is to store which equipment the diver will need provided
**/
struct EquipmentNeeded{
    char wetsuit;
    char regulator;
    char o2tank;
};
/**
This structure is to store location coordinates
**/
struct Coordinate{
    double latitude;
    double longitutde;
};
/**
This structure is to store the Diver info
**/
struct Diver{
    Name name;
    Date dob;
    long long int emPhoneNum;
    string certLevel;
    string certAgency;
    EquipmentNeeded equipNeeded;
};
/**
This structure is to store the Boat info
**/
struct Boat{
    string name;
    SizeOfBoat boatSize;
    int personCap;
    int fuelCap;
};
/**
This structure is to store the Dive Location info
**/
struct DiveLocation{
    string name;
    Coordinate diveCoord;
    int visability;
};
/**
This structure is to store the dive equipment info
**/
struct Equipment {
   string equipType;
   string condition;
   Date datePurchased;
};

///Function Prototypes
int readDivers(Diver *&divers, int &arrSize);
int readBoats(Boat *&boats, int &arrSize);
int readLocations(DiveLocation *&diveLocation, int &arrSize);
int readEquips(Equipment *&equipment, int &arrSize);

void printDivers(Diver divers[], int arrSize);
void printBoats(Boat boats[], int arrSize);
void printLocations(DiveLocation diveLocation[], int arrSize);
void printEquips(Equipment equipment[], int arrSize);

Name getDiverName();
void printPhoneNumber(Diver *divers, int diversSize, Name name);

int main()
{
    ///Create Null pointers and size to pass to READ functions
    Diver *divers = 0;
    int diversSize = 0;
    Boat *boats = 0;
    int boatsSize = 0;
    DiveLocation *diveLocations = 0;
    int diveLocationSize = 0;
    Equipment *equipment = 0;
    int equipmentSize = 0;


    ///Call the read functions
    if(readDivers(divers, diversSize))
        return 1;
    if(readBoats(boats,boatsSize))
        return 1;
    if(readLocations(diveLocations, diveLocationSize))
        return 1;
    if(readEquips(equipment, equipmentSize))
        return 1;


    /**
    Display the prompt and do the requested action. Keep repeating the prompt until exit.
    If the number entered is not an option, just repeat the prompt.
    **/
    int chosenOption;
    Name toPrint;
    do{
        cout << "\n"
         << "1. Print all Divers \n"
         << "2. Print all Boats \n"
         << "3. Print all Dive Locations \n"
         << "4. Print all Equipment \n"
         << "5. Search for a Diver's emergency contact info \n"
         << "6. Exit \n"
         << "\n"
         << "Enter Option (1-5): ";
        cin >> chosenOption;
        /**
        Do the correct action according to the chosenOption
        **/
        switch(chosenOption)
        {
        case 1:
            printDivers(divers, diversSize);
            break;
        case 2:
            printBoats(boats, boatsSize);
            break;
        case 3:
            printLocations(diveLocations, diveLocationSize);
            break;
        case 4:
            printEquips(equipment, equipmentSize);
            break;
        case 5:
            toPrint = getDiverName();
            printPhoneNumber(divers, diversSize, toPrint);
            break;
        default:
            break;
        }

    }while(chosenOption != 6);

    return 0;
}

void printDivers(Diver *divers, int arrSize){
    cout << "Divers--------------------------------------------------------------------\n";
    cout << "Name\t\t DOB \t Emergency Phone Cert Lvl   Cert Agency\t Equip Needed\n";
    for (int i =0; i < arrSize; i++){
        cout << divers[i].name.firstName << " " << divers[i].name.lastName << "\t" << left << setw(2) <<
        divers[i].dob.month << "/" << setw(2) << divers[i].dob.day << "/" << setw(7) <<divers[i].dob.year <<
        divers[i].emPhoneNum <<  "\t" << setw(19) << divers[i].certLevel <<divers[i].certAgency <<  "\t" <<
        divers[i].equipNeeded.wetsuit << ":" <<  divers[i].equipNeeded.regulator << ":" << divers[i].equipNeeded.o2tank << endl;

    }
}
void printBoats(Boat *boats, int arrSize){
    cout << "Boats--------------------------------------------------------------------\n";
    cout << "Boat Name\tLocation     Person Cap Fuel Cap\n";
    for(int i=0; i < arrSize; i++){
        cout << left <<setw(15) << boats[i].name << "\t" << setw(2) <<boats[i].boatSize.height << ":" << setw(2) <<boats[i].boatSize.width << ":" << setw(2) <<boats[i].boatSize.length
            << "\t" << boats[i].personCap << "\t" << boats[i].fuelCap << endl;
    }
}
void printLocations(DiveLocation *diveLocation, int arrSize){
    cout << "Dive-Locations---------------------------------------------------------\n";
    cout << "Location\tCoordinates\tVisability\n";
    for(int i=0; i < arrSize; i++){

        cout << setw(14) << diveLocation[i].name << "\t" << diveLocation[i].diveCoord.latitude << ":" << diveLocation[i].diveCoord.longitutde << "\t"
        << diveLocation[i].visability << endl;
    }
}
void printEquips(Equipment *equipment, int arrSize){
    cout << "Equipment----------------------------------------------------------------\n";
    cout << setw(11) << "Type" << setw(10) << "Condition" << "\t\tDate\n";
    for(int i=0; i < arrSize; i++){
        cout << setw(11) << equipment[i].equipType << "\t" << setw(10) << equipment[i].condition << "\t"
        << equipment[i].datePurchased.month << "/" << equipment[i].datePurchased.day << "/" << equipment[i].datePurchased.year << endl;
    }

}

int readDivers(Diver *&divers, int &arrSize){
    ///Open the input files
    fstream diverFile("Divers.txt");

    /**
    If the any of the file cannot be opened then the program terminates displaying
    the error message
    **/
    if (!diverFile)
    {
        cout << "The Diver input file does not exist. Program terminates!" << endl;
        return 1;
    }

    ///Get Size Of array and create the array
    diverFile >> arrSize;
    divers = new Diver[arrSize];

    ///Take in the information from the file
    char trash;
    for(int i =0; i < arrSize; i++){
        diverFile >> divers[i].name.firstName >> divers[i].name.lastName
        >> divers[i].dob.month >> trash >> divers[i].dob.day >> trash >> divers[i].dob.year
        >> divers[i].emPhoneNum
        >> divers[i].certLevel
        >> divers[i].certAgency
        >> divers[i].equipNeeded.wetsuit
        >> trash
        >> divers[i].equipNeeded.regulator
        >> trash
        >> divers[i].equipNeeded.o2tank;
    }
    ///close the file
    diverFile.close();

    return 0;
}
int readBoats(Boat *&boats, int &arrSize){
    ///Open the input files
    fstream boatFile("Boats.txt");

    /**
    If the any of the file cannot be opened then the program terminates displaying
    the error message
    **/
    if (!boatFile)
    {
        cout << "The Boat input file does not exist. Program terminates!" << endl;
        return 1;
    }
    ///Get Size Of array and create the array
    boatFile >> arrSize;
    boats = new Boat[arrSize];

    ///Take in the information from the file
    char trash;
    for(int i =0; i < arrSize; i++){
        boatFile >> boats[i].name >> boats[i].boatSize.height >> trash >> boats[i].boatSize.width >> trash >> boats[i].boatSize.length
        >> boats[i].personCap >> boats[i].fuelCap;
    }
    ///close the file
    boatFile.close();
    return 0;
}
int readLocations(DiveLocation *&diveLocations, int &arrSize){
    ///Open the input files
    fstream locationFile("DiveLocations.txt");

    /**
    If the any of the file cannot be opened then the program terminates displaying
    the error message
    **/
    if (!locationFile)
    {
        cout << "The Dive Location input file does not exist. Program terminates!" << endl;
        return 1;
    }
    ///Get Size Of array and create the array
    locationFile >> arrSize;
    diveLocations = new DiveLocation[arrSize];

    ///Take in the information from the file
    char trash;
    for(int i =0; i < arrSize; i++){
        locationFile >> diveLocations[i].name >> diveLocations[i].diveCoord.latitude >> trash >> diveLocations[i].diveCoord.longitutde
        >> diveLocations[i].visability;
    }
    ///close the file
    locationFile.close();
    return 0;

}
int readEquips(Equipment *&equipment, int &arrSize){
    ///Open the input files
    fstream equipFile("Equipment.txt");

    /**
    If the any of the file cannot be opened then the program terminates displaying
    the error message
    **/
    if (!equipFile)
    {
        cout << "The Equipment input file does not exist. Program terminates!" << endl;
        return 1;
    }
    ///Get Size Of array and create the array
    equipFile >> arrSize;
    equipment = new Equipment[arrSize];

    ///Take in the information from the file
    char trash;
    for(int i=0; i < arrSize; i++){
        equipFile >> equipment[i].equipType >> equipment[i].condition
        >> equipment[i].datePurchased.month >> trash >> equipment[i].datePurchased.day >> trash >> equipment[i].datePurchased.year;
    }

    ///close the file
    equipFile.close();
    return 0;

}

Name getDiverName(){
    Name nameToFind;
    cout << "\nWhat is the diver's Name? First Last: ";
    cin >> nameToFind.firstName >> nameToFind.lastName;

    return nameToFind;
}

void printPhoneNumber(Diver *divers,int diversSize, Name name){

    bool found = false;
    for(int i = 0; i< diversSize; i++){
        if(divers[i].name.firstName == name.firstName && divers[i].name.lastName == name.lastName){
            cout << "Phone number: " << divers[i].emPhoneNum << endl;
            found = true;
        }
    }

    if(!found){
        cout << "\nDiver not located.\n";
    }
}
