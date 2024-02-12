# python3
import sys
from collections import deque


class Node:
	def __init__(self, front, end, first):
		self.front = front
		self.end = end
		self.children = list()
		self.parent = ''
		self.first = first


def build_suffix_tree(content, position):
	n = len(content)
	j = 0  # j = new string starting point
	tree = list()
	while j < n:
		add_new = True
		for node in tree:
			if match_or_not(i, content, node):
				if j >= position:
					node.first = False
				child = node
				add_new = False
				break
		if add_new:
			new = Node(j, n, j < position)
			tree.append(new)
		else:
			found = True
			while found:  # f = check whether child is new
				found = False
				i, f, e = matching(i, content, child)  # f = child front
				if f >= e:  # string match child, child = new child; else child = old child
					if j >= position:
						child.first = False
					for node in child.children:
						if match_or_not(i, content, node):
							child = node
							found = True  # confirm new child
							break
			if f < child.end:  # only when mother node has space
				child.end = f
				relic = Node(f, e, child.first)
				relic.children = child.children
				child.children = [relic]
			if j >= position:
				child.first = False
			new_child = Node(i, n, j < position)
			child.children.append(new_child)
		j = j + 1  # new string set and while for next string
		i = j
	return tree


def match_or_not(i, content, target):
	return content[i] == content[target.front]


def matching(i, content, target):
	f = target.front
	e = target.end
	while f < e and content[i] == content[f]:  # need to mark off target end from not match
		i, f = i + 1, f + 1
	return i, f, e


def solve(p, q):
	content = p+'#'+q+'$'
	position, end = len(p), len(content)
	suffix_tree = build_suffix_tree(content, position)
	result = list()
	nodes = deque()
	for node in suffix_tree:
		nodes.append(node)
	while len(nodes) > 0:
		node = nodes.popleft()
		if node.front < position:
			if node.first:
				result.append(node.parent + content[node.front])
			elif node.end < position:
				for child in node.children:
					child.parent = node.parent + content[node.front: node.end]
					nodes.append(child)
			elif node.end == end:
					result.append(node.parent + content[node.front])
	mini = end
	for sub in result:
		if len(sub) <= mini:
			mini = len(sub)
			shortest = sub
	return shortest

p = sys.stdin.readline().strip()
q = sys.stdin.readline().strip()

ans = solve(p, q)
sys.stdout.write(ans + '\n')