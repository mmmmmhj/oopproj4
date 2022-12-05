#include <stdio.h>
#include <vector>
#include "CWall.h"
#include "CSphere.h"
#include <random>

using namespace std;

class Board {

private:
    CSphere brd[10][8];
    int col = 10;
    int ror = 8;
    float x_bdCtr, y_bdCtr, z_bdCtr;

public:

    //Board() {
    //            x_bdCtr = gamemanager.getcenter_x();
    //            y_bdCtr = gamemanager.getcenter_y();
    //            z_bdCtr = gamemanager.getcenter_z();



    //}
    Board(float X, float Y, float Z, IDirect3DDevice9* pDevice) {

        this->x_bdCtr = X;
        this->y_bdCtr = Y;
        this->z_bdCtr = Z;

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dis(1, 4);

        // 중심 기준으로 공의 x z 초기좌표 설정

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

                //set center만 넣어주세요

                if (i > 3)
                    brd[i][j].set_exist(false);
            }
        }

        //for (int i = 0; i < sizeof(brd) / sizeof(*brd); i++) {
        //    if (i % 2 == 0) {
        //        // 중심 기준으로 공의 x z 초기좌표 설정
        //        // col[i]line[j]_x = x_bdCtr-(line->size()/2)+0.5+j ball.center_x =
        //        // col[i]line[j]_z = [z_bdCtr+(boardlength/2)]-i
        //    }
        //    else if (i % 2 == 1) {
        //        // col[i]line[j]_x = x_bdCtr-(line->size()/2)+1+j
        //        // col[i]line[j]_z = [z_bdCtr+(boardlength/2)]-i
        //    }
        //}
    }

    void destroy(int m, int n, int col) {
        chNeighball(m, n, col);

    }

    void chNeighball(int m, int n, int col) {
        //ball 에 chflag 추가, getter, setter 도 마찬가지
        if (brd[m][n].getChflag() == 0) {
            if (brd[m][n].getColor() == col) {
                brd[m][n].setChflag(1);

                if (n < sizeof(brd[0]) / sizeof(*brd[0]) - 1) {
                    chNeighball(m, n + 1, col);
                }

                if (m % 2 == 0) {
                    if (m < sizeof(brd) / sizeof(*brd) - 1) {
                        chNeighball(m + 1, n, col);
                        if (n > 0)
                            chNeighball(m + 1, n - 1, col);

                    }
                    if (n > 0) {
                        chNeighball(m, n - 1, col);
                        if (m > 0)
                            chNeighball(m - 1, n - 1, col);
                    }
                    if (m > 0)
                        chNeighball(m - 1, n, col);
                }

                else if (m % 2 == 1) {
                    if (m < sizeof(brd) / sizeof(*brd) - 1) {
                        if (n < sizeof(brd[0]) / sizeof(*brd[0]) - 1)
                            chNeighball(m + 1, n + 1, col);

                        chNeighball(m + 1, n, col);
                    }
                    if (n > 0)
                        chNeighball(m, n - 1, col);

                    if (m > 0) {
                        chNeighball(m - 1, n, col);
                        if (n < sizeof(brd[0]) / sizeof(*brd[0]) - 1)
                            chNeighball(m - 1, n + 1, col);
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
                if (brd[i][j].ball_existance())
                    brd[i][j].draw(pDevice, mWorld);
            }
        }
    }

    void bAttach() {

    }

    int bDetach() {

    }

    void resume() {

    }

};
