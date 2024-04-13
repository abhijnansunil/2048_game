#include<iostream>
#include<iomanip>
#include<windows.h>
int board[4][4]={0};
int temp[4][4]={0}; // a temp board to compare to see if a new move was made
int score=0;
using namespace std;

pair<int,int> unoccupiedpos() //get an unoccupied pos
{
    int row,col;
    while(true)
    {
        row=rand()%4;
        col=rand()%4;
        if(board[row][col]==0)
        return {row,col};
    }
    exit(0);
}

void addpiece() // add 2 with prob 0.9 and 4 with prob 0.1
{
    pair<int,int> pos=unoccupiedpos();
    if(rand()%10<9){
        board[pos.first][pos.second]=2;
        score=score+2;}
    else{
        board[pos.first][pos.second]=4;
        score=score+4;
    }

}
void newgame()
{
    for(int i=0;i<4;i++)
       for(int j=0;j<4;j++)
           board[i][j]=0;
           score=0;
        addpiece();
}
void printui()
{
    system("cls");
    cout<<"SCORE ::"<<score<<endl;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++)
            if(board[i][j]==0)
                cout<<setw(8)<<".";
            else
                cout<<setw(8)<<board[i][j];
        cout<<endl<<endl;
    }
    cout<<"N: NEW GAME,W: UP,S: DOWN,D: RIGHT,A: LEFT,Q: EXIT"<<endl;
}

bool checknotequal()  // to add piece only if move was made
{
   for(int i=0;i<4;i++)
   for(int j=0;j<4;j++)
   {
    if(temp[i][j]!=board[i][j])
    return 1;
   }
   return 0;

}
void applymove(int dir) // dir 0-down 1 -right 2-up 3-left
{
    int k;
    for(int i=0;i<4;i++) // store board before move
    {
        for(int j=0;j<4;j++)
        temp[i][j]=board[i][j];
    }
    if(dir==0)
    {
        for(int j=0;j<4;j++)// seprate zeros to the end
        {
            k=3;
            for(int i=3;i>=0;i--)
            {
                if(board[i][j]!=0)
                {
                    swap(board[i][j],board[k][j]);
                    k--;
                }
            }
            for(int i=2;i>=0;i--)// combine if 2 nos are equal
            {
                if(board[i][j]==0)
                    break;
                if(board[i+1][j]==board[i][j])
                {
                    board[i+1][j]*=2;
                    board[i][j]=0;
                }
            }
            k=3;
            for(int i=3;i>=0;i--)// again move zeros to end
            {
                if(board[i][j]!=0)
                {
                    swap(board[i][j],board[k][j]);
                    k--;
                }
            }
        }

    }
    else if(dir==1)
    {
        for(int i=0;i<4;i++)
        {
            k=3;
            for(int j=3;j>=0;j--)
            {
                if(board[i][j]!=0)
                {
                    swap(board[i][j],board[i][k]);
                    k--;
                }
            }
            for(int j=2;j>=0;j--)
            {
                if(board[i][j]==0)
                    break;
                if(board[i][j]==board[i][j+1])
                {
                    board[i][j+1]*=2;
                    board[i][j]=0;
                }
            }
            k=3;
            for(int j=3;j>=0;j--)
            {
                if(board[i][j]!=0)
                {
                    swap(board[i][j],board[i][k]);
                    k--;
                }
            }

        }


    }
    else if(dir==2)
    {
        for(int j=0;j<4;j++)
        {
            k=0;
            for(int i=0;i<4;i++)
            {
                if(board[i][j]!=0)
                {
                    swap(board[i][j],board[k][j]);
                    k++;
                }
            }
            for(int i=1;i<4;i++)
            {
                if(board[i][j]==0)
                break;
                if(board[i-1][j]==board[i][j])
                {
                    board[i-1][j]*=2;
                    board[i][j]=0;
                }
            }
            k=0;
            for(int i=0;i<4;i++)
            {
                if(board[i][j]!=0)
                {
                    swap(board[i][j],board[k][j]);
                    k++;
                }
            }
           
        }

    }
    else
    {
        for(int i=0;i<4;i++)
        {
            k=0;
            for(int j=0;j<4;j++)
            {
                if(board[i][j]!=0)
                {
                    swap(board[i][j],board[i][k]);
                    k++;
                }
            }
            for(int j=0;j<4;j++)
            {
                if(board[i][j]==0)
                break;
                if(board[i][j]==board[i][j-1])
                {
                    board[i][j-1]*=2;
                    board[i][j]=0;
                }
            }
            k=0;
            for(int j=0;j<4;j++)
            {
                if(board[i][j]!=0)
                {
                    swap(board[i][j],board[i][k]);
                    k++;
                }
            }
            

        }


    }

    if(checknotequal()) // only add piece if a proper move was made
    addpiece();
    
}

int checkover()// to check if game is over
{
	int fl=0,gl=0,i,j;
	for(i=0;i<4;i++)
    	for(j=0;j<4;j++){
    		if(board[i][j]==0)
    		{
    			fl=1;
				break;	
			}
            else if(board[i][j]==2048)
            {
                printui();
                cout<<endl<<"YOU WON!!";
                Sleep(5000);
                exit(0);

            }
        }
        

			
	for(i=0;i<3;i++)
    	for(j=0;j<3;j++)
    		if(board[i+1][j]==board[i][j] || board[i][j+1]==board[i][j])
    		{
    			gl=1;
    			break;
			}
			
	if(fl || gl) return 1;
	else return 0;
        }




int main()
{   srand(time(0));
    system("cls");
    system("color 0E");
    cout<<"===============2048==============\n"; 
    cout<<"WELCOME TO PUZZLE 2048\n";
    cout<<"> CONTROLS\n"; 
    cout<<"  FOR MOVES:- 'W','S','A','D'\n";
    //cout<<"  GO BACKWARD:- 'P'\n";
    cout<<"  RESTART THE GAME:- 'N'\n";
    cout<<"  EXIT:-'Q'\n";
    cout<<"\nPRESS ANY KEY TO START THE GAME>>>";


    getchar();
    system("cls");
    cout<<"\n===============2048==============\n"; 
    cout<<"\nLOADING...\n";
    cout<<"\n\n";
    for (int i = 0; i < 26; i++) 
        cout<<char(177);
    cout<<"\r";
    for (int i = 0; i <26; i++) { 
        cout<<char(219); 
        Sleep(100); 
    } 
    system("cls");
    char choice;
    int dir;
    newgame();
    while(1)
    {
        printui();
        cin>>choice;
        switch(choice)
        {
            case 'Q':
            case 'q':
                cout<<"ARE YOU SURE?[Y/n]\n";
                wrongans: cin>>choice;
                if(choice=='y'||choice=='Y')
                    {
                    cout<<"\n\nTHANK YOU FOR PLAYING>>\n";
                    Sleep(2);
                    exit(0);
                    }
                else if(choice=='n'||choice=='N')
                    {
                    break;
                    }
                else{
                    cout<<"PLEASE ENTER A VALID CHOICE\n";
                    goto wrongans;
                    }
            break;
            case 'N':
            case 'n':
                newgame();
                break;
            case 'S':
            case 's':
                applymove(0);
                break;
            case 'D':
            case 'd':
                applymove(1);
                break;
            case 'W':
            case 'w':
                applymove(2);
                break;
            case 'A':
            case 'a':
                applymove(3);
                break;
            default:
                cout<<"\nPLEASE ENTER A VALID INPUT\n";
        }
        if(!checkover())
        {
            printui();
            cout<<endl;
            cout<<"GAME OVER!!";
            Sleep(3000);
            exit(0);
        }
    }

    return 0;
}
