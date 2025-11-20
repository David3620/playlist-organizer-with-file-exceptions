//CopyRight 2025
#ifndef _PlayNodeH_
#define _PlayNodeH_
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using std::string;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::istream;
using std::ostringstream;
using std::ostream;
using std::cin;
using std::cout;
using std::istringstream;
using std::flush;

class PlayNode  
{
    private:
    string ID;
    string songname;
    string artistname;
    int length;
    PlayNode * nextnodeptr;

    public:
    PlayNode();
    PlayNode(string initID, string initSongName, string initArtistName, int initSongLength, PlayNode* nextLoc = 0);
    void InsertAfter(PlayNode* nodePtr);
    void SetNext(PlayNode* nodePtr);
    string GetID()const;
    string GetSongName()const;
    string GetArtistName()const;
    int GetSongLength()const;
    PlayNode * GetNext();
    void PrintNode();
    PlayNode * GetNextPtr();
    friend ostream& operator<<(ostream& out, PlayNode& node)
    {   
        out<<"Unique ID: "<<node.ID<<"|Song Name: "<<node.songname<<"|Artist Name: "<<node.artistname<<"|Song Length (in seconds): "<<node.length;
        return out;
    };

     friend istream& operator>>(istream& infs, PlayNode& node)
    {
        char delimiter = '|';
        
        getline(infs,node.ID,delimiter);
        getline(infs,node.songname,delimiter);
        getline(infs,node.artistname,delimiter);
      
        string line;
        int num;
        istringstream iss;
        getline(infs,line);
        iss.str(line);
        char del=':';
        getline(iss,line,del);
        iss>>num;
        node.length=num;
      
        return infs;
    };
};
#endif
