function fetchArticle() {
	var response;
	var req = new XMLHttpRequest();
	// build the GET request
	req.open('GET', "http://en.wikipedia.org/wiki/Special:FeedItem/potd/" + 20140216 + "000000/en", true);
	req.onload = function(e) {
		if (req.readyState == 4) {
			// 200 - HTTP OK
			if(req.status == 200) {
				response = req.responseText;
				var title = /<span .*?<\/span>/.exec(response);
				console.log(title);
				//Pebble.sendAppMessage({
				// "article": "$" + price.toString()});
				
			} else {
				console.log("Request returned error code " + req.status.toString());
			}
		}
	};
	req.send(null);
}

Pebble.addEventListener("ready",
						function(e) {
							console.log("connect!" + e.ready);
							console.log(e.type);
						});

Pebble.addEventListener("appmessage",
						function(e) {
							console.log("message");
							fetchArticle();
						});

