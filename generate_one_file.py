import os
import sys
def hamming_dis(a,b):
	res = 0
	for i in range(32):
		if a[i]!=b[i]:
			res+=1
	return res
def contain(a,b):
	flag = True
	for i in range(32):
		if  a[i]!="*" and a[i]!=b[i]:
			flag=False
	return flag
def extract_pattern(a,b):
	res = ""
	for i in range(32):
		if a[i]!=b[i]:
			res += "*"
		else:
			res += a[i]
	return res

fin = open("./pattern_set_size_global.txt","r")
fin1 = open("./pattern_set_size_global_dec.txt","r")
new_pattern = eval(fin.read())
new_pattern_dec = eval(fin1.read())
new_pattern = [(x,new_pattern[x]) for x in new_pattern]+[(x,new_pattern_dec[x]) for x in new_pattern_dec]

new_pattern = sorted(new_pattern,key = lambda x:-x[1])
# pattern_count[50]
small_pattern=[]
count = 0
for pattern in new_pattern:
#     print pattern
    wildnum = 32-hamming_dis(pattern[0],"********************************")
    if wildnum>=1 and pattern[1]>=10:
        small_pattern.append((pattern[0],pattern[1]*(2**(8-wildnum)),pattern[1],wildnum))

small_pattern = sorted(small_pattern,key = lambda x:-x[1])
len(small_pattern)
len(small_pattern)

seed = 1
pattern_num = 0

fout = open("./pre_scan_target.txt","w")
for pattern_tur in small_pattern:
	pattern = pattern_tur[0]
	# print(pattern)
	pattern_num+=1
	wildnum = pattern_tur[3]
	targets_num = 10000
	if 16**wildnum<10000:
		targets_num = 16**wildnum
	for i in range(targets_num):
		seed = (seed+10000019)%(16**8)
		temp = ("%08x" % (seed))[8-wildnum:]
		k = 0
		new_address = ['*' for i in range(39)]
		top=0
		for j in range(32):
			if j%4==0 and j>0:
				new_address[top]=':'
				top+=1
			if pattern[j] == "*":
				new_address[top]=temp[k]
				top+=1
				k+=1
			else:
				new_address[top]=pattern[j]
				top+=1
		sys.stdout.write(''.join(new_address)+"\n")



