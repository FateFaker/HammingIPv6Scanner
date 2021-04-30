from icmplib import ping, multiping, traceroute, resolve, Host, Hop
import random
def isalias(ip):
    lastseg = len(ip)-1
    targets = []
    while ip[lastseg]!=":":
        lastseg-=1
    for i in range(16):
        temp = random.randint(0,16**4-1)
        targets.append(ip[:lastseg+1]+("%04x" % (temp)))
    hosts = multiping(targets,timeout=1)
    alive = 0
    for host in hosts:
        if host.is_alive:
            alive+=1
        else:
            print(str(host))
    if alive > 10:
        hosts = multiping(targets,timeout=2, count=3)
        alive = 0
        for host in hosts:
            if host.is_alive:
                alive+=1
            else:
                print(str(host))
    return alive

fin = open("./pattern_num.txt","r")
fout = open("./pattern_num_dealiased.txt","w")
fout1 = open("./fruit_pattern_global.txt","w")
fout2 = open("./alias_pattern.txt","w")
for line in fin:
    [pattern,num,sample] = line.strip().split("\t")
    num = int(num)
    sample =":".join([sample[0:4],sample[4:8],sample[8:12],sample[12:16],sample[16:20],sample[20:24],sample[24:28],sample[28:32]])
    if num == 0:
        continue
    if num >1000:
        res_num = isalias(sample)
    else:
        res_num = 0
    if res_num>13:
        fout2.write(str([pattern,num,sample])+"\n")
        continue
    print(str([pattern,num,res_num,sample]))
    fout.write("\t".join([pattern,str(num),sample])+"\n")
    fout1.write(pattern+"\n")

