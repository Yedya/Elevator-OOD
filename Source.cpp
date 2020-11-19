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

enum  Direction{UP,DOWN,IDLE};

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
		FloorButton(){};
		FloorButton(int ID, int buttonNumber) :Button{ ID,buttonNumber } {};
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
	Floor()
	{

	}

private:
	int ID;

};

class Request
{
	public:
		Request()
		{

		}
		Request(int requestedFloor,Direction direction) : requestedFloor(requestedFloor), direction(direction)
		{
			ID = to_string(requestedFloor) + " " + to_string(direction);
		}
		//~Request();
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
		Elevator(int ID,int numberOfFloors) : ID(ID)
		{
			currentFloor = 1;
			inputReceived = false;
			initializeButtons(numberOfFloors);
			initializeInputService();
		}
		void initializeInputService()
		{
			while (true)
			{
				char input;
				string strInput;
				int timer = 5;
				while (inputReceived == false)
				{
					cout << "\n";
					cout << "\t Wait for button to be pressed  "  <<  endl;
					//while (timer > 0)
					//{
					//	cout << "\t  " << timer;
					//	waitFor(3);
					//	timer--;
					//	if (timer == 0)
					//	{
					//		waitFor(3);
					//		timer = 5;
					//	}
					//}
					
					cin >> input;
					cout << "\n";

					if (isdigit(input))
					{
						inputReceived = true;
						break;
					}
					else
					{
						cout << "\t Press a valid button " <<endl;
					}
				}
				if (isdigit(input) && (int)input - '0' >= 1 && (int)input - '0' <= buttons.size())
				{
					inputReceived = true;
					cout << "\t Button Pressed  " << input << " @  FLOOR " << currentFloor <<  endl;
					int floorRequestNumber = (int)input - '0';
					addRequest(floorRequestNumber);
					input = 'a';
				}
				else if (isdigit(input) && (int)input - '0' == 0 )
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
				//cout << "handleRequest   ";
				handleRequest();
			}
			else
			{
				//cout << "IDLE TO  ";
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
			if (directionToMove == IDLE)
				return;

			//cout << "\t CURRENT FLOOR " << currentFloor << " REQUESTED " << floorRequested << " DIRECTION " << enum_to_string(directionToMove) << endl;
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
			
			//Deduce direction
			Direction directionToMove = request.getDirection();

			//Move up or down direction
			if (directionToMove == UP)
			{
				cout << "\t MOVING TO  " << request.getRequestedFloor() << " " << endl;
				//moveUp();
				waitFor(2);
				currentFloor = request.getRequestedFloor();
				requestQueue.pop();
				cout << "\n";
				cout << "\t Arrived at  " << currentFloor <<endl;
			}
			else if (directionToMove == DOWN)
			{
				cout << "\t MOVING TO  " << request.getRequestedFloor() << " " << endl;
				//moveDown();
				waitFor(2);
				currentFloor = request.getRequestedFloor();
				requestQueue.pop();
				cout << "\t Arrived at  " << currentFloor << endl;
			}
		}
	private:
		bool inputReceived;
		int ID;
		int currentFloor;
		const int maxWeight = 1700;
		Direction directionToMove;
		queue<Request> requestQueue;
		Request getNextRequestedFloor();
		Direction getDirectionToMove();
		vector<Button> buttons;
};

//Singleton
class Building
{
	public:
		void initializeBuilding(int ID, int numberOfFloors, int numberOfElevators)
		{
			numberOfFloors = numberOfFloors;
			numberOfElevators = numberOfElevators;
			ID = ID;
		};
		static Building& getIntance()
		{
			static Building building;
			return building; 
		};
		int getID() { return ID; };
		int getNumberOfFloors() { return numberOfFloors; };
		int getNumberOfElevators() { return numberOfElevators; };
	private:
		Building(){};
		vector<Floor> floors;
		int ID;
		int numberOfFloors;
		int numberOfElevators;

};

int main(void)
{

	Building::getIntance().initializeBuilding(1, 50, 1);

	Elevator elevator1(5, 50);

	system("pause");
	return 0;

}