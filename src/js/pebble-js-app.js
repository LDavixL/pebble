function fetchWiki(key) {
	var req = new XMLHttpRequest();
	if (key == "random") {
		req.open('GET', "http://en.wikipedia.org/w/index.php?title=Special:Random&mobileaction=toggle_view_desktop", true);
	}
	else {
		req.open('GET', "http://en.wikipedia.org/w/index.php?title=Main%20Page&mobileaction=toggle_view_desktop", true);
	}
	req.onload = function(e) {
		if (req.readyState == 4) {
			if(req.status == 200) {
				var section = req.responseText;
				var sitelink = /canonical.*/.exec(section)[0];
				sitelink = sitelink.replace('canonical" href=', '');
				sitelink = sitelink.replace('/>', '');
				switch(key) {
					case 'article':
						section = section.replace(/(?:.|\n)*?<div id="mp-tfa" /m, '');
						section = /<p(?:.|\n)*?p>/.exec(section)[0];
						section = section.replace(/<(?:.|\n)*?>/gm, '');
						section = section.replace(/&(?:.|\n)*?;/gm, ' ');
						section = section.replace(' (Full article...)', '');
						Pebble.sendAppMessage({ "article": section.concat("\n\n\nRead more at: " + sitelink)});
						break;
					case 'news':
						section = section.replace(/(?:.|\n)*?<div id="mp-itn">/m, '');
						section = /<ul(?:.|\n)*?ul>/m.exec(section)[0];
						section = section.replace(/<li>/g, '- ');
						section = section.replace(/<(?:.|\n)*?>/gm, '');
						section = section.replace(/&(?:.|\n)*?;/gm, ' ');
						Pebble.sendAppMessage({ "news": section.concat("\n\n\nRead more at: " + sitelink)});
						break;
					case 'trivia':
						section = section.replace(/(?:.|\n)*?<div id="mp-dyk">/m, '');
						section = /<ul(?:.|\n)*?ul>/m.exec(section)[0];
						section = section.replace(/<(?:.|\n)*?>/gm, '');
						section = section.replace(/&(?:.|\n)*?;/gm, ' ');
						Pebble.sendAppMessage({ "trivia": section.concat("\n\n\nRead more at: " + sitelink)});
						break;
					case 'history':
						section = section.replace(/(?:.|\n)*?<div id="mp-otd">/m, '');
						section = /<ul(?:.|\n)*?ul>/m.exec(section)[0];
						section = section.replace(/<(?:.|\n)*?>/gm, '');
						section = section.replace(/&(?:.|\n)*?;/gm, ' ');
						Pebble.sendAppMessage({ "history": section.concat("\n\n\nRead more at: " + sitelink)});
						break;
					case 'random':
						section = section.replace(/(?:.|\n)*?<div id="mw-content-text" /m, '');
						section = /<p(?:.|\n)*?p>/.exec(section)[0];
						section = section.replace(/<(?:.|\n)*?>/gm, '');
						section = section.replace(/&(?:.|\n)*?;/gm, ' ');
						section = section.replace('[citation needed]', '');
						section = section.replace('[1]', '');
						section = section.replace('[2]', '');
						section = section.replace('[3]', '');
						Pebble.sendAppMessage({ "random": section.concat("...\n\n\nRead more at: " + sitelink)});
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
