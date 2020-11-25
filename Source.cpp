#include <algorithm>
#include <iostream>
#include <string>
#include<math.h>
#include <cmath>
#include <vector>
#include<map>
#include<List>
#include<unordered_map>
#include <string.h> 
#include <sstream>
#include <queue>
using namespace std;
#include <iostream>
#include <chrono>
#include <thread>
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

namespace ElevatorSystem
{


	enum  Direction { UP, DOWN, IDLE };

	string enum_to_string(Direction type)
	{
		switch (type) {
		case UP:
			return "UP";
		case DOWN:
			return "DOWN";
		case IDLE:
			return "IDLE";
		default:
			return "Invalid";
		}
	}

	void waitFor(int amount)
	{
		sleep_for(nanoseconds(10));
		sleep_until(system_clock::now() + seconds(amount));
	}

	class Button
	{
	public:
		Button() {};
		Button(int ID, int buttonNumber) :ID(ID)
		{
			wasPressed = false;
		};
		void buttonPressed(int ID)
		{
			wasPressed = true;
		}
		int getButtonStatus() { return wasPressed; };
		int getID() { return ID; };
		int getButtonNumber() { return buttonNumber; };
	private:
		int ID;
		int buttonNumber;
		bool wasPressed;


	};

	class FloorButton : public Button
	{
	public:
		FloorButton() {};
		FloorButton(int ID, int buttonNumber) :Button{ ID,buttonNumber }
		{

		};

	private:
		int buttonNumber;


	};

	class DoorButton : public Button
	{
	public:
		DoorButton() {};
		DoorButton(int ID, int buttonNumber) :Button{ ID,buttonNumber } {};
	private:
		int buttonNumber;
	};

	class Floor
	{
	public:
		Floor(int ID, int numberOfFloors) : ID(ID)
		{
			initializeButtons(numberOfFloors);
			initializeInputService();
		}
		void initializeButtons(int numberOfFloors)
		{
			floorButtons.resize(numberOfFloors);
			for (int f = 1; f <= numberOfFloors; f++)
			{
				string eunumerateID = to_string(this->ID) + to_string(f);
				FloorButton button(stoi(eunumerateID), f);
				floorButtons[f - 1] = button;
			}
			DoorButton doorButton(0, 0);
			floorButtons.push_back(doorButton);
		}
		void initializeInputService()
		{
			while (true)
			{
				char input;
				string strInput;
				int intputAsInt = -1;
				int timer = 5;
				while (inputReceived == false)
				{
					cout << "\n";
					cout << "\t Wait for floor to be pressed  " << endl;
					cin >> input;
					cout << "\n";

					int validInputAsInt = (int)input;

					if (isdigit(input))
					{
						inputReceived = true;
						break;
					}
					else
					{
						//cout << "\t Press a valid button " << endl;
					}
				}
				if (isdigit(input) && (int)input - '0' >= 1 && (int)input - '0' <= floorButtons.size())
				{
					inputReceived = true;
					cout << "\t Button Pressed  " << input << " @  FLOOR " << currentFloor << endl;
					int floorNumberRequest = (int)input - '0';
					//ElevatorSystem::Dispatcher::shared_instance().processRequest(floorNumberRequest);
					//addRequest(floorRequestNumber);
					input = 'a';
				}
				else if (isdigit(input) && (int)input - '0' == 0)
				{
					//inputReceived = true;
					//cout << "\t Doors closing " << input << endl;

					//input = 'a';
					////closeDoors();
				}
				cout << "\n";
				inputReceived = false;
			}

		}
	private:
		int ID;
		bool inputReceived;
		int currentFloor;
		vector<Button> floorButtons;

	};

	class Request
	{
	public:
		Request()
		{

		}
		Request(int requestedFloor, Direction direction) : requestedFloor(requestedFloor), direction(direction)
		{
			ID = to_string(requestedFloor) + " " + to_string(direction);
		}
		~Request(void)
		{
		};
		Direction getDirection() { return direction; };
		string getID() { return ID; };
		int getRequestedFloor() { return requestedFloor; };
	private:
		string ID;
		int requestedFloor;
		Direction direction;
	};

	class Elevator
	{
	public:
		Elevator() {};
		Elevator(int ID, int numberOfFloors) : ID(ID)
		{
			currentFloor = 1;
			inputReceived = false;
			initializeButtons(numberOfFloors);
			//initializeInputService();
		}
		void initializeInputService()
		{
			while (true)
			{
				char input;
				string strInput;
				int intputAsInt = -1;
				int timer = 5;
				while (inputReceived == false)
				{
					cout << "\n";
					cout << "\t Wait for button to be pressed  " << endl;
					cin >> input;
					cout << "\n";

					int validInputAsInt = (int)input;

					if (isdigit(input))
					{
						inputReceived = true;
						break;
					}
					else
					{
						cout << "\t Press a valid button " << endl;
					}
				}
				if ((int)input != currentFloor && isdigit(input) && (int)input - '0' >= 1 && (int)input - '0' <= buttons.size())
				{
					inputReceived = true;
					cout << "\t Button Pressed  " << input << " @  FLOOR " << currentFloor << endl;
					int floorRequestNumber = (int)input - '0';
					addRequest(floorRequestNumber);
					input = 'a';
				}
				else if (isdigit(input) && (int)input - '0' == 0)
				{
					inputReceived = true;
					cout << "\t Doors closing " << input << endl;

					input = 'a';
					closeDoors();
				}
				cout << "\n";
				inputReceived = false;
			}

		}
		void moveUp()
		{

		}
		void moveDown()
		{

		}
		void stop()
		{

		}
		void openDoors()
		{

		}
		void closeDoors()
		{
			if (!requestQueue.empty())
			{
				handleRequest();
			}
			else
			{
				cout << "\t Idle @  " << currentFloor << " " << endl;
				//IDLE
			}
		}
		int getCurrentFloor() { return currentFloor; };
		int getID() { return ID; };
		Direction getRequestDirection(int floorRequested)
		{
			if (floorRequested > currentFloor)
				return UP;
			else if (floorRequested < currentFloor)
				return DOWN;
			return IDLE;
		};
		void addRequest(int floorRequested)
		{
			Direction directionToMove = getRequestDirection(floorRequested);
			cout << "\t CURRENT FLOOR " << currentFloor << " REQUESTED " << floorRequested << " DIRECTION " << enum_to_string(directionToMove) << endl;
			if (directionToMove == IDLE)
				return;


			//cout << "\n";
			Request newRequest(floorRequested, directionToMove);
			requestQueue.push(newRequest);
		}
		queue<Request> getRequestQueue() { return requestQueue; };
		void initializeButtons(int numberOfFloors)
		{
			buttons.resize(numberOfFloors);
			for (int f = 1; f <= numberOfFloors; f++)
			{
				string eunumerateID = to_string(this->ID) + to_string(f);
				FloorButton button(stoi(eunumerateID), f);
				buttons[f - 1] = button;
			}
			DoorButton doorButton(0, 0);
			buttons.push_back(doorButton);

		}
		vector<Button> getButtons(int numberOfFloors) { return buttons; };
		//This will only be called if the queue has requests 
		void handleRequest()
		{
			//Get the request
			Request request = requestQueue.front();
			requestQueue.pop();
			//Deduce direction
			Direction directionToMove = request.getDirection();

			//Move up or down direction
			if (directionToMove == UP)
			{
				cout << "\t Moving to  " << request.getRequestedFloor() << " " << endl;
				if (!requestQueue.empty())
				{
				}
				//moveUp();
				waitFor(2);
				currentFloor = request.getRequestedFloor();
				//request.~Request();
				cout << "\n";
				cout << "\t Arrived at  " << currentFloor << endl;
			}
			else if (directionToMove == DOWN)
			{
				cout << "\t MOVING TO  " << request.getRequestedFloor() << " " << endl;
				//moveDown();
				waitFor(2);
				currentFloor = request.getRequestedFloor();
				cout << "\t Arrived at  " << currentFloor << endl;
			}
		}
		Request getNextRequestedFloor();
		Direction getDirectionToMove();
	private:
		bool inputReceived;
		int ID;
		int currentFloor;
		const int maxWeight = 1700;
		Direction directionToMove;
		queue<Request> requestQueue;
		vector<Button> buttons;
	};

	class Dispatcher
	{
	public:
		static Dispatcher& shared_instance() { static Dispatcher dispatcher; return dispatcher; }
		void initalizeDispatcher(int ID, int numberOfFloors, vector<Elevator> buildingElevators)
		{
			setNumberOfFloors(numberOfFloors);
			setID(ID);
			//initializeElevators(buildingElevators);
		}
		void setID(int givenID)
		{
			ID = givenID;
		}
		void setNumberOfFloors(int numFloors)
		{
			numberOfFloors = numFloors;
		}
		void initializeElevators(vector<Elevator> buildingElevators)
		{

			for (auto& i : buildingElevators)
			{
				elevators.push_back(i);
			}
		}
		void processRequest(int floorRequested)
		{
			//Make the request
			//Request floorRequested(floorRequested, IDLE);

			//Find the elavator serving the floor the request was made from, TODO: Change entire structure such that an elevator ID is mapped to a set of floors, this hanldes the N elevators problem
			elevators[0].addRequest(floorRequested);
			//requestQueue.push(newRequest);
			//Parse shaft ID 
		}
	private:
		int ID;
		int numberOfFloors;
		vector<Elevator> elevators;
	};

	//Singleton
	class Building
	{
	public:
		void initializeBuilding(int ID, int numberOfFloors, int numberOfElevators)
		{
			setNumberOfFloors(numberOfFloors);
			setNumberOfElevators(numberOfElevators);
			setID(ID);
			initializeFloors(numberOfFloors);
			initializeElevators(1);

			Dispatcher::shared_instance().initalizeDispatcher(ID, numberOfFloors, elevators);
		};
		static Building& getIntance()
		{
			static Building building;
			return building;
		};
		void initializeFloors(int numberOfFloors)
		{
			for (size_t i = 0; i < numberOfFloors; i++)
			{
				Floor newFloor(i + 1, numberOfFloors);
				floors.push_back(newFloor);
			}
		}
		void initializeElevators(int numberOfElevators)
		{
			for (size_t i = 0; i < numberOfElevators; i++)
			{
				Elevator elevator(i + 1, 50);
				elevators.push_back(elevator);
			}
			//cout << " HERE";
			Dispatcher::shared_instance().initializeElevators(elevators);
		}
		int getID() { return ID; };
		int getNumberOfFloors() { return numberOfFloors; };
		int getNumberOfElevators() { return numberOfElevators; };
		vector<Elevator> getElevators() { return elevators; };
		void setID(int givenID)
		{
			ID = givenID;
		}
		void setNumberOfElevators(int numberElevators)
		{
			numberOfElevators = numberElevators;
		}
		void setNumberOfFloors(int numFloors)
		{
			numberOfFloors = numFloors;
		}
	private:
		Building() {};
		vector<Floor> floors;
		vector<Elevator> elevators;
		int ID;
		int numberOfFloors;
		int numberOfElevators;

	};


}
int main(void)
{
	//50 Floors, one elevator 
	//Building::getIntance().initializeBuilding(1, 50, 1);
	ElevatorSystem::Building::getIntance().initializeBuilding(1, 50, 1);
	ElevatorSystem::Dispatcher::shared_instance();


	system("pause");
	return 0;



}