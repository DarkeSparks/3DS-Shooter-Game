#ifndef GAME_H
#define GAME_H

#include <3ds.h>
#include <citro2d.h>

#include <stdlib.h>

#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "Math.h"
#include "Rotated.h"

#include "Button.h" 

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

#define ENEMY_SIZE 10

#define SCREEN_SIZE SetVector2f(400, 240)

typedef struct Game {
    enum GameState {
        _main = 0, _game, _restart, _gameover, _loselife, _credits, _paused, _exitGame
    } state;

    C3D_RenderTarget* top;
	C3D_RenderTarget* bot;

    struct Player* pl;
	struct Bullet* bpl;
	struct Enemy*  es;

    struct Button* startGame;
    struct Button* credits;
    struct Button* endGame;

    struct Button* back;

    struct Button* restart;

    struct Button* pauseGame;
    
    touchPosition touch;

    unsigned short firstTime : 1;
    unsigned short score, highscore;

    C2D_Font font;
    C2D_TextBuf  static_textBuf;
    C2D_TextBuf dynamic_textBuf;
    C2D_Text texts[10];
} Game;

Game InitGame(Game g);

void StateMainMenu(Game* g);
void StateCreditsMenu(Game* g);
void StateGame(Game* g);
void StateGameOver(Game* g);
void StatePause(Game* g);

Game LoseHealth(Game g);
Game RestartGame(Game g);

void Input(Game* g);

u32   ButtonUp(int input);
u32 ButtonDown(int input);
u32 ButtonHeld(int input);


void Draw(Game g, int side, u32 clrClear);
void Clear();

void DeInitGame(Game g);

#endif