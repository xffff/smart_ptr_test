/* test out unique_ptr because i'm going to use it in a project */

#include <iostream>
#include <vector>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

class Derived;
class Base {
public:
    Base();
    Base(int, int) {}; // dummy
    Base(int numDerived);
    std::unique_ptr<Derived> derivedClassPtr;
    std::vector<std::unique_ptr<Derived>> vDerivedClassPtr;
    std::vector<std::vector<float>> getVals();
private:
    int numDerived;
    int genRand() { return rand() % 10; };
};

class Derived : public Base {
public:
    Derived(float x, float y) : x(x), y(y), Base(0,0)
	{};
    float x,y;
};

Base::Base()
{
    std::unique_ptr<Derived> temp(new Derived(genRand(),genRand()));
    derivedClassPtr = std::move(temp);
}

Base::Base(int numDerived) : numDerived(numDerived)
{
    std::cout<<"Number of derived classes being created: "
	     <<this->numDerived<<std::endl;

    std::vector<int> rvals;
    for(int j=0; j<numDerived*2; j++)
	rvals.push_back(genRand());
    
    for(int i=0; i<numDerived; i++) {
	int x = rvals[i];
	int y = rvals[i+1];
	
    	std::unique_ptr<Derived> temp(new Derived(x,y));
    	vDerivedClassPtr.push_back(std::move(temp));
    }
}

int main()
{
    srand(time(NULL));
    std::unique_ptr<int> a(new int(100));
    std::cout<<"A unique pointer: "<<*a<<std::endl;

    std::vector<std::unique_ptr<int>> v;
    for(int i=0; i<10; i++) {
	std::unique_ptr<int> temp(new int(i));
	v.push_back(std::move(temp));
    }

    for(auto& i : v)
	std::cout<<"Unique pointer in a vector: "<<*i<<std::endl;

    /* first do this with a single entity of unique pointer to derived class */
    Base* baseClass = new Base();
    std::cout<<"Derived Class X: "<<baseClass->derivedClassPtr->x<<std::endl
	     <<"Derived Class Y: "<<baseClass->derivedClassPtr->y<<std::endl;
    delete baseClass;

    /* now create an arbirtrary number of derived classes
     * and shove the lot in a vector
     */
    int nDerived = 10;
    Base* vBaseClass = new Base(nDerived); // different constructor
    for(int i=0; i<nDerived; i++)
	std::cout<<i<<": "<<vBaseClass->vDerivedClassPtr[i]->x
		 <<", "<<vBaseClass->vDerivedClassPtr[i]->y<<std::endl;
    delete vBaseClass;
    return 0;
}
