#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "Concurrent/readwritelock.h"
#include "Concurrent/simplethreadpool.h"
#include <vector>
#include <functional>
#include <algorithm>

namespace event {

using namespace concurrent;

// place holders for the event arguments
const std::_Placeholder<1> _1_ =std::placeholders::_1;
const std::_Placeholder<2> _2_ =std::placeholders::_2;
const std::_Placeholder<3> _3_ =std::placeholders::_3;
const std::_Placeholder<4> _4_ =std::placeholders::_4;
const std::_Placeholder<5> _5_ =std::placeholders::_5;
const std::_Placeholder<6> _6_ =std::placeholders::_6;
const std::_Placeholder<7> _7_ =std::placeholders::_7;
const std::_Placeholder<8> _8_ =std::placeholders::_8;
const std::_Placeholder<9> _9_ =std::placeholders::_9;
const std::_Placeholder<10> _10_ =std::placeholders::_10;
const std::_Placeholder<11> _11_ =std::placeholders::_11;
const std::_Placeholder<12> _12_ =std::placeholders::_12;
const std::_Placeholder<13> _13_ =std::placeholders::_13;
const std::_Placeholder<14> _14_ =std::placeholders::_14;
const std::_Placeholder<15> _15_ =std::placeholders::_15;
const std::_Placeholder<16> _16_ =std::placeholders::_16;
const std::_Placeholder<17> _17_ =std::placeholders::_17;
const std::_Placeholder<18> _18_ =std::placeholders::_18;
const std::_Placeholder<19> _19_ =std::placeholders::_19;
const std::_Placeholder<20> _20_ =std::placeholders::_20;
const std::_Placeholder<21> _21_ =std::placeholders::_21;
const std::_Placeholder<22> _22_ =std::placeholders::_22;
const std::_Placeholder<23> _23_ =std::placeholders::_23;
const std::_Placeholder<24> _24_ =std::placeholders::_24;
const std::_Placeholder<25> _25_ =std::placeholders::_25;
const std::_Placeholder<26> _26_ =std::placeholders::_26;
const std::_Placeholder<27> _27_ =std::placeholders::_27;
const std::_Placeholder<28> _28_ =std::placeholders::_28;
const std::_Placeholder<29> _29_ =std::placeholders::_29;

/**
 * @brief An event connection is the association and channel between an event publisher and an event listener.
 * The listener object can aquire a connection by calling EventHandler::subscribe() method to subscribe the event
 * from the event publisher, see EventHandler::subscribe() for details. The connection can be closed by
 * calling EventConnection::close() when it not be needed. The connection should be closed before the listener
 * object be destroied, or a wild pointer would be called when the event occurring. The EventConnection object
 * would self-destruct after it be closed by both listener and publisher, so, DO NOT delete the EventConnection
 * object explicitly.
 * @note All public method of this template are thread-safe.
 */
class EventConnection {
private:
    bool _closed = false;
protected:
    mutable ReadWriteLock rwLock;
    const bool& closed = this->_closed;
public:
    bool isClosed() const { ReadLock lock(rwLock); return this->_closed; }
    void close() {
        {
            WriteLock lock(rwLock);
            if(!this->_closed) {
                this->_closed = true;
                return;
            }
        }
        delete this;
    }

    virtual ~EventConnection() {}
};

using std::vector;
using std::for_each;
using std::function;
using std::bind;
using std::mem_fn;

/**
 * @brief The EventHandler is the template of manager of the event subscriptions. The event publisher
 * should prepare one EventHandler instance for each kind of event it would send, and publish the const
 * reference or pointer to the listeners. The event listeners can subscribe the event interested by calling
 * EventHandler::subscribe(). When the event occurred, The publisher can trigger the corresponding
 * EventHandler by calling EventHandler::trigger() to notify all connected listeners. Alternatively,
 * The publisher can also call listening methods of all listeners synchronously in current thread by calling
 * EventHandler::call().
 * The best practice of use:
 * @code
 * typedef EventHandler<void, int> DataChangedEvent; //define an event type.
 *
 * class Publisher {
 * private:
 *     int i;
 *     DataChangedEvent _dataChangedEvent; // define an event handler instance.
 * public:
 *     ...
 *     // publish the const reference to allow listeners to subscribe.
 *     const DataChangedEvent& dataChangedEvent =this->_dataChangedEvent;
 *     void setI( int value ) {
 *         if(this->i != value) }
 *              this->i = value;
 *              this->_dataChangedEvent.trigger(value); //trigger a event, the listening methods of listeners would be invoked with the value.
 *         }
 *     }
 * }
 *
 * class Listener {
 * private:
 *     EventConnection* connection;
 *     // the event listening method. it would be called when the event occur.
 *     void onPubChanged(int newValue) {
 *         // do something with new value of the publisher .
 *         ...
 *     }
 * public:
 *     Listener(const Publisher& pub) {
 *          //subscribe the event, and keep the connection.
 *          this->connection = pub.subscribe(this, &Listener::onPubChanged, _1_);
 *     }
 *     ~Listener() {
 *          this->connection->close(); // close the event connection before destruction.
 *     }
 * }
 *
 * @param RET the type of return value of the event. //TODO: not implement yet. only void is allowed.
 * @param ARGS the types of event arguments.
 * @note All public method of this template are thread-safe.
 */
template<typename RET, typename ... ARGS>
class EventHandler
{
public:
    typedef function<RET(ARGS...)> Listener;
private:
    class Connection : public EventConnection {
    private:
        Listener listener;
    public:
        Connection(const Listener& listener) : listener(listener) {}
        void call(ARGS... args) const {
            ReadLock lock(this->rwLock);
            if(!this->closed)
                this->listener(args...);
        }
    };

    class RunnableWrapper : public Runnable {
    private:
        function<void()> fn;
    public:
        RunnableWrapper(const Connection* core, ARGS... args) :
            fn(bind(&Connection::call, core, args...)) {}
        void run() { this->fn(); }
        void done() { delete this; }
    };

    mutable vector<Connection*> listeners;
    mutable ReadWriteLock rwlock;
    const AbstractThreadPool& tPool;

    void triggerOne(Connection* listener, ARGS... args) const {
        if(!listener->isClosed())
            this->tPool.start(new RunnableWrapper(listener, args...));
    }

public:

    EventHandler(const AbstractThreadPool& tPool=SimpleThreadPool::DEFAULT) :
        tPool(tPool) {}

    ~EventHandler() {
        WriteLock lock(rwlock);
        for_each(this->listeners.begin(), this->listeners.end(), mem_fn(&Connection::close));
        this->listeners.clear();
    }

    /**
     * @brief subscribe //TODO: Doc it.
     * @param listeningFunction
     * @return
     */
    EventConnection* subscribe(const Listener& listeningFunction) const {
        WriteLock lock(rwlock);

        Connection* result = new Connection(listeningFunction);
        listeners.push_back( result );
        return result;
    }

    template<class ListenerClass, typename METHOD_RET, typename ...METHOD_ARGS, typename ...PLACEHOLDERS>
    /**
     * @brief subscribe  //TODO: Doc it.
     * @param listeningObject
     * @param phs
     * @return
     */
    EventConnection* subscribe(ListenerClass* listeningObject, METHOD_RET (ListenerClass::*listeningMethod)(METHOD_ARGS...), PLACEHOLDERS... phs) const {
        return this->subscribe(bind(listeningMethod, listeningObject, phs...));
    }

    /**
     * @brief trigger //TODO: Doc it.
     * @param args
     */
    void trigger(ARGS... args) {
        ReadLock lock(rwlock);
        for_each(this->listeners.cbegin(), this->listeners.cend(),
                 bind(&EventHandler<RET, ARGS...>::triggerOne, this, _1_, args...));
    }

    /**
     * @brief call //TODO: Doc it.
     * @param args
     */
    void call(ARGS... args) {
        ReadLock lock(rwlock);
        for_each(this->listeners.cbegin(), this->listeners.cend(),
                      mem_fn(&Connection::call, args...));
    }
};

/**
 * @brief NotifyEventHandler  //TODO: Doc it.
 */
typedef EventHandler<void> NotifyEventHandler;
/**
 * @brief IntegerNotifyEventHandler  //TODO: Doc it.
 */
typedef EventHandler<void, int> IntegerNotifyEventHandler;

} // namespace event
#endif // EVENTHANDLER_H
