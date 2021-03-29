#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;


string main_known_input(double eq1_mX, double eq1_mY, double eq1_result, double eq2_mX, double eq2_mY, double eq2_result) {
	ostringstream s;

	if ((eq1_mX == 0) && (eq1_mY == 0) && (eq2_mX == 0) && (eq2_mY == 0) && (eq1_result == 0) && (eq2_result == 0)) {
		s << "5";
	}

	else if ((eq1_mX * eq2_mY - eq2_mX * eq1_mY != 0) && ((eq1_result * eq2_mY - eq1_mY * eq2_result != 0) || (eq1_mX * eq2_result - eq2_mX * eq1_result != 0))) {
		double y = (eq1_mX * eq2_result - eq2_mX * eq1_result) / (eq1_mX * eq2_mY - eq2_mX * eq1_mY);
		double x = (eq2_mY * eq1_result - eq1_mY * eq2_result) / (eq2_mY * eq1_mX - eq1_mY * eq2_mX);
		s << "2 " << x << ' ' << y;
	}

	else if (((eq1_mX * eq2_mY - eq2_mX * eq1_mY == 0) && ((eq1_result * eq2_mY - eq1_mY * eq2_result != 0) || (eq1_mX * eq2_result - eq2_mX * eq1_result != 0))) ||
		(eq1_mX == 0 && eq2_mX == 0 && eq1_result / eq1_mY != eq2_result / eq2_mY) ||
		(eq1_mY == 0 && eq2_mY == 0 && eq1_result / eq1_mX != eq2_result / eq2_mX) ||
		(eq1_mX == 0 && eq1_mY == 0 && eq2_mX == 0 && eq2_mY == 0 && (eq1_result / eq2_result > 0))) {
		if (((eq1_mX == 0 && eq1_mY == 0 && eq1_result == 0 && eq2_mY != 0 && eq2_mX == 0) ||
			(eq2_mX == 0 && eq2_mY == 0 && eq2_result == 0 && eq1_mY != 0 && eq1_mX == 0))) {
			double y;
			if (eq1_mY == 0)
				y = eq2_result / eq2_mY;
			else if (eq2_mY == 0)
				y = eq1_result / eq1_mY;
			else if (eq1_result == 0 || eq2_result == 0)
				y = 0;
			s << '4' << ' ' << y;
		}
		else if (((eq1_mX == 0 && eq1_mY == 0 && eq1_result == 0 && eq2_mX != 0 && eq2_mY == 0) ||
			(eq2_mX == 0 && eq2_mY == 0 && eq2_result == 0 && eq1_mX != 0 && eq1_mY == 0))) {
			double x;
			if (eq1_mX == 0)
				x = eq2_result / eq2_mX;
			else if (eq2_mX == 0)
				x = eq1_result / eq1_mX;
			else if (eq1_result == 0 || eq2_result == 0)
				x = 0;

			s << '3' << ' ' << x;
		}
		else {
			s << '0';
		}

	}
	else if (eq1_mX == 0 && eq2_mX == 0) {
		double y;
		if (eq1_result == 0)
			y = eq2_result / eq2_mY;
		else if (eq2_result == 0)
			y = eq1_result / eq1_mY;
		else
			y = eq1_result / eq1_mY;

		s << '4' << ' ' << y;
	}
	else if (eq1_mY == 0 && eq2_mY == 0) {
		double x;
		if (eq1_result == 0)
			x = eq2_result / eq2_mX;
		else if (eq2_result == 0)
			x = eq1_result / eq1_mX;
		else
			x = eq1_result / eq1_mX;
		s << '3' << ' ' << x;
	}
	else if (eq1_mY == 0 && eq1_result == 0) {
		double k, n;
		k = -eq2_mX / eq2_mY;
		n = eq2_result / eq2_mY;
		s << '1' << ' ' << k << ' ' << n;
	}
	else if (eq2_mY == 0 && eq2_result == 0) {
		double k, n;
		k = -eq1_mX / eq1_mY;
		n = eq1_result / eq1_mY;
		s << '1' << ' ' << k << ' ' << n;
	}
	else if (eq1_mX == 0 && eq1_result == 0) {
		double k, n;
		k = -eq2_mY / eq2_mX;
		n = eq2_result / eq2_mX;
		s << '1' << ' ' << k << ' ' << n;
	}
	else if (eq2_mX == 0 && eq2_result == 0) {
		double k, n;
		k = -eq1_mY / eq1_mX;
		n = eq1_result / eq1_mX;
		s << '1' << ' ' << k << ' ' << n;
	}
	else if ((eq1_mX / eq1_mY == eq2_mX / eq2_mY)) {
		double k, n;
		k = -eq2_mX / eq2_mY;
		n = eq2_result / eq2_mY;
		s << '1' << ' ' << k << ' ' << n;
	}
	else {
		s << "Are you kidding me?";
	}
	string ret = s.str();
	return ret;
}

int main() {
	//eq1_mX*x+eq1_mY*x=eq1_result   mX =multipleX
	//eq2_mX*x+eq2_mY*x=eq2_result
	while (true)
	{
		double eq1_mX, eq1_mY, eq2_mX, eq2_mY, eq1_result, eq2_result;
		cin >> eq1_mX >> eq1_mY >> eq1_result >> eq2_mX >> eq2_mY >> eq2_result;
		if ((eq1_mX == 0) && (eq1_mY == 0) && (eq2_mX == 0) && (eq2_mY == 0) && (eq1_result == 0) && (eq2_result == 0)) {
			cout << '5';
		}

		else if ((eq1_mX * eq2_mY - eq2_mX * eq1_mY != 0) && ((eq1_result * eq2_mY - eq1_mY * eq2_result != 0) || (eq1_mX * eq2_result - eq2_mX * eq1_result != 0))) {
			double y = (eq1_mX * eq2_result - eq2_mX * eq1_result) / (eq1_mX * eq2_mY - eq2_mX * eq1_mY);
			double x = (eq2_mY * eq1_result - eq1_mY * eq2_result) / (eq2_mY * eq1_mX - eq1_mY * eq2_mX);
			cout << "2 " << x << ' ' << y;
		}

		else if (((eq1_mX * eq2_mY - eq2_mX * eq1_mY == 0) && ((eq1_result * eq2_mY - eq1_mY * eq2_result != 0) || (eq1_mX * eq2_result - eq2_mX * eq1_result != 0))) ||
			(eq1_mX == 0 && eq2_mX == 0 && eq1_result / eq1_mY != eq2_result / eq2_mY) ||
			(eq1_mY == 0 && eq2_mY == 0 && eq1_result / eq1_mX != eq2_result / eq2_mX) ||
			(eq1_mX == 0 && eq1_mY == 0 && eq2_mX == 0 && eq2_mY == 0 && (eq1_result / eq2_result > 0))) {
			if (((eq1_mX == 0 && eq1_mY == 0 && eq1_result == 0 && eq2_mY != 0 && eq2_mX == 0) ||
				(eq2_mX == 0 && eq2_mY == 0 && eq2_result == 0 && eq1_mY != 0 && eq1_mX == 0))) {
				double y;
				if (eq1_mY == 0)
					y = eq2_result / eq2_mY;
				else if (eq2_mY == 0)
					y = eq1_result / eq1_mY;
				else if (eq1_result == 0 || eq2_result == 0)
					y = 0;
				cout << '4' << ' ' << y;
			}
			else if (((eq1_mX == 0 && eq1_mY == 0 && eq1_result == 0 && eq2_mX != 0 && eq2_mY == 0) ||
				(eq2_mX == 0 && eq2_mY == 0 && eq2_result == 0 && eq1_mX != 0 && eq1_mY == 0))) {
				double x;
				if (eq1_mX == 0)
					x = eq2_result / eq2_mX;
				else if (eq2_mX == 0)
					x = eq1_result / eq1_mX;
				else if (eq1_result == 0 || eq2_result == 0)
					x = 0;
				cout << '3' << ' ' << x;
			}
			else
				cout << '0';
		}
		else if (eq1_mX == 0 && eq2_mX == 0) {
			double y;
			if (eq1_result == 0)
				y = eq2_result / eq2_mY;
			else if (eq2_result == 0)
				y = eq1_result / eq1_mY;
			else
				y = eq1_result / eq1_mY;
			cout << '4' << ' ' << y;
		}
		else if (eq1_mY == 0 && eq2_mY == 0) {
			double x;
			if (eq1_result == 0)
				x = eq2_result / eq2_mX;
			else if (eq2_result == 0)
				x = eq1_result / eq1_mX;
			else
				x = eq1_result / eq1_mX;
			cout << '3' << ' ' << x;
		}
		else if (eq1_mY == 0 && eq1_result == 0) {
			double k, n;
			k = -eq2_mX / eq2_mY;
			n = eq2_result / eq2_mY;
			cout << '1' << ' ' << k << ' ' << n;
		}
		else if (eq2_mY == 0 && eq2_result == 0) {
			double k, n;
			k = -eq1_mX / eq1_mY;
			n = eq1_result / eq1_mY;
			cout << '1' << ' ' << k << ' ' << n;
		}
		else if (eq1_mX == 0 && eq1_result == 0) {
			double k, n;
			k = -eq2_mY / eq2_mX;
			n = eq2_result / eq2_mX;
			cout << '1' << ' ' << k << ' ' << n;
		}
		else if (eq2_mX == 0 && eq2_result == 0) {
			double k, n;
			k = -eq1_mY / eq1_mX;
			n = eq1_result / eq1_mX;
			cout << '1' << ' ' << k << ' ' << n;
		}
		else if ((eq1_mX / eq1_mY == eq2_mX / eq2_mY)) {
			double k, n;
			k = -eq2_mX / eq2_mY;
			n = eq2_result / eq2_mY;
			cout << '1' << ' ' << k << ' ' << n;
		}
		else {
			cout << "Are you kidding me?";
		}
		cout << endl;
	}
	
	return 0;
}

