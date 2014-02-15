function fetchWiki(key) {
	var response;
	var req = new XMLHttpRequest();
	req.open('GET', "http://en.wikipedia.org/wiki/Main_Page", true);
	req.onload = function(e) {
		if (req.readyState == 4) {
			if(req.status == 200) {
				response = req.responseText;
				var section = /<p.*?p>/.exec(response)[0];
				section = section.replace(/<(?:.|\n)*?>/gm, '');
				section = section.replace('&#160;', ' ');
				section = section.replace(' (Full&#160;article...)', '');
				switch(key) {
					case 'article': Pebble.sendAppMessage({
								"article": section });
						break;
					case 'news': Pebble.sendAppMessage({
								"news": section });
						break;
					case 'trivia': Pebble.sendAppMessage({
								"trivia": section });
						break;
					case 'history': Pebble.sendAppMessage({
								"history": section });
				}
			} else {
				console.log("Request returned error code " + req.status.toString());
			}
		}
	}; 
	req.send(null);
}

Pebble.addEventListener("appmessage", function(e) {
	for(var key in e.payload) break;
	fetchWiki(key);
});
