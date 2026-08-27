#include<iostream>
#include<filesystem>
#include<unordered_map>
int main()
{
	std::cout << " *************** welcome to filexplor **********************" << "\n";
	std::filesystem::path folder = "folder";

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
		std::string category = categories[i.path().extension().string()];

		if (category == "Images")
			images++;
		else if (category == "Documents")
			docs++;
		else if (category == "Code")
			code++;
		else if (category == "Audio")
			audio++;
		else
			other++;
	}
	std::cout << "*********************" << "\n"
		<< "images : " << images << "\n" << "docs : " << docs << "\n" << "code : " << code << "\n"
		<< "audio : " << audio << "\n" << "other : " << other << "\n";

	return 0;
}