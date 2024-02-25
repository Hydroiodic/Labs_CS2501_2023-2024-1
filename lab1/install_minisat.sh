#!/bin/bash

echo "Start installing minisat..."
sudo apt update
sudo apt install libc6=2.35-0ubuntu3 libc-bin=2.35-0ubuntu3 -y --allow-downgrades
sudo apt install zip build-essential -y --allow-downgrades
sudo apt install minisat zlib1g=1:1.2.11.dfsg-2ubuntu9 zlib1g-dev -y --allow-downgrades
sudo apt install 
echo "Installation complete"