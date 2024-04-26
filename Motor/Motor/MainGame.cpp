#include "MainGame.h"
#include "Sprite.h"
MainGame::MainGame()
{
	window = NULL;
	width = 1920;
	height = 1080;
	gameState = GameState::PLAY;
	time = 0.0f;
}

void MainGame::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("nombre_ventana_xd", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	//es valida si hubo un error
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		//falta validar el estado del glew
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
	initShaders();
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	init();
	// Inicializa el primer rectángulo
	numSprites = 1;  // Inicializa con un sprite
	sprites[0].init(-1, -1, 1, 1);
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
	// Dibuja todos los rectángulos
	for (auto& sprite : sprites) {
		sprite.draw();
	}
	program.unuse();
	SDL_GL_SwapWindow(window);
}

void MainGame::update()
{
	while (gameState != GameState::EXIT) {
		// Si han pasado más de X segundos, actualiza los sprites existentes
		if (time > 10.0f) {
			for (int i = 0; i < numSprites; ++i) {
				float x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
				float y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
				sprites[i].init(x, y, 1, 1);
			}
			time = 0.0f; // Reinicia el contador de tiempo
		}
		draw();
		processInput();
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

	program.linkShader();

}
