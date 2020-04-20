#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<Windows.h>
#include<iostream>
#include<sstream>
#define GRIDSIZE 25
#define LVL1_WIDTH 9
#define LVL1_HEIGHT 9
#define LVL2_WIDTH 16
#define LVL2_HEIGHT 16
#define LVL3_WIDTH 30
#define LVL3_HEIGHT 16
#define LVL1_NUM 10
#define LVL2_NUM 40
#define LVL3_NUM 99
using namespace sf;

//ö�ٶ�������״̬
typedef enum GRIDSTATE
{
	ncNULL,   //�յ�
	ncUNDOWN, //��������
	ncMINE,   //����
	ncONE,    //1
	ncTWO,    //2
	ncTHREE,  //3
	ncFOUR,   //4
	ncFIVE,   //5
	ncSIX,    //6
	ncSEVEN,  //7
	ncEIGHT,  //8
	ncFLAG,   //���
	ncQ,      //�ʺ�
	ncX,      //����
	ncBOMBING,//��ը_��
	ncUNFOUND//δ����_��
};
typedef enum GAMEOVERSTATE
{
	ncNO,   //��Ϸδ����
	ncWIN,  //��Ϸʤ��
	ncLOSE  //��Ϸʧ��
};
class LEI
{
public:
	int mState;      //դ��״̬
	int mStateBackUp;//դ��״̬����
	bool isPress;     //դ���Ƿ񱻵��
};
class Game
{
public:
	sf::RenderWindow window;//���ڶ�������
	Game();
	~Game();
	bool gameover, gamequit;
	int Window_width, Window_height, stageWidth, stageHeight, mMineNum, mFlagCalc;
	int gamelvl, mTime;//��Ϸ�Ѷȣ���Ϸ��ʱ
	LEI mGameData[LVL3_HEIGHT][LVL3_WIDTH];
	bool isGameBegin;//��Ϸ�Ƿ�ʼ
	int isGameOverState;//��Ϸ����״̬
	Vector2i mCornPoint;//��̨�󶥵�����
	int gridsize;//��Ĵ�С
	int imgBGNo, imgSkinNo;
	Vector2i press1, press2;

	Texture tBackground, tTiles, tButtons, tNum, tTimer, tCounter, tGameOver;
	Sprite sBackground, sTiles, sButtons, sNum, sTimer, sCounter, sGameOver;
	sf::IntRect ButtonRectEasy, ButtonRectNormal, ButtonRectHard, ButtonRectBG, ButtonRectSkin, ButtonRectRestart, ButtonRectQuit;
	bool MButtonRectEasy, MButtonRectNormal, MButtonRectHard, MButtonRectBG, MButtonRectSkin, MButtonRectRestart, MButtonRectQuit;
	bool PButtonRectEasy, PButtonRectNormal, PButtonRectHard, PButtonRectBG, PButtonRectSkin, PButtonRectRestart, PButtonRectQuit;

	SoundBuffer sbWin, sbBoom;
	Sound soundWin, soundBoom;
	Music bkMusic;

	sf::Clock mouseClickTimer, gameClock;

	void Run();

	void Initial();
	void IniData();
	void LoadMediaData();
	void MineSet(int Py, int Px);//����

	void Input();
	void RButtonDown(Vector2i mPoint);  //�Ҽ�����
	void LButtonDown(Vector2i mPoint);  //�������
	void LButtonDblClk(Vector2i mPoint);//���˫��

	void NullClick(int j, int i);//���ҿտ�

	void Logic();
	void isWin();
	void unCover();

	void Draw();
	void DrawGrid();
	void DrawButton();
	void DrawScore();
	void DrawTimer();
	void DrawGameEnd();

};

// TODO: ���Ҫ�ڴ˴�Ԥ����ı�ͷ


