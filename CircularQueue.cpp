#include <iostream>

using namespace std;

int waitingRoomQueue[5], queueFront{-1},queueEnd{-1};

struct Owner{
    int ID{};
    string name;
    int phone{};
}owners[10];

struct Cat{
    string catName;
    Owner owner{};
}cats[10];

Owner OwnerSearchByName(string);

void CatRegister(bool &);
int CatArraySize();

int QueueSize();
void Push(int &);
int Pop();
bool IsEmpty();
bool IsFull();

int main(){
    bool ended = false, catFull = false;
    int option, catIndex{}, servedCatIndx{};

    Cat servedCat;

    while (!ended){
        cout<<"Welcome to Happy Paws!"<<"\n"
        <<"What do you want to do?"<<"\n"
        <<"1- Register Today Cats"<<"\n"
        <<"2- Enter a cat to the wait room"<<"\n"
        <<"3- Serve a cat"<<"\n"
        <<"4- EXIT"<<"\n";
        cin>>option;

        switch (option) {
            case 1:
                if(!catFull){
                    CatRegister(catFull);
                } else {
                    cout<<"--------There is no more space for Today :(--------"<<"\n";
                }
                break;
            case 2:
                if(catIndex < CatArraySize()){
                    Push(catIndex);
                } else {
                    cout<<"--------All cats for today were served :)--------"<<"\n";
                }
                break;
            case 3:
                if(!IsEmpty()) {
                    servedCatIndx = Pop();
                    servedCat = cats[servedCatIndx];
                    cout << "**** Cat's name: " << servedCat.catName << "\n"
                         << "**** Owner's ID: " << servedCat.owner.ID << "\n"
                         << "**** Owner's name: " << servedCat.owner.name << "\n"
                         << "**** Owner's phone number: " << servedCat.owner.phone << "\n";
                } else {
                    cout<<"--------The waiting room is empty :)--------"<<"\n";
                }
                break;
            case 4:
                ended = true;
                break;
            default:
                cout<<"--------INVALID OPTION SHUTTING DOWN THE PROGRAM...--------"<<"\n";
                ended = true;
        }
    }

    return 0;
}


Owner OwnerSearchByName(string ownerName){
    int count = 0;

    for(auto & owner : owners){
        count++;
        if(owner.name.empty()){
            cout<<"--------This owner is not registered jet--------"<<"\n"
            <<"Enter the owner's phone number: "<<"\n";
            cin>>owner.phone;
            owner.name = ownerName;
            owner.ID = count;
            return owner;
        } else {
            if(owner.name == ownerName) {
                return owner;
            }
        }
    }
}

void CatRegister(bool &full){

    string ownerName;

    for(int i = 0; i < CatArraySize(); i++){
        cout<<"Enter cat's name"<<"\n"
            <<"Cat name: ";
        cin>>cats[i].catName;
        cout<<"Enter the owner name"<<"\n"
            <<"Owner: ";
        cin>>ownerName;

        cats[i].owner = OwnerSearchByName(ownerName);
    }
    full = true;
}
int CatArraySize(){
    return sizeof(cats)/sizeof(Cat);
}

int QueueSize(){
    return sizeof(waitingRoomQueue)/sizeof(int);
}

void Push(int &catIndex){
    if(!IsFull()) {
        if (IsEmpty()) {
            queueFront = 0;
        }
        queueEnd = (queueEnd + 1) % QueueSize();
        waitingRoomQueue[queueEnd] = catIndex;
        cout<<"--------New cat entered to the waiting room--------"<<"\n";
        catIndex++;
    } else {
        cout<<"--------There is no more space in the wait room :(--------"<<"\n";
    }
}

int Pop(){
    int catIndex;

    if(!IsEmpty()){
        catIndex = waitingRoomQueue[queueFront];
        if(queueFront == queueEnd){
            queueEnd = queueFront = -1;
        } else {
            queueFront = (queueFront +1) % QueueSize();
        }
        return catIndex;
    } else {
        cout<<"--------The waiting room is empty :)--------"<<"\n";
        return -1;
    }
}

bool IsEmpty(){
    return queueFront == -1;
}

bool IsFull(){
    if (queueFront == 0 && queueEnd == QueueSize() - 1) {
        return true;
    }
    if (queueEnd == queueFront - 1) {
        return true;
    } else {
        return false;
    }
}