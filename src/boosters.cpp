//
// Created by dtitenko on 6/8/17.
//
#include "../include/ART.h"

void	get_files_in_folder(const fs::path& root,
							const string& ext,
							vector<fs::path>& ret)
{
	if(!fs::exists(root) || !fs::is_directory(root)) return;

	fs::directory_iterator it(root);
	fs::directory_iterator endit;

	while(it != endit)
	{
		if(fs::is_regular_file(*it) && it->path().extension() == ext)
			ret.push_back(it->path());
		++it;
	}

}

void	read_bits_from_file(const fs::path& filepath,
							vector<int>& ret)
{
	fs::ifstream is(filepath);

	if (!is)
		throw runtime_error("No such file " + filepath.string());
	is.seekg(0, is.end);
	int length = is.tellg();
	is.seekg(0, is.beg);

	char *buf = new char[length];
	is.read(buf, length);
	if (!is)
		throw runtime_error("Can not read all chars from file");
	is.close();

	for (int i = 0; i < length; i++)
	{
		if (isspace(buf[i]))
			continue ;
		else if (!strchr("10", buf[i]))
			throw runtime_error(filepath.filename().string() + ": invalid file.");
		ret.push_back((buf[i] == '1') ? 1 : 0);
	}
	delete[] buf;
}

void	compose_patterns(const vector<fs::path>& trainPaths,
						 const vector<fs::path>& paths,
						 t_vec_pat& ret)
{
	vector<int> t;

	for (size_t i = 0; i < trainPaths.size(); i++)
	{
		read_bits_from_file(trainPaths[i], t);
		ret.push_back(t);
		t.clear();
	}

	for (size_t i = 0; i < paths.size(); i++)
	{
		read_bits_from_file(paths[i], t);
		ret.push_back(t);
		t.clear();
	}

}