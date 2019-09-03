#pragma once
#define DllExport __declspec( dllexport )

#include <string>
#include <fstream>
#include <Mark.h>

namespace sc
{
	/*!
	 * BitA is a handle to .bitA file format. This format consist form numbers,
	 * in first line we have two numbers declarating size of file. Then rest will represent
	 * "znak color znak color znak color" sume of them would be size_x * szie_y * 2 
	*/
	template<class T, class PathType = std::string>
	class DllExport BitA {
	public:
		/// Name of file
		std::string name;

		/// relative or absolute path to file
		PathType path;

		unsigned int size_x;
		unsigned int size_y;

		/// 2d array of marks ( znak + color )
		T **marks;

		// Maby making 2 seprate tables will help with preformance !

		/// Populate whole image with one mark
		void populate(int znak, short color);

		/// Save open file
		bool save();

		/// Open new .bitA file if not path specified ptrogram will look for file in its directory
 		bool load(PathType path);

		BitA(PathType file_path);
		BitA(PathType file_name, unsigned int sizeX, unsigned int sizeY);
		~BitA();

	private:
		void makeMarks(unsigned int sizeX, unsigned int sizeY);
		void clean();
	};

	template<class T, class PathType>
	BitA<T, PathType>::BitA(PathType file_path) {
		load(file_path);
	}

	template<class T, class PathType>
	BitA<T, PathType>::BitA(PathType file_name, unsigned int sizeX, unsigned int sizeY) {
		makeMarks(sizeX, sizeY);
		name = file_name;
		path = file_name;
		size_x = sizeX;
		size_y = sizeY;
	}

	template<class T, class PathType>
	BitA<T, PathType>::~BitA() {
		clean();
	}

	template<class T, class PathType>
	void sc::BitA<T, PathType>::makeMarks(unsigned int sizeX, unsigned int sizeY) {
		marks = new T *[sizeY];
		for (int i = 0; i < sizeY; ++i) {
			marks[i] = new T[sizeX];
		}
	}

	template<class T, class PathType>
	void sc::BitA<T, PathType>::clean() {

		for (int i = 0; i < size_y; ++i) {
			delete[] marks[i];
		}
		delete[] marks;
	}

	template<class T, class PathType>
	void BitA<T, PathType>::populate(int znak, short color) {
		for (int y = 0; y < size_y; y++) {
			for (int x = 0; x < size_x; x++) {
				marks[y][x].color = color;
				marks[y][x].znak = znak;
			}
		}
	}

	template<class T, class PathType>
	bool BitA<T, PathType>::save() {
		std::fstream file(path, std::ios::in | std::ios::out | std::ios::trunc);
		file << size_x << ' ' << size_y << std::endl; // save size

		// ======================================= save marks
		for (int y = 0; y < size_y; y++) {
			for (int x = 0; x < size_x; x++) {
				file << static_cast<int>(marks[y][x].color) << ' ' << static_cast<int>(marks[y][x].znak);
				if (x + 1 < size_x) file << ' ';
			}
			file << std::endl;
		}

		file.close();
		return true;
	}

	template<class T, class PathType>
	bool BitA<T, PathType>::load(PathType path) {
		this->path = path;

		clean();
		std::fstream file(path);

		if (!file.good())
			return false;

		file >> size_x >> size_y;
		makeMarks(size_x, size_y);

		int color, znak;

		// load marks
		for (int y = 0; y < size_y; y++) {
			for (int x = 0; x < size_x; x++) {
				file >> color >> znak;

				marks[y][x].color = color;
				marks[y][x].znak = znak;
			}
		}

		file.close();
		return false;
	}
}



