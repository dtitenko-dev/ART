//
// Created by dtitenko on 6/8/17.
//

#include "../include/Program.h"
#include "../include/ART.h"
#include "../include/ART1.h"


Program::Program(int argc, char **argv)
{
	try
	{
		TCLAP::CmdLine				cmd("", ' ', "0.1");
		TCLAP::SwitchArg			showClustersSwitch("S", "show-clusters",
			"Show final weight values for each cluster.", false
		);
		TCLAP::UnlabeledValueArg<std::string>
									folderPathArg("folder",
			"Path to the folder where the patterns are located.",
			true, ".", "folder"
		);
		TCLAP::UnlabeledValueArg<std::string>
									trainingFolderPathArg("training-folder",
			"Path to the folder where the training patterns are located.",
			true, ".", "training folder"
		);
		TCLAP::ValueArg<uint>		clustersMaxNumArg("m", "max-clusters",
			"Max number of clusters to be formed.", false, 10, "int"
		);
		TCLAP::ValueArg<uint>		bitsNumArg("n", "bits-num",
			"Number of components in an input vector(file).", false, 63, "int"
		);
		TCLAP::ValueArg<uint>		fontWidthArg("F", "font-width",
			"Number of symbols in one line of cluster.", false, 7, "int"
		);
		TCLAP::ValueArg<float>		vigilanceArg("V", "viglance",
			"Vigilance level (0.0f < v < 1.0).", false, 0.8, "float"
		);

		cmd.add(clustersMaxNumArg);
		cmd.add(bitsNumArg);
		cmd.add(fontWidthArg);
		cmd.add(vigilanceArg);
		cmd.add(showClustersSwitch);
		cmd.add(trainingFolderPathArg);
		cmd.add(folderPathArg);
		cmd.parse(argc, argv);
		showCluster = showClustersSwitch.getValue();
		folderPath = folderPathArg.getValue();
		trainPath = trainingFolderPathArg.getValue();
		clustersMaxNum = clustersMaxNumArg.getValue();
		bitsNum = bitsNumArg.getValue();
		fontWidth = fontWidthArg.getValue();
		vigilance = vigilanceArg.getValue();
	}
	catch (TCLAP::ArgException &e)
	{
		std::cerr << "error: " << e.error()
				  << " for arg " << e.argId() << std::endl;
	}

	fs::path root = fs::absolute(folderPath);
	fs::path trainRoot = fs::absolute(trainPath);
	get_files_in_folder(root, ".pat", paths);
	get_files_in_folder(trainRoot, ".pat", trainPaths);
	sort(paths.begin(), paths.end());
	sort(trainPaths.begin(), trainPaths.end());
	trainNum = static_cast<int>(trainPaths.size());
	patNum = static_cast<int>(paths.size());
}

Program::~Program()
{

}

void Program::_exec()
{
	compose_patterns(trainPaths, paths, patterns);
	ART1 art(bitsNum, clustersMaxNum, vigilance, fontWidth, trainNum, patterns);
	vector<fs::path> p;
	p.insert(p.end(), trainPaths.begin(), trainPaths.end());
	p.insert(p.end(), paths.begin(), paths.end());
	art.setPaths(p);
	art.init_arrays();
	art.exec();
	art.printMembership();
	if (showCluster)
		art.printWeightValues();
}
