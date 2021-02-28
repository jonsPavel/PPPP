#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int** create_Matrix(int Rows, int Columns) {
	cout << "Создание матрицы\n";
	int** Matrix = new int* [Rows];
	for (int i = 0; i < Rows; i++)
		Matrix[i] = new int[Columns];

	return Matrix;
}

void show_Matrix(int** Matrix, int Rows, int Columns) {
	for (int i = 0; i < Rows; i++) {
		for (int j = 0; j < Columns; j++)
			cout << Matrix[i][j] << " ";
		cout << endl;
	}
}

int** filling_zeros(int** Matrix, int Rows, int Columns) {
	cout << "Заполнение нулями\n";
	for (int i = 0; i < Rows; i++) {
		for (int j = 0; j < Columns; j++)
			Matrix[i][j] = 0;
	}
	return Matrix;
}

int** copy_matrix(int** Matrix_from, int** Matrix_inTo, int Rows, int Columns) {
	cout << "Ввод матрицы вручную:\n";
	for (int i = 0; i < Rows; i++) {
		for (int j = 0; j < Columns; j++)
			Matrix_inTo[i][j] = Matrix_from[i][j];
	}
	return Matrix_inTo;
}


int** manual_Matrix(int** inputMatrix, int Rows, int Columns) {
	cout << "Ручной ввод матрицы\n";
	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Columns; j++)
			cin >> inputMatrix[i][j];
	return inputMatrix;
}


int** randomize_Matrix(int** Matrix, int Rows, int Columns) {
	srand(time(NULL));
	cout << "Рандомизацмя матрицы\n";
	//int** Matrix = new int* [Rows];
	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Columns; j++)
			Matrix[i][j] = rand() % 10;
	return Matrix;
}




int main(){
	srand(time(NULL));
	int Rows_M1, Columns_M1, Rows_M2, Columns_M2, Input_case, NewSizeDeg2_Matrix = 2;
	system("chcp 1251");
	cout << "Вас приветствует программа" << endl <<
		"быстрого перемножения матриц методом Штрассена\n\n";

	///////////////////////////////////////////////////////////////////////////////
	////////////////////Ввод размеров матрицы пользователем////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	do
	{
		cout << "Введите размеры первой матрицы\n";
		cin >> Rows_M1 >> Columns_M1;
	} while (Rows_M1 <= 0 || Columns_M1 <= 0);
	do
	{
		cout << "Введите размеры второй матрицы\n";
		cin >> Rows_M2 >> Columns_M2;
	} while (Rows_M2 <= 0 || Columns_M2 <= 0);


	int** Matrix_1 = create_Matrix(Rows_M1, Columns_M1);
	int** Matrix_2 = create_Matrix(Rows_M2, Columns_M2);

	///////////////////////////////////////////////////////////////////////////////
	////////////////Выбор способа заполнения и заполнение матриц///////////////////
	///////////////////////////////////////////////////////////////////////////////

	do
	{
		cout << "Выберите способ заполнения матриц\n" <<
			"1 - Вручную \n2 - Случайным образом\n";
		cin >> Input_case;
	} while (Input_case < 1 || Input_case > 2);
	switch (Input_case)
	{
	case 1:
		Matrix_1 = manual_Matrix(Matrix_1, Rows_M1, Columns_M1);
		Matrix_2 = manual_Matrix(Matrix_2, Rows_M2, Columns_M2);

		cout << "\nМатрица 1\n\n";
		show_Matrix(Matrix_1, Rows_M1, Columns_M1);

		cout << "\nМатрица 2\n\n";
		show_Matrix(Matrix_2, Rows_M2, Columns_M2);
		break;
	case 2:
		Matrix_1 = randomize_Matrix(Matrix_1, Rows_M1, Columns_M1);
		Matrix_2 = randomize_Matrix(Matrix_2, Rows_M2, Columns_M2);

		cout << "\nМатрица 1\n\n";
		show_Matrix(Matrix_1, Rows_M1, Columns_M1);

		cout << "\nМатрица 2\n\n";
		show_Matrix(Matrix_2, Rows_M2, Columns_M2);
		break;
	}

	///////////////////////////////////////////////////////////////////////////////
	/////////////////Приведение матриц к требуемому размеру////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	while (NewSizeDeg2_Matrix < Rows_M1 || NewSizeDeg2_Matrix < Rows_M2 || NewSizeDeg2_Matrix < Columns_M1 || NewSizeDeg2_Matrix < Columns_M2)
		NewSizeDeg2_Matrix *= 2;
	//создание матриц нового размера
	int** Matrix_1_New = create_Matrix(NewSizeDeg2_Matrix, NewSizeDeg2_Matrix);
	int** Matrix_2_New = create_Matrix(NewSizeDeg2_Matrix, NewSizeDeg2_Matrix);
	
	Matrix_1_New = filling_zeros(Matrix_1_New,NewSizeDeg2_Matrix, NewSizeDeg2_Matrix);
	Matrix_2_New = filling_zeros(Matrix_2_New,NewSizeDeg2_Matrix, NewSizeDeg2_Matrix);

	//Копирование
	Matrix_1_New = copy_matrix(Matrix_1, Matrix_1_New, Rows_M1, Columns_M1);
	Matrix_2_New = copy_matrix(Matrix_2, Matrix_2_New, Rows_M2, Columns_M2);

	cout << "Приведенные матрицы\n";
	show_Matrix(Matrix_1_New, NewSizeDeg2_Matrix, NewSizeDeg2_Matrix);
	show_Matrix(Matrix_2_New, NewSizeDeg2_Matrix, NewSizeDeg2_Matrix);


	///////////////////////////////////////////////////////////////////////////////
	///////////////Разбиение матриц на подматрицы и их заполнение//////////////////
	///////////////////////////////////////////////////////////////////////////////


	int** Quarter1_Matrix1 = create_Matrix(NewSizeDeg2_Matrix / 2, NewSizeDeg2_Matrix / 2);
	int** Quarter2_Matrix1 = create_Matrix(NewSizeDeg2_Matrix / 2, NewSizeDeg2_Matrix / 2);
	int** Quarter3_Matrix1 = create_Matrix(NewSizeDeg2_Matrix / 2, NewSizeDeg2_Matrix / 2);
	int** Quarter4_Matrix1 = create_Matrix(NewSizeDeg2_Matrix / 2, NewSizeDeg2_Matrix / 2);

	int** Quarter1_Matrix2 = create_Matrix(NewSizeDeg2_Matrix / 2, NewSizeDeg2_Matrix / 2);
	int** Quarter2_Matrix2 = create_Matrix(NewSizeDeg2_Matrix / 2, NewSizeDeg2_Matrix / 2);
	int** Quarter3_Matrix2 = create_Matrix(NewSizeDeg2_Matrix / 2, NewSizeDeg2_Matrix / 2);
	int** Quarter4_Matrix2 = create_Matrix(NewSizeDeg2_Matrix / 2, NewSizeDeg2_Matrix / 2);




	for (int i = 0; i < NewSizeDeg2_Matrix / 2; i++){
		for (int j = 0; j < NewSizeDeg2_Matrix / 2; j++) {
			Quarter1_Matrix1[i][j] = Matrix_1_New[i][j];
			Quarter2_Matrix1[i][j] = Matrix_1_New[i][j + NewSizeDeg2_Matrix / 2];
			Quarter3_Matrix1[i][j] = Matrix_1_New[i + NewSizeDeg2_Matrix / 2][j];
			Quarter4_Matrix1[i][j] = Matrix_1_New[i + NewSizeDeg2_Matrix / 2][j + NewSizeDeg2_Matrix / 2];
		
			Quarter1_Matrix2[i][j] = Matrix_2_New[i][j];
			Quarter2_Matrix2[i][j] = Matrix_2_New[i][j + NewSizeDeg2_Matrix / 2];
			Quarter3_Matrix2[i][j] = Matrix_2_New[i + NewSizeDeg2_Matrix / 2][j];
			Quarter4_Matrix2[i][j] = Matrix_2_New[i + NewSizeDeg2_Matrix / 2][j + NewSizeDeg2_Matrix / 2];

		}
	}

	///////////////////////////////////////////////////////////////////////////////
	////////////////////////Создание промежуточных матриц//////////////////////////
	///////////////////////////////////////////////////////////////////////////////


	int** Intermediate_Matrix_1 = create_Matrix(NewSizeDeg2_Matrix / 2, NewSizeDeg2_Matrix / 2);
	int** Intermediate_Matrix_2 = create_Matrix(NewSizeDeg2_Matrix / 2, NewSizeDeg2_Matrix / 2);
	int** Intermediate_Matrix_3 = create_Matrix(NewSizeDeg2_Matrix / 2, NewSizeDeg2_Matrix / 2);
	int** Intermediate_Matrix_4 = create_Matrix(NewSizeDeg2_Matrix / 2, NewSizeDeg2_Matrix / 2);
	int** Intermediate_Matrix_5 = create_Matrix(NewSizeDeg2_Matrix / 2, NewSizeDeg2_Matrix / 2);
	int** Intermediate_Matrix_6 = create_Matrix(NewSizeDeg2_Matrix / 2, NewSizeDeg2_Matrix / 2);
	int** Intermediate_Matrix_7 = create_Matrix(NewSizeDeg2_Matrix / 2, NewSizeDeg2_Matrix / 2);

	///////////////////////////////////////////////////////////////////////////////
	////////////////////Вычисление значений промежуточных матриц///////////////////
	///////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < NewSizeDeg2_Matrix / 2; i++){
		for (int j = 0; j < NewSizeDeg2_Matrix / 2; j++){
			Intermediate_Matrix_1[i][j] = 0;
			Intermediate_Matrix_2[i][j] = 0;
			Intermediate_Matrix_3[i][j] = 0;
			Intermediate_Matrix_4[i][j] = 0;
			Intermediate_Matrix_5[i][j] = 0;
			Intermediate_Matrix_6[i][j] = 0;
			Intermediate_Matrix_7[i][j] = 0;

			for (int z = 0; z < NewSizeDeg2_Matrix / 2; z++){
				Intermediate_Matrix_1[i][j] += (Quarter1_Matrix1[i][z] + Quarter4_Matrix1[i][z]) * (Quarter1_Matrix2[z][j] + Quarter4_Matrix2[z][j]);
				Intermediate_Matrix_2[i][j] += (Quarter3_Matrix1[i][z] + Quarter4_Matrix1[i][z]) * Quarter1_Matrix2[z][j];
				Intermediate_Matrix_3[i][j] += Quarter1_Matrix1[i][z] * (Quarter2_Matrix2[z][j] - Quarter4_Matrix2[z][j]);
				Intermediate_Matrix_4[i][j] += Quarter4_Matrix1[i][z] * (Quarter3_Matrix2[z][j] - Quarter1_Matrix2[z][j]);
				Intermediate_Matrix_5[i][j] += (Quarter1_Matrix1[i][z] + Quarter2_Matrix1[i][z]) * Quarter4_Matrix2[z][j];
				Intermediate_Matrix_6[i][j] += (Quarter3_Matrix1[i][z] - Quarter1_Matrix1[i][z]) * (Quarter1_Matrix2[z][j] + Quarter2_Matrix2[z][j]);
				Intermediate_Matrix_7[i][j] += (Quarter2_Matrix1[i][z] - Quarter4_Matrix1[i][z]) * (Quarter3_Matrix2[z][j] + Quarter4_Matrix2[z][j]);
			}
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	///////////////////////Создание вспомогательных матриц/////////////////////////
	///////////////////////////////////////////////////////////////////////////////
	int** Auxiliary_Matrix_1 = create_Matrix(NewSizeDeg2_Matrix / 2, NewSizeDeg2_Matrix / 2);
	int** Auxiliary_Matrix_2 = create_Matrix(NewSizeDeg2_Matrix / 2, NewSizeDeg2_Matrix / 2);
	int** Auxiliary_Matrix_3 = create_Matrix(NewSizeDeg2_Matrix / 2, NewSizeDeg2_Matrix / 2);
	int** Auxiliary_Matrix_4 = create_Matrix(NewSizeDeg2_Matrix / 2, NewSizeDeg2_Matrix / 2);


	///////////////////////////////////////////////////////////////////////////////
	////////////Подсчет значений вспомогательных матриц из промежуточных///////////
	///////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < NewSizeDeg2_Matrix / 2; i++){
		for (int j = 0; j < NewSizeDeg2_Matrix / 2; j++){
			Auxiliary_Matrix_1[i][j] = Intermediate_Matrix_1[i][j] + Intermediate_Matrix_4[i][j] - Intermediate_Matrix_5[i][j] + Intermediate_Matrix_7[i][j];
			Auxiliary_Matrix_2[i][j] = Intermediate_Matrix_3[i][j] + Intermediate_Matrix_5[i][j];
			Auxiliary_Matrix_3[i][j] = Intermediate_Matrix_2[i][j] + Intermediate_Matrix_4[i][j];
			Auxiliary_Matrix_4[i][j] = Intermediate_Matrix_1[i][j] - Intermediate_Matrix_2[i][j] + Intermediate_Matrix_3[i][j] + Intermediate_Matrix_6[i][j];
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	///////////////////Создание результирующей матрицы/////////////////////////////
	///////////////////////////////////////////////////////////////////////////////


	int** result_Matrix = create_Matrix(NewSizeDeg2_Matrix, NewSizeDeg2_Matrix);

	///////////////////////////////////////////////////////////////////////////////
	///////Занесение информации из вспомогательных матриц в результирующую/////////
	///////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < NewSizeDeg2_Matrix / 2; i++){
		for (int j = 0; j < NewSizeDeg2_Matrix / 2; j++){
			result_Matrix[i][j] = Auxiliary_Matrix_1[i][j];
			result_Matrix[i][j + NewSizeDeg2_Matrix / 2] = Auxiliary_Matrix_2[i][j];
			result_Matrix[i + NewSizeDeg2_Matrix / 2][j] = Auxiliary_Matrix_3[i][j];
			result_Matrix[i + NewSizeDeg2_Matrix / 2][j + NewSizeDeg2_Matrix / 2] = Auxiliary_Matrix_4[i][j];
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	////////////////Выравнивание границ результирующей матрицы/////////////////////
	///////////////////////////////////////////////////////////////////////////////

	int x = 0, f = 100, s = 100;
	for (int i = 0; i < NewSizeDeg2_Matrix; i++){
		x = 0;
		for (int j = 0; j < NewSizeDeg2_Matrix; j++){
			if (result_Matrix[i][j] != 0){
				x++;
				f = 100;
			}
		}
		if (x == 0 && i < f){
			f = i;
		}
	}
	for (int i = 0; i < NewSizeDeg2_Matrix; i++){
		x = 0;
		for (int j = 0; j < NewSizeDeg2_Matrix; j++){
			if (result_Matrix[j][i] != 0){
				x++;
				s = 100;
			}
		}
		if (x == 0 && i < s){
			s = i;
		}
	}

	int** result_Matrix_aligned = create_Matrix(f, s);
	for (int i = 0; i < f; i++){
		for (int j = 0; j < s; j++)
			result_Matrix_aligned[i][j] = result_Matrix[i][j];
	}

	///////////////////////////////////////////////////////////////////////////////
	///////////////////Вывод результирующей матрицы////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	cout << "\nРезультирующая матрица\n\n";
	for (int i = 0; i < f; i++){
		for (int j = 0; j < s; j++)
			cout << result_Matrix_aligned[i][j] << " ";
		cout << endl;
	}

	system("pause");

	///////////////////////////////////////////////////////////////////////////////
	/////////////////////Очистка динамической памяти///////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < Rows_M1; i++)
		delete[] Matrix_1[i];
	for (int i = 0; i < Rows_M2; i++)
		delete[] Matrix_2[i];
	for (int i = 0; i < NewSizeDeg2_Matrix; i++)
	{
		delete[] Matrix_1_New[i];
		delete[] Matrix_2_New[i];
		delete[] result_Matrix[i];
	}
	for (int i = 0; i < f; i++)
		delete[] result_Matrix_aligned[i];
	for (int i = 0; i < NewSizeDeg2_Matrix / 2; i++)
	{
		delete[] Quarter1_Matrix1[i];
		delete[] Quarter2_Matrix1[i];
		delete[] Quarter3_Matrix1[i];
		delete[] Quarter4_Matrix1[i];
		delete[] Quarter1_Matrix2[i];
		delete[] Quarter2_Matrix2[i];
		delete[] Quarter3_Matrix2[i];
		delete[] Quarter4_Matrix2[i];
		delete[] Auxiliary_Matrix_1[i];
		delete[] Auxiliary_Matrix_2[i];
		delete[] Auxiliary_Matrix_3[i];
		delete[] Auxiliary_Matrix_4[i];
		delete[] Intermediate_Matrix_1[i];
		delete[] Intermediate_Matrix_2[i];
		delete[] Intermediate_Matrix_3[i];
		delete[] Intermediate_Matrix_4[i];
		delete[] Intermediate_Matrix_5[i];
		delete[] Intermediate_Matrix_6[i];
		delete[] Intermediate_Matrix_7[i];
	}
	delete[] Matrix_1, Matrix_2, Matrix_1_New, Matrix_2_New, result_Matrix, result_Matrix_aligned;
	delete[] Quarter1_Matrix1, Quarter2_Matrix1, Quarter3_Matrix1, Quarter4_Matrix1, Quarter1_Matrix2, Quarter2_Matrix2, Quarter3_Matrix2, Quarter4_Matrix2, Auxiliary_Matrix_1, Auxiliary_Matrix_2, Auxiliary_Matrix_3, Auxiliary_Matrix_4;
	delete[] Intermediate_Matrix_1, Intermediate_Matrix_2, Intermediate_Matrix_3, Intermediate_Matrix_4, Intermediate_Matrix_5, Intermediate_Matrix_6, Intermediate_Matrix_7;
	return 0;
}