
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
                
            }
            else if (i%2 ==1){
                
            }
        }
    }
    
    void chNeighball(){
        
    }

    void draw(){
        
    }
    
    void bAttach(){
        
    }
    
    void bDetach(){
        
    }
    
    void resume(){
        
    }
    
};


