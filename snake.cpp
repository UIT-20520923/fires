#include <bits/stdc++.h>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
using namespace std;
#define R 10
#define C 10
char a[R][C];
string s[R];
bool check[R][C];
void gotoxy( int column, int line );
int dirrow[4]={0,-1,0,1};
int dircol[4]={1,0,-1,0};
struct point{

int x;int y;};
struct squaredata{
    point adr;
    int dist;

};
bool check_in(int r,int c)
{
    return ((r>=0)&&(r<R)&&(c>=0)&&(c<C));

}
int mint(string s[],point start,point des,map<string,point>&mep)
{        check[start.x][start.y]=true;

        queue<squaredata>q;
        squaredata k={start,0};
        q.push(k);
      while(!q.empty())
      {
        squaredata curr=q.front();
           point pt=curr.adr;
      if(pt.x==des.x&&pt.y==des.y)
      {
          return curr.dist;
      }
      q.pop();
      for(int i=0;i<=3;i++)
      {

          int r= pt.x+dirrow[i];
          int c=pt.y+dircol[i];
          if(check_in(r,c)&&(!check[r][c])&&(s[r][c]=='.'))
          {
              check[r][c]=true;
              squaredata adjsqu;
              adjsqu.adr.x=r;
              adjsqu.adr.y=c;
              adjsqu.dist=curr.dist+1;
              string k=to_string(r)+"|"+to_string(c);
              mep[k]={pt.x,pt.y};
              q.push(adjsqu);
          }
      }
      }

}
int main()
{string s[11] ={"..........",
                "#.#.#####.",
                "#.#..###..",
                "..##..##.#",
                "....#.##.#",
                "..#.#....#",
                "......####",
                "#.###.####",
                "#..##....#",
                ".#....##.."};
    map<string ,point>mep;
        map<string ,point>mepp;
    memset(check,false,sizeof check);
    squaredata start,des;
    start.adr.x=0;
    start.adr.y=0;
    des.adr.x=9;
    des.adr.y=9;
    des.dist=mint(s,start.adr,des.adr,mep);

  string k = to_string(des.adr.x)+"|"+to_string(des.adr.y);

   point temp;
    temp.x=des.adr.x;
    temp.y=des.adr.y;


  while(1)
  { string kk = to_string(mep[k].x)+"|"+to_string(mep[k].y);
       mepp[kk].x=temp.x;
       mepp[kk].y=temp.y;
     //  cout<<kk<<":"<<mepp[kk].x<<" "<<mepp[kk].y<<endl;
       temp.x=mep[k].x;
       temp.y=mep[k].y;
       if(mep[k].x==start.adr.x&&mep[k].y==start.adr.y)
       {
           break;
       }
      k = to_string(mep[k].x)+"|"+to_string(mep[k].y);



  } s[des.adr.x][des.adr.y]=char(219);
   k = to_string(start.adr.x)+"|"+to_string(start.adr.y);
  while(1)
  {
    system("cls");
     gotoxy(0,0);
      for(int i=0;i<R;i++)
      {
          for(int j=0;j<C;j++)
          {
              if((i==mepp[k].x)&&(j==mepp[k].y))
               {        cout<<char(219);

              }
              else {
             cout<<s[i][j];}
          }
          cout<<endl;
      }

      Sleep(300);
         if(mepp[k].x==des.adr.x&&mepp[k].y==des.adr.y)
         {
             break;
         }
      k=to_string(mepp[k].x)+"|"+to_string(mepp[k].y);
  }
//cout<<mepp["9|3"].x<< " "<<mepp["9|3"].y;

  return 0;
}
  void gotoxy( int column, int line )
  {
  COORD coord;
  coord.X = column;
  coord.Y = line;
  SetConsoleCursorPosition(
    GetStdHandle( STD_OUTPUT_HANDLE ),
    coord
    );
  }
