
#pragma once
#include <string>
#include "status.h"
#include "commandstruct.h"
using namespace std;

class Unit{
    protected:
    string name;
    Status status;
    CommandData select_cmd;
    Unit* target;

    public:
    Unit(string nm);
    virtual ~Unit() = default;

    string get_name() const;
    Status& get_status();
    CommandData get_select_cmd() const;
    Unit* get_target() const;

    void set_target(Unit* t);

    bool is_alive() const;
    virtual void cmd_select() = 0;
    void random_status();
};
