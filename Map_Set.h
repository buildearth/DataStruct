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
	////typedef pair<const Key, T> value_type���ж��壻
	//map<string, string> dict;
	//dict.insert(make_pair("tree","��"));    //insert����ʱ��һ��pair �Ľṹ����󣻷���һ���ṹ��pair<iterator,bool> insert (const value_type& val);
	//dict.insert(pair<string, string>("insert", "����"));
	//dict.insert(make_pair("jeep", "����"));
	//dict.insert(make_pair("search", "����"));
	////dict.insert(make_pair("tree", "xx")).first->second = "����"; //�޸ģ�
	//PrintMap(dict);
	////cout << dict.insert(make_pair("tree", "xx")).first->first << endl; //insert���в��ң�

	///*ɾ��
	//Find �ҵ�֮��erase����ɾ����
	//iterator find (const key_type& k);  //�Ҳ�������end()��������
	//(1)
	//void erase (iterator position);  //ɾ��һ��λ��
	//(2)
	//size_type erase (const key_type& k);  //����keyֵɾ��
	//(3)
	//void erase (iterator first, iterator last);  //ɾ��һ�����������䣻
	//*/
	//map<string, string>::iterator DictIt;
	//DictIt = dict.find("tree");
	//if (DictIt != dict.end())
	//{
	//	dict.erase(DictIt);
	//}
	//else
	//{
	//	cout << "û�����ֵ" << endl;
	//}
	//PrintMap(dict);

	/*---------------------------------
	operator[]�Ĳ��룬�޸ģ����ң� (*((this->insert(make_pair(k,mapped_type()))).first)).second;����insertʵ�֣�

	mapped_type& operator[] (const key_type& k);  ����value�����ã�

	*/
	map<string, string> dict;
	//����
	dict["sort"] = "����";
	dict["map"] = "��ͼ";
	PrintMap(dict);
	//�޸�
	dict["sort"] = "����";
	PrintMap(dict);
	//����
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
	string fruit[] = { "ƻ��", "�㽶", "����", "ƻ��", "ƻ��", "ƻ��", "����", "����", "ƻ��", "ƻ��", "����", "�㽶", "����", "����", "����", "����"};
	map<string, int> countMap;

	for (int i = 0; i< sizeof(fruit) / sizeof(fruit[0]); i++)
	{
		/*��һ�ַ������Ȳ��ٲ�
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
		//�ڶ��֣�����insert�ķ���ֵ��
		pair<map<string, int>::iterator, bool > pr = countMap.insert(pair<string,int>(fruit[i],1));
		if (pr.second == false)
		{
			(pr.first)->second++;
		}*/

		/*-------------------------
		�����֣�operator[];
		�ҵ��˷���second��value�����ã�
		û�ҵ������벢����value��value�ĳ�ʼֵΪĬ��ȱʡ�������ã�
		*/
		countMap[fruit[i]]++;
	}
	//PrintMap(countMap);
	/*-----------------------------
	topK�����⣻
	1.sort
	2.make_heap
	3.���ȼ�����
	*/

	/*//sort----------------------------------
	vector<map<string, int>::iterator> v;
	map<string, int>::iterator countIt = countMap.begin();
	while (countIt != countMap.end())
	{
		v.push_back(countIt);
		countIt++;
	}

	//�Ƚϵ���value��ֵ��
	struct Compare
	{
		bool operator()(map<string, int>::iterator l, map<string, int>::iterator r)
		{
			return l->second > r->second;
		}
	};

	sort(v.begin(),v.end(),Compare());
	*/

	/*//����-------------------------
	��С��
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

void TestMultimap() //�����ظ�key�Ĳ��룬û��[]���أ�û�����壻 
{
	multimap<string, string> dict;
	multimap<string, string>::iterator it;
	dict.insert(make_pair("world","��ǧ����"));
	dict.insert(make_pair("people", "ܿܿ����"));
	dict.insert(make_pair("world", "a����"));
	dict.insert(make_pair("world", "bС����"));
	dict.insert(make_pair("world", "cС����"));
	dict.insert(make_pair("world", "dС����"));
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
	1.�ж�һ�������ڲ��ڼ�����
	2.����
	3.ȥ�أ�

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