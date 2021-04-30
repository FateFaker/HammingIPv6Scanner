#include <stdio.h>
#include <string.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <list>
using namespace std;
int hamming_dis(string a, string b)
{
	int x = 0;
	for (int i = 0; i < 32; ++i)
	{
		if (a[i] != b[i] || a[i] =='*'|| b[i] =='*')
			x++;
		if (x>8)
			break;
	}
	return x;
}

string extract_pattern(string a, string b)
{
	string x= "";
	for (int i = 0; i < 32; ++i)
	{
		if (a[i] != b[i])
		{
			x=x+'*';
		}
		else
			x = x+a[i];
	}
	return x;
}
int main()
{
	// cout << hamming_dis("20011284ffff00000000000000000044","20011284ffff00000000000000000006") <<endl;
	// return 0;
	ifstream fin("./seedlist_f.txt");
	if (!fin.is_open())
    {
        cout << "未成功打开文件" << endl;
    }
	list<string> seedlist;
	string ip;
	int temp = 0;
	while(getline(fin,ip))
    {
    	// cout << temp.size() << endl;
        if ((temp++)%1==0)
        	seedlist.push_back(ip);
    }
    cout << seedlist.size() <<endl;
    map<string, list<string> > pattern_set;
    int bestsegment[4][7] = {{20, 16, 29, 17, 30, 4, 6},{5, 7, 22, 21, 10, 15, 24},{31, 14, 13, 18, 12, 8, 19},{11, 9, 28, 25, 27, 26, 23}};
    for (int seg = 0;seg<4; seg++)
    	for (int diff = 0; diff <7; diff++)
    	{
    		map<string, list<list<string>::iterator > > bucket;
    		for (auto iterip =seedlist.begin(); iterip != seedlist.end(); ++iterip)
    		{
    			string signature=(*iterip).substr(0,4);

    			for (int i = 0; i <7; i++)
    				if (i!=diff)
    					signature+=(*iterip)[bestsegment[seg][i]];
    			// cout<< signature << endl;
    			if (signature.find("*")!= string::npos)
    				continue;
    			auto iter = bucket.find(signature);
    			if (iter!=bucket.end())
    			{
    				iter->second.push_back(iterip);
    			}
    			else{
    				bucket[signature] = list<list<string>::iterator >(1,iterip);
    				// list<string>::iterator iter;
    				// cout <<*bucket[signature].begin()<< endl;
    			}
    		}
			for (auto bucket_iter= bucket.begin();bucket_iter != bucket.end();++bucket_iter)
			{
				// cout << pattern_set.size() << endl;
				int ratio = bucket_iter->second.size()/1000;
				if (ratio==0)
					ratio = 1;
				if (ratio>1)
					cout << bucket_iter->first<<"\t"<<bucket_iter->second.size() << "\t" << pattern_set.size() << endl;
				for (auto iter1 = bucket_iter->second.begin();iter1 != bucket_iter->second.end();)
				{
					bool found_pattern = false;
					auto iter2 = iter1;
					for (++iter2;iter2 != bucket_iter->second.end();)
					{
						int dis = hamming_dis(**iter1,**iter2);
						if (dis <=8)
						{
							string pattern = extract_pattern(**iter1,**iter2);
							bool new_pattern = false;
							list<string> *target_list;
							if (pattern_set.find(pattern)==pattern_set.end())
							{
								// cout << "pattern: " << pattern << endl;
								new_pattern = true;
								pattern_set[pattern] = list<string>();
								target_list = &pattern_set[pattern];
								if ((**iter1).find("*")!= string::npos)
								{
									for (string ip : pattern_set[**iter1])
										target_list -> push_back(ip);
									pattern_set[**iter1].clear();
								}else
								{
									target_list -> push_back(**iter1);
								}
								// cout << "pattern_count: " << target_list->size() << endl;
								// cout << *iter1 << "\t" << *iter2 <<"\t" << dis << endl;
							}

							for (auto iter3 = bucket_iter->second.begin(); iter3 != bucket_iter->second.end();)
								if (iter3!= iter1 && hamming_dis(**iter3,pattern) <= dis)
								{
									if (new_pattern)
										if ((**iter3).find("*")!= string::npos)
										{
											for (string ip : pattern_set[**iter3])
												target_list -> push_back(ip);
											pattern_set[**iter3].clear();
										}else
										{
											target_list -> push_back(**iter3);
										}
									seedlist.erase(*iter3);
									iter3 = bucket_iter->second.erase(iter3);
								}
								else{
									++iter3;
								}
							**iter1 = pattern;
							found_pattern = true;
							// if (new_pattern)
							// 	cout << "pattern: " << pattern <<"\t" << target_list->size() << endl;
							break;
						}
						for(int i = 0;i<ratio &&iter2 != bucket_iter->second.end();i++ )
							++iter2;
					}
					if (!found_pattern)
						for(int i = 0;i<ratio &&iter1 != bucket_iter->second.end();i++ )
							++iter1;
				}
			}
    	}

    ofstream fout1("./pattern_set_size_global.txt", ios::out);
    fout1 <<"{";
    for (auto iter = pattern_set.begin(); iter != pattern_set.end(); ++iter)
    {
    	if (!iter->second.size())
    		continue;
    	fout1 << "\""<< iter->first << "\":";
    	fout1 << iter->second.size();
    	fout1 << ",";
    }
    fout1 <<"}";
    fout1.close();

    ofstream fout2("./pattern_set_size_global_dec.txt", ios::out);
    fout2 <<"{";
    map<string, list<string> > new_pattern_set;
    for (auto iter = pattern_set.begin(); iter != pattern_set.end(); ++iter)
    {
    	if (!iter->second.size())
    		continue;
    	int total = iter->second.size();
    	if (total< 10)
    		continue;
    	string pattern = iter->first;
    	auto temp = iter->second;
    	bool flag = false;
    	bool flag1 = false;
		for (int i = 4; i < 32; ++i)
			if (pattern[i] =='*' )
    		{
				int a[200];
				for (int j = 0; j<200; ++j)
					a[j] = 0;
				for (string ip : iter->second)
					a[int(ip[i])-int('0')]++;
				for (int j = 0; j<200; ++j)
					if (a[j]>total/2)
					{
						// flag1 = true;
						flag = true;
						pattern[i] = char(j+int('0'));
						for (auto it = iter->second.begin();it != iter->second.end();it++)
							while (it != iter->second.end() && (*it)[i] != pattern[i])
								it = iter->second.erase(it);
						break;
					}
    		}
    	if (flag)
    	{
    		fout2 << "\""<< pattern << "\":";
    		fout2 << iter->second.size();
    		fout2 << ",";
    		cout << iter->first << "\t" << pattern <<"\t" << total <<"\t"<< iter->second.size()<<endl;
    	}
    }
    fout2 <<"}";
    fout2.close();
	return 0;
}