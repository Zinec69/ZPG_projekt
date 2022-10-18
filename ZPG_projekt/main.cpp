#include "Application.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

int main()
{
	Application application(WINDOW_WIDTH, WINDOW_HEIGHT);
	application.run();

	return 0;
}
