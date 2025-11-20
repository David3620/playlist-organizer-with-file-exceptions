//Copyright 2025
#include "Playlist.h"
#include <stdexcept>
using std::cout;
using std::endl;
using std::cerr;
using std::invalid_argument;
using std::istringstream;

Playlist::Playlist()
{
    headnode = nullptr;
    tailnode = nullptr;
}
Playlist::~Playlist()
{
    while (headnode!=nullptr)
    {
        PlayNode * next=headnode->GetNext();
        delete headnode;
        headnode=next;
    }
}

 PlayNode* Playlist::GetHead()const
{
    if (headnode!=nullptr)
    {
        return headnode->GetNext();//original
    }
    else
    {
        //return nullptr;
        return headnode;
    }

}

 PlayNode* Playlist::GetTail()const
{
    if (tailnode!=nullptr)
    {
        return tailnode;
    }
    else
    {
        return nullptr;
    }
}
void Playlist::AddSong(const string& uniqueID, const string& songName, const string& artistName, int songLength)
{
    if (headnode == nullptr)//create new head if none
    {
        headnode = new PlayNode();
        tailnode = headnode;
    }
    PlayNode * tracker = headnode;
    while (tracker->GetNext()!=nullptr)//checks for duplicate ids
    {
        if (tracker->GetID() == uniqueID)
        {
            throw std::invalid_argument("AddSong: duplicate found");
        }
        tracker = tracker->GetNext();
    }
    //cout << uniqueID << " " << tracker->GetID() << endl;
    if ((tracker->GetID())==uniqueID)//checks if the last node id is identical to the unique id
    {
        throw std::invalid_argument("AddSong: duplicate found in tail");    
    }

    if (songLength<0)
    {
        throw invalid_argument("AddSong: invalid input");
    }
    
    PlayNode * curr =new PlayNode(uniqueID,songName,artistName,songLength);
    tailnode->InsertAfter(curr);
    tailnode=curr;
}

bool Playlist::RemoveSong(const string& uniqueID )
{
    PlayNode * curr= headnode;
    PlayNode * prev=curr;//test: prev intialezed to curr 
    PlayNode * next;//test next intialized to curr->getNext();
    bool found = false;
    if (headnode!= nullptr)
    {
    while (curr!=nullptr)
    { 
        if (curr->GetID()==uniqueID)
        {
            next = curr->GetNext();
            
            prev->SetNext(next);//set the next pointer of the previous node to node after the node with the matching unique id
            
            cout<<"\""<<curr->GetSongName()<<"\""<<" removed."<<endl;
            found =true;
        }
        else
        {
            prev=curr;// if the unique id is not equal to the curr node unique id then the prev node is set to the curr node as th previous node
        }
        curr=curr->GetNext(); //updates curr
    }//end of loop
    
    if (headnode->GetNext()==nullptr)
    {
        headnode = nullptr;
        tailnode = nullptr;
    }
    }
    if (found== true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Playlist::ChangePosition(int songPosition, int newPosition)
{
    int size=0;
    PlayNode * counter = headnode;
    PlayNode * curr = headnode->GetNext();// set to first node
    PlayNode * newPos= headnode; // set to the head node of the alterd linked list
    PlayNode * prev = headnode; // set to before curr node
    PlayNode * next = curr->GetNext(); // set to node after curr node
    while (counter!=nullptr)
    {
        counter=counter->GetNext();
        size++;
    }
    if (((songPosition != 0) && (newPosition != 0)) && ((songPosition < size) && (newPosition < size)))
    {
        for (int i=1;i<songPosition;++i)// tranverse the linked list until we reach the desired node
        {
            
            
                prev = prev->GetNext();// update prev node with the next node until the desired node is reached. prev tracks the node before the desired node at songPosition
                
                curr = curr->GetNext();// update prev node with the next node until the desired node is reached. curr tracks the desired node at songPosition 
                
                next = next->GetNext();// update prev node with the next node until the desired node is reached.
                
            
        }
        /*
        //test start
        cout<<"prev is: "<<prev->GetID()<<endl;
        cout<<"curr is: "<<curr->GetID()<<endl;
        if (next==nullptr)
        {
            cout<<"next is nullptr"<<endl;
        }
        else{
        cout<<"next is: "<<next->GetID()<<endl;
        }//end of test*/

        curr->SetNext(nullptr);
        prev->SetNext(next); // discconect the node at songPosition from the linked list by setting the nextnodeptr member variable of the  node previous to the songPosition node, to the node after the songPosition node 
        for (int i=1;i<newPosition;++i)// traverse the alterd linked list until we reach the desired loction on the linked list
        {
            newPos=newPos->GetNext();// updates newPos with the next node and stores the desired node postion
        }
        //cout<<"newPos is: "<<newPos->GetID()<<endl;//test
        newPos->InsertAfter(curr);// the node that was at the songPosition in the linked list is inserted at the new postion
       cout<<"\""<<curr->GetSongName()<<"\""<<" moved to position "<<newPosition<<endl<<endl;
        curr=headnode;
        while (curr->GetNext()!=nullptr)
        {
            curr=curr->GetNext();
        }
        tailnode=curr;
        return true;
    }
    else
    {
        return false;
    }
}

void Playlist::OutputSongsByArtist(const string& artistName) const
{int num=1;
    PlayNode * curr = headnode->GetNext();
    while (curr!=nullptr)
    {
        if (curr->GetArtistName() == artistName)
        {cout<<num<<"."<<endl;
            curr-> PrintNode();
        }
       curr=curr->GetNext();
       num++;
    }
}

int Playlist::OutputTotalTime() const
{
    int totaltime=0;

    PlayNode * curr = headnode->GetNext();
    
    while (curr!=nullptr)
    {
        totaltime += curr->GetSongLength();
       curr=curr->GetNext();
    }
    cout<<"Total time: "<<totaltime<<" seconds"<<endl;
    return totaltime;
}

void Playlist::OutputFullPlaylist(const string& playlistTitle) const
{
     PlayNode * curr= nullptr;
    cout<<playlistTitle<<" - OUTPUT FULL PLAYLIST"<<endl;
    if (headnode!=nullptr)
    {
        curr = headnode->GetNext();
    }
    else
    {
        cout<<"Playlist is empty"<<endl;
    }
   int counter=1;
    while (curr!=nullptr)
    {
       if (curr!=nullptr)
       {
        cout<<counter<<"."<<endl;
        counter++;
        curr -> PrintNode();
        cout<<endl;
        curr = curr->GetNext();
       }
    }
}

bool Playlist::IsEmpty() const
{
    if (headnode == nullptr)
    {
        cout<<" Empty"<<endl;
        return true;
    }
    else
    {
        cout<<"node is not Empty"<<endl;
        return false;
    }
}

bool Playlist::saveSongList(const std::string& filename)
{
    PlayNode * curr= nullptr;
    bool completion=false;
    ofstream out;
   if (headnode!=nullptr)
    {
        curr = headnode->GetNext();
    }

    out.open(filename);

    if (!out.is_open())
    {
        completion=false;
        throw std::ios_base::failure("saveSongList : failed to open "+filename);   
    }

    while (curr!=nullptr)
    {
        out << *(curr);
        if (curr->GetNext()!=nullptr)//put endl at end of out buffer when at last node
        {
            out<<endl;    
        }
        if (out.fail())//fail to read throw error
        {
            completion=false;
            throw std::runtime_error("saveSongList : error reading");
        }
        else
        {
            completion=true;
        }
        curr = curr->GetNext();//update curr node
    }     
    
    out.close();
    return completion;
    
}
bool Playlist::loadSongList(const std::string& filename)
{
    bool completion = false;
    string line;
    ifstream inf;
    istringstream iss;
    PlayNode * curr;

    if (headnode==nullptr)//if playlist is empty create new head and assign headnode to tail
    {
        this->headnode= new PlayNode();
        this->tailnode= headnode;
    }
    
    inf.open(filename);
    
    if (!inf.is_open())
    {
        completion=false;//original
        return false;   
    }
    
    curr = new PlayNode();
    while (!(inf.eof()))
    {
        
        getline(inf,line);
        if (line.empty())
        {
            return completion;
        }
        iss.str(line);
        iss>>*(curr);
        if (iss.fail())
        {
            cout<<"loadSongList(): error in iss read"<<endl;
            return false;
        }
       //inf>>*(curr);//orignal
        if (inf.fail())
        {
            completion=false;
            throw std::runtime_error("loadSongList : failed to read");
        }
        else
        {
            completion=true;
        }
        PlayNode * prev=headnode->GetNext();
    
        while (prev!=nullptr)// checks and prevents duplicates from being read from file to list
        {
            if (prev->GetID()==curr->GetID())// if the new node created from file has a duplicate id when compared to playlist nodes, it will not add to list
            {
                return false;
            }
            else
            {
                completion=true;
            }
            prev=prev->GetNext();
            
        }
        AddSong(curr->GetID(),curr->GetSongName(),curr->GetArtistName(),curr->GetSongLength());
        iss.clear();
        inf.clear();

    }
    
    inf.close(); 
    return completion; 
}

void Playlist::saveSongListOrThrow(const std::string& filename)
{
  saveSongList(filename);
}
void Playlist::loadSongListOrThrow(const std::string& filename)
{

    string line;
    ifstream inf;
    istringstream iss;
    PlayNode * curr;

    if (headnode==nullptr)//if playlist is empty create new head and assign headnode to tail
    {
        this->headnode= new PlayNode();
        this->tailnode= headnode;
    }
    
    inf.open(filename);
    
    if (!inf.is_open())
    {
    
       throw std::ios_base::failure("loadSongList : failed to open "+filename);//original
        
    }
    
    curr = new PlayNode();
    while (!(inf.eof()))
    {

        iss.str(line);
        iss>>*(curr);
       //inf>>*(curr);//orignal
        if (inf.fail())
        {
           
            throw std::runtime_error("loadSongList : failed to read");
        } 
        PlayNode * prev=headnode->GetNext();
        while (prev!=nullptr)// checks and prevents duplicates from being read from file to list
        {
            if (prev->GetID()==curr->GetID()&&(prev!=curr))// if the new node created from file has a duplicate id when compared to playlist nodes, it will not add to list
            {
                throw std::runtime_error("loadSongList : failed to read");
            }
            prev=prev->GetNext();
        }

        AddSong(curr->GetID(),curr->GetSongName(),curr->GetArtistName(),curr->GetSongLength());
    }
    
    inf.close();     
}
