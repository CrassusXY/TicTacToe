#include "tictactoe.hh"

tictactoe::tictactoe(){
    size = 3;
    required = 2;
    grid = new char[size*size];
    for(int i=0; i<size*size; i++){
        grid[i] = ' ';
    }
}

void tictactoe::displayGrid(){
    for(int x=1; x<size+1; x++){
        if(x==1){
            cout<<" ";
        }
        cout<<"   "<<x;
    }
    cout<<endl;
    int y=1;
    for (int i=0; i<size*size; i++){
        if(i%size == 0){
            if(y<10)
                cout<<y<<"   "<<grid[i];
            else
                cout<<y<<"  "<<grid[i];
            y++;
        }
        else if(i%size == size-1){
            cout<<" | "<<grid[i]<<endl;
            if(i != size*size-1){
                for(int j=0; j<size; j++){
                    if(j%size == size-1)
                        cout<<"---"<<endl;
                    else if(j%size == 0)
                        cout<<"   ---|";
                    else
                        cout<<"---|";
                }
            }
        
        }
        else 
            cout<<" | "<<grid[i];   
    }
}

bool tictactoe::isWon(){
    int tmpA, tmpB;
    int ind=0;
    for (int i=0; i<size; i++)
    {
        tmpA=0;
        tmpB=0;
        for (int j=0; j<size; j++)
        {
            ind = j+i*size;
            //ind = i + j*size;           (pionowe?)
            if(grid[ind] == grid[ind+1] && grid[ind] != ' '){
                
                tmpA++;
                if(tmpA == required)
                    return true;
            }
        }  
    }
    return false;
}

bool tictactoe::isDraw(){
    if(played == size*size && !isWon()){
        return true;
    }
    else 
        return false;
}

void tictactoe::play(){
    int x, y;
    int choice;
    played=0;

    system("clear");
    cout<<"KÓŁKO I KRZYŻYK"<<endl;
    cout<<"Zaczyna kółko"<<endl;
    displayGrid();
    
    do{
        if(played%2==0){
            cout<<endl<<"Gdzie postawić kółko?"<<endl;
            cin>>x;
            cin>>y;
            while (x<1 || x>size || y<1 || y>size){
                cout<<"Wychodzisz poza index! Podaj inne pole."<<endl;
                cin>>x;
                cin>>y;  
            }
            choice = x + size * (y-1) - 1;
            while (grid[choice] == 'O' || grid[choice] == 'X'){
                cout<<"To pole jest zajęte, wybierz inne!"<<endl;
                cin>>x;
                cin>>y;
                choice = x + size * (y-1) - 1;
            }
            setFigure(choice, 'O');
        }    
        else{
            cout<<endl<<"Gdzie postawić krzyżyk?"<<endl;
            cin>>x;
            cin>>y;
            while (x<1 || x>size || y<1 || y>size){
                cout<<"Wychodzisz poza index! Podaj inne pole."<<endl;
                cin>>x;
                cin>>y;  
            }
            choice = x + size * (y-1) - 1;
            while (grid[choice] == 'O' || grid[choice] == 'X'){
                cout<<"To pole jest zajęte, wybierz inne!"<<endl;
                cin>>x;
                cin>>y;
                choice = x + size * (y-1) - 1;
            }
            setFigure(choice, 'X');
        }
        system("clear");
        displayGrid();
        played++;
    }while (!isDraw() && !isWon());
    system("clear");
    displayGrid();
    if(isWon()){
        if(played%2==1){
            cout<<"Wygrało kółko!"<<endl;
        }
        else{
            cout<<"Wygrał krzyżyk!"<<endl;
        }
    }
    else if(isDraw()){
        cout<<"Remis i chuj."<<endl;
    }
}












if(x<=size-required && grid[x][y] != ' ' ){
                tmpA=0;
                for (int i=0; i<required; i++){
                    if(grid[x][y] == grid[x+i][y])
                        tmpA++;
                    else break;
                }
                //cout<<"Kurew konfidenckich poziomo "<<tmpA<<endl;
                if (tmpA == required)
                    return true;
            }
            if(y<=size-required && grid[x][y] != ' '){
                tmpB=0;
                for (int i=0; i<required; i++){
                    if(grid[x][y] == grid[x][y+i])
                        tmpB++;
                    else break;                    
                }
                //cout<<"Kurew konfidenckich pionowo "<<tmpB<<endl;
                if (tmpB == required)
                    return true;
            }
            if(x<=size-required && y<=size-required && grid[x][y] != ' '){
                tmpC=0;
                for (int i=0; i<required; i++){
                    if(grid[x][y] == grid[x+i][y+i])
                        tmpC++;
                    else break;  
                }
                //cout<<"Kurew konfidenckich skosnie- "<<tmpA<<endl;
                if (tmpC == required)
                    return true;
            }
            if(x<=required && y<=required && grid[x][y] != ' '){
                tmpD=0;
                for (int i=0; i<required; i++){
                    if(grid[x][y] == grid[x+i][y-i])
                        tmpD++;
                    else break;  
                }
                //cout<<"Kurew konfidenckich skosnie+ "<<tmpA<<endl;
                if (tmpD == required)
                    return true;
            }



std::pair<int,int> tictactoe::minimax(int depth, bool isMax){
    minmax++;
    if(isWon()){
        if(played%2==1)
            return 10-depth;
        else
            return -10+depth;
    }
    else if (isDraw())
        return 0;
    
    //maksymalizacja
    if (isMax)
    {
        int best = -1000;
        for (int y=0; y<size; y++){
            for (int x=0; x<size; x++){
                if (grid[x][y] == ' ')
                {
                    grid[x][y]='X';
                    played++;

                    best = std::max(best, minimax(depth + 1, !isMax));

                    // Undo the move
                    grid[x][y] = ' ';
                    played--;
                }
            }
        }
        return best;
    }

    //minimalizacja
    else
    {
        int best = 1000;
        for (int y=0; y<size; y++){
            for (int x=0; x<size; x++){
                if (grid[x][y] == ' ')
                {
                    grid[x][y]='O';
                    played++;
                    best = std::min(best, minimax(depth + 1, !isMax));

                    // Undo the move
                    grid[x][y] = ' ';
                    played--;
                }
            }
        }
        return best;
    }
}


std::pair<int,int> tictactoe::bestMove()
{
    int bestVal = -1000;
    int bestMove[2]={-1,-1};

    for (int y=0; y<size; y++){
        for (int x=0; x<size; x++){
            if (grid[x][y] == ' ')
            {
                grid[x][y]='O';
                played++;
                int moveValue = minimax(0, true);
                grid[x][y]=' ';
                played--;
                
                if (moveValue > bestVal)
                {
                    bestVal = moveValue;
                    bestMove[0] = x;
                    bestMove[1] = y;
                }
            }
        }
    }
    cout << "najlepszy ruch to: " << bestMove[0] << " " << bestMove[1] << endl;
    cout<<minmax<<endl;
   
}