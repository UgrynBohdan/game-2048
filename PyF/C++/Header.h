#pragma once
#include <iostream>
using namespace std;

class Game_2048
{
private:
	int* field;
	int score;
public:
	Game_2048(); // �������� ��� � ��������� ����
	~Game_2048(); // �������� �� ��'����
	int Get_obj(int index); // ������� ��� � python
	void Create_square(int number); // ��������� ����� �������
	void Move_objs(char key); // ������ ��'����
	int Get_score(); // �������� �������
};



extern "C"
{
	__declspec(dllexport) Game_2048* Start_game() // �������� ���
	{
		srand(time(NULL));
		return new Game_2048();
	}
	
	__declspec(dllexport) void End_game(Game_2048* game) //��������� ���
	{
		delete game;
	}


	__declspec(dllexport) int Get_obj(Game_2048* game, int index) // �������� ��'����
	{
		return game->Get_obj(index);
	}

	__declspec(dllexport) void Create_square(Game_2048* game, int number) // ��������� ����� �������
	{
		game->Create_square(number);
	}

	__declspec(dllexport) void Move_objs(Game_2048* game, char key) // ������ ��'����
	{
		game->Move_objs(key);
	}

	__declspec(dllexport) int Get_score(Game_2048* game) // �������� �������
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