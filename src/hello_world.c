#include <pebble.h>

Animation *animation;
Window *window;
TextLayer *text_layer;

void handle_init(void) {
	// Create a window and text layer
	window = window_create();
	text_layer = text_layer_create(GRect(0, 0, 144, 154));

	// Set the text, font, and text alignment
	text_layer_set_text(text_layer, "Hi, I'm Chaoren!");
	text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);

	// Add the text layer to the window
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));

	animation = animation_create();
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
