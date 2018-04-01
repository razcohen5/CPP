#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
using namespace std;

class Member{   

private:

    
public: 

    int  followsAfter,followedBy,id;
    static int counter;
    static vector <Member*> members;
    vector <int> ifollow;
    vector <int> followedme;
    
    Member()
    {
        followsAfter=0;
        followedBy=0;
        id=counter;
        counter++;
        members.push_back(this);
    }

    ~Member()
    {
        for(int i=0;i<followsAfter;i++)
        {
            memberbyid(ifollow[i]).deletefromfollowedby(*this);
            memberbyid(ifollow[i]).followedBy--;
        }
        for(int i=0;i<followedBy;i++)
        {
            memberbyid(followedme[i]).deletefromfollowers(*this);
            memberbyid(followedme[i]).followsAfter--;
        }
        //members.erase(members.begin()+id);
        deletemember(id);
        counter--;

    }

    Member& memberbyid(int id)
    {
        for(int i=0;i<counter;i++)
            if(members[i]->id == id)
                return *members[i];
    }

    static void deletemember(int id)
    {
        for(int i=0;i<counter;i++)
            if(members[i]->id == id)
                members.erase(members.begin() + i);
    }
    bool isfollowingafter(Member &m)
    {
        for(int i=0;i<followsAfter;i++)
            if(ifollow[i] == m.id)
                return true;
        return false;
    }
    void deletefromfollowers(Member &m)//when u unfollow some1 u want to delete him from your ifollow vector.
    {
        for(int i=0;i<followsAfter;i++)
            if(ifollow[i]==m.id)
                 ifollow.erase(ifollow.begin()+i); 
    }
    void deletefromfollowedby(Member &m)//when u unfollow someone u want to delete yourself from his followedme vector.
    {
        for(int i=0;i<followedBy;i++)
            if(followedme[i]==m.id)
                 followedme.erase(followedme.begin()+i); 
    }

    void follow(Member &m)
    {
        if(!isfollowingafter(m))
        {
            followsAfter++;
            ifollow.push_back(m.id);
            m.followedBy++;
            m.followedme.push_back(id);
        }
    }
    void unfollow(Member &m)
    {
        if(isfollowingafter(m))
        {
             deletefromfollowers(m);
             followsAfter--;
             m.deletefromfollowedby(*this);
             m.followedBy--;
        }
    }
    static int count()
    {
        return counter;
    }
 /*   static void printmembers()
    {
        for(int i=0;i<members.size;i++)
            printf("%d ", members[i].id);
    }*/
    int numFollowers()
    {
        return followedBy;
    }
    int numFollowing()
    {
        return followsAfter;
    }

};
int Member::counter=0;
vector <Member*> Member::members;



