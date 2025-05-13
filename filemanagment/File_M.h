#ifndef FILE_M
#define FILE_M

#include <iostream>
#include <fstream>


using namespace std;


struct FileException
{
  FileException()
  {
    cerr << "File exception: " << endl;
  }
  FileException(string file)
  {
    cout << endl
         << "'" << file << "'" << " could not be opened." << endl;
  }
};


template <typename T3>
long search_obj(string filename, int key, T3 &o)
{   cout<<"in serch_obj";
    ifstream i;
    i.open(filename, ios::binary | ios::in);
    long current_pos = -1;
    i.seekg(0, ios::beg);
    if (i.is_open())
    {
        while (!i.eof())
        {
            
            i.read(reinterpret_cast<char *>(&o), sizeof(T3));
            if (o.check_id(key))
            {
                current_pos = i.tellg() - sizeof(T3);
                i.close();
                return current_pos;
            }
            else
            {
                cout<<"id doesnot match"<<endl;
            }
        }
        i.close();
    }
    else
    {
        cout<<"file not open";
        FileException(filename);
        return -1;
    }
    return current_pos;
}



template <typename T>
bool load_from_bin(const string &filename, T &s, int key)
{
    ifstream i(filename, ios::binary | ios::in |ios::ate);
    long obj_pos = search_obj(filename, key, s);
    i.seekg(0,ios::beg);
    cout<<obj_pos;
    if (obj_pos == -1)
    {
        cout << "unable to find object" << endl;
        return false;
    }
    else if (i.is_open())
    {
        i.seekg(obj_pos,ios::beg);
        i.read(reinterpret_cast<char *> (&s), sizeof(T));
        i.close();
        return true;
    }
    else
    {
        FileException(filename);
        i.close();
        return false;
    }
}

template <typename T1>
bool save_to_bin(const string &filename, T1 &s, int key)
{
    cout<<"INside save to bin";
    fstream o(filename, ios::binary | ios::in | ios::out);
    long obj_pos = search_obj<T1>(filename, key, s);

    if (obj_pos == -1)
    {
        cout << "unable to find object" << endl;
        return false;
    }

    if (o.is_open())
    {
        o.seekp(obj_pos,ios::beg);
        o.write(reinterpret_cast<char *> (&s), sizeof(T1));
        o.close();
        return true;
    }
    else
    {
        FileException(filename);
        o.close();
        return false;
    }
}


template<typename T4>
bool create_obj_in_file(const string &filename, T4 &s)
{
        ofstream o;
        o.open(filename,ios::out|ios::binary| ios::app);

        if (o.is_open())
        {
            o.write(reinterpret_cast<char*>(&s),sizeof(T4));
            o.close();
            return true;
        }
        else
        {
            FileException(filename);
            return false;
        }
}

template<typename T5>
bool deleteObject(const string& filename, int idToDelete,T5 & obj) {
    ifstream i(filename, ios::binary);
    ofstream o("..\\FILES\\Buffer_file.bin",ios::binary);

    if (!i || !o) {
        FileException(filename);
        return false;
    }

    while (i.read(reinterpret_cast<char*>(&obj), sizeof(T5))) {
        if (obj.check_id(idToDelete)) {
            o.write(reinterpret_cast<const char*>(&obj), sizeof(T5));
        }
    }

    i.close();
    o.close();

    std::remove(filename.c_str());
    std::rename("..\\FILES\\Buffer_file.bin", filename.c_str());

    cout << "Object with ID " << idToDelete << " deleted." << std::endl;
    return  true;

}

inline int return_no_of_acc_present(string filename)
{
    int temp;
    fstream i(filename, ios::in | ios::out);
    i.seekg(0,ios::beg);
    i>>temp;
    i.close();
    return temp;
}

inline void update_no_of_acc(string filename,int n)
{
    fstream i(filename, ios::trunc | ios::out);
    i.seekg(0,ios::beg);
    i<<n;

    i.close(); 
}

// template<typename T5>
// bool updateObject(const std::string &filename, int idToUpdate, const T5 &newData) {
//     std::ifstream i(filename, std::ios::binary);
//     std::ofstream o("..\\FILES\\Buffer_file1.bin", std::ios::binary);

//     if (!i || !o) {
//         FileException(filename); // Handle the exception case as needed
//         return false;
//     }

//     bool objectFound = false;

//     // Step 1: Read the file object by object
//     while (i.read(reinterpret_cast<char*>(&newData), sizeof(T5))) {
//         if (obj.check_id(idToUpdate)) {
//             // Step 2: If the ID matches, write the updated object
//             o.write(reinterpret_cast<const char*>(&newData), sizeof(T5));
//             objectFound = true;
//         } else {
//             // Otherwise, write the original object
//             o.write(reinterpret_cast<const char*>(&obj), sizeof(T5));
//         }
//     }

//     i.close();
//     o.close();

//     // Step 3: Replace the original file with the updated file
//     std::remove(filename.c_str());
//     std::rename("..\\FILES\\Buffer_file1.bin", filename.c_str());

//     if (!objectFound) {
//         std::cerr << "Object with ID " << idToUpdate << " not found." << std::endl;
//         return false;
//     }

//     std::cout << "Object with ID " << idToUpdate << " updated successfully." << std::endl;
//     return true;
// }


#endif