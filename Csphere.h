#pragma once
#include "d3dUtility.h"

#define M_RADIUS 0.21   // ball radius
#define PI 3.14159265
#define M_HEIGHT 0.01
#define DECREASE_RATE 0.9982

class CSphere {
private:
    float               center_x, center_y, center_z;
    float                   m_radius;
    float               m_velocity_x;
    float               m_velocity_z;
    bool ball_exist = true;
    bool is_thrown = false;
    int chflag;

    int ball_color; // 1 - ��� 2- ���� 3- �Ķ� 4- �ʷ�
    float pre_center_x, pre_center_z;

public:
    CSphere(void);
    ~CSphere(void);

    bool create(IDirect3DDevice9* pDevice, D3DXCOLOR color = d3d::WHITE);
    void destroy(void);
    void draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld);

    bool hasIntersected(CSphere& ball);

    bool colorcheck(CSphere& ball);

    void ballUpdate(float timeDiff);

    double getVelocity_X();
    double getVelocity_Z();

    void setPower(double vx, double vz);

    void setCenter(float x, float y, float z);

    bool ball_existance();
    float getRadius(void) const;
    const D3DXMATRIX& getLocalTransform(void) const;
    void setLocalTransform(const D3DXMATRIX& mLocal);

    D3DXVECTOR3 getCenter(void) const;

    void setColor(const D3DXCOLOR ball_color);
    int getColor();
    void adjustPosition(CSphere& ball);


    double getPreCenter_x() const;
    double getPreCenter_z() const;

    void set_exist(bool a);

    //bool already_thrown();
    //void set_thrown();

    int getChflag();

    void setChflag(int val);

private:
    D3DXMATRIX              m_mLocal;
    D3DMATERIAL9            m_mtrl;
    ID3DXMesh* m_pSphereMesh;

};
