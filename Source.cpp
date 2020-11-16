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

enum  Direction{UP,DOWN};

class Button
{
	public:
		Button(){};
		Button(int ID) :ID(ID) 
		{
			wasPressed = false;
		};
		int getButtonStatus() { return wasPressed; };
		int getID() { return ID; };
	private:
		int ID;
		bool wasPressed;
};

class Request
{
	public:
		Request()
		{

		}
		Request(int requestedFloor,Direction direction) : requestedFloor(requestedFloor), direction(direction)
		{

		}
		~Request();
		Direction getDirection() { return direction; };
		int getID() { return ID; };
		int getRequestedFloor() { return requestedFloor; };
	private:
		int ID;
		int requestedFloor;
		Direction direction;
};

class Elevator
{
public:
	Elevator() {};
	Elevator(int ID) : ID(ID)
	{
		currentFloor = 1;
	}
	void moveUp();
	void moveDown();
	void stop();
	int getCurrentFloor() { return currentFloor; };
	int getID() { return ID; };
	queue<Request> getrequestQueue() { return requestQueue; };
private:
	int ID;
	int currentFloor;
	const int maxWeight = 1700;
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
		int ID;
		int numberOfFloors;
		int numberOfElevators;

};

int main(void)
{

	Building::getIntance().initializeBuilding(1, 50, 1);

	system("pause");
	return 0;

}