
#include <stdio.h>
#include <vector>
#include "CWall.h"
#include "CSphere.h"


using namespace std;

class Board{
    
    private :
    vector <CSphere> line [8];
    vector <vector <CSphere>> col [10];
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
        
        for (int i = 0; i<col->size(); i++) {
            if (i%2 == 0) {
                // col[i]line[j]_x = x_bdCtr-(line->size()/2)+0.5+j
                // col[i]line[j]_z = [z_bdCtr+(boardlength/2)]-i
                // col[i]line[j].setcolor()
            }
            else if (i%2 ==1){
                // col[i]line[j]_x = x_bdCtr-(line->size()/2)+1+j
                // col[i]line[j]_z = [z_bdCtr+(boardlength/2)]-i
                // col[i]line[j].setcolor()
            }
        }
    }
    
    void chNeighball(CSphere& ball){
        
    }

    void draw(){
        //ball.draw()
        //wall.draw()
    }
    
    void bAttach(){
        
    }
    
    void bDetach(){
        
    }
    
    void resume(){
        
    }
    
};


