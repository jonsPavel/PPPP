#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <map>
#include <tuple>
#include "Lab3_header.h"
#include <vector>
#include <memory>
constexpr auto SIZE = 16;

const std::string points[SIZE] = { "msk_AP","msk_TS","msk_WH","mzh_TS",
"mzh_WH","zvn_WH","NN_AP","NN_TS", "NN_WH","dzr_TS","dzr_WH",
"vlg_AP","vlg_TS","vlg_WH","kam_TS","kam_WH" };

const std::map<std::string, int> towns = {
	{"Moscow", 2},
	{"Mozhaisk", 4},
	{"Zvenigorod", 5},
	{"Nizhniy Novgorod", 8},
	{"Dzerzhinsk", 10},
	{"Volgograd", 13},
	{"Kamishin", 15} };

const std::map<std::string, int> table = {
	{"msk", 0},
	{"mzh", 1},
	{"zvn", 2},
	{"NN", 3},
	{"dzr", 4},
	{"vlg", 5},
	{"kam", 6} };

const std::tuple<int, int, double> tableCost[21] = {
	{500, 300, 100},
	{200, 100, 500},
	{100, 60, 50},
	{0, 0, 0},
	{200, 100, 500},
	{100, 60, 50},
	{0, 0, 0},
	{0, 0, 0},
	{100, 60, 50},
	{500, 300, 100},
	{200, 100, 500},
	{100, 60, 50},
	{0, 0, 0},
	{200, 100, 500},
	{100, 60, 50},
	{500, 300, 100},
	{200, 100, 500},
	{100, 60, 50},
	{0, 0, 0},
	{200, 100, 500},
	{100, 60, 50} };

const int matrixDist[SIZE][SIZE] = {
{0, 20, 30, 108, 110, 65, 398, 0, 0, 0, 0, 926, 0, 0, 0, 0},
{20, 0, 10, 98, 100, 55, 0, 415, 0, 483, 0, 0, 937, 0, 1204, 0},
{30, 10, 0, 108, 110, 65, 0, 0, 430, 0, 390, 0, 0, 652, 0, 1234},
{108, 98, 108, 0, 5, 0, 0, 0, 0, 581, 0, 0, 1035, 0, 1302, 0},
{110, 100, 110, 5, 0, 78, 0, 0, 540, 0, 500, 0, 0 ,1062, 0, 1344},
{65, 55, 65, 0, 78, 0, 0, 0, 495, 0, 455, 0, 0, 1017, 0, 1299},
{398, 0, 0, 0, 0, 0, 0, 19, 23, 0, 26, 828, 0, 0, 0, 0},
{0, 415, 0, 0, 0, 0 ,19, 0, 4, 32, 0, 0, 840, 0, 919, 0},
{0, 0, 430, 0, 540, 495, 23, 4, 0, 0, 40, 0, 0, 849, 0, 1010},
{0, 483, 0, 581, 0, 0, 0, 32, 0, 0, 4, 0, 872, 0, 951, 0},
{0, 0, 390, 0, 500, 455, 26, 0, 40, 4, 0, 0, 0, 889, 0, 1050},
{926, 0, 0, 0, 0 ,0 ,828, 0, 0 ,0 ,0, 0, 15, 16, 0, 285},
{0, 937, 0, 1035, 0, 0, 0, 840, 0, 872, 0, 15, 0, 2, 257, 281},
{0, 0, 952, 0, 1062, 1017, 0, 0, 849, 0, 889, 16, 2, 0, 0 ,282},
{0, 1204, 0, 1302, 0, 0, 0, 919, 0, 951, 0, 0, 257, 0, 0, 2},
{0, 0, 1234, 0, 1344, 1299, 0, 0, 1010, 0, 1050, 285, 281, 282, 2, 0} };


enum Type { Turbo, Standart, Economy };


//#########################################################################
//########################Pattern Builder##################################
//#########################################################################

//Way
class Transport {
protected:
	int speed;
	int volume;
	double price;
	int distance;
public:

	void SetSpeed(const int& d) { speed = d; }
	void SetVolume(const int& s) { volume = s; }
	void SetPrice(const double& t) { price = t; }
	void SetDistance(const int& t) { distance = t; }

	double sumCost(int mass, int dist) {
		return (mass / volume) * sumTime(dist) * price;
	}

	double sumTime(int dist) {
		return dist / speed;
	}

	int getDistance() {
		return this->distance;
	}
};


// Abstract Builder
class TransportBuilder
{
protected:
	std::shared_ptr<Transport> transport;
public:
	TransportBuilder() {}
	~TransportBuilder() {}
	std::shared_ptr<Transport> GetTransport() { return transport; }

	void createNewTransportWay() { transport.reset(new Transport); }

	virtual void buildSpeed() = 0;
	virtual void buildVolume() = 0;
	virtual void buildPrice() = 0;
	virtual void buildDistance() = 0;

};

// ConcreteBuilder
class TrainTransportBuilder :TransportBuilder {
public:
	TrainTransportBuilder() : TransportBuilder() {}
	~TrainTransportBuilder() {}

	void buildSpeed() { transport->SetSpeed(100); }
	void buildVolume() { transport->SetVolume(500); }
	void buildPrice() { transport->SetPrice(200); }
	void buildDistane() { transport->SetDistance(0); }
};

// ConcreteBuilder
class CarTransportBuilder :TransportBuilder {
public:
	CarTransportBuilder() : TransportBuilder() {}
	~CarTransportBuilder() {}

	void buildSpeed() { transport->SetSpeed(60); }
	void buildVolume() { transport->SetVolume(50); }
	void buildPrice() { transport->SetPrice(100); }
	void buildDistane() { transport->SetDistance(0); }
};

// ConcreteBuilder
class PlaneTransportBuilder :TransportBuilder {
public:
	PlaneTransportBuilder() : TransportBuilder() {}
	~PlaneTransportBuilder() {}

	void buildSpeed() { transport->SetSpeed(300); }
	void buildVolume() { transport->SetVolume(100); }
	void buildPrice() { transport->SetPrice(500); }
	void buildDistane() { transport->SetDistance(0); }
};


// Director
class Passenger {
private:
	TransportBuilder* transportBuilder;
public:
	Passenger() : transportBuilder(nullptr) {}
	~Passenger() { }

	void SetTransportBuilder(TransportBuilder* b) { transportBuilder = b; }
	std::shared_ptr<Transport> GetTransport() { return transportBuilder->GetTransport(); }
	void ConstructTransport()
	{
		transportBuilder->createNewTransportWay();
		transportBuilder->buildSpeed();
		transportBuilder->buildVolume();
		transportBuilder->buildPrice();
		transportBuilder->buildDistance();
	}
};

// Пассажир составляет путь
int main(){
	Passenger passenger;

	CarTransportBuilder carTransportBuilder;
	passenger.SetTransportBuilder(&carTransportBuilder);
	passenger.ConstructTransport();
	std::shared_ptr<Transport> car = passenger.GetTransport();

	TrainTransportBuilder trainTransportBuilder;
	passenger.SetTransportBuilder(&trainTransportBuilder);
	passenger.ConstructTransport();
	std::shared_ptr<Transport> train = passenger.GetTransport();

	PlaneTransportBuilder planeTransportBuilder;
	passenger.SetTransportBuilder(&planeTransportBuilder);
	passenger.ConstructTransport();
	std::shared_ptr<Transport> plane = passenger.GetTransport();


	return EXIT_SUCCESS;
}

class Track {
	double cost;
	double time;
	int volume;
public:
	std::vector <Transport> vc;


	Track() {
		this->cost = 0;
		this->time = 0;
		this->volume = 0;
	}
	Track(Car car1, int volume) {
		cost = car1.sumCost(volume, car1.getDistance());
		time = car1.sumTime(car1.getDistance());
	}
	Track(Car car1, Car car2, Train train1, int volume) {
		cost = car1.sumCost(volume, car1.getDistance()) + car2.sumCost(volume, car2.getDistance());
		time = car1.sumTime(car1.getDistance()) + car2.sumTime(car2.getDistance());
		cost += train1.sumCost(volume, train1.getDistance());
		time += train1.sumTime(train1.getDistance());
	}
	Track(Car car1, Car car2, Plane plane1, int volume) {
		cost = car1.sumCost(volume, car1.getDistance()) + car2.sumCost(volume, car2.getDistance());
		time = car1.sumTime(car1.getDistance()) + car2.sumTime(car2.getDistance());
		cost += plane1.sumCost(volume, plane1.getDistance());
		time += plane1.sumTime(plane1.getDistance());
	}
	Track(Car car1, Car car2, Car car3, Train train1, Plane plane1, int volume) {
		cost = car1.sumCost(volume, car1.getDistance()) + car2.sumCost(volume, car2.getDistance()) + car3.sumCost(volume, car3.getDistance());
		time = car1.sumTime(car1.getDistance()) + car2.sumTime(car2.getDistance()) + car3.sumTime(car3.getDistance());
		cost += train1.sumCost(volume, train1.getDistance());
		time += train1.sumTime(train1.getDistance());
		cost += plane1.sumCost(volume, plane1.getDistance());
		time += plane1.sumTime(plane1.getDistance());
	}
	Track(Car car1, Car car2, Car car3, Car car4, Train train1, Train train2, Plane plane1, int volume) {
		cost = car1.sumCost(volume, car1.getDistance()) + car2.sumCost(volume, car2.getDistance()) + car3.sumCost(volume, car3.getDistance()) + car4.sumCost(volume, car4.getDistance());
		time = car1.sumTime(car1.getDistance()) + car2.sumTime(car2.getDistance()) + car3.sumTime(car3.getDistance()) + car4.sumTime(car4.getDistance());
		cost += train1.sumCost(volume, train1.getDistance()) + train2.sumCost(volume, train2.getDistance());
		time += train1.sumTime(train1.getDistance()) + train2.sumTime(train2.getDistance());
		cost += plane1.sumCost(volume, plane1.getDistance());
		time += plane1.sumTime(plane1.getDistance());
	}

	double getCost() {
		return this->cost;
	}

};


class Order {
	double cost;
	int volume;
	std::string startPoint;
	std::string finishPoint;
	enum::Type type;
	Track track;
public:
	Order() {
		this->cost = 0;
		this->volume = 0;
		this->startPoint = "";
		this->finishPoint = "";
		this->track = Track();
		this->type = Type::Economy;
	}

	Order(Type deliv, std::string startP, std::string finishP, int vol) {
		this->startPoint = startP;
		this->finishPoint = finishP;
		type = deliv;
		this->track = best(startP, finishP, deliv, vol);
		this->cost = track.getCost();
		this->volume = vol;
	}
	~Order() {

	}
	int decr(std::string);
	int** matrixUpd(Type);
	int* optim(int**, int, int);
	Track best(std::string, std::string, Type, int);

};

Track Order::best(std::string startP, std::string finishP, Type deliv, int volume) {
	int start = decr(startP);
	int finish = decr(finishP);
	int** mat = new int* [SIZE];
	for (int i = 0; i < SIZE; i++)
		mat[i] = new int[SIZE];
	mat = matrixUpd(deliv);
	int* path = new int[SIZE];
	for (int i = 0; i < SIZE; i++) {
		path[i] = -1;
	}
	path = optim(mat, start, finish);
	int count = 0;
	for (int i = 0; i < SIZE; i++) {
		if (path[i] != -1) {
			count++;
		}
		else {
			break;
		}
	}
	switch (count) {
	case 1: {
		Car car1 = Car();
		for (auto it = table.begin(); it != table.end(); it++) {
			if ((*it).first.find(points[path[0]])) {
				car1 = Car(tableCost[(*it).second * 3 + 2], matrixDist[path[0]][path[1]]);
			}
		}

		Track track = Track(car1, volume);
		return track;
	}
	case 3: {
		Car car1 = Car();
		for (auto it = table.begin(); it != table.end(); it++) {
			if ((*it).first.find(points[path[0]])) {
				car1 = Car(tableCost[(*it).second * 3 + 2], matrixDist[path[0]][path[1]]);
			}
		}

		Car car2 = Car();
		for (auto it = table.begin(); it != table.end(); it++) {
			if ((*it).first.find(points[path[2]])) {
				car2 = Car(tableCost[(*it).second * 3 + 2], matrixDist[path[2]][path[3]]);
			}
		}

		Train train1 = Train();
		Plane plane1 = Plane();
		Track track = Track();

		for (auto it = table.begin(); it != table.end(); it++) {
			if ((*it).first.find(points[path[1]]) && points[path[1]].find("TS")) {
				train1 = Train(tableCost[(*it).second * 3 + 1], matrixDist[path[1]][path[2]]);
				track = Track(car1, car2, train1, volume);
			}

			if ((*it).first.find(points[path[1]]) && points[path[1]].find("AP")) {
				plane1 = Plane(tableCost[(*it).second * 3], matrixDist[path[1]][path[2]]);
				track = Track(car1, car2, plane1, volume);
			}
		}

		return track;
	}
	case 5: {

		Car car1 = Car();
		for (auto it = table.begin(); it != table.end(); it++) {
			if ((*it).first.find(points[path[0]])) {
				car1 = Car(tableCost[(*it).second * 3 + 2], matrixDist[path[0]][path[1]]);
			}
		}

		Train train1 = Train();
		Plane plane1 = Plane();
		for (auto it = table.begin(); it != table.end(); it++) {
			if ((*it).first.find(points[path[1]]) && points[path[1]].find("TS")) {
				train1 = Train(tableCost[(*it).second * 3 + 1], matrixDist[path[1]][path[2]]);
			}
			if ((*it).first.find(points[path[1]]) && points[path[1]].find("AP")) {
				plane1 = Plane(tableCost[(*it).second * 3], matrixDist[path[1]][path[2]]);
			}
		}

		Car car2 = Car();
		for (auto it = table.begin(); it != table.end(); it++) {
			if ((*it).first.find(points[path[2]])) {
				car2 = Car(tableCost[(*it).second * 3 + 2], matrixDist[path[2]][path[3]]);
			}
		}

		for (auto it = table.begin(); it != table.end(); it++) {
			if ((*it).first.find(points[path[3]]) && points[path[3]].find("AP")) {
				plane1 = Plane(tableCost[(*it).second * 3], matrixDist[path[3]][path[4]]);
			}
			if ((*it).first.find(points[path[3]]) && points[path[3]].find("TS")) {
				train1 = Train(tableCost[(*it).second * 3 + 1], matrixDist[path[3]][path[4]]);
			}
		}

		Car car3 = Car();
		for (auto it = table.begin(); it != table.end(); it++) {
			if ((*it).first.find(points[path[4]])) {
				car3 = Car(tableCost[(*it).second * 3 + 2], matrixDist[path[4]][path[5]]);
			}
		}

		Track track = Track(car1, car2, car3, train1, plane1, volume);
		return track;
	}

	case 7: {
		Car car1 = Car();
		for (auto it = table.begin(); it != table.end(); it++) {
			if ((*it).first.find(points[path[0]]))
			{
				car1 = Car(tableCost[(*it).second * 3 + 2], matrixDist[path[0]][path[1]]);
			}
		}

		Train train1 = Train();
		for (auto it = table.begin(); it != table.end(); it++) {
			if ((*it).first.find(points[path[1]])) {
				train1 = Train(tableCost[(*it).second * 3 + 1], matrixDist[path[1]][path[2]]);
			}
		}

		Car car2 = Car();
		for (auto it = table.begin(); it != table.end(); it++) {
			if ((*it).first.find(points[path[2]])) {
				car2 = Car(tableCost[(*it).second * 3 + 2], matrixDist[path[2]][path[3]]);
			}
		}

		Plane plane1 = Plane();
		for (auto it = table.begin(); it != table.end(); it++) {
			if ((*it).first.find(points[path[3]])) {
				plane1 = Plane(tableCost[(*it).second * 3], matrixDist[path[3]][path[4]]);
			}
		}

		Car car3 = Car();
		for (auto it = table.begin(); it != table.end(); it++) {
			if ((*it).first.find(points[path[4]])) {
				car3 = Car(tableCost[(*it).second * 3 + 2], matrixDist[path[4]][path[5]]);
			}
		}

		Train train2 = Train();
		for (auto it = table.begin(); it != table.end(); it++) {
			if ((*it).first.find(points[path[5]])) {
				train2 = Train(tableCost[(*it).second * 3 + 1], matrixDist[path[5]][path[6]]);
			}
		}

		Car car4 = Car();
		for (auto it = table.begin(); it != table.end(); it++) {
			if ((*it).first.find(points[path[6]])) {
				car4 = Car(tableCost[(*it).second * 3 + 2], matrixDist[path[6]][path[7]]);
			}
		}

		Track track = Track(car1, car2, car3, car4, train1, train2, plane1, volume);

		return track;
	}
	}
}


int** Order::matrixUpd(Type type) {
	int** matrix = new int* [SIZE];
	for (int i = 0; i < SIZE; i++) {
		matrix[i] = new int[SIZE];
		for (int j = 0; j < SIZE; j++)
		{
			matrix[i][j] = matrixDist[i][j];
		}
	}
	switch (type) {
	case Economy:
		for (int i = 0; i < SIZE; i++) {
			if (points[i].find("TS"))
				for (int j = 0; j < SIZE; j++)
					matrix[i][j] = 99999;
		}
	case Standart:
		for (int i = 0; i < SIZE; i++) {
			if (points[i].find("AP"))
				for (int j = 0; j < SIZE; j++)
					matrix[i][j] = 99999;
		}
	case Turbo:
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++)
				if (matrix[i][j] == 0)
					matrix[i][j] = 99999;
		}
	}
	return matrix;
}

int* Order::optim(int** arr, int beginPoint, int endPoint) {
	int* d = new int[SIZE];
	int* v = new int[SIZE];
	int temp, minindex, min;
	int begin_index = beginPoint;

	for (int i = 0; i < SIZE; i++) {
		d[i] = 99999;
		v[i] = 1;
	}
	d[begin_index] = 0;

	do {
		minindex = 99999;
		min = 99999;
		for (int i = 0; i < SIZE; i++) {
			if ((v[i] == 1) && (d[i] < min)) {
				min = d[i];
				minindex = i;
			}
		}

		if (minindex != 99999) {
			for (int i = 0; i < SIZE; i++) {
				if (arr[minindex][i] > 0) {
					temp = min + arr[minindex][i];
					if (temp < d[i]) {
						d[i] = temp;
					}
				}
			}
			v[minindex] = 0;
		}
	} while (minindex < 99999);

	int* ver = new int[SIZE];
	int end = endPoint;
	ver[0] = end;
	int k = 1;
	int weight = d[end];

	while (end != begin_index) {
		for (int i = 0; i < SIZE; i++)
			if (arr[end][i] != 0) {
				int temp = weight - arr[end][i];
				if (temp == d[i]) {
					weight = temp;
					end = i;
					ver[k] = i + 1;
					k++;
				}
			}
	}
	for (int i = 0; i < k / 2; i++)
		std::swap(ver[i], ver[k - 1 - i]);
	delete[] d, v;
	return ver;
}

int Order::decr(std::string str) {
	for (auto it = towns.begin(); it != towns.end(); it++) {
		if (str._Equal((*it).first))
			return (*it).second;
	}
	return -1;
}
