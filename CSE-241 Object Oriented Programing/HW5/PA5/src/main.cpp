#include "Field.h" /*Header file*/

class Fields  /*Fields is general class for holding all entry type.*/
{
public:

	class Title : public Field<string> 	/*Title field.*/
	{
	public:
		Title() {}
		Title(string content)
		{
			this->SetContent(content);
		}
	};

	class Authors : public Field<string> 	/*Authors field.*/
	{
	public:
		Authors() {}
		Authors(string content)
		{
			this->SetContent(content);
		}
	};

	class Year : public Field<string> 	/*Year field.*/
	{
	public:
		Year() {}
		Year(string content)
		{
			this->SetContent(content);
		}
	};

	class Tags : public Field<string>	/*Tags field.*/
	{
	public:
		Tags() {}
		Tags(string content)
		{
			this->SetContent(content);
		}
	};

	class Artists : public Field<string> 	/*Artists field.*/
	{
	public:
		Artists() {}
		Artists(string content)
		{
			this->SetContent(content);
		}
	};

	class Genre : public Field<string> 	/*Genre field.*/
	{
	public:
		Genre() {}
		Genre(string content)
		{
			this->SetContent(content);
		}
	};

	class Director : public Field<string> 	/*Director field.*/
	{
	public:
		Director() {}
		Director(string content)
		{
			this->SetContent(content);
		}
	};

	class Starring : public Field<string> 	/*Starring field.*/
	{
	public:
		Starring() {}
		Starring(string content)
		{
			this->SetContent(content);
		}
	};
};


class Catalogs /*Catalogs is a general class to hold all catalogs and products.*/
{
public:
	template <typename T, typename U, typename W, typename Y>
	class Book
	{
	private:
		T title;
		U authors;
		W year;
		Y tags;
	public:
		Book(T title, U authors, W year, Y tags)
		{
			this->title = title;
			this->authors = authors;
			this->year = year;
			this->tags = tags;

		}

		T GetTitle() const	/*Gets the title field.*/
		{
			return this->title;
		}
		U GetAuthors() const	/*Gets the authors field.*/
		{
			return this->authors;
		}
		W GetYear() const	/*Gets the year field.*/
		{
			return this->year;
		}
		Y GetTags() const /*Gets tag*/
		{

			return this->tags;
		}
		void SetTitle(T title)	/*Sets the title field.*/
		{
			this->title = title;
		}
		void SetAuthors(U authors) /*Sets author*/
		{
			this->authors = authors;
		}
		void SetYear(W year) /*Sets year*/
		{
			this->year = year;
		}
		void SetTags(Y tags) /*Sets tag*/
		{
			this->tags = tags;
		}
	};

	template <typename M, typename N, typename O, typename P>
	class Music
	{
	private:
		M title;
		N artists;
		O year;
		P genre;
	public:
		Music(M title, N artists, O year, P genre)
		{
			this->title = title;
			this->artists = artists;
			this->year = year;
			this->genre = genre;
		}

		M GetTitle() const
		{
			return this->title;
		}
		N GetArtists() const
		{
			return this->artists;
		}
		O GetYear() const
		{
			return this->year;
		}
		P GetGenre() const
		{
			return this->genre;
		}
	};

	template <typename A, typename B, typename C, typename D, typename E>
	class Movie
	{
	private:
		A title;
		B director;
		C year;
		D genre;
		E starring;
	public:
		Movie(A title, B director, C year, D genre, E starring)
		{
			this->title = title;
			this->director = director;
			this->year = year;
			this->genre = genre;
			this->starring = starring;
		}

		A GetTitle() const
		{
			return this->title;
		}
		B GetDirector() const
		{
			return this->director;
		}
		C GetYear() const
		{
			return this->year;
		}
		D GetGenre() const
		{
			return this->genre;
		}
		E GetStarring() const
		{
			return this->starring;
		}
	};


	class BookCatalog 	/*Book catalog class.*/
	{
	private:

		vector<Book<Fields::Title, Fields::Authors, Fields::Year, Fields::Tags>> books;	 	/*Holds all books in the data.*/
	public:
		BookCatalog()
		{
			
		}

		/*Default-empty book.*/
		Book<Fields::Title, Fields::Authors, Fields::Year, Fields::Tags> Default =
			Book<Fields::Title, Fields::Authors, Fields::Year, Fields::Tags>(Fields::Title("Title"), Fields::Authors("Authors"), Fields::Year("0"), Fields::Tags("Tags"));
		void AddBook(Book<Fields::Title, Fields::Authors, Fields::Year, Fields::Tags> book)	/*Adds book to list.*/
		{
			this->books.push_back(book);
		}
		Book<Fields::Title, Fields::Authors, Fields::Year, Fields::Tags> GetBook(int index) const	/*Gets the book that is given its index.*/
		{
			return this->books[index];
		}
		int CountBook() const	/*Gets the count of books in the list.*/
		{
			return this->books.size();
		}
		string GetString(int index) const	/*Format in string.*/
		{
			return this->books[index].GetTitle().GetContent() + " " + this->books[index].GetAuthors().GetContent() +
				" " + this->books[index].GetYear().GetContent() + " " + this->books[index].GetTags().GetContent();
		}
		vector<int>* Search(string value, Field<string>::FieldType field)	/*Search the value in given field in the list.*/
		{
			vector<int>* mapping = new vector<int>();	/*Hold all indices of found value.*/
			if (field == Field<string>::FieldType::Title)	/*Field type.*/
			{
				for (int i = 0; i < this->books.size(); i++)	/*Loop for count of the books in list (linear search).*/
				{
					if (this->books[i].GetTitle().GetContent().find(value) != string::npos)	/*Equalization.*/
						mapping->push_back(i);	/*If there is value in that field, push to list.*/
				}
			}
			else if (field == Field<string>::FieldType::Authors)
			{
				for (int i = 0; i < this->books.size(); i++)
				{
					if (this->books[i].GetAuthors().GetContent().find(value) != string::npos)
						mapping->push_back(i);
				}
			}
			else if (field == Field<string>::FieldType::Year)
			{
				for (int i = 0; i < this->books.size(); i++)
				{
					if (this->books[i].GetYear().GetContent().find(value) != string::npos)
						mapping->push_back(i);
				}
			}
			else if (field == Field<string>::FieldType::Tags)
			{
				for (int i = 0; i < this->books.size(); i++)
				{
					if (this->books[i].GetTags().GetContent().find(value) != string::npos)
						mapping->push_back(i);
				}
			}
			else
				return NULL;	/*If a book has empty field, return null to detect the error.*/

			return mapping;
		}
		bool Sort(Field<string>::FieldType field)	/*Sorting algorithm in given field in the list.*/
		{
			Catalogs::Book<Fields::Title, Fields::Authors, Fields::Year, Fields::Tags> temp = this->Default;

			if (field != Field<string>::FieldType::Title && field != Field<string>::FieldType::Authors
				&& field != Field<string>::FieldType::Year && field != Field<string>::FieldType::Tags)
				return false;

			int iCv, k;
			for (iCv = 1; iCv < this->books.size(); ++iCv)
			{
				temp = this->books[iCv];
				if (field == Field<string>::FieldType::Title)
				{
					for (k = iCv - 1; k >= 0 && this->books[k].GetTitle().GetContent() > temp.GetTitle().GetContent(); k--)
						this->books[k + 1] = this->books[k];
				}
				else if (field == Field<string>::FieldType::Authors)
				{
					for (k = iCv - 1; k >= 0 && this->books[k].GetAuthors().GetContent() > temp.GetAuthors().GetContent(); k--)
						this->books[k + 1] = this->books[k];
				}
				else if (field == Field<string>::FieldType::Year)
				{
					for (k = iCv - 1; k >= 0 && this->books[k].GetYear().GetContent() > temp.GetYear().GetContent(); k--)
						this->books[k + 1] = this->books[k];
				}
				else if (field == Field<string>::FieldType::Tags)
				{
					for (k = iCv - 1; k >= 0 && this->books[k].GetTags().GetContent() > temp.GetTags().GetContent(); k--)
						this->books[k + 1] = this->books[k];
				}
				else
					return false;
				this->books[k + 1] = temp;
			}
			return true;
		}
	};

	class MusicCatalog /*Music catalog class*/
	{
	private:
		vector<Music<Fields::Title, Fields::Artists, Fields::Year, Fields::Genre>> music;
	public:
		MusicCatalog() {}

		Music<Fields::Title, Fields::Artists, Fields::Year, Fields::Genre> Default =
			Music<Fields::Title, Fields::Artists, Fields::Year, Fields::Genre>(Fields::Title("Title"), Fields::Artists("Artists"), Fields::Year("0"), Fields::Genre("Genre"));
		void AddMusic(Music<Fields::Title, Fields::Artists, Fields::Year, Fields::Genre> music)
		{
			this->music.push_back(music);
		}
		Music<Fields::Title, Fields::Artists, Fields::Year, Fields::Genre> GetMusic(int index) const
		{
			return this->music[index];
		}
		int CountMusic() const
		{
			return this->music.size();
		}
		string GetString(int index) const
		{
			return this->music[index].GetTitle().GetContent() + " " + this->music[index].GetArtists().GetContent() +
				" " + this->music[index].GetYear().GetContent() + " " + this->music[index].GetGenre().GetContent();
		}
		vector<int>* Search(string value, Field<string>::FieldType field)
		{
			vector<int>* mapping = new vector<int>();
			if (field == Field<string>::FieldType::Title)
			{
				for (int i = 0; i < this->music.size(); i++)
				{
					if (this->music[i].GetTitle().GetContent().find(value) != string::npos)
						mapping->push_back(i);
				}
			}
			else if (field == Field<string>::FieldType::Artists)
			{
				for (int i = 0; i < this->music.size(); i++)
				{
					if (this->music[i].GetArtists().GetContent().find(value) != string::npos)
						mapping->push_back(i);
				}
			}
			else if (field == Field<string>::FieldType::Year)
			{
				for (int i = 0; i < this->music.size(); i++)
				{
					if (this->music[i].GetYear().GetContent().find(value) != string::npos)
						mapping->push_back(i);
				}
			}
			else if (field == Field<string>::FieldType::Genre)
			{
				for (int i = 0; i < this->music.size(); i++)
				{
					if (this->music[i].GetGenre().GetContent().find(value) != string::npos)
						mapping->push_back(i);
				}
			}
			else
				return NULL;

			return mapping;
		}
		bool Sort(Field<string>::FieldType field)
		{
			Catalogs::Music<Fields::Title, Fields::Artists, Fields::Year, Fields::Genre> temp = this->Default;

			if (field != Field<string>::FieldType::Title && field != Field<string>::FieldType::Artists
				&& field != Field<string>::FieldType::Year && field != Field<string>::FieldType::Genre)
				return false;

			int iCv, k;
			for (iCv = 1; iCv < this->music.size(); ++iCv)
			{
				temp = this->music[iCv];
				if (field == Field<string>::FieldType::Title)
				{
					for (k = iCv - 1; k >= 0 && this->music[k].GetTitle().GetContent() > temp.GetTitle().GetContent(); k--)
						this->music[k + 1] = this->music[k];
				}
				else if (field == Field<string>::FieldType::Authors)
				{
					for (k = iCv - 1; k >= 0 && this->music[k].GetArtists().GetContent() > temp.GetArtists().GetContent(); k--)
						this->music[k + 1] = this->music[k];
				}
				else if (field == Field<string>::FieldType::Year)
				{
					for (k = iCv - 1; k >= 0 && this->music[k].GetYear().GetContent() > temp.GetYear().GetContent(); k--)
						this->music[k + 1] = this->music[k];
				}
				else if (field == Field<string>::FieldType::Tags)
				{
					for (k = iCv - 1; k >= 0 && this->music[k].GetGenre().GetContent() > temp.GetGenre().GetContent(); k--)
						this->music[k + 1] = this->music[k];
				}
				else
					return false;
				this->music[k + 1] = temp;
			}
			return true;
		}
	};

	class MovieCatalog /*Movie catalog class*/
	{
	private:
		vector<Movie<Fields::Title, Fields::Director, Fields::Year, Fields::Genre, Fields::Starring>> movies;
	public:
		MovieCatalog() {}

		Movie<Fields::Title, Fields::Director, Fields::Year, Fields::Genre, Fields::Starring> Default =
			Movie<Fields::Title, Fields::Director, Fields::Year, Fields::Genre, Fields::Starring>(Fields::Title("Title"),
				Fields::Director("Director"), Fields::Year("0"), Fields::Genre("Genre"), Fields::Starring("Starring"));
		void AddMovie(Movie<Fields::Title, Fields::Director, Fields::Year, Fields::Genre, Fields::Starring> movie)
		{
			this->movies.push_back(movie);
		}
		Movie<Fields::Title, Fields::Director, Fields::Year, Fields::Genre, Fields::Starring> GetMovie(int index) const
		{
			return this->movies[index];
		}
		int CountMovie() const
		{
			return this->movies.size();
		}
		string GetString(int index) const
		{
			return this->movies[index].GetTitle().GetContent() + " " + this->movies[index].GetDirector().GetContent() +
				" " + this->movies[index].GetYear().GetContent() + " " + this->movies[index].GetGenre().GetContent() +
				" " + this->movies[index].GetStarring().GetContent();
		}
		vector<int>* Search(string value, Field<string>::FieldType field)
		{
			vector<int>* mapping = new vector<int>();
			if (field == Field<string>::FieldType::Title)
			{
				for (int i = 0; i < this->movies.size(); i++)
				{
					if (this->movies[i].GetTitle().GetContent().find(value) != string::npos)
						mapping->push_back(i);
				}
			}
			else if (field == Field<string>::FieldType::Director)
			{
				for (int i = 0; i < this->movies.size(); i++)
				{
					if (this->movies[i].GetDirector().GetContent().find(value) != string::npos)
						mapping->push_back(i);
				}
			}
			else if (field == Field<string>::FieldType::Year)
			{
				for (int i = 0; i < this->movies.size(); i++)
				{
					if (this->movies[i].GetYear().GetContent().find(value) != string::npos)
						mapping->push_back(i);
				}
			}
			else if (field == Field<string>::FieldType::Genre)
			{
				for (int i = 0; i < this->movies.size(); i++)
				{
					if (this->movies[i].GetGenre().GetContent().find(value) != string::npos)
						mapping->push_back(i);
				}
			}
			else if (field == Field<string>::FieldType::Starring)
			{
				for (int i = 0; i < this->movies.size(); i++)
				{
					if (this->movies[i].GetStarring().GetContent().find(value) != string::npos)
						mapping->push_back(i);
				}
			}
			else
				return NULL;

			return mapping;
		}
		bool Sort(Field<string>::FieldType field)
		{
			Catalogs::Movie<Fields::Title, Fields::Director, Fields::Year, Fields::Genre, Fields::Starring> temp = this->Default;

			if (field != Field<string>::FieldType::Title && field != Field<string>::FieldType::Director
				&& field != Field<string>::FieldType::Year && field != Field<string>::FieldType::Genre && field != Field<string>::FieldType::Starring)
				return false;

			int iCv, k;
			for (iCv = 1; iCv < this->movies.size(); ++iCv)
			{
				temp = this->movies[iCv];
				if (field == Field<string>::FieldType::Title)
				{
					for (k = iCv - 1; k >= 0 && this->movies[k].GetTitle().GetContent() > temp.GetTitle().GetContent(); k--)
						this->movies[k + 1] = this->movies[k];
				}
				else if (field == Field<string>::FieldType::Director)
				{
					for (k = iCv - 1; k >= 0 && this->movies[k].GetDirector().GetContent() > temp.GetDirector().GetContent(); k--)
						this->movies[k + 1] = this->movies[k];
				}
				else if (field == Field<string>::FieldType::Year)
				{
					for (k = iCv - 1; k >= 0 && this->movies[k].GetYear().GetContent() > temp.GetYear().GetContent(); k--)
						this->movies[k + 1] = this->movies[k];
				}
				else if (field == Field<string>::FieldType::Genre)
				{
					for (k = iCv - 1; k >= 0 && this->movies[k].GetGenre().GetContent() > temp.GetGenre().GetContent(); k--)
						this->movies[k + 1] = this->movies[k];
				}
				else if (field == Field<string>::FieldType::Starring)
				{
					for (k = iCv - 1; k >= 0 && this->movies[k].GetStarring().GetContent() > temp.GetStarring().GetContent(); k--)
						this->movies[k + 1] = this->movies[k];
				}
				else
					return false;
				this->movies[k + 1] = temp;
			}
			return true;
		}
	};
};

class Streams
{
public:

	class StreamReader 	/*Reads the given file and return data as a list.*/
	{
	private:
		string fileName;	/*Holds the name of file.*/
	public:
		StreamReader(string fileName)
		{
			this->fileName = fileName;
		}


		vector<string>* ReadFile()  		/*Read the file and return data line by line.*/
		{
			vector<string>* data = new vector<string>();
			fstream file;
			file.open(this->fileName, ios::in);

			string line;
			if (file.is_open())
			{
				while (!file.eof())
				{
					getline(file, line);
					data->push_back(line);
				}
			}
			file.close();
			return data;
		}
	};


	class StreamWriter  	/*Write data to specified file.*/
	{
	private:
		string fileName;
	public:
		StreamWriter(string fileName)
		{
			this->fileName = fileName;
		}

		void WriteFile(vector<string>* data)
		{
			if (data == NULL)
				return;

			fstream file;
			file.open(this->fileName, ios::out);

			if (file.is_open())
			{
				for (int i = 0; i < data->size(); i++)
				{

					string line = (*data)[i] + "\n";
					file.write(line.c_str(), (*data)[i].size() + 1);
				}
			}
			file.close();

		}
	};
};



class Application  /*Simulation (core) class.*/
{
private:
	string dataFile;	/*The name of input file. "data.txt"*/
	string commandFile;	/*The name of command file. "commands.txt"*/
	string outputFile;	/*The name of output file. "output.txt"*/
	Catalogs::BookCatalog books;	/*All books in the data file.*/
	Catalogs::MusicCatalog music;	/*All musics "	"	"	"*/
	Catalogs::MovieCatalog movies;	/*All movies.*/
	vector<string>* output = new vector<string>();	/*Output data that was rendered by core.*/
public:
	enum CatalogTypes
	{
		Book = 0,
		Music = 1,
		Movie = 2,
	};
	enum Commands
	{
		Search = 0,
		Sort = 1,

		EmptyCommand = 999,
	};

	
	Application(string datafile, string commandfile, string outputfile)  /*Constructor method to take the names of files.*/
	{
		this->dataFile = datafile; /*Input file*/
		this->commandFile = commandfile; /*Command file*/
		this->outputFile = outputfile; /*Output file*/
	}
	bool ControlDuplicate(CatalogTypes type, Fields::Title title)	/*Controls duplicates for that catalog.*/
	{
		switch (type)
		{
		case Application::Book:
			for (int i = 0; i < this->books.CountBook(); i++)
			{
				if (this->books.GetBook(i).GetTitle().GetContent() == title.GetContent())
					return true;
			}
			return false;
		case Application::Music:
			for (int i = 0; i < this->music.CountMusic(); i++)
			{
				if (this->music.GetMusic(i).GetTitle().GetContent() == title.GetContent())
					return true;
			}
			return false;
		case Application::Movie:
			for (int i = 0; i < this->movies.CountMovie(); i++)
			{
				if (this->movies.GetMovie(i).GetTitle().GetContent() == title.GetContent())
					return true;
			}
			return false;
		}
		return false;
	}
	vector<string>* Split(string data)	/*Split the data to string list by using the reagents -> "\""*/
	{
		vector<string>* splited = new vector<string>();
		
		string splash = "";
		bool lock = false;
		for (auto x : data)
		{
			if (x == '\"' && splash == "")
			{
				lock = true;
				splash += x;
			}
			else if (x == '\"' && splash != "")
			{
				lock = false;
				splash += x;
				splited->push_back(splash);
				splash = "";
			}
			else if (lock)
				splash += x;
		}

		return splited;
	}
	void CreateCatalogs()	/*Crate all catalogs (book, music and movie) and render data file.*/
	{
		Streams::StreamReader read = Streams::StreamReader(this->dataFile);	
		vector<string>* data = read.ReadFile();	/*Reads the input file.*/

		int size = data->size();
		if (size <= 1)
			return;

		string Entries[] = { "book", "music", "movie" };	/*Defines to entries.*/
		CatalogTypes catalog_type = CatalogTypes::Book;

		string entry = (*data)[0];	/*Gets the entry from input file.*/

		string entry_output = "Catalog Read: " + entry;	/*Makes output for entry flag.*/
		this->output->push_back(entry_output);	/*Loads entry output to the array.*/
		
		for (int i = 1; i < size; i++)	/*Counts line of the data.*/
		{
			vector<string>* splited = this->Split((*data)[i]);	/*Split the line.*/
			if (entry == Entries[0])	/*If entry is Book*/
			{
				if (splited->size() == 4)
				{
					catalog_type = CatalogTypes::Book;
					Catalogs::Book<Fields::Title, Fields::Authors, Fields::Year, Fields::Tags> book =
						Catalogs::Book<Fields::Title, Fields::Authors, Fields::Year, Fields::Tags>(Fields::Title((*splited)[0]),
							Fields::Authors((*splited)[1]), Fields::Year((*splited)[2]), Fields::Tags((*splited)[3]));

					if (this->ControlDuplicate(CatalogTypes::Book, book.GetTitle()))
					{
						string exception_handler = "Exception: duplicate entry";
						this->output->push_back(exception_handler);
						this->output->push_back((*data)[i]);
					}
					else
					{
						this->books.AddBook(book);
					}
				}
				else
				{
					this->output->push_back("Exception: missing field");
					this->output->push_back((*data)[i]);
				}
			}
			else if (entry == Entries[1])	/*If entry is Music*/
			{
				if (splited->size() == 4)
				{
					catalog_type = CatalogTypes::Music;
					Catalogs::Music<Fields::Title, Fields::Artists, Fields::Year, Fields::Genre> mus =
						Catalogs::Music<Fields::Title, Fields::Artists, Fields::Year, Fields::Genre>(Fields::Title((*splited)[0]),
							Fields::Artists((*splited)[1]), Fields::Year((*splited)[2]), Fields::Genre((*splited)[3]));

					if (this->ControlDuplicate(CatalogTypes::Music, mus.GetTitle()))
					{
						string exception_handler = "Exception: duplicate entry";
						this->output->push_back(exception_handler);
						this->output->push_back((*data)[i]);
					}
					else
						this->music.AddMusic(mus);
				}
				else
				{
					this->output->push_back("Exception: missing field");
					this->output->push_back((*data)[i]);
				}
			}
			else /*If entry is Movie*/
			{
				if (splited->size() == 5)
				{
					catalog_type = CatalogTypes::Movie;
					Catalogs::Movie<Fields::Title, Fields::Director, Fields::Year, Fields::Genre, Fields::Starring> movie =
						Catalogs::Movie<Fields::Title, Fields::Director, Fields::Year, Fields::Genre, Fields::Starring>
						(Fields::Title((*splited)[0]), Fields::Director((*splited)[1]), Fields::Year((*splited)[2]),
							Fields::Genre((*splited)[3]), Fields::Starring((*splited)[4]));

					if (this->ControlDuplicate(CatalogTypes::Movie, movie.GetTitle()))
					{
						string exception_handler = "Exception: duplicate entry";
						this->output->push_back(exception_handler);
						this->output->push_back((*data)[i]);
					}
					else
						this->movies.AddMovie(movie);
				}
				else
				{
					this->output->push_back("Exception: missing field");
					this->output->push_back((*data)[i]);
				}
			}
		}

		string unique_entries = "";
		switch (catalog_type)
		{
		case Application::Book:
			unique_entries += to_string(this->books.CountBook());
			break;
		case Application::Music:
			unique_entries += to_string(this->music.CountMusic());
			break;
		case Application::Movie:
			unique_entries += to_string(this->movies.CountMovie());
			break;
		}
		unique_entries += " unique entries";
		this->output->push_back(unique_entries);
	}
	void ProcessCommands()	/*Render commands.*/
	{
		Streams::StreamReader read = Streams::StreamReader(this->commandFile);	/*Read the command file.*/
		vector<string>* commands = read.ReadFile();	/*Reads all commands.*/

		for (int i = 0; i < commands->size(); i++)	/*Loop for count of commands in the file.*/
		{
			Commands cmd = this->GetCommand((*commands)[i]);	/*Transform.*/
			switch (cmd)
			{
			case Application::Search:
			{

				vector<string>* splited = this->Split((*commands)[i]); 				/*Prepare the data for suitable format.*/
				string value = (*splited)[0].substr(1, (*splited)[0].size() - 1);
				value = value.substr(0, value.size() - 2);
				string field = (*splited)[1].substr(1, (*splited)[1].size() - 1);
				field = field.substr(0, field.size() - 1);

				if (this->books.CountBook() != 0)
				{
					vector<int>* map = this->books.Search(value, Field<string>::Transform(field));	/*Search.*/
					if (map == NULL)	/*If map is null, there is the error called command is wrong.*/
					{
						this->output->push_back("Exception: command is wrong");
						this->output->push_back((*commands)[i]);
					}
					else
					{
						if (map->size() != 0)
							this->output->push_back((*commands)[i]);	/*Push command.*/
						for (int p = 0; p < map->size(); p++)
							this->output->push_back(this->books.GetString((*map)[p]));	/*Push found books.*/
					}
				}
				
				if (this->music.CountMusic() != 0)
				{
					vector<int>* map = this->music.Search(value, Field<string>::Transform(field));
					if (map == NULL)
					{
						this->output->push_back("Exception: command is wrong");
						this->output->push_back((*commands)[i]);
					}
					else
					{
						if (map->size() != 0)
							this->output->push_back((*commands)[i]);
						for (int p = 0; p < map->size(); p++)
							this->output->push_back(this->music.GetString((*map)[p]));
					}
				}
				
				if (this->movies.CountMovie() != 0)
				{
					vector<int>* map = this->movies.Search(value, Field<string>::Transform(field));
					if (map == NULL)
					{
						this->output->push_back("Exception: command is wrong");
						this->output->push_back((*commands)[i]);
					}
					else
					{
						if (map->size() != 0)
							this->output->push_back((*commands)[i]);
						for (int p = 0; p < map->size(); p++)
							this->output->push_back(this->movies.GetString((*map)[p]));
					}
				}

				break;
			}
			case Application::Sort:	/*Render sort algorithm.*/
			{
				vector<string>* splited = this->Split((*commands)[i]);
				string field = (*splited)[0].substr(1, (*splited)[0].size() - 1);
				field = field.substr(0, field.size() - 1);

				if (this->books.CountBook() != 0)
				{
					bool state = this->books.Sort(Field<string>::Transform(field));	/*Sorting.*/
					if (state)
					{
						this->output->push_back((*commands)[i]);
						for (int i = 0; i < this->books.CountBook(); i++)
							this->output->push_back(this->books.GetString(i));
					}
					else
					{
						this->output->push_back("Exception: command is wrong");
						this->output->push_back((*commands)[i]);
					}
				}
				if (this->music.CountMusic() != 0)
				{
					bool state = this->music.Sort(Field<string>::Transform(field));
					if (state)
					{
						this->output->push_back((*commands)[i]);
						for (int i = 0; i < this->music.CountMusic(); i++)
							this->output->push_back(this->music.GetString(i));
					}
					else
					{
						this->output->push_back("Exception: command is wrong");
						this->output->push_back((*commands)[i]);
					}
				}
				if (this->movies.CountMovie() != 0)
				{
					bool state = this->movies.Sort(Field<string>::Transform(field));
					if (state)
					{
						this->output->push_back((*commands)[i]);
						for (int i = 0; i < this->movies.CountMovie(); i++)
							this->output->push_back(this->movies.GetString(i));
					}
					else
					{
						this->output->push_back("Exception: command is wrong");
						this->output->push_back((*commands)[i]);
					}
				}
				break;
			}
			case Application::EmptyCommand:
				this->output->push_back("Exception: command is wrong");
				this->output->push_back((*commands)[i]);
				break;
			}
		}
	}
	Commands GetCommand(string data)
	{
		vector<string> command;
		bool lock = 0;
		string cmd = "";
		for (auto x : data)
		{
			if (lock) 
			{
				if (x == '\"')
					lock = !lock;
			}	
			else
			{
				if (x == '\"')
					lock = !lock;
				else if (x == ' ')
				{
					if (cmd == "search")
						command.push_back(cmd);
					else if (cmd == "in")
						command.push_back(cmd);
					else if (cmd == "sort")
						return Commands::Sort;
					cmd = "";
				}
				else
					cmd += x;
			}
		}

		if (command.size() == 2)
		{
			if (command[0] == "search" && command[1] == "in")
				return Commands::Search;
		}

		return Commands::EmptyCommand;
	}

	void WriteOutput()	/*Print sto the file.*/
	{
		Streams::StreamWriter write = Streams::StreamWriter(this->outputFile);
		write.WriteFile(this->output);
	}
};

int main()
{
	Application app = Application("data.txt", "commands.txt", "output.txt");	/*Creates application object.*/
	
	app.CreateCatalogs(); 	/*Creates catalogs and data Render():*/
	app.ProcessCommands(); 	/*Reads all commands.*/
	app.WriteOutput();	/*Prints to file.*/
	return 0;
}

