#include <pebble.h>

Animation *animation;
Window *window;
TextLayer *text_layer;

void handle_init(void) {
	// Create a window and text layer
	window = window_create();

	animation = animation_create();
	animation_set_duration(animation, ANIMATION_DURATION_INFINITE);
	animation_schedule(animation);

	// Push the window
	window_stack_push(window, true);
}

void handle_deinit(void) {
	// Destroy the text layer
	text_layer_destroy(text_layer);

	animation_destroy(animation);

	// Destroy the window
	window_destroy(window);
}

int main(void) {
	handle_init();
	app_event_loop();
	handle_deinit();
}
