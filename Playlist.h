//CopyRight2025
#ifndef _PLAYLISTH_
#define _PLAYLISTH_
#include "PlayNode.h"
#include <iostream>
class Playlist
{
    private:
    PlayNode * headnode;
    PlayNode * tailnode;
    
    public:
    Playlist();
    ~Playlist();
    PlayNode* GetHead()const;
    PlayNode* GetTail()const;
    void AddSong(const string& uniqueID, const string& songName, const string& artistName, int songLength);
    bool RemoveSong(const string& uniqueID );
    bool ChangePosition(int songPosition, int newPosition);
    void OutputSongsByArtist(const string& artistName)const;
    int OutputTotalTime() const;
    void OutputFullPlaylist(const string& playlistTitle) const;
    bool IsEmpty() const;

    friend ostream& operator<<(ostream& out, Playlist& ll)
    {   
       PlayNode*temp = ll.GetHead();
       if (temp==nullptr)
       {
        out<<"Playlist is empty"<<endl;
       }
       int counter=1;
       while (temp!=nullptr)
       {
        out<<counter<<"."<<endl;
        counter++;
        out<<temp->GetID()<<"|"<<temp->GetSongName()<<"|"<<temp->GetArtistName()<<"|"<<temp->GetSongLength()<<"\n";
        temp=temp->GetNextPtr();
        }
        return out;
    };
    
    bool saveSongList(const std::string& filename);
    bool loadSongList(const std::string& filename);

    void saveSongListOrThrow(const std::string& filename);
    void loadSongListOrThrow(const std::string& filename);
};
#endif
