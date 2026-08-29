#include<iostream>
#include<filesystem>
#include<unordered_map>
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

	for (const auto& i : std::filesystem::directory_iterator(folder))
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

	for (const auto& i : {images,docs,code,audio,other })
	{
		if (i != 0)
		{
			std::filesystem::create_directory(folder / list[j]);
		}
		j++;
	}

	for (const auto& i : std::filesystem::directory_iterator(folder))
	{
		if (!i.is_regular_file())
			continue;
			std::string category = categories[i.path().extension().string()];

			if (category == "Images")
			{
				std::filesystem::rename(i.path(), folder / "images" / i.path().filename());
			}
			else if (category == "Documents")
			{
				std::filesystem::rename(i.path(), folder / "docs" / i.path().filename());

			}
			else if (category == "Code")
			{
				std::filesystem::rename(i.path(), folder / "code" / i.path().filename());

			}
			else if (category == "Audio")
			{
				std::filesystem::rename(i.path(), folder / "audio" / i.path().filename());

			}
			else
			{
				std::filesystem::rename(i.path(), folder / "other" / i.path().filename());

			}
	}
	//display :
	std::cout << "*********************" << "\n"
		<< "images : " << images << "\n" << "docs : " << docs << "\n" << "code : " << code << "\n"
		<< "audio : " << audio << "\n" << "other : " << other << "\n";
	

	return 0;
}