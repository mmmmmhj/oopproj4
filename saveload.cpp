#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<string>
#include<vector>
#include <sstream>
#include "CSphere.h"

using namespace std;


int score = 0, moves = 20;//denotes current user score

void gamesave(CSphere brd[][8]);
void gameload(CSphere brd[][8]);

void gamesave(CSphere *brd[][8]) //포인터로 받아야함-------------------------------------------

{
	fstream fout;
	fout.open("SaveData.txt", ios::out);
	if (fout.is_open())
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				fout << brd[i][j].getColor() << " "; //ㅇㄹ호ㅓㅏㅣㅓㅗㅎㄹㅇ
				fout << brd[i][j].getCenter().x << " ";
				fout << brd[i][j].getCenter().y << " ";
				fout << brd[i][j].getCenter().z << " ";
				fout << brd[i][j].getExist() << " "; //true = 1 false 0
				fout << endl;
			}

		}
		fout << " " << score << " " << moves;
		fout.close();

	}
}
void gameload(CSphere *brd[][8])
{
	string line;
	fstream fin;
	fin.open("SaveData.txt", ios::in);
	ifstream myfile("SaveData.txt");
	
	if (myfile.is_open())
	{
		int col = sizeof(brd) / sizeof(CSphere);
		int row = sizeof(brd) / sizeof(brd[0]);


		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				while (getline(myfile, line))
				{
					stringstream ss(line);
					string color, x, y, z, exist;
					ss >> color >> x >> y >> z >> exist;
					float X = stof(x);
					float Y = stof(y);
					float Z = stof(z);
					int Color = stoi(color);
					int exist_ = stoi(exist);
					bool Exist;

					if (exist_ == 0) {
						Exist = false;
					}
					else {
						Exist = true;
					}

					brd.resume(j, i, X, Y, Z, Color, Exist);

					break;
				}
			}
		}

		

		 
		fin >> score;
		fin >> moves;
		fin.close();
	}
	//cout <<score<< moves;

}
