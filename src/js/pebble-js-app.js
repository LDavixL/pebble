function fetchWiki() {
	var response;
	var req = new XMLHttpRequest();
	req.open('GET', "http://en.wikipedia.org/wiki/Main_Page", true);
	req.onload = function(e) {
		if (req.readyState == 4) {
			if(req.status == 200) {
				response = req.responseText;
				var article = /<p.*?p>/.exec(response)[0];
				article = article.replace(/<(?:.|\n)*?>/gm, '');
				article = article.replace('&#160;', ' ');
				article = article.replace(' (Full&#160;article...)', '');
				Pebble.sendAppMessage({
					"article": article });
			} else {
				console.log("Request returned error code " + req.status.toString());
			}
		}
	};
	req.send(null);
}

Pebble.addEventListener("ready", function(e) { fetchWiki(); });
