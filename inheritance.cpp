#include <iostream>
using namespace std;

// Parent class

class Vehicle {
public:
	int price = 100;
private:
	int maxSpeed = 200;
protected:
	int numTyres = 300;
};

class Car : public Vehicle {
public:
	int numGears = 6;

	void print() {
		cout << numTyres << " " << maxSpeed << " " << price << endl;
	}
};

int main() {
	Car c1;
	c1.print();
}
