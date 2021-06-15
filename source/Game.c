#include "Game.h"

static Vector2f selectionPos[2] = {(Vector2f){105, 45}, (Vector2f){101.25f, 52}};

Game InitGame(Game g) {
    romfsInit();
    gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
    //consoleInit(GFX_BOTTOM, NULL);

    srand((unsigned)time(NULL));

    //g.top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    //g.bot = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

    {
        Game t = {_main, C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT), C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT), malloc(sizeof(Player)),
                malloc(sizeof(Bullet)), calloc(ENEMY_SIZE, sizeof(Enemy)), malloc(sizeof(Button)), malloc(sizeof(Button)),
                malloc(sizeof(Button)), malloc(sizeof(Button)), malloc(sizeof(Button)), malloc(sizeof(Button))};

        g = t;
    }

    g.firstTime = 1;


    g.font = C2D_FontLoad("romfs:/gfx/FFFFORWA.bcfnt");
    if (!g.font) { svcBreak(USERBREAK_PANIC); DeInitGame(g); exit(0); }

    g.static_textBuf  = C2D_TextBufNew(4096);
    g.dynamic_textBuf = C2D_TextBufNew(4096);

    C2D_TextFontParse(&g.texts[0], g.font, g.static_textBuf, "Shooter Game");
    C2D_TextFontParse(&g.texts[1], g.font, g.static_textBuf, "By Derrick Wilder");
    C2D_TextFontParse(&g.texts[2], g.font, g.static_textBuf, "Credits");
    C2D_TextFontParse(&g.texts[3], g.font, g.static_textBuf, "This Game Was An Inspiration To\n"
        "A Game That I Made When I Started Out\n"
        "Making Games In Unity When I Was New.\n"
        "I Recreated This Game In Citro2D And C\n"
        "With No Other Libraries.");

    C2D_TextFontParse(&g.texts[4], g.font, g.static_textBuf, "Press L Or R To Start\n\n\n\n\n\n\n\n\nUse The D Pad Or The C Stick To Move");
    C2D_TextFontParse(&g.texts[5], g.font, g.static_textBuf, "Game Over");
    

    g.startGame = InitButton(g.startGame, "Start", C2D_Color32(0x33, 0x50, 0xFF, 0xFF),
                    SetVector2f(110, 50), SetVector2f(75, 25), 0.375f, g.font, g.static_textBuf);

    g.pauseGame = InitButton(g.pauseGame, "Pause", C2D_Color32(0x33, 0x50, 0xFF, 0xFF),
                    SetVector2f(SCREEN_SIZE.x / 2 - (75+18.75f), SCREEN_SIZE.y / 2 - 12.5f), SetVector2f(90, 40), 0.5f, g.font, g.static_textBuf);

    g.credits = InitButton(g.credits, "Credits", C2D_Color32(0x33, 0x50, 0xFF, 0xFF),
                    SetVector2f(110, 100), SetVector2f(75, 25), 0.375f, g.font, g.static_textBuf);

    g.back = InitButton(g.back, "Back", C2D_Color32(0x33, 0x50, 0xFF, 0xFF),
                    SetVector2f(SCREEN_SIZE.x / 2 - (75+18.75f), SCREEN_SIZE.y / 2 - 12.5f), SetVector2f(90, 40), 0.5f, g.font, g.static_textBuf);

    g.restart = InitButton(g.restart, "Restart", C2D_Color32(0x33, 0x50, 0xFF, 0xFF),
                    SetVector2f(SCREEN_SIZE.x / 2 - (75+18.75f), 57.5f), SetVector2f(90, 40), 0.5f, g.font, g.static_textBuf);

    g.endGame = InitButton(g.endGame, "Exit", C2D_Color32(0x33, 0x50, 0xFF, 0xFF),
                    SetVector2f(110, 150), SetVector2f(75, 25), 0.375f, g.font, g.static_textBuf);

    int i;

    for (i = 0; i < 6; i++) C2D_TextOptimize (&g.texts[i]);

    {
		Vector2f pos[3] = {
			SetVector2f(200 / 1.375f + 50, 110 / 1.375f + 25),
			SetVector2f(188 / 1.375f + 50, 135 / 1.375f + 25),
			SetVector2f(213 / 1.375f + 50, 135 / 1.375f + 25)
		};

		g.pl = InitPlayer(g.pl, pos, DEGTORAD(90),  C2D_Color32(0x3A, 0x59, 0xE0, 0xFF), 3);

		pos[0].y += 12.5f/2;
		pos[1].x -= 12.5f/2;
		pos[2].x += 12.5f/2;

		for (i = 0; i < 3; i++) pos[i].x -= 75;

		for (i = 0; i < ENEMY_SIZE; i++) {
		    *(g.es + i) = *InitEnemy((g.es + i), pos, DEGTORAD(90),  C2D_Color32(0xE0, 0x3F, 0x3A, 0xFF) );

            (g.es + i)->id = i;

			float randFloat = RANDFLOAT(12.5f);

            for (int j = 0; j < 3; j++) { 
                (g.es + i)->e.pos[j].x += (25 + randFloat) * i;
                (g.es + i)->e.pos[j].y -= (125 + randFloat);
            }
		}
	}

    return g;
}

void StateMainMenu(Game* g) {
    const Vector2f pos = SetVector2f(SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2);

    if (ButtonDown(KEY_UP) &&   selectionPos[0].y > 45)   selectionPos[0].y -= 50;
    if (ButtonDown(KEY_DOWN) && selectionPos[0].y < 145)  selectionPos[0].y += 50;

    // if (ButtonPressed(g->startGame, g->touch)) g->state = _game;
    

    if (ButtonDown(KEY_A | KEY_B | KEY_X | KEY_Y | KEY_START | KEY_SELECT)) {
        switch ((int)selectionPos[0].y) {
            case 45:
                g->state = _game;
                break;
            case 95:
                g->state = _credits;
                break;
            case 145:
                g->state = _exit;
                break;
        }
    }

    Draw(*g, 0, C2D_Color32(0x0D, 0x0D, 0x0D, 0xFF));

        C2D_DrawText (&g->texts[0], C2D_WithColor | C2D_AtBaseline | C2D_AlignCenter, pos.x, pos.y     , 0, 0.75, 0.75,
                        C2D_Color32(0x82, 0x33, 0xFF, 0xFF));

        C2D_DrawText (&g->texts[1], C2D_WithColor | C2D_AtBaseline | C2D_AlignCenter, pos.x, pos.y + 20, 0, 0.375, 0.375, 
                        C2D_Color32(0x62, 0x13, 0xDF, 0xFF));

    Draw(*g, 1, C2D_Color32(0x0A, 0x0A, 0x0A, 0xFF));

        C2D_DrawRectSolid(selectionPos[0].x,  selectionPos[0].y, 0, 85, 35, C2D_Color32(0x82, 0x33, 0xFF, 0xFF));

	    DrawButton(g->startGame, SetVector2f(38, 19));
        DrawButton(g->credits  , SetVector2f(38, 19));
        DrawButton(g->endGame  , SetVector2f(38, 19));

    Clear();
}

void StateCreditsMenu(Game* g) {
    if (ButtonDown(KEY_A | KEY_B | KEY_X | KEY_Y | KEY_START | KEY_SELECT)) g->state = _main;
    

    Draw(*g, 0, C2D_Color32(0x0D, 0x0D, 0x0D, 0xFF));
        C2D_DrawText (&g->texts[2], C2D_WithColor | C2D_AtBaseline | C2D_AlignCenter, SCREEN_SIZE.x / 2, 40, 0, 0.75, 0.75,
                        C2D_Color32(0x82, 0x33, 0xFF, 0xFF));

        C2D_DrawText (&g->texts[3], C2D_WithColor | C2D_AtBaseline | C2D_AlignCenter, SCREEN_SIZE.x / 2 - 5, 90, 0, 0.5, 0.5,
                        C2D_Color32(0x82, 0x33, 0xFF, 0xFF));

    Draw(*g, 1, C2D_Color32(0x0A, 0x0A, 0x0A, 0xFF));  

        C2D_DrawRectSolid(SCREEN_SIZE.x / 2 - (75+18.75f) - 5, SCREEN_SIZE.y / 2 - 17.5f, 0, 100, 50, C2D_Color32(0x82, 0x33, 0xFF, 0xFF));

        DrawButton(g->back, SetVector2f(38 * 1.2f, 19 * 1.5f));

    Clear(); 
}

void StateGame(Game* g) {
    int i;

    if (g->pl->health > 3) g->pl->health = 3;
    
    TeleportPlayer(g->pl, SCREEN_SIZE);
	MovePlayer(g->pl);

    if (g->pl->didMove) {
        if (ButtonDown(KEY_START)) {
            g->back->pos.y = 57.5f;
            g->endGame->size = SetVector2f(90, 40);
            g->endGame->pos.x = SCREEN_SIZE.x / 2 - (75+18.75f);
            g->endGame->textSize = 0.5f;

            g->state = _paused;
        }
        
	    SpawnBullet(g->pl, g->bpl);
	    DestroyBullet(g->pl, g->bpl, SCREEN_SIZE);

	    for (i = 0; i < ENEMY_SIZE; ++i) {
	    	TeleportEnemy( (g->es + i), SCREEN_SIZE);
	    	MoveEnemy( (g->es + i));
	    	RotateEnemy( (g->es + i), g->pl->e);

            if (g->pl->health <= 0) {
                g->back->pos.y = 150.0f;
                g->state = _gameover;
            }


            // Lose Player Health
            if (TriangleOnTriangle(g->pl->e.pos, (g->es + i)->e.pos)) {
                g->pl->health--;
                g->state = _loselife;
            }

            // Move Enemy
            if (TriangleOnTriangle(g->bpl->e.pos, (g->es + i)->e.pos) && !TriangleOnTriangle(g->pl->e.pos, (g->es + i)->e.pos)) {
                g->pl->didShoot = 0;
                g->score += 50;
                MoveHitEnemy((g->es + i));

            }
	    }

        g->firstTime = 0;
    }

    if (g->score > g->highscore) g->highscore = g->score;

    C2D_TextBufClear(g->dynamic_textBuf);

    char buf[160];
	C2D_Text scoreText, highscoreText;

	snprintf(buf, sizeof(buf), "Score: %d", g->score);
	C2D_TextFontParse(&scoreText, g->font, g->dynamic_textBuf, buf);
	C2D_TextOptimize(&scoreText);

    snprintf(buf, sizeof(buf), "HighScore: %d", g->highscore);
	C2D_TextFontParse(&highscoreText, g->font, g->dynamic_textBuf, buf);
	C2D_TextOptimize(&highscoreText);

			
		// Render the scene
	Draw(*g, 0, C2D_Color32(0x0D, 0x0D, 0x0D, 0xFF));

		DrawRotatedTriangle(g->bpl->e, SetVector2f(9.0f, 8), g->bpl->e.angle-DEGTORAD(90), g->bpl->e.color);

		DrawRotatedTriangle(g->pl->e, SetVector2f(9.0f, 8), g->pl->e.angle-DEGTORAD(90), g->pl->e.color);

        const Vector2f pos[3] = {
            SetVector2f(200 / 1.375f - 45, 110 / 1.375f - (135/4)),
			SetVector2f(188 / 1.375f - 45, 135 / 1.375f - (135/4)),
			SetVector2f(213 / 1.375f - 45, 135 / 1.375f - (135/4))
        };


        if (!g->pl->didMove && g->firstTime)
            C2D_DrawText (&g->texts[4], C2D_WithColor | C2D_AtBaseline | C2D_AlignCenter, SCREEN_SIZE.x / 2, 40, 0, 0.5, 0.5,
                            C2D_Color32(0x82, 0x33, 0xFF, 0xFF));

		for (i = 0; i < ENEMY_SIZE; i++)
			DrawRotatedTriangle((g->es + i)->e,
				SetVector2f(16, 5), (g->es + i)->e.angle-DEGTORAD(90), (g->es + i)->e.color);

	Draw(*g, 1, C2D_Color32(0x0A, 0x0A, 0x0A, 0xFF));

        for (int i = 0; i < g->pl->health; i++)
        C2D_DrawTriangle(pos[0].x+(50 * i), pos[0].y, g->pl->e.color, pos[1].x+(50 * i), pos[1].y, g->pl->e.color,
                            pos[2].x+(50 * i), pos[2].y, g->pl->e.color, 0);

        C2D_DrawRectSolid(SCREEN_SIZE.x / 2 - (75+18.75f) - 5, SCREEN_SIZE.y / 2 - 17.5f, 0, 100, 50, C2D_Color32(0x82, 0x33, 0xFF, 0xFF));
        DrawButton(g->pauseGame, SetVector2f(38 * 1.2f, 19 * 1.5f));

	    C2D_DrawText(&scoreText, C2D_AlignCenter | C2D_WithColor | C2D_AtBaseline, 150, 220.0f, 0.5f, 0.5f, 0.5f,
                        C2D_Color32(0x82, 0x33, 0xFF, 0xFF));

        C2D_DrawText(&highscoreText, C2D_AlignCenter | C2D_WithColor | C2D_AtBaseline, 150, 180.0f, 0.5f, 0.5f, 0.5f,
                        C2D_Color32(0x82, 0x33, 0xFF, 0xFF));

	Clear();
}

void StateGameOver(Game* g) {
    int i;

    if (ButtonDown(KEY_UP)   &&   selectionPos[1].y > 52  ) selectionPos[1].y -= 92.5f;
    if (ButtonDown(KEY_DOWN) && selectionPos[1].y < 144.5f) selectionPos[1].y += 92.5f;

    const Vector2f pos = SetVector2f(SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2);

    if (ButtonDown(KEY_A | KEY_B | KEY_X | KEY_Y | KEY_START | KEY_SELECT)) {
        if (selectionPos[1].y == 52) {
            RestartGame(*g);
            
            g->score = 0;
            g->state = _game;
        }

        if (selectionPos[1].y == 144.5f) {
            g->back->pos.y = 107.5f;

            selectionPos[1].y = 52;

            RestartGame(*g);

            g->score = 0;
            g->state = _main;

        }

    }

    if (g->state != _main) {
        Draw(*g, 0, C2D_Color32(0x0D, 0x0D, 0x0D, 0xFF));

	    	DrawRotatedTriangle(g->bpl->e, SetVector2f(9.0f, 8), g->bpl->e.angle-DEGTORAD(90), g->bpl->e.color);

	    	DrawRotatedTriangle(g->pl->e, SetVector2f(9.0f, 8), g->pl->e.angle-DEGTORAD(90), g->pl->e.color);

	    	for (i = 0; i < ENEMY_SIZE; i++)
	    		DrawRotatedTriangle((g->es + i)->e,
	    			SetVector2f(16, 5), (g->es + i)->e.angle-DEGTORAD(90), (g->es + i)->e.color);

            C2D_DrawRectSolid(0, 0, 0, SCREEN_SIZE.x, SCREEN_SIZE.y, C2D_Color32(0x00, 0x00, 0x00, 0xAF));

            C2D_DrawText (&g->texts[5], C2D_WithColor | C2D_AtBaseline | C2D_AlignCenter, pos.x, pos.y, 0, 0.75, 0.75, C2D_Color32(0x82, 0x33, 0xFF, 0xFF));

	    Draw(*g, 1, C2D_Color32(0x0A, 0x0A, 0x0A, 0xFF));
            C2D_DrawRectSolid(selectionPos[1].x, selectionPos[1].y, 0, 100, 50, C2D_Color32(0x82, 0x33, 0xFF, 0xFF));
            DrawButton(g->restart, SetVector2f(38 * 1.2f, 19 * 1.5f));

            DrawButton(g->back, SetVector2f(38 * 1.2f, 19 * 1.5f));

	    Clear();
	}
}

void StatePause(Game* g) {
    int i;

    if (ButtonDown(KEY_UP)   &&   selectionPos[1].y > 52  ) selectionPos[1].y -= 92.5f;
    if (ButtonDown(KEY_DOWN) && selectionPos[1].y < 144.5f) selectionPos[1].y += 92.5f;

    if (ButtonDown(KEY_A | KEY_B | KEY_X | KEY_Y | KEY_START | KEY_SELECT)) {
        if (selectionPos[1].y == 52) 
            g->state = _game;

        if (selectionPos[1].y == 144.5f) {
            g->back->pos.y = 107.5f;
            g->endGame->size = SetVector2f(75, 25);
            g->endGame->pos.x = 110;
            g->endGame->textSize = 0.375f;

            selectionPos[1].y = 52;

            g->state = _restart;

        }

    }

   if (g->state != _restart) {
    	Draw(*g, 0, C2D_Color32(0x0D, 0x0D, 0x0D, 0xFF));

		    DrawRotatedTriangle(g->bpl->e, SetVector2f(9.0f, 8), g->bpl->e.angle-DEGTORAD(90), g->bpl->e.color);

		    DrawRotatedTriangle(g->pl->e, SetVector2f(9.0f, 8), g->pl->e.angle-DEGTORAD(90), g->pl->e.color);

		    for (i = 0; i < ENEMY_SIZE; i++)
		    	DrawRotatedTriangle((g->es + i)->e,
		    		SetVector2f(16, 5), (g->es + i)->e.angle-DEGTORAD(90), (g->es + i)->e.color);

            C2D_DrawRectSolid(0, 0, 0, SCREEN_SIZE.x, SCREEN_SIZE.y, C2D_Color32(0x00, 0x00, 0x00, 0xAF));

	    Draw(*g, 1, C2D_Color32(0x0A, 0x0A, 0x0A, 0xFF));

        	C2D_DrawRectSolid(selectionPos[1].x, selectionPos[1].y, 0, 100, 50, C2D_Color32(0x82, 0x33, 0xFF, 0xFF));
        	DrawButton(g->back, SetVector2f(38 * 1.2f, 19 * 1.5f));

        	DrawButton(g->endGame, SetVector2f(38 * 1.2f, 19 * 1.5f));
        
        

		Clear();
	}
}

Game LoseHealth(Game g) {
    int i;
    {
		Vector2f pos[3] = {
			SetVector2f(200 / 1.375f + 50, 110 / 1.375f + 25),
			SetVector2f(188 / 1.375f + 50, 135 / 1.375f + 25),
			SetVector2f(213 / 1.375f + 50, 135 / 1.375f + 25)
		};
        
        g.pl->deltaPos = SetVector2f(0, 0);

        for (i = 0; i < 3; i++) {
            g.pl->e.pos[i].x = pos[i].x;
            g.pl->e.pos[i].y = pos[i].y;
        }

        g.pl->didMove = 0;
        g.pl->e.angle = DEGTORAD(90);

        g.pl->didShoot = 0;

        for (i = 0; i < 3; i++) {
            g.bpl->e.pos[i].x = g.pl->e.pos[i].x;
            g.bpl->e.pos[i].y = g.pl->e.pos[i].y;
        }

        g.bpl->e.angle = DEGTORAD(90);

        pos[0].y += 12.5f/2;
		pos[1].x -= 12.5f/2;
		pos[2].x += 12.5f/2;

		for (i = 0; i < 3; i++) pos[i].x -= 75;

		for (i = 0; i < ENEMY_SIZE; i++) {
            *(g.es + i) = *InitEnemy((g.es + i), pos, DEGTORAD(90),  C2D_Color32(0xE0, 0x3F, 0x3A, 0xFF) );

			float randFloat = RANDFLOAT(12.5f);

			for (int j = 0; j < 3; j++) { 
                (g.es + i)->e.pos[j].x += (25 + randFloat) * i;
                (g.es + i)->e.pos[j].y -= (125 + randFloat);
            }

		}
	}

    g.state = _game;

    return g;
}

Game RestartGame(Game g) {
    int i;

    {
		Vector2f pos[3] = {
			SetVector2f(200 / 1.375f + 50, 110 / 1.375f + 25),
			SetVector2f(188 / 1.375f + 50, 135 / 1.375f + 25),
			SetVector2f(213 / 1.375f + 50, 135 / 1.375f + 25)
		};

		g.pl = InitPlayer(g.pl, pos, DEGTORAD(90),  C2D_Color32(0x3A, 0x59, 0xE0, 0xFF), 3);
        g.pl->deltaPos = SetVector2f(0, 0);

        g.pl->didShoot = 0;

        for (i = 0; i < 3; i++) {
            g.bpl->e.pos[i].x = g.pl->e.pos[i].x;
            g.bpl->e.pos[i].y = g.pl->e.pos[i].y;
        }

        g.bpl->e.angle = DEGTORAD(90);

		pos[0].y += 12.5f/2;
		pos[1].x -= 12.5f/2;
		pos[2].x += 12.5f/2;

		for (i = 0; i < 3; i++) pos[i].x -= 75;

		for (i = 0; i < ENEMY_SIZE; i++) {
			*(g.es + i) = *InitEnemy((g.es + i), pos, DEGTORAD(90),  C2D_Color32(0xE0, 0x3F, 0x3A, 0xFF) );

			float randFloat = RANDFLOAT(12.5f);

			for (int j = 0; j < 3; j++) { 
                (g.es + i)->e.pos[j].x += (25 + randFloat) * i;
                (g.es + i)->e.pos[j].y -= (125 + randFloat);
            }
            
		}
	}

    return g;
    
}

void Input(Game* g) {
    hidScanInput();
    hidTouchRead(&g->touch);
}

u32 ButtonUp  (int input) { return hidKeysUp()   & input; };
u32 ButtonDown(int input) { return hidKeysDown() & input; };
u32 ButtonHeld(int input) { return hidKeysHeld() & input; };

void Draw(Game g, int side, u32 clrClear) {
    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear((side == 0) ? g.top : g.bot, clrClear);
	C2D_SceneBegin((side == 0) ? g.top : g.bot);
}

void Clear() {
    C3D_FrameEnd(0);
}

void DeInitGame(Game g) {
    free(g.es);
	g.es = NULL;

	free(g.pl);
	g.pl = NULL;

    free(g.bpl);
    g.bpl = NULL;

    C2D_FontFree(g.font);
    C2D_TextBufDelete(g.static_textBuf);

    svcBreak(USERBREAK_PANIC);

    C2D_Fini();
	C3D_Fini();
	gfxExit();
}
