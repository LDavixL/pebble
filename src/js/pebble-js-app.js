function fetchWiki(key) {
	var req = new XMLHttpRequest();
	req.open('GET', "http://en.wikipedia.org/w/index.php?title=Main%20Page&mobileaction=toggle_view_desktop", true);
	req.onload = function(e) {
		if (req.readyState == 4) {
			if(req.status == 200) {
				var section = req.responseText;
				switch(key) {
					case 'article':
						section = section.replace(/(?:.|\n)*?<div id="mp-tfa" /m, '');
						section = /<p(?:.|\n)*?p>/.exec(section)[0];
						section = section.replace(/<(?:.|\n)*?>/gm, '');
						section = section.replace(/&(?:.|\n)*?;/gm, ' ');
						section = section.replace(' (Full article...)', '');
						Pebble.sendAppMessage({ "article": section });
						break;
					case 'news':
						section = section.replace(/(?:.|\n)*?<div id="mp-itn">/m, '');
						section = /<ul(?:.|\n)*?ul>/m.exec(section)[0];
						section = section.replace(/<li>/g, '- ');
						section = section.replace(/<(?:.|\n)*?>/gm, '');
						section = section.replace(/&(?:.|\n)*?;/gm, ' ');
						Pebble.sendAppMessage({ "news": section });
						break;
					case 'trivia':
						section = section.replace(/(?:.|\n)*?<div id="mp-dyk">/m, '');
						section = /<ul(?:.|\n)*?ul>/m.exec(section)[0];
						section = section.replace(/<(?:.|\n)*?>/gm, '');
						section = section.replace(/&(?:.|\n)*?;/gm, ' ');
						Pebble.sendAppMessage({ "trivia": section });
						break;
					case 'history':
						section = section.replace(/(?:.|\n)*?<div id="mp-otd">/m, '');
						section = /<ul(?:.|\n)*?ul>/m.exec(section)[0];
						section = section.replace(/<(?:.|\n)*?>/gm, '');
						section = section.replace(/&(?:.|\n)*?;/gm, ' ');
						Pebble.sendAppMessage({ "history": section });
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
