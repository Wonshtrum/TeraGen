#!/usr/bin/python3

from sys import argv

def templates(program):
	name, _, ext = program.split("/")[-1].partition(".")
	NAME = name.upper()

	headerTemplate = """#ifndef __{0}_H__
#define __{0}_H__

{1}

#endif""".format(NAME, "{}")

	coreTemplate = """#include "{0}.h"
{1}""".format(name, "{}")

	return (name, headerTemplate, coreTemplate)

def beginWith(line, *words):
	lineClean = line.replace("\t", "")
	return any(lineClean[:len(word)] == word for word in words)

def findTabs(line):
	tabs = 0
	while line[tabs] == "\t":
		tabs += 1
	return tabs

def correctTabs(line, tabs):
	for i in range(tabs):
		if line[0] == "\t":
			line = line[1:]
		else:
			break
	return line

def extract(program):
	print(program)
	name, headerTemp, coreTemp = templates(program)
	header = core = ""

	with open(program) as stream:
		lines = stream.readlines()
	
	state = 0
	nameSpace = ""
	tabs = 0
	for line in lines:
		if beginWith(line, "#include", "#define", "typedef"):
			header += line
		elif beginWith(line, "class", "struct", "enum"):
			header += line
			nameSpace = line.split(" ")[1]
		elif beginWith(line, "//", "/*", "template") or ((state == 0 or (state == 1 and nameSpace)) and line.replace(" ", "").replace("\t", "") == "\n"):
			if len(core) < 2 or core[-2] != "\n":
				core += "\n"
			if len(header) < 2 or header[-2] != "\n":
				header += "\n"
		elif (state == 0 or (state == 1 and nameSpace)) and "{" in line:
			tabs = findTabs(line)
			if ") {" in line:
				proto, _, impl = line.partition(" {")
			else:
				proto, _, impl = line.partition(" = {")
			protoClean, _, init = proto.replace("::", "##").partition(":")
			protoClean = protoClean.replace("##", "::")
			header += protoClean+";\n"
			if "=" in protoClean:
				protoClean = protoClean.replace("\t", "")
				frags = protoClean.split(" = ")
				protoCleanNoDefault = frags[0]
				for frag in frags[1:]:
					if "," in frag:
						var, _, end = frag.partition(",")
					else:
						var, _, end = frag.partition(")")
					protoCleanNoDefault += _+end
				line = line.replace(protoClean, protoCleanNoDefault, 1)
			if nameSpace:
				if "[" in line and not ") {" in line:
					pre, _, args = line.partition("[")
				else:
					pre, _, args = line.partition("(")
				fun = pre.replace("\t", "").split(" ")[-1]
				line = line.replace(fun, nameSpace+"::"+fun, 1)
				if "noise2D" in line:
					print(line)
			if beginWith(line, "static "):		
				line = line.replace("static ", "", 1)
			core += correctTabs(line, tabs)
		elif state == 1 and nameSpace:
			header += line
		elif nameSpace == "" or state >= 2:
			core += correctTabs(line, tabs)

		state += line.count("{")-line.count("}")
		if state == 0 and nameSpace:
			nameSpace = ""

	program = program.replace("coupled", "src").replace(".cpp", "")
	with open(program+".h", "w") as stream:
		stream.write(headerTemp.format(header))
	with open(program+".cpp", "w") as stream:
		stream.write(coreTemp.format(core))

if __name__ == "__main__":
    program = argv[1]
    extract(program)
