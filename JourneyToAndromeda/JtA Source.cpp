
//Name: Jacinda Visser
//Program: Journey to Andromeda
//Description: Interactive Novel w/ multiple storylines
//Use: SIP project



#include <iostream>//standard- allows for cout/cin
#include <memory>//allows smart pointers
#include <cstdlib>//allows randomizer srand() function
#include <ctime>//allows for current time to be used to seed randomizer
#include <fstream>//allows file i/o
#include <string>//allows getline()
using namespace std;


//global variables-needed everywhere
string userChoice;//used for the user to make choices
int tripLength = 25;//used to determine length of user's trip

//resource variables
int money = 100;//player's money
int ship = 100; //ship condition (percentage)
int morale = 100; //crew morale (percentage)
int reputation = 0; //player's reputation (neg= ruthless, pos = compassionate)

//set (normal) pointers to resource vars - allows for easy value changing in functions/classes
int* pMoney = &money;
int* pShip = &ship;
int* pMorale = &morale;
int* pRep = &reputation;


//prints out the current status of resource values- to be used whenever status check is needed. No Rep b/c reputation is not shown to player- only affects story
void status(int* pMoney, int* pShip, int* pMorale) {
	cout << "\n\nCurrent status" << endl;
	cout << "Money: " << *pMoney << endl;
	//both shipC and morale are percentages so their status includes a %
	cout << "Ship Status: " << *pShip << "%" << endl;
	cout << "Crew Morale: " << *pMorale << "%\n\n" << endl;
}


//**test function to see reputation value**
void repStatus(int* pRep) {
	cout << "Reputation is: " << *pRep << endl;
}


//to be used whenever ship or morale change in a scenario to limit them to 100%
void limit(int* pShip, int* pMorale) {
	//if ship or morale get over 100, they are set to exactly 100- both resources are percentages
	if (*pShip > 100) {
		cout << "\n\nYour ship is fully up and running" << endl;
		*pShip = 100;
	}
	if (*pMorale > 100) {//if morale is over 100
		cout << "\n\nYour crew has never been happier" << endl;
		*pMorale = 100;//morale equals 100
	}
}

class GameStructure {//solo class- no parent or child classes
public:
	//to be placed where ever user makes a input in case they want help
	void Help() {
		if (userChoice == "h") {
			cout << "Input a lowercase 'a' or 'b' (or 'c' if you have 3 choices). The scenario will detail what response each of those inputs would represent. \nIf any of your resources hit zero, it is gameover. Choose carefully!\n\nIf you would like to see your current status again, input 's'." << endl;
		}
	}

	//to be placed where ever user makes a input in case they want another status update
	void StatusUpdateQ() {
		if (userChoice == "s") {
			//printout of current status
			status(pMoney, pShip, pMorale);
		}
	}
};

//for scenarios with no choices
class NoChoice {//parent class of the other 2 scenario classes
	//no private variables: all are used by child classes
protected://variable used by this and child classes
	string intro;//used for scenario introduction

	//variables for the ending (child classes will use them for their 1st ending)
	string end1;//used for the ending

	//used to define how much the resources change by add/subtract in the ending 
	int changeMoney1 = 0;
	int changeShip1 = 0;
	int changeMorale1 = 0;
	int changeRep1 = 0;

public:
	void setIntro(string setIntro) {//set intro
		intro = setIntro;
	}

	void setEnd1(string setEnd1, int setchangeMoney, int setchangeShip, int setchangeMorale, int setchangeRep) {//sets 1st ending with how the resources will change
		end1 = setEnd1;

		//set resource changes
		changeMoney1 = setchangeMoney;
		changeShip1 = setchangeShip;
		changeMorale1 = setchangeMorale;
		changeRep1 = setchangeRep;
	}

	string playScenario() { //scenario getter- displays scenario
		cout << intro << endl;//intro text
		cout << end1 << endl;//ending text

		*pMoney += changeMoney1;//update money var
		*pShip += changeShip1;//update ship var
		*pMorale += changeMorale1;//update morale var
		*pRep += changeRep1;//update rep var

		//run limit function in case ship or morale is over 100
		limit(pShip, pMorale);

		return intro, end1;//pointers don't need to be returned
	}
};

//for scenarios with 2 choices
class TwoChoice : public NoChoice {//child class of NoChoice
	//no private variables in this class- all vars are either from parent class or is used in child class

protected://variables used by this and child class
	//variables for the 2nd ending
	string end2;

	//used to define how much the resources change for the ending
	int changeMoney2 = 0;
	int changeShip2 = 0;
	int changeMorale2 = 0;
	int changeRep2 = 0;

public:
	void setEnd2(string setEnd2, int setchangeMoney, int setchangeShip, int setchangeMorale, int setchangeRep) {//sets 2nd ending with how the resources will change
		end2 = setEnd2;

		changeMoney2 = setchangeMoney;
		changeShip2 = setchangeShip;
		changeMorale2 = setchangeMorale;
		changeRep2 = setchangeRep;
	}

	string playScenario() {//runs scenario
		GameStructure twoC;//creates gamestructure class in order to use its functions(help and status)- only needs to be done once for twoChoice class
		cout << intro << endl;
		cin >> userChoice;

		while ((userChoice == "h") || (userChoice == "s")) {
			//run help in case user wants help
			twoC.Help();//calls help function- only works if userChoice is h

			//run statusupdateq in case user wants their status
			twoC.StatusUpdateQ();//calls the statusupdateq function itself- only works if userChoice is s

			cin >> userChoice;
		}

		//invalid input = try again
		while ((userChoice != "a") && (userChoice != "b")) {
			cout << "Invalid input. Please input 'a' or 'b'" << endl;
			cin >> userChoice;
		}

		//user chose 1st option/ending
		if (userChoice == "a") {
			cout << end1 << endl; //ending text

			//any updates to resource vars
			*pMoney += changeMoney1;//update money var
			*pShip += changeShip1;//update ship var
			*pMorale += changeMorale1;//update morale var
			*pRep += changeRep1; //update rep var
		}

		//user chose 2nd option/ending
		else if (userChoice == "b") {
			cout << end2 << endl; //ending text

			//any updates to resource vars
			*pMoney += changeMoney2;//update money var
			*pShip += changeShip2;//update ship var
			*pMorale += changeMorale2;//update morale var
			*pRep += changeRep2; //update rep var
		}

		//run limit function in case ship or morale is over 100
		limit(pShip, pMorale);

		return intro, end1, end2;
	}
};

//for scenarios with 3 choices
class ThreeChoice : public TwoChoice {//child class of TwoChoice

private://variable only used by this class
	//variables for 3rd ending
	string end3;

	//used to define how much the resources change for the ending
	int changeMoney3 = 0;
	int changeShip3 = 0;
	int changeMorale3 = 0;
	int changeRep3 = 0;

	//used to define how the resources will be set a value in the ending 
	int moneySet3 = 0;
	int shipSet3 = 0;
	int moraleSet3 = 0;
	int repSet3 = 0;

public:
	void setEnd3(string setEnd3, int setchangeMoney, int setchangeShip, int setchangeMorale, int setchangeRep) {//set 3rd ending with how the resources will change
		end3 = setEnd3;

		changeMoney3 = setchangeMoney;
		changeShip3 = setchangeShip;
		changeMorale3 = setchangeMorale;
		changeRep3 = setchangeRep;
	}

	string playScenario() {//runs scenario
		GameStructure threeC;//creates gamestructure class in order to use its functions (help and status) only needs to be done once for threeChoice class

		cout << intro << endl;
		cin >> userChoice;

		while ((userChoice == "h") || (userChoice == "s")) {
			//run help in case user wants help
			threeC.Help();//calls help function- only works if user input h

			//run statusupdateq in case user wants thier status
			threeC.StatusUpdateQ();//calls the statusupdateq function itself- only works if user input s
		}

		//invalid input = try again
		while ((userChoice != "a") && (userChoice != "b") && (userChoice != "c")) {
			cout << "Invalid Input. Please input 'a', 'b', or 'c'" << endl;
			cin >> userChoice;
		}

		//user chose 1st option/ending
		if (userChoice == "a") {
			cout << end1 << endl;//ending text

			//any updates to resource vars
			*pMoney += changeMoney1;//update money var
			*pShip += changeShip1;//update ship var
			*pMorale += changeMorale1;//update morale var
			*pRep += changeRep1;//update rep var
		}

		//user chose 2nd option/ending
		else if (userChoice == "b") {
			cout << end2 << endl;//ending text

			//any updates to resource vars
			*pMoney += changeMoney2;//update money var
			*pShip += changeShip2;//update ship var
			*pMorale += changeMorale2;//update morale var
			*pRep += changeRep2;//update rep var
		}

		//user chose 3rd option/ending
		else if (userChoice == "c") {
			cout << end3 << endl;//ending text

			//any updates to resource vars
			*pMoney += changeMoney3;//update money var
			*pShip += changeShip3;//update ship var
			*pMorale += changeMorale3;//update morale var
			*pRep += changeRep3;//update rep var
		}

		//run limit function in case ship or morale is over 100
		limit(pShip, pMorale);

		return intro, end1, end2, end3;
	}
};

//for the actual execution of the randomized scenarios
void scenarios(int* pMoney, int* pShip, int* pMorale) {

	int day;//counter for how far user is in the trip
	bool gameOver = false;

	//counters to track how many times user hit a specifc scenario
	//Also ref table for type of content of each scenario
	int s1Reps = 0;//3 nochoice parts- no branching
	int s2Reps = 0;//3 twochoice parts- branching (parts 1, 2A, 2B, 3AA, 3AB, 3BA, 3BB)
	int s3Reps = 0;//3 threechoice parts- branching (parts 1, 2A, 2B, 2C, 3AA, 3AB, 3AC, 3BA, 3BB, 3BC, 3CA, 3CB, 3CC)
	int s4Reps = 0;//3 mixed parts (twochoice-nochoice-threechoice)- branching (parts 1, 2A, 2B, 3AA, 3BA)
	int s5Reps = 0;//3 mixed parts (threechoice-twochoice-nochoice)- branching (parts 1, 2A, 2B, 2C, 3AA, 3AB, 3BA, 3BB, 3CA, 3CB)
	int s6Reps = 0;//3 nochoice parts- no branching (delayed beginning- 15 days)
	int s7Reps = 0;//4 nochoice parts- no branching (repeat end)
	int s8Reps = 0;//1 single nochoice part


	//vars to track story part decisions (branching stories only)
	//story 2
	string s2p1Decision;
	string s2p2Decision;
	//story 3
	string s3p1Decision;
	string s3p2Decision;
	//story 4
	string s4p1Decision;
	//story 5
	string s5p1Decision;
	string s5p2Decision;



	srand(static_cast<unsigned int>(time(0)));//seeds randomizer

	for (day = 1; (day < (tripLength + 1)) && (!gameOver); day++) {//will run a "day" amount of times/days or until gameover (tripLength +1= tripLength since there is no day 0)
		cout << "\nDay " << day << endl;//output which day user is on

		bool dayComplete = false; //boolean used to know when a story part has been run for that day. If a story has been fully played, it will remain false and system will choose a new storyline for that day

		while (dayComplete == false) {

			int scenarioNum = ((rand() % 8) + 1);//chooses random number between 1 and 8 to choose which scenario plays (randomizer starts at 0 so +1 is needed to not get 0 as a result)

			//int scenarioNum = 1; //**test line for running specific scenarios**

			if (scenarioNum == 1) { //3 nochoice parts- no branching
				s1Reps++;//add to scenario 1 rep counter
				cout << "Story 1 selected" << endl;// test/status line- delete later

				if (s1Reps == 1) { 
					unique_ptr<NoChoice> scenario1p1(new NoChoice());//new class
					scenario1p1->setIntro("\nIntroduction of Story 1- Part 1.\nNo choices.");//set intro
					scenario1p1->setEnd1("\nEnding of Story 1- Part 1", 0, 0, 0, 0);//set ending
					scenario1p1->playScenario();//run scenario
					dayComplete = true;//stops while loop for that day
				}
				else if (s1Reps == 2) {
					unique_ptr<NoChoice> scenario1p2(new NoChoice());//new class
					scenario1p2->setIntro("\nIntroduction of Story 1- Part 2.\nNo choices");//set intro
					scenario1p2->setEnd1("\nEnding of Story 1- Part 2.", 0, 0, 0, 0);//set ending
					scenario1p2->playScenario();//run scenario
					dayComplete = true;//stops while loop for that day
				}
				else if (s1Reps == 3) {
					unique_ptr<NoChoice> scenario1p3(new NoChoice());//new class
					scenario1p3->setIntro("\nIntroduction of Story 1- Part 3.\nNo choices");//set intro
					scenario1p3->setEnd1("\nEnding of Story 1- Part 3.", 0, 0, 0, 0);//set ending
					scenario1p3->playScenario();//run scenario
					dayComplete = true;//stops while loop for that day
				}
				//test code- delete later
				else if (s1Reps >= 4) {
					cout << "Story is over. ";
				}
			}

			else if (scenarioNum == 2) {//3 twochoice parts- full branching
				s2Reps++;//add to scenario 2 rep counter
				cout << "Story 2 selected" << endl;//test line- delete later

				if (s2Reps == 1) {
					unique_ptr<TwoChoice> scenario2p1(new TwoChoice());//new class
					scenario2p1->setIntro("\nIntroduction of Story 2- Part 1.\nTwo choices- type 'a' or 'b'");//set intro
					scenario2p1->setEnd1("\nEnding of Story 2- Part 1-A", 0, 0, 0, 0);//set 1st ending
					scenario2p1->setEnd2("\nEnding of Story 2- Part 1-B", 0, 0, 0, 0);//set 2nd ending
					scenario2p1->playScenario();//run scenario

					s2p1Decision = userChoice;//save decision

					dayComplete = true;//stops while loop for that day
				}

				else if (s2Reps == 2) {
					
					if (s2p1Decision == "a") { //player part 1 choice was a
						unique_ptr<TwoChoice> scenario2p2a(new TwoChoice());//new class
						scenario2p2a->setIntro("\nIntroduction of Story 2- Part 2A.\nTwo choices- type 'a' or 'b'");//set intro
						scenario2p2a->setEnd1("\nEnding of Story 2- Part 2A-A", 0, 0, 0, 0);//set 1st ending
						scenario2p2a->setEnd2("\nEnding of Story 2- Part 2A-B", 0, 0, 0, 0);//set 2nd ending
						scenario2p2a->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}

					else if (s2p1Decision == "b") { //player part 1 choice was b
						unique_ptr<TwoChoice> scenario2p2b(new TwoChoice());//new class
						scenario2p2b->setIntro("\nIntroduction of Story 2- Part 2B.\nTwo choices- type 'a' or 'b'");//set intro
						scenario2p2b->setEnd1("\nEnding of Story 2- Part 2B-A", 0, 0, 0, 0);//set 1st ending
						scenario2p2b->setEnd2("\nEnding of Story 2- Part 2B-B", 0, 0, 0, 0);//set 2nd ending
						scenario2p2b->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}
					s2p2Decision = userChoice;//save decision
				}
				else if (s2Reps == 3) {

					if (s2p1Decision == "a" && s2p2Decision == "a") { //player followed choice path: a-> a
						unique_ptr<TwoChoice> scenario2p3aa(new TwoChoice());//new class
						scenario2p3aa->setIntro("\nIntroduction of Story 2- Part 3AA.\nTwo choices- type 'a' or 'b'");//set intro
						scenario2p3aa->setEnd1("\nEnding of Story 2- Part 3AA-A", 0, 0, 0, 0);//set 1st ending
						scenario2p3aa->setEnd2("\nEnding of Story 2- Part 3AA-B", 0, 0, 0, 0);//set 2nd ending
						scenario2p3aa->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}
					else if (s2p1Decision == "a" && s2p2Decision == "b") { //player followed choice path: a-> b
						unique_ptr<TwoChoice> scenario2p3ab(new TwoChoice());//new class
						scenario2p3ab->setIntro("\nIntroduction of Story 2- Part 3AB.\nTwo choices- type 'a' or 'b'");//set intro
						scenario2p3ab->setEnd1("\nEnding of Story 2- Part 3AB-A", 0, 0, 0, 0);//set 1st ending
						scenario2p3ab->setEnd2("\nEnding of Story 2- Part 3AB-B", 0, 0, 0, 0);//set 2nd ending
						scenario2p3ab->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}

					else if (s2p1Decision == "b" && s2p2Decision == "a") { //player followed choice path: b-> a
						unique_ptr<TwoChoice> scenario2p3ba(new TwoChoice());//new class
						scenario2p3ba->setIntro("\nIntroduction of Story 2- Part 3BA.\nTwo choices- type 'a' or 'b'");//set intro
						scenario2p3ba->setEnd1("\nEnding of Story 2- Part 3BA-A", 0, 0, 0, 0);//set 1st ending
						scenario2p3ba->setEnd2("\nEnding of Story 2- Part 3BA-B", 0, 0, 0, 0);//set 2nd ending
						scenario2p3ba->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}
					else if (s2p1Decision == "b" && s2p2Decision == "b") { //player followed choice path: b-> b
						unique_ptr<TwoChoice> scenario2p3bb(new TwoChoice());//new class
						scenario2p3bb->setIntro("\nIntroduction of Story 2- Part 3BB.\nTwo choices- type 'a' or 'b'");//set intro
						scenario2p3bb->setEnd1("\nEnding of Story 2- Part 3BB-A", 0, 0, 0, 0);//set 1st ending
						scenario2p3bb->setEnd2("\nEnding of Story 2- Part 3BB-B", 0, 0, 0, 0);//set 2nd ending
						scenario2p3bb->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}
					//part 3 decision does not need to be recorded- last part of story 2
				}
				//test code- delete later
				else if (s2Reps >= 4) {
					cout << "Story is over. ";
				}
			}

			else if (scenarioNum == 3) {//3 threechoice parts- full branching
				s3Reps++;//add to scenario 3 rep counter
				cout << "Story 3 selected" << endl;//test line- delete later

				if (s3Reps == 1) {
					unique_ptr<ThreeChoice> scenario3p1(new ThreeChoice());//new class
					scenario3p1->setIntro("\nIntroduction of Story 3- Part 1.\nThree choices- type 'a', 'b', or 'c'");//set intro
					scenario3p1->setEnd1("\nEnding of Story 3- Part 1-A", 0, 0, 0, 0);//set 1st ending
					scenario3p1->setEnd2("\nEnding of Story 3- Part 1-B", 0, 0, 0, 0);//set 2nd ending
					scenario3p1->setEnd3("\nEnding of Story 3- Part 1-C", 0, 0, 0, 0);//set 3rd ending
					scenario3p1->playScenario();//run scenario
					dayComplete = true;//stops while loop for that day

					s3p1Decision = userChoice;//save decision
				}
				else if (s3Reps == 2) {

					if (s3p1Decision == "a") {//player part 1 choice was a
						unique_ptr<ThreeChoice> scenario3p2a(new ThreeChoice());//new class
						scenario3p2a->setIntro("\nIntroduction of Story 3- Part 2A.\nThree choices- type 'a', 'b', or 'c'");//set intro
						scenario3p2a->setEnd1("\nEnding of Story 3- Part 2A-A", 0, 0, 0, 0);//set 1st ending
						scenario3p2a->setEnd2("\nEnding of Story 3- Part 2A-B", 0, 0, 0, 0);//set 2nd ending
						scenario3p2a->setEnd3("\nEnding of Story 3- Part 2A-C", 0, 0, 0, 0);//set 3rd ending
						scenario3p2a->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}
					else if (s3p1Decision == "b") {//player part 1 choice was b
						unique_ptr<ThreeChoice> scenario3p2b(new ThreeChoice());//new class
						scenario3p2b->setIntro("\nIntroduction of Story 3- Part 2B.\nThree choices- type 'a', 'b', or 'c'");//set intro
						scenario3p2b->setEnd1("\nEnding of Story 3- Part 2B-A", 0, 0, 0, 0);//set 1st ending
						scenario3p2b->setEnd2("\nEnding of Story 3- Part 2B-B", 0, 0, 0, 0);//set 2nd ending
						scenario3p2b->setEnd3("\nEnding of Story 3- Part 2B-C", 0, 0, 0, 0);//set 3rd ending
						scenario3p2b->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}
					else if (s3p1Decision == "c") {//player part 1 choice was c
						unique_ptr<ThreeChoice> scenario3p2c(new ThreeChoice());//new class
						scenario3p2c->setIntro("\nIntroduction of Story 3- Part 2C.\nThree choices- type 'a', 'b', or 'c'");//set intro
						scenario3p2c->setEnd1("\nEnding of Story 3- Part 2C-A", 0, 0, 0, 0);//set 1st ending
						scenario3p2c->setEnd2("\nEnding of Story 3- Part 2C-B", 0, 0, 0, 0);//set 2nd ending
						scenario3p2c->setEnd3("\nEnding of Story 3- Part 2C-C", 0, 0, 0, 0);//set 3rd ending
						scenario3p2c->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}

					s3p2Decision = userChoice;//save decision
				}
				else if (s3Reps == 3) {

					if (s3p1Decision == "a" && s3p2Decision == "a") {//player followed choice path: a-> a
						unique_ptr<ThreeChoice> scenario3p3aa(new ThreeChoice());//new class
						scenario3p3aa->setIntro("\nIntroduction of Story 3- Part 3AA.\nThree choices- type 'a', 'b', or 'c'");//set intro
						scenario3p3aa->setEnd1("\nEnding of Story 3- Part 3AA-A", 0, 0, 0, 0);//set 1st ending
						scenario3p3aa->setEnd2("\nEnding of Story 3- Part 3AA-B", 0, 0, 0, 0);//set 2nd ending
						scenario3p3aa->setEnd3("\nEnding of Story 3- Part 3AA-C", 0, 0, 0, 0);//set 3rd ending
						scenario3p3aa->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}
					else if (s3p1Decision == "a" && s3p2Decision == "b") {//player followed choice path: a-> b
						unique_ptr<ThreeChoice> scenario3p3ab(new ThreeChoice());//new class
						scenario3p3ab->setIntro("\nIntroduction of Story 3- Part 3AB.\nThree choices- type 'a', 'b', or 'c'");//set intro
						scenario3p3ab->setEnd1("\nEnding of Story 3- Part 3AB-A", 0, 0, 0, 0);//set 1st ending
						scenario3p3ab->setEnd2("\nEnding of Story 3- Part 3AB-B", 0, 0, 0, 0);//set 2nd ending
						scenario3p3ab->setEnd3("\nEnding of Story 3- Part 3AB-C", 0, 0, 0, 0);//set 3rd ending
						scenario3p3ab->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}
					else if (s3p1Decision == "a" && s3p2Decision == "c") {//player followed choice path: a-> c
						unique_ptr<ThreeChoice> scenario3p3ac(new ThreeChoice());//new class
						scenario3p3ac->setIntro("\nIntroduction of Story 3- Part 3AC.\nThree choices- type 'a', 'b', or 'c'");//set intro
						scenario3p3ac->setEnd1("\nEnding of Story 3- Part 3AC-A", 0, 0, 0, 0);//set 1st ending
						scenario3p3ac->setEnd2("\nEnding of Story 3- Part 3AC-B", 0, 0, 0, 0);//set 2nd ending
						scenario3p3ac->setEnd3("\nEnding of Story 3- Part 3AC-C", 0, 0, 0, 0);//set 3rd ending
						scenario3p3ac->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}

					else if (s3p1Decision == "b" && s3p2Decision == "a") {//player followed choice path: b-> a
						unique_ptr<ThreeChoice> scenario3p3ba(new ThreeChoice());//new class
						scenario3p3ba->setIntro("\nIntroduction of Story 3- Part 3BA.\nThree choices- type 'a', 'b', or 'c'");//set intro
						scenario3p3ba->setEnd1("\nEnding of Story 3- Part 3BA-A", 0, 0, 0, 0);//set 1st ending
						scenario3p3ba->setEnd2("\nEnding of Story 3- Part 3BA-B", 0, 0, 0, 0);//set 2nd ending
						scenario3p3ba->setEnd3("\nEnding of Story 3- Part 3BA-C", 0, 0, 0, 0);//set 3rd ending
						scenario3p3ba->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}
					else if (s3p1Decision == "b" && s3p2Decision == "b") {//player followed choice path: b-> b
						unique_ptr<ThreeChoice> scenario3p3bb(new ThreeChoice());//new class
						scenario3p3bb->setIntro("\nIntroduction of Story 3- Part 3BB.\nThree choices- type 'a', 'b', or 'c'");//set intro
						scenario3p3bb->setEnd1("\nEnding of Story 3- Part 3BB-A", 0, 0, 0, 0);//set 1st ending
						scenario3p3bb->setEnd2("\nEnding of Story 3- Part 3BB-B", 0, 0, 0, 0);//set 2nd ending
						scenario3p3bb->setEnd3("\nEnding of Story 3- Part 3BB-C", 0, 0, 0, 0);//set 3rd ending
						scenario3p3bb->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}
					else if (s3p1Decision == "b" && s3p2Decision == "c") {//player followed choice path: b-> c
						unique_ptr<ThreeChoice> scenario3p3bc(new ThreeChoice());//new class
						scenario3p3bc->setIntro("\nIntroduction of Story 3- Part 3BC.\nThree choices- type 'a', 'b', or 'c'");//set intro
						scenario3p3bc->setEnd1("\nEnding of Story 3- Part 3BC-A", 0, 0, 0, 0);//set 1st ending
						scenario3p3bc->setEnd2("\nEnding of Story 3- Part 3BC-B", 0, 0, 0, 0);//set 2nd ending
						scenario3p3bc->setEnd3("\nEnding of Story 3- Part 3BC-C", 0, 0, 0, 0);//set 3rd ending
						scenario3p3bc->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}

					else if (s3p1Decision == "c" && s3p2Decision == "a") {//player followed choice path: c-> a
						unique_ptr<ThreeChoice> scenario3p3ca(new ThreeChoice());//new class
						scenario3p3ca->setIntro("\nIntroduction of Story 3- Part 3CA.\nThree choices- type 'a', 'b', or 'c'");//set intro
						scenario3p3ca->setEnd1("\nEnding of Story 3- Part 3CA-A", 0, 0, 0, 0);//set 1st ending
						scenario3p3ca->setEnd2("\nEnding of Story 3- Part 3CA-B", 0, 0, 0, 0);//set 2nd ending
						scenario3p3ca->setEnd3("\nEnding of Story 3- Part 3CA-C", 0, 0, 0, 0);//set 3rd ending
						scenario3p3ca->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}
					else if (s3p1Decision == "c" && s3p2Decision == "b") {//player followed choice path: c-> b
						unique_ptr<ThreeChoice> scenario3p3cb(new ThreeChoice());//new class
						scenario3p3cb->setIntro("\nIntroduction of Story 3- Part 3CB.\nThree choices- type 'a', 'b', or 'c'");//set intro
						scenario3p3cb->setEnd1("\nEnding of Story 3- Part 3CB-A", 0, 0, 0, 0);//set 1st ending
						scenario3p3cb->setEnd2("\nEnding of Story 3- Part 3CB-B", 0, 0, 0, 0);//set 2nd ending
						scenario3p3cb->setEnd3("\nEnding of Story 3- Part 3CB-C", 0, 0, 0, 0);//set 3rd ending
						scenario3p3cb->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}
					else if (s3p1Decision == "c" && s3p2Decision == "c") {//player followed choice path: c-> c
						unique_ptr<ThreeChoice> scenario3p3cc(new ThreeChoice());//new class
						scenario3p3cc->setIntro("\nIntroduction of Story 3- Part 3CC.\nThree choices- type 'a', 'b', or 'c'");//set intro
						scenario3p3cc->setEnd1("\nEnding of Story 3- Part 3CC-A", 0, 0, 0, 0);//set 1st ending
						scenario3p3cc->setEnd2("\nEnding of Story 3- Part 3CC-B", 0, 0, 0, 0);//set 2nd ending
						scenario3p3cc->setEnd3("\nEnding of Story 3- Part 3CC-C", 0, 0, 0, 0);//set 3rd ending
						scenario3p3cc->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}
					//part 3 decision does not need to be recorded- last part of story 3
				}
				//test code- delete later
				else if (s3Reps >= 4) {
				cout << "Story is over. ";
				}
			}

			else if (scenarioNum == 4) {//3 mixedchoice parts(twochoice - nochoice - threechoice) - branching(parts 1, 2A, 2B, 3AA, 3BA)
				s4Reps++;//add to scenario 4 rep counter
				cout << "Story 4 selected" << endl;//test line- delete later

				if (s4Reps == 1) {
					unique_ptr<TwoChoice> scenario4p1(new TwoChoice());//new class
					scenario4p1->setIntro("\nIntroduction of Story 4- Part 1.\nTwo choices- type 'a' or 'b'");//set intro
					scenario4p1->setEnd1("\nEnding of Story 4- Part 1-A", 0, 0, 0, 0);//set 1st ending
					scenario4p1->setEnd2("\nEnding of Story 4- Part 1-B", 0, 0, 0, 0);//set 2nd ending
					scenario4p1->playScenario();//run scenario

					s4p1Decision = userChoice;//save decision

					dayComplete = true;//stops while loop for that day
				}

				else if (s4Reps == 2) {
					if (s4p1Decision == "a") { //player part 1 choice was a
						unique_ptr<NoChoice> scenario4p2a(new NoChoice());//new class
						scenario4p2a->setIntro("\nIntroduction of Story 4- Part 2A.\nNo choices");//set intro
						scenario4p2a->setEnd1("\nEnding of Story 4- Part 2A-A", 0, 0, 0, 0);//set ending
						scenario4p2a->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}

					else if (s4p1Decision == "b") { //player part 1 choice was b
						unique_ptr<NoChoice> scenario4p2b(new NoChoice());//new class
						scenario4p2b->setIntro("\nIntroduction of Story 4- Part 2B.\nNo choices");//set intro
						scenario4p2b->setEnd1("\nEnding of Story 4- Part 2B-A", 0, 0, 0, 0);//set ending
						scenario4p2b->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}
				}
				else if (s4Reps == 3) {

					if (s4p1Decision == "a") { //player part 1 choice was a- part 2 had no choices
						unique_ptr<ThreeChoice> scenario4p3aa(new ThreeChoice());//new class
						scenario4p3aa->setIntro("\nIntroduction of Story 4- Part 3AA.\nThree choices- type 'a', 'b', or 'c'");//set intro
						scenario4p3aa->setEnd1("\nEnding of Story 4- Part 3AA-A", 0, 0, 0, 0);//set 1st ending
						scenario4p3aa->setEnd2("\nEnding of Story 4- Part 3AA-B", 0, 0, 0, 0);//set 2nd ending
						scenario4p3aa->setEnd3("\nEnding of Story 4- Part 3AA-C", 0, 0, 0, 0);//set 3rd ending
						scenario4p3aa->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}

					else if (s4p1Decision == "b") { //player part 1 choice was b- part 2 had no choices
						unique_ptr<ThreeChoice> scenario4p3ba(new ThreeChoice());//new class
						scenario4p3ba->setIntro("\nIntroduction of Story 4- Part 3BA.\nThree choices- type 'a', 'b', or 'c'");//set intro
						scenario4p3ba->setEnd1("\nEnding of Story 4- Part 3BA-A", 0, 0, 0, 0);//set 1st ending
						scenario4p3ba->setEnd2("\nEnding of Story 4- Part 3BA-B", 0, 0, 0, 0);//set 2nd ending
						scenario4p3ba->setEnd3("\nEnding of Story 4- Part 3BA-C", 0, 0, 0, 0);//set 3rd ending
						scenario4p3ba->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}
				}
				//test code- delete later
				else if (s4Reps >= 4) {
					cout << "Story is over. ";
				}
			}

			else if (scenarioNum == 5) {//3 mixedchoice parts (threechoice-twochoice-nochoice)- branching (parts 1, 2A, 2B, 2C, 3AA, 3AB, 3BA, 3BB, 3CA, 3CB)
				s5Reps++;//add to scenario 5 rep counter
				cout << "Story 5 selected" << endl;//test line- delete later

				if (s5Reps == 1) {
					unique_ptr<ThreeChoice> scenario5p1(new ThreeChoice());//new class
					scenario5p1->setIntro("\nIntroduction of Story 5- Part 1.\nThree choices- type 'a', 'b', or 'c'");//set intro
					scenario5p1->setEnd1("\nEnding of Story 5- Part 1-A", 0, 0, 0, 0);//set 1st end
					scenario5p1->setEnd2("\nEnding of Story 5- Part 1-B", 0, 0, 0, 0);//set 2nd end
					scenario5p1->setEnd3("\nEnding of Story 5- Part 1-C", 0, 0, 0, 0);//set 3rd end
					scenario5p1->playScenario();//run scenario

					s5p1Decision = userChoice;//save decision
					dayComplete = true;//stops while loop for that day
				}
				else if (s5Reps == 2) {
					if (s5p1Decision == "a") {//player part 1 choice was a
						unique_ptr<TwoChoice> scenario5p2a(new TwoChoice());//new class
						scenario5p2a->setIntro("\nIntroduction of Story 5- Part 2A.\nTwo choices- type 'a' or 'b'");//set intro
						scenario5p2a->setEnd1("\nEnding of Story 5- Part 2A-A", 0, 0, 0, 0);//set 1st end
						scenario5p2a->setEnd2("\nEnding of Story 5- Part 2A-B", 0, 0, 0, 0);//set 2nd end
						scenario5p2a->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}

					else if (s5p1Decision == "b") {//player part 1 choice was b
						unique_ptr<TwoChoice> scenario5p2b(new TwoChoice());//new class
						scenario5p2b->setIntro("\nIntroduction of Story 5- Part 2B.\nTwo choices- type 'a' or 'b'");//set intro
						scenario5p2b->setEnd1("\nEnding of Story 5- Part 2B-A", 0, 0, 0, 0);//set 1st end
						scenario5p2b->setEnd2("\nEnding of Story 5- Part 2B-B", 0, 0, 0, 0);//set 2nd end
						scenario5p2b->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}

					else if (s5p1Decision == "c") {//player part 1 choice was c
						unique_ptr<TwoChoice> scenario5p2c(new TwoChoice());//new class
						scenario5p2c->setIntro("\nIntroduction of Story 5- Part 2C.\nTwo choices- type 'a' or 'b'");//set intro
						scenario5p2c->setEnd1("\nEnding of Story 5- Part 2C-A", 0, 0, 0, 0);//set 1st end
						scenario5p2c->setEnd2("\nEnding of Story 5- Part 2C-B", 0, 0, 0, 0);//set 2nd end
						scenario5p2c->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}

					s5p2Decision = userChoice;//save decision
				}
				else if (s5Reps == 3) {
					if (s5p1Decision == "a" && s5p2Decision == "a") {//player followed choice path: a-> a
						unique_ptr<NoChoice> scenario5p3aa(new NoChoice());//new class
						scenario5p3aa->setIntro("\nIntroduction of Story 5- Part 3AA.\nNo choices");//set intro
						scenario5p3aa->setEnd1("\nEnding of Story 5- Part 3AA", 0, 0, 0, 0);//set ending
						scenario5p3aa->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}
					else if (s5p1Decision == "a" && s5p2Decision == "b") {//player followed choice path: a-> b
						unique_ptr<NoChoice> scenario5p3ab(new NoChoice());//new class
						scenario5p3ab->setIntro("\nIntroduction of Story 5- Part 3AB.\nNo choices");//set intro
						scenario5p3ab->setEnd1("\nEnding of Story 5- Part 3AB", 0, 0, 0, 0);//set ending
						scenario5p3ab->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}

					else if (s5p1Decision == "b" && s5p2Decision == "a") {//player followed choice path: b-> a
						unique_ptr<NoChoice> scenario5p3ba(new NoChoice());//new class
						scenario5p3ba->setIntro("\nIntroduction of Story 5- Part 3BA.\nNo choices");//set intro
						scenario5p3ba->setEnd1("\nEnding of Story 5- Part 3BA", 0, 0, 0, 0);//set ending
						scenario5p3ba->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}
					else if (s5p1Decision == "b" && s5p2Decision == "b") {//player followed choice path: b-> b
						unique_ptr<NoChoice> scenario5p3bb(new NoChoice());//new class
						scenario5p3bb->setIntro("\nIntroduction of Story 5- Part 3BB.\nNo choices");//set intro
						scenario5p3bb->setEnd1("\nEnding of Story 5- Part 3BB", 0, 0, 0, 0);//set ending
						scenario5p3bb->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}

					else if (s5p1Decision == "c" && s5p2Decision == "a") {//player followed choice path: c-> a
						unique_ptr<NoChoice> scenario5p3ca(new NoChoice());//new class
						scenario5p3ca->setIntro("\nIntroduction of Story 5- Part 3CA.\nNo choices");//set intro
						scenario5p3ca->setEnd1("\nEnding of Story 5- Part 3CA", 0, 0, 0, 0);//set ending
						scenario5p3ca->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}
					else if (s5p1Decision == "c" && s5p2Decision == "b") {//player followed choice path: c-> b
						unique_ptr<NoChoice> scenario5p3cb(new NoChoice());//new class
						scenario5p3cb->setIntro("\nIntroduction of Story 5- Part 3CB.\nNo choices");//set intro
						scenario5p3cb->setEnd1("\nEnding of Story 5- Part 3CB", 0, 0, 0, 0);//set ending
						scenario5p3cb->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}
				}
				//test code- delete later
				else if (s5Reps >= 4) {
					cout << "Story is over. ";
				}
			}

			else if (scenarioNum == 6) { //3 nochoice parts- no branching (delayed beginning- 15 days)
				if (day >= 15) {//creates delayed start to story
					s6Reps++;//add to scenario 6 rep counter
					cout << "Story 6 selected. Delayed start = 15 days" << endl;//test line- delete later

					if (s6Reps == 1) {
						unique_ptr<NoChoice> scenario6p1(new NoChoice());//new class
						scenario6p1->setIntro("\nIntroduction of Story 6- Part 1.");//set intro
						scenario6p1->setEnd1("\nEnding of Story 6- Part 1", 0, 0, 0, 0);//set ending
						scenario6p1->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}
					else if (s6Reps == 2) {
						unique_ptr<NoChoice> scenario6p2(new NoChoice());//new class
						scenario6p2->setIntro("\nIntroduction of Story 6- Part 2.");//set intro
						scenario6p2->setEnd1("\nEnding of Story 6- Part 2", 0, 0, 0, 0);//set ending
						scenario6p2->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}
					else if (s6Reps == 3) {
						unique_ptr<NoChoice> scenario6p3(new NoChoice());//new class
						scenario6p3->setIntro("\nIntroduction of Story 6- Part 3.");//set intro
						scenario6p3->setEnd1("\nEnding of Story 6- Part 3", 0, 0, 0, 0);//set ending
						scenario6p3->playScenario();//run scenario
						dayComplete = true;//stops while loop for that day
					}
					//test code- delete later
					else if (s6Reps >= 4) {
						cout << "Story is over. ";
					}
				}
				else {
					cout << "Story 6 skipped due to delay start of 15 days." << endl;
				}
			}

			else if (scenarioNum == 7) { //4 nochoice parts- no branching (repeating end)
				s7Reps++;//add to scenario 7 rep counter
				cout << "Story 7 selected" << endl;//test line- delete later

				if (s7Reps == 1) {
					unique_ptr<NoChoice> scenario7p1(new NoChoice());//new class
					scenario7p1->setIntro("\nIntroduction of Story 7- Part 1.");//set intro
					scenario7p1->setEnd1("\nEnding of Story 7- Part 1", 0, 0, 0, 0);//set ending
					scenario7p1->playScenario();//run scenario
					dayComplete = true;//stops while loop for that day
				}
				else if (s7Reps == 2) {
					unique_ptr<NoChoice> scenario7p2(new NoChoice());//new class
					scenario7p2->setIntro("\nIntroduction of Story 7- Part 2.");//set intro
					scenario7p2->setEnd1("\nEnding of Story 7- Part 2", 0, 0, 0, 0);//set ending
					scenario7p2->playScenario();//run scenario
					dayComplete = true;//stops while loop for that day
				}
				else if (s7Reps == 3) {
					unique_ptr<NoChoice> scenario7p3(new NoChoice());//new class
					scenario7p3->setIntro("\nIntroduction of Story 7- Part 3.");//set intro
					scenario7p3->setEnd1("\nEnding of Story 7- Part 3", 0, 0, 0, 0);//set ending
					scenario7p3->playScenario();//run scenario
					dayComplete = true;//stops while loop for that day
				}
				else if (s7Reps >= 4) {
					unique_ptr<NoChoice> scenario7p4(new NoChoice());//new class
					scenario7p4->setIntro("\nIntroduction of Story 7- Part 4. This part can repeat- it represents reoccurring/ reminisce endings.");//set intro
					scenario7p4->setEnd1("\nEnding of Story 7- Part 4", 0, 0, 0, 0);//set ending
					scenario7p4->playScenario();//run scenario
					dayComplete = true;//stops while loop for that day
				}
			}

			else if (scenarioNum == 8) { //1 single nochoice part (single part/rep story)
				s8Reps++;
				cout << "Story 8 selected" << endl;

				if (s8Reps == 1) {
					unique_ptr<NoChoice> scenario8(new NoChoice());//new class
					scenario8->setIntro("\nIntroduction of Story 8- single part.");//set intro
					scenario8->setEnd1("\nEnding of Story 8", 0, 0, 0, 0);//set ending
					scenario8->playScenario();//run scenario

					dayComplete = true;//stops while loop for the day
				}
				//test code- delete later
				else if (s8Reps >= 2) {
					cout << "Story is over. ";
				}
			}
			
			if (dayComplete == false) {
				cout << "Story rejected- choosing another" << endl;
			}
		}


		
		//**tempoprary removal for initial prototype- will be put back once the actual storylines are in
		//printout of current status at end of each day
		//status(pMoney, pShip, pMorale);

		//GAMEOVER = if any resource equals 0
		if (*pMoney <= 0 || *pShip <= 0 || *pMorale <= 0) {
			gameOver = true;
			cout << "GAME OVER" << endl;
		}

		//if user survives the day, press enter to continue
		if (!gameOver) {
			cout << "Press Enter to continue to next day" << endl;
			// pauses program, requires enter to continue
			cin.ignore();
			cin.get();
		}
	}
}


int main() {
	string userName;

	//introduction (DESCRIPTION OF GAME, INSTRUCTIONS)
	cout << "Welcome to Journey to Andromeda!\nYour task is to lead the crew of your spaceship to the Andromeda star system without running out of any of your resources. Periodically, you will need to choose how you react to a situation. I implore you to choose carefully, all of those choices will affect both your resources, how others react to you, and the rest of your journey." << endl;//game intro

	//sets "userName" to user's given name
	cout << "\n\nHello, I am an AI designed to get Captains like you ready for your upcoming journey. What is your name? \nEnter your last name: ";
	cin >> userName;

	cout << "\nWelcome Captain " << userName << endl;
	cout << "\nYou and your crew have just gotten orders to set out for the Andromeda star system. This will be a " << tripLength << "-day journey." << endl;
	cout << "As Captain, you are responsible for getting your crew and ship there in the best possible condition." << endl;

	//replaces exception section
	cout << "\nOne last thing: at any time, should you want help or an additional status update please input either 'h' for help or 's' for your status. I wish you all the best as you set out. Good luck and goodbye." << endl;

	cout << "\nPress Enter to begin your journey" << endl;
	// pauses program, requires enter to continue
	cin.ignore();
	cin.get();


	//printout of current status at start of game
	status(pMoney, pShip, pMorale);

	//run actual game play
	scenarios(pMoney, pShip, pMorale);

	//printout of current status at end of game
	status(pMoney, pShip, pMorale);


	//outtros
	string endType;//used to display what type of ending the user got with their score

	//gameovers- more rare than previous version
	if (*pShip <= 0) {//0% ship condition ending
		cout << "\nYour ship has suffered irreparable damage and you and your crew perish. Your ship drifts into the void, cold and dead. Hopefully someone will find it and you before the ship drifts into a black hole.";
		endType = "Dead Ship (0% Ship)";
	}
	else if (*pMorale <= 0) {//0% morale ending
		cout << "\nYour crew has gotten sick and tired of your poor decisions and your poor treatment of them. They stage a mutiny, and you are tossed out the airlock to die alone in the void. Your First Officer, Jonny, takes over and he and the rest of the crew decide to become pirates. Needless to say: they never complete your mission. They do quite well for themselves and become quite fearsome. You would be very impressed- if you weren\'t already dead. :)";
		endType = "Munity (0% Morale)";
	}
	else if (*pMoney <= 0) {//0 money ending
		cout << "\nYou are completely out of money- and your once-loyal crew just found out. You are useless to them if you are penniless. They abandon you at the nearest space station and take the ship with them to decide their own destiny. Needless to say: you don't make it to the Andromeda system. You have failed.";
		endType = "Abandonment (No Money)";
	}

	//win ending
	if (*pMoney > 0 && *pShip > 0 && *pMorale > 0) {
		cout << "You made it!\nAfter " << tripLength << " eventful days, you arrive at the Andromeda system. Good job Captain " << userName;
		endType = "Successful Trip (Win)";
	}

	//choose whether to add some sort of score-saving


	cout << "\nThank you for playing! Hope you had fun." << endl;

	return 0;
}