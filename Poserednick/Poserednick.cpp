#include <iostream>
#include <string>

class Mediator;  // Декларація класу Mediator

// Colleague
class Colleague {
protected:
    Mediator* mediator;

public:
    Colleague(Mediator* mediator) : mediator(mediator) {}

    virtual void send(const std::string& message) const = 0;
    virtual void receive(const std::string& message) const = 0;
};

// Mediator
class Mediator {
public:
    virtual void mediate(const Colleague* sender, const std::string& message) const = 0;
};

// ConcreteColleagueA
class ConcreteColleagueA : public Colleague {
public:
    ConcreteColleagueA(Mediator* mediator) : Colleague(mediator) {}

    void send(const std::string& message) const override {
        mediator->mediate(this, message);
    }

    void receive(const std::string& message) const override {
        std::cout << "ConcreteColleagueA receives message: " << message << std::endl;
    }
};

// ConcreteColleagueB
class ConcreteColleagueB : public Colleague {
public:
    ConcreteColleagueB(Mediator* mediator) : Colleague(mediator) {}

    void send(const std::string& message) const override {
        mediator->mediate(this, message);
    }

    void receive(const std::string& message) const override {
        std::cout << "ConcreteColleagueB receives message: " << message << std::endl;
    }
};

// ConcreteMediator
class ConcreteMediator : public Mediator {
private:
    const ConcreteColleagueA* colleagueA;
    const ConcreteColleagueB* colleagueB;

public:
    void setColleagues(const ConcreteColleagueA* a, const ConcreteColleagueB* b) {
        colleagueA = a;
        colleagueB = b;
    }

    void mediate(const Colleague* sender, const std::string& message) const override {
        if (sender == colleagueA) {
            colleagueB->receive(message);
        }
        else if (sender == colleagueB) {
            colleagueA->receive(message);
        }
    }
};

int main() {
    ConcreteMediator mediator;

    ConcreteColleagueA colleagueA(&mediator);
    ConcreteColleagueB colleagueB(&mediator);

    mediator.setColleagues(&colleagueA, &colleagueB);

    colleagueA.send("Hello from Colleague A!");
    colleagueB.send("Hi from Colleague B!");

    return 0;
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
