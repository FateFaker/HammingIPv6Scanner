# HammingIPv6Scanning

## fruit_targets_generate.cpp
Generates targets for scanning. Outputs targets to Stdout. You can use ZMap with "--ipv6-target-file=-" to perform scanning.

## hamming.cpp
Usage:  hamming filename

Where filename is your IPv6 dataset in hex IP format (32 hex characters per line, no colons).

## generate_one_file.py
Generate targets for pre-scanning.

## de_alias.py
Detect for aliased IPv6 addresses.

## Use ZMapv6 for Scanning
Source: <github.com/tumi8/zmap>

## pattern_gloabal.txt
Patterns extracted from global IPv6 hitlist.
