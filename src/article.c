#include <pebble.h>

static Window *window;
static TextLayer *title_layer;
static TextLayer *article_layer;
static ScrollLayer *scroll_layer;

enum {
	WIKI_KEY_ARTICLE = 0x0,
};

static void in_received_handler(DictionaryIterator *iter, void *context) {
	Tuple *article_tuple = dict_find(iter, WIKI_KEY_ARTICLE);
	
	if (article_tuple) {
		text_layer_set_text(article_layer, article_tuple->value->cstring);
	} else {
		text_layer_set_text(article_layer, "Error: article not received.");
	}
	int16_t article_h = text_layer_get_content_size(article_layer).h;
	
	APP_LOG(APP_LOG_LEVEL_DEBUG, "article h %d", article_h);
	
	text_layer_set_size(article_layer, GSize(144, article_h));
	scroll_layer_set_content_size(scroll_layer, GSize(144, 20 + article_h));
	scroll_layer_set_click_config_onto_window(scroll_layer, window);
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

static void window_load(Window *window) {
	Layer *window_layer = window_get_root_layer(window);

	title_layer = text_layer_create(GRect(0, 0, 144, 20));
	article_layer = text_layer_create(GRect(0, 20, 144, 10000));
	scroll_layer = scroll_layer_create(GRect(0, 0, 144, 152));
	scroll_layer_set_content_size(scroll_layer, GSize(144, 152));
	
	text_layer_set_text(title_layer, "Article of the Day:");
	text_layer_set_text_alignment(title_layer, GTextAlignmentCenter);
	
	scroll_layer_add_child(scroll_layer, text_layer_get_layer(title_layer));
	scroll_layer_add_child(scroll_layer, text_layer_get_layer(article_layer));
	layer_add_child(window_layer, scroll_layer_get_layer(scroll_layer));
}

static void window_unload(Window *window) {
	text_layer_destroy(title_layer);
	text_layer_destroy(article_layer);
	scroll_layer_destroy(scroll_layer);
}

static void init(void) {
  window = window_create();
  app_message_init();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(window, true);
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
