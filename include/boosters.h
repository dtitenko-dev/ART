//
// Created by dtitenko on 6/8/17.
//

#ifndef ART_BOOSTERS_H
#define ART_BOOSTERS_H

#include "ART.h"

void	get_files_in_folder(const fs::path& root,
							const string& ext,
							vector<fs::path>& ret);

void	read_bits_from_file(const fs::path& filepath,
							vector<int>& ret);

void	compose_patterns(const vector<fs::path>& trainPaths,
						 const vector<fs::path>& paths,
						 t_vec_pat& ret);

#endif //ART_BOOSTERS_H
