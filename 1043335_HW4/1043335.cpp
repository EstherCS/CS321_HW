//==========================================================================
///  @file      1043335.cpp
///  @brief     An automatically generated netlist parser
///  @version   1.0
///  @date      2017-12-26
//==========================================================================

//--------------------------------------------------------------------------
// function : for system use
//--------------------------------------------------------------------------
#include <iostream>
#include "ScalableVectorGraphicsGenerator.cpp"
#include <string>
#include "1043335.h"
using namespace std;

//--------------------------------------------------------------------------
// function : announce functions
//--------------------------------------------------------------------------
void FindLevel(int Gcount, int& level, vector< vector<int> >&route);
void Draw(int Gcount, int level, vector<vector<int>> route);

//==========================================================================
///  @brief  Find the max level
///  @note   用 level 0 的每個數字去找 level 2，依此類推
///~~~
///      route : 
/// 　　┌───┬───┬───┬────┐
///  L0 ∣ 301  ∣ 302  ∣  303 ∣  304   ∣
/// 　　├───┼───┼───┼────┤
///  L1 ∣ 500  ∣ 502  ∣  503 ∣   0    ∣502 -> -100 ( 502 在 level3 出現 )
/// 　　├───┼───┼───┼────┤
///  L2 ∣ 501  ∣ 400  ∣  401 ∣   0    ∣
/// 　　├───┼───┼───┼────┤
///  L3 ∣ 502  ∣  0   ∣   0  ∣   0    ∣
/// 　　├───┼───┼───┼────┤
///  L4 ∣ 400  ∣  0   ∣   0  ∣   0　  ∣
/// 　　└───┴───┴───┴────┘
///~~~
//==========================================================================
void FindLevel(int Gcount, int& level, vector< vector<int> >& route)
{
	for(int i = 0; i < Inline; i++)
	{		
		route[level].push_back(in[i]);		
	}

	int next = level + 1;
	int Length = 0;

	for(int i = 0; i < route[level].size(); i++)
	{		
		route.push_back(vector<int>());
		for(int j = 0; j < Gcount; j++)
		{
			if(route[level][i] ==gate[j] && (j %4 != 0))
			{
				int index = j;
				// find the result, and use the resault as the basic to fine the next
				while(index % 4 != 0)    
					index--;
				bool exist = false;
				for(int x = next; x < next + 1; x++)
				{
					for(int y = 0; y < route[next].size(); y++)
					{						
						if(gate[index] == route[x][y])
						{
							exist = true;						
						}
					}
				}				
				// when the same number appear at the higher lever, the number in the low level become 100 
				if(level > 0)
				{
					for(int i = 0; i < next; i++)
					{
						for(int j = 0; j < route[i].size(); j++)
						{
							if(gate[index] == route[i][j])
							{
								route[i][j] = -100;
							}
						}
					}
				}
                // put to next level
				if(!exist && gate[index] != 0)
				{
					route.push_back(vector<int>());
					route[next].push_back(gate[index]);   
				}
			}
		}
		if(route[level].size() > Length)
			Length = route[level].size();
		if(i == route[level].size() - 1)
		{
			level++;
			next = level + 1;
			i = -1;
		}
	}
	// every level should contain same numbers, if not, put 0 in that level
	for(int i = 0; i < level; i++)
	{
		while(route[i].size() < Length)
		{
			route[i].push_back(0);
		}
	}
}

//==========================================================================
///  @brief  畫出 gate & path
///  @note   先畫出 input, output, 再根據 max level 分配位置，畫出其他 gate，
///          最後再畫出兩個 gates 之間的 path
///~~~
///  gate
/// ┌───┬───┬───┬────┐
/// ∣ 400  ∣   B  ∣  502 ∣   .    ∣
/// ├───┼───┼───┼────┤
/// ∣ 401  ∣   B  ∣  503 ∣   .    ∣
/// ├───┼───┼───┼────┤
/// ∣ 501  ∣   T  ∣  503 ∣   .    ∣
/// ├───┼───┼───┼────┤
/// ∣ 500  ∣   A  ∣  503 ∣  301   ∣
/// ├───┼───┼───┼────┤
/// ∣ 502  ∣   A  ∣  503 ∣  302   ∣
/// ├───┼───┼───┼────┤
/// ∣ 503  ∣   A  ∣  302 ∣  303   ∣
/// └───┴───┴───┴────┘
///~~~
//==========================================================================
void Draw(int Gcount, int level, vector<vector<int>> route)
{
	int Max = level;	

	vector< vector<int>> record;
	ScalableVectorGraphicsGenerator test;
	test.SVGBegin("result",5000,5000);
  
	//------------------------------------------------------------------------
	// function: draw input
	//------------------------------------------------------------------------
	for(int i = 0,j = 0; j < Inline; i += 150, j++)
	{
		record.push_back(vector<int>());
		record.push_back(vector<int>());
		record.push_back(vector<int>());
		record[0].push_back(in[j]);
		record[1].push_back(0);
		record[2].push_back(i);
		test.drawIOBox(0, i, 0);
		test.drawText(-10, i + 10, in[j]);
	 }

	//------------------------------------------------------------------------
	// function: graw gates
	//------------------------------------------------------------------------
	for(int i = 0; i < route[0].size() ; i++)
	{
		for(int j = 1; j < Max; j++)
		{
			int xx = 300*j;
			for(int k = 0; k < Gcount; k++)
			{
				//------------------------------------------------------------------
				// function: find the gate name and draw
				//------------------------------------------------------------------ 
				if((k % 4 == 0) && (route[j][i] == gate[k]))
				{
					string GateName;
					if(gate[k + 1]  == 0 )
						GateName = name[k/4];

					int Snum = 0;
					if(GateName == "NOT")
						Snum = 1;
					else if(GateName == "AND")
						Snum = 2;
					else if(GateName == "NAND")
						Snum = 3;
					else if(GateName == "OR")
						Snum = 4;
					else if(GateName == "NOR")
						Snum = 5;
					else if(GateName == "XOR")
						Snum = 6;
					else if(GateName == "XNOR")
						Snum = 7;
					else if(GateName == "BUFF")
						Snum = 8;
					switch(Snum)
					{
						// NOT
						case 1 :
							test.drawINV(xx, i*150);
							record[0].push_back(gate[k]);
							record[1].push_back(xx - 5);
							record[2].push_back(i*150);
							test.drawText(xx-20, i*150 + 10, gate[k]);
							break;
						case 2 :
							test.drawAND(xx, i*150);
							break;			
						case 3 :
							test.drawNAND(xx, i*150);
							break;
						case 4 :
							test.drawOR(xx - 10, i*150);
							test.drawText(xx-20, i*150 + 10, gate[k]);
							break;		
						case 5 :
							test.drawNOR(xx - 10, i*150);
							test.drawText(xx-20, i*150 + 10, gate[k]);
							break;
						case 6 :
							test.drawXOR(xx - 10, i*150);
							test.drawText(xx-20, i*150 + 10, gate[k]);
							break;	
						case 7 :							
							test.drawXNOR(xx - 10, i*150);							
							break;
						case 8 :
							test.drawBuff(xx, i*150);
							record[0].push_back(gate[k]);
							record[1].push_back(xx - 5);
							record[2].push_back(i*150);
							test.drawText(xx-20, i*150 + 10, gate[k]);
							break;
					}
					if(GateName == "AND" || GateName == "NAND")
					{
						record[0].push_back(gate[k]);
						record[1].push_back(xx);
						record[2].push_back(i*150);
						test.drawText(xx-10, i*150 + 10, gate[k]);
					}
					else if(GateName == "OR" || GateName == "NOR" || GateName == "XOR" || GateName == "XNOR")
					{
						record[0].push_back(gate[k]);
						record[1].push_back(xx);
						record[2].push_back(i*150);
						test.drawText(xx-20, i*150 + 10, gate[k]);
					}
				}
			}
		}
	}
	//------------------------------------------------------------------------
  // function: draw output
  //------------------------------------------------------------------------
	vector<vector<int>> Outposition;
	Outposition.push_back(vector<int>());
	Outposition.push_back(vector<int>());
	Outposition.push_back(vector<int>());
	for(int i = 0, j = 0; j < Outline; i+= 150, j++)
	{
		Outposition[0].push_back(output[j]);
		Outposition[1].push_back(300*Max);
		Outposition[2].push_back(i);
		test.drawIOBox(300*Max, i, 2);
		test.drawText(300*Max-15, i + 10, output[j]);
	}	

	//------------------------------------------------------------------------
  // function: use the number in vector to draw path
  //------------------------------------------------------------------------
	vector<int> path(4);
	int pi = 0;
	int count = 0;
	for(int i = 0; i < Gcount; i++)
	{
		if(i == 1 || (i % 4 == 1))
			i++;
		for(int k = 0; k < record[0].size(); k++)
		{
			// this is result
			if((gate[i] == record[0][k]) && count == 0)        
			{
				path[pi++] = record[1][k] + 5;
				path[pi++] = record[2][k] + 25;
				count++;
			}	
			//  draw path to result, ex : 300 301
			else if((gate[i] == record[0][k]) && count != 0)   
			{
				path[pi++] = record[1][k] + 50;
				path[pi++] = record[2][k] + 25;
				count++;
			}		
		}
		if(count > 1)
		{
			test.drawPath(path);
			pi -= 2;
			if(gate[i + 1] == 46)
			{
				count = 0;
				pi = 0;
			}
			if(count == 3)
			{
				count = 0;
				pi = 0;
			}
		}
	}	
	for(int i = 0; i < record[0].size(); i++)
	{
		for(int j = 0; j < Outposition[0].size(); j++)
		{
			if(record[0][i] == Outposition[0][j])
			{
				path[0] = record[1][i] + 5;
				path[1] = record[2][i] + 25;
				path[2] = Outposition[1][j] + 50;
				path[3] = Outposition[2][j] + 25;
				test.drawPath(path);
			}
		}
	}	
	test.SVGEnd();
}
