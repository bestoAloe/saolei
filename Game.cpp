#include "Game.h"
using namespace sf;
Game::Game()
{
	Window_width = 860;
	Window_height = 600;

	gamelvl = 2;
	imgBGNo = 1;
	imgSkinNo = 1;
	window.create(sf::VideoMode(Window_width, Window_height), L"MineSweeper by 禹建伟");
}


Game::~Game()
{
}

void Game::Initial()
{
	window.setFramerateLimit(60);
	gridsize = GRIDSIZE;//点击位置的块的大小

	switch (gamelvl)
	{
	case 1:
		stageWidth = LVL1_WIDTH;
		stageHeight = LVL1_HEIGHT;
		mMineNum = LVL1_NUM;
		break;
	case 2:
		stageWidth = LVL2_WIDTH;
		stageHeight = LVL2_HEIGHT;
		mMineNum = LVL2_NUM;
		break;
	case 3:
		stageWidth = LVL3_WIDTH;
		stageHeight = LVL3_HEIGHT;
		mMineNum = LVL3_NUM;
		break;
	default:
		break;
	}
	gameover = false;
	gamequit = false;
	isGameOverState = ncNO;//初始化游戏结束状态
	mFlagCalc = 0;         //初始化旗子数量
	isGameBegin = false;   //初始化游戏是否开始
	mTime = 0;             //初始化游戏进行时间

	mCornPoint.x = (Window_width - stageWidth * GRIDSIZE) / 2;   //使舞台处于窗口中心位置
	mCornPoint.y = (Window_height - stageHeight * GRIDSIZE) / 2;
	IniData();   //初始化数据
	LoadMediaData();  //加载素材
}
void Game::IniData()
{
	int i, j;
	for (j = 0; j < stageHeight; j++)//所有块置为空且未点击
	{
		for (i = 0; i < stageWidth; i++)
		{
			mGameData[j][i].mState = ncUNDOWN;
			mGameData[j][i].isPress = false;
		}
	}
	//鼠标悬浮改变按钮样式
	MButtonRectEasy = false;
	MButtonRectNormal = false;
	MButtonRectHard = false;
	MButtonRectBG = false;
	MButtonRectSkin = false;
	MButtonRectRestart = false;
	MButtonRectQuit = false;

	PButtonRectEasy = false;
	PButtonRectNormal = false;
	PButtonRectHard = false;
	PButtonRectBG = false;
	PButtonRectSkin = false;
	PButtonRectRestart = false;
	PButtonRectQuit = false;
}
void Game::LoadMediaData()
{
	std::stringstream ss;
	ss << "data/images/BK0" << imgBGNo << ".jpg";
	if (!tBackground.loadFromFile(ss.str()))
	{
		std::cout << "BK image 没有找到" << std::endl;
	}
	ss.str("");//清空字符串
	ss << "data/images/Game" << imgSkinNo << ".jpg";
	if (!tTiles.loadFromFile(ss.str()))
		std::cout << "Game Skin image 没有找到" << std::endl;
	if (!tNum.loadFromFile("data/images/num.jpg"))
		std::cout << "num.jpg 没有找到" << std::endl;
	if (!tTimer.loadFromFile("data/images/jishiqi.jpg"))
		std::cout << "jishiqi.jpg 没有找到" << std::endl;
	if (!tCounter.loadFromFile("data/images/jishuqi.jpg"))
		std::cout << "jishuqi.jpg 没有找到" << std::endl;
	if (!tButtons.loadFromFile("data/images/button.jpg"))
		std::cout << "button.jpg 没有找到" << std::endl;
	if (!tGameOver.loadFromFile("data/images/gameover.jpg"))
		std::cout << "gameover.jpg 没有找到" << std::endl;
	sBackground.setTexture(tBackground);
	sTiles.setTexture(tTiles);
	sButtons.setTexture(tButtons);
	sNum.setTexture(tNum);
	sTimer.setTexture(tTimer);
	sCounter.setTexture(tCounter);
	sGameOver.setTexture(tGameOver);
}

void Game::Input()         //击中按钮
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
			gamequit = true;
		}
		if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Escape)
		{
			window.close();
			gamequit = true;
		}
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)//左键单双击
		{
			press2 = Mouse::getPosition(window);
			if (isGameOverState == ncNO)
			{
				if (mouseClickTimer.getElapsedTime().asMilliseconds() > 300 || (press1.x != press2.x || press1.y != press2.y))
				{
					LButtonDown(Mouse::getPosition(window));
					std::cout << "左单击" << std::endl;
				}
				else if (mouseClickTimer.getElapsedTime().asMilliseconds() < 300 && (press1.x == press2.x && press1.y == press2.y))
				{
					LButtonDblClk(Mouse::getPosition(window));
					std::cout << "左双击" << std::endl;
				}
			}
			if (mouseClickTimer.getElapsedTime().asMilliseconds() > 300 || (press1.x != press2.x || press1.y != press2.y))
			{
				std::cout << "左单击" << std::endl;

				if (isGameOverState == ncNO)
				{
					//难度按钮
					if (isGameBegin == false)
					{
						if (ButtonRectEasy.contains(event.mouseButton.x, event.mouseButton.y))
							PButtonRectEasy = true;
						else
							PButtonRectEasy = false;
						if (ButtonRectNormal.contains(event.mouseButton.x, event.mouseButton.y))
							PButtonRectNormal = true;
						else
							PButtonRectNormal = false;
						if (ButtonRectHard.contains(event.mouseButton.x, event.mouseButton.y))
							PButtonRectHard = true;
						else
							PButtonRectHard = false;
					}
				}
				//背景按钮
				if (ButtonRectBG.contains(event.mouseButton.x, event.mouseButton.y))
					PButtonRectBG = true;
				else
					PButtonRectBG = false;
				//皮肤按钮
				if (ButtonRectSkin.contains(event.mouseButton.x, event.mouseButton.y))
					PButtonRectSkin = true;
				else
					PButtonRectSkin = false;
				//重来按钮
				if (ButtonRectRestart.contains(event.mouseButton.x, event.mouseButton.y))
					PButtonRectRestart = true;
				else
					PButtonRectRestart = false;
				//离开按钮
				if (ButtonRectQuit.contains(event.mouseButton.x, event.mouseButton.y))
					PButtonRectQuit = true;
				else
					PButtonRectQuit = false;
			}
		}
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)//左键松开
		{

			if (isGameOverState == ncNO)
			{
				press1 = Mouse::getPosition(window);
				mouseClickTimer.restart();
				//难度按钮
				if (isGameBegin == false)
				{
					if (ButtonRectEasy.contains(event.mouseButton.x, event.mouseButton.y))
						gamelvl = 1;
					if (ButtonRectNormal.contains(event.mouseButton.x, event.mouseButton.y))
						gamelvl = 2;
					if (ButtonRectHard.contains(event.mouseButton.x, event.mouseButton.y))
						gamelvl = 3;
					Initial();
				}
			}
			//背景按钮
			if (ButtonRectBG.contains(event.mouseButton.x, event.mouseButton.y))
			{
				imgBGNo++;
				if (imgBGNo > 7)
					imgBGNo = 1;
				LoadMediaData();
			}
			//皮肤按钮
			if (ButtonRectSkin.contains(event.mouseButton.x, event.mouseButton.y))
			{
				imgSkinNo++;
				if (imgSkinNo > 6)
					imgSkinNo = 1;
				LoadMediaData();
			}
			//重来按钮
			if (ButtonRectRestart.contains(event.mouseButton.x, event.mouseButton.y))
				Initial();
			//离开按钮
			if (ButtonRectQuit.contains(event.mouseButton.x, event.mouseButton.y))
			{
				window.close();
				gamequit = true;
			}
		}
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)//右键单击
		{
			if (isGameOverState == ncNO)
				RButtonDown(Mouse::getPosition(window));
			std::cout << "rightpressed" << std::endl;
		}
		if (event.type == sf::Event::MouseMoved)
		{
			if (isGameOverState == ncNO)
			{
				//难度按钮
				if (isGameBegin == false)
				{
					if (ButtonRectEasy.contains(event.mouseMove.x, event.mouseMove.y))
						MButtonRectEasy = true;
					else
						MButtonRectEasy = false;
					if (ButtonRectNormal.contains(event.mouseMove.x, event.mouseMove.y))
						MButtonRectNormal = true;
					else
						MButtonRectNormal = false;
					if (ButtonRectHard.contains(event.mouseMove.x, event.mouseMove.y))
						MButtonRectHard = true;
					else
						MButtonRectHard = false;
				}
			}
			//背景按钮
			if (ButtonRectBG.contains(event.mouseMove.x, event.mouseMove.y))
				MButtonRectBG = true;
			else
				MButtonRectBG = false;
			//皮肤按钮
			if (ButtonRectSkin.contains(event.mouseMove.x, event.mouseMove.y))
				MButtonRectSkin = true;
			else
				MButtonRectSkin = false;
			//重来按钮
			if (ButtonRectRestart.contains(event.mouseMove.x, event.mouseMove.y))
				MButtonRectRestart = true;
			else
				MButtonRectRestart = false;
			//离开按钮
			if (ButtonRectQuit.contains(event.mouseMove.x, event.mouseMove.y))
				MButtonRectQuit = true;
			else
				MButtonRectQuit = false;
		}
	}
}     


void Game::Logic()
{
	isWin();
}

void Game::isWin()
{
	int i, j, c = 0;
	if (mFlagCalc == mMineNum)
	{
		for (i = 0; i < stageWidth; i++)
			for (j = 0; j < stageHeight; j++)
			{
				if (mGameData[j][i].mState == ncFLAG)
					if (mGameData[j][i].mStateBackUp == ncMINE)
						c++;
			}
	}
	else
	{
		if (isGameOverState != ncLOSE)
		{
			for (i = 0; i < stageWidth; i++)
				for (j = 0; j < stageHeight; j++)
				{
					if (mGameData[j][i].isPress == false || mGameData[j][i].mState == ncFLAG)
						c++;
				}
		}
	}
	if (c == mMineNum)
	{
		isGameBegin = false;
		isGameOverState = ncWIN;
	}
}

void Game::Draw()
{
	window.clear();
	//绘制背景
	sBackground.setPosition(0, 0);
	window.draw(sBackground);
	//绘制舞台
	DrawGrid();
	DrawButton();
	DrawScore();
	DrawTimer();

	if (isGameOverState)
		DrawGameEnd();

	window.display();
}

void Game::MineSet(int Py, int Px)//布雷
{
	int mCount, i, j, k, l;
	mCount = 0;

	srand(time(NULL));//用当前系统时间作为随机数生成器的种子
	do {
		bool flag = true;
		k = rand() % stageHeight;
		l = rand() % stageWidth;
		for (i = Py - 1; i < Py + 2; i++)
			for (j = Px - 1; j < Px + 2; j++)
				if (i >= 0 && i < stageHeight &&i >= 0 && j < stageHeight)
					if (k == i && l == j)
						flag = false;

		if (flag && mGameData[k][l].mState == ncUNDOWN)
		{
			mGameData[k][l].mState = ncMINE;
			mGameData[k][l].mStateBackUp = ncMINE;
			mCount++;
		}
	} while (mCount != mMineNum);

	//方格赋值
	for (i = 0; i < stageHeight; i++)
	{
		for (j = 0; j < stageWidth; j++)
		{
			if (mGameData[i][j].mState != ncMINE)
			{
				mCount = 0;
				for (k = i - 1; k < i + 2; k++)
				{
					for (l = j - 1; l < j + 2; l++)
					{
						if (k >= 0 && k < stageHeight && l >= 0 && l < stageWidth)
						{
							if (mGameData[k][l].mState == ncMINE)
								mCount++;
						}
					}
				}
				switch (mCount)
				{
				case 0:
					mGameData[i][j].mState = ncNULL;
					break;
				case 1:
					mGameData[i][j].mState = ncONE;
					break;
				case 2:
					mGameData[i][j].mState = ncTWO;
					break;
				case 3:
					mGameData[i][j].mState = ncTHREE;
				case 4:
					mGameData[i][j].mState = ncFOUR;
					break;
				case 5:
					mGameData[i][j].mState = ncFIVE;
					break;
				case 6:
					mGameData[i][j].mState = ncSIX;
					break;
				case 7:
					mGameData[i][j].mState = ncSEVEN;
					break;
				case 8:
					mGameData[i][j].mState = ncEIGHT;
					break;
				}
			}
		}
	}
}

void Game::unCover()
{
	int i, j;
	for (j = 0; j < stageHeight; j++)
		for (i = 0; i < stageWidth; i++)
		{
			if (mGameData[j][i].isPress == false)
				if (mGameData[j][i].mState == ncMINE)
				{
					mGameData[j][i].isPress = true;
					mGameData[j][i].mState = ncUNFOUND;
				}
		}
}

void Game::RButtonDown(Vector2i mPoint) //右键单击
{
	int i, j;
	i = (mPoint.x - mCornPoint.x) / gridsize;
	j = (mPoint.y - mCornPoint.y) / gridsize;

	if (i >= 0 && i < stageWidth && j >= 0 && j < stageHeight)
	{
		if (mGameData[j][i].isPress == false)
		{
			mGameData[j][i].isPress = true;
			mGameData[j][i].mStateBackUp = mGameData[j][i].mState;
			mGameData[j][i].mState = ncFLAG;
			mFlagCalc++;
		}
		else
		{
			if (mGameData[j][i].mState == ncFLAG)
			{
				mGameData[j][i].isPress = true;
				mGameData[j][i].mState = ncQ;
				mFlagCalc--;
			}
			else if (mGameData[j][i].mState == ncQ)
			{
				mGameData[j][i].isPress = false;
				mGameData[j][i].mState = mGameData[j][i].mStateBackUp;
			}
		}
	}
}

void Game::LButtonDown(Vector2i mPoint)  //左键单击
{
	int i, j;
	i = (mPoint.x - mCornPoint.x) / gridsize;//获取当前点击块的位置
	j = (mPoint.y - mCornPoint.y) / gridsize;

	if (i >= 0 && i < stageWidth && j >= 0 && j < stageHeight)//点击在舞台内
	{
		if (isGameBegin == false)
		{
			isGameBegin = true;
			gameClock.restart();
			MineSet(j, i);
		}
		if (mGameData[j][i].mState != ncFLAG)
		{
			if (mGameData[j][i].isPress == false)
			{
				mGameData[j][i].isPress = true;
				if (mGameData[j][i].mState == ncMINE)
				{
					isGameBegin = false;
					isGameOverState = ncLOSE;
					mGameData[j][i].mState = ncBOMBING;
					unCover();
				}
			}
		}
		if (mGameData[j][i].mState == ncNULL)
		{
			NullClick(j, i);
		}
	}
}

void Game::NullClick(int j, int i)
{
	int k, l;
	for (k = j - 1; k < j + 2; k++)
	{
		for (l = i - 1; l < i + 2; l++)
		{
			if (k >= 0 && k < stageHeight && l >= 0 && l < stageWidth)
			{
				if (mGameData[k][l].isPress == false)
				{
					mGameData[k][l].isPress = true;
					if (mGameData[k][l].mState == ncNULL)
						NullClick(k, l);
				}
			}
		}
	}
}

void Game::LButtonDblClk(Vector2i mPoint)//左键双击
{
	int i, j, k, l, lvl;
	i = (mPoint.x - mCornPoint.x) / gridsize;
	j = (mPoint.y - mCornPoint.y) / gridsize;

	if (i >= 0 && i < stageHeight&&j >= 0 && j < stageHeight)
	{
		if (mGameData[j][i].mState != ncFLAG)
			for (k = j - 1; k < j + 2; k++)
				for (l = i - 1; l < i + 2; l++)
					if (k >= 0 && k < stageHeight&&l >= 0 && l < stageWidth)
					{
						if (mGameData[k][l].mState == ncFLAG)
						{
							if (mGameData[k][l].mStateBackUp != ncMINE)//旗插错 双击失败
							{
								isGameOverState = ncLOSE;
								isGameBegin = false;
								unCover();
							}
						}
						else
						{
							if (mGameData[k][l].isPress == false)
							{
								mGameData[k][l].isPress = true;
								if (mGameData[k][l].mState == ncMINE)
								{
									isGameOverState = ncLOSE;
									isGameBegin = false;
									mGameData[k][l].mState = ncBOMBING;
									unCover();
								}
								if (mGameData[k][l].mState == ncNULL)
									NullClick(k, l);
							}
						}
					}
	}
}

void Game::DrawGrid()
{
	int i, j;
	for (j = 0; j < stageHeight; j++)
	{
		for (i = 0; i < stageWidth; i++)
		{
			if (mGameData[j][i].isPress == true)
			{
				sTiles.setTextureRect(IntRect(mGameData[j][i].mState * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
				sTiles.setPosition(mCornPoint.x + i * GRIDSIZE, mCornPoint.y + j * GRIDSIZE);
			}
			else
			{
				sTiles.setTextureRect(IntRect(ncUNDOWN * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
				sTiles.setPosition(mCornPoint.x + i * GRIDSIZE, mCornPoint.y + j * GRIDSIZE);
			}
			window.draw(sTiles);
		}
	}
}

void Game::DrawButton()
{
	Vector2i LeftCorner;
	int ButtonWidth = 60;
	int ButtonHeight = 36;
	int detaX;
	detaX = (Window_width - ButtonWidth * 7) / 8;
	LeftCorner.y = Window_height - GRIDSIZE * 3;

	//ButtonRectEasy
	LeftCorner.x = detaX;
	if (!MButtonRectEasy)
		sButtons.setTextureRect(IntRect(0 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	else if (!PButtonRectEasy)
		sButtons.setTextureRect(IntRect(14 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	else
		sButtons.setTextureRect(IntRect(7 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);
	ButtonRectEasy.left = LeftCorner.x;
	ButtonRectEasy.top = LeftCorner.y;
	ButtonRectEasy.width = ButtonWidth;
	ButtonRectEasy.height = ButtonHeight;
	window.draw(sButtons);
	//ButtonRectNormal
	LeftCorner.x = detaX * 2 + ButtonWidth * 1;
	if (!MButtonRectNormal)
		sButtons.setTextureRect(IntRect(1 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	else if (!PButtonRectNormal)
		sButtons.setTextureRect(IntRect(14 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	else
		sButtons.setTextureRect(IntRect(7 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);
	ButtonRectNormal.left = LeftCorner.x;
	ButtonRectNormal.top = LeftCorner.y;
	ButtonRectNormal.width = ButtonWidth;
	ButtonRectNormal.height = ButtonHeight;
	window.draw(sButtons);
	//ButtonRectHard
	LeftCorner.x = detaX * 3 + ButtonWidth * 2;
	if (!MButtonRectHard)
		sButtons.setTextureRect(IntRect(2 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	else if (!PButtonRectHard)
		sButtons.setTextureRect(IntRect(16 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	else
		sButtons.setTextureRect(IntRect(9 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);
	ButtonRectHard.left = LeftCorner.x;
	ButtonRectHard.top = LeftCorner.y;
	ButtonRectHard.width = ButtonWidth;
	ButtonRectHard.height = ButtonHeight;
	window.draw(sButtons);
	//ButtonRectBG
	LeftCorner.x = detaX * 5 + ButtonWidth * 4;
	if (!MButtonRectBG)
		sButtons.setTextureRect(IntRect(4 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	else if (!PButtonRectBG)
		sButtons.setTextureRect(IntRect(18 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	else
		sButtons.setTextureRect(IntRect(11 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);
	ButtonRectBG.left = LeftCorner.x;
	ButtonRectBG.top = LeftCorner.y;
	ButtonRectBG.width = ButtonWidth;
	ButtonRectBG.height = ButtonHeight;
	window.draw(sButtons);
	//ButtonRectSkin
	LeftCorner.x = detaX * 4 + ButtonWidth * 3;
	if (!MButtonRectSkin)
		sButtons.setTextureRect(IntRect(3 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	else if (!PButtonRectSkin)
		sButtons.setTextureRect(IntRect(17 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	else
		sButtons.setTextureRect(IntRect(10 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);
	ButtonRectSkin.left = LeftCorner.x;
	ButtonRectSkin.top = LeftCorner.y;
	ButtonRectSkin.width = ButtonWidth;
	ButtonRectSkin.height = ButtonHeight;
	window.draw(sButtons);
	//ButtonRectRestart
	LeftCorner.x = detaX * 6 + ButtonWidth * 5;
	if (!MButtonRectRestart)
		sButtons.setTextureRect(IntRect(5 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	else if (!PButtonRectRestart)
		sButtons.setTextureRect(IntRect(19 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	else
		sButtons.setTextureRect(IntRect(12 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);
	ButtonRectRestart.left = LeftCorner.x;
	ButtonRectRestart.top = LeftCorner.y;
	ButtonRectRestart.width = ButtonWidth;
	ButtonRectRestart.height = ButtonHeight;
	window.draw(sButtons);
	//ButtonRectQuit
	LeftCorner.x = detaX * 7 + ButtonWidth * 6;
	if (!MButtonRectQuit)
		sButtons.setTextureRect(IntRect(6 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	else if (!PButtonRectQuit)
		sButtons.setTextureRect(IntRect(20 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	else
		sButtons.setTextureRect(IntRect(13 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	sButtons.setPosition(LeftCorner.x, LeftCorner.y);
	ButtonRectQuit.left = LeftCorner.x;
	ButtonRectQuit.top = LeftCorner.y;
	ButtonRectQuit.width = ButtonWidth;
	ButtonRectQuit.height = ButtonHeight;
	window.draw(sButtons);
}

void Game::DrawScore()
{
	Vector2i LeftCorner;
	LeftCorner.x = Window_width - sCounter.getLocalBounds().width * 1.25;
	LeftCorner.y = sCounter.getLocalBounds().height * 0.5;
	sCounter.setPosition(LeftCorner.x, LeftCorner.y);
	window.draw(sCounter);

	int NumSize = sNum.getLocalBounds().height;
	LeftCorner.x = LeftCorner.x + sCounter.getLocalBounds().width - NumSize;
	LeftCorner.y = LeftCorner.y + sCounter.getLocalBounds().height * 0.5 - NumSize * 0.5;

	int mScore = mMineNum - mFlagCalc;
	//绘制个位数数字
	int a = mScore % 10;
	sNum.setTextureRect(IntRect(a*NumSize, 0, NumSize, NumSize));
	sNum.setPosition(LeftCorner.x, LeftCorner.y);
	window.draw(sNum);
	//绘制十位数数字
	mScore /= 10;
	a = mScore % 10;
	LeftCorner.x -= NumSize;
	sNum.setTextureRect(IntRect(a*NumSize, 0, NumSize, NumSize));
	sNum.setPosition(LeftCorner.x, LeftCorner.y);
	window.draw(sNum);
	//绘制百位数数字
	mScore /= 10;
	a = mScore % 10;
	LeftCorner.x -= NumSize;
	sNum.setTextureRect(IntRect(a*NumSize, 0, NumSize, NumSize));
	sNum.setPosition(LeftCorner.x, LeftCorner.y);
	window.draw(sNum);
}

void Game::DrawTimer()
{
	Vector2i LeftCorner;
	LeftCorner.x = sTimer.getLocalBounds().width * 0.25;
	LeftCorner.y = sTimer.getLocalBounds().height * 0.5;
	sTimer.setPosition(LeftCorner.x, LeftCorner.y);
	window.draw(sTimer);
	if (isGameBegin)
		mTime = gameClock.getElapsedTime().asSeconds();
	int mScore = mTime;
	if (mScore > 999) mScore = 999;

	int NumSize = sNum.getLocalBounds().height;
	LeftCorner.x = LeftCorner.x + sTimer.getLocalBounds().width - NumSize;
	LeftCorner.y = LeftCorner.y + sTimer.getLocalBounds().height * 0.5 - NumSize * 0.5;
	//绘制个位数数字
	int a = mScore % 10;
	sNum.setTextureRect(IntRect(a*NumSize, 0, NumSize, NumSize));
	sNum.setPosition(LeftCorner.x, LeftCorner.y);
	window.draw(sNum);
	//绘制十位数数字
	mScore /= 10;
	a = mScore % 10;
	LeftCorner.x -= NumSize;
	sNum.setTextureRect(IntRect(a*NumSize, 0, NumSize, NumSize));
	sNum.setPosition(LeftCorner.x, LeftCorner.y);
	window.draw(sNum);
	//绘制百位数数字
	mScore /= 10;
	a = mScore % 10;
	LeftCorner.x -= NumSize;
	sNum.setTextureRect(IntRect(a*NumSize, 0, NumSize, NumSize));
	sNum.setPosition(LeftCorner.x, LeftCorner.y);
	window.draw(sNum);
}

void Game::DrawGameEnd()
{
	Vector2i LeftCorner;
	int ButtonWidth = 200;
	int ButtonHeight = sGameOver.getLocalBounds().height;
	LeftCorner.x = (Window_width - ButtonWidth) / 2;
	LeftCorner.y = (Window_height - ButtonHeight) / 2;

	sGameOver.setPosition(LeftCorner.x, LeftCorner.y);

	if (isGameOverState == ncWIN)
	{
		sGameOver.setTextureRect(IntRect(0 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	}
	if (isGameOverState == ncLOSE)
	{
		sGameOver.setTextureRect(IntRect(1 * ButtonWidth, 0, ButtonWidth, ButtonHeight));
	}
	window.draw(sGameOver);
}


void Game::Run()
{
	do
	{
		Initial();
		while (window.isOpen() && gameover == false)
		{
			Input();
			Logic();
			Draw();
		}
	} while (!gamequit && window.isOpen());
}