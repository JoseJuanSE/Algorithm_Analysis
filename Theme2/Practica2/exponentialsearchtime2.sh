#!/bin/bash
gcc exponentialsearchtime2.c tiempo.c -o exponentialsearchtime2
./exponentialsearchtime2 1000000 < ordenados.txt > ExponentialSearchTime2.txt
./exponentialsearchtime2 2000000 < ordenados.txt >> ExponentialSearchTime2.txt
./exponentialsearchtime2 3000000 < ordenados.txt >> ExponentialSearchTime2.txt
./exponentialsearchtime2 4000000 < ordenados.txt >> ExponentialSearchTime2.txt
./exponentialsearchtime2 5000000 < ordenados.txt >> ExponentialSearchTime2.txt
./exponentialsearchtime2 6000000 < ordenados.txt >> ExponentialSearchTime2.txt
./exponentialsearchtime2 7000000 < ordenados.txt >> ExponentialSearchTime2.txt
./exponentialsearchtime2 8000000 < ordenados.txt >> ExponentialSearchTime2.txt
./exponentialsearchtime2 9000000 < ordenados.txt >> ExponentialSearchTime2.txt
./exponentialsearchtime2 10000000 < ordenados.txt >> ExponentialSearchTime2.txt
