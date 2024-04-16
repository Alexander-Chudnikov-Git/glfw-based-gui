#include "window_handler/CGUIMainWindow.hpp"


int main(int argc, char const *argv[])
{
	switch(argc)
	{
		case 1:
		{
			CGUIMainWindow window;

			window.show();
			window.close();
		}
		break;

		default:
		{
			std::string error_msg = "";
			for(std::size_t index = 0; index < (std::size_t)(argc - 1); ++index)
			{
				error_msg += argv[index];
				error_msg += " ";
			}
			std::cerr << error_msg;
		}
	}

	return 0;
}
