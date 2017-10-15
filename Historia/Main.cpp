#include "GL_Helpers.h"
#include "Playground.h"
#include "Super_Bible_Chapter_1.h"
#include "Super_Bible_Chapter_5.h"
#include "Super_Bible_Chapter_5_Textures.h"
#include "Learn_OpenGL_Transformations.h"
#include "Learn_OpenGL_Lighting.h"

#include "InputManager.h"

#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>
/*
Forward Declarations
*/

bool init();
bool initGL();
void close();
void render();
void update();
/*
Main Variables
*/
GLfloat currentTime;
GLuint WINDOW_WIDTH;
GLuint WINDOW_HEIGHT;
SDL_Window* gWindow = NULL;
SDL_GLContext gContext;
Tutorial* currentTutorial;
InputManager* inputManager;

bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL Could not be initialized! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Use OpenGL 4.5
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		// Get main monitor resolution
		SDL_DisplayMode current;
		int getDisplay = SDL_GetCurrentDisplayMode(0, &current);

		if (getDisplay != 0)
		{
			printf("Could not get display mode: %s\n", SDL_GetError());
			success = 0;
		}
		else
		{
			WINDOW_WIDTH = current.w / 1.5;
			WINDOW_HEIGHT = current.h / 1.5;

			// Create window
			gWindow = SDL_CreateWindow("Historia", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

			if (gWindow == NULL)
			{
				printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				gContext = SDL_GL_CreateContext(gWindow);

				if (gContext == NULL)
				{
					printf("OpenGL Context could not be created! SDL Error: %s\n", SDL_GetError());
					success = false;
				}
				else
				{
					// initialize glew
					glewExperimental = GL_TRUE;
					GLenum glewError = glewInit();

					if (glewError != GLEW_OK)
					{
						printf("Error initializing GLEW! Glew Error: %s\n", glewGetErrorString(glewError));
						success = false;
					}
					else
					{
						// Use vsync
						if (SDL_GL_SetSwapInterval(1) < 0)
						{
							printf("Warning: Unable to set vsync: SDL Error: %s\n", SDL_GetError());
						}

						// initialize OpenGL
						if (!initGL())
						{
							printf("Unable to initialize OpenGL!\n");
							success = false;
						}
					}
				}
			}
		}
	}

	return success;
}

bool initGL()
{
	return true;
}

void close()
{
	printf("Closing program\n");

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	//delete dynamic_cast<Super_Bible_Chapter_1*>(currentTutorial);
	//delete dynamic_cast<Super_Bible_Chapter_5*>(currentTutorial);
	//delete dynamic_cast<Learn_Open_GL_Transformations*>(currentTutorial);
	delete dynamic_cast<Learn_OpenGL_Lighting*>(currentTutorial);
	//delete dynamic_cast<Playground*>(currentTutorial);


	// Quiit SDL Subsystems
	SDL_Quit();
}

void update()
{
	currentTime = (float)SDL_GetTicks() / 1000.0f;
	inputManager->update(currentTime);
	currentTutorial->update(currentTime);
}

void render()
{
	float ticks = (float)SDL_GetTicks();
	currentTutorial->render(ticks/1000.f);	
}

int main(int argc, char* args[])
{

	int frame = 0;
	
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		bool quit = false;
		SDL_Event e;
		
		inputManager = InputManager::getInstance();

		SDL_StartTextInput();
		//currentTutorial = new Super_Bible_Chapter_1();
		//currentTutorial = new Super_Bible_Chapter_5();
		//currentTutorial = new Super_Bible_Chapter_5_Textures();
		//currentTutorial = new Learn_Open_GL_Transformations();
		currentTutorial = new Learn_OpenGL_Lighting();
		//currentTutorial = new Playground();
		currentTutorial->init();

		while (!quit)
		{
			++frame;

			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				else if (e.type == SDL_MOUSEMOTION)
				{
					inputManager->receiveMouseMotion(e.motion);
				}
			}
			
			update();
			inputManager->processInput();
			render();

			// Update Screen
			SDL_GL_SwapWindow(gWindow);
		}

		SDL_StopTextInput();
	}

	close();

	return 0;
}