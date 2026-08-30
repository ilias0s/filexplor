#include<iostream>
#include<filesystem>
#include<unordered_map>
#include<vector>
int main()
{
	std::cout << " *************** welcome to filexplor **********************" << "\n"
		<< "enter the folder path : ";
	std::string folderpath;
	std::getline(std::cin, folderpath);
	std::filesystem::path folder = folderpath;


	std::unordered_map<std::string, std::string> categories;
	categories[".jpg"] = "Images";
	categories[".png"] = "Images";
	categories[".gif"] = "Images";

	categories[".pdf"] = "Documents";
	categories[".docx"] = "Documents";
	categories[".txt"] = "Documents";

	categories[".cpp"] = "Code";
	categories[".py"] = "Code";

	categories[".mp3"] = "Audio";
	categories[".wav"] = "Audio";
	int images = 0, docs = 0, code = 0, audio = 0, other = 0;

	for (const auto& i : std::filesystem::recursive_directory_iterator(folder))
	{
		if (!i.is_regular_file())
			continue;
			std::string category = categories[i.path().extension().string()];
			if (category == "Images")
			{
				images++;
			}
			else if (category == "Documents")
			{
				docs++;
			}
			else if (category == "Code")
			{
				code++;
			}
			else if (category == "Audio")
			{
				audio++;
			}
			else
			{
				other++;
			}
	}

	int j=0;
	std::string list[5] = { "images","docs","code","audio","other" };

	for (const auto& i : { images,docs,code,audio,other })
	{
		if (i != 0)
		{
			std::filesystem::create_directory(folder / list[j]);
		}
		j++;
	}

	std::vector <std::filesystem::path> v;

	for (const auto& i : std::filesystem::recursive_directory_iterator(folder))
	{
		if (!i.is_regular_file())
		continue;
		v.push_back(i.path());
	}

	for (const auto& i : v)
	{
			std::string category = categories[i.extension().string()];
			std::filesystem::path target;
			if (category == "Images")
			{
				target = folder / "images" / i.filename();
			}
			else if (category == "Documents")
			{
				target =  folder / "docs" / i.filename();

			}
			else if (category == "Code")
			{
				target =  folder / "code" / i.filename();

			}
			else if (category == "Audio")
			{
				target =  folder / "audio" / i.filename();

			}
			else
			{
				target = folder / "other" / i.filename();

			}

			if (i.parent_path() == target.parent_path())
				continue;
			std::filesystem::rename(i, target);

	}
	std::vector<std::filesystem::path> removelist;
	for (const auto& i : std::filesystem::recursive_directory_iterator(folder))
	{
		if (std::filesystem::is_empty(i))
		removelist.push_back(i.path());
	}
	for (const auto& i : removelist)
	{
		std::filesystem::remove_all(i);
	}

	//display :
	std::cout << "*********************" << "\n"
		<< "images : " << images << "\n" << "docs : " << docs << "\n" << "code : " << code << "\n"
		<< "audio : " << audio << "\n" << "other : " << other << "\n";
	

	return 0;
}