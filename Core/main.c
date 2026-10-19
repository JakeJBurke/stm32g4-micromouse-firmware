#include "board_init.h"
#include "App/app.h"

int main(void)
{

	const BOARD_Status_t board_status = board_init();
	if (board_status != BOARD_STATUS_OK) while (1);

	app_init();

	while (1)
	{
		app_update();
	}
}
