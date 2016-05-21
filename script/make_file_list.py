#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import os
import re
import argparse

def gen_dir_entries_html(directory,format,base,hrefpath,cssprefix,dironly,charset,order,exclude_patterns,skip,links):
	l = os.listdir(directory)
# sortieren: Nondir, dann Dir. Hier koennem wir auch filtern
	t_non = []
	t_dir = []
	if dironly == False:
		for e in l:
			if os.path.isdir(directory + "/" + e) == False:
				if exclude_patterns != None :
					excluded = False
					for pattern in exclude_patterns:
						if re.search(pattern,directory + "/" + e) != None:
							excluded = True
					if excluded == False:
						t_non.append(e)
				else:
					t_non.append(e)
	for e in l:
		if os.path.isdir(directory + "/" + e) == True:
			if exclude_patterns != None :
				excluded = False
				for pattern in exclude_patterns:
					if re.search(pattern,directory + "/" + e) != None:
						excluded = True
				if excluded == False:
					t_dir.append(e)
			else:
				t_dir.append(e)
# alphabetisch sortieren
	if order == "files":
		l = sorted(t_non) + sorted(t_dir)
	elif order == "dirs":
		l = sorted(t_dir) + sorted(t_non)
	else:
		l = sorted(t_dir + t_non)
# l ist sortiert
	if format == "plain":
		for e in l:
			if os.path.isdir(directory + "/" + e) == True:
				yield " " + e,True,e == l[-1]
				for u,is_child,is_last in gen_dir_entries_html(directory + "/" + e,format,base,hrefpath + "/" + e,cssprefix,dironly,charset,order,exclude_patterns,skip,links):
					if is_child == True:
						for i in range(skip):
							if charset == "utf-8":
								yield "|",False,e == l[-1]
							else:
								yield "|",False,e == l[-1]
						if is_last:
							if charset == "utf-8":
								yield "└──" + u,False,e == l[-1]
							else:
								yield "+--" + u,False,e == l[-1]
						else:
							if charset == "utf-8":
								yield "├──" + u,False,e == l[-1]
							else:
								yield "+--" + u,False,e == l[-1]
					else:
						if is_last:
							yield "    " + u,False,e == l[-1]
						else:
							if charset == "utf-8":
								yield "│   " + u,False,e == l[-1]
							else:
								yield "|   " + u,False,e == l[-1]
			elif os.path.islink(directory + "/" + e) == True:
				yield " " + e,True,e == l[-1]
			else:
				yield " " + e,True,e == l[-1]
	elif format == "html":
		for e in l:
			if os.path.isdir(directory + "/" + e) == True:
				yield " <span class='%sdir'>" % cssprefix + e + "</span>",True,e == l[-1]
				for u,is_child,is_last in gen_dir_entries_html(directory + "/" + e,format,base,hrefpath + "/" + e,cssprefix,dironly,charset,order,exclude_patterns,skip,links):
					if is_child == True:
						for i in range(skip):
							if charset == "utf-8":
								yield "|",False,e == l[-1]
							else:
								yield "|",False,e == l[-1]
						if is_last:
							if charset == "utf-8":
								yield "└──" + u,False,e == l[-1]
							else:
								yield "+--" + u,False,e == l[-1]
						else:
							if charset == "utf-8":
								yield "├──" + u,False,e == l[-1]
							else:
								yield "+--" + u,False,e == l[-1]
					else:
						if is_last:
							if charset == "utf-8":
								yield "&nbsp;&nbsp;&nbsp;&nbsp;" + u,False,e == l[-1]
							else:
								yield "&nbsp;&nbsp;&nbsp;&nbsp;" + u,False,e == l[-1]
						else:
							if charset == "utf-8":
								yield "│&nbsp;&nbsp;&nbsp;" + u,False,e == l[-1]
							else:
								yield "|&nbsp;&nbsp;&nbsp;" + u,False,e == l[-1]
			elif os.path.islink(directory + "/" + e) == True:
				suffix = os.path.splitext(e)[-1][1:]
				yield " <span class='%slink' suffix='%s'>" % (cssprefix,suffix) + e + "</span>",True,e == l[-1]
			else:
				suffix = os.path.splitext(e)[-1][1:]
				if links:
					yield " <span class='%sfile' suffix='%s'><a href='%s'>" % (cssprefix,suffix,base + "/" + hrefpath + "/" + e) + e + "</a></span>",True,e == l[-1]
				else:
					yield " <span class='%sfile' suffix='%s'>" % (cssprefix,suffix) + e + "</span>",True,e == l[-1]

def list_as_html(directory,format,base,cssprefix,dironly,charset,order,exclude_patterns,skip,links):
	dirbase = os.path.basename(os.path.realpath(directory))
	g = gen_dir_entries_html(directory,format,base,dirbase,cssprefix,dironly,charset,order,exclude_patterns,skip,links)
	if format == "plain":
		print dirbase
		for d,is_child,is_last in g:
			if is_child:
				for i in range(skip):
					if charset == "utf-8":
						print "|"
					else:
						print "|"
				if is_last:
					if charset == "utf-8":
						print "└──" + d
					else:
						print "+--" + d
				else:
					if charset == "utf-8":
						print "├──" + d
					else:
						print "+--" + d
			else:
				if is_last:
					if charset == "utf-8":
						print "    " + d
					else:
						print "    " + d
				else:
					if charset == "utf-8":
						print "│   " + d
					else:
						print "|   " + d
	elif format == "html":
		print "<span class='%sdir'>" % cssprefix + dirbase + "</span><br/>"
		for d,is_child,is_last in g:
			if is_child:
				for i in range(skip):
					if charset == "utf-8":
						print "|<br/>"
					else:
						print "|<br/>"
				if is_last:
					if charset == "utf-8":
						print "└──" + d + "<br/>"
					else:
						print "+--" + d + "<br/>"
				else:
					if charset == "utf-8":
						print "├──" + d + "<br/>"
					else:
						print "+--" + d + "<br/>"
			else:
				if is_last:
					if charset == "utf-8":
						print "&nbsp;&nbsp;&nbsp;&nbsp;" + d + "<br/>"
					else:
						print "&nbsp;&nbsp;&nbsp;&nbsp;" + d + "<br/>"
				else:
					if charset == "utf-8":
						print "│&nbsp;&nbsp;&nbsp;" + d + "<br/>"
					else:
						print "|&nbsp;&nbsp;&nbsp;" + d + "<br/>"


parser = argparse.ArgumentParser(description = 'command line options for make_file_list.',epilog="Good luck and have fun!")
parser.add_argument("-path",dest = "path",default = ".",help = "directory to list")
parser.add_argument("-linkbase",dest = "linkbase",default = ".",help = "path added before -path in html for href-links")
parser.add_argument("-links",dest = "links",default = False,help = "generate links in html (otherwise plain text)")
parser.add_argument("-format",dest = "format",default = "html",help = "possible values are: 'html', 'plain'")
parser.add_argument("-charset",dest = "charset",default = "utf-8",help = "possible values are: 'ascii', 'utf-8'")
parser.add_argument("-dironly",dest = "dironly",default = False,help = "possible values are: True, False - list dirs only")
parser.add_argument("-exclude",dest = "exclude",nargs = "*",help = "patterns to exclude (python regex)")
parser.add_argument("-cssprefix",dest = "cssprefix",default = "",help = "prefix for css classnames")
parser.add_argument("-order",dest = "order",default = "",help = "possible values are: 'dirs', 'files', 'mixed'.")
parser.add_argument("-skip",dest = "skip",default = 0,help = "extend by empty lines, possible values are: 0,1,2...")

args = parser.parse_args()


if len(sys.argv) == 1:
	print "make_file_list, (C) SDV 2015"
	print "try -h"
else:
	list_as_html(args.path,args.format,args.linkbase,args.cssprefix,args.dironly,args.charset,args.order,args.exclude,int(args.skip),bool(args.links))


