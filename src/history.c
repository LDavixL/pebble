#include <pebble.h>

Window *window;
TextLayer *text_layer;

static void in_received_handler(DictionaryIterator *received, void *context) {	
	Tuple *tuple = dict_find(received, 0);
	
	text_layer = text_layer_create(GRect(0, 0, 144, 154));
	
	// Set the text, font, and text alignment
	text_layer_set_text(text_layer, tuple->value->cstring);
	//text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	//text_layer_set_text_alignment(text_layer, GTextAlignmentLeft);
	
	// Add the text layer to the window
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
}

void init(void) {
	window = window_create();
	window_stack_push(window, true);
	
	app_message_register_inbox_received(in_received_handler); 
	app_message_open(app_message_inbox_size_maximum(), 0);
}

void deinit(void) {
	app_message_deregister_callbacks();
	window_destroy(window);
}

int main( void ) {
	init();
	app_event_loop();
	deinit();
}
