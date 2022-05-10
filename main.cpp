#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <fstream>
#include <cctype>
#include "BT.h"

using namespace std;

typedef BST < int > intBST;
typedef intBST * intBSTPtr;
intBSTPtr myTree(new intBST);

int countwords(string line)
{
    int s=0,j=0,count=0;

    for(s=0; line[s]!='\0'&&line[s]!='\r'&&line[s]!='\n'; s++)
    {};
    while(line[j]!='\0'&&j<=s&&line[j]!='\n')
    {
        while(line[j]==' '||line[j]=='\t')
            j++;
        while(line[j]!=' '&&line[j]!='\0'&&line[j]!='\n'&&line[j]!='\t')
        {
            j++;
        }
        count++;
        j++;
    }
    return count;
}

string getfirstword(string line)
{
    int s=0,j=0,count=0;
    string first="",data="";

    for(s=0; line[s]!='\0'&&line[s]!='\r'&&line[s]!='\n'; s++)
    {};
    while(line[j]==' '||line[j]=='\t')
        j++;
    while(line[j]!='\0'&&j<=s&&line[j]!='\n')
    {
        data="";
        while(line[j]!=' '&&line[j]!='\0'&&line[j]!='\n'&&line[j]!='\t')
        {
            data=data+line[j];
            j++;
        }
        if(count==0)
            first=data;
        count++;
        j++;
    }
    return first;
}

void add(int day,int hour,string title,ofstream &file)
{
    myTree->insert((100*day)+hour,title,file);
}

void find(int day,int hour,ofstream &file)
{
    intBSTPtr getmeeting(myTree->retrieve((100*day)+hour));
    if (getmeeting->isEmpty())
    {
        cout<<"Empty "<<day<<" "<<hour<<endl;
        file<<"Empty "<<day<<" "<<hour<<endl;
    }
    else
    {
        cout<<getmeeting->getTitle()<<endl;
        file<<getmeeting->getTitle()<<endl;
    }
}

void modify(int day,int hour,string title,ofstream &file)
{
    intBSTPtr getmeeting(myTree->Modify((100*day)+hour,title));
    if (getmeeting->isEmpty())
    {
        cout<<"Empty "<<day<<" "<<hour<<endl;
        file<<"Empty "<<day<<" "<<hour<<endl;
    }
}

void Delete(int day,int hour,string title,ofstream &file)
{
    intBSTPtr getmeeting(myTree->retrieve((100*day)+hour));
    if (!getmeeting->isEmpty())
        myTree->delet((100*day)+hour,title);
    else
    {
        cout<<"Empty "<<day<<" "<<hour<<endl;
        file<<"Empty "<<day<<" "<<hour<<endl;
    }
}

void print(ofstream &file)
{
    if(myTree->isEmpty())
    {
        cout<<"Empty Planner"<<endl;
        file<<"Empty Planner"<<endl;
    }
    else
        myTree->inOrderTraverse(myTree,file);
}

int main(int argc,char ** argv)
{
    string path1,path2,command,data,title="",tempday,temphour,subcommand,word;
    int s=0,i=0,j=0,k=0,x=0,wordCount=0,flag=0,day,hour,flag1=0;
    int y1=0,y2=0,words=0,failed1=0,failed=0,temp=0,space,t=0,index=0;

    path1=argv[1];
    path2=argv[2];

    ifstream PlannerIn;
    ofstream PlannerOut;

    PlannerIn.open(path1);
    PlannerOut.open(path2);

    if (argc != 3)
    {
        cout<<"wrong number of files"<<endl;
        PlannerOut<<"wrong number of files"<<endl;
        return 0;
    }

    if(PlannerIn.is_open())
    {
        while(!PlannerIn.eof())
        {
l:
            t=0;
            words=0;
            getline(PlannerIn,command);
            if(!(command.find('\r')==-1||command.find('\r')>command.size()+2))
                command=command.substr(0,command.size()-1);
            failed=0;
            if(command==" ")
            {
                goto l;
            }
            ///cout<<command<<endl;
            while(command[command.length()-1]==' '||command[command.length()-1]=='\t')
            {
                command=command.substr(0,command.length()-1);
            }
            data=getfirstword(command);
            if(data=="ADD"||data=="MOD")
            {
                words=countwords(command);
                space=command.find(' ');
                while(command[space]==' ')
                    space++;
                if(words>=4)
                {
                    flag=1;
                    y1=command.find('"');
                    y2=command.rfind('"');
                    temp=y1;
                    subcommand=command;
                    for(index=0; index<3; index++)
                    {
                        word=getfirstword(subcommand);
                        subcommand=subcommand.substr(word.length()+1,subcommand.length()-1);
                    }
                    if(y1==4&&(command[y2+1]==' '||command[y2+1]=='\t'))
                    {
                        while(y2>=y1&&(y1!=-1&&y2!=-1))
                        {
                            title=title+command[y1];
                            y1++;
                            x=1;
                        }
                    }
                    while(title[0]==' '||title[0]=='\t')
                        title=title.substr(1,title.length());
                    k=y2;
                    while(command[k+1]!=' '&&command[k+1]!='	')
                    {
                        k++;
                    }
                    command=command.substr(k+1,command.length());
                    if(!x&&!failed&&(y2==y1)&&words!=4)
                    {
                        cout<<"Invalid arguments"<<endl;
                        PlannerOut<<"Invalid arguments"<<endl;
                        failed=1;
                    }
                    if((!failed&&temp==-1&&y2==-1)||(!x&&y1!=space+1)||(k!=y2&&!failed&&flag&&x)||(y2==temp&&!failed&&temp!=-1))
                    {
                        if(words!=4&&!failed)
                        {
                            cout<<"Invalid arguments"<<endl;
                            PlannerOut<<"Invalid arguments"<<endl;
                            failed=1;
                        }
                        else if(!failed&&word[0]!='"')
                        {
                            cout<<"Invalid title"<<endl;
                            PlannerOut<<"Invalid title"<<endl;
                            failed=1;
                            t=1;
                        }
                    }
                    ///cout<<"m "<<k<<" "<<y2<<endl;
                    ///cout<<"comm[0]="<<command[1]<<endl;
                    if(t&&y2==-1)
                    {
                        command=command.substr(getfirstword(command).length()+1,command.length());
                    }
                    words=countwords(command);
                    if(words>2&&!failed)
                    {
                        cout<<"Invalid arguments"<<endl;
                        PlannerOut<<"Invalid arguments"<<endl;
                        failed=1;
                    }
                    if((x||t)&&words==2)
                    {
                        tempday=getfirstword(command);
                        command=command.substr(command.find(tempday)-1,command.length());
                        space=0;
                        while(tempday[space]==' ')
                        {
                            tempday=tempday.substr(space+1,tempday.length());
                        }
                        command=command.substr(tempday.length()+2,command.length()-1);
                        temphour=command;
                        space=0;
                        while(temphour[space]==' ')
                        {
                            temphour=temphour.substr(space+1,temphour.length());
                        }
                        failed1=0;
                        for(k=0; tempday[k]!='\0'&&tempday[k]!='\n'; k++)
                        {
                            if(isdigit(tempday[k]));
                            else
                                failed1=1;
                        }
                        if(!failed1&&(stoi(tempday)>=1&&stoi(tempday)<=365))
                        {
                            day=stoi(tempday);
                        }
                        else
                        {
                            cout<<"Invalid day"<<endl;
                            PlannerOut<<"Invalid day"<<endl;
                            failed=1;
                        }
                        failed1=0;
                        for(k=0; temphour[k]!='\0'&&temphour[k]!='\n'; k++)
                        {
                            if(isdigit(temphour[k]));
                            else
                                failed1=1;
                        }
                        if(!failed1&&(stoi(temphour)>=0&&stoi(temphour)<=23))
                        {
                            hour=stoi(temphour);
                        }
                        else
                        {
                            cout<<"Invalid hour"<<endl;
                            PlannerOut<<"Invalid hour"<<endl;
                            failed=1;
                        }
                    }
                    else if(words!=2&&!failed&&!x&&!t)
                    {
                        cout<<"Invalid arguments"<<endl;
                        PlannerOut<<"Invalid arguments"<<endl;
                        failed=1;
                    }
                }
                else
                {
                    cout<<"Invalid arguments"<<endl;
                    PlannerOut<<"Invalid arguments"<<endl;
                    failed=1;
                }
                if((!failed)&&(data=="ADD"))
                {
                    add(day,hour,title,PlannerOut);
                }
                else if(!failed&&data=="MOD")
                    modify(day,hour,title,PlannerOut);
            }
            x=0;
            failed=0;
            failed1=0;
            title="";
            flag=0;
            ///========================================================\\\

            if(data=="DEL"||data=="Find")
            {
                words=countwords(command);
                if(words!=3)
                {
                    cout<<"Invalid arguments"<<endl;
                    PlannerOut<<"Invalid arguments"<<endl;
                    failed=1;
                }
                else
                {
                    command=command.substr(4,command.length()-1);
                    tempday=getfirstword(command);
                    command=command.substr(command.find(tempday),command.length());
                    space=0;
                    while(tempday[space]==' ')
                    {
                        tempday=tempday.substr(space+1,tempday.length());
                    }
                    command=command.substr(tempday.length(),command.length()-1);
                    temphour=command;
                    space=0;
                    while(temphour[space]==' ')
                    {
                        temphour=temphour.substr(space+1,temphour.length());
                    }
                    failed1=0;
                    for(k=0; tempday[k]!='\0'&&tempday[k]!='\n'; k++)
                    {
                        if(isdigit(tempday[k]));
                        else
                            failed1=1;
                    }
                    if(!failed1&&(stoi(tempday)>=1&&stoi(tempday)<=365))
                    {
                        day=stoi(tempday);
                    }
                    else
                    {
                        cout<<"Invalid day"<<endl;
                        PlannerOut<<"Invalid day"<<endl;
                        failed=1;
                    }
                    failed1=0;
                    for(k=0; temphour[k]!='\0'&&temphour[k]!='\n'; k++)
                    {
                        if(isdigit(temphour[k]));
                        else
                            failed1=1;
                    }
                    if(!failed1&&(stoi(temphour)>=0&&stoi(temphour)<=23))
                    {
                        hour=stoi(temphour);
                    }
                    else
                    {
                        cout<<"Invalid hour"<<endl;
                        PlannerOut<<"Invalid hour"<<endl;
                        failed=1;
                    }
                }
                if(!failed&&data=="DEL")
                    Delete(day,hour,title,PlannerOut);
                else if(!failed&&data=="Find")
                    find(day,hour,PlannerOut);
            }
            failed=0;
            failed1=0;
            ///========================================================\\\

            if(data=="Print")
            {
                words=countwords(command);
                if(words!=1)
                {
                    cout<<"Invalid arguments"<<endl;
                    PlannerOut<<"Invalid arguments"<<endl;
                }
                else
                    print(PlannerOut);
            }
            ///========================================================\\\

            failed=0;
            if(data!="ADD"&&data!="MOD"&&data!="DEL"&&data!="Find"&&data!="Print")
            {
                words=countwords(command);
                k=0;
                while(command[k]!='\0')
                {
                    if(command[k]!=' ')
                        failed=1;
                    k++;
                }
                if(words!=0&&failed)
                {
                    cout<<"Invalid command"<<endl;
                    PlannerOut<<"Invalid command"<<endl;
                }
            }
        }
    }
    else
    {
        cout<<"input file not found"<<endl;
        PlannerOut<<"input file not found"<<endl;
        return 0;
    }

    PlannerIn.close();
    PlannerOut.close();

    return 0;
}
