#include <pebble.h>

static Window *window = NULL;
static BitmapLayer *bitmap = NULL;

void init(void) {
	window = window_create();
	window_set_background_color(window, GColorBlack);
	window_stack_push(window, true);

	bitmap = bitmap_layer_create(GRect(0, 0, 20, 20));
	bitmap_layer_set_background_color(bitmap, GColorWhite);
}

void deinit(void) {
	window_destroy(window);
	bitmap_layer_destroy(bitmap);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}
