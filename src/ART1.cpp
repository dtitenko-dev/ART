//
// Created by dtitenko on 6/8/17.
//

#include "../include/ART1.h"

static int		vectorSum(int *nodeArray, int n)
{
	int tempSum = 0;

	for(int i = 0; i < n; i++)
		tempSum += nodeArray[i];
	return tempSum;
}

static int		maximum(double *nodeArray, int m)
{
	int winner;
	bool foundNewWinner;

	winner = 0;
	do
	{
		foundNewWinner = false;
		for (int i = 0; i < m; i++)
		{
			foundNewWinner = nodeArray[i] > nodeArray[winner];
			winner = (foundNewWinner) ? i : winner;
		}
	}
	while (foundNewWinner);
	return winner;
}

static bool testForReset(int activSum, int inputSum,
						 double *f2Arr, int f2Max, double vglnc)
{
	double test = static_cast<double>(activSum) /
				  static_cast<double>(inputSum);
	bool ret = test < vglnc;

	ret ? f2Arr[f2Max] = -1.0 : 0;
	return ret;
}

ART1::ART1(int inputSize, int numClusters, double vglnc, int fntWdth,
		   int numTraining, t_vec_pat patts)
{
	Pattern = patts;
	n = inputSize;
	m = numClusters;
	vigilance = vglnc;
	fontWidth = fntWdth;
	trainingPatterns = numTraining;
	inPatterns = static_cast<int>(patts.size());

	//allocation
	bw = new double*[m];
	tw = new int*[m];
	for(int i = 0; i < m; i++)
	{
		bw[i] =  new double[n];
		tw[i] =  new int[n];
	}
	f1a = new int[n];
	f1b = new int[n];
	f2 = new double[m];
	membership = new int[inPatterns];
}

ART1::~ART1()
{
	delete[] f1a;
	delete[] f1b;
	delete[] f2;
	delete[] membership;
	for (int i = 0; i < m; i++)
	{
		delete[] bw[i];
		delete[] tw[i];
	}

	delete[] bw;
	delete[] tw;
}

void ART1::init_arrays()
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			bw[i][j] = 1.0 / (1.0 + n);
			tw[i][j] = 1;
		}
}

void ART1::updateWeights(int activSum, int f2Max)
{
	for (int i = 0; i < n; i++)
	{
		bw[f2Max][i] = (2.0 * f1b[i]) / (1.0 + activSum);
		tw[f2Max][i] = f1b[i];
	}
}

void ART1::exec()
{
	int		inputSum;
	int		activSum;
	int		f2Max;
	bool	reset;

	for (int vecNum = 0; vecNum < inPatterns; vecNum++)
	{
		for (int i = 0; i < m; i++)
			f2[i] = 0.0;
		for (int i = 0; i < n; i++)
		{
			f1a[i] = Pattern[vecNum][i];
			f1b[i] = f1a[i];
		}
		inputSum = vectorSum(f1a, n);
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				f2[i] += bw[i][j] * f1a[j];
		reset = true;
		do
		{
			f2Max = maximum(f2, m);
			for (int i = 0; i < n; i++)
				f1b[i] = f1a[i] * tw[f2Max][i];
			activSum = vectorSum(f1b, n);
			reset = testForReset(activSum, inputSum, f2, f2Max, vigilance);
		}
		while (reset);
		if (vecNum < trainingPatterns)
			updateWeights(activSum, f2Max);
		membership[vecNum] = f2Max;
	}
}

void ART1::printMembership()
{
	cout << "Input vectors assigned to each cluster:" << endl << endl;
	for (int i = 0; i < m; i++)
	{
		cout << "Cluster #" << i << ": ";
		for (int j = 0; j < inPatterns; j++)
		{
			if (membership[j] == i)
				cout << "\t" << paths[j].stem().string();
		}
		cout << endl;
	}
	cout << endl;
}

void ART1::printWeightValues()
{
	cout << "Final weight values for each cluster:" << endl << endl;
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n; j++)
		{
			cout << ((tw[i][j] > 0) ? "#" : ".");
			if(!((j + 1) % fontWidth))
				cout << endl;
		}
		cout << endl;
	}
}

const vector<boost::filesystem::path> &ART1::getPaths() const
{
	return paths;
}

void ART1::setPaths(const vector<boost::filesystem::path> &paths)
{
	this->paths = paths;
}
