package com.rarTree;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Map.Entry;

public class rareTree {

	public static void main(String[] args) {

		String str1 = "abab";
		String str2 = "banb";

		// 输入参数列表
		ArrayList<String> argList = new ArrayList<String>();
		argList.add(str1);
		argList.add(str2);
		System.out.println("argList");
		System.out.println(argList);

		// 所有后缀子序列列表
		ArrayList<String> elemList = new ArrayList<String>();

		// 填充后缀子序列列表元素
		System.out.println("elemList");
		makeList(argList, elemList);
		System.out.println(elemList);

		// 处理流程
		// 所有节点与其子节点在后缀树上的关系（只包含一层的关系），key一个节点，value，这个节点对应的子节点
		Map<String, ArrayList<String>> firstMap = new HashMap<String, ArrayList<String>>();
		// 所有子节点与父节点在后缀树上的关系（firstMap倒过来，只包含一层的关系），key一个节点，value，这个节点对应的父节点
		Map<String, String> secondMap = new HashMap<String, String>();
		// 所有叶子节点（后缀子序列）的深度，key一个叶子节点，value，这个叶子节点的深度（层数）
		Map<String, Integer> levelMap = new HashMap<String, Integer>();

		// 计算firstMap，所有节点与其子节点在后缀树上的关系
		System.out.println("firstMap");
		makeMap(elemList, firstMap);
		System.out.println(firstMap);

		// 计算secondMap，所有子节点与父节点在后缀树上的关系（firstMap倒过来）
		System.out.println("secondMap");
		reverseMap(firstMap, secondMap);
		System.out.println(secondMap);

		// 所有叶子节点（后缀子序列）的深度
		System.out.println("levelMap");
		makeLevelMap(elemList, secondMap, levelMap);
		System.out.println(levelMap);

		System.out.println("result");
		printLevelMap(levelMap);
	}

	// 制作所有的后缀子序列
	public static void makeList(ArrayList<String> argList,
			ArrayList<String> elemList) {
		for (int i = 0; i < argList.size(); i++) {
			String str = (String) argList.get(i);
			
			for (int j = 0; j < str.length(); j++) {
				int index = str.length() - j - 1;
				String subStr = str.substring(index, str.length());
				int file = i + 1;
				String elemStr = subStr + "_" + file + ".txt" + "_" + index;
				elemList.add(elemStr);
			}
		}
	}

	// 制作每个节点和它的子节点，只构造一层父子关系
	public static void makeMap(ArrayList<String> elemList,
			Map<String, ArrayList<String>> map) {
		for (int j = 0; j < elemList.size(); j++) {

			String elemStr = elemList.get(j);
			String[] split = elemStr.split("_");
			String splitStr = split[0];
			int size = splitStr.length();
			for (int i = 0; i < size; i++) {
				String subStr = elemStr.substring(0, i + 1);
				String subStrBefore = elemStr.substring(0, i);
				if (map.get(subStr) == null) {
					ArrayList<String> mapList = new ArrayList<String>();
					mapList.add(elemStr);

					map.put(subStr, mapList);
				} else {
					map.get(subStr).add(elemStr);
				}
				if (map.get(subStrBefore) != null) {
					map.get(subStrBefore).add(subStr);
				}
			}
		}
		System.out.println(map);
		// 合并单条分支，如果一个父子关系中，没有两个叶子节点，则这个父子关系是多余的，可以合并
		System.out.println("firstMap merge node");
		removeUnusedPathSub(map);
	}

	/* 过滤重复多余的路径，其实是把n->b合并成nb这样的功能 */
	public static void removeUnusedPathSub(
			Map<String, ArrayList<String>> firstMap) {
		Iterator<Entry<String, ArrayList<String>>> iter = firstMap.entrySet()
				.iterator();
		ArrayList<String> removeList = new ArrayList<String>();
		while (iter.hasNext()) {
			Map.Entry<String, ArrayList<String>> entry = (Entry<String, ArrayList<String>>) iter
					.next();
			String key = entry.getKey();
			ArrayList<String> value = entry.getValue();
			int count = 0;
			for (int i = 0; i < value.size(); i++) {
				String str = value.get(i);
				if (str.contains("txt")) {
					count++;
				}
			}
			if (count < 2) {
				removeList.add(key);
			}
		}

		for (int i = 0; i < removeList.size(); i++) {
			firstMap.remove(removeList.get(i));
		}
	}

	// 将一层父子关系倒过来，变成子父关系，便于从叶子节点向上搜索到根，来确定层数
	public static void reverseMap(Map<String, ArrayList<String>> firstMap,
			Map<String, String> secondMap) {
		Iterator<Entry<String, ArrayList<String>>> iter = firstMap.entrySet()
				.iterator();
		while (iter.hasNext()) {
			Map.Entry<String, ArrayList<String>> entry = (Entry<String, ArrayList<String>>) iter
					.next();
			String key = entry.getKey();
			ArrayList<String> value = entry.getValue();
			for (int i = 0; i < value.size(); i++) {
				String str = value.get(i);
				if (secondMap.get(str) == null) {
					secondMap.put(str, key);
				} else {
					if (secondMap.get(str).length() < key.length()) {
						secondMap.put(str, key);
					}
				}
			}
		}
	}

	// 从叶子节点想上搜索到根，计算这条路径的长度（深度）
	public static void makeLevelMap(ArrayList<String> elemList,
			Map<String, String> secondMap, Map<String, Integer> levelMap) {
		for (int i = 0; i < elemList.size(); i++) {
			String elemStr = elemList.get(i);
			int level = getLevelSub(elemStr, secondMap);
			levelMap.put(elemStr, level);
		}
	}

	// 计算深度的子函数
	public static int getLevelSub(String elem, Map<String, String> secondMap) {
		int res = 1;
		String str = elem;
		while (secondMap.get(str) != null) {
			str = secondMap.get(str);
			res++;
		}
		return res;
	}

	// 打印函数
	public static void printLevelMap(Map<String, Integer> levelMap) {
		Iterator<Entry<String, Integer>> iter = levelMap.entrySet().iterator();
		while (iter.hasNext()) {
			Map.Entry<String, Integer> entry = (Entry<String, Integer>) iter
					.next();
			String key = entry.getKey();
			Integer value = entry.getValue();
			System.out.print(value + " ");
			String[] splitArr = key.split("_");
			System.out.println(splitArr[1] + ":" + splitArr[2]);
		}
	}
}
