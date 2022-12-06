#include <stdio.h>
#include <vector>
#include "CWall.h"
#include "CSphere.h"
#include <random>

using namespace std;

class Board {

private:
    CSphere brd[10][8];
    float x_bdCtr, y_bdCtr, z_bdCtr;
    int rBoundary;
    int empFl = -3;

public:

    //Board() {
    //            x_bdCtr = gamemanager.getcenter_x();
    //            y_bdCtr = gamemanager.getcenter_y();
    //            z_bdCtr = gamemanager.getcenter_z();
    //}



    Board(float X, float Y, float Z, IDirect3DDevice9* pDevice, float depth) {

        this->x_bdCtr = X;
        this->y_bdCtr = Y;
        this->z_bdCtr = Z;

        rBoundary = 3;

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dis(1, 4);

        // �߽� �������� ���� x z �ʱ���ǥ ����

        for (int i = 0; i < sizeof(brd) / sizeof(brd[0]); i++) //row
        {
            for (int j = 0; j < sizeof(brd) / sizeof(CSphere); j++) //col
            {
                
				brd[i][j].create(pDevice);

                int color = dis(gen);
				if (color == 1)
					brd[i][j].setColor(d3d::YELLOW);
				else if (color == 2)
					brd[i][j].setColor(d3d::RED);
                else if(color==3)
                    brd[i][j].setColor(d3d::BLUE);
                else
                    brd[i][j].setColor(d3d::GREEN);

                //��ġ ����
                if (i % 2 == 0) {
                    brd[i][j].setCenter(x_bdCtr - (sizeof(brd[0]) / sizeof(*brd[0]) / 2 - 0.5 - j) * brd[i][j].getRadius() / 0.5, 0, z_bdCtr + depth / 2 - i * brd[i][j].getRadius() / 0.5);
                }
                else if (i % 2 == 1) {
                    brd[i][j].setCenter(x_bdCtr - (sizeof(brd[0]) / sizeof(*brd[0]) / 2 - j) * brd[i][j].getRadius(), 0, z_bdCtr + depth / 2 - i * brd[i][j].getRadius());
                }

                if (i > 4)
                {
                    brd[i][j].setExist(false);
                    brd[i][j].setColor(d3d::MAGENTA);
                }
            }
        }
    }

    void destroy(int m, int n, int col) {
        this->chNeighball(m, n, col, 1);
        
        for (int i = 0; i < sizeof(brd[0]) / sizeof(*brd[0]); i++) {
            if (brd[rBoundary][i].getExist())
                break;
            else if (i == sizeof(brd[0]) / sizeof(*brd[0]) && (!brd[rBoundary][i].getExist())) {
                i = -1;
                rBoundary--;

            }
        }

    }

    void chNeighball(int m, int n, int col, int cs) {
        //ball �� chflag �߰�, getter, setter �� ��������
        if (brd[m][n].getChflag() == 0) {
            if (brd[m][n].getColor() == col) {
                brd[m][n].setChflag(cs);

                if (n < sizeof(brd[0]) / sizeof(*brd[0]) - 1) {
                    chNeighball(m, n + 1, col, cs);
                }

                if (m % 2 == 0) {
                    if (m <= rBoundary) {
                        chNeighball(m + 1, n, col, cs);
                        if (n > 0)
                            chNeighball(m + 1, n - 1, col, cs);

                    }
                    if (n > 0) {
                        chNeighball(m, n - 1, col, cs);
                        if (m > 0)
                            chNeighball(m - 1, n - 1, col, cs);
                    }
                    if (m > 0)
                        chNeighball(m - 1, n, col, cs);
                }

                else if (m % 2 == 1) {
                    if (m <= rBoundary) {
                        if (n < sizeof(brd[0]) / sizeof(*brd[0]) - 1)
                            chNeighball(m + 1, n + 1, col, cs);

                        chNeighball(m + 1, n, col, cs);
                    }
                    if (n > 0)
                        chNeighball(m, n - 1, col, cs);

                    if (m > 0) {
                        chNeighball(m - 1, n, col, cs);
                        if (n < sizeof(brd[0]) / sizeof(*brd[0]) - 1)
                            chNeighball(m - 1, n + 1, col, cs);
                    }
                }

            }
        }
    }


    void draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld) {
        for (int i = 0; i < sizeof(brd) / sizeof(brd[0]); i++) //row
        {
            for (int j = 0; j < sizeof(brd) / sizeof(CSphere); j++) //col
            {
                if (brd[i][j].getExist())
                    brd[i][j].draw(pDevice, mWorld);
            }
        }
    }

    bool bAttach(int m, int n, CSphere& ball) {

        float bCent_x = ball.getCenter().x;

        if (m < sizeof(brd) / sizeof(*brd) - 1) {
            if (bCent_x >= brd[m][n].getCenter().x) {
                if (m % 2 == 0) {
                    brd[m + 1][n].setColor(ball.getColor());
                    brd[m + 1][n].setExist(ball.getExist());
                }
                else if (m % 2 == 1) {
                    brd[m + 1][n + 1].setColor(ball.getColor());
                    brd[m + 1][n + 1].setExist(ball.getExist());
                }
            }
            else if (bCent_x < brd[m][n].getCenter().x) {
                if (m % 2 == 0) {
                    brd[m + 1][n - 1].setColor(ball.getColor());
                    brd[m + 1][n - 1].setExist(ball.getExist());
                }
                else if (m % 2 == 1) {
                    brd[m + 1][n].setColor(ball.getColor());
                    brd[m + 1][n].setExist(ball.getExist());
                }
            }
            rBoundary++;
            return true;
        }
        else return false;
    }

    void chEmpty(int m, int n, int* hMax, int* wMin, int* wMax) {

        if (brd[m][n].getColor() == 0) {
            brd[m][n].setChflag(empFl);
            if (m > *hMax)
                *hMax = m;
            if (n < *wMin)
                *wMin = n;
            else if (n > *wMax)
                *wMax = n;

            if (n > 0)
                chEmpty(m, n - 1, hMax, wMin, wMax);

            if (m % 2 == 0) {

                if (m > 0) {
                    if (n > 0) {
                        chEmpty(m - 1, n - 1, hMax, wMin, wMax);
                    }
                    chEmpty(m - 1, n, hMax, wMin, wMax);
                }


                chEmpty(m, n + 1, hMax, wMin, wMax);
                chEmpty(m + 1, n, hMax, wMin, wMax);
                chEmpty(m + 1, n - 1, hMax, wMin, wMax);

            }
            else if (m % 2 == 1) {

                chEmpty(m - 1, n, hMax, wMin, wMax);
                chEmpty(m - 1, n + 1, hMax, wMin, wMax);
                chEmpty(m, n + 1, hMax, wMin, wMax);
                chEmpty(m + 1, n + 1, hMax, wMin, wMax);
                chEmpty(m + 1, n, hMax, wMin, wMax);
            }
        }
    }

    int bDetach() {

        int i;
        int* min;
        int* max;
        int* hei;

        for (i = 0; i < sizeof(brd[0]) / sizeof(*brd[0]); i++) {
            if (brd[rBoundary][i].getColor() == 0)
                break;
        }

        *hei = rBoundary;
        *min = i;
        *max = i;

        chEmpty(rBoundary, i, hei, min, max);

        if (*hei < rBoundary && *min < *max) {
            for (int i = *hei; i <= rBoundary; i++) {
                for (int j = *min; j <= *max; j++) {
                    //�Ͷ߸���
                }
            }
        }

    }

    void resume(int col, int row, float x, float y, float z, int color, bool exist) //�� �ϳ��� ���� �ٲٱ�
    {
        brd[row][col].setCenter(x, y, z);

        if (color == 1)
            brd[row][col].setColor(d3d::YELLOW);
        else if (color == 2)
            brd[row][col].setColor(d3d::RED);
        else if (color == 3)
            brd[row][col].setColor(d3d::BLUE);
        else if (color == 4)
            brd[row][col].setColor(d3d::GREEN);
        else
            brd[row][col].setColor(d3d::MAGENTA);

        brd[row][col].setExist(exist);
    }

};
