#include <pebble.h>

static Window *window = NULL;
static Layer *root = NULL;

void update(Layer *layer, GContext *ctx) {
	graphics_draw_circle(ctx, GPoint(0, 0), 20);
}

void init(void) {
	window = window_create();
	window_set_background_color(window, GColorBlack);
	window_stack_push(window, true);

	root = window_get_root_layer(window);
	layer_set_update_proc(root, update);
	layer_mark_dirty(root);
}

void deinit(void) {
	window_destroy(window);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}
