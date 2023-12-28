#pragma once
#include <iostream>
using namespace std;

class Game_2048
{
private:
	int* field;
	int score;
public:
	Game_2048(); // починаємо гру з створення поля
	~Game_2048(); // видаляєм всі об'єкти
	int Get_obj(int index); // передаєм дані в python
	void Create_square(int number); // створюємо новий квадрат
	void Move_objs(char key); // рухаємо об'єкти
	int Get_score(); // отримаємо рахунок
};



extern "C"
{
	__declspec(dllexport) Game_2048* Start_game() // починаємо гру
	{
		srand(time(NULL));
		return new Game_2048();
	}
	
	__declspec(dllexport) void End_game(Game_2048* game) //завершуємо гру
	{
		delete game;
	}


	__declspec(dllexport) int Get_obj(Game_2048* game, int index) // передаємо об'єкти
	{
		return game->Get_obj(index);
	}

	__declspec(dllexport) void Create_square(Game_2048* game, int number) // створюємо новий квадрат
	{
		game->Create_square(number);
	}

	__declspec(dllexport) void Move_objs(Game_2048* game, char key) // рухаємо об'єкти
	{
		game->Move_objs(key);
	}

	__declspec(dllexport) int Get_score(Game_2048* game) // отримаємо рахунок
	{
		return game->Get_score();
	}
}






















//extern "C"
//{
//	__declspec(dllexport) int sum(int a, int b);
//}













//extern "C" __declspec(dllexport) int sum(int, int);
//extern "C" __declspec(dllexport) void printUC(char a[]);
//extern "C" __declspec(dllexport) void start();