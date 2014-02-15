#include <pebble.h>

static Window *window, *subwindow;
static SimpleMenuLayer *menu_layer;
static TextLayer *title_layer;
static TextLayer *section_layer;
static ScrollLayer *scroll_layer;

SimpleMenuItem items[] = {
	{ .icon = NULL, .subtitle = NULL, .title = "Article", },
	{ .icon = NULL, .subtitle = NULL, .title = "News" },
	{ .icon = NULL, .subtitle = NULL, .title = "Trivia" },
	{ .icon = NULL, .subtitle = NULL, .title = "History" },
};

const SimpleMenuSection sections = {
	.items = items,
	.num_items = 4,
	.title = NULL,
};

int8_t wiki = 0x0;

char *titles[] = {
	"Featured Article",
	"In the News",
	"Did You Know...",
	"On this Day...",
};

enum {
	WIKI_KEY_ARTICLE = 0x0,
	WIKI_KEY_NEWS = 0x1,
	WIKI_KEY_KNOW = 0x2,
	WIKI_KEY_DAY = 0x3,
	//WIKI_KEY_PIC = 0x4,
};

static void in_received_handler(DictionaryIterator *iter, void *context) {
	Tuple *section_tuple = dict_read_first(iter);
	text_layer_set_text(title_layer, titles[section_tuple->key]);
	text_layer_set_text(section_layer, section_tuple->value->cstring);
	int16_t h = text_layer_get_content_size(section_layer).h;
	text_layer_set_size(section_layer, GSize(144, h));
	scroll_layer_set_content_size(scroll_layer, GSize(144, 20 + h));
}

static void in_dropped_handler(AppMessageResult reason, void *context) {
	APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Dropped!");
}

static void app_message_init(void) {
  app_message_register_inbox_received(in_received_handler);
  app_message_register_inbox_dropped(in_dropped_handler);
  app_message_open(app_message_inbox_size_maximum(),
				   APP_MESSAGE_OUTBOX_SIZE_MINIMUM);
}

static void subwindow_load(Window *window) {
	Layer *window_layer = window_get_root_layer(subwindow);
	
	title_layer = text_layer_create(GRect(0, 0, 144, 20));
	text_layer_set_text_alignment(title_layer, GTextAlignmentCenter);
	
	section_layer = text_layer_create(GRect(0, 20, 144,
		app_message_inbox_size_maximum()));
	text_layer_set_text_alignment(section_layer, GTextAlignmentLeft);
	
	scroll_layer = scroll_layer_create(GRect(0, 0, 144, 152));
	scroll_layer_set_content_size(scroll_layer, GSize(144, 152));
	scroll_layer_set_click_config_onto_window(scroll_layer, subwindow);
	
	scroll_layer_add_child(scroll_layer, text_layer_get_layer(title_layer));
	scroll_layer_add_child(scroll_layer, text_layer_get_layer(section_layer));
	layer_add_child(window_layer, scroll_layer_get_layer(scroll_layer));
}

static void subwindow_unload(Window *window) {
	text_layer_destroy(title_layer);
	text_layer_destroy(section_layer);
	scroll_layer_destroy(scroll_layer);
}
static void window_load(Window *window) {

	menu_layer = simple_menu_layer_create(GRect(0, 0, 144, 152),
										  window, &sections, 4, NULL);
}

static void window_unload(Window *window) {
	simple_menu_layer_destroy(menu_layer);
}

static void subinit(void) {
	subwindow = window_create();
	window_set_window_handlers(subwindow, (WindowHandlers) {
		.load = subwindow_load,
		.unload = subwindow_unload,
	});
	window_stack_push(subwindow, true);
}

static void subdeinit(void) {
	window_destroy(subwindow);
}

static void init(void) {
	window = window_create();
	app_message_init();
	APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Init!");
	window_set_window_handlers(window, (WindowHandlers) {
		.load = window_load,
		.unload = window_unload,
	});
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Window Handlers!!");
	window_stack_push(window, true);
}

static void deinit(void) {
	window_destroy(window);
}

int main(void) {
	init();
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Finished Init!");
	app_event_loop();
	deinit();
}
