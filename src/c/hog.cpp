#include "consts.h"
#include "math.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ap_int.h"
#define FACTOR 1024

void computeHistogram0(ap_int<15>  descriptor[HISTOGRAMSIZE/16], unsigned char image_buffer[18][34], int sum[2]) {
	for(int i=0;i<HISTOGRAMSIZE/16;i++){
		descriptor [i] = 0;
	}
	for(int i=0;i<2;i++){
		sum [i]=0;
	}
	int  blkIdx, blkPosX, blkPosY;
	int Gx,Gy,mag;
	int bin_index;
	blkIdx = 0;
	//Lookup tables for tan(20)*Gx
	int lut0[256] = {0,0,0,1,1,1,2,2,2,3,3,3,4,4,5,5,5,6,6,6,7,7,7,8,8,9,9,9,10,10,10,11,11,11,12,12,13,13,13,14,14,14,15,15,15,16,16,17,17,17,18,18,18,19,19,19,20,20,21,21,21,22,22,22,23,23,23,24,24,25,25,25,26,26,26,27,27,27,28,28,29,29,29,30,30,30,31,31,31,32,32,33,33,33,34,34,34,35,35,35,36,36,37,37,37,38,38,38,39,39,39,40,40,41,41,41,42,42,42,43,43,43,44,44,45,45,45,46,46,46,47,47,47,48,48,49,49,49,50,50,50,51,51,51,52,52,53,53,53,54,54,54,55,55,55,56,56,57,57,57,58,58,58,59,59,59,60,60,61,61,61,62,62,62,63,63,63,64,64,65,65,65,66,66,66,67,67,67,68,68,69,69,69,70,70,70,71,71,71,72,72,73,73,73,74,74,74,75,75,75,76,76,77,77,77,78,78,78,79,79,79,80,80,81,81,81,82,82,82,83,83,83,84,84,85,85,85,86,86,86,87,87,87,88,88,89,89,89,90,90,90,91,91,91,92,92};
#pragma HLS RESOURCE variable=lut0 core=ROM_1P_BRAM
	//Lookup tables for tan(40)*Gx
	int lut1[256] = {0,0,1,2,3,4,5,5,6,7,8,9,10,10,11,12,13,14,15,15,16,17,18,19,20,20,21,22,23,24,25,26,26,27,28,29,30,31,31,32,33,34,35,36,36,37,38,39,40,41,41,42,43,44,45,46,46,47,48,49,50,51,52,52,53,54,55,56,57,57,58,59,60,61,62,62,63,64,65,66,67,67,68,69,70,71,72,72,73,74,75,76,77,78,78,79,80,81,82,83,83,84,85,86,87,88,88,89,90,91,92,93,93,94,95,96,97,98,98,99,100,101,102,103,104,104,105,106,107,108,109,109,110,111,112,113,114,114,115,116,117,118,119,119,120,121,122,123,124,124,125,126,127,128,129,130,130,131,132,133,134,135,135,136,137,138,139,140,140,141,142,143,144,145,145,146,147,148,149,150,150,151,152,153,154,155,156,156,157,158,159,160,161,161,162,163,164,165,166,166,167,168,169,170,171,171,172,173,174,175,176,177,177,178,179,180,181,182,182,183,184,185,186,187,187,188,189,190,191,192,192,193,194,195,196,197,197,198,199,200,201,202,203,203,204,205,206,207,208,208,209,210,211,212,213,213};
#pragma HLS RESOURCE variable=lut1 core=ROM_1P_BRAM
	//Lookup tables for tan(60)*Gx
	int lut2[256] = {0,1,3,5,6,8,10,12,13,15,17,19,20,22,24,25,27,29,31,32,34,36,38,39,41,43,44,46,48,50,51,53,55,57,58,60,62,63,65,67,69,70,72,74,76,77,79,81,83,84,86,88,89,91,93,95,96,98,100,102,103,105,107,108,110,112,114,115,117,119,121,122,124,126,127,129,131,133,134,136,138,140,141,143,145,147,148,150,152,153,155,157,159,160,162,164,166,167,169,171,172,174,176,178,179,181,183,185,186,188,190,191,193,195,197,198,200,202,204,205,207,209,210,212,214,216,217,219,221,223,224,226,228,230,231,233,235,236,238,240,242,243,245,247,249,250,252,254,255,257,259,261,262,264,266,268,269,271,273,274,276,278,280,281,283,285,287,288,290,292,294,295,297,299,300,302,304,306,307,309,311,313,314,316,318,319,321,323,325,326,328,330,332,333,335,337,338,340,342,344,345,347,349,351,352,354,356,358,359,361,363,364,366,368,370,371,373,375,377,378,380,382,383,385,387,389,390,392,394,396,397,399,401,402,404,406,408,409,411,413,415,416,418,420,421,423,425,427,428,430,432,434,435,437,439,441};
#pragma HLS RESOURCE variable=lut2 core=ROM_1P_BRAM
	//Lookup tables for tan(80)*Gx
	int lut3[256] = {0,5,11,17,22,28,34,39,45,51,56,62,68,73,79,85,90,96,102,107,113,119,124,130,136,141,147,153,158,164,170,175,181,187,192,198,204,209,215,221,226,232,238,243,249,255,260,266,272,277,283,289,294,300,306,311,317,323,328,334,340,345,351,357,362,368,374,379,385,391,396,402,408,413,419,425,430,436,442,447,453,459,464,470,476,481,487,493,498,504,510,515,521,527,532,538,544,549,555,561,566,572,578,584,589,595,601,606,612,618,623,629,635,640,646,652,657,663,669,674,680,686,691,697,703,708,714,720,725,731,737,742,748,754,759,765,771,776,782,788,793,799,805,810,816,822,827,833,839,844,850,856,861,867,873,878,884,890,895,901,907,912,918,924,929,935,941,946,952,958,963,969,975,980,986,992,997,1003,1009,1014,1020,1026,1031,1037,1043,1048,1054,1060,1065,1071,1077,1082,1088,1094,1099,1105,1111,1116,1122,1128,1133,1139,1145,1150,1156,1162,1168,1173,1179,1185,1190,1196,1202,1207,1213,1219,1224,1230,1236,1241,1247,1253,1258,1264,1270,1275,1281,1287,1292,1298,1304,1309,1315,1321,1326,1332,1338,1343,1349,1355,1360,1366,1372,1377,1383,1389,1394,1400,1406,1411,1417,1423,1428,1434,1440,1445};
#pragma HLS RESOURCE variable=lut3 core=ROM_1P_BRAM
	int  x_offset,y_offset;

	histogram:for (unsigned int bX = 0; bX < NUMBLOCKSX/2; bX++) {
		blkPosX = bX * BLOCKSTRIDEX;
		computeHistogram_label1:for (unsigned int y = 0; y < BLOCKSIZEY * CELLSIZEY; y++) {
			for (unsigned int x = 0; x < BLOCKSIZEX * CELLSIZEX; x=x+2) {
#pragma HLS PIPELINE II=1

				//Compute Gradients
				Gx = image_buffer[y+1][blkPosX + x + 2] - image_buffer[y+1][blkPosX + x];
				Gy = image_buffer[y+2][blkPosX + x+1] - image_buffer[y][blkPosX + x+1];

				//Compute Magnitude
				mag = abs(Gx - Gy);

				x_offset = x / CELLSIZEX;
				y_offset = y / CELLSIZEY;

				//Histogram Binning
				 if((Gx >= 0 && Gy >= 0) || (Gx <= 0 && Gy <= 0)){
					if 		(abs(Gy) < lut0[abs(Gx)]) 	{bin_index = 0;}
					else if (abs(Gy) < lut1[abs(Gx)]) 	{bin_index = 1;}
					else if (abs(Gy) < lut2[abs(Gx)]) 	{bin_index = 2;}
					else if (abs(Gy) < lut3[abs(Gx)]) 	{bin_index = 3;}
					else 								{bin_index = 4;}
				} else{
					if 		(abs(Gy) <  lut0[abs(Gx)])	{bin_index = 4;}
					else if (abs(Gy) <  lut1[abs(Gx)]) 	{bin_index = 5;}
					else if (abs(Gy) <  lut2[abs(Gx)]) 	{bin_index = 6;}
					else if (abs(Gy) <  lut3[abs(Gx)]) 	{bin_index = 7;}
					else 								{bin_index = 8;}
				}
				descriptor [bX*36 + x_offset * 18 + y_offset * 9 + bin_index] += mag;
				#pragma HLS DEPENDENCE variable=descriptor inter false
				sum [bX] += mag;
				#pragma HLS DEPENDENCE variable=sum inter false
			}
		}
	}
}

void  normalizeHisto0(int sum[2], ap_int<15>  descriptor[HISTOGRAMSIZE/16],ap_int<11> normalized[HISTOGRAMSIZE/16]) {
	int  average;
	unsigned int blkIdx, i;
	unsigned int blkSize = 36;
	for (blkIdx = 0; blkIdx < NUMBLOCKSX/2; blkIdx++) {
		for (i = 0; i < 36; i++) {
#pragma HLS PIPELINE II=1
			//Average of block
			average = sum[blkIdx]/blkSize;
			//Normalization quantization method
			if (descriptor[blkIdx*36+i] > 2*average){
				normalized[blkIdx*36+i] = 409;
			}
			else if (descriptor[blkIdx*36+i] > 7*average/4){
				normalized[blkIdx*36+i] = 358;
			}
			else if (descriptor[blkIdx*36+i] > 6*average/4){
				normalized[blkIdx*36+i] = 307;
			}
			else if (descriptor[blkIdx*36+i] > 5*average/4){
				normalized[blkIdx*36+i] = 256;
			}
			else if (descriptor[blkIdx*36+i] > average){
				normalized[blkIdx*36+i] = 204;
			}
			else if (descriptor[blkIdx*36+i] > 3*average/4){
				normalized[blkIdx*36+i] = 153;
			}
			else if (descriptor[blkIdx*36+i] > average/2){
				normalized[blkIdx*36+i] = 102;
			}
			else if (descriptor[blkIdx*36+i] > average/4){
				normalized[blkIdx*36+i] = 51;
			}
			else {
				normalized[blkIdx*36+i] = 0;
			}
		}
	}
}

void computeHistogram1(ap_int<15>  descriptor[HISTOGRAMSIZE/16], unsigned char image_buffer[18][34], int sum[2]) {
	for(int i=0;i<HISTOGRAMSIZE/16;i++){
		descriptor [i] = 0;
	}
	for(int i=0;i<2;i++){
		sum [i]=0;
	}
	int  blkIdx, blkPosX, blkPosY;
	int Gx,Gy,mag;
	int bin_index;
	blkIdx = 0;
	//Lookup tables for tan(20)*Gx
	int lut0[256] = {0,0,0,1,1,1,2,2,2,3,3,3,4,4,5,5,5,6,6,6,7,7,7,8,8,9,9,9,10,10,10,11,11,11,12,12,13,13,13,14,14,14,15,15,15,16,16,17,17,17,18,18,18,19,19,19,20,20,21,21,21,22,22,22,23,23,23,24,24,25,25,25,26,26,26,27,27,27,28,28,29,29,29,30,30,30,31,31,31,32,32,33,33,33,34,34,34,35,35,35,36,36,37,37,37,38,38,38,39,39,39,40,40,41,41,41,42,42,42,43,43,43,44,44,45,45,45,46,46,46,47,47,47,48,48,49,49,49,50,50,50,51,51,51,52,52,53,53,53,54,54,54,55,55,55,56,56,57,57,57,58,58,58,59,59,59,60,60,61,61,61,62,62,62,63,63,63,64,64,65,65,65,66,66,66,67,67,67,68,68,69,69,69,70,70,70,71,71,71,72,72,73,73,73,74,74,74,75,75,75,76,76,77,77,77,78,78,78,79,79,79,80,80,81,81,81,82,82,82,83,83,83,84,84,85,85,85,86,86,86,87,87,87,88,88,89,89,89,90,90,90,91,91,91,92,92};
#pragma HLS RESOURCE variable=lut0 core=ROM_1P_BRAM
	//Lookup tables for tan(40)*Gx
	int lut1[256] = {0,0,1,2,3,4,5,5,6,7,8,9,10,10,11,12,13,14,15,15,16,17,18,19,20,20,21,22,23,24,25,26,26,27,28,29,30,31,31,32,33,34,35,36,36,37,38,39,40,41,41,42,43,44,45,46,46,47,48,49,50,51,52,52,53,54,55,56,57,57,58,59,60,61,62,62,63,64,65,66,67,67,68,69,70,71,72,72,73,74,75,76,77,78,78,79,80,81,82,83,83,84,85,86,87,88,88,89,90,91,92,93,93,94,95,96,97,98,98,99,100,101,102,103,104,104,105,106,107,108,109,109,110,111,112,113,114,114,115,116,117,118,119,119,120,121,122,123,124,124,125,126,127,128,129,130,130,131,132,133,134,135,135,136,137,138,139,140,140,141,142,143,144,145,145,146,147,148,149,150,150,151,152,153,154,155,156,156,157,158,159,160,161,161,162,163,164,165,166,166,167,168,169,170,171,171,172,173,174,175,176,177,177,178,179,180,181,182,182,183,184,185,186,187,187,188,189,190,191,192,192,193,194,195,196,197,197,198,199,200,201,202,203,203,204,205,206,207,208,208,209,210,211,212,213,213};
#pragma HLS RESOURCE variable=lut1 core=ROM_1P_BRAM
	//Lookup tables for tan(60)*Gx
	int lut2[256] = {0,1,3,5,6,8,10,12,13,15,17,19,20,22,24,25,27,29,31,32,34,36,38,39,41,43,44,46,48,50,51,53,55,57,58,60,62,63,65,67,69,70,72,74,76,77,79,81,83,84,86,88,89,91,93,95,96,98,100,102,103,105,107,108,110,112,114,115,117,119,121,122,124,126,127,129,131,133,134,136,138,140,141,143,145,147,148,150,152,153,155,157,159,160,162,164,166,167,169,171,172,174,176,178,179,181,183,185,186,188,190,191,193,195,197,198,200,202,204,205,207,209,210,212,214,216,217,219,221,223,224,226,228,230,231,233,235,236,238,240,242,243,245,247,249,250,252,254,255,257,259,261,262,264,266,268,269,271,273,274,276,278,280,281,283,285,287,288,290,292,294,295,297,299,300,302,304,306,307,309,311,313,314,316,318,319,321,323,325,326,328,330,332,333,335,337,338,340,342,344,345,347,349,351,352,354,356,358,359,361,363,364,366,368,370,371,373,375,377,378,380,382,383,385,387,389,390,392,394,396,397,399,401,402,404,406,408,409,411,413,415,416,418,420,421,423,425,427,428,430,432,434,435,437,439,441};
#pragma HLS RESOURCE variable=lut2 core=ROM_1P_BRAM
	//Lookup tables for tan(80)*Gx
	int lut3[256] = {0,5,11,17,22,28,34,39,45,51,56,62,68,73,79,85,90,96,102,107,113,119,124,130,136,141,147,153,158,164,170,175,181,187,192,198,204,209,215,221,226,232,238,243,249,255,260,266,272,277,283,289,294,300,306,311,317,323,328,334,340,345,351,357,362,368,374,379,385,391,396,402,408,413,419,425,430,436,442,447,453,459,464,470,476,481,487,493,498,504,510,515,521,527,532,538,544,549,555,561,566,572,578,584,589,595,601,606,612,618,623,629,635,640,646,652,657,663,669,674,680,686,691,697,703,708,714,720,725,731,737,742,748,754,759,765,771,776,782,788,793,799,805,810,816,822,827,833,839,844,850,856,861,867,873,878,884,890,895,901,907,912,918,924,929,935,941,946,952,958,963,969,975,980,986,992,997,1003,1009,1014,1020,1026,1031,1037,1043,1048,1054,1060,1065,1071,1077,1082,1088,1094,1099,1105,1111,1116,1122,1128,1133,1139,1145,1150,1156,1162,1168,1173,1179,1185,1190,1196,1202,1207,1213,1219,1224,1230,1236,1241,1247,1253,1258,1264,1270,1275,1281,1287,1292,1298,1304,1309,1315,1321,1326,1332,1338,1343,1349,1355,1360,1366,1372,1377,1383,1389,1394,1400,1406,1411,1417,1423,1428,1434,1440,1445};
#pragma HLS RESOURCE variable=lut3 core=ROM_1P_BRAM
	int  x_offset,y_offset;

	histogram:for (unsigned int bX = 0; bX < NUMBLOCKSX/2; bX++) {
		blkPosX = bX * BLOCKSTRIDEX;
		computeHistogram_label1:for (unsigned int y = 0; y < BLOCKSIZEY * CELLSIZEY; y++) {
			for (unsigned int x = 0; x < BLOCKSIZEX * CELLSIZEX; x=x+2) {
#pragma HLS PIPELINE II=1

				//Compute Gradients
				Gx = image_buffer[y+1][blkPosX + x + 2] - image_buffer[y+1][blkPosX + x];
				Gy = image_buffer[y+2][blkPosX + x+1] - image_buffer[y][blkPosX + x+1];

				//Compute Magnitude
				mag = abs(Gx - Gy);

				x_offset = x / CELLSIZEX;
				y_offset = y / CELLSIZEY;

				//Histogram Binning
				 if((Gx >= 0 && Gy >= 0) || (Gx <= 0 && Gy <= 0)){
					if 		(abs(Gy) < lut0[abs(Gx)]) 	{bin_index = 0;}
					else if (abs(Gy) < lut1[abs(Gx)]) 	{bin_index = 1;}
					else if (abs(Gy) < lut2[abs(Gx)]) 	{bin_index = 2;}
					else if (abs(Gy) < lut3[abs(Gx)]) 	{bin_index = 3;}
					else 								{bin_index = 4;}
				} else{
					if 		(abs(Gy) <  lut0[abs(Gx)])	{bin_index = 4;}
					else if (abs(Gy) <  lut1[abs(Gx)]) 	{bin_index = 5;}
					else if (abs(Gy) <  lut2[abs(Gx)]) 	{bin_index = 6;}
					else if (abs(Gy) <  lut3[abs(Gx)]) 	{bin_index = 7;}
					else 								{bin_index = 8;}
				}
				descriptor [bX*36 + x_offset * 18 + y_offset * 9 + bin_index] += mag;
				#pragma HLS DEPENDENCE variable=descriptor inter false
				sum [bX] += mag;
				#pragma HLS DEPENDENCE variable=sum inter false
			}
		}
	}
}

void  normalizeHisto1(int sum[2], ap_int<15>  descriptor[HISTOGRAMSIZE/16],ap_int<11> normalized[HISTOGRAMSIZE/16]) {
	int  average;
	unsigned int blkIdx, i;
	unsigned int blkSize = 36;
	for (blkIdx = 0; blkIdx < NUMBLOCKSX/2; blkIdx++) {
		for (i = 0; i < 36; i++) {
#pragma HLS PIPELINE II=1
			//Average of block
			average = sum[blkIdx]/blkSize;
			//Normalization quantization method
			if (descriptor[blkIdx*36+i] > 2*average){
				normalized[blkIdx*36+i] = 409;
			}
			else if (descriptor[blkIdx*36+i] > 7*average/4){
				normalized[blkIdx*36+i] = 358;
			}
			else if (descriptor[blkIdx*36+i] > 6*average/4){
				normalized[blkIdx*36+i] = 307;
			}
			else if (descriptor[blkIdx*36+i] > 5*average/4){
				normalized[blkIdx*36+i] = 256;
			}
			else if (descriptor[blkIdx*36+i] > average){
				normalized[blkIdx*36+i] = 204;
			}
			else if (descriptor[blkIdx*36+i] > 3*average/4){
				normalized[blkIdx*36+i] = 153;
			}
			else if (descriptor[blkIdx*36+i] > average/2){
				normalized[blkIdx*36+i] = 102;
			}
			else if (descriptor[blkIdx*36+i] > average/4){
				normalized[blkIdx*36+i] = 51;
			}
			else {
				normalized[blkIdx*36+i] = 0;
			}
		}
	}
}

void svm(ap_int<11>  normalized0[HISTOGRAMSIZE/16],ap_int<11> normalized1[HISTOGRAMSIZE/16],int offset,int offset2,int *classify){
	//SVM weights vector
	ap_int<12>  weights[HISTOGRAMSIZE] = {-34,-84,-158,1,-48,11,-63,18,-15,13,2,-62,-108,33,-7,-29,-48,-21,46,-191,-96,8,-9,-57,-70,8,0,16,-173,-21,-62,27,-29,-2,-16,-60,77,-227,19,35,-31,-27,-50,56,14,67,-7,-24,8,15,-51,-52,-32,-22,127,-224,-28,40,28,-75,-47,28,20,18,3,180,274,22,-54,1,88,56,128,-142,24,-10,-45,-69,-72,12,0,11,-156,-46,111,33,40,102,164,65,102,-192,-58,18,-21,-100,-51,37,-9,11,-165,-45,-109,-3,15,-10,21,-24,44,-112,-100,19,9,-23,-62,17,3,51,-93,-45,-67,49,0,-9,-9,-2,16,-109,-109,7,33,-10,-61,20,24,45,-41,-47,-54,65,-6,-40,-3,-9,-17,20,-71,-51,50,-9,-32,30,-19,-67,31,-72,-49,85,-43,-30,29,-21,96,-90,-49,-31,35,10,-27,43,21,7,-140,-77,-22,16,-26,-20,48,-15,17,0,-100,-74,19,-8,-56,-54,-19,-28,87,96,35,-35,-50,-65,-34,-0,38,275,110,103,44,71,21,39,9,-90,235,237,102,-22,46,61,72,18,-22,62,-39,17,15,75,44,45,-28,-127,120,131,24,-62,41,100,78,18,3,-62,-152,-100,-31,-8,-44,-79,-58,-82,-143,-67,-97,-48,58,66,2,-64,37,-21,79,-55,29,-25,-27,-13,-13,20,-25,-31,-14,42,-9,-30,-9,-14,27,-40,51,45,3,-9,-50,-6,0,64,-9,59,22,-20,-7,-35,-13,-10,-7,26,-136,-29,82,-35,-47,83,33,12,63,-151,-10,115,11,-33,44,23,73,193,-148,-0,5,-43,-50,43,62,182,-11,-110,3,37,-52,-27,71,53,112,447,44,26,-28,-66,-64,-4,45,72,242,-79,-27,8,-8,-37,-44,25,-68,384,82,-45,-88,17,9,26,-57,20,19,32,-26,-29,22,-9,-57,-65,-119,81,86,-31,-48,93,28,-16,-92,-50,-17,-19,-104,-25,27,-42,-35,-66,-63,-96,18,-63,90,202,47,-23,-28,-56,17,-49,-78,92,92,1,-35,-60,-9,-114,59,-32,75,33,-44,-34,14,23,-83,-40,-30,100,52,-10,-1,15,10,-15,59,-29,-14,-44,-75,-43,6,19,-33,31,-23,10,-21,-66,-19,-1,-42,50,-79,-30,90,1,-82,47,-5,3,32,28,-30,36,-42,-17,-2,24,65,-67,-113,23,62,-10,-4,39,34,76,-24,15,-5,58,38,-30,94,41,26,136,-21,-7,-20,37,-39,-8,-13,87,146,-41,-49,-28,43,9,19,-20,-48,53,75,-62,-34,-9,-20,-25,-71,-33,50,71,-17,-55,31,13,1,-56,-40,6,8,-40,-38,24,-18,-5,-80,-75,-46,-16,42,-75,-9,-31,-37,-72,17,40,-77,-76,29,72,-2,-39,-52,2,57,-23,-11,69,106,5,6,-56,14,-39,39,5,62,12,-67,19,18,9,-2,-47,-15,37,-4,-18,7,9,3,-20,12,-9,23,-61,-64,18,27,16,-3,25,-34,16,-47,-42,7,35,-26,3,-54,3,-9,-46,-76,27,-25,-15,95,-80,-34,8,17,-55,31,11,-46,-89,-51,52,78,17,-33,70,13,16,120,93,-69,43,-52,-38,59,31,29,44,-99,-53,13,38,4,47,8,79,131,-77,-42,32,25,-40,20,-7,-110,-75,-1,-84,-115,13,-16,-30,-101,17,16,-67,-71,-47,10,-57,-46,-90,-67,84,-42,-32,-124,-32,-49,-35,-75,29,87,-135,-38,-13,25,-52,-51,-115,57,178,54,49,63,55,-9,-2,-22,70,126,-43,-3,75,67,-39,4,16,21,-5,31,34,66,-20,-32,14,4,-60,-66,21,-9,56,-0,-59,-13,8,-6,-91,-1,-29,-6,-72,-41,-1,11,-47,-53,40,25,14,-66,-57,-7,10,-46,94,-16,-20,-15,5,-66,19,14,52,76,-37,-32,-44,-35,-54,29,25,60,189,-6,-47,95,-21,-64,90,-28,-81,141,-8,67,18,-56,-17,127,19,-8,172,-52,-100,1,-28,-110,-56,-52,-16,264,121,-50,-54,-32,-75,-46,-36,24,191,36,-89,-40,55,-58,-86,-120,0,193,92,-93,-74,32,-75,-94,-94,-4,66,-137,-158,-74,76,-86,-86,-177,20,210,-25,-155,-31,46,-53,-93,-138,-49,22,-107,-128,7,69,-34,-62,-59,-33,46,-84,-120,11,85,-37,-52,-92,-50,-12,87,-16,37,3,-52,3,8,-73,4,37,63,20,-13,-22,5,22,-45,11,-18,-23,-41,-62,-67,-38,-13,-72,25,-26,33,-32,-76,-90,3,-24,25,-11,-100,4,-51,-63,-94,41,7,67,82,-123,-63,18,-79,-4,-8,-82,-70,222,-159,34,37,24,20,92,50,42,138,-38,104,115,211,121,93,-19,-56,113,-23,-56,-76,-30,-101,-73,-38,-39,161,-26,-36,-70,14,-55,-59,-82,27,33,105,-144,-27,30,-101,-98,-104,88,189,52,-20,30,66,-47,-68,-120,35,45,-148,-138,10,18,-50,-76,-118,61,201,-35,-111,16,95,-15,-32,-61,-31,-14,-8,-83,-20,58,-31,-11,-17,-17,174,-86,-78,-11,64,-36,-49,-66,-75,54,94,55,60,24,0,35,39,-47,169,112,45,29,9,19,52,39,-79,18,-74,16,-44,-29,-71,3,12,-106,2,-26,-36,-37,-41,-72,16,32,115,-165,-56,-134,-188,-126,-17,-93,-221,100,-180,-129,-72,-236,-58,263,12,39,-222,-163,-146,-88,-54,-56,-31,19,-33,-119,15,-80,-103,-20,-40,-60,4,-11,-99,16,21,88,76,41,94,109,122,-150,-20,3,-75,-5,-75,-33,15,24,-105,68,22,73,104,24,32,172,194,-184,-39,-181,-87,-18,-66,-62,-35,16,-104,45,-167,278,177,-7,21,109,130,-173,-108,-135,-33,32,-120,-52,-5,107,-110,137,33,259,66,45,25,61,-15,-142,-11,24,14,11,-41,-36,-67,57,-138,28,2,133,13,-39,-63,14,-95,-117,16,67,-29,-19,-94,-57,-49,16,-88,102,-6,-57,-49,-44,-69,13,-157,-72,-35,-71,-3,47,-46,-55,-20,0};
#pragma HLS RESOURCE variable=weights core=ROM_2P_BRAM
	// SVM's model initial bias
	int sum = -14;


	svm_loop:for(int i=0;i<HISTOGRAMSIZE/16;i++){
#pragma HLS PIPELINE II=1
		//Compute 1/16 of each buffer using the offset
		sum+=normalized0[i]*weights[i+offset];
		sum+=normalized1[i]*weights[i+offset2];
	}
	classify[0] = sum;
}

/*HOG top function
 *
 * Each accelerator computes the classification of the
 * 1/8 of the detection window
 *
 * specs[0] = Top left corner of the detection window
 * specs[1] = Input image width
 * specs[2] = Accelerator id
 * specs[3] = Accelerators classification output
 *
 * image = Input image DDR address
*/

void hog(int specs[4],
		unsigned char *image0
		){
#pragma HLS INTERFACE s_axilite depth=16 port=specs bundle=SPECS
#pragma HLS INTERFACE s_axilite port=return bundle=CONTROL_BUS
#pragma HLS INTERFACE m_axi port=image0 offset=slave bundle=INPUT_IMAGE

	// Histogram and Normalized descriptors for the first half of the input
	ap_int<15>  descriptor0[HISTOGRAMSIZE/16];
	ap_int<11>  normalized0[HISTOGRAMSIZE/16];
#pragma HLS RESOURCE variable=normalized0 core=RAM_2P_BRAM
	ap_int<15>  descriptor1[HISTOGRAMSIZE/16];
	ap_int<11>  normalized1[HISTOGRAMSIZE/16];
#pragma HLS RESOURCE variable=normalized1 core=RAM_2P_BRAM

	unsigned char image_buffer0[18][34];
#pragma HLS ARRAY_PARTITION variable=image_buffer0 complete dim=1
	unsigned char image_buffer1[18][34];
#pragma HLS ARRAY_PARTITION variable=image_buffer1 complete dim=1

	//Sum of the magnitudes of each block
	int sum0[2];
	int sum1[2];

	int classify[1];

	//Store the 1/16 of the detection window
	read_input0:for(int i=0;i<18;i++){
		memcpy(image_buffer0[i],image0 + i*specs[1]+ specs[0],34*sizeof(unsigned char));
	}
	//Store the 1/16 of the detection window
	read_input1:for(int i=0;i<18;i++){
		memcpy(image_buffer1[i],image0 + i*specs[1] + specs[0]+33,34*sizeof(unsigned char));
	}

	computeHistogram0(descriptor0,image_buffer0,sum0);
	computeHistogram1(descriptor1,image_buffer1,sum1);

	normalizeHisto0(sum0,descriptor0,normalized0);
	normalizeHisto1(sum1,descriptor1,normalized1);

	svm(normalized0,normalized1,specs[2]*HISTOGRAMSIZE/8,specs[2]*HISTOGRAMSIZE/8+HISTOGRAMSIZE/16,classify);

	specs[3] = classify[0];
}
