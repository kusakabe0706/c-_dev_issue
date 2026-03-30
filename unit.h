
#pragma once
#include <string>
#include "status.h"
#include "commandData.h"

class Unit{
    protected:
    std::string name;
    Status status;
    CommandData select_cmd;
    Unit* target;

    public:
    Unit(std::string nm);
    virtual ~Unit() = default;

    std::string getName() const;
    Status* getStatus();
    CommandData getSelectCmd() const;
    Unit* get_target() const;

    void set_target(Unit* t);

    bool is_alive() const;
    virtual void cmd_select() = 0;
    void random_status();
};
