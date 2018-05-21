//#include <bits/stdc++.h>
#include <bitset>
#include <immintrin.h>
#include <vector>
#include <array>
#include <limits>
//#include <iostream>
//using namespace std;

//typedef int T;
namespace quickdouble
{

__attribute__((aligned(64))) int PTL[16 * 8] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0,
    2, 3, 0, 0, 0, 0, 0, 0,
    0, 1, 2, 3, 0, 0, 0, 0,
    4, 5, 0, 0, 0, 0, 0, 0,
    0, 1, 4, 5, 0, 0, 0, 0,
    2, 3, 4, 5, 0, 0, 0, 0,
    0, 1, 2, 3, 4, 5, 0, 0,
    6, 7, 0, 0, 0, 0, 0, 0,
    0, 1, 6, 7, 0, 0, 0, 0,
    2, 3, 6, 7, 0, 0, 0, 0,
    0, 1, 2, 3, 6, 7, 0, 0,
    4, 5, 6, 7, 0, 0, 0, 0,
    0, 1, 4, 5, 6, 7, 0, 0,
    2, 3, 4, 5, 6, 7, 0, 0,
    0, 1, 2, 3, 4, 5, 6, 7};
__attribute__((aligned(64))) int PTR[16 * 8] = {
    0, 1, 2, 3, 4, 5, 6, 7,
    2, 3, 4, 5, 6, 7, 0, 0,
    0, 1, 4, 5, 6, 7, 0, 0,
    4, 5, 6, 7, 0, 0, 0, 0,
    0, 1, 2, 3, 6, 7, 0, 0,
    2, 3, 6, 7, 0, 0, 0, 0,
    0, 1, 6, 7, 0, 0, 0, 0,
    6, 7, 0, 0, 0, 0, 0, 0,
    0, 1, 2, 3, 4, 5, 0, 0,
    2, 3, 4, 5, 0, 0, 0, 0,
    0, 1, 4, 5, 0, 0, 0, 0,
    4, 5, 0, 0, 0, 0, 0, 0,
    0, 1, 2, 3, 0, 0, 0, 0,
    2, 3, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0};

__attribute__((aligned(64))) int PTL2[256 * 8] = {
0,0,0,0,0,0,0,0,	
0,0,0,0,0,0,0,0,	
1,0,0,0,0,0,0,0	,
0,1,0,0,0,0,0,0	,
2,0,0,0,0,0,0,0	,
0,2,0,0,0,0,0,0	,
1,2,0,0,0,0,0,0	,
0,1,2,0,0,0,0,0	,
3,0,0,0,0,0,0,0	,
0,3,0,0,0,0,0,0	,
1,3,0,0,0,0,0,0	,
0,1,3,0,0,0,0,0,
0,2,3,0,0,0,0,0 , 
1,2,3,0,0,0,0,0  ,
0,1,2,3,0,0,0,0  ,
4,0,0,0,0,0,0,0  ,
0,4,0,0,0,0,0,0  ,
1,4,0,0,0,0,0,0  ,
0,1,4,0,0,0,0,0  ,
2,4,0,0,0,0,0,0  ,
0,2,4,0,0,0,0,0  ,
1,2,4,0,0,0,0,0  ,
0,1,2,4,0,0,0,0  ,
3,4,0,0,0,0,0,0  ,
0,3,4,0,0,0,0,0  ,
1,3,4,0,0,0,0,0  ,
0,1,3,4,0,0,0,0  ,
2,3,4,0,0,0,0,0  ,
0,2,3,4,0,0,0,0  ,
1,2,3,4,0,0,0,0  ,
0,1,2,3,4,0,0,0  ,
5,0,0,0,0,0,0,0  ,
0,5,0,0,0,0,0,0  ,
1,5,0,0,0,0,0,0  ,
0,1,5,0,0,0,0,0  ,
2,5,0,0,0,0,0,0  ,
0,2,5,0,0,0,0,0  ,
1,2,5,0,0,0,0,0  ,
0,1,2,5,0,0,0,0  ,
3,5,0,0,0,0,0,0  ,
0,3,5,0,0,0,0,0  ,
1,3,5,0,0,0,0,0  ,
0,1,3,5,0,0,0,0  ,
2,3,5,0,0,0,0,0  ,
0,2,3,5,0,0,0,0  ,
1,2,3,5,0,0,0,0  ,
0,1,2,3,5,0,0,0  ,
4,5,0,0,0,0,0,0  ,
0,4,5,0,0,0,0,0  ,
1,4,5,0,0,0,0,0  ,
0,1,4,5,0,0,0,0  ,
2,4,5,0,0,0,0,0  ,
0,2,4,5,0,0,0,0  ,
1,2,4,5,0,0,0,0  ,
0,1,2,4,5,0,0,0  ,
3,4,5,0,0,0,0,0  ,
0,3,4,5,0,0,0,0  ,
1,3,4,5,0,0,0,0  ,
0,1,3,4,5,0,0,0  ,
2,3,4,5,0,0,0,0  ,
0,2,3,4,5,0,0,0  ,
1,2,3,4,5,0,0,0  ,
0,1,2,3,4,5,0,0  ,
6,0,0,0,0,0,0,0  ,
0,6,0,0,0,0,0,0  ,
1,6,0,0,0,0,0,0  ,
0,1,6,0,0,0,0,0  ,
2,6,0,0,0,0,0,0  ,
0,2,6,0,0,0,0,0  ,
1,2,6,0,0,0,0,0  ,
0,1,2,6,0,0,0,0  ,
3,6,0,0,0,0,0,0  ,
0,3,6,0,0,0,0,0  ,
1,3,6,0,0,0,0,0  ,
0,1,3,6,0,0,0,0  ,
2,3,6,0,0,0,0,0  ,
0,2,3,6,0,0,0,0  ,
1,2,3,6,0,0,0,0  ,
0,1,2,3,6,0,0,0  ,
4,6,0,0,0,0,0,0  ,
0,4,6,0,0,0,0,0  ,
1,4,6,0,0,0,0,0  ,
0,1,4,6,0,0,0,0  ,
2,4,6,0,0,0,0,0  ,
0,2,4,6,0,0,0,0  ,
1,2,4,6,0,0,0,0  ,
0,1,2,4,6,0,0,0  ,
3,4,6,0,0,0,0,0  ,
0,3,4,6,0,0,0,0  ,
1,3,4,6,0,0,0,0  ,
0,1,3,4,6,0,0,0  ,
2,3,4,6,0,0,0,0  ,
0,2,3,4,6,0,0,0  ,
1,2,3,4,6,0,0,0  ,
0,1,2,3,4,6,0,0  ,
5,6,0,0,0,0,0,0  ,
0,5,6,0,0,0,0,0  ,
1,5,6,0,0,0,0,0  ,
0,1,5,6,0,0,0,0  ,
2,5,6,0,0,0,0,0  ,
0,2,5,6,0,0,0,0,
1,2,5,6,0,0,0,0,
0,1,2,5,6,0,0,0,
3,5,6,0,0,0,0,0,
0,3,5,6,0,0,0,0,
1,3,5,6,0,0,0,0,
0,1,3,5,6,0,0,0,
2,3,5,6,0,0,0,0,
0,2,3,5,6,0,0,0,
1,2,3,5,6,0,0,0,
0,1,2,3,5,6,0,0,
4,5,6,0,0,0,0,0,
0,4,5,6,0,0,0,0,
1,4,5,6,0,0,0,0,
0,1,4,5,6,0,0,0,
2,4,5,6,0,0,0,0,
0,2,4,5,6,0,0,0,
1,2,4,5,6,0,0,0,
0,1,2,4,5,6,0,0,
3,4,5,6,0,0,0,0,
0,3,4,5,6,0,0,0,
1,3,4,5,6,0,0,0,
0,1,3,4,5,6,0,0,
2,3,4,5,6,0,0,0,
0,2,3,4,5,6,0,0,
1,2,3,4,5,6,0,0,
0,1,2,3,4,5,6,0,
7,0,0,0,0,0,0,0,
0,7,0,0,0,0,0,0,
1,7,0,0,0,0,0,0,
0,1,7,0,0,0,0,0,
2,7,0,0,0,0,0,0,
0,2,7,0,0,0,0,0,
1,2,7,0,0,0,0,0,
0,1,2,7,0,0,0,0,
3,7,0,0,0,0,0,0,
0,3,7,0,0,0,0,0,
1,3,7,0,0,0,0,0,
0,1,3,7,0,0,0,0,
2,3,7,0,0,0,0,0,
0,2,3,7,0,0,0,0,
1,2,3,7,0,0,0,0,
0,1,2,3,7,0,0,0,
4,7,0,0,0,0,0,0,
0,4,7,0,0,0,0,0,
1,4,7,0,0,0,0,0,
0,1,4,7,0,0,0,0,
2,4,7,0,0,0,0,0,
0,2,4,7,0,0,0,0,
1,2,4,7,0,0,0,0,
0,1,2,4,7,0,0,0,
3,4,7,0,0,0,0,0,
0,3,4,7,0,0,0,0,
1,3,4,7,0,0,0,0,
0,1,3,4,7,0,0,0,
2,3,4,7,0,0,0,0,
0,2,3,4,7,0,0,0,
1,2,3,4,7,0,0,0,
0,1,2,3,4,7,0,0,
5,7,0,0,0,0,0,0,
0,5,7,0,0,0,0,0,
1,5,7,0,0,0,0,0,
0,1,5,7,0,0,0,0,
2,5,7,0,0,0,0,0,
0,2,5,7,0,0,0,0,
1,2,5,7,0,0,0,0,
0,1,2,5,7,0,0,0,
3,5,7,0,0,0,0,0,
0,3,5,7,0,0,0,0,
1,3,5,7,0,0,0,0,
0,1,3,5,7,0,0,0,
2,3,5,7,0,0,0,0,
0,2,3,5,7,0,0,0,
1,2,3,5,7,0,0,0,
0,1,2,3,5,7,0,0,
4,5,7,0,0,0,0,0,
0,4,5,7,0,0,0,0,
1,4,5,7,0,0,0,0,
0,1,4,5,7,0,0,0,
2,4,5,7,0,0,0,0,
0,2,4,5,7,0,0,0,
1,2,4,5,7,0,0,0,
0,1,2,4,5,7,0,0,
3,4,5,7,0,0,0,0,
0,3,4,5,7,0,0,0,
1,3,4,5,7,0,0,0,
0,1,3,4,5,7,0,0,
2,3,4,5,7,0,0,0,
0,2,3,4,5,7,0,0,
1,2,3,4,5,7,0,0,
0,1,2,3,4,5,7,0,
6,7,0,0,0,0,0,0,
0,6,7,0,0,0,0,0,
1,6,7,0,0,0,0,0,
0,1,6,7,0,0,0,0,
2,6,7,0,0,0,0,0,
0,2,6,7,0,0,0,0,
1,2,6,7,0,0,0,0,
0,1,2,6,7,0,0,0,
3,6,7,0,0,0,0,0,
0,3,6,7,0,0,0,0,
1,3,6,7,0,0,0,0,
0,1,3,6,7,0,0,0,
2,3,6,7,0,0,0,0,
0,2,3,6,7,0,0,0,
1,2,3,6,7,0,0,0,
0,1,2,3,6,7,0,0,
4,6,7,0,0,0,0,0,
0,4,6,7,0,0,0,0,
1,4,6,7,0,0,0,0,
0,1,4,6,7,0,0,0,
2,4,6,7,0,0,0,0,
0,2,4,6,7,0,0,0,
1,2,4,6,7,0,0,0,
0,1,2,4,6,7,0,0,
3,4,6,7,0,0,0,0,
0,3,4,6,7,0,0,0,
1,3,4,6,7,0,0,0,
0,1,3,4,6,7,0,0,
2,3,4,6,7,0,0,0,
0,2,3,4,6,7,0,0,
1,2,3,4,6,7,0,0,
0,1,2,3,4,6,7,0,
5,6,7,0,0,0,0,0,
0,5,6,7,0,0,0,0,
1,5,6,7,0,0,0,0,
0,1,5,6,7,0,0,0,
2,5,6,7,0,0,0,0,
0,2,5,6,7,0,0,0,
1,2,5,6,7,0,0,0,
0,1,2,5,6,7,0,0,
3,5,6,7,0,0,0,0,
0,3,5,6,7,0,0,0,
1,3,5,6,7,0,0,0,
0,1,3,5,6,7,0,0,
2,3,5,6,7,0,0,0,
0,2,3,5,6,7,0,0,
1,2,3,5,6,7,0,0,
0,1,2,3,5,6,7,0,
4,5,6,7,0,0,0,0,
0,4,5,6,7,0,0,0,
1,4,5,6,7,0,0,0,
0,1,4,5,6,7,0,0,
2,4,5,6,7,0,0,0,
0,2,4,5,6,7,0,0,
1,2,4,5,6,7,0,0,
0,1,2,4,5,6,7,0,
3,4,5,6,7,0,0,0,
0,3,4,5,6,7,0,0,
1,3,4,5,6,7,0,0,
0,1,3,4,5,6,7,0,
2,3,4,5,6,7,0,0,
0,2,3,4,5,6,7,0,
1,2,3,4,5,6,7,0,
0,1,2,3,4,5,6,7};

__attribute__((aligned(64))) int PTR2[256 * 8] = {
 0,1,2,3,4,5,6,7 , 
 1,2,3,4,5,6,7,0 , 
 0,2,3,4,5,6,7,0 , 
 2,3,4,5,6,7,0,0 , 
 0,1,3,4,5,6,7,0 , 
 1,3,4,5,6,7,0,0 , 
 0,3,4,5,6,7,0,0 , 
 3,4,5,6,7,0,0,0 , 
 0,1,2,4,5,6,7,0 , 
 1,2,4,5,6,7,0,0 , 
 0,2,4,5,6,7,0,0 , 
 2,4,5,6,7,0,0,0 , 
 0,1,4,5,6,7,0,0 , 
 1,4,5,6,7,0,0,0 , 
 0,4,5,6,7,0,0,0 , 
 4,5,6,7,0,0,0,0 , 
 0,1,2,3,5,6,7,0 , 
 1,2,3,5,6,7,0,0 , 
 0,2,3,5,6,7,0,0 , 
 2,3,5,6,7,0,0,0 , 
 0,1,3,5,6,7,0,0 , 
 1,3,5,6,7,0,0,0 , 
 0,3,5,6,7,0,0,0 , 
 3,5,6,7,0,0,0,0 , 
 0,1,2,5,6,7,0,0 , 
 1,2,5,6,7,0,0,0 , 
 0,2,5,6,7,0,0,0 , 
 2,5,6,7,0,0,0,0 , 
 0,1,5,6,7,0,0,0 , 
 1,5,6,7,0,0,0,0 , 
 0,5,6,7,0,0,0,0 , 
 5,6,7,0,0,0,0,0 , 
 0,1,2,3,4,6,7,0 , 
 1,2,3,4,6,7,0,0 , 
 0,2,3,4,6,7,0,0 , 
 2,3,4,6,7,0,0,0 , 
 0,1,3,4,6,7,0,0 , 
 1,3,4,6,7,0,0,0 , 
 0,3,4,6,7,0,0,0 , 
 3,4,6,7,0,0,0,0 , 
 0,1,2,4,6,7,0,0 , 
 1,2,4,6,7,0,0,0 , 
 0,2,4,6,7,0,0,0 , 
 2,4,6,7,0,0,0,0 , 
 0,1,4,6,7,0,0,0 , 
 1,4,6,7,0,0,0,0 , 
 0,4,6,7,0,0,0,0 , 
 4,6,7,0,0,0,0,0 , 
 0,1,2,3,6,7,0,0 , 
 1,2,3,6,7,0,0,0 , 
 0,2,3,6,7,0,0,0 , 
 2,3,6,7,0,0,0,0 , 
 0,1,3,6,7,0,0,0 , 
 1,3,6,7,0,0,0,0 , 
 0,3,6,7,0,0,0,0 , 
 3,6,7,0,0,0,0,0 , 
 0,1,2,6,7,0,0,0 , 
 1,2,6,7,0,0,0,0 , 
 0,2,6,7,0,0,0,0 , 
 2,6,7,0,0,0,0,0 , 
 0,1,6,7,0,0,0,0 , 
 1,6,7,0,0,0,0,0 , 
 0,6,7,0,0,0,0,0 , 
 6,7,0,0,0,0,0,0 , 
 0,1,2,3,4,5,7,0 , 
 1,2,3,4,5,7,0,0 , 
 0,2,3,4,5,7,0,0 , 
 2,3,4,5,7,0,0,0 , 
 0,1,3,4,5,7,0,0 , 
 1,3,4,5,7,0,0,0 , 
 0,3,4,5,7,0,0,0 , 
 3,4,5,7,0,0,0,0 , 
 0,1,2,4,5,7,0,0 , 
 1,2,4,5,7,0,0,0 , 
 0,2,4,5,7,0,0,0 , 
 2,4,5,7,0,0,0,0 , 
 0,1,4,5,7,0,0,0 , 
 1,4,5,7,0,0,0,0 , 
 0,4,5,7,0,0,0,0 , 
 4,5,7,0,0,0,0,0 , 
 0,1,2,3,5,7,0,0 , 
 1,2,3,5,7,0,0,0 , 
 0,2,3,5,7,0,0,0 , 
 2,3,5,7,0,0,0,0 , 
 0,1,3,5,7,0,0,0 , 
 1,3,5,7,0,0,0,0 , 
 0,3,5,7,0,0,0,0 , 
 3,5,7,0,0,0,0,0 ,  
 0,1,2,5,7,0,0,0 , 
 1,2,5,7,0,0,0,0 , 
 0,2,5,7,0,0,0,0 , 
 2,5,7,0,0,0,0,0 , 
 0,1,5,7,0,0,0,0 , 
 1,5,7,0,0,0,0,0 , 
 0,5,7,0,0,0,0,0 , 
 5,7,0,0,0,0,0,0 , 
 0,1,2,3,4,7,0,0 , 
 1,2,3,4,7,0,0,0 , 
 0,2,3,4,7,0,0,0 , 
 2,3,4,7,0,0,0,0 , 
 0,1,3,4,7,0,0,0 ,  
 1,3,4,7,0,0,0,0 ,  
 0,3,4,7,0,0,0,0 ,  
 3,4,7,0,0,0,0,0 , 
 0,1,2,4,7,0,0,0 , 
 1,2,4,7,0,0,0,0 , 
 0,2,4,7,0,0,0,0 , 
 2,4,7,0,0,0,0,0 , 
 0,1,4,7,0,0,0,0 , 
 1,4,7,0,0,0,0,0 , 
 0,4,7,0,0,0,0,0 , 
 4,7,0,0,0,0,0,0 , 
 0,1,2,3,7,0,0,0 , 
 1,2,3,7,0,0,0,0 , 
 0,2,3,7,0,0,0,0 , 
 2,3,7,0,0,0,0,0 , 
 0,1,3,7,0,0,0,0 , 
 1,3,7,0,0,0,0,0 , 
 0,3,7,0,0,0,0,0 , 
 3,7,0,0,0,0,0,0 , 
 0,1,2,7,0,0,0,0 , 
 1,2,7,0,0,0,0,0 , 
 0,2,7,0,0,0,0,0 , 
 2,7,0,0,0,0,0,0 , 
 0,1,7,0,0,0,0,0 , 
 1,7,0,0,0,0,0,0 , 
 0,7,0,0,0,0,0,0 , 
 7,0,0,0,0,0,0,0 , 
 0,1,2,3,4,5,6,0 , 
 1,2,3,4,5,6,0,0 , 
 0,2,3,4,5,6,0,0 , 
 2,3,4,5,6,0,0,0 , 
 0,1,3,4,5,6,0,0 , 
 1,3,4,5,6,0,0,0 , 
 0,3,4,5,6,0,0,0 , 
 3,4,5,6,0,0,0,0 , 
 0,1,2,4,5,6,0,0 , 
 1,2,4,5,6,0,0,0 , 
 0,2,4,5,6,0,0,0 , 
 2,4,5,6,0,0,0,0 , 
 0,1,4,5,6,0,0,0 , 
 1,4,5,6,0,0,0,0 , 
 0,4,5,6,0,0,0,0 , 
 4,5,6,0,0,0,0,0 , 
 0,1,2,3,5,6,0,0 , 
 1,2,3,5,6,0,0,0 , 
 0,2,3,5,6,0,0,0 , 
 2,3,5,6,0,0,0,0 , 
 0,1,3,5,6,0,0,0 , 
 1,3,5,6,0,0,0,0 , 
 0,3,5,6,0,0,0,0 , 
 3,5,6,0,0,0,0,0 , 
 0,1,2,5,6,0,0,0 , 
 1,2,5,6,0,0,0,0 , 
 0,2,5,6,0,0,0,0 , 
 2,5,6,0,0,0,0,0 , 
 0,1,5,6,0,0,0,0 , 
 1,5,6,0,0,0,0,0 , 
 0,5,6,0,0,0,0,0 , 
 5,6,0,0,0,0,0,0 , 
 0,1,2,3,4,6,0,0 , 
 1,2,3,4,6,0,0,0 , 
 0,2,3,4,6,0,0,0 , 
 2,3,4,6,0,0,0,0 , 
 0,1,3,4,6,0,0,0 , 
 1,3,4,6,0,0,0,0 , 
 0,3,4,6,0,0,0,0 , 
 3,4,6,0,0,0,0,0 , 
 0,1,2,4,6,0,0,0 , 
 1,2,4,6,0,0,0,0 , 
 0,2,4,6,0,0,0,0 , 
 2,4,6,0,0,0,0,0 , 
 0,1,4,6,0,0,0,0 , 
 1,4,6,0,0,0,0,0 , 
 0,4,6,0,0,0,0,0 , 
 4,6,0,0,0,0,0,0 , 
 0,1,2,3,6,0,0,0 , 
 1,2,3,6,0,0,0,0 , 
 0,2,3,6,0,0,0,0 , 
 2,3,6,0,0,0,0,0 , 
 0,1,3,6,0,0,0,0 , 
 1,3,6,0,0,0,0,0 , 
 0,3,6,0,0,0,0,0 , 
 3,6,0,0,0,0,0,0 , 
 0,1,2,6,0,0,0,0 , 
 1,2,6,0,0,0,0,0 , 
 0,2,6,0,0,0,0,0 , 
 2,6,0,0,0,0,0,0 , 
 0,1,6,0,0,0,0,0 , 
 1,6,0,0,0,0,0,0 , 
 0,6,0,0,0,0,0,0 , 
 6,0,0,0,0,0,0,0 , 
 0,1,2,3,4,5,0,0 , 
 1,2,3,4,5,0,0,0 , 
 0,2,3,4,5,0,0,0 , 
 2,3,4,5,0,0,0,0 , 
 0,1,3,4,5,0,0,0 , 
 1,3,4,5,0,0,0,0 , 
 0,3,4,5,0,0,0,0 , 
 3,4,5,0,0,0,0,0 , 
 0,1,2,4,5,0,0,0 , 
 1,2,4,5,0,0,0,0 , 
 0,2,4,5,0,0,0,0 , 
 2,4,5,0,0,0,0,0 , 
 0,1,4,5,0,0,0,0 , 
 1,4,5,0,0,0,0,0 , 
 0,4,5,0,0,0,0,0 , 
 4,5,0,0,0,0,0,0 , 
 0,1,2,3,5,0,0,0 , 
 1,2,3,5,0,0,0,0 , 
 0,2,3,5,0,0,0,0 , 
 2,3,5,0,0,0,0,0 , 
 0,1,3,5,0,0,0,0 , 
 1,3,5,0,0,0,0,0 , 
 0,3,5,0,0,0,0,0 , 
 3,5,0,0,0,0,0,0 , 
 0,1,2,5,0,0,0,0 , 
 1,2,5,0,0,0,0,0 , 
 0,2,5,0,0,0,0,0 , 
 2,5,0,0,0,0,0,0 , 
 0,1,5,0,0,0,0,0 , 
 1,5,0,0,0,0,0,0 , 
 0,5,0,0,0,0,0,0 , 
 5,0,0,0,0,0,0,0 , 
 0,1,2,3,4,0,0,0 , 
 1,2,3,4,0,0,0,0 , 
 0,2,3,4,0,0,0,0 , 
 2,3,4,0,0,0,0,0 , 
 0,1,3,4,0,0,0,0 , 
 1,3,4,0,0,0,0,0 , 
 0,3,4,0,0,0,0,0 , 
 3,4,0,0,0,0,0,0 , 
 0,1,2,4,0,0,0,0 , 
 1,2,4,0,0,0,0,0 , 
 0,2,4,0,0,0,0,0 , 
 2,4,0,0,0,0,0,0 , 
 0,1,4,0,0,0,0,0 , 
 1,4,0,0,0,0,0,0 , 
 0,4,0,0,0,0,0,0 , 
 4,0,0,0,0,0,0,0 , 
 0,1,2,3,0,0,0,0 , 
 1,2,3,0,0,0,0,0 , 
 0,2,3,0,0,0,0,0 , 
 2,3,0,0,0,0,0,0 , 
 0,1,3,0,0,0,0,0 , 
 1,3,0,0,0,0,0,0 , 
 0,3,0,0,0,0,0,0 , 
 3,0,0,0,0,0,0,0 , 
 0,1,2,0,0,0,0,0 , 
 1,2,0,0,0,0,0,0 , 
 0,2,0,0,0,0,0,0 , 
 2,0,0,0,0,0,0,0 , 
 0,1,0,0,0,0,0,0 , 
 1,0,0,0,0,0,0,0 , 
 0,0,0,0,0,0,0,0 , 
 0,0,0,0,0,0,0,0

};



template <typename T>
static void insertion_sort(T *d, unsigned long n)
{
    if (n <= 1)
        return;
    long i, j;
    for (i = 1; i < n; i++)
    {
        T tmp = d[i];
        for (j = i; j >= 1 && tmp < d[j - 1]; j--)
            d[j] = d[j - 1];
        d[j] = tmp;
    }
}

// SIMD AVX instructions for double
void part(int l, double *&in, std::array<__m256d, 8> &A,
          std::array<__m256d, 8> &M, // a temporary, no idea why it's an argument or an array since it's always written to before it's used. Maybe it's an array to allow for multi-threading?
                                     // Don't see how multi-threading can work with the below since it seems to rely on the sequentially updated top and bottom array bounds.
          __m256i *&PermTableLeft, // not sure why these are arguments, they're global and AFAICT they aren't mutated
          __m256i *&PermTableRight, // see above
          __m256d &PIVOT, // a four-double pivot
          std::array<unsigned long, 8> &mask, // effectively storage for 4 bools, not sure why it's an array
          double *&bottom,
          double *&top)
{
    for (int i = 0; i < l; ++i)
    {
        A[i] = _mm256_loadu_pd(in + i * 4); // load 4 doubles
        M[i] = _mm256_cmp_pd(A[i], PIVOT, 2); // compare them to the pivot 4 doubles using less-than
        mask[i] = _mm256_movemask_pd(M[i]); // effectively cast the comparison result to 4 bools

        // Parition the 4 doubles into less-than (M) and greater-or-equal-to (A).
        M[i] = (__m256d)_mm256_permutevar8x32_ps((__m256)A[i], PermTableLeft[mask[i]]);
        A[i] = (__m256d)_mm256_permutevar8x32_ps((__m256)A[i], PermTableRight[mask[i]]);

        // Find the number moved to less-than
        mask[i] = __builtin_popcount(mask[i]);

        // Store unaligned the separated values in the extremes of the array.
        _mm256_storeu_pd(bottom, M[i]);
        _mm256_storeu_pd(top, A[i]);

        // Shift the ends of the array inward by the number of elements stored.
        bottom += mask[i];
        mask[i] = 4 - mask[i];
        top += mask[i];
    }
    in += l * 4;
}

// SIMD AVX instructions for float
void part(int l, float *&in, std::array<__m256, 8> &A,
          std::array<__m256, 8> &M,
          __m256i *&PermTableLeft,
          __m256i *&PermTableRight,
          __m256 &PIVOT,
          std::array<unsigned long, 16> &mask,
          float *&bottom,
          float *&top,unsigned long &n)
{
    __m256 shuf[256];
int adv[256];

    int lefti = 0, righti = n;
    righti -= 8;
    for (int i = 0; i < l; ++i)
    {
    //     A[i] = _mm256_loadu_ps(in + i * 8);
    //     M[i] = _mm256_cmp_ps(A[i], PIVOT, 2);
    //     mask[i] = _mm256_movemask_ps(M[i]);
    //     // M[i] = (__m256)_mm256_permutevar8x32_ps((__m256)A[i], PermTableLeft[mask[i]]);
    //     // A[i] = (__m256)_mm256_permutevar8x32_ps((__m256)A[i], PermTableRight[mask[i]]);

    //     M[i] = _mm256_permutevar8x32_ps(A[i], PermTableLeft[mask[i]]);
    //     //A[i] = _mm256_permutevar8x32_epi32(A[i], PermTableRight[mask[i]]);

    //     mask[i] = __builtin_popcount(mask[i]);
    //     _mm256_storeu_ps(bottom, M[i]);
    //    _mm256_storeu_ps(top, M[i]);
    //     bottom += mask[i];
    //     mask[i] = 8 - mask[i];
    //     top += mask[i];
        __m256 vals = _mm256_loadu_ps(in + i * 8); // Load 256-bits (composed of 8 packed single-precision (32-bit) floating-point elements) from memory into dst
        __m256 cm = _mm256_cmp_ps(PIVOT,vals, 14); // Compare packed 32-bit integers in a and b for greater-than, and store the results in dst.
        int mask = _mm256_movemask_ps((__m256)cm); //Set each bit of mask dst based on the most significant bit of the corresponding packed single-precision (32-bit) floating-point element in a.
        vals = _mm256_permutevar8x32_ps(vals, (__m256i)shuf[mask]); // Shuffle 32-bit integers in a across lanes using the corresponding index in idx, and store the results in dst.
        int ad = adv[mask];
        _mm256_storeu_ps(bottom, vals); // Store 256-bits (composed of 8 packed single-precision (32-bit) floating-point elements) from a into memory.
        _mm256_storeu_ps(top, vals);
        // lefti += ad;
        // righti -= 8 - ad;
        // i += 8;

    }
    in += l * 8;
    n -= 7 * 8;
}

// SIMD AVX instructions for double
int qsort_AVX2(double *in, double *tmp, unsigned long n)
{
    std::array<__m256d, 8> A;
    std::array<__m256d, 8> M;

    __m256d T;
    __m256d PIVOT;
    double pivot;

    double *bottom = in;
    double *top = tmp;

    std::array<unsigned long, 8> mask;
    unsigned long ret_val;

    __m256i *PermTableLeft = (__m256i *)PTL;
    __m256i *PermTableRight = (__m256i *)PTR;



// median of three
#define swap(a, b, t) \
    t = a;            \
    a = b;            \
    b = t;
#define el1 in[0]
#define el2 in[n - 1]
#define el3 in[n / 2]

    if (el1 > el2)
    {
        swap(el1, el2, pivot);
    }
    if (el2 > el3)
    {
        swap(el2, el3, pivot);
        if (el1 > el2)
        {
            swap(el1, el2, pivot);
        }
    }
    pivot = el2;

    // Duplicates the pivot value 4 times into the vector version.
    PIVOT = _mm256_broadcast_sd(&pivot);
    //PIVOT = _mm256_set1_pd(pivot);

    //     while (n >= 8 * 4)
    // {
    //     part(8, in, A, M, PermTableLeft, PermTableRight, PIVOT, mask, bottom, top);
    //     n -= 8 * 4;
    // }

    // All of these while loops that call part seem unnecessary if part just looped through as many as were available.
    // The only necessary part of these is the loop below that handles the less-than-4 remainder that can't be vectorized.
    while (n >= 7 * 4)
    {
        part(7, in, A, M, PermTableLeft, PermTableRight, PIVOT, mask, bottom, top);
        n -= 7 * 4;
    }

    while (n >= 6 * 4)
    {
        part(6, in, A, M, PermTableLeft, PermTableRight, PIVOT, mask, bottom, top);
        n -= 6 * 4;
    }

    while (n >= 5 * 4)
    {
        part(5, in, A, M, PermTableLeft, PermTableRight, PIVOT, mask, bottom, top);
        n -= 20;
    }

    while (n >= 4 * 4)
    {
        part(4, in, A, M, PermTableLeft, PermTableRight, PIVOT, mask, bottom, top);
        n -= 16;
    }

    while (n >= 12)
    {
        part(3, in, A, M, PermTableLeft, PermTableRight, PIVOT, mask, bottom, top);
        n -= 12;
    }

    while (n >= 8)
    {
        part(2, in, A, M, PermTableLeft, PermTableRight, PIVOT, mask, bottom, top);
        n -= 8;
    }

    while (n >= 4)
    {
        part(1, in, A, M, PermTableLeft, PermTableRight, PIVOT, mask, bottom, top);
        n -= 4;
    }

    // This handles the remainder of elements that can't be vectorized.
    while (n > 0)
    {
        if (in[0] <= pivot)
        {
            bottom[0] = in[0];
            bottom += 1;
            in += 1;
            n--;
        }
        else
        {
            top[0] = in[0];
            top += 1;
            in += 1;
            n--;
        }
    }

    // The top is written into a temporary since the vector instructions would otherwise result in 'overlap' and therefore corruption.
    // These are then copied back into the main array.
    ret_val = ((uint64_t)top - (uint64_t)tmp) / 8;
    if (ret_val)
        memcpy(bottom, tmp, ret_val * 8);

    return ret_val;
}

// SIMD AVX instructions for float
int qsort_AVX2(float *in, float *tmp, unsigned long n)
{
    std::array<__m256, 8> A;
    std::array<__m256, 8> M;
    __m256 T;
    __m256 PIVOT;
    float pivot;

    float *bottom = in;
    float *top = tmp;

    std::array<unsigned long, 16> mask;
    unsigned long ret_val;

    __m256i *PermTableLeft = (__m256i *)PTL2;
    __m256i *PermTableRight = (__m256i *)PTR2;



// median of three
#define swap(a, b, t) \
    t = a;            \
    a = b;            \
    b = t;
#define el1 in[0]
#define el2 in[n - 1]
#define el3 in[n / 2]

    if (el1 > el2)
    {
        swap(el1, el2, pivot);
    }
    if (el2 > el3)
    {
        swap(el2, el3, pivot);
        if (el1 > el2)
        {
            swap(el1, el2, pivot);
        }
    }
    pivot = el2;

    PIVOT = _mm256_broadcast_ss(&pivot);
    //PIVOT = _mm256_set1_ps(pivot);

    //     while (n >= 8 * 8)
    // {
    //     part(7, in, A, M, PermTableLeft, PermTableRight, PIVOT, mask, bottom, top);
    //     n -= 8 * 8;
    // }

    while (n >= 7 * 8)
    {
        part(7, in, A, M, PermTableLeft, PermTableRight, PIVOT, mask, bottom, top, n);

    }

    // while (n >= 6 * 8)
    // {
    //     part(6, in, A, M, PermTableLeft, PermTableRight, PIVOT, mask, bottom, top);
    //     n -= 6 * 8;
    // }

    // while (n >= 5 * 8)
    // {
    //     part(5, in, A, M, PermTableLeft, PermTableRight, PIVOT, mask, bottom, top);
    //     n -= 5 * 8;
    // }

    // while (n >= 4 * 8)
    // {
    //     part(4, in, A, M, PermTableLeft, PermTableRight, PIVOT, mask, bottom, top);
    //     n -= 4 * 8;
    // }

    // while (n >= 3 * 8)
    // {
    //     part(3, in, A, M, PermTableLeft, PermTableRight, PIVOT, mask, bottom, top);
    //     n -= 3 * 8;
    // }

    // while (n >= 2*8)
    // {
    //     part(2, in, A, M, PermTableLeft, PermTableRight, PIVOT, mask, bottom, top);
    //     n -= 2 * 8;
    // }

    // while (n >= 1 * 8)
    // {
    //     part(1, in, A, M, PermTableLeft, PermTableRight, PIVOT, mask, bottom, top);
    //     n -= 1 * 8;
    // }

    while (n > 0)
    {
        if (in[0] <= pivot)
        {
            bottom[0] = in[0];
            bottom += 1;
            in += 1;
            n--;
        }
        else
        {
            top[0] = in[0];
            top += 1;
            in += 1;
            n--;
        }
    }

    ret_val = ((uint64_t)top - (uint64_t)tmp) / 8;
    if (ret_val)
        memcpy(bottom, tmp, ret_val * 8);

    return ret_val;
}

template <typename T>
void my_qsort_AVX2(T *unsorted_array, T *tmp_array,
                   unsigned long n)
{
    int new_n;
    while (n > 32)
    {
        new_n = qsort_AVX2(unsorted_array, tmp_array, n);
        n = n - new_n - 1;
        my_qsort_AVX2(&unsorted_array[n + 1], tmp_array, new_n);
    }
    insertion_sort(unsorted_array, n);
}


template <typename T>
void qs_double(std::vector<T> &vec)
{
    T *data = &vec[0];
    std::vector<T> temp(vec.size());
    T *tmp = &temp[0];
    int len = vec.size();
    quickdouble::my_qsort_AVX2(data, tmp, len);
}
} // namespace end
