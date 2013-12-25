#! /usr/bin/python
# -*- coding: utf-8 -*-
import sys
import urllib2
import urllib
from lxml import etree, html
import StringIO
import codecs
def parse_result(page):
	f = open('../temp/page.html', 'w')
	f.write(page)
	f.close()
	parser = etree.HTMLParser()	
	page = page.decode('utf-8')
	tree = etree.parse(StringIO.StringIO(page), parser)
	tree = tree.xpath("//div[@id='en-collins']/ul[1]")[0]
	result = etree.tostring(tree, method='html', encoding='utf-8', pretty_print=True )
	result = result.decode('utf-8')
	f = codecs.open('../temp/result.html', 'w', 'utf-8')
	f.write(result)
	f.close()
def main(keyword):
	data = {}
	data['wd'] = keyword
	url_values = urllib.urlencode(data)
	url = 'http://dict.baidu.com/s'
	full_url = url + '?' + url_values
	print 'Requesting URL ' + full_url
	try:
		response = urllib2.urlopen(full_url)
	except:
		print 'Error while crawling the page'
		return -1
	the_page = response.read()
	parse_result(the_page)
	return 0;

if __name__ == "__main__":
	ret = main(sys.argv[1])
