#define _CRT_SECURE_NO_DEPRECATE
#pragma once
#include<iostream>
#include<string>
#include<map>
#include<set>
#include<algorithm>
#include<vector>
using namespace std;

#include "Heap.h"

void PrintMap(const map<string,string> & dict)
{
	map<string, string>::const_iterator DictIt = dict.begin();
	while (DictIt != dict.end())
	{
		cout << (*DictIt).first << ":" << DictIt->second << endl;
		DictIt++;
	}
	cout << endl;
}



void TestMap()
{ 
	////typedef pair<const Key, T> value_type库中定义；
	//map<string, string> dict;
	//dict.insert(make_pair("tree","树"));    //insert插入时是一个pair 的结构体对象；返回一个结构体pair<iterator,bool> insert (const value_type& val);
	//dict.insert(pair<string, string>("insert", "插入"));
	//dict.insert(make_pair("jeep", "吉普"));
	//dict.insert(make_pair("search", "查找"));
	////dict.insert(make_pair("tree", "xx")).first->second = "大树"; //修改；
	//PrintMap(dict);
	////cout << dict.insert(make_pair("tree", "xx")).first->first << endl; //insert进行查找；

	///*删除
	//Find 找到之后erase进行删除；
	//iterator find (const key_type& k);  //找不到返回end()迭代器；
	//(1)
	//void erase (iterator position);  //删除一个位置
	//(2)
	//size_type erase (const key_type& k);  //根据key值删除
	//(3)
	//void erase (iterator first, iterator last);  //删除一个迭代器区间；
	//*/
	//map<string, string>::iterator DictIt;
	//DictIt = dict.find("tree");
	//if (DictIt != dict.end())
	//{
	//	dict.erase(DictIt);
	//}
	//else
	//{
	//	cout << "没有这个值" << endl;
	//}
	//PrintMap(dict);

	/*---------------------------------
	operator[]的插入，修改，查找； (*((this->insert(make_pair(k,mapped_type()))).first)).second;利用insert实现；

	mapped_type& operator[] (const key_type& k);  返回value的引用；

	*/
	map<string, string> dict;
	//插入
	dict["sort"] = "排序";
	dict["map"] = "地图";
	PrintMap(dict);
	//修改
	dict["sort"] = "整理";
	PrintMap(dict);
	//查找
	cout << dict["map"] << endl;

}

void PrintMap(const map<string,int> & dict)
{
	map<string, int>::const_iterator DictIt = dict.begin();
	while (DictIt != dict.end())
	{
		cout << (*DictIt).first << ":" << DictIt->second << endl;
		DictIt++;
	}
	cout << endl;
}
void TestTopK()
{
	string fruit[] = { "苹果", "香蕉", "西瓜", "苹果", "苹果", "苹果", "西瓜", "西瓜", "苹果", "苹果", "西瓜", "香蕉", "葡萄", "桃子", "桃子", "桃子"};
	map<string, int> countMap;

	for (int i = 0; i< sizeof(fruit) / sizeof(fruit[0]); i++)
	{
		/*第一种方法：先查再插
		map<string,int>::iterator ret = countMap.find(fruit[i]); 
		if (ret != countMap.end())
		{
			(ret->second)++;
		}
		else
		{
			countMap.insert(make_pair(fruit[i], 1));
		}*/
		/*--------------------------
		//第二种：利用insert的返回值；
		pair<map<string, int>::iterator, bool > pr = countMap.insert(pair<string,int>(fruit[i],1));
		if (pr.second == false)
		{
			(pr.first)->second++;
		}*/

		/*-------------------------
		第三种：operator[];
		找到了返回second即value的引用；
		没找到，插入并返回value（value的初始值为默认缺省）的引用；
		*/
		countMap[fruit[i]]++;
	}
	//PrintMap(countMap);
	/*-----------------------------
	topK的问题；
	1.sort
	2.make_heap
	3.优先级队列
	*/

	/*//sort----------------------------------
	vector<map<string, int>::iterator> v;
	map<string, int>::iterator countIt = countMap.begin();
	while (countIt != countMap.end())
	{
		v.push_back(countIt);
		countIt++;
	}

	//比较的是value的值；
	struct Compare
	{
		bool operator()(map<string, int>::iterator l, map<string, int>::iterator r)
		{
			return l->second > r->second;
		}
	};

	sort(v.begin(),v.end(),Compare());
	*/

	/*//建堆-------------------------
	建小堆
	*/
	struct Less
	{
		bool operator()(map<string, int>::iterator l, map<string, int>::iterator r)
		{
			return l->second > r->second;
		}
	};
	Heap<map<string, int>::iterator,Less> minHeap;
	map<string, int>::iterator countIt = countMap.begin();
	while (countIt != countMap.end())
	{
		minHeap.Push(countIt);
		countIt++;
	}
	while (!minHeap.Empty())
	{
		cout << minHeap.Top()->first << ":" << minHeap.Top()->second << endl;
		minHeap.Pop();
	}
}

void TestMultimap() //允许重复key的插入，没有[]重载，没有意义； 
{
	multimap<string, string> dict;
	multimap<string, string>::iterator it;
	dict.insert(make_pair("world","大千世界"));
	dict.insert(make_pair("people", "芸芸众生"));
	dict.insert(make_pair("world", "a世界"));
	dict.insert(make_pair("world", "b小世界"));
	dict.insert(make_pair("world", "c小世界"));
	dict.insert(make_pair("world", "d小世界"));
	it = dict.find("world");
	while (it != dict.end() && it->first == "world")
	{
		cout << it->first << " :" << it->second << endl;
		it++;
	}
	cout << endl;
}

void TestSet()
{
	/*------------------------
	set
	1.判断一个对象在不在集合里
	2.排序
	3.去重；

	*/

	/*--------------------------
	multiset
	*/
	multiset<int> s;
	s.insert(0);
	s.insert(0);
	s.insert(2);
	s.insert(6);
	s.insert(4);
	s.insert(5);
	s.insert(8);

	multiset<int>::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << endl;
		it++;
	}
}