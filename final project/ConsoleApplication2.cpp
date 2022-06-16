#include <iostream> 
#include "SBDL.h"
#include <ctime>
#include <fstream>
using namespace std;

int main(int argc, const char* argv[]) 
{
	int highscore = 0;
	fstream f1("highscore.txt", ios::in);
	f1 >> highscore;
	f1.close();

	SDL_Rect backGround[2];
	for (int i = 0, y = 0; i < 2; i++, y -= 600)
	{
		backGround[i] = { 0,y,400,600 };
	}
	SDL_Rect ninjaRect = { 320,440,45,45 };
	SDL_Rect birdRect = { 40,90,40,45 };
	SDL_Rect balconyBig[1];
	for (int i = 0, y = -700; i < 1; i++, y -= (rand()%1000)+1000)
	{
		balconyBig[i] = { 40,y,170,95 };
	}
	SDL_Rect balconySmall[1];
	for (int i = 0, y = -200; i < 1; i++, y -= (rand()%1200)+1200)
	{
		balconySmall[i] = { 40,y,100,50 };
	}
	SDL_Rect spikeRect[1];
	for (int i = 0, y = -440; i < 1; i++, y -= (rand() % 1200) + 1200)
	{
		spikeRect[i] = { 327,y,50,120 };
	}
	SDL_Rect throwerRect[1];
	for (int i = 0, y = -950; i < 1; i++, y -= 600)
	{
		throwerRect[i] = { 25,y,60,50 };
	}
	SDL_Rect Rope = { 35,-10,330,60 };
	SDL_Rect squirrelRec = { 40,Rope.y,60,40 };
	SDL_Rect bladeRect = { 30,150,25,25 };
	SDL_Rect shieldRect = { 327,-900,45,45 };

	int move = 4;
	int frameCount = 0;
	bool inAir = false;
	bool whichWall = true;
	bool bird = true;
	bool squirrel = true;
	bool ninjaFall = false;
	bool blade = false;
	int birdCount = 0;
	bool spike = true;
	int ninjaCounter = 0;
	int ninjump = 15;
	bool shield = false;
	bool bubbleAvailable = true;
	int scoreSave = 0;
	int score = 0;
	bool musicOn = true;

	SBDL::InitEngine("Test", 400, 600);

	
	//loading textures
	Texture backGroundTex = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets/background/back1.png");
	Texture RopeTex = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets2/obstacles/rope/rope.png");
	Texture ninjaTexL1 = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets/run/4.png");
	Texture ninjaTexL2 = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets/run/5.png");
	Texture ninjaTexL3 = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets/run/6.png");
	Texture ninjaTexR1 = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets/run/1.png");
	Texture ninjaTexR2 = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets/run/2.png");
	Texture ninjaTexR3 = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets/run/3.png");
	Texture jumpTex1 = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/ConsoleApplication2/Debug/assets/run/7.png");
	Texture jumpTex2 = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/ConsoleApplication2/Debug/assets/run/8.png");
	Texture jumpTex3 = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/ConsoleApplication2/Debug/assets/run/9.png");
	Texture jumpTex4 = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/ConsoleApplication2/Debug/assets/run/10.png");
	Texture spikeTex = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets2/obstacles/spike/SPIKES.png");
	Texture shieldTex = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets2/Shield/shield.png");
	Texture bird1 = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets2/obstacles/bird/bird1.png");
	Texture bird2 = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets2/obstacles/bird/bird2.png");
	Texture bird3 = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets2/obstacles/bird/bird3.png");
	Texture balconyBigTex = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets2/obstacles/houses/balcony.png");
	Texture balconySmallTex = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets2/obstacles/houses/balcony2.png");
	Texture squirrel1 = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets2/obstacles/squirrels/SQ1.png");
	Texture squirrel2 = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets2/obstacles/squirrels/SQ2.png");
	Texture squirrel3 = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets2/obstacles/squirrels/SQ3.png");
	Texture squirrel4 = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets2/obstacles/squirrels/SQ4.png");
	Texture throwerTex = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets2/obstacles/thrower/thrower.png");
	Texture blade1 = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets2/obstacles/blade/1.png");
	Texture blade2 = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets2/obstacles/blade/2.png");
	Texture blade3 = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets2/obstacles/blade/3.png");
	Texture blade4 = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets2/obstacles/blade/4.png");
	Texture ninjaFall1 = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets2/falling(emtiyazi)/falling1.png");
	Texture ninjaFall2 = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets2/falling(emtiyazi)/falling2.png");
	Texture ninjaFall3 = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets2/falling(emtiyazi)/falling3.png");
	Font* font = SBDL::loadFont("Azuki Regular.ttf", 24);
	Sound* fallSound = SBDL::loadSound("E:/Uni Mini Project/ConsoleApplication2/assets2/sound/fall_1.wav");
	Sound* jumpsound = SBDL::loadSound("E:/Uni Mini Project/ConsoleApplication2/assets2/sound/jump.wav");
	Music* musicMenu = SBDL::loadMusic("E:/Uni Mini Project/ConsoleApplication2/assets2/sound/music.mp3");
	
	//menu Textures
	bool onMenu = true;
	SDL_Rect menuRect = { 0,0,400,600 };
	Texture menutex = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets2/background/back.jpg");
	SDL_Rect playbutton = { 60,280,150,140 };
	Texture playbuttontex = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets2/menu/PLAYBTN.png");
	SDL_Rect exitRect = { 290,500,90,50 };
	Texture exitbuttonTex = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets2/menu/QUITBTN.png");
	SDL_Rect musicOffRect = { 300,410,70,70 };
	Texture musicOffTex = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets2/menu/sound_btn.png");
	Texture musicIsOff = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets2/menu/off_slash.png");

	//game-over Texture
	bool gameOver = false;
	SDL_Rect gameOverRec = { 0,0,400,600 };
	Texture gameOvertex = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets2/menu/gameover_panel.png");
	SDL_Rect replayRec = { 90,390,40,40 };
	Texture replayButton = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets2/menu/again.png");
	SDL_Rect endRec = { 44,290,310,50 };
	Texture endButton = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication1/Debug/assets2/SpriteAtlasTexture_2048x1024_fmt13.png");
	SDL_Rect gotoMenuRec = { 250,390,50,50 };
	Texture gotoMenuTex = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets2/menu/home.png");
	SDL_Rect scoreNUmRec = { 150,50,100,50 };
	SDL_Rect distanceNUmRec = { 120,145,170,50 };
	SDL_Rect exitRec2 = { 150,450,90,50 };

	//pause
	bool pause = false;
	SDL_Rect resumeBackground = { 0,0,400,600 };
	Texture resumeBackgroundTex = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets2/menu/PAUSEMENU.png");
	SDL_Rect resumeButton = { 90,210,220,100 };
	Texture resumeButtonTex = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication2/assets2/menu/generic_scroll_btn.png");
	Texture resumeButtonWord = SBDL::createFontTexture(font, "RESUME", 0, 0, 0);
	SDL_Rect resumeButtonRect = { 100,220,200,80 };
	Texture pausebuttonBackTex = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication1/Debug/assets2/img/back.png");
	Texture pausebuttonTex = SBDL::loadTexture("E:/Uni Mini Project/ConsoleApplication1/Debug/assets2/img/pauseSign.png");

	SBDL::playMusic(musicMenu, -1);

 	while (SBDL::isRunning())
	{
		SBDL::updateEvents();
		SBDL::clearRenderScreen();

		if (score > highscore)
		{
			highscore = score;
			fstream file("highscore.txt", ios::out);
			file << highscore << endl;
			file.close();
		}

		//if the PLAY button is hit
		if (SBDL::mouseInRect(playbutton) && SBDL::Mouse.clicked())
		{
			onMenu = false;
		}
		//the main-menu
		if (onMenu)
		{
			SBDL::showTexture(menutex, menuRect);
			SBDL::showTexture(playbuttontex, playbutton);
			SBDL::showTexture(exitbuttonTex, exitRect);
			SBDL::showTexture(musicOffTex, musicOffRect);
			if (SBDL::mouseInRect(exitRect) && SBDL::Mouse.clicked())
			{
				SBDL::stop();
			}
			if (SBDL::mouseInRect(musicOffRect) && SBDL::Mouse.clicked())
			{
				if (musicOn)
				{
					musicOn = false;
					SBDL::stopMusic();
				}
				else
				{
					SBDL::playMusic(musicMenu, -1);
					musicOn = true;
				}
			}
			if (!musicOn)
			{
				SBDL::showTexture(musicIsOff, musicOffRect);
			}
			

			if (SBDL::mouseInRect(playbutton) && SBDL::Mouse.clicked())
			{
				onMenu = false;
			}
			for (int i = 0, y = 0; i < 2; i++, y -= 600)
			{
				backGround[i] = { 0,y,400,600 };
			}
			ninjaRect.x = 327;
			ninjaRect.y = 440;
			birdRect.x = 40;
			birdRect.y = 90;
			for (int i = 0, y = -700; i < 1; i++, y -= (rand() % 1000) + 1000)
			{
				balconyBig[i] = { 40,y,170,95 };
			}
			for (int i = 0, y = -200; i < 1; i++, y -= (rand() % 1200) + 1200)
			{
				balconySmall[i] = { 40,y,100,50 };
			}
			for (int i = 0, y = -440; i < 1; i++, y -= (rand() % 1200) + 1200)
			{
				spikeRect[i] = { 327,y,50,120 };
			}
			for (int i = 0, y = -950; i < 1; i++, y -= 600)
			{
				throwerRect[i] = { 25,y,60,50 };
			}
			Rope = { 35,-10,330,60 };
			squirrelRec.x = 40;
			squirrelRec.y = Rope.y;
			bladeRect.x = 30;
			bladeRect.y = 150;
			shieldRect.x = 327;
			shieldRect.y = -800;

			frameCount = 0;
			inAir = false;
			whichWall = true;
			bird = true;
			squirrel = true;
			ninjaFall = false;
			blade = false;
			birdCount = 0;
			spike = true;
			ninjaCounter = 0;
			ninjump = 15;
			shield = false;
			bubbleAvailable = true;
			SBDL::updateRenderScreen();
			SBDL::delay(30);
			continue;
		}

		Texture scoreNum = SBDL::createFontTexture(font, "score:" + to_string(scoreSave), 0, 0, 200);
		Texture dostanceNum = SBDL::createFontTexture(font, "highScore:" + to_string(highscore), 0, 0, 200);

		
		//game-over menu
		if (gameOver)
		{
			SBDL::showTexture(gameOvertex, gameOverRec);
			SBDL::showTexture(replayButton, replayRec);
			SBDL::showTexture(endButton, endRec);
			SBDL::showTexture(gotoMenuTex, gotoMenuRec);
			SBDL::showTexture(scoreNum, scoreNUmRec);
			SBDL::showTexture(dostanceNum, distanceNUmRec);
			SBDL::showTexture(exitbuttonTex, exitRec2);
			SBDL::showTexture(exitbuttonTex, exitRec2);
			if (SBDL::mouseInRect(exitRec2) && SBDL::Mouse.clicked())
			{
				SBDL::stop();
			}
			if (SBDL::mouseInRect(gotoMenuRec) && SBDL::Mouse.clicked())
			{
				onMenu = true;
				gameOver = false;
			}
			if (SBDL::mouseInRect(replayRec) && SBDL::Mouse.clicked())
			{
				gameOver = false;
				for (int i = 0, y = 0; i < 2; i++, y -= 600)
				{
					backGround[i] = { 0,y,400,600 };
				}
				ninjaRect.x = 327;
				ninjaRect.y = 440;
				birdRect.x = 40;
				birdRect.y = 90;
				for (int i = 0, y = -700; i < 1; i++, y -= (rand() % 1000) + 1000)
				{
					balconyBig[i] = { 40,y,170,95 };
				}
				for (int i = 0, y = -200; i < 1; i++, y -= (rand() % 1200) + 1200)
				{
					balconySmall[i] = { 40,y,100,50 };
				}
				for (int i = 0, y = -440; i < 1; i++, y -= (rand() % 1200) + 1200)
				{
					spikeRect[i] = { 327,y,50,120 };
				}
				for (int i = 0, y = -950; i < 1; i++, y -= 600)
				{
					throwerRect[i] = { 25,y,60,50 };
				}
				Rope = { 35,-10,330,60 };
				squirrelRec.x = 40;
				squirrelRec.y = Rope.y;
				bladeRect.x = 30;
				bladeRect.y = 150;
				shieldRect.x = 327;
				shieldRect.y = -800;
			
				frameCount = 0;
				score = 0;
				inAir = false;
				whichWall = true;
				bird = true;
				squirrel = true;
				ninjaFall = false;
				blade = false;
				birdCount = 0;
				spike = true;
				ninjaCounter = 0;
				ninjump = 15;
				shield = false;
				bubbleAvailable = true;
			}
			SBDL::updateRenderScreen();
			SBDL::delay(30);
			continue;
		}

		if (SBDL::keyPressed(SDL_SCANCODE_P))
		{
			pause = true;
		}

		//paused
		if (pause)
		{
			SBDL::showTexture(resumeBackgroundTex, resumeBackground);
			SBDL::showTexture(resumeButtonTex, resumeButton);
			SBDL::showTexture(resumeButtonWord, resumeButtonRect);
			SBDL::showTexture(replayButton, replayRec);
			SBDL::showTexture(gotoMenuTex, gotoMenuRec);
			if (SBDL::mouseInRect(resumeButton) && SBDL::Mouse.clicked())
			{
				pause = false;
			}
			if (SBDL::mouseInRect(gotoMenuRec) && SBDL::Mouse.clicked())
			{
				onMenu = true;
				pause = false;
			}
			if (SBDL::mouseInRect(replayRec) && SBDL::Mouse.clicked())
			{
				pause = false;
				for (int i = 0, y = 0; i < 2; i++, y -= 600)
				{
					backGround[i] = { 0,y,400,600 };
				}
				ninjaRect.x = 327;
				ninjaRect.y = 440;
				birdRect.x = 40;
				birdRect.y = 90;
				for (int i = 0, y = -700; i < 1; i++, y -= (rand() % 1000) + 1000)
				{
					balconyBig[i] = { 40,y,170,95 };
				}
				for (int i = 0, y = -200; i < 1; i++, y -= (rand() % 1200) + 1200)
				{
					balconySmall[i] = { 40,y,100,50 };
				}
				for (int i = 0, y = -440; i < 1; i++, y -= (rand() % 1200) + 1200)
				{
					spikeRect[i] = { 327,y,50,120 };
				}
				for (int i = 0, y = -950; i < 1; i++, y -= 600)
				{
					throwerRect[i] = { 25,y,60,50 };
				}
				Rope = { 35,-10,330,60 };
				squirrelRec.x = 40;
				squirrelRec.y = Rope.y;
				bladeRect.x = 30;
				bladeRect.y = 150;
				shieldRect.x = 327;
				shieldRect.y = -800;

				frameCount = 0;
				score = 0;
				inAir = false;
				whichWall = true;
				bird = true;
				squirrel = true;
				ninjaFall = false;
				blade = false;
				birdCount = 0;
				spike = true;
				ninjaCounter = 0;
				ninjump = 15;
				shield = false;
				bubbleAvailable = true;
			}
			SBDL::updateRenderScreen();
			SBDL::delay(30);
			continue;
		}

		//showing background
		for (int i = 0; i < 2; i++)
		{
			SBDL::showTexture(backGroundTex, backGround[i]);
			backGround[i].y += move;
			if (backGround[i].y >= 600)
				backGround[i].y = -600;
		}
		//showing big balcony
		for (int i = 0; i < 1; i++)
		{
			SBDL::showTexture(balconyBigTex, balconyBig[i]);
			balconyBig[i].y += move;
			if (balconyBig[i].y >= 1200)
				balconyBig[i].y = -900-((rand()%600)+100);
		}
		//big balcony intersection
		for (int i = 0; i < 1; i++)
		{
			if (SBDL::hasIntersectionRect(ninjaRect, balconyBig[i]))
			{
				if (!inAir && !shield)
				{
					ninjaFall = true;
					//gameOver = true;
					//should go to game-over menu
				}
				else if (!inAir && shield)
				{
					shield = false;
					shieldRect.x = 1000;
					balconyBig->y = -800;
				}
			}
		}
		//showing small balcony
		for (int i = 0; i < 1; i++)
		{
			SBDL::showTexture(balconySmallTex, balconySmall[i]);
			balconySmall[i].y += move;
			if (balconySmall[i].y >= 1000)
				balconySmall[i].y = -300-((rand()%600)+10);
		}
		for (int i = 0; i < 1; i++)
		{
			if (SBDL::hasIntersectionRect(ninjaRect, balconySmall[i]))
			{
				if (!inAir && !shield)
				{
					ninjaFall = true;
					//gameOver = true;
					//should go to game-over menu
				}
				else if (!inAir && shield)
				{
					shield = false;
					shieldRect.x = 1000;
					balconySmall->y = -500;
				}
			}
		}
		//showing the birds
		if (bird)
		{
			if (birdCount < 25)
			{
				if (frameCount % 12 < 4)
					SBDL::showTexture(bird1, birdRect);
				else if (frameCount % 12 < 8)
					SBDL::showTexture(bird2, birdRect);
				else if (frameCount % 12 < 12)
					SBDL::showTexture(bird3, birdRect);
			}
			else
			{
				if (frameCount % 12 < 4)
					SBDL::showTexture(bird1, birdRect);
				else if (frameCount % 12 < 8)
					SBDL::showTexture(bird2, birdRect);
				else if (frameCount % 12 < 12)
					SBDL::showTexture(bird3, birdRect);
				birdRect.x += 15;
				birdRect.y += 20;
			}
		}
		if (birdRect.y>(rand()%800)+5000)
		{
			birdCount = 0;
			birdRect.y = 85;
			birdRect.x = 40;
		}
		birdCount++;
		//bird intersection
		if (SBDL::hasIntersectionRect(ninjaRect, birdRect))
		{
			if (inAir && bird)
			{
				birdRect.x = 500;
				score += 10;
			}
			else if (!inAir && bird && !shield)
			{
				ninjaFall = true;
			}
			else if (!inAir && bird && shield)
			{
				shield = false;
				shieldRect.x = 1000;
				birdRect.y = -600;
			}
		}
		//showig spikes
		if (spike)
		{
			for (int i = 0; i < 1; i++)
			{
				SBDL::showTexture(spikeTex, spikeRect[i]);
				spikeRect[i].y += move;
				if (spikeRect[i].y >= 2000)
					spikeRect[i].y = -800 - ((rand() % 240) + 800);
			}
		}
		//spike intersection
		for (int i = 0; i < 1; i++)
		{
			if (SBDL::hasIntersectionRect(ninjaRect, spikeRect[i]))
			{
				if (!shield)
				{
					ninjaFall = true;
				}
				else 
				{
					shield = false;
					shieldRect.x = 1000;
					spikeRect->y = -700;
				}
			}
		}
		//showing the ropes
			SBDL::showTexture(RopeTex, Rope);
			Rope.y += move;
			if (Rope.y >= 1000)
				Rope.y = -700 - ((rand() % 500) + 600);

		//showing the squirrels
		if (squirrel)
		{
			if (frameCount % 16 < 4)
				SBDL::showTexture(squirrel1, squirrelRec);
			else if (frameCount % 16 < 8)
				SBDL::showTexture(squirrel2, squirrelRec);
			else if (frameCount % 16 < 12)
				SBDL::showTexture(squirrel3, squirrelRec);
			else if (frameCount % 16 < 16)
				SBDL::showTexture(squirrel4, squirrelRec);
			squirrelRec.y += move;
			if (squirrelRec.y >= 335)
			{	
				squirrelRec.x += 10;	
			}
			if (squirrelRec.x >= 327)
				squirrel = false;
		}
		//to hsow squirrel on other ropes throughout the game 
		if (Rope.y == 0)
		{
			squirrelRec.x = 40;
			squirrelRec.y = Rope.y; 
			squirrel = true;
		}

		//squirrel intersection
		if (SBDL::hasIntersectionRect(ninjaRect, squirrelRec))
		{
			if (inAir && squirrel)
			{
				squirrel = false;
				score += 10;
			}
			else if (!inAir && squirrel && !shield)
			{
				ninjaFall = true;
				gameOver = true;
			}
			else if (!inAir && squirrel && shield)
			{
				shield = false;
				shieldRect.x = 1000;
				squirrelRec.y = -500;
			}
		}

		//showing the throwers
		for (int i = 0; i < 1; i++)
		{
			SBDL::showTexture(throwerTex, throwerRect[i]);
			throwerRect[i].y += move;
			if (throwerRect[i].y >= 150)
				blade = true;
			if (throwerRect[i].y > 5700)
				throwerRect[i].y = -600-((rand()%700)+50);
		}
		//thrower intersection
		for (int i = 0; i < 1; i++)
		{
			if (SBDL::hasIntersectionRect(ninjaRect, throwerRect[i]))
			{
				if (!inAir && !shield)
				{
					ninjaFall = true;
					gameOver = true;
				}
				else if (!inAir && shield)
				{
					shield = false;
					shieldRect.x = 1000;
					throwerRect->y = -500;
				}
			}
		}
		//showing blades thrown by the thrower
		if (blade)
		{
			if (throwerRect->y >= 150)
			{
				if (frameCount % 16 < 4)
					SBDL::showTexture(blade1, bladeRect);
				else if (frameCount % 16 < 8)
					SBDL::showTexture(blade2, bladeRect);
				else if (frameCount % 16 < 12)
					SBDL::showTexture(blade3, bladeRect);
				else if (frameCount % 16 < 16)
					SBDL::showTexture(blade4, bladeRect);
				bladeRect.x += 10;
				bladeRect.y += 10;
				if (bladeRect.x >= 327)
					blade = false;
			}
		}
		//rethrowing the blade
		if (throwerRect->y == 150)
		{
			bladeRect.y = 150;
			bladeRect.x = 30;
			blade = true;
		}
		//blade intersection
		if (SBDL::hasIntersectionRect(ninjaRect,bladeRect))
		{
			if (!inAir && blade && !shield)
			{
				ninjaFall = true;
				gameOver = true;
			}
			else if (inAir && blade)
				blade = false;
			else if (!inAir && blade && shield)
			{
				shield = false;
				shieldRect.x = 1000;
				bladeRect.y = -500;
			}
		}
		//showing shield
		if (bubbleAvailable)
		{
			SBDL::showTexture(shieldTex, shieldRect);
			shieldRect.y += move;
			if (shieldRect.y > 800)
			{
				shieldRect.y = -999 - ((rand() % 600) + 1000);
			}
		}
		//intersection with the shield
		if (SBDL::hasIntersectionRect(ninjaRect, shieldRect))
		{
			shield = true;
			bubbleAvailable = false;
		}
		if (!shield)
			bubbleAvailable = true;

		score++;
	
		//run and jump
		if (!inAir)
		{
			if (whichWall)
			{
				if (!shield)
				{
					ninjaRect.x = 320;
					if (frameCount % 12 < 4)
						SBDL::showTexture(ninjaTexR1, ninjaRect);
					else if (frameCount % 12 < 8)
						SBDL::showTexture(ninjaTexR2, ninjaRect);
					else if (frameCount % 12 < 12)
						SBDL::showTexture(ninjaTexR3, ninjaRect);
				}
				else if(shield)
				{
					ninjaRect.w = 45;
					ninjaRect.x = 320;
					if (frameCount % 12 < 4)
					{
						SBDL::showTexture(shieldTex, ninjaRect);
						SBDL::showTexture(ninjaTexR1, ninjaRect);
						
					}
					else if (frameCount % 12 < 8)
					{
						SBDL::showTexture(shieldTex, ninjaRect);
						SBDL::showTexture(ninjaTexR2, ninjaRect);
						
					}
					else if (frameCount % 12 < 12)
					{
						SBDL::showTexture(shieldTex, ninjaRect);
						SBDL::showTexture(ninjaTexR3, ninjaRect);
						
					}
				}
			}
			else
			{
				if (!shield)
				{
					ninjaRect.x = 40;
					if (frameCount % 12 < 4)
						SBDL::showTexture(ninjaTexL1, ninjaRect);
					else if (frameCount % 12 < 8)
						SBDL::showTexture(ninjaTexL2, ninjaRect);
					else if (frameCount % 12 < 12)
						SBDL::showTexture(ninjaTexL3, ninjaRect);
				}
				else if(shield)
				{
					ninjaRect.w = 45;
					ninjaRect.x=40;
					if (frameCount % 12 < 4)
					{
						SBDL::showTexture(shieldTex, ninjaRect);
						SBDL::showTexture(ninjaTexL1, ninjaRect);
					}
					else if (frameCount % 12 < 8)
					{
						SBDL::showTexture(shieldTex, ninjaRect);
						SBDL::showTexture(ninjaTexL2, ninjaRect);
					}
					else if (frameCount % 12 < 12)
					{
						SBDL::showTexture(shieldTex, ninjaRect);
						SBDL::showTexture(ninjaTexL3, ninjaRect);
					}
				}
			}
		}
		else
		{
			if (whichWall)
				ninjaRect.x -= ninjump;
			else
				ninjaRect.x += ninjump;

			if (!shield)
			{
				if (frameCount % 16 < 4)
					SBDL::showTexture(jumpTex1, ninjaRect);
				else if (frameCount % 16 < 8)
					SBDL::showTexture(jumpTex2, ninjaRect);
				else if (frameCount % 16 < 12)
					SBDL::showTexture(jumpTex3, ninjaRect);
				else if (frameCount % 16 < 16)
					SBDL::showTexture(jumpTex4, ninjaRect);
			}
			else if(shield)
			{
				ninjaRect.w = 45;
				if (frameCount % 16 < 4)
				{
					SBDL::showTexture(shieldTex, ninjaRect);
					SBDL::showTexture(jumpTex1, ninjaRect);
				}
				else if (frameCount % 16 < 8)
				{
					SBDL::showTexture(shieldTex, ninjaRect);
					SBDL::showTexture(jumpTex2, ninjaRect);
				}
				else if (frameCount % 16 < 12)
				{
					SBDL::showTexture(shieldTex, ninjaRect);
					SBDL::showTexture(jumpTex3, ninjaRect);
				}
				else if (frameCount % 16 < 16)
				{
					SBDL::showTexture(shieldTex, ninjaRect);
					SBDL::showTexture(jumpTex4, ninjaRect);
				}
			}
		}
		if (SBDL::keyPressed(SDL_SCANCODE_SPACE))
		{
			SBDL::playSound(jumpsound,1);
			inAir = true;
		}
		if (inAir && whichWall && ninjaRect.x < 40)
		{
			whichWall=false;
			inAir = false;
		}
		if (inAir && !whichWall && ninjaRect.x > 327)
		{
			whichWall = true;
			inAir = false;
		}
		frameCount++;
		//showing ninjaFalling
		if (ninjaFall)
		{
			SBDL::playSound(fallSound, 1);
			ninjaCounter++;
			if (frameCount % 12 < 4)
				SBDL::showTexture(ninjaFall1, ninjaRect);
			else if (frameCount % 12 < 8)
				SBDL::showTexture(ninjaFall2, ninjaRect);
			else if (frameCount % 12 < 12)
				SBDL::showTexture(ninjaFall3, ninjaRect);
			ninjaRect.y += 10;
			if (ninjaCounter > 20)
			{
				gameOver = true;
				scoreSave = score;
			}
		}

		SBDL::updateRenderScreen(); 
		SBDL::delay(30);
	}
}