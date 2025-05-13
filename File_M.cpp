// #include "File_M.h"

// template <typename T>
// bool load_from_bin(const string &filename, T &s, int key)
// {
//     ifstream i(filename, ios::binary | ios::in);
//     long obj_pos = search_obj<T>(filename, key, s);

//     if (obj_pos == -1)

    
//     {
//         cout << "unable to find object" << endl;
//         return false;
//     }
//     if (i.is_open())
//     {
//         i.seekg(obj_pos);
//         i.read((char *) (&s), sizeof(T));
//         i.close();
//         return true;
//     }
//     else
//     {
//         FileException(filename);
//         i.close();
//         return false;
//     }
// }

// template <typename T1>
// bool save_to_bin(const string &filename, T1 &s, int key)
// {
//     fstream o(filename, ios::binary | ios::in | ios::out);
//     long obj_pos = search_obj<T1>(filename, key, s);

//     if (obj_pos == -1)
//     {
//         cout << "unable to find object" << endl;
//         return false;
//     }

//     if (o.is_open())
//     {
//         o.seekp(obj_pos);
//         o.write((char *) (&s), sizeof(T1));
//         o.close();
//         return true;
//     }
//     else
//     {
//         FileException(filename);
//         o.close();
//         return false;
//     }
// }

// template <typename T3>
// long search_obj(string filename, int key, T3 &o)
// {
//     ifstream i;
//     i.open(filename, ios::binary | ios::in);
//     long current_pos = -1;
//     i.seekg(0, ios::beg);
//     if (i.is_open())
//     {
//         while (!i.eof())
//         {
//             i.read(reinterpret_cast<char *>(&o), sizeof(T3));
//             if (o.check_id(key))
//             {
//                 current_pos = i.tellg() - sizeof(T3);
//                 i.close();
//                 return current_pos;
//             }
//         }
//         i.close();
//     }
//     else
//     {
//         FileException(filename);
//         return -1;
//     }
//     cout << "NOT FOUND" << endl;
//     return current_pos;
// }

// template<typename T4>
// bool create_obj_in_file(const string &filename, T4 &s)
// {
//         ofstream o;
//         o.open(filename,ios::out|ios::binary);
//         if (o.is_open())
//         {
//             o.write(reinterpret_cast<char*>(&o),sizeof(T4));
//             o.close();
//             return true;
//         }
//         else
//         {
//             FileException(filename);
//             return false;
//         }
// }

// template<typename T5>
// bool deleteObject(const string& filename, int idToDelete,T5 & obj) {
//     ifstream i(filename, ios::binary);
//     ofstream o("..\\FILES\\.Buffer_file.bin",ios::binary);

//     if (!i || !o) {
//         FileException(filename);
//         return false;
//     }

//     while (i.read(reinterpret_cast<char*>(&obj), sizeof(T5))) {
//         if (obj.comp != idToDelete) {
//             o.write(reinterpret_cast<const char*>(&obj), sizeof(T5));
//         }
//     }

//     i.close();
//     o.close();

//     std::remove(filename.c_str());
//     std::rename("..\\FILES\\Buffer_file.bin", filename.c_str());

//     cout << "Object with ID " << idToDelete << " deleted." << std::endl;
//     return  true;

// }