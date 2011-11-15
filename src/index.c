/* pshs -- file index generation
 * (c) 2011 Michał Górny
 * 2-clause BSD-licensed
 */

#include "config.h"

#include <stdlib.h>
#include <string.h>

#include "index.h"

/* Building parts of the index page. */

const char head[] = "<!DOCTYPE html>\n"
	"<html>"
		"<head>"
			"<meta charset='utf-8'/>"
		"</head>"
		"<body>"
			"<ol>";

const char tail[] =
			"</ol>"
		"</body>"
	"</html>";

/* Building parts of a single link. */

const char filenameprefix[] = "<li><a href='/";
const char filenamemidfix[] = "'>";
const char filenamesuffix[] = "</a></li>";

/**
 * generate_index
 * @buf: target buffer
 * @files: filelist
 *
 * Generate HTML index of files in @filelist and write it to buffer @buf.
 */
void generate_index(struct evbuffer *buf, const char **files) {
	evbuffer_add_reference(buf, head, sizeof(head)-1, NULL, NULL);

	for (; *files; files++) {
		const int fnlen = strlen(*files);

		evbuffer_add_reference(buf, filenameprefix,
				sizeof(filenameprefix)-1, NULL, NULL);
		evbuffer_add_reference(buf, *files, fnlen, NULL, NULL);
		evbuffer_add_reference(buf, filenamemidfix,
				sizeof(filenamemidfix)-1, NULL, NULL);
		evbuffer_add_reference(buf, *files, fnlen, NULL, NULL);
		evbuffer_add_reference(buf, filenamesuffix,
				sizeof(filenamesuffix)-1, NULL, NULL);
	}

	evbuffer_add_reference(buf, tail, sizeof(tail)-1, NULL, NULL);
}
