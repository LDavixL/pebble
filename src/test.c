#include <pebble.h>


void init(void) {
	Window *window = window_create();
	window_set_background_color(window, GColorBlack);
	window_stack_push(window, true);
}

void deinit(void) {
	Window *window = window_stack_pop(true);
	window_destroy(window);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}
