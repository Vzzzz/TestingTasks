#include <cstdio>
#include <map>
#include <string>

using namespace std;

class cAnimal
{
public:
    virtual string getType() { return "undefined"; };
};

class cElephant : public cAnimal
{
public: 
    string getType() { return "Elephant"; };    
};

class cRabbit : public cAnimal
{
public: 
    string getType() { return "Rabbit"; };
};

class cHyena : public cAnimal
{
public: 
    string getType() { return "Hyena"; };
};

class cKangaroo : public cAnimal
{
public: 
    string getType() { return "Kangaroo"; };
};

class cZebra : public cAnimal
{
public: 
    string getType() { return "Zebra"; };
};

class cFox : public cAnimal
{
public: 
    string getType() { return "Fox"; };
};

struct cCell
{
    cCell* next;
    cAnimal* animal;
};

class cZoo
{
private:
    int count;
    cCell* head;
public:
    cZoo() { count = 0; head = NULL; };
    ~cZoo();
    void AddAnimal(cAnimal* animal);
    void RemoveAnimal(int number);
    int AnimalsCount() { return count; };
    void EnumerateAnimals();
};

cZoo::~cZoo()
{
    while(head != NULL)
    {
        cCell* tmp = head->next;
        delete head;
        head = tmp;
    }
}

void cZoo::AddAnimal(cAnimal* animal)
{
    if(animal != NULL)
    {
        cCell* cell = new cCell;
        cell->next = head;
        cell->animal = animal;
        head = cell;
        count++;
    }
}

void cZoo::EnumerateAnimals()
{
    if(count == 0)
    {
        printf("Trere are no animals in the zoo\n");
        return;
    }
    map<string, int> zooMap;
    auto cell = head;
    while(cell != NULL)
    {
        if(zooMap.count(cell->animal->getType()))
        {
            zooMap[cell->animal->getType()]++;
        }
        else
        {
            zooMap[cell->animal->getType()] = 1;
        }
        cell = cell->next;
    }
    printf("There are:\n");
    for(auto i = zooMap.begin(); i != zooMap.end(); i++)
    {
        printf("\t%s:\t%d\n", (*i).first.c_str(), (*i).second);
    }
    printf("Total:\t%d", count);
}

void cZoo::RemoveAnimal(int number)
{
    if(number < count && number > -1)
    {
        auto cell = head->next;
        if(number == 0)
        {
            delete head;
            head = cell;
        }
        else
        {
            auto prevCell = head;
            int i = 1;
            while(i < number)
            {
                cell = cell->next;
                prevCell = prevCell->next;
                i++;
            }
            prevCell->next = cell->next;
            delete cell;
        }
        count--;
    }
}

int main()
{
    cZoo* zoo = new cZoo();
    zoo->AddAnimal(new cFox());
    zoo->AddAnimal(new cFox());
    zoo->AddAnimal(new cZebra());
    zoo->AddAnimal(new cFox());
    zoo->EnumerateAnimals();
    printf("\n");
    zoo->RemoveAnimal(0);
    zoo->EnumerateAnimals();
    printf("\n");
    zoo->AddAnimal(new cRabbit());
    zoo->RemoveAnimal(3);
    zoo->EnumerateAnimals();
    printf("\n");
    delete zoo;
}
