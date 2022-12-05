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
    
    public :

    Board (){
//        x_bdCtr = gamemanager.getcenter_x();
//        y_bdCtr = gamemanager.getcenter_y();
//        z_bdCtr = gamemanager.getcenter_z();
        
        

    }
    Board (float X, float Y, float Z){
        
        this->x_bdCtr = X;
        this->y_bdCtr = Y;
        this->z_bdCtr = Z;
        
        for (int i = 0; i<sizeof(brd)/sizeof(*brd); i++) {
            if (i%2 == 0) {
                // col[i]line[j]_x = x_bdCtr-(line->size()/2)+0.5+j ball.center_x =
                // col[i]line[j]_z = [z_bdCtr+(boardlength/2)]-i
            }
            else if (i%2 ==1){
                // col[i]line[j]_x = x_bdCtr-(line->size()/2)+1+j
                // col[i]line[j]_z = [z_bdCtr+(boardlength/2)]-i
            }
        }
    }
    
    void destroy(int m, int n, int col){
        chNeighball(m, n, col);
        
    }
    
    void chNeighball(int m, int n, int col){
        //ball 에 chflag 추가, getter, setter 도 마찬가지
        if(brd[m][n].getChflag()==0){
            if (brd[m][n].getColor()==col) {
                brd[m][n].setChflag(1);
                
                if (n<sizeof(brd[0])/sizeof(*brd[0])-1) {
                    chNeighball(m, n+1, col);
                }
                
                if(m%2==0){
                    if(m<sizeof(brd)/sizeof(*brd)-1){
                        chNeighball(m+1, n, col);
                        if (n>0)
                            chNeighball(m+1,n-1, col);
                        
                    }
                    if (n>0) {
                        chNeighball(m, n-1, col);
                        if(m>0)
                            chNeighball(m-1, n-1, col);
                    }
                    if(m>0)
                        chNeighball(m-1, n, col);
                }
                
                else if (m%2 ==1){
                    if (m<sizeof(brd)/sizeof(*brd)-1) {
                        if(n<sizeof(brd[0])/sizeof(*brd[0])-1)
                            chNeighball(m+1, n+1, col);
                        
                        chNeighball(m+1, n, col);
                    }
                    if (n>0)
                        chNeighball(m, n-1, col);
                    
                    if (m>0) {
                        chNeighball(m-1, n, col);
                        if(n<sizeof(brd[0])/sizeof(*brd[0])-1)
                            chNeighball(m-1, n+1, col);
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
            return true;
        }
        else return false;
    }
    
    int bDetach(){
        
    }
    
    void resume(){
        
    }
    
     void draw(){
        
    }
    
};


