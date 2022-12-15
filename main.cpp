//#include "Root.h"
#include "Root.h"
#include "Fraction.h"
#include <iostream>
#include <chrono>
#include <random>

template <class T> int demonstration(char*);
template<> int demonstration<Fraction>(char* wf);
int main()
{
    std::cout<<"Please specify the name of the file tree\n---> "<<std::ends;
    char filename[10];
    std::cin>>filename;
    std::cout<<"Select the type of object in file tree "<<filename<<"\n1) int\n2) Products\n---> "<<std::ends;
    short decision;
    while (true)
    {
        std::cin>>decision;
        switch(decision)
        {
            case(1):
            {
                return demonstration<int>(filename);
            }
            case(2):
            {
                return demonstration<Fraction>(filename);
            }
            default: std::cout<<"Please enter the correct number!";
        }
    }
}


template <class T> int demonstration(char* wf)
{
    Root<T> newRoot(wf);
    //Tree<T>* tTree;
    int decision; std::string input;
    while (true)
    {
        std::cout<<"What will we do?\n-1) Clean tree\n1) Print tree\n2) Add new object\n"
                   "3) Search object with name\n4) Delete object with name\n"
                   "5) Balancing tree\n6) Adding with random objects\n7) EXIT\n---> "<<std::ends;
        std::cin>>input;
        try
        {
            decision = stoi(input);
        }
        catch (std::invalid_argument &e) {
            //Говорим, что можно вводить только числа
            std::cerr << "Only numbers are allowed! \n";
            continue;
        }
        catch (std::out_of_range &e) {
            //Число не соответствует диапазону
            std::cerr << "Out of range! \n";
            continue;
        }
        switch (decision) {
            case(-1):
            {
                newRoot.clearFTree();
                break;
            }
            case(1):
            {
                std::cout<<newRoot<<std::endl;
                break;
            }
            case(2):
            {
                T newObj;
                std::cout<<"Object---> "<<std::ends;
                std::cin>>newObj;
                std::cout<<"Object has been written on position "<< newRoot.addValue(newObj)<<std::endl;
                break;
            }
            case(3):
            {
                T desiredObj;
                std::cout<<"Object---> "<<std::ends;
                std::cin>>desiredObj;
                long pos = newRoot.search(desiredObj);
                if (pos!=FNULL) std::cout << "Node has this position in file: " << pos << std::endl;
                break;
            }
            case(4):
            {
                T desiredObj;
                std::cout<<"Object---> "<<std::ends;
                std::cin>>desiredObj;
                if (newRoot.deleteVal(desiredObj)) std::cout << "Object " << desiredObj << " has been deleted" << std::endl;
                else std::cout<<"Incorrect name of object!"<<std::endl;
                break;
            }
            case(5):
            {
                newRoot.balance();
                break;
            }
            case(6):
            {
                std::cout<<"\nNumber of obj ---> "<<std::ends;
                std::cin>>input;
                try
                {
                    decision = stoi(input);
                    if (decision<0) throw std::out_of_range("less than zero");
                }
                catch (std::invalid_argument &e) {
                    //Говорим, что можно вводить только числа
                    std::cerr << "Only numbers are allowed! \n";
                    continue;
                }
                catch (std::out_of_range &e) {
                    //Число не соответствует диапазону
                    std::cerr << "Out of range! \n";
                    continue;
                }
                for (int i = 0; i < decision; ++i) {
                    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
                    std::default_random_engine e(seed);
                    T t = e()%1000;
                    newRoot.addValue(t);
                }
                break;
            }
            case(7): return 0;
            default: std::cout<<"Please enter the correct number!";
        }
    }
}
template<> int demonstration<Fraction>(char* wf)
{
    Root<Fraction> newRoot(wf);
    //Tree<Fraction>* tTree;
    int decision; std::string input;
    while (true)
    {
        std::cout<<"What will we do?\n-1) Clean tree\n1) Print tree\n2) Add new object\n"
                   "3) Search object with name\n4) Delete object with name\n"
                   "5) Balancing tree\n6) EXIT\n---> "<<std::ends;
        std::cin>>input;
        try
        {
            decision = stoi(input);
        }
        catch (std::invalid_argument &e) {
            //Говорим, что можно вводить только числа
            std::cerr << "Only numbers are allowed! \n";
            continue;
        }
        catch (std::out_of_range &e) {
            //Число не соответствует диапазону
            std::cerr << "Out of range! \n";
            continue;
        }
        switch (decision) {
            case(-1):
            {
                newRoot.clearFTree();
                break;
            }
            case(1):
            {
                std::cout<<newRoot<<std::endl;
                break;
            }
            case(2):
            {
                Fraction newObj;
                std::cout<<"Object---> "<<std::ends;
                std::cin>>newObj;
                std::cout<<"Object has been written on position "<< newRoot.addValue(newObj)<<std::endl;
                break;
            }
            case(3):
            {
                Fraction desiredObj;
                std::cout<<"Object---> "<<std::ends;
                std::cin>>desiredObj;
                long pos = newRoot.search(desiredObj);
                if (pos!=FNULL) std::cout << "Node has this position in file: " << pos << std::endl;
                break;
            }
            case(4):
            {
                Fraction desiredObj;
                std::cout<<"Object---> "<<std::ends;
                std::cin>>desiredObj;
                if (newRoot.deleteVal(desiredObj)) std::cout << "Object " << desiredObj << " has been deleted" << std::endl;
                else std::cout<<"Incorrect name of object!"<<std::endl;
                break;
            }
            case(5):
            {
                newRoot.balance();
                break;
            }
            case(6): return 0;
            default: std::cout<<"Please enter the correct number!";
        }
    }
}