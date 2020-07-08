//==========================================================================
///  @file      1043335.cpp
///  @brief     A hand crafted netlist parser
///  @version   1.0
///  @date      2017-09-22
//==========================================================================

//--------------------------------------------------------------------------
// function : for system use
//--------------------------------------------------------------------------
#include <iostream>
#include "ScalableVectorGraphicsGenerator.hpp"
#include <string>
using namespace std;

//--------------------------------------------------------------------------
// function : announce functions
//--------------------------------------------------------------------------
void load(char program[][200], int &numLines, char* name);
void FindNum(char program[][200]);
void group(int& Gcount, char program[][200]);
void FindLevel(int Gcount, int& level, vector< vector<int> >&route);
void Draw(char* name, int Gcount, int level, vector<vector<int>> route);

//--------------------------------------------------------------------------
// function : define global variables
//--------------------------------------------------------------------------
char program[1000][200], input[1000][200], output[1000][200], gate[1000][200];
int numLines = 0, Inline = 0, Outline = 0, line = 0;  

//==========================================================================
///  @brief  main function
///  @note   read the file -> find the max level -> graw graphics
//==========================================================================
int main(int argc, char** argv)
{
    // read the file ( user can change the file name from makefile )
	load(program, numLines, argv[1]);     

	FindNum(program);
		
	int Gcount = 0;
	group(Gcount, program);
	cout << "1  \n";
	// find the max level	
	vector< vector<int> >route;
	route.push_back(vector<int>());
	int level = 0;
	FindLevel(Gcount, level, route);
	cout << "2  \n";
	// graw graph
	Draw(argv[2], Gcount, level, route);
	cout << "3  \n";
    return 0;
}

//==========================================================================
///  @brief  Find input numbers and output numbers
///  @note   get input numbers & output numbers from the file
//==========================================================================
void FindNum(char program[][200])
{
	// find input number
	while(program[line][0] == 'I')
	{
		int i = 6, s = 0;
		while(program[line][i] != ')')
		{
			input[Inline][s] = program[line][i];
			i++;
			s++;
		}
		Inline++;
		line++;
	}
  
	// find output number
	while(program[line][0] == 'O')
	{
		int i = 7, s = 0;
		while(program[line][i] != ')')
		{
			output[Outline][s] = program[line][i];
			i++;
			s++;
		}
		Outline++;
		line++;
	}
}

//==========================================================================
///  @brief  find gate numbers
///  @note   find other gates' number,four numbers become a group
///~~~
///  gate : 
///  ¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢?
///  ?400  ?  B  ? 502 ?  .    ?
///  ¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢?
///  ?401  ?  B  ? 503 ?  .    ?
///  ¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢?
///  ?501  ?  T  ? 503 ?  .    ?
///  ¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢?
///  ?500  ?  A  ? 503 ? 301   ?
///  ¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢?
///  ?502  ?  A  ? 503 ? 302   ?
///  ¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢?
///  ?503  ?  A  ? 302 ? 303   ?
///  ¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢?
///~~~
//==========================================================================
void group(int& Gcount, char program[1000][200])
{
	while(line < numLines)
	{
		for(int i = 0, j = 0; program[line][i] != ')'; i++)
		{
			//--------------------------------------------------------------------
			// function: NOT -> T, NOR -> R, XNOR -> F, AND -> A, OR -> O, XOR -> X
			//--------------------------------------------------------------------
			if(program[line][i] == '=' && program[line][i+1] == ' ')
			{
				// NOT
				if(program[line][i+2] - '0' == 30 &&  program[line][i+4] - '0' == 36)      
					gate[Gcount++][0] = 'T';                         
				// NOR
				else if(program[line][i+2] - '0' == 30 &&  program[line][i+4] - '0' == 34) 
					gate[Gcount++][0] = program[line][i+4];                            
				// XNOR
				else if(program[line][i+2] - '0' == 41 &&  program[line][i+4] - '0' == 31) 
					gate[Gcount++][0] = 'F';
				else
					gate[Gcount++][0] = program[line][i+2];   
			}
      
			//--------------------------------------------------------------------
			// function: get all number and count
			//--------------------------------------------------------------------
			if(program[line][i] - '0' >= 0 && program[line][i] - '0' <= 9)
			{
				gate[Gcount][j++] = program[line][i];
				if(program[line][i + 1] - '0' < 0 || program[line][i + 1] - '0' > 9)
				{
					Gcount++;
					j = 0;
				}
			}
		}
		while(Gcount % 4 != 0)
		{
			gate[Gcount++][0] = '.';
		}
		line++;
	}
}

//==========================================================================
///  @brief  Find the max level
///  @note   use the numbers in level 0 to find the numbers in level 2, and so on
///~~~
///      route : 
///     ¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢?
///  L0 ?301  ?302  ? 303 ? 304   ?
///     ¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢?
///  L1 ?500  ?502  ? 503 ?  0    ?502 -> -100 ( 502 is appear in level3 )
///     ¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢?
///  L2 ?501  ?400  ? 401 ?  0    ?
///     ¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢?
///  L3 ?502  ? 0   ?  0  ?  0    ?
///     ¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢?
///  L4 ?400  ? 0   ?  0  ?  0    ?
///     ¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢?
///~~~
//==========================================================================
void FindLevel(int Gcount, int& level, vector< vector<int> >& route)
{
	for(int i = 0; i < Inline; i++)
	{		
		route[level].push_back(atoi(input[i]));		
	}

	int next = level + 1;
	int Length = 0;

	for(int i = 0; i < route[level].size(); i++)
	{		
		route.push_back(vector<int>());
		for(int j = 0; j < Gcount; j++)
		{
			if(route[level][i] == atoi(gate[j]) && (j %4 != 0))
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
						if(atoi(gate[index]) == route[x][y])
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
							if(atoi(gate[index]) == route[i][j])
							{
								route[i][j] = -100;
							}
						}
					}
				}
                // put to next level
				if(!exist && atoi(gate[index]) != 0)
				{
					route.push_back(vector<int>());
					route[next].push_back(atoi(gate[index]));   
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
///  @brief  draw gate & path
///  @note   draw input, output first, and calculate the space by max level. Then draw other gates,
///          finally, draw the path between two gates.
///~~~
///  gate : 
///  ¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢?
///  ?400  ?  B  ? 502 ?  .    ?
///  ¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢?
///  ?401  ?  B  ? 503 ?  .    ?
///  ¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢?
///  ?501  ?  T  ? 503 ?  .    ?
///  ¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢?
///  ?500  ?  A  ? 503 ? 301   ?
///  ¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢?
///  ?502  ?  A  ? 503 ? 302   ?
///  ¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢?
///  ?503  ?  A  ? 302 ? 303   ?
///  ¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢¢?
///~~~
//==========================================================================
void Draw(char* name, int Gcount, int level, vector<vector<int>> route)
{
	int Max = level;	

	vector< vector<int>> record;
	ScalableVectorGraphicsGenerator test;
	test.SVGBegin(name,5000,5000);
  
	//------------------------------------------------------------------------
	// function: draw input
	//------------------------------------------------------------------------
	for(int i = 0,j = 0; j < Inline; i += 150, j++)
	{
		record.push_back(vector<int>());
		record.push_back(vector<int>());
		record.push_back(vector<int>());
		record[0].push_back(atoi(input[j]));
		record[1].push_back(0);
		record[2].push_back(i);
		string s = input[j];
		test.drawIOBox(0, i, 0);
		test.drawText(-10, i + 10, s);
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
				if((k % 4 == 0) && (route[j][i] == atoi(gate[k])))
				{
					string s = gate[k];
					char GateName;
					if(gate[k + 1][0] - '0' >= 17 && gate[k - 1][0] - '0' <= 43 )
						GateName = gate[k + 1][0];
					switch(GateName)
					{
						// NOT
						case 'T' :
							test.drawINV(xx, i*150);
							record[0].push_back(atoi(gate[k]));
							record[1].push_back(xx - 5);
							record[2].push_back(i*150);
							test.drawText(xx-20, i*150 + 10, s);
							break;
						case 'A' :
							test.drawAND(xx, i*150);
							break;			
						case 'N' :
							test.drawNAND(xx, i*150);
							break;
						case 'O' :
							test.drawOR(xx - 10, i*150);
							test.drawText(xx-20, i*150 + 10, s);
							break;		
						case 'R' :
							test.drawNOR(xx - 10, i*150);
							test.drawText(xx-20, i*150 + 10, s);
							break;
						case 'X' :
							test.drawXOR(xx - 10, i*150);
							test.drawText(xx-20, i*150 + 10, s);
							break;	
						case 'F' :							
							test.drawXNOR(xx - 10, i*150);							
							break;
						case 'B' :
							test.drawBuff(xx, i*150);
							record[0].push_back(atoi(gate[k]));
							record[1].push_back(xx - 5);
							record[2].push_back(i*150);
							test.drawText(xx-20, i*150 + 10, s);
							break;
					}
					if(GateName == 'A' || GateName == 'N')
					{
						record[0].push_back(atoi(gate[k]));
						record[1].push_back(xx);
						record[2].push_back(i*150);
						test.drawText(xx-10, i*150 + 10, s);
					}
					else if(GateName == 'O' || GateName == 'R' || GateName == 'X' || GateName == 'F')
					{
						record[0].push_back(atoi(gate[k]));
						record[1].push_back(xx);
						record[2].push_back(i*150);
						test.drawText(xx-20, i*150 + 10, s);
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
		Outposition[0].push_back(atoi(output[j]));
		Outposition[1].push_back(300*Max);
		Outposition[2].push_back(i);
		string s = output[j];
		test.drawIOBox(300*Max, i, 2);
		test.drawText(300*Max-15, i + 10, s);
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
			if((atoi(gate[i]) == record[0][k]) && count == 0)        
			{
				path[pi++] = record[1][k] + 5;
				path[pi++] = record[2][k] + 25;
				count++;
			}	
			//  draw path to result, ex : 300 301
			else if((atoi(gate[i]) == record[0][k]) && count != 0)   
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
			if(gate[i + 1][0] == '.')
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

//==========================================================================
///  @brief  read the information in the file
//==========================================================================
void load(char program[][200], int &numLines, char* name)
{
  // read the file name, can change it in the makefile
	ifstream infile(name, ios::in);

  //------------------------------------------------------------------------
  // function: read the file and count the lines
  //------------------------------------------------------------------------
	if (infile.is_open())                           
	{
		numLines = 0;
		while (!infile.eof())                         
		{
			infile.getline(program[numLines], 200);      
      
			// delete comments and space
			if(program[numLines][0] == '#' || program[numLines][0] - '0' == -48 || program[numLines][0] - '0' == -35)
				numLines--;
			numLines++;                                  
		}
	}
	else
	{
		cout << "Open Error" << endl;
		exit(1);
	}
	infile.close();
}
