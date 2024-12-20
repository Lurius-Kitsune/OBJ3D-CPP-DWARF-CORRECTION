#include "ControlsMenu.h"
#include "Macro.h"
#include "FileStream.h"

ControlsMenu::ControlsMenu() : Menu("Controls")
{

}

void ControlsMenu::Show(const bool _toAdd)
{
	Super::Show(_toAdd);

	Gradient _gradient = Gradient({159, 37, 96}, {94, 153, 42});
	FileStream::DisplayFile("Assets/Menus/Controls/ControlsInfo.txt", _gradient);
}