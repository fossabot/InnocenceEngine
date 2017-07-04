#include "CoreEngine.h"

Time::Time() {
}
Time::~Time() {}

const double Time::getTime() {
	return 1.0;
}

const double Time::getDelta()
{

	typedef std::chrono::high_resolution_clock clock;
	typedef std::chrono::duration<float, std::milli> duration;

	static clock::time_point start = clock::now();
	duration elapsed = clock::now() - start;

	delta = elapsed.count();
	return delta;

}

CoreEngine::CoreEngine()
{
	init();
}


CoreEngine::~CoreEngine()
{
	shutdown();
}

void CoreEngine::init()
{
	_isRunning = true;
	frameTime = 1.0f / frameRate;

	_time = new Time();
	_window = new Window();
	_input = new Input();
	_input->setWindow(_window);
	_renderingEngine = new RenderingEngine();
	_audioEngine = new AudioEngine();
	_game = new Game();
	_game->setRenderingEngine(_renderingEngine);
	_renderingEngine->setMainCamera(_game->getCameraComponent());


	fprintf(stdout, "Core Engine has been initialized.\n");
	//_audioEngine->playSound("D:/WwiseOriginalFiles/NewSourceFiles/20170418/Item_Ride_Egg_Break.wav");
	//_audioEngine->playSound("F:/Installation Files/Music/TesseracT - Altered State (2013) [FLAC]/test.wav");

}

void CoreEngine::update()
{
	double unprocessedTime = 0;
	double passedTime = 0;

	while (_isRunning) {

		passedTime = _time->getDelta();
		unprocessedTime += passedTime;
		std::cout << passedTime << std::endl;
		while (unprocessedTime > frameTime)
		{
			//fprintf(stdout, "Core Engine is updating.\n");
			unprocessedTime -= frameTime;

			_game->input(frameTime);
			_input->update();
			_game->update(frameTime);

			//fprintf(stdout, "Core Engine is rendering.\n");
			_window->render();
			_game->render();
			_audioEngine->update();

		}
		//fprintf(stdout, "Core Engine is sleeping.\n");
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	shutdown();
}

void CoreEngine::shutdown() {
	delete _game;
	delete _renderingEngine;
	delete _audioEngine;
	delete _input;
	delete _window;
	delete _time;
	fprintf(stdout, "Core Engine has been destroyed.\n");
	std::this_thread::sleep_for(std::chrono::seconds(3));
}
