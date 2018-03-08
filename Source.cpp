#include "Adventure.h"
#include <Windows.h>  // import windows library

Adventure adventure;

int main() {
	SetConsoleTitle(TEXT("World War Y"));

	adventure.run();
	return 0;
}