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

//枚举定义网格状态
typedef enum GRIDSTATE
{
	ncNULL,   //空地
	ncUNDOWN, //背景方块
	ncMINE,   //地雷
	ncONE,    //1
	ncTWO,    //2
	ncTHREE,  //3
	ncFOUR,   //4
	ncFIVE,   //5
	ncSIX,    //6
	ncSEVEN,  //7
	ncEIGHT,  //8
	ncFLAG,   //标记
	ncQ,      //问号
	ncX,      //备用
	ncBOMBING,//爆炸_雷
	ncUNFOUND//未检测出_雷
};
typedef enum GAMEOVERSTATE
{
	ncNO,   //游戏未结束
	ncWIN,  //游戏胜利
	ncLOSE  //游戏失败
};
class LEI
{
public:
	int mState;      //栅格状态
	int mStateBackUp;//栅格状态备份
	bool isPress;     //栅格是否被点击
};
class Game
{
public:
	sf::RenderWindow window;//窗口对象声明
	Game();
	~Game();
	bool gameover, gamequit;
	int Window_width, Window_height, stageWidth, stageHeight, mMineNum, mFlagCalc;
	int gamelvl, mTime;//游戏难度，游戏计时
	LEI mGameData[LVL3_HEIGHT][LVL3_WIDTH];
	bool isGameBegin;//游戏是否开始
	int isGameOverState;//游戏结束状态
	Vector2i mCornPoint;//舞台左顶点坐标
	int gridsize;//块的大小
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
	void MineSet(int Py, int Px);//布雷

	void Input();
	void RButtonDown(Vector2i mPoint);  //右键单击
	void LButtonDown(Vector2i mPoint);  //左键单击
	void LButtonDblClk(Vector2i mPoint);//左键双击

	void NullClick(int j, int i);//查找空块

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

// TODO: 添加要在此处预编译的标头


