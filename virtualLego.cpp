////////////////////////////////////////////////////////////////////////////////
//
// File: virtualLego.cpp
//
// Original Author: 박창현 Chang-hyeon Park, 
// Modified by Bong-Soo Sohn and Dong-Jun Kim
// 
// Originally programmed for Virtual LEGO. 
// Modified later to program for Virtual Billiard.
//        
////////////////////////////////////////////////////////////////////////////////
//
//#include "d3dUtility.h"
//#include "CSphere.h"
//#include "CWall.h"
//#include <vector>
//#include <ctime>
//#include <cstdlib>
//#include <cstdio>
//#include <cassert>
//#include <cmath>  
//
//IDirect3DDevice9* Device = NULL;
//
// window size
//const int Width  = 1024;
//const int Height = 768;
//
//#define BLOCKNUM 54
//
//
// -----------------------------------------------------------------------------
// Transform matrices
// -----------------------------------------------------------------------------
//D3DXMATRIX g_mWorld;
//D3DXMATRIX g_mView;
//D3DXMATRIX g_mProj;
//
//#define M_RADIUS 0.5   // ball radius
//#define PI 3.14159265
//#define M_HEIGHT 0.01
//#define DECREASE_RATE 0.9982
//
//const float spherePos[BLOCKNUM][2] = {
//{-16 * M_RADIUS, -7 * M_RADIUS}, {-16 * M_RADIUS, -5 * M_RADIUS}, {-16 * M_RADIUS, -3 * M_RADIUS}, {-16 * M_RADIUS, -M_RADIUS}, {-16 * M_RADIUS, M_RADIUS}, {-16 * M_RADIUS, 3 * M_RADIUS}, {-16 * M_RADIUS, 5 * M_RADIUS}, {-16 * M_RADIUS, 7 * M_RADIUS},   // 8개
//{-14 * M_RADIUS, -9 * M_RADIUS}, {-14 * M_RADIUS, 9 * M_RADIUS}, // 2개
//{-12 * M_RADIUS, -11 * M_RADIUS}, {-12 * M_RADIUS, 11 * M_RADIUS}, // 2개
//{-10 * M_RADIUS,-11 * M_RADIUS}, {-10 * M_RADIUS, -5 * M_RADIUS}, {-10 * M_RADIUS, 5 * M_RADIUS}, {-10 * M_RADIUS, 11 * M_RADIUS}, //4개
//{-8 * M_RADIUS,-11 * M_RADIUS}, {-8 * M_RADIUS, -5 * M_RADIUS}, {-8 * M_RADIUS, 5 * M_RADIUS}, {-8 * M_RADIUS, 11 * M_RADIUS},  //4개
//{-6 * M_RADIUS, -11 * M_RADIUS}, {6 * M_RADIUS, 11 * M_RADIUS}, // 2개
//{-4 * M_RADIUS, -11 * M_RADIUS}, {-4 * M_RADIUS, 0}, {-4 * M_RADIUS, 11 * M_RADIUS}, // 3개
//{-2 * M_RADIUS, -11 * M_RADIUS}, {-2 * M_RADIUS, 0}, {-2 * M_RADIUS, 11 * M_RADIUS},  // 3개
//{0, -11 * M_RADIUS}, {0, -7 * M_RADIUS}, {0, 7 * M_RADIUS}, {0, 11 * M_RADIUS},  // 4개
//{2 * M_RADIUS, -11 * M_RADIUS}, {2 * M_RADIUS, -5 * M_RADIUS}, {2 * M_RADIUS, 5 * M_RADIUS}, {2 * M_RADIUS, 11 * M_RADIUS},  // 4개
//{4 * M_RADIUS, -11 * M_RADIUS}, {4 * M_RADIUS, -3 * M_RADIUS}, {4 * M_RADIUS, -M_RADIUS}, {4 * M_RADIUS, M_RADIUS}, {4 * M_RADIUS, 3 * M_RADIUS}, {4 * M_RADIUS, 11 * M_RADIUS},  // 6개
//{6 * M_RADIUS, -11 * M_RADIUS}, {6 * M_RADIUS, 11 * M_RADIUS}, // 2개
//{8 * M_RADIUS, -9 * M_RADIUS}, {8 * M_RADIUS, 9 * M_RADIUS},  // 2개
//{10 * M_RADIUS, -7 * M_RADIUS}, {10 * M_RADIUS, -5 * M_RADIUS}, {10 * M_RADIUS, -3 * M_RADIUS}, {10 * M_RADIUS, -M_RADIUS}, {10 * M_RADIUS, M_RADIUS}, {10 * M_RADIUS, 3 * M_RADIUS}, {10 * M_RADIUS, 5 * M_RADIUS}, {10 * M_RADIUS, 7 * M_RADIUS}   // 8개
//};  // 블록 좌표 (총 54개)
// initialize the color of each ball (ball0 ~ ball53)
//
//// -----------------------------------------------------------------------------
//// CSphere class definition
//// -----------------------------------------------------------------------------
//
//class CSphere {
//private :
//	float					center_x, center_y, center_z;
//    float                   m_radius;
//	float					m_velocity_x;
//	float					m_velocity_z;
//	bool					m_is_used = false;   // 블록, 빨간공이 활성화 됐는지 여부를 저장함
//
//public:
//    CSphere(void)
//    {
//        D3DXMatrixIdentity(&m_mLocal);
//        ZeroMemory(&m_mtrl, sizeof(m_mtrl));
//        m_radius = 0;
//		m_velocity_x = 0;
//		m_velocity_z = 0;
//        m_pSphereMesh = NULL;
//		m_is_used = false;
//    }
//    ~CSphere(void) {}
//
//public:
//    bool create(IDirect3DDevice9* pDevice,  D3DXCOLOR color = d3d::YELLOW)
//    {
//        if (NULL == pDevice)
//            return false;
//		
//        m_mtrl.Ambient  = color;
//        m_mtrl.Diffuse  = color;
//        m_mtrl.Specular = color;
//        m_mtrl.Emissive = d3d::BLACK;
//        m_mtrl.Power    = 5.0f;
//		
//        if (FAILED(D3DXCreateSphere(pDevice, getRadius(), 50, 50, &m_pSphereMesh, NULL)))
//            return false;
//        return true;
//    }
//	
//    void destroy(void)
//    {
//        if (m_pSphereMesh != NULL) {
//            m_pSphereMesh->Release();
//            m_pSphereMesh = NULL;
//        }
//    }
//
//    void draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld)
//    {
//        if (NULL == pDevice)
//            return;
//        pDevice->SetTransform(D3DTS_WORLD, &mWorld);
//        pDevice->MultiplyTransform(D3DTS_WORLD, &m_mLocal);
//        pDevice->SetMaterial(&m_mtrl);
//		m_pSphereMesh->DrawSubset(0);
//    }
//	
//    bool hasIntersected(CSphere& ball)   // 수정한 코드 
//	{
//		if (false) {
//			return false;
//		}
//
//		D3DXVECTOR3 cord = this->getCenter(); // 첫 번째 공
//		float aX = cord.x;
//		float aY = cord.z;
//
//		D3DXVECTOR3 ballcenter = ball.getCenter();  // 두 번째 공
//		float bX = ballcenter.x;
//		float bY = ballcenter.z;
//
//		float distance = sqrt(pow(aX- bX, 2) + pow(aY - bY, 2));  //  두 공 사이의 거리
//
//		if (abs(distance) <= 2 * M_RADIUS) {  // 공 사이의 거리가 반지름의 두 배보다 작거나 같은 경우 return true;
//			return true;
//		}
//
//		return false;
//	}
//	
//	void hitBy(CSphere& ball)    // 수정한 코드
//	{  // ball은 항상 red_ball
//		if (hasIntersected(ball)) { // 충돌이 있을 경우에
//			
//			D3DXVECTOR3 cord = this->getCenter();
//			D3DXVECTOR3 red_ball = ball.getCenter();
//
//			double theta = acos(sqrt(pow(cord.x - red_ball.x, 2)) / sqrt(pow(cord.x - red_ball.x, 2) +
//				pow(cord.z - red_ball.z, 2)));      // 기본 1 사분면
//			if (cord.z - red_ball.z < 0 && cord.x - red_ball.x > 0) { theta = -theta; }   //4 사분면
//			if (cord.z - red_ball.z >= 0 && cord.x - red_ball.x <= 0) { theta = PI - theta; } //2 사분면
//			if (cord.z - red_ball.z < 0 && cord.x - red_ball.x < 0) { theta = PI + theta; } // 3 사분면
//
//			ball.setPower(-cos(theta), -sin(theta));  // red_ball에서 block까지의 반대 방향으로 power를 설정, 공의 고유 속도는 항상 1이 되도록 함
//
//			if (!this->is_used()) {
//				this->change_is_used();  // block은 안 부딪혔을 경우 false, white는 항상 true 상태 -> block이 부딪힌 경우 is_used를 true로 바꿈
//			}
//		}
//	}
//
//	void ballUpdate(float timeDiff)   
//	{
//		const float TIME_SCALE = 3.3;
//		D3DXVECTOR3 cord = this->getCenter();
//		double vx = abs(this->getVelocity_X());
//		double vz = abs(this->getVelocity_Z());
//
//		if(vx > 0.01 || vz > 0.01)
//		{
//			float tX = cord.x + TIME_SCALE*timeDiff*m_velocity_x;
//			float tZ = cord.z + TIME_SCALE*timeDiff*m_velocity_z;
//			
//			this->setCenter(tX, cord.y, tZ);
//		}
//		else { this->setPower(0,0);}
//		this->setPower(getVelocity_X(), getVelocity_Z());
//	}
//
//	double getVelocity_X() { return this->m_velocity_x;	}
//	double getVelocity_Z() { return this->m_velocity_z; }
//
//	void setPower(double vx, double vz)
//	{
//		this->m_velocity_x = vx;
//		this->m_velocity_z = vz;
//	}
//
//	void setCenter(float x, float y, float z)
//	{
//		D3DXMATRIX m;
//		center_x=x;	center_y=y;	center_z=z;
//		D3DXMatrixTranslation(&m, x, y, z);
//		setLocalTransform(m);
//	}
//	
//	bool is_used() { return this->m_is_used; }  // m_is_used (redball과 block의 사용여부를 반환)
//	void change_is_used() { this->m_is_used = !this->m_is_used; }  // m_is_used 값을 바꿈
//
//	float getRadius(void)  const { return (float)(M_RADIUS);  }
//    const D3DXMATRIX& getLocalTransform(void) const { return m_mLocal; }
//    void setLocalTransform(const D3DXMATRIX& mLocal) { m_mLocal = mLocal; }
//    D3DXVECTOR3 getCenter(void) const
//    {
//        D3DXVECTOR3 org(center_x, center_y, center_z);
//        return org;
//    }
//	
//private:
//    D3DXMATRIX              m_mLocal;
//    D3DMATERIAL9            m_mtrl;
//    ID3DXMesh*              m_pSphereMesh;
//	
//};
//
//
//
//// -----------------------------------------------------------------------------
//// CWall class definition
//// -----------------------------------------------------------------------------
//
//class CWall {
//
//private:
//	
//    float					m_x;
//	float					m_z;
//	float                   m_width;
//    float                   m_depth;
//	float					m_height;
//	
//public:
//    CWall(void)
//    {
//        D3DXMatrixIdentity(&m_mLocal);
//        ZeroMemory(&m_mtrl, sizeof(m_mtrl));
//        m_width = 0;
//        m_depth = 0;
//        m_pBoundMesh = NULL;
//    }
//    ~CWall(void) {}
//public:
//    bool create(IDirect3DDevice9* pDevice, float ix, float iz, float iwidth, float iheight, float idepth, D3DXCOLOR color = d3d::YELLOW)
//    {
//        if (NULL == pDevice)
//            return false;
//		
//        m_mtrl.Ambient  = color;
//        m_mtrl.Diffuse  = color;
//        m_mtrl.Specular = color;
//        m_mtrl.Emissive = d3d::BLACK;
//        m_mtrl.Power    = 5.0f;
//		
//        m_width = iwidth;
//        m_depth = idepth;
//		
//        if (FAILED(D3DXCreateBox(pDevice, iwidth, iheight, idepth, &m_pBoundMesh, NULL)))
//            return false;
//        return true;
//    }
//    void destroy(void)
//    {
//        if (m_pBoundMesh != NULL) {
//            m_pBoundMesh->Release();
//            m_pBoundMesh = NULL;
//        }
//    }
//    void draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld)
//    {
//        if (NULL == pDevice)
//            return;
//        pDevice->SetTransform(D3DTS_WORLD, &mWorld);
//        pDevice->MultiplyTransform(D3DTS_WORLD, &m_mLocal);
//        pDevice->SetMaterial(&m_mtrl);
//		m_pBoundMesh->DrawSubset(0);
//    }
//	
//	bool hasIntersected(CSphere& ball) // 수정한 코드
//	{	
//		D3DXVECTOR3 cord = ball.getCenter(); // 공의 위치를 가져옴
//
//		float tX = cord.x;
//		float tZ = cord.z;
//
//		if (tX >= (4.5 + M_RADIUS) || tX <= (-4.5 + M_RADIUS) || tZ <= (-3 + M_RADIUS) || tZ >= (3 - M_RADIUS)) {  // 아래(좀 더 넓은 범위), 위, 왼쪽 , 오른쪽 벽과 부딪히는지 확인
//			return true;
//		}
//
//		return false;
//	}
//
//	void hitBy(CSphere& ball) // 수정한 코드
//	{	
//		if (this->hasIntersected(ball)) { // 공이 벽에 부딪힌 경우
//			D3DXVECTOR3 cord = ball.getCenter();
//			double vx = ball.getVelocity_X();
//			double vz = ball.getVelocity_Z();
//			float tX = cord.x;
//			float tZ = cord.z;
//			if (tX <= (-4.5 + M_RADIUS)) {  // 위쪽 벽에 부딪히면 x속도의 부호를 바꿈
//				ball.setPower(-vx, vz);
//			}
//			else if (tZ <= (-3 + M_RADIUS) || tZ >= (3 - M_RADIUS)){ // 왼쪽이나 오른쪽 벽에 부딪히면 y속도의 부호를 바꿈
//				ball.setPower(vx,-vz);
//			}
//			else {
//				ball.change_is_used(); // 아래쪽에 부딪힌 경우 -> 공이 밑으로 떨어지면 red_ball의 m_is_used를 바꿈, white ball 위에 위치하도록
//				ball.setCenter(4.5f, (float)M_RADIUS, 0);
//			}
//			return;
//		}
//	}    
//	
//	void setPosition(float x, float y, float z)
//	{
//		D3DXMATRIX m;
//		this->m_x = x;
//		this->m_z = z;
//
//		D3DXMatrixTranslation(&m, x, y, z);
//		setLocalTransform(m);
//	}
//	
//    float getHeight(void) const { return M_HEIGHT; }
//	
//	
//	
//private :
//    void setLocalTransform(const D3DXMATRIX& mLocal) { m_mLocal = mLocal; }
//	
//	D3DXMATRIX              m_mLocal;
//    D3DMATERIAL9            m_mtrl;
//    ID3DXMesh*              m_pBoundMesh;
//};
//
// -----------------------------------------------------------------------------
// CLight class definition
// -----------------------------------------------------------------------------
//
//class CLight {
//public:
//    CLight(void)
//    {
//        static DWORD i = 0;
//        m_index = i++;
//        D3DXMatrixIdentity(&m_mLocal);
//        ::ZeroMemory(&m_lit, sizeof(m_lit));
//        m_pMesh = NULL;
//        m_bound._center = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//        m_bound._radius = 0.0f;
//    }
//    ~CLight(void) {}
//public:
//    bool create(IDirect3DDevice9* pDevice, const D3DLIGHT9& lit, float radius = 0.000001f) // 빛의 크기를 작게 하여 화면에 보이지 않도록 함
//    {
//        if (NULL == pDevice)
//            return false;
//        if (FAILED(D3DXCreateSphere(pDevice, radius, 10, 10, &m_pMesh, NULL)))
//            return false;
//		
//        m_bound._center = lit.Position;
//        m_bound._radius = radius;
//		
//        m_lit.Type          = lit.Type;
//        m_lit.Diffuse       = lit.Diffuse;
//        m_lit.Specular      = lit.Specular;
//        m_lit.Ambient       = lit.Ambient;
//        m_lit.Position      = lit.Position;
//        m_lit.Direction     = lit.Direction;
//        m_lit.Range         = lit.Range;
//        m_lit.Falloff       = lit.Falloff;
//        m_lit.Attenuation0  = lit.Attenuation0;
//        m_lit.Attenuation1  = lit.Attenuation1;
//        m_lit.Attenuation2  = lit.Attenuation2;
//        m_lit.Theta         = lit.Theta;
//        m_lit.Phi           = lit.Phi;
//        return true;
//    }
//    void destroy(void)
//    {
//        if (m_pMesh != NULL) {
//            m_pMesh->Release();
//            m_pMesh = NULL;
//        }
//    }
//    bool setLight(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld)
//    {
//        if (NULL == pDevice)
//            return false;
//		
//        D3DXVECTOR3 pos(m_bound._center);
//        D3DXVec3TransformCoord(&pos, &pos, &m_mLocal);
//        D3DXVec3TransformCoord(&pos, &pos, &mWorld);
//        m_lit.Position = pos;
//		
//        pDevice->SetLight(m_index, &m_lit);
//        pDevice->LightEnable(m_index, TRUE);
//        return true;
//    }
//
//    void draw(IDirect3DDevice9* pDevice)
//    {
//        if (NULL == pDevice)
//            return;
//        D3DXMATRIX m;
//        D3DXMatrixTranslation(&m, m_lit.Position.x, m_lit.Position.y, m_lit.Position.z);
//        pDevice->SetTransform(D3DTS_WORLD, &m);
//        pDevice->SetMaterial(&d3d::WHITE_MTRL);
//        m_pMesh->DrawSubset(0);
//    }
//
//    D3DXVECTOR3 getPosition(void) const { return D3DXVECTOR3(m_lit.Position); }
//
//private:
//    DWORD               m_index;
//    D3DXMATRIX          m_mLocal;
//    D3DLIGHT9           m_lit;
//    ID3DXMesh*          m_pMesh;
//    d3d::BoundingSphere m_bound;
//};
//
//
// -----------------------------------------------------------------------------
// Global variables
// -----------------------------------------------------------------------------
//CWall	g_legoPlane;
//CWall	g_legowall[4];
//CSphere	g_sphere[BLOCKNUM];
//CSphere g_red_ball; 
//CSphere g_white_ball;
//CLight	g_light;
//
//double g_camera_pos[3] = {0.0, 5.0, -8.0};
//
// -----------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------
//
//
//void destroyAllLegoBlock(void)
//{
//}
//
// initialization
//bool Setup()
//{
//	int i;
//	
//    D3DXMatrixIdentity(&g_mWorld);
//    D3DXMatrixIdentity(&g_mView);
//    D3DXMatrixIdentity(&g_mProj);
//		
//	 create plane and set the position
//    if (false == g_legoPlane.create(Device, -1, -1, 9, 0.03f, 6, d3d::GREEN)) return false;
//    g_legoPlane.setPosition(0.0f, -0.0006f / 5, 0.0f);
//	
//	 create walls and set the position. note that there are four walls
//	if (false == g_legowall[0].create(Device, -1, -1, 9, 0.3f, 0.12f, d3d::DARKRED)) return false;
//	g_legowall[0].setPosition(0.0f, 0.12f, 3.06f);
//	if (false == g_legowall[1].create(Device, -1, -1, 9, 0.3f, 0.12f, d3d::DARKRED)) return false;
//	g_legowall[1].setPosition(0.0f, 0.12f, -3.06f);
//	if (false == g_legowall[2].create(Device, -1, -1, 0.12f, 0.3f, 6.24f, d3d::DARKRED)) return false;
//	g_legowall[2].setPosition(-4.56f, 0.12f, 0.0f);
//	if (false == g_legowall[3].create(Device, -1, -1, 0.12f, 0.3f, 6.24f, d3d::DARKRED)) return false;
//	g_legowall[3].setPosition(4.56f, 0.12f, 0.0f);
//
//	 create blocks and set the position
//	for (i=0;i<BLOCKNUM;i++) {   // 블록들 위치 세팅
//		if (false == g_sphere[i].create(Device)) return false;
//		g_sphere[i].setCenter(spherePos[i][0], (float)M_RADIUS , spherePos[i][1]);
//		g_sphere[i].setPower(0,0);
//	}
//	
//	if (false == g_white_ball.create(Device, d3d::WHITE)) return false;
//	g_white_ball.setCenter(4.5f, (float)M_RADIUS, .0f);
//	g_white_ball.setPower(0, 0);
//	g_white_ball.change_is_used();   // 항상 true로 (white_ball은 상태가 변하지 않음, 항상 움직임)
//
//	if (false == g_red_ball.create(Device, d3d::DARKRED)) return false;
//	g_red_ball.setCenter(4.5f - 2*(float)M_RADIUS, (float)M_RADIUS, .0f);
//	g_red_ball.setPower(0, 0);
//
//	
//	 light setting 
//    D3DLIGHT9 lit;
//    ::ZeroMemory(&lit, sizeof(lit));
//    lit.Type         = D3DLIGHT_POINT;
//    lit.Diffuse      = d3d::WHITE; 
//	lit.Specular     = d3d::WHITE * 0.9f;
//    lit.Ambient      = d3d::WHITE * 0.9f;
//    lit.Position     = D3DXVECTOR3(0.0f, 3.0f, 0.0f);
//    lit.Range        = 100.0f;
//    lit.Attenuation0 = 0.0f;
//    lit.Attenuation1 = 0.9f;
//    lit.Attenuation2 = 0.0f;
//    if (false == g_light.create(Device, lit))
//        return false;
//	
//	 Position and aim the camera.
//	D3DXVECTOR3 pos(8.0f, 9.0f, 0.0f);
//	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
//	D3DXVECTOR3 up(0.0f, 2.0f, 0.0f);
//	D3DXMatrixLookAtLH(&g_mView, &pos, &target, &up);
//	Device->SetTransform(D3DTS_VIEW, &g_mView);
//	
//	 Set the projection matrix.
//	D3DXMatrixPerspectiveFovLH(&g_mProj, D3DX_PI / 4,
//        (float)Width / (float)Height, 1.0f, 100.0f);
//	Device->SetTransform(D3DTS_PROJECTION, &g_mProj);
//	
//     Set render states.
//    Device->SetRenderState(D3DRS_LIGHTING, TRUE);
//    Device->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
//    Device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
//	
//	g_light.setLight(Device, g_mWorld);
//	return true;
//}
//
//void Cleanup(void)
//{
//    g_legoPlane.destroy();
//	for(int i = 0 ; i < 4; i++) {
//		g_legowall[i].destroy();
//	}
//    destroyAllLegoBlock();
//    g_light.destroy();
//}
//
//
// timeDelta represents the time between the current image frame and the last image frame.
// the distance of moving balls should be "velocity * timeDelta"
//bool Display(float timeDelta)
//{
//	int i=0;
//	int j = 0;
//
//
//	if( Device )
//	{
//		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00afafaf, 1.0f, 0);
//		Device->BeginScene();
//		
//		 update the position of each ball. during update, check whether each ball hit by walls.
//		for( i = 0; i < 4; i++) { // 벽이 red_ball에 의해 부딪혔는지 확인
//			g_white_ball.ballUpdate(timeDelta);
//			g_red_ball.ballUpdate(timeDelta);
//			g_sphere[i].ballUpdate(timeDelta);
//			g_legowall[i].hitBy(g_red_ball);
//		}
//
//		
//		for (i = 0; i < BLOCKNUM; i++) { // block들이 red_ball에 의해 부딪혔는지 확인
//			if (!g_sphere[i].is_used()) {
//				g_sphere[i].hitBy(g_red_ball);
//			}
//		}
//
//		g_white_ball.hitBy(g_red_ball);   // 빨간 공이 하얀 공에 부딪혔나 확인 
//
//		 draw plane, walls, and spheres
//		g_legoPlane.draw(Device, g_mWorld);
//		for (i=0;i<3;i++) 	{
//			g_legowall[i].draw(Device, g_mWorld);
//		}
//
//		/*for (i = 0; i < BLOCKNUM; i++) {
//			if (!g_sphere[i].is_used()) {
//				g_sphere[i].draw(Device, g_mWorld);
//			}
//		}*/
//
//		if (!g_red_ball.is_used()) { // red_ball의 m_is_used가 false인 경우 white공 위에 위치하도록 함 -> space키가 눌리면 튕김
//			D3DXVECTOR3 coord3d = g_white_ball.getCenter();
//			g_red_ball.setCenter(coord3d.x - 2 * (float)M_RADIUS, coord3d.y, coord3d.z);
//			g_red_ball.setPower(0, 0);
//
//			if (g_red_ball.getCenter().z <= (-3 + M_RADIUS)) { // red_ball이 바깥으로 나가지 않도록 설정
//				g_red_ball.setCenter(coord3d.x - 2 * (float)M_RADIUS, coord3d.y, -3 + M_RADIUS);
//				g_red_ball.setPower(0, 0);
//			}
//			else if (g_red_ball.getCenter().z >= (3 - M_RADIUS)) {
//				g_red_ball.setCenter(coord3d.x - 2 * (float)M_RADIUS, coord3d.y, 3 - M_RADIUS);
//				g_red_ball.setPower(0, 0);
//			}
//		}
//
//		if (g_white_ball.getCenter().z <= -3) { // white_ball은 가장자리까지 갈 수 있도록 설정
//			g_white_ball.setCenter(4.5f, (float)M_RADIUS, -3 );
//		}
//		else if (g_white_ball.getCenter().z >= 3){
//			g_white_ball.setCenter(4.5f, (float)M_RADIUS, 3 );
//		}
//
//
//		 red_ball, white_ball 그리기
//		g_white_ball.draw(Device, g_mWorld);
//		g_red_ball.draw(Device, g_mWorld);
//        g_light.draw(Device);
//		
//		Device->EndScene();
//		Device->Present(0, 0, 0, 0);
//		Device->SetTexture( 0, NULL );
//	}
//	return true;
//}
//
//LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	static bool wire = false;
//	static bool isReset = true;
//    static int old_x = 0;
//    static int old_y = 0;
//    static enum { WORLD_MOVE, LIGHT_MOVE, BLOCK_MOVE } move = WORLD_MOVE;
//	
//	switch( msg ) {
//	case WM_DESTROY:
//        {
//			::PostQuitMessage(0);
//			break;
//        }
//	case WM_KEYDOWN:
//        {
//            switch (wParam) {
//            case VK_ESCAPE:
//				::DestroyWindow(hwnd);
//                break;
//            case VK_RETURN:
//                if (NULL != Device) {
//                    wire = !wire;
//                    Device->SetRenderState(D3DRS_FILLMODE,
//                        (wire ? D3DFILL_WIREFRAME : D3DFILL_SOLID));
//                }
//                break;
//            case VK_SPACE:    // space를 누르면 white_ball 위에 있던 red_ball의 m_is_used()값이 바뀌면서 위로 움직임
//				if (isReset) {
//					isReset = false;
//				}
//				else {
//					if (!g_red_ball.is_used()) {
//
//						g_red_ball.change_is_used();
//						g_red_ball.setPower(-1, 0);
//
//
//						break;
//					}
//				}
//				break;
//		
//			case VK_RIGHT:  // 화살표 오른쪽 키를 누르면 white_ball이 오른쪽으로 움직임
//				if (isReset) {
//				isReset = false;
//				}
//				else {
//
//				D3DXVECTOR3 _coord3d = g_white_ball.getCenter();
//				float _tZ = _coord3d.z;
//				if (_tZ >= 3 ) { // 바깥으로 빠져나가지 않도록 설정
//					_tZ = 3;
//					g_white_ball.setCenter(_coord3d.x, _coord3d.y, _tZ);
//				}
//				D3DXVECTOR3 coord3d = g_red_ball.getCenter();
//				float tZ = coord3d.z;
//				if (tZ >= (3 - M_RADIUS)) {
//					tZ = 3 - M_RADIUS;
//					g_red_ball.setCenter(coord3d.x, coord3d.y, tZ);
//					g_red_ball.setPower(0, 0);
//				}
//				if (!g_red_ball.is_used()) {  // red_ball의 m_is_used가 false인 경우 white_ball과 함께 움직임
//					g_red_ball.setPower(0, 0.7);
//				}
//				g_white_ball.setPower(0, 0.7);
//
//				break;
//				}
//				break;
//			case VK_LEFT: // 화살표 왼쪽 키를 누르면 white_ball이 오른쪽으로 움직임
//				if (isReset) {
//					isReset = false;
//				}
//				else {
//
//					D3DXVECTOR3 _coord3d = g_white_ball.getCenter();
//					float _tZ = _coord3d.z;
//					if (_tZ <= -3) { // 바깥으로 빠져나가지 않도록 설정
//						_tZ = -3;
//						g_white_ball.setCenter(_coord3d.x, _coord3d.y, _tZ);
//						break;
//					}
//					D3DXVECTOR3 coord3d = g_red_ball.getCenter();
//					float tZ = coord3d.z;
//					if (tZ <= (-3 + M_RADIUS)) {
//						tZ = -3 + M_RADIUS;
//						g_red_ball.setCenter(coord3d.x, coord3d.y, tZ);
//						g_red_ball.setPower(0, 0);
//						break;
//					}
//					if (!g_red_ball.is_used()) { // red_ball의 m_is_used가 false인 경우 white_ball과 함께 움직임
//						g_red_ball.setPower(0, -0.7);
//					}
//					g_white_ball.setPower(0, -0.7);
//					break;
//				}
//				
//				
//			break;
//			}
//
//			default:   
//				break;
//			break;
//
//        }
//	case WM_KEYUP:
//		if (!g_red_ball.is_used()) {
//			g_red_ball.setPower(0, 0);
//		}
//		g_white_ball.setPower(0, 0);
//	}
//
//	return ::DefWindowProc(hwnd, msg, wParam, lParam);
//}
//
//int WINAPI WinMain(HINSTANCE hinstance,
//				   HINSTANCE prevInstance, 
//				   PSTR cmdLine,
//				   int showCmd)
//{
//    srand(static_cast<unsigned int>(time(NULL)));
//	
//	if(!d3d::InitD3D(hinstance,
//		Width, Height, true, D3DDEVTYPE_HAL, &Device))
//	{
//		::MessageBox(0, "InitD3D() - FAILED", 0, 0);
//		return 0;
//	}
//	
//	if(!Setup())
//	{
//		::MessageBox(0, "Setup() - FAILED", 0, 0);
//		return 0;
//	}
//	
//	d3d::EnterMsgLoop( Display );
//	
//	Cleanup();
//	
//	Device->Release();
//	
//	return 0;
//}