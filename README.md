# HammingIPv6Scanner
HammingIPv6Scanner learns patterns from IPv6 addresses, and use patterns for targets generation.
# Quick Start
Use pre-learned patterns in `pattern_gloabal.txt` for scanning
  1. Install ZMapv6 https://github.com/tumi8/zmap
  2. build `targets_generate.cpp`
  3. Change working directory to this repository.
  4. Run `./targets_generate pattern_gloabal.txt | zmap --ipv6-target-file=-` followed by other ZMap options


## targets_generate.cpp
Generates targets for scanning and write targets into Stdout. You can use ZMap with `--ipv6-target-file=-` to perform scanning.

## IPv6 hitlist from scanning
109M responsive addresses
https://drive.google.com/file/d/1qWqJwH897pW1s5bS3NOCKMLvpZ4nyZy_/view?usp=sharing

## hamming.cpp
Generates patterns from IPv6 dataset.
Usage: 
1.Prepare your IPv6 dataset in hex IP format (32 hex characters per line, no colons).
2.
```
hamming <filename>
```
filename is your IPv6 dataset in hex IP format (32 hex characters per line, no colons).

## pre_scan_generate.py
Generate targets for pre-scanning, write targets into Stdout.

## de_alias.py
Detects for aliased IPv6 addresses.

## ZMapv6
We recommend using  for Scanning
Source: <github.com/tumi8/zmap>

## pattern_gloabal.txt
Patterns extracted from ipv6 hitlist, by https://ipv6hitlist.github.io.
