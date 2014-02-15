#include <pebble.h>

Animation *animation;
Window *window;
TextLayer *text_layer;

void update(Animation *animation, const uint32_t time) {
	GRect frame = {
	};
	bitmap_layer_create(frame);
}

void init(void) {
	srand(time(NULL));

	window = window_create();
	window_set_background_color(window, GColorBlack);
	window_stack_push(window, true);

	animation = animation_create();
	animation_set_duration(animation, ANIMATION_DURATION_INFINITE);
	const AnimationImplementation implementation = {
		.setup = NULL,
		.update = update,
		.teardown = NULL
	};
	animation_set_implementation(animation, &implementation);
	animation_schedule(animation);
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
