//
// Created by dtitenko on 6/8/17.
//

#ifndef ART_PROGRAM_H
#define ART_PROGRAM_H

#include <iostream>
#include <string>
#include <algorithm>
#include <tclap/CmdLine.h>

#include "../include/boosters.h"

using namespace std;

class Program
{
	public:
		explicit	Program(int argv, char **argc);
		virtual		~Program();
		void		_exec();


	private:
		int					trainNum;
		int					patNum;
		bool				showCluster;
		string				folderPath;
		string				trainPath;
		uint				clustersMaxNum;
		uint				bitsNum;
		uint				fontWidth;
		float				vigilance;
		vector<fs::path>	paths;
		vector<fs::path>	trainPaths;
		t_vec_pat			patterns;
};

#endif //ART_PROGRAM_H
