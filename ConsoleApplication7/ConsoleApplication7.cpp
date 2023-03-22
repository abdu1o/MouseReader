#include <iostream>
#include <Windows.h>

int main()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(consoleHandle, &consoleInfo);

    INPUT_RECORD inputRecords[128];
    DWORD eventsCount;
    HANDLE inputHandle = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(inputHandle, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);

    while (true) 
    {
        if (ReadConsoleInput(inputHandle, inputRecords, 128, &eventsCount))
        {
            for (DWORD i = 0; i < eventsCount; ++i) 
            {
                if (inputRecords[i].EventType == MOUSE_EVENT) 
                {
                    MOUSE_EVENT_RECORD& mouseEvent = inputRecords[i].Event.MouseEvent;
                    // Проверяем, что курсор мыши находится в пределах окна консоли

                    if (mouseEvent.dwMousePosition.X >= 0 && mouseEvent.dwMousePosition.X < consoleInfo.dwSize.X
                        && mouseEvent.dwMousePosition.Y >= 0 && mouseEvent.dwMousePosition.Y < consoleInfo.dwSize.Y) 
                    {
                        // Выводим координаты курсора
                        std::cout << "Mouse position: (" << mouseEvent.dwMousePosition.X << ", " << mouseEvent.dwMousePosition.Y << ")" << std::endl;

                        // Проверяем, что нажата левая клавиша мыши
                        if (mouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) 
                        {
                            std::cout << "Left button is pressed" << std::endl;
                        }
                    }
                }
            }
        }
    }
}