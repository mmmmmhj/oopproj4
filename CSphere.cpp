#include "CSphere.h"

CSphere::CSphere(void)
{
    D3DXMatrixIdentity(&m_mLocal);
    ZeroMemory(&m_mtrl, sizeof(m_mtrl));
    m_radius = 0;
    m_velocity_x = 0;
    m_velocity_z = 0;
    m_pSphereMesh = NULL;
    
    int chflag = 0;
}

CSphere::~CSphere(void) {}

bool CSphere::create(IDirect3DDevice9* pDevice, D3DXCOLOR color = d3d::WHITE)
{
    if (NULL == pDevice)
        return false;

    m_mtrl.Ambient = color;
    m_mtrl.Diffuse = color;
    m_mtrl.Specular = color;
    m_mtrl.Emissive = d3d::BLACK;
    m_mtrl.Power = 5.0f;

    if (FAILED(D3DXCreateSphere(pDevice, getRadius(), 50, 50, &m_pSphereMesh, NULL)))
        return false;
    return true;
}

void CSphere::destroy(void)
{
    if (m_pSphereMesh != NULL) {
        m_pSphereMesh->Release();
        m_pSphereMesh = NULL;
        this->ball_exist = false;
    }
}

void CSphere::draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld)
{
    if (NULL == pDevice)
        return;
    pDevice->SetTransform(D3DTS_WORLD, &mWorld);
    pDevice->MultiplyTransform(D3DTS_WORLD, &m_mLocal);
    pDevice->SetMaterial(&m_mtrl);
    m_pSphereMesh->DrawSubset(0);
}

bool CSphere::hasIntersected(CSphere& ball)
{
    D3DXVECTOR3 position_this = this->getCenter();
    D3DXVECTOR3 position_other = ball.getCenter();
    double xDistance = abs((position_this.x - position_other.x) * (position_this.x - position_other.x));
    double zDistance = abs((position_this.z - position_other.z) * (position_this.z - position_other.z));
    double totalDistance = sqrt(xDistance + zDistance);
    if (totalDistance < (this->getRadius() + ball.getRadius()))
    {
        return true;
    }
    return false;
}

void CSphere::hitBy(CSphere& ball)
{
    if (this->hasIntersected(ball))
    {
        adjustPosition(ball);
        //���� ���� �ε����°�
        float dx = ball.getCenter().x - this->getCenter().x;
        float dz = ball.getCenter().z - this->getCenter().z;
        float distance = sqrt(dx * dx + dz * dz);

        float bvx = ball.m_velocity_x;
        float bvz = ball.m_velocity_z;

        float velocity = sqrt(bvx * bvx + bvz * bvz);
        float dt = velocity / distance;
        ball.setPower(dx * dt, dz * dt);

        if (this->ball_color == 0)
        {
            this->ball_exist = false;
            this->setCenter(-100, -100, -100);
        }
    }
}

void CSphere::ballUpdate(float timeDiff)
{
    const float TIME_SCALE = 3.3;
    D3DXVECTOR3 cord = this->getCenter();
    double vx = abs(this->getVelocity_X());
    double vz = abs(this->getVelocity_Z());
    this->pre_center_x = cord.x;
    this->pre_center_z = cord.z;

    if (vx > 0.01 || vz > 0.01)
    {
        float tX = cord.x + TIME_SCALE * timeDiff * m_velocity_x;
        float tZ = cord.z + TIME_SCALE * timeDiff * m_velocity_z;
        this->setCenter(tX, cord.y, tZ);
    }
    else { this->setPower(0, 0); }
}

void CSphere::setPower(double vx, double vz)
{
    this->m_velocity_x = vx;
    this->m_velocity_z = vz;
}

void CSphere::setCenter(float x, float y, float z)
{
    D3DXMATRIX m;
    center_x = x;   center_y = y;   center_z = z;
    D3DXMatrixTranslation(&m, x, y, z);
    setLocalTransform(m);
}

D3DXVECTOR3 CSphere::getCenter(void) const
{
    D3DXVECTOR3 org(center_x, center_y, center_z);
    return org;
}


void CSphere::setColor(const D3DXCOLOR ball_color)
{
    if (ball_color == d3d::YELLOW)
        this->ball_color = 0;
    else if (ball_color == d3d::RED)
        this->ball_color = 1;
    else
        this->ball_color = 2;
}


void CSphere::adjustPosition(CSphere& ball) {
    D3DXVECTOR3 ball_cord = ball.getCenter();

    this->setCenter((center_x + this->pre_center_x) / 2, center_y, (center_z + this->pre_center_z) / 2);
    ball.setCenter((ball_cord.x + ball.pre_center_x) / 2, ball_cord.y, (ball_cord.z + ball.pre_center_z) / 2);
    if (this->hasIntersected(ball))
    {
        this->setCenter(this->pre_center_x, center_y, this->pre_center_z);
        ball.setCenter(ball.pre_center_x, ball_cord.y, ball.pre_center_z);
    }
}
int CSphere::getChflag(){
    return chflag;
}

void CSphere::setChflag(int val){
    chflag = val;
}

int CSphere::getColor(){
    return ball_color;
}
