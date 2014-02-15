Pebble.addEventListener("ready",
							function(e) {
								var text = "This a sample text";
								Pebble.sendAppMessage({0: text});
							}
						);