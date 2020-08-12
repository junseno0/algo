#include <iostream>
#include <string>
#include <memory>
using namespace std;

class Component {
public:
    Component() {
        std::cout<<"Component constructed.\n\n";
    }
    virtual ~Component() {
        std::cout<<"Component destructed.\n\n";
    }
};

class SimpleComponent : public Component {
public:
    SimpleComponent() {
        std::cout<<"SimpleComponent constructed.\n\n";
    }
    virtual ~SimpleComponent() {
        std::cout<<"SimpleComponent destructed.\n\n";
    }
};

class ComponentInterfaceHelper {
public:
    ComponentInterfaceHelper() {
        std::cout<<"ComponentInterfaceHelper contructed.\n\n";
    }
    virtual ~ComponentInterfaceHelper() {
        std::cout<<"ComponentInterfaceHelper destructed.\n\n";
    }
};

class AvcComponent : public SimpleComponent, public ComponentInterfaceHelper {
public:
    AvcComponent() {
        std::cout<<"AvcComponent constructed.\n\n";
    }
    ~AvcComponent() {
        std::cout<<"AvcComponent destructed.\n\n";
    }
};
int main() {
    {
        std::cout<<"-------------------------------------------\n\n";
        std::shared_ptr<AvcComponent> comp = std::make_shared<AvcComponent>();
        std::cout<<"make component succeed.\n\n";
    }
    {
        std::cout<<"-------------------------------------------\n\n";
        std::shared_ptr<Component> comp = std::make_shared<AvcComponent>();
        std::cout<<"make component by AvcComponent succeed.\n\n";
    }
    {
        std::cout<<"-------------------------------------------\n\n";
        Component* comp = new AvcComponent();
        std::cout<<"make component by new AvcComponent succeed.\n\n";
        delete comp;
    }
    return 0;
}