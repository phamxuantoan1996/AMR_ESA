#ifndef EVENT_BUS_H
#define EVENT_BUS_H

#include <functional>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <memory>

#include "state_amr.h"

class EventBus {
    private:
        EventBus() = default;
        using RawHandler = std::function<void(const void*)>;
        std::unordered_map<std::type_index, std::vector<RawHandler>> subscribers_;
    public:
        static EventBus& instance() {
            static EventBus bus;
            return bus;
        }
        template<typename Event>
        using Handler = std::function<void(const Event&)>;

        template<typename Event>
        void subscribe(Handler<Event> handler)
        {
            auto& handlers = subscribers_[std::type_index(typeid(Event))];
            handlers.push_back(
                [handler](const void* event) {
                    handler(*static_cast<const Event*>(event));
                }
            );
        }

        template<typename Event>
        void publish(const Event& event)
        {
    auto it = subscribers_.find(std::type_index(typeid(Event)));
    if (it != subscribers_.end()) {
                if (it == subscribers_.end())
                    return;
                for (const auto& handler : it->second) {
                    handler(&event);
                }
            }
        }
};


#endif