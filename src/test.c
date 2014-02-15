#include <pebble.h>

static Window *window = NULL;
static Layer *root = NULL;
static Animation *animation = NULL;

void draw(Layer *layer, GContext *ctx) {
	graphics_draw_circle(ctx, GPoint(0, 0), rand() % 100);
}

void update(Animation *animation, const uint32_t time) {
	layer_mark_dirty(root);
}

static const AnimationImplementation implementation = {
	.update = update
};

void init(void) {
	window = window_create();
	window_set_background_color(window, GColorBlack);
	window_stack_push(window, true);

	animation = animation_create();
	animation_set_duration(animation, ANIMATION_DURATION_INFINITE);
	animation_schedule(animation);
	animation_set_implementation(animation, &implementation);

	root = window_get_root_layer(window);
	layer_set_update_proc(root, draw);
}

void deinit(void) {
	animation_destroy(animation);
	window_destroy(window);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}
