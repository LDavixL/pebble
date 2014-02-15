#include <pebble.h>

Window *window;	

void tap_handler(AccelAxisType axis, int32_t direction) {
	Layer *root = window_get_root_layer(window);
}

void init(void) {
	window = window_create();
	window_stack_push(window, true);
	
	accel_tap_service_subscribe(tap_handler);
}

void deinit(void) {
	window_destroy(window);
}

int main( void ) {
	init();
	app_event_loop();
	deinit();
}