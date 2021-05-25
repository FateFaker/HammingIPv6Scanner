# HammingIPv6Scanner
HammingIPv6Scanner learns patterns from IPv6 addresses, and use patterns for targets generation.
# Quick Start
To use pre-learned patterns in `pattern_gloabal.txt` for scanning:
  1. Install [ZMapv6](https://github.com/tumi8/zmap)
  2. Change working directory to this repository.
  3. build 
```
cmake .
make
```
  4. Run `./targets_generate -f pattern_gloabal.txt | zmap --ipv6-target-file=- --probe-module icmp6_echoscan` followed by other ZMap options

## targets_generate.cpp
Generates targets for scanning and write targets into stdout. 

## hamming.cpp
Generates patterns from IPv6 dataset.

Usage: 
  1. Prepare your IPv6 dataset in hex IP format (32 hex characters per line, no colons).
  2.
```
hamming -f <filename> -o <outputfile>
```
  filename is your IPv6 dataset in hex IP format (32 hex characters per line, no colons).

## IPv6 hitlist from scanning
109M responsive addresses
https://drive.google.com/file/d/1qWqJwH897pW1s5bS3NOCKMLvpZ4nyZy_/view?usp=sharing


## pre_scan_generate.py
Generate targets for pre-scanning, write targets into stdout.

## de_alias.py
Detects for aliased IPv6 addresses.

## ZMapv6
We recommend using ZMapv6 for Scanning

Source: [<github.com/tumi8/zmap>](https://github.com/tumi8/zmap)

## pattern_gloabal.txt
Patterns extracted from ipv6 hitlist, by https://ipv6hitlist.github.io.
