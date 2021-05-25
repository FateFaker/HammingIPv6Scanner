#include <stdio.h>
#include <string.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "cmdline.h"
using namespace std;
int main()
{
	// setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
 //    setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
    cmdline::parser a;
    a.add<string>("pattern-file", 'f', "pattern list for scanning", false, "pattern_gloabal.txt");
    a.add<int>("sampling-ratio", 'r', "sampling ratio for scanning", false, 1, cmdline::range(1, 65535));

    ifstream fin(a.get<string>("pattern-file"));
	if (!fin.is_open())
    {
        cout << "Can not open pattern file!" << endl;
		return 0;
    }
	int ratio = a.get<int>("sampling-ratio");
	string pattern_list[15000];
	long long targets_num[15000];
	string pattern;
	int n = 0;
	long long sum = 0;
	while(getline(fin,pattern))
    {
    	// cout << n.size() << endl;
        pattern_list[n++]=pattern;
        targets_num[n-1] = 0;
        for (int i = 0; i < 32; ++i)
        	if (pattern[i]=='*')
        		targets_num[n-1]++;
        targets_num[n-1] = (long long)1<<(4*targets_num[n-1]);
        sum+=targets_num[n-1];
        // cout << sum <<endl;
    }
    // cout << sum <<endl;
    // return 0;
    long long seed = 1;
    const char hex_arr[17] = "0123456789abcdef";

    for (long long q = 0; q < ((long long)1<<32); q++ )
    {
    	seed = (seed+10000019)%((long long)1<<32);
    	// seed = (seed+10000019)%((long long)1<<32);
    	// long long ttt = 0;
    	// ttt = (long long)1<<32;
    	// cout << seed <<endl;
    	// return 0;
    	for (int i = 0; i < n; i++)
    		if (q<targets_num[i]/ratio)
	    	{
	    		char temp[40] = "0000:0000:0000:0000:0000:0000:0000:0000";
	    		long long t = seed;
	    		for (int j = 0; j<39; ++j)
	    		{
	    			if (j%5 == 4)
	    				continue;
	    			int k = j -int(j/5);
	    			if (pattern_list[i][k]!='*')
	    				temp[j] = pattern_list[i][k];
	    			else
	    			{
	    				temp[j] = hex_arr[t%16];
	    				t = t >> 4;
	    			}
	    		}
	    		printf("%s\n",temp);
	    	}
    }
	return 0;
}
