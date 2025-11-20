#include "Playlist.h"
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::cin;
using std::flush;
using std::string;
//g++ main.cpp Playlist.cpp PlayNode.cpp
void PrintMenu( string playlistTitle)
{
    cout<<playlistTitle<<" PLAYLIST MENU"<<endl;
    cout<<"a - Add song"<<endl;
    cout<<"d - Remove song"<<endl;
    cout<<"c - Change position of song"<<endl;
    cout<<"s - Output songs by specific artist"<<endl;
    cout<<"t - Output total time of playlist (in seconds)"<<endl;
    cout<<"o - Output full playlist"<<endl;
    cout<<"w - Write (save) playlist to file"<<endl;
    cout<<"l - Load playlist from file"<<endl;
    cout<<"q - Quit"<<endl;
    cout<<endl;
}
void ExecuteMenu(char option,string playlistTitle, Playlist & playlist)
{
    string filename="text.txt";
    switch(option)
    {
    case 'a':
    {
        string id,song,artist;
        int seconds=0;
        cout<<"ADD SONG"<<endl;
        cout<<"Enter song's unique ID: ";
        cin>>id;
        //cout<<id<<endl;
        cout<<"Enter song's name: ";
        cin.ignore(1);
        getline(cin,song);
        //cout<<song<<endl;
        cout<<"Enter artist's name: ";
        
        getline(cin,artist);
        //cout<<artist<<endl;
        cout<<"Enter song's length (in seconds): ";
        cin>>seconds;
        //cout<<seconds<<endl;
        
        playlist.AddSong(id,song,artist,seconds);
    }break;

    case'd':
    {
        string songid;
        
        cout<<"REMOVE SONG"<<endl;
        cout<<"Enter song's unique ID: ";
        cin.ignore(1);
        getline(cin,songid);
        //cout<<songid<<endl;
        playlist.RemoveSong(songid);
        
    }break;

    case'o':
    {
        //cout<<playlistTitle<<" - OUTPUT FULL PLAYLIST"<<endl;
        playlist.OutputFullPlaylist(playlistTitle);
    }break;
    case'c':
    {
        int songposition;
        int newposition;

        cout<<"CHANGE POSITION OF SONG"<<endl;
        cout<<"Enter song's current position: ";
        cin>>songposition;
        //cout<<songposition<<endl;
        cout<<"Enter new position for song: ";
        cin>>newposition;
       // cout<<newposition<<endl;
        playlist.ChangePosition(songposition,newposition);

    }break;
    case's':
    {
        string artistname;
        cout<<"OUTPUT SONGS BY SPECIFIC ARTIST"<<endl;
        cout<<"Enter artist's name: ";
        cin.ignore(1);
        getline(cin,artistname);
        //cout<<artistname<<endl;
        playlist.OutputSongsByArtist(artistname);
    }
    break;
    case't':
    {
        //cout<<"OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)"<<endl;
        playlist.OutputTotalTime();
    }
    break;
    case'w':
    {
        
        playlist.saveSongList(filename);
    }break;
    case'l':
    {
        playlist.loadSongList(filename);
    }break;
    default:
    break;
    }
}

int main()
{
    string name;
    Playlist list;
    char option;

    cout<<"Enter playlist's title: ";
    getline(cin,name);

    //cout<<name<<flush;
    //cout<<endl;
    PrintMenu(name);

    cout<<"Choose an option: "<<flush;
    cin>>option;
    //cout<<option<<flush;

    while(option!='q'){
    ExecuteMenu(option,name,list);
    PrintMenu(name);
   
    cout<<"Choose an option: "<<flush;
    cin>>option;
    //cout<<option<<endl;
    }
    
    return 0;
}
