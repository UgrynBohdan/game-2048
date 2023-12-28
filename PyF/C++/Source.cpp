#include "Header.h"

Game_2048::Game_2048() // починаємо гру з створення поля
{
	this->field = new int[4 * 4] {};
	this->score = 0;
}

Game_2048::~Game_2048() // видаляєм всі об'єкти
{
	delete[] this->field; // видаляємо сам масив
}


int Game_2048::Get_obj(int index) // передаєм дані
{
	return this->field[index];
}

void Game_2048::Create_square(int number) // створюємо новий квадрат
{
	for (int i = rand() % 4, j = rand() % 4; 1; i = rand() % 4, j = rand() % 4) // випадково вибираємо місце
		if (this->field[i * 4 + j] == 0)
		{
			this->field[i * 4 + j] = number;
			return;
		}
}

void Game_2048::Move_objs(char key)
{
	// тричі зміщуємо всі об'єкти окрім тих які розташовані у крайному рядку
	// зміщуємо у бік цього рядка
	switch (key)
	{
	case 'w':
		for (int k = 0; k < 3; k++)
			for (int i = 1; i < 4; i++) // рухаємось вгору тому 1 рядок не рухаємо
				for (int j = 0; j < 4; j++)
					if (this->field[i * 4 + j] != 0)
						if (this->field[(i - 1) * 4 + j] == 0) // якщо є вільне місце то записуємо цифру туди
						{
							this->field[(i - 1) * 4 + j] = this->field[i * 4 + j];
							this->field[i * 4 + j] = 0;
						}
						else if (this->field[(i - 1) * 4 + j] == this->field[i * 4 + j]) // якщо ні то перевіряємо чи є 2 об'єкти ідентичні
						{
							this->field[(i - 1) * 4 + j] *= 2;
							this->field[i * 4 + j] = 0;
							this->score += this->field[(i - 1) * 4 + j];
						}
		break;
	case 's':
		for (int k = 0; k < 3; k++)
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 4; j++)
					if (this->field[i * 4 + j] != 0)
						if (this->field[(i + 1) * 4 + j] == 0)
						{
							this->field[(i + 1) * 4 + j] = this->field[i * 4 + j];
							this->field[i * 4 + j] = 0;
						}
						else if (this->field[(i + 1) * 4 + j] == this->field[i * 4 + j])
						{
							this->field[(i + 1) * 4 + j] *= 2;
							this->field[i * 4 + j] = 0;
							this->score += this->field[(i + 1) * 4 + j];
						}
		break;
	case 'a':
		for (int k = 0; k < 3; k++)
			for (int i = 0; i < 4; i++)
				for (int j = 1; j < 4; j++)
					if (this->field[i * 4 + j] != 0)
						if (this->field[i * 4 + j - 1] == 0)
						{
							this->field[i * 4 + j - 1] = this->field[i * 4 + j];
							this->field[i * 4 + j] = 0;
						}
						else if (this->field[i * 4 + j - 1] == this->field[i * 4 + j])
						{
							this->field[i * 4 + j - 1] *= 2;
							this->field[i * 4 + j] = 0;
							this->score += this->field[i * 4 + j - 1];
						}
		break;
	case 'd':
		for (int k = 0; k < 3; k++)
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 3; j++)
					if (this->field[i * 4 + j] != 0)
						if (this->field[i * 4 + j + 1] == 0)
						{
							this->field[i * 4 + j + 1] = this->field[i * 4 + j];
							this->field[i * 4 + j] = 0;
						}
						else if (this->field[i * 4 + j + 1] == this->field[i * 4 + j])
						{
							this->field[i * 4 + j + 1] *= 2;
							this->field[i * 4 + j] = 0;
							this->score += this->field[i * 4 + j + 1];
						}
		break;
	default:
		break;
	}
}

int Game_2048::Get_score()
{
	return this->score;
}


//ctrl + k && ctrl + f


//int sum(int a, int b)
//{
//	return a + b;
//}


//extern "C" __declspec(dllexport) int sum(int a, int b)
//{
//	return a + b;
//}
//extern "C" __declspec(dllexport) void printUC(char a[])
//{
//	cout << "Прив " << a << endl;
//}
//extern "C" __declspec(dllexport) void start()
//{
//	system("chcp 1251");
//}