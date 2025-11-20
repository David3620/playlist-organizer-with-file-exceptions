//CopyRight 2025
#include "PlayNode.h"
#include <iostream>
 #include <fstream>
using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::istringstream; 

PlayNode::PlayNode()
{
    ID = "none";
    songname = "none";
    artistname = "none";
    length = 0;
    nextnodeptr = nullptr;
}

PlayNode::PlayNode(string initID, string initSongName, string initArtistName, int initSongLength, PlayNode* nextLoc)
{
    this->ID = initID;
    this->songname = initSongName;
    this->artistname =  initArtistName;
    this->length = initSongLength;
    this->nextnodeptr = nextLoc;
}

void PlayNode::InsertAfter(PlayNode* nodePtr)
{
    PlayNode * next = this->GetNext();
    this->nextnodeptr = nodePtr;
    if (nodePtr!=nullptr)
    nodePtr->nextnodeptr = next;
    
}
PlayNode * PlayNode::GetNextPtr()
{
    return nextnodeptr;
}
PlayNode * PlayNode::GetNext()
{
    return nextnodeptr;
}

void PlayNode::SetNext(PlayNode* nodePtr)
{
    this->nextnodeptr = nodePtr;
}

string PlayNode::GetID() const
{
     //parsing string to extract ID
    istringstream iss(ID);
    string line;
    char del=':';
    getline(iss,line,del);
    iss>>line;
    return line;
    //return ID;
}

string PlayNode::GetSongName()const
{
    //parsing string to extract songname
    istringstream iss(songname);
    string line;
    char del=':';
    getline(iss,line,del);
    iss>>line;
    return line;
    //return songname;
}

string PlayNode::GetArtistName()const
{//parsing string to extract artistname
    istringstream iss(artistname);
    string line;
    char del=':';
    getline(iss,line,del);
    iss>>line;
    return line;
   // return artistname;
}

int PlayNode::GetSongLength()const
{
    return length;
}

void PlayNode::PrintNode()
{
    cout<<"Unique ID: "<<GetID()<<endl;
    cout<<"Song Name: "<<GetSongName()<<endl;
    cout<<"Artist Name: "<<GetArtistName()<<endl;
    cout<<"Song Length (in seconds): "<<GetSongLength() <<endl; 
}
