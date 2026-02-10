#ifndef STATE_AMR_H
#define STATE_AMR_H
#include <string>
// state design pattern + singleton
enum class AMRStateType{
    IDLE,
    BUSY,
    ERROR
};

class StateAMR;
class IStateAMR
{
    public:
        virtual std::string name() const = 0;
        virtual ~IStateAMR() = default;
        virtual void onEnter() = 0;
        virtual void onExit() = 0;
};

class IdleStateAMR : public IStateAMR
{
    public:
        static IdleStateAMR& instance();
        std::string name() const override;
        void onEnter(void) override;
        void onExit(void) override;
};

class BusyStateAMR : public IStateAMR
{
    public:
        static BusyStateAMR& instance();
        std::string name() const override;
        void onEnter(void) override;
        void onExit(void) override;
        
};

class ErrorStateAMR : public IStateAMR
{
    public:
        static ErrorStateAMR& instance();
        std::string name() const override;
        void onEnter(void) override;
        void onExit(void) override;
};

class StateAMR
{
    private:
        IStateAMR *state_;
        StateAMR():state_(&IdleStateAMR::instance()){};
    public:
        static StateAMR& instance();
        void changeState(IStateAMR& newState);
        std::string nameState() const;
};
#endif