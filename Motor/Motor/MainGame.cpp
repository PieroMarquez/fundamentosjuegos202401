#include "MainGame.h"
#include "Sprite.h"

MainGame::MainGame() : initTime(0), spriteInitialized{ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false }
{
	window = NULL;
	width = 1920;
	height = 1080;
	gameState = GameState::PLAY;

}

void MainGame::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = new Window();
	window->create("Motor WD2M", width, height, 0);

	initShaders();
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	init();
	sprite.init(-1,-1,1,1, "images/solaire.png");
	update();
}

void MainGame::draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program.use();
	GLuint timeLocation = program.getUniformLocation("time");
	glUniform1f(timeLocation, time);
	time += 0.02;
	for (int i = 0; i < 15; i++) {
		if (spriteInitialized[i]) {
			sprites[i].draw();
		}
	}
	sprite.draw();
	program.unuse();
	window->swapWindow();

}
float MainGame::randomCoordinated()
{
	float random_num = (float)rand();
	random_num /= RAND_MAX;
	random_num = random_num * 2.0 - 1.0;
	return random_num;
}
void MainGame::update()
{
	while (gameState != GameState::EXIT) {
		processInput();
		Uint32 currentTime = SDL_GetTicks();
		for (int i = 0; i < 15; i++) {
			if (!spriteInitialized[i] && currentTime - initTime > 2000 * (i + 1)) {
				sprites[i].init(randomCoordinated(), randomCoordinated(), 1, 1, "images/solaire.png");
				spriteInitialized[i] = true;
			}
		}
		draw();
	}
}
void MainGame::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)){
		switch (event.type) {
		case SDL_QUIT:
			gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			cout << " Posicion en X " << event.motion.x 
			<< " Posicion en Y " << event.motion.y << endl;
			break;
		}
	}
}
void MainGame::initShaders()
{
	program.compileShaders("Shaders/colorShaderVert.txt", "Shaders/colorShaderFrag.txt");
	program.addAtribute("vertexPoistion");
	program.addAtribute("vertexColor");
	program.addAtribute("vertexUV");
	program.linkShader();

}
