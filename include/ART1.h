//
// Created by dtitenko on 6/8/17.
//

#ifndef ART_ART1_H
#define ART_ART1_H


#include "ART.h"

class ART1
{
	public:
		explicit ART1(int inputSize, int numClusters,
					  double vglnc, int fntWdth,
					  int numTraining, t_vec_pat patts);
		virtual ~ART1();

		void init_arrays();
		void updateWeights(int activSum, int f2Max);
		void exec();
		void printMembership();
		void printWeightValues();

	private:
		int			inPatterns;
		int			trainingPatterns;
		int			n;
		int			m;
		int			fontWidth;
		double		vigilance;
		t_vec_pat	Pattern;
		double		**bw;
		int			**tw;
		int			*f1a, *f1b;
		double		*f2;
		int			*membership;
		bool		notFirstEpoch = false;

		vector<fs::path> paths;
	public:
		const vector<boost::filesystem::path> &getPaths() const;

		void setPaths(const vector<boost::filesystem::path> &paths);


};


#endif //ART_ART1_H
