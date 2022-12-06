//
//  Board.cpp
//  oop_prj4
//
//  Created by 정지현 on 12/3/22.
//

#include <stdio.h>
#include <vector>
#include "CWall.h"
#include "CSphere.h"


using namespace std;

class Board{
    
    private :
    CSphere brd [10][8];
    float x_bdCtr, y_bdCtr, z_bdCtr;
    int rBoundary;
    int empFl = -3;
    public :

    Board (){
//        x_bdCtr = gamemanager.getcenter_x();
//        y_bdCtr = gamemanager.getcenter_y();
//        z_bdCtr = gamemanager.getcenter_z();
        
        

    }
    Board (float X, float Y, float Z, float depth){
        
        this->x_bdCtr = X;
        this->y_bdCtr = Y;
        this->z_bdCtr = Z;
        
        rBoundary = 3;
        
        for (int i = 0; i<rBoundary; i++) {
            for (int j = 0; j<sizeof(brd[0])/sizeof(*brd[0]); j++) {
                // 이 부분만 합쳐주시면 됩니다.
                if (i%2 == 0) {
                    brd[i][j].setCenter(x_bdCtr-(sizeof(brd[0])/sizeof(*brd[0])/2-0.5-j)*brd[i][j].getRadius()/0.5,0,z_bdCtr + depth/2-i*brd[i][j].getRadius()/0.5);
                    // col[i]line[j]_x = x_bdCtr-(line->size()/2)+0.5+j ball.center_x =
                    // col[i]line[j]_z = [z_bdCtr+(boardlength/2)]-i
                }
                else if (i%2 ==1){
                    brd[i][j].setCenter(x_bdCtr-(sizeof(brd[0])/sizeof(*brd[0])/2-j)*brd[i][j].getRadius(),0,z_bdCtr + depth/2-i*brd[i][j].getRadius());
                    // col[i]line[j]_x = x_bdCtr-(line->size()/2)+1+j
                    // col[i]line[j]_z = [z_bdCtr+(boardlength/2)]-i
                }
            }
        }
        
        
    }
    
    ~Board(){}
    
    void destroy(int m, int n, int col){
        chNeighball(m, n, col, 1);
        for (int i = 0; i<sizeof(brd[0])/sizeof(*brd[0]); i++) {
            if(brd[rBoundary][i].getExist())
                break;
            else if(i==sizeof(brd[0])/sizeof(*brd[0])&&(!brd[rBoundary][i].getExist())){
                i = -1;
                rBoundary --;
            }
        }
        // 터트리기
        
    }
    
    void chNeighball(int m, int n, int col, int cs){
        //ball 에 chflag 추가, getter, setter 도 마찬가지
        if(brd[m][n].getChflag()==0){
            if (brd[m][n].getColor()==col) {
                brd[m][n].setChflag(cs);
                
                if (n<sizeof(brd[0])/sizeof(*brd[0])-1) {
                    chNeighball(m, n+1, col, cs);
                }
                
                if(m%2==0){
                    if(m<=rBoundary){
                        chNeighball(m+1, n, col, cs);
                        if (n>0)
                            chNeighball(m+1,n-1, col, cs);
                        
                    }
                    if (n>0) {
                        chNeighball(m, n-1, col, cs);
                        if(m>0)
                            chNeighball(m-1, n-1, col, cs);
                    }
                    if(m>0)
                        chNeighball(m-1, n, col, cs);
                }
                
                else if (m%2 ==1){
                    if (m<=rBoundary) {
                        if(n<sizeof(brd[0])/sizeof(*brd[0])-1)
                            chNeighball(m+1, n+1, col, cs);
                        
                        chNeighball(m+1, n, col, cs);
                    }
                    if (n>0)
                        chNeighball(m, n-1, col, cs);
                    
                    if (m>0) {
                        chNeighball(m-1, n, col, cs);
                        if(n<sizeof(brd[0])/sizeof(*brd[0])-1)
                            chNeighball(m-1, n+1, col, cs);
                    }
                    
                }
                
                
                
            }
        }
    }
    
    
    
    bool bAttach(int m, int n, CSphere& ball){
        
        float bCent_x = ball.getCenter().x;
        
        if (m<sizeof(brd)/sizeof(*brd)-1) {
            if (bCent_x >= brd[m][n]) {
                if (m%2==0) {
                    brd[m+1][n].setColor(ball.getColor());
                    brd[m+1][n].setExist(ball.getExist());
                }
                else if(m%2==1){
                    brd[m+1][n+1].setColor(ball.getColor());
                    brd[m+1][n+1].setExist(ball.getExist());
                }
            }
            else if (bCent_x < brd[m][n]){
                if (m%2==0) {
                    brd[m+1][n-1].setColor(ball.getColor());
                    brd[m+1][n-1].setExist(ball.getExist());
                }
                else if(m%2==1){
                    brd[m+1][n].setColor(ball.getColor());
                    brd[m+1][n].setExist(ball.getExist());
                }
            }
            rBoundary++;
            return true;
        }
        else return false;
    }
    
    void chEmpty(int m,int n, int* hMax, int *wMin, int* wMax){
       
        if(brd[m][n].getColor()==0){
            brd[m][n].setChflag(empFl);
            if (m>*hMax)
                *hMax = m;
            if (n<*wMin)
                *wMin = n;
            else if (n>*wMax)
                *wMax = n;
            
            if(n>0)
            chEmpty(m, n-1, hMax, wMin, wMax);
            
            if (m%2 == 0) {
                
                if(m>0){
                    if (n>0) {
                        chEmpty(m-1, n-1, hMax , wMin , wMax);
                    }
                    chEmpty(m-1, n, hMax, wMin, wMax);
                }
                
                
                chEmpty(m, n+1, hMax, wMin, wMax);
                chEmpty(m+1, n, hMax, wMin, wMax);
                chEmpty(m+1, n-1, hMax, wMin, wMax);
                
            }
            else if(m%2 == 1){
                
                chEmpty(m-1, n, hMax , wMin , wMax);
                chEmpty(m-1, n+1, hMax, wMin, wMax);
                chEmpty(m, n+1, hMax, wMin, wMax);
                chEmpty(m+1, n+1, hMax, wMin, wMax);
                chEmpty(m+1, n, hMax, wMin, wMax);
            }
        }
        
                
        
                
            
    }
    
    int bDetach(){
        
        int i;
        int* min;
        int* max;
        int* hei;
        
        for (i = 0; i<sizeof(brd[0])/sizeof(*brd[0]); i++) {
            if (brd[rBoundary][i].getColor == 0)
                break;
        }
        
        *hei = rBoundary;
        *min = i;
        *max = i;
        
        chEmpty(rBoundary, i, hei, min, max);
        
        if(*hei<rBoundary && *min<*max){
            for (int i = *hei; i<= rBoundary; i++) {
                for (int j = *min; j<= *max; j++) {
                    //터뜨리기
                }
            }
        }
        
    }
    
    void resume(){
        
    }
    
    void draw(){
        
    }
};


